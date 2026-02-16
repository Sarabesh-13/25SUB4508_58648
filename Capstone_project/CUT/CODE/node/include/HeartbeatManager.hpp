/*
 * File: HeartbeatManager.hpp
 * Purpose: Manages the timing for automatic "I am alive" signals.
 *
 * This class acts like a metronome. Every 1 second, it tells the NodeController
 * to send a Heartbeat packet to the server so the server knows we are still online.
 */

#ifndef HEARTBEAT_MANAGER_HPP
#define HEARTBEAT_MANAGER_HPP

#include <NodeController.hpp>
#include <chrono>

class HeartbeatManager {
private:
    std::chrono::steady_clock::time_point lastBeatTime;
    std::chrono::steady_clock::time_point lastLogTime;
    
    // How often to send a heartbeat (1 second)
    const int beatIntervalSec = 1;  

    // How often to print "Heartbeat sent" to the logs (10 seconds)
    // We don't want to spam the log file every single second.
    const int logIntervalSec = 10;  

public:
    HeartbeatManager();
    
    // Checks the clock. If 1 second has passed, it triggers the controller 
    // to send a heartbeat packet.
    void update(NodeController& controller);
};

#endif