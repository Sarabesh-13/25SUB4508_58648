/*
 * File: NodeMain.cpp
 * Purpose: Main entry point for the DCRMS Node application.
 *
 * This file handles the main execution flow for a client node:
 * 1. Initializes communication based on command-line ID.
 * 2. Manages the interactive menu for status, policy, and chat.
 * 3. Uses a select-based loop to handle both keyboard input and server messages.
 * 4. Ensures a graceful exit when Ctrl+C is pressed.
 */

#include <Protocol.hpp>
#include <NodeController.hpp>
#include <HeartbeatManager.hpp> 
#include <Logger.hpp>
#include <ConfigParser.hpp>

#include <iostream>
#include <string>
#include <sys/select.h>
#include <unistd.h>
#include <thread>
#include <limits>
#include <vector>
#include <csignal>
#include <atomic>

// Global pointer for clean shutdown via signal handler
std::atomic<bool> g_running(true);

// Signal Handler for Ctrl+C: Ensures the server knows we are disconnecting
void handleSignal(int signum) {
    std::cout << "\n[ADVISORY] Caught Signal " << signum << ". Disconnecting..." << std::endl;
    g_running = false;
}

// Visual menu display showing current node configuration
void displayMenu(int32_t nodeId, int policyMode, int32_t redirectId) {
    std::cout << "\n======================================" << std::endl;
    std::cout << "   DCRMS NODE [" << nodeId << "] CONTROL" << std::endl;
    std::cout << "======================================" << std::endl;
    
    if (policyMode == 2) 
        std::cout << "   [POLICY: GLOBAL -> " << redirectId << "]" << std::endl;
    else if (policyMode == 1)
        std::cout << "   [POLICY: LOCAL -> " << redirectId << "]" << std::endl;
    else
        std::cout << "   [POLICY: DISABLED]" << std::endl;

    std::cout << "--------------------------------------" << std::endl;
    std::cout << "1. Set Status: AVAILABLE" << std::endl;
    std::cout << "2. Set Status: BUSY" << std::endl;
    std::cout << "3. Show Current Status" << std::endl;
    std::cout << "4. Configure Redirection Policy" << std::endl;
    std::cout << "5. Connect (Chat)" << std::endl;
    std::cout << "0. Exit" << std::endl;
    std::cout << "Selection >> " << std::flush;
}

int main(int argc, char** argv) {
    // Setup signal handling for graceful exit
    std::signal(SIGINT, handleSignal);
    std::signal(SIGPIPE, SIG_IGN);
    if (argc < 2) {
        std::cerr << "Usage: ./node_app <NODE_ID>" << std::endl;
        return 1;
    }
    int32_t nodeId = std::stoi(argv[1]);
    
    // Initialize system components
    Logger::getInstance().init("logs/node_" + std::to_string(nodeId) + ".log");
    ConfigParser config;
    config.load("config/node.conf");
    
    std::string srvIp = config.getString("server_ip", "127.0.0.1");
    int srvPort = config.getInt("server_port", 8080);
    std::string key = config.getString("secret_key", "MY_SECURE_KEY_123");

    {
        NodeController controller(nodeId, srvIp, srvPort, key);
        HeartbeatManager heartbeatManager; 

        // 1. Initial Handshake with Server
        if (!controller.initRegistration()) {
            std::cout << "Exiting application due to ID conflict." << std::endl;
            return 1; 
        }

        controller.startBackgroundServices(); 

        int32_t currentRedirectId = 0;
        int currentPolicyMode = 0; 
        fd_set readfds;
        struct timeval tv;
        bool repaintMenu = true; 

        // Main Operation Loop
        while (g_running) {
            try {
                if (repaintMenu) {
                    displayMenu(nodeId, currentPolicyMode, currentRedirectId);
                    repaintMenu = false;
                }

                int sock = controller.getSocket(); 
                if (sock < 0) break;

                // Handle periodic heartbeat timing
                heartbeatManager.update(controller);

                // Setup FD set for non-blocking monitoring
                FD_ZERO(&readfds);
                FD_SET(0, &readfds);     // Keyboard
                FD_SET(sock, &readfds);  // Server Socket

                tv.tv_sec = 0; tv.tv_usec = 100000; // 100ms timeout
                int activ = select(sock + 1, &readfds, NULL, NULL, &tv);
                
                if (!g_running) break;
                if (activ < 0) continue; 
                if (activ == 0) continue; 

                // Scenario: Server sent us data (Incoming call or shutdown)
                if (FD_ISSET(sock, &readfds)) {
                    uint8_t buffer[1024];
                    ssize_t len = recv(sock, buffer, sizeof(buffer), 0);
                    
                    if (len <= 0) {
                        std::cout << "\n[ADVISORY] Connection lost..." << std::endl;
                        break; 
                    }

                    std::vector<uint8_t> enc(buffer, buffer + len);
                    std::vector<uint8_t> dec = SecurityUtils::decrypt(enc, controller.getKey());
                    
                    if (dec.size() >= sizeof(PacketHeader)) {
                        PacketHeader head;
                        std::memcpy(&head, dec.data(), sizeof(PacketHeader));

                        if (head.type == (uint8_t)PacketType::CONNECT_REQ) {
                            if (!controller.handleIncomingRequest(dec)) {
                                g_running = false;
                                break;
                            }
                            repaintMenu = true; 
                        }
                        else if (head.type == (uint8_t)PacketType::SERVER_SHUTDOWN) {
                            std::cout << "\n[CRITICAL] GLOBAL SHUTDOWN." << std::endl;
                            break;
                        }
                    }
                }

                // Scenario: User typed something
                if (FD_ISSET(0, &readfds)) {
                    int choice;
                    if (!(std::cin >> choice)) {
                        std::cin.clear(); 
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
                        std::cout << "\n[CRITICAL] Invalid input. Please enter a number." << std::endl;
                        repaintMenu = true; 
                        continue;
                    }

                    switch (choice) {
                        case 1: 
                            controller.setStatus(NodeStatus::AVAILABLE); 
                            std::cout << "[SUCCESS] Set to Available.\n"; 
                            break;
                        case 2: 
                            controller.setStatus(NodeStatus::BUSY); 
                            std::cout << "[SUCCESS] Set to Busy.\n"; 
                            break;
                        case 3: 
                            std::cout << "[OPERATIONAL] Status: " << (controller.getStatus() == NodeStatus::AVAILABLE ? "AVAILABLE" : "BUSY") << "\n"; 
                            break;
                        case 4: {
                            int mode;
                            std::cout << "\n--- Configure Redirection ---\n1. Local (Conditional)\n2. Global (Always)\n3. Disable\n>> ";
                            if (std::cin >> mode) {
                                if (mode == 3) {
                                    currentPolicyMode = 0; currentRedirectId = 0; controller.setPolicy(0, 0);
                                } else if (mode == 1 || mode == 2) {
                                    std::cout << "Target ID: "; 
                                    if (std::cin >> currentRedirectId) {
                                        if(currentRedirectId == nodeId) std::cout << "Error: Self-redirect prohibited.\n";
                                        else { currentPolicyMode = mode; controller.setPolicy(mode, currentRedirectId); }
                                    }
                                }
                            } else {
                                std::cin.clear(); std::cin.ignore(1000, '\n');
                            }
                            break;
                        }
                        case 5: {
                            int32_t target;
                            std::cout << "Target Node ID: ";
                            if (!(std::cin >> target)) {
                                std::cin.clear(); std::cin.ignore(1000, '\n');
                                std::cout << "Invalid ID.\n";
                            } else {
                                // Clear buffer before entering chat session
                                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                                int32_t actual = controller.requestConnection(target); 
                                
                                if (actual == -99) { 
                                    std::cout << "\n[CRITICAL] Server Shutdown. Exiting.\n";
                                    g_running = false;
                                }
                                else if (actual > 0) {
                                    if (!controller.startChatSession(actual, (actual != target))) {
                                        g_running = false;
                                    }
                                }
                                else if (actual == -1) {
                                    std::cout << "[OPERATIONAL] Connection Refused.\n";
                                }
                            }
                            break;
                        }
                        case 0: 
                            g_running = false;
                            break;
                        default:
                            std::cout << "\n[CRITICAL] Invalid Selection (" << choice << "). Try again." << std::endl;
                            break;
                    }
                    repaintMenu = true; 
                }
            } catch (const std::exception& e) {
                Logger::getInstance().log(LogLevel::CRITICAL, "NODE_MAIN", "Loop Exception: " + std::string(e.what()));
                repaintMenu = true; 
            }
        }
        controller.stopBackgroundServices();
    }
    
    return 0;
}