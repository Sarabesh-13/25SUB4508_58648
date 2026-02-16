/*
 * File: ServerMain.cpp
 * Purpose: Entry point for the DCRMS Server application.
 *
 * This file performs the system startup sequence:
 * 1. Sets up the signal handler for graceful shutdown (Ctrl+C).
 * 2. Initializes the Logger and ConfigParser.
 * 3. Creates the Registry (Database) and Policy Engine.
 * 4. Starts the main TunnelService loop to listen for connections.
 */

#include <TunnelService.hpp>
#include <RegistryManager.hpp>
#include <PolicyEngine.hpp>
#include <Logger.hpp>
#include <ConfigParser.hpp>

#include <iostream>
#include <csignal>
#include <unistd.h>
#include <stdexcept>

// Global pointer allows the static signal handler to access the running service
TunnelService* g_tunnelService = nullptr;

// Signal Handler: Catches Ctrl+C to ensure we save state/notify nodes before dying
void handleSignal(int signum) {
    if (g_tunnelService) {
        std::cout << "\n[OPERATIONAL] Caught Signal " << signum << ". Stopping Server..." << std::endl;
        g_tunnelService->shutdown(); // Broadcast shutdown packet to all nodes
    }
    //exit(0); 
}

// Visual banner to show the admin that the server is ready
void printBanner(int port) {
    std::cout << "\n";
    std::cout << "======================================================\n";
    std::cout << "            SECURE DCRMS PORTAL STARTED               \n";
    std::cout << "======================================================\n";
    std::cout << " [OPERATIONAL] Logger Initialized                     \n";
    std::cout << " [OPERATIONAL] Configuration Loaded                   \n";
    std::cout << " [OPERATIONAL] Registry & Policy Engine Ready         \n";
    std::cout << " [OPERATIONAL] Listening on Port: " << port << "                 \n";
    std::cout << "======================================================\n";
    std::cout << " >> Server is running. Press Ctrl+C to shutdown.\n\n";
}

int main(int argc, char** argv) {
    try {
        // 1. Setup Signal Handling (Ctrl+C)
        std::signal(SIGINT, handleSignal); 

        // 2. Initialize the centralized Logger
        Logger::getInstance().init("logs/server.log");
        
        // 3. Load Server Configuration
        ConfigParser config;
        // Safe check for config loading
        if (!config.load("config/server.conf")) {
             // Continue with defaults if missing
        }

        // 4. Initialize Core Components
        RegistryManager registry;       // The "Phonebook" of nodes
        PolicyEngine policy(registry);  // The "Brain" for redirection logic
        
        int port = config.getInt("port", 8080);
        int maxConn = config.getInt("max_connections", 100);

        // 5. Create the Network Service
        TunnelService tunnel(port, maxConn, registry, policy);
        
        // Assign global pointer so the signal handler can stop the tunnel
        g_tunnelService = &tunnel;

        // 6. Show Banner and Start Blocking Loop
        printBanner(port);
        tunnel.start();

    } catch (const std::exception& e) {
        std::cerr << "[CRITICAL] Server Startup Failed: " << e.what() << std::endl;
        return 1;
    } catch (...) {
        std::cerr << "[CRITICAL] Server Startup Failed: Unknown Error" << std::endl;
        return 1;
    }

    return 0;
}