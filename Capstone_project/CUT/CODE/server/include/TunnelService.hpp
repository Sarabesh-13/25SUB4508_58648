/*
 * File: TunnelService.hpp
 * Purpose: The main networking engine of the server.
 *
 * This class handles all the "heavy lifting" of the network:
 * 1. It opens the main listening port (e.g., 8080).
 * 2. It accepts new connections from nodes.
 * 3. It reads raw data packets from the network.
 * 4. It passes those packets to the Logic Engine (Policy/Registry) to be processed.
 * * Updates:
 * - Added <atomic> for thread-safe shutdown control.
 * - Standardized includes.
 */

#ifndef TUNNEL_SERVICE_HPP
#define TUNNEL_SERVICE_HPP

#include <RegistryManager.hpp>
#include <PolicyEngine.hpp>
#include <vector>
#include <string>
#include <atomic> // Added for thread-safe boolean flag

class TunnelService {
private:
    int serverPort;     // The port to listen on (e.g., 8080)
    int maxEvents;      // How many events (connections) to handle at once
    int listenSock;     // The main socket waiting for new nodes
    int epollFd;        // The "Event Poll" file descriptor (Linux high-speed I/O)
    
    // References to the shared Logic Components
    RegistryManager& registry;
    PolicyEngine& policy;
    
    std::atomic<bool> isRunning; // Thread-safe flag to control the main loop

    // Internal helper functions
    void setupServerSocket();
    void handleNewConnection();
    void handleClientData(int clientSock);
    void processPacket(int clientSock, const std::vector<uint8_t>& rawData);

public:
    // Constructor: Needs Port, Max Events, and references to the logic engines
    TunnelService(int port, int events, RegistryManager& reg, PolicyEngine& pol);
    
    // Destructor: Cleans up sockets when the server stops
    ~TunnelService();

    // The main blocking loop (Where the server spends 99% of its life)
    void start();
    
    // Graceful Shutdown: Tells the loop to stop and cleans up
    void shutdown(); 
};

#endif