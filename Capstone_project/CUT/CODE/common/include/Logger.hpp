/*
 * File: Logger.hpp
 * Purpose: Thread-safe system for recording application events.
 *
 * This class uses the "Singleton" pattern to ensure that every part of the 
 * system (Server, Node, Admin) writes to the same log file. 
 * It includes automatic "Log Rotation"—if the file grows larger than 5MB,
 * it archives the old one and starts fresh to save disk space.
 */

#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <string>
#include <mutex>
#include <fstream>

// The four levels of severity for our system
enum class LogLevel {
    OPERATIONAL, // Standard events (Server started, Node registered)
    ADVISORY,    // Potential issues (Node timed out, Connection rejected)
    CRITICAL,    // System failures (Socket error, Bind failed)
    TRACE        // Deep debugging (Heartbeat pulses, Packet raw data)
};

class Logger {
private:
    std::ofstream logFile;
    std::mutex logMutex;         // Protects the file from multiple threads writing at once
    std::string currentFilename;
    
    // Rotation Limit: 5 Megabytes
    const size_t MAX_LOG_SIZE = 5 * 1024 * 1024; 

    // Private Constructor: Prevents other classes from creating their own Logger
    Logger();
    ~Logger();

    // Prevent making copies of the logger
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

    // Checks the file size and renames the file if it's too big
    void rotateLogIfNeeded();

public:
    // Global access point to the single Logger instance
    static Logger& getInstance();

    // Opens the log file for writing (called once at startup)
    void init(const std::string& filename);

    // Main logging function: Level (Priority), Module (Where), Message (What)
    void log(LogLevel level, const std::string& module, const std::string& message);
};

#endif