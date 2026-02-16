/*
 * File: HeartbeatManager.cpp
 * Purpose: Implementation of the background timer.
 *
 * This file contains the logic to check the clock. 
 * - Every 1 second, it sends a network packet (Heartbeat).
 * - Every 10 seconds, it logs a "Trace" message so you know the system is alive
 * without flooding your screen.
 */

#include <HeartbeatManager.hpp>
#include <Logger.hpp>
#include <stdexcept>

HeartbeatManager::HeartbeatManager() {
    // Initialize the timers to "now" when the program starts
    lastBeatTime = std::chrono::steady_clock::now();
    lastLogTime = std::chrono::steady_clock::now();
}

void HeartbeatManager::update(NodeController& controller) {
    // Wrap heartbeat logic in try-catch to prevent background thread crashes
    try {
        auto now = std::chrono::steady_clock::now();
        
        // 1. Check Heartbeat Interval (1 second)
        auto durationBeat = std::chrono::duration_cast<std::chrono::seconds>(now - lastBeatTime).count();
        
        if (durationBeat >= beatIntervalSec) {
            // Trigger the controller to actually send the packet
            controller.sendKeepAlive();
            lastBeatTime = now;
        }

        // 2. Check Log Interval (10 seconds)
        auto durationLog = std::chrono::duration_cast<std::chrono::seconds>(now - lastLogTime).count();
        
        if (durationLog >= logIntervalSec) {
            // We use the new TRACE level here so it doesn't clutter the main logs
            // unless you specifically ask for deep debugging.
            Logger::getInstance().log(LogLevel::TRACE, "HEARTBEAT", "Pulse active. System stable.");
            lastLogTime = now;
        }
    } catch (const std::exception& e) {
        // Log the error but don't stop the heartbeat manager
        Logger::getInstance().log(LogLevel::ADVISORY, "HEARTBEAT", "Pulse Error: " + std::string(e.what()));
    } catch (...) {
        // Swallow unknown errors to keep the system alive
    }
}