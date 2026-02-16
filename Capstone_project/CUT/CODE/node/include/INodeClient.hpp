/*
 * File: INodeClient.hpp
 * Purpose: Abstract Interface for the Network Client.
 *
 * This file acts as a strict contract. It defines WHAT a NodeClient must do,
 * but not HOW it does it. This allows the Controller to talk to the
 * Network layer without worrying about sockets, encryption, or IP addresses.
 */

#ifndef INODE_CLIENT_HPP
#define INODE_CLIENT_HPP

#include <cstdint>

class INodeClient {
public:
    virtual ~INodeClient() = default;

    // Connection Management
    
    // Gets the raw socket descriptor (used to check if we are online)
    virtual int getSocket() = 0;

    // Safely closes the connection to the server
    virtual void closeConnection() = 0;

    // Core Features

    // Sends the initial "Hello, I am Node X" packet to the server
    virtual bool registerNode(int32_t nodeId) = 0;

    // Sends a "Heartbeat" packet to tell the server we are still alive
    virtual void sendHeartbeat(int32_t nodeId, int status) = 0;

    // Updates the redirection rules (e.g., "If busy, redirect to Node Y")
    // mode: 1 = Active, 0 = Disabled
    virtual bool updatePolicyOnServer(int32_t nodeId, uint8_t mode, int32_t redirectId) = 0;

    // Asks the server to connect us to another node (Target ID)
    virtual int32_t requestConnection(int32_t sourceId, int32_t targetId) = 0;
};

#endif