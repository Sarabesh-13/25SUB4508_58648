/*
 * File: AdminConsole.hpp
 * Purpose: The Command Center for the DCRMS Network.
 *
 * This class provides a specialized interface for administrators to monitor
 * and manage the server. It allows for viewing the global node registry,
 * force-removing nodes, or triggering a system-wide shutdown.
 */

#ifndef ADMIN_CONSOLE_HPP
#define ADMIN_CONSOLE_HPP

#include <string>

class AdminConsole {
private:
    std::string serverIp;   // Target IP of the DCRMS Server
    int serverPort;          // Target Port of the DCRMS Server
    std::string adminKey;    // Shared secret key for encrypted communication

    // Prints the available admin commands to the screen
    void displayMenu();
    
    // --- Admin Actions ---

    // Requests and prints the full table of connected nodes and their statuses
    void listAllNodes();

    // Requests the server to force-disconnect a specific Node ID
    void deregisterNode(); 

    // Sends a high-priority command to shut down the server and all clients
    void shutdownServer(); 
    
    // Internal helper to establish a TCP link with the server
    int connectToServer(); 

public:
    // Constructor: Sets up server destination and security credentials
    AdminConsole(const std::string& ip, int port, const std::string& key);

    // The main execution loop for the admin interactive shell
    void run();
};

#endif