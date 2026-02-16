/*
 * File: RegistryManager.cpp
 * Purpose: Implementation of the central node database.
 *
 * This file handles the storage, updating, and cleanup of node records.
 * It uses a mutex to make sure that if the Admin Console and the Network Listener
 * try to access the list at the same time, nothing crashes.
 */

#include <RegistryManager.hpp>
#include <Logger.hpp>
#include <chrono>
#include <unistd.h>
#include <stdexcept>
#include <string>

RegistryManager::RegistryManager() {
    // Safe initialization logging
    try {
        Logger::getInstance().log(LogLevel::OPERATIONAL, "REGISTRY", "Initialized registry.");
    } catch (...) {
        // Suppress logging errors during startup
    }
}

RegistryManager::~RegistryManager() {
    try {
        std::lock_guard<std::mutex> lock(registryMutex);
        nodes.clear();
    } catch (...) {
        // Destructors must never throw exceptions
    }
}

void RegistryManager::updateNode(int32_t nodeId, uint8_t status, int sock) {
    std::lock_guard<std::mutex> lock(registryMutex);
    
    try {
        // Get current time in milliseconds
        uint64_t now = std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::system_clock::now().time_since_epoch()
        ).count();

        bool isNew = (nodes.find(nodeId) == nodes.end());
        
        // Update or Insert the record
        nodes[nodeId].nodeId = nodeId;
        nodes[nodeId].status = status;
        nodes[nodeId].clientSock = sock; 
        nodes[nodeId].lastHeartbeat = now;

        if (isNew) {
            // Default policy is "Disabled" (0)
            nodes[nodeId].activePolicy = 0; 
            nodes[nodeId].redirectNodeId = 0;
            Logger::getInstance().log(LogLevel::OPERATIONAL, "REGISTRY", "New Node Registered: " + std::to_string(nodeId));
        }
    } catch (const std::exception& e) {
        Logger::getInstance().log(LogLevel::CRITICAL, "REGISTRY", "Update Error: " + std::string(e.what()));
    }
}

bool RegistryManager::getNode(int32_t nodeId, NodeRecord& outRecord) {
    std::lock_guard<std::mutex> lock(registryMutex);
    try {
        if (nodes.find(nodeId) != nodes.end()) {
            outRecord = nodes[nodeId];
            return true;
        }
    } catch (...) {
        return false;
    }
    return false;
}

bool RegistryManager::isNodeResponsive(int32_t nodeId) {
    std::lock_guard<std::mutex> lock(registryMutex);
    // If the node exists in our map, we consider it responsive (timeout handles the rest)
    return (nodes.find(nodeId) != nodes.end());
}

std::vector<NodeRecord> RegistryManager::getAllNodes() {
    std::lock_guard<std::mutex> lock(registryMutex);
    std::vector<NodeRecord> list;
    try {
        for (const auto& kv : nodes) {
            list.push_back(kv.second);
        }
    } catch (...) {
        // Return whatever partial list we have if allocation fails
    }
    return list;
}

void RegistryManager::setNodePolicy(int32_t nodeId, uint8_t policyMode, int32_t redirectId) {
    std::lock_guard<std::mutex> lock(registryMutex);
    try {
        if (nodes.find(nodeId) != nodes.end()) {
            nodes[nodeId].activePolicy = policyMode;
            nodes[nodeId].redirectNodeId = redirectId;
            Logger::getInstance().log(LogLevel::OPERATIONAL, "REGISTRY", "Policy Updated for Node " + std::to_string(nodeId));
        }
    } catch (const std::exception& e) {
        Logger::getInstance().log(LogLevel::ADVISORY, "REGISTRY", "Policy Update Failed: " + std::string(e.what()));
    }
}

bool RegistryManager::removeNode(int32_t nodeId) {
    std::lock_guard<std::mutex> lock(registryMutex);
    try {
        auto it = nodes.find(nodeId);
        if (it != nodes.end()) {
            // Close the socket to prevent leaks
            if (it->second.clientSock > 0) {
                close(it->second.clientSock);
            }
            nodes.erase(it);
            Logger::getInstance().log(LogLevel::ADVISORY, "REGISTRY", "Node " + std::to_string(nodeId) + " removed via Admin.");
            return true;
        }
    } catch (...) {
        return false;
    }
    return false;
}

void RegistryManager::removeNodeBySocket(int sock) {
    std::lock_guard<std::mutex> lock(registryMutex);
    
    try {
        // We have to iterate manually because the key is NodeID, but we are searching by Socket
        for (auto it = nodes.begin(); it != nodes.end(); ) {
            if (it->second.clientSock == sock) {
                Logger::getInstance().log(LogLevel::ADVISORY, "REGISTRY", "Removing Node " + std::to_string(it->first) + " (Socket Disconnect)");
                
                // Ensure socket is closed if not already
                if (it->second.clientSock > 0) {
                    close(it->second.clientSock);
                }
                
                it = nodes.erase(it); // Erase returns the next iterator
            } else {
                ++it;
            }
        }
    } catch (const std::exception& e) {
        Logger::getInstance().log(LogLevel::CRITICAL, "REGISTRY", "Cleanup Error: " + std::string(e.what()));
    }
}

void RegistryManager::cleanupStaleNodes() {
    std::lock_guard<std::mutex> lock(registryMutex);
    
    try {
        uint64_t now = std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::system_clock::now().time_since_epoch()
        ).count();

        for (auto it = nodes.begin(); it != nodes.end(); ) {
            // Check if the heartbeat is older than the timeout limit
            if (now - it->second.lastHeartbeat > HEARTBEAT_TIMEOUT_MS) {
                Logger::getInstance().log(LogLevel::ADVISORY, "REGISTRY", "Node " + std::to_string(it->first) + " timed out. Removing.");
                
                if (it->second.clientSock > 0) close(it->second.clientSock);
                it = nodes.erase(it);
            } else {
                ++it;
            }
        }
    } catch (...) {
        // Swallow timeout errors to keep server running
    }
}