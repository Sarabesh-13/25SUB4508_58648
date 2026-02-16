/*
 * File: AdminConsole.cpp
 * Purpose: Implementation of the Admin Control Panel logic.
 *
 * This file handles the networking and UI for administrators:
 * 1. Establishes a short-lived connection to the server for each command.
 * 2. Fetches and displays the node registry as a table.
 * 3. Handles secure "Purge" requests and global "Shutdown" commands.
 * 4. Logs all administrative actions for auditing.
 */

#include <AdminConsole.hpp>
#include <Logger.hpp>
#include <SecurityUtils.hpp>
#include <Protocol.hpp>

#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <vector>
#include <cstring>
#include <thread>
#include <chrono>
#include <limits> 
#include <stdexcept>

AdminConsole::AdminConsole(const std::string& ip, int port, const std::string& key)
    : serverIp(ip), serverPort(port), adminKey(key) {
    Logger::getInstance().log(LogLevel::OPERATIONAL, "CONSOLE", "Admin Console Initialized. Target: " + ip + ":" + std::to_string(port));
}

void AdminConsole::displayMenu() {
    std::cout << "\n===============================" << std::endl;
    std::cout << "   DCRMS ADMIN CONTROL PANEL   " << std::endl;
    std::cout << "===============================" << std::endl;
    std::cout << "1. List Registered Nodes" << std::endl;
    std::cout << "2. Deregister (Purge) Node" << std::endl;
    std::cout << "3. Shutdown Server (Global)" << std::endl;
    std::cout << "0. Exit" << std::endl;
    std::cout << "Selection >> " << std::flush;
}

void AdminConsole::run() {
    int choice = 0;
    while (true) {
        try {
            displayMenu();
            
            // Handle non-numeric input errors
            if (!(std::cin >> choice)) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "[CRITICAL] Invalid input format." << std::endl;
                continue;
            }

            switch (choice) {
                case 1: 
                    Logger::getInstance().log(LogLevel::OPERATIONAL, "ACTION", "User selected: List All Nodes");
                    listAllNodes(); 
                    break;
                case 2: 
                    Logger::getInstance().log(LogLevel::OPERATIONAL, "ACTION", "User selected: Deregister Node");
                    deregisterNode(); 
                    break; 
                case 3: 
                    Logger::getInstance().log(LogLevel::ADVISORY, "ACTION", "User selected: Global Shutdown");
                    shutdownServer(); 
                    // Clean return so resources are freed in main()
                    return;
                case 0: // Changed to Case 0
                    Logger::getInstance().log(LogLevel::OPERATIONAL, "CONSOLE", "Exiting Admin Console.");
                    std::cout << "Exiting Admin Console..." << std::endl; 
                    return; // Returns to main() -> clean exit
                default: std::cout << "Invalid selection. Please choose 1, 2, 3, or 0." << std::endl;
            }
        } catch (const std::exception& e) {
            Logger::getInstance().log(LogLevel::CRITICAL, "CONSOLE", "Runtime Error: " + std::string(e.what()));
        }
    }
}

int AdminConsole::connectToServer() {
    try {
        int sock = socket(AF_INET, SOCK_STREAM, 0);
        if (sock < 0) {
            Logger::getInstance().log(LogLevel::CRITICAL, "NETWORK", "Failed to create socket.");
            return -1;
        }

        struct sockaddr_in serv_addr;
        serv_addr.sin_family = AF_INET;
        serv_addr.sin_port = htons(serverPort);
        
        if (inet_pton(AF_INET, serverIp.c_str(), &serv_addr.sin_addr) <= 0) {
             Logger::getInstance().log(LogLevel::CRITICAL, "NETWORK", "Invalid IP Address.");
             close(sock);
             return -1;
        }

        // Attempt to connect to the central hub
        if (connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
            Logger::getInstance().log(LogLevel::CRITICAL, "NETWORK", "Connection failed. Is Server running?");
            close(sock);
            return -1;
        }
        return sock;
    } catch (...) {
        return -1;
    }
}

void AdminConsole::listAllNodes() {
    std::cout << "[OPERATIONAL] Fetching list from " << serverIp << "..." << std::endl;
    
    int sock = connectToServer();
    if (sock < 0) {
        std::cerr << "[CRITICAL] Could not connect to Server." << std::endl;
        return;
    }

    try {
        // Prepare an empty payload for the VIEW request
        std::vector<uint8_t> emptyPayload; 
        Packet pkt = Packet::create(PacketType::ADMIN_VIEW_NODES, emptyPayload);
        std::vector<uint8_t> encrypted = SecurityUtils::encrypt(pkt.serialize(), adminKey);
        
        send(sock, encrypted.data(), encrypted.size(), 0);
        Logger::getInstance().log(LogLevel::OPERATIONAL, "NETWORK", "Sent VIEW_NODES request.");

        char buffer[4096];
        ssize_t bytesRead = recv(sock, buffer, sizeof(buffer), 0);
        
        if (bytesRead > 0) {
            std::vector<uint8_t> encResponse(buffer, buffer + bytesRead);
            std::vector<uint8_t> decrypted = SecurityUtils::decrypt(encResponse, adminKey);

            // Print the table string received from the server
            if (decrypted.size() > sizeof(PacketHeader)) {
                std::string output(decrypted.begin() + sizeof(PacketHeader), decrypted.end());
                std::cout << output << std::endl;
                Logger::getInstance().log(LogLevel::OPERATIONAL, "NETWORK", "Received Node List successfully.");
            } else {
                std::cout << "[ADVISORY] Registry is empty or response invalid." << std::endl;
                Logger::getInstance().log(LogLevel::ADVISORY, "NETWORK", "Received empty Node List.");
            }
        } else {
            std::cout << "[CRITICAL] No response from server." << std::endl;
            Logger::getInstance().log(LogLevel::CRITICAL, "NETWORK", "No response received.");
        }
    } catch (const std::exception& e) {
        Logger::getInstance().log(LogLevel::CRITICAL, "NETWORK", "ListNodes Error: " + std::string(e.what()));
    }
    
    close(sock);
}

void AdminConsole::deregisterNode() {
    int32_t targetId;
    std::cout << "Enter Node ID to purge: ";
    if (!(std::cin >> targetId)) {
        std::cin.clear(); std::cin.ignore(1000, '\n');
        std::cout << "[CRITICAL] Invalid ID format." << std::endl;
        return;
    }
    
    Logger::getInstance().log(LogLevel::OPERATIONAL, "ACTION", "Attempting to deregister Node ID: " + std::to_string(targetId));

    int sock = connectToServer();
    if (sock < 0) {
        std::cerr << "[CRITICAL] Could not connect to Server." << std::endl;
        return;
    }

    try {
        // Build the purge request payload
        AdminDeregisterPayload payload = { targetId };
        Packet pkt = Packet::create(PacketType::ADMIN_DEREGISTER_REQ, payload);
        std::vector<uint8_t> encrypted = SecurityUtils::encrypt(pkt.serialize(), adminKey);

        send(sock, encrypted.data(), encrypted.size(), 0);
        Logger::getInstance().log(LogLevel::OPERATIONAL, "NETWORK", "Sent DEREGISTER_REQ.");

        char buffer[1024];
        ssize_t bytesRead = recv(sock, buffer, sizeof(buffer), 0);

        if (bytesRead > 0) {
            std::vector<uint8_t> enc(buffer, buffer + bytesRead);
            std::vector<uint8_t> dec = SecurityUtils::decrypt(enc, adminKey);

            if (dec.size() >= sizeof(PacketHeader)) {
                AdminDeregisterRespPayload resp;
                std::memcpy(&resp, dec.data() + sizeof(PacketHeader), sizeof(AdminDeregisterRespPayload));
                
                if (resp.success) {
                    std::cout << "\n[SUCCESS] Node " << targetId << " has been removed from the Registry." << std::endl;
                    Logger::getInstance().log(LogLevel::OPERATIONAL, "SUCCESS", "Node " + std::to_string(targetId) + " successfully removed.");
                } else {
                    std::cout << "\n[FAILED] Node " << targetId << " not found or could not be removed." << std::endl;
                    Logger::getInstance().log(LogLevel::ADVISORY, "FAILURE", "Failed to remove Node " + std::to_string(targetId) + " (Not found).");
                }
            }
        } else {
            std::cout << "[CRITICAL] No confirmation received." << std::endl;
            Logger::getInstance().log(LogLevel::CRITICAL, "NETWORK", "No response for deregister request.");
        }
    } catch (const std::exception& e) {
        Logger::getInstance().log(LogLevel::CRITICAL, "NETWORK", "Deregister Error: " + std::string(e.what()));
    }
    
    close(sock);
}

void AdminConsole::shutdownServer() {
    char confirm;
    std::cout << ">>> WARNING: This will kill the Server and disconnect ALL nodes. <<<\n";
    std::cout << ">>> Are you sure? (y/n): ";
    std::cin >> confirm;
    
    if (confirm != 'y' && confirm != 'Y') {
        std::cout << "[OPERATIONAL] Cancelled." << std::endl;
        Logger::getInstance().log(LogLevel::OPERATIONAL, "ACTION", "Shutdown cancelled by user.");
        return;
    }

    int sock = connectToServer();
    if (sock < 0) {
        std::cerr << "[CRITICAL] Could not connect to Server." << std::endl;
        return;
    }

    try {
        std::vector<uint8_t> emptyPayload;
        Packet pkt = Packet::create(PacketType::ADMIN_SHUTDOWN, emptyPayload);
        std::vector<uint8_t> encrypted = SecurityUtils::encrypt(pkt.serialize(), adminKey);

        ssize_t sent = send(sock, encrypted.data(), encrypted.size(), 0);
        
        if (sent > 0) {
            std::cout << "[OPERATIONAL] Shutdown command sent successfully." << std::endl;
            std::cout << "[SUCCESS] Server shutting down..." << std::endl;
            Logger::getInstance().log(LogLevel::ADVISORY, "NETWORK", "SENT SHUTDOWN COMMAND TO SERVER.");
        } else {
            std::cout << "[CRITICAL] Failed to send packet." << std::endl;
            Logger::getInstance().log(LogLevel::CRITICAL, "NETWORK", "Failed to send shutdown packet.");
        }
    } catch (const std::exception& e) {
        Logger::getInstance().log(LogLevel::CRITICAL, "NETWORK", "Shutdown Error: " + std::string(e.what()));
    }
    
    close(sock);
    // Removed exit(0) to allow clean stack unwinding in main()
}