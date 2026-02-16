/*
 * File: PolicyEngine.hpp
 * Purpose: Defines the logic for handling redirection rules.
 *
 * This class determines where a connection request should ultimately go.
 * It checks the status and policy of the requested node to see if the 
 * connection needs to be rerouted to a specific target.
 */

#ifndef POLICY_ENGINE_HPP
#define POLICY_ENGINE_HPP

#include <RegistryManager.hpp>
#include <cstdint>

class PolicyEngine {
private:
    RegistryManager& registry;

public:
    // Constructor taking a reference to the central registry
    explicit PolicyEngine(RegistryManager& reg) : registry(reg) {}

    // The main function.
    // Input: The Node ID the user wants to connect to.
    // Output: The Node ID they *actually* connect to (after checking policies).
    int32_t resolveTarget(int32_t requestedId);
};

#endif