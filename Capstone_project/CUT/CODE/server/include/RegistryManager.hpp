/*
 * File: RegistryManager.hpp
 * Purpose: Manages the database of active nodes.
 *
 * This class is the "Phonebook" of the server. It stores which nodes are online,
 * their current IP/Socket, their Status (Available/Busy), and their Redirection Rules.
 * It also handles the logic for removing nodes that stop sending heartbeats.
 */

#ifndef REGISTRY_MANAGER_HPP
#define REGISTRY_MANAGER_HPP

#include <unordered_map>
#include <mutex>
#include <vector>
#include <Protocol.hpp> // Updated to < >

class RegistryManager {
private:
    // The main storage: Maps NodeID -> NodeRecord
    std::unordered_map<int32_t, NodeRecord> nodes;
    
    // Mutex to ensure thread safety (so two threads don't write at once)
    std::mutex registryMutex;
    
    // How long we wait for a heartbeat before declaring a node dead (30 seconds)
    const uint64_t HEARTBEAT_TIMEOUT_MS = 30000;

public:
    RegistryManager();
    ~RegistryManager();

    // --- Core Management Functions ---

    // Updates a node's status (Alive/Busy) and refreshes its timestamp
    void updateNode(int32_t nodeId, uint8_t status, int sock);

    // Retrieves the full record for a specific Node ID
    // Returns false if the node is not found
    bool getNode(int32_t nodeId, NodeRecord& outRecord);

    // Checks if a node has sent a heartbeat recently
    bool isNodeResponsive(int32_t nodeId);

    // Returns a list of all currently registered nodes (for the Admin Console)
    std::vector<NodeRecord> getAllNodes();
    
    // --- Policy Management ---

    // Updates the redirection rules for a specific node
    void setNodePolicy(int32_t nodeId, uint8_t policyMode, int32_t redirectId);
    
    // --- Removal & Cleanup ---

    // Manually remove a node by ID (e.g., Admin Deregister)
    bool removeNode(int32_t nodeId);

    // Remove a node associated with a specific socket (e.g., on Disconnect)
    void removeNodeBySocket(int sock);

    // Scans the list and removes nodes that haven't sent a heartbeat in 30s
    void cleanupStaleNodes();
};

#endif