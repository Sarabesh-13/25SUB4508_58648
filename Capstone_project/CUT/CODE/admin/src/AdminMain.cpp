/*
 * File: AdminMain.cpp
 * Purpose: Entry point for the DCRMS Administrative Tool.
 *
 * This file performs the initial setup for the Admin Console:
 * 1. Initializes the admin-specific log file.
 * 2. Loads server connection details (IP, Port, Secret Key) from 'admin.conf'.
 * 3. Launches the interactive Admin Console shell.
 */

#include <AdminConsole.hpp>
#include <Logger.hpp>
#include <ConfigParser.hpp>
#include <iostream>
#include <stdexcept>

int main() {
    try {
        // 1. Initialize Logger for the Admin tool
        Logger::getInstance().init("logs/admin.log");

        // 2. Load configuration settings
        ConfigParser config;
        
        // Attempt to load specific admin config, fallback to default if missing
        if (!config.load("config/admin.conf")) {
            Logger::getInstance().log(LogLevel::ADVISORY, "ADMIN", "Config 'admin.conf' not found. Using internal defaults.");
        }

        // 3. Extract connection parameters
        std::string ip = config.getString("server_ip", "127.0.0.1");
        int port = config.getInt("server_port", 8080);
        std::string key = config.getString("admin_key", "MY_SECURE_KEY_123");

        // 4. Create and start the Admin Console interface
        AdminConsole admin(ip, port, key);
        admin.run();

    } catch (const std::exception& e) {
        std::cerr << "[CRITICAL] Admin Console Crash: " << e.what() << std::endl;
        return 1;
    } catch (...) {
        std::cerr << "[CRITICAL] Admin Console Crash: Unknown Error" << std::endl;
        return 1;
    }

    // Clean exit allows destructors to run (Happy Valgrind)
    return 0;
}