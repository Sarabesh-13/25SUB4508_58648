/*
 * File: NodeClient.hpp
 * Purpose: The network worker for the Client Node.
 *
 * This class handles the actual TCP connection to the server.
 * It is responsible for encrypting outgoing packets, managing the socket,
 * and sending specific requests like Heartbeats or Connection Requests.
 */

#ifndef NODE_CLIENT_HPP
#define NODE_CLIENT_HPP

#include <INodeClient.hpp>
#include <string>
#include <vector>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <Protocol.hpp>
#include <SecurityUtils.hpp>

class NodeClient : public INodeClient {
private:
    std::string serverIp;
    int serverPort;
    std::string secretKey;
    int sock; // The active connection socket

    // Internal helper to encrypt and send a packet struct
    void sendPacket(const Packet& p);

public:
    // Constructor: Sets up the target server details
    NodeClient(const std::string& ip, int port, const std::string& key);
    virtual ~NodeClient();

    // Connection Setup
    
    // Tries to connect to the server IP/Port. Returns true if successful.
    bool connectToServer();
    
    // Cleanly closes the socket
    void closeConnection() override;
    
    // Returns the raw socket ID (used by the Controller to listen for data)
    int getSocket() override;

    // Core Actions

    // Sends the registration packet. Returns true if server says "Success".
    bool registerNode(int32_t nodeId) override;

    // Sends the "I am alive" pulse
    void sendHeartbeat(int32_t nodeId, int status) override;

    // Interface Implementation

    // Asks the server to connect us to a Target ID
    int32_t requestConnection(int32_t sourceId, int32_t targetId) override;
    
    // Updates redirection rules (Mode 1=Local, Mode 2=Global)
    bool updatePolicyOnServer(int32_t nodeId, uint8_t mode, int32_t redirectId) override;
};

#endif