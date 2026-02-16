/*
 * File: PolicyEngine.cpp
 * Purpose: Logic for routing connections through chained policies.
 * * This file implements the "Chain of Redirection". If a node redirects to another,
 * and that one redirects to a third, this engine follows the path.
 * It also prevents infinite loops using a "Max Hops" safety brake.
 */

#include <PolicyEngine.hpp>
#include <Logger.hpp>
#include <string>
#include <stdexcept>

int32_t PolicyEngine::resolveTarget(int32_t requestedId) {
    // Wrap logic in try-catch to prevent routing errors from crashing the server
    try {
        int32_t currentId = requestedId;
        int hops = 0;
        const int MAX_HOPS = 10; // Safety brake to prevent infinite loops (A->B->A)

        while (hops < MAX_HOPS) {
            NodeRecord node;
            
            // 1. Check if the current node exists and is online (Heartbeat active)
            if (!registry.getNode(currentId, node)) {
                Logger::getInstance().log(LogLevel::ADVISORY, "POLICY", "Target Node " + std::to_string(currentId) + " is Offline/Unknown.");
                return -1; // Dead End
            }

            // 2. CHECK POLICY MODE 2: ACTIVELY OVERRIDDEN (Always Redirect)
            // Priority: Highest. We redirect regardless of status (Busy or Available).
            if (node.activePolicy == 2) {
                Logger::getInstance().log(LogLevel::OPERATIONAL, "POLICY", "Override (Mode 2): " + std::to_string(currentId) + " -> " + std::to_string(node.redirectNodeId));
                
                currentId = node.redirectNodeId; // Update target
                hops++;
                continue; // RESTART LOOP -> Now check the *Backup Node's* policy/status
            }

            // 3. CHECK STATUS: AVAILABLE
            // If we get here, Mode 2 didn't force a redirect.
            if (node.status == 0) {
                // Success! We found a node that is ready to talk.
                return currentId;
            }

            // 4. CHECK STATUS: BUSY
            if (node.status == 1) {
                // Check Policy Mode 1: CONDITIONAL REDIRECT (Redirect ONLY if Busy)
                if (node.activePolicy == 1) {
                    Logger::getInstance().log(LogLevel::OPERATIONAL, "POLICY", "Node Busy (Mode 1): " + std::to_string(currentId) + " -> " + std::to_string(node.redirectNodeId));
                    
                    currentId = node.redirectNodeId; // Update target
                    hops++;
                    continue; // RESTART LOOP -> Check the Backup Node
                } else {
                    // Node is Busy, and has NO redirection policy.
                    Logger::getInstance().log(LogLevel::ADVISORY, "POLICY", "Node " + std::to_string(currentId) + " is BUSY and has no backup policy.");
                    return -1; // Connection Refused
                }
            }
        }

        // If we exit the loop, we exceeded MAX_HOPS
        Logger::getInstance().log(LogLevel::CRITICAL, "POLICY", "Routing Loop Detected! Hops exceeded limit.");
        return -1;

    } catch (const std::exception& e) {
        Logger::getInstance().log(LogLevel::CRITICAL, "POLICY", "Resolution Error: " + std::string(e.what()));
        return -1; // Fail safe
    } catch (...) {
        Logger::getInstance().log(LogLevel::CRITICAL, "POLICY", "Resolution Error: Unknown Exception");
        return -1;
    }
}