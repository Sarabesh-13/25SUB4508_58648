/*
 * File: Logger.cpp
 * Purpose: Implementation of the thread-safe, rotating logger.
 *
 * This file handles the actual writing to the disk. It includes logic to:
 * 1. Create log directories automatically.
 * 2. Format timestamps and log levels into a readable string.
 * 3. Rename and archive log files when they exceed the 5MB size limit.
 */

#include <Logger.hpp>
#include <iostream>
#include <sstream>
#include <chrono>
#include <iomanip>
#include <filesystem>
#include <stdexcept>

Logger::Logger() {}

Logger::~Logger() {
    try {
        if (logFile.is_open()) {
            logFile.close();
        }
    } catch (...) {
        // Destructors should never throw
    }
}

Logger& Logger::getInstance() {
    // Guaranteed to be thread-safe in C++11 and later
    static Logger instance;
    return instance;
}

void Logger::init(const std::string& filename) {
    std::lock_guard<std::mutex> lock(logMutex);
    currentFilename = filename;

    try {
        // Ensure the logs/ directory exists before trying to open the file
        std::filesystem::path path(filename);
        if (path.has_parent_path()) {
            std::filesystem::create_directories(path.parent_path());
        }

        logFile.open(filename, std::ios::app);
        if (!logFile.is_open()) {
            std::cerr << "[CRITICAL] Failed to open log file: " << filename << std::endl;
        }
    } catch (const std::exception& e) {
        std::cerr << "[CRITICAL] Logger Init Error: " << e.what() << std::endl;
    }
}

void Logger::rotateLogIfNeeded() {
    if (!logFile.is_open()) return;

    try {
        // Check the current size of the file
        long currentPos = logFile.tellp();
        if (currentPos == -1) return;

        if (static_cast<size_t>(currentPos) >= MAX_LOG_SIZE) {
            logFile.close();

            // Create a backup filename with a timestamp (e.g., server.log.2026-02-12_08-55-00)
            auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
            std::stringstream ss;
            // Use local_time safely
            std::tm tmBuffer;
            localtime_r(&now, &tmBuffer); // Thread-safe version of localtime
            ss << std::put_time(&tmBuffer, "%Y-%m-%d_%H-%M-%S");
            
            std::string backupName = currentFilename + "." + ss.str();
            
            std::filesystem::rename(currentFilename, backupName);

            // Open a brand-new file for subsequent logs
            logFile.open(currentFilename, std::ios::app);
        }
    } catch (const std::exception& e) {
        // If rotation fails, we try to re-open the original file to keep logging
        std::cerr << "[CRITICAL] Log rotation failed: " << e.what() << std::endl;
        if (!logFile.is_open()) {
             logFile.open(currentFilename, std::ios::app);
        }
    }
}

void Logger::log(LogLevel level, const std::string& module, const std::string& message) {
    // Wrap logging in try-catch so logging errors don't crash the main app
    try {
        std::lock_guard<std::mutex> lock(logMutex);

        // Ensure the file hasn't grown too large before writing
        rotateLogIfNeeded();

        auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        std::tm tmBuffer;
        localtime_r(&now, &tmBuffer); // Thread-safe
        
        // Convert the enum to a human-readable string for the log file
        std::string levelStr;
        switch(level) {
            case LogLevel::OPERATIONAL: levelStr = "OPERATIONAL"; break;
            case LogLevel::ADVISORY:    levelStr = "ADVISORY";    break;
            case LogLevel::CRITICAL:    levelStr = "CRITICAL";    break;
            case LogLevel::TRACE:       levelStr = "TRACE";       break;
        }

        // Write the formatted entry to the file
        if (logFile.is_open()) {
            logFile << "[" << std::put_time(&tmBuffer, "%Y-%m-%d %H:%M:%S") << "] "
                    << "[" << levelStr << "] "
                    << "[" << module << "] "
                    << message << std::endl;
        }
    } catch (...) {
        // If logging fails, we silently ignore it to keep the server running
    }
}