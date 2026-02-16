/*
 * File: NodeController.hpp
 * Purpose: The "Brain" of the Client Node.
 *
 * This class coordinates everything the node does:
 * 1. Manages the registration handshake with the server.
 * 2. Handles user status (Available/Busy) and Redirection Policies.
 * 3. Controls the Chat Session UI and data flow.
 * 4. Listens for incoming connection requests while the user is in the menu.
 */

#ifndef NODE_CONTROLLER_HPP
#define NODE_CONTROLLER_HPP

#include <Protocol.hpp>
#include <SecurityUtils.hpp>
#include <Logger.hpp> 
#include <INodeClient.hpp>
#include <NodeClient.hpp>

#include <memory>
#include <iostream>
#include <sys/select.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <cstring>
#include <unistd.h>
#include <limits> 
#include <vector>
#include <string>
#include <stdexcept>

class NodeController {
private:
    std::shared_ptr<NodeClient> client; // The network worker
    int32_t nodeId;                     // This node's unique ID
    std::string secretKey;              // Key used for packet encryption
    int currentStatus;                  // 0 = Available, 1 = Busy

public:
    NodeController(int32_t id, const std::string& ip, int port, const std::string& key) 
        : nodeId(id), secretKey(key), currentStatus(0) {
        client = std::make_shared<NodeClient>(ip, port, key);
    }

    // Handles the initial startup registration.
    bool initRegistration() {
        std::cout << "[OPERATIONAL] Registering Node ID " << nodeId << " with Server..." << std::endl;
        Logger::getInstance().log(LogLevel::OPERATIONAL, "CONTROLLER", "Starting Registration Process...");
        
        try {
            bool success = client->registerNode(nodeId);
            if (success) {
                std::cout << "[SUCCESS] Registration Verified." << std::endl;
                Logger::getInstance().log(LogLevel::OPERATIONAL, "CONTROLLER", "Registration Verified.");
                return true;
            } else {
                std::cout << "[CRITICAL] Registration Failed! Duplicate ID." << std::endl;
                Logger::getInstance().log(LogLevel::CRITICAL, "CONTROLLER", "Registration Failed: Duplicate ID.");
                return false;
            }
        } catch (const std::exception& e) {
             std::cout << "[CRITICAL] Registration Exception: " << e.what() << std::endl;
             return false;
        }
    }

    // Basic Heartbeat/Background controls
    void startBackgroundServices() { 
        try {
            client->sendHeartbeat(nodeId, currentStatus);
        } catch (...) {}
    }
    
    void stopBackgroundServices() {
        client->closeConnection();
    }

    void sendKeepAlive() {
        try {
            client->sendHeartbeat(nodeId, currentStatus);
        } catch (...) {}
    }

    // Updates local status and tells the server immediately
    void setStatus(NodeStatus status) { 
        std::string sStr = (status == NodeStatus::AVAILABLE) ? "AVAILABLE" : "BUSY";
        Logger::getInstance().log(LogLevel::OPERATIONAL, "CONTROLLER", "User changed status to: " + sStr);
        currentStatus = static_cast<int>(status);
        try {
            client->sendHeartbeat(nodeId, currentStatus);
        } catch (...) {}
    }

    NodeStatus getStatus() const { return static_cast<NodeStatus>(currentStatus); }

    // Sends a policy update (Redirection rules) to the server
    bool setPolicy(uint8_t mode, int32_t redirectId) {
        Logger::getInstance().log(LogLevel::OPERATIONAL, "CONTROLLER", "Policy Updated.");
        try {
            return client->updatePolicyOnServer(nodeId, mode, redirectId);
        } catch (...) { return false; }
    }
    
    int getSocket() { return client->getSocket(); }
    std::string getKey() { return secretKey; }

    // Initiates a chat request with another node
    int32_t requestConnection(int32_t targetId) {
        if (targetId == nodeId) {
            Logger::getInstance().log(LogLevel::ADVISORY, "CONTROLLER", "User attempted self-connection.");
            std::cout << "[CRITICAL] You cannot connect to yourself." << std::endl;
            return -2;
        }

        Logger::getInstance().log(LogLevel::OPERATIONAL, "CONTROLLER", "User initiating chat with Node " + std::to_string(targetId));
        std::cout << "[OPERATIONAL] Sending request to Node " << targetId << "..." << std::endl;
        
        try {
            if (client->requestConnection(nodeId, targetId) < 0) return -1;
        } catch (...) { return -1; }

        std::cout << "[OPERATIONAL] Waiting for response..." << std::endl;
        int sock = client->getSocket();
        uint8_t buffer[1024];
        
        // Blocking wait for connection response
        while(true) {
            ssize_t len = recv(sock, buffer, sizeof(buffer), 0);
            
            if (len <= 0) {
                 client->closeConnection();
                 return -99; 
            }

            try {
                std::vector<uint8_t> enc(buffer, buffer + len);
                std::vector<uint8_t> dec = SecurityUtils::decrypt(enc, secretKey);
                
                if(dec.size() >= sizeof(PacketHeader)) {
                    PacketHeader head;
                    std::memcpy(&head, dec.data(), sizeof(PacketHeader));
                    
                    if (head.type == (uint8_t)PacketType::SERVER_SHUTDOWN) {
                        return -99; 
                    }

                    if(head.type == (uint8_t)PacketType::CONNECT_RESP) {
                        ConnectRespPayload resp;
                        std::memcpy(&resp, dec.data() + sizeof(PacketHeader), sizeof(ConnectRespPayload));
                        
                        if (resp.status == 1) {
                            Logger::getInstance().log(LogLevel::OPERATIONAL, "CONTROLLER", "Connection Accepted by Node " + std::to_string(resp.respondingNodeId));
                            return resp.respondingNodeId; 
                        } else {
                            Logger::getInstance().log(LogLevel::ADVISORY, "CONTROLLER", "Connection Rejected by Node " + std::to_string(resp.respondingNodeId));
                            return -1; 
                        }
                    }
                }
            } catch (...) {
                continue;
            }
        }
    }

    // Handles the UI logic when another node tries to call us
    bool handleIncomingRequest(const std::vector<uint8_t>& decryptedPacket) {
        try {
            ConnectReqPayload req;
            std::memcpy(&req, decryptedPacket.data() + sizeof(PacketHeader), sizeof(ConnectReqPayload));

            Logger::getInstance().log(LogLevel::OPERATIONAL, "CONTROLLER", "Incoming Chat Request from Node " + std::to_string(req.sourceId));

            // Clear current line and prompt the user
            std::cout << "\r\033[K"; 
            std::cout << ">>> INCOMING CONNECTION: Node " << req.sourceId << " wants to chat." << std::endl;
            std::cout << ">>> Accept? (y/n): ";
            
            char choice;
            std::cin >> choice;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            int sock = client->getSocket();
            
            ConnectRespPayload resp = { nodeId, req.sourceId, (uint8_t)(choice == 'y' ? 1 : 0) };
            Packet pkt = Packet::create(PacketType::CONNECT_RESP, resp);
            std::vector<uint8_t> enc = SecurityUtils::encrypt(pkt.serialize(), secretKey);
            send(sock, enc.data(), enc.size(), 0);

            if (choice == 'y') {
                Logger::getInstance().log(LogLevel::OPERATIONAL, "CONTROLLER", "User ACCEPTED request.");
                return startChatSession(req.sourceId, false);
            } else {
                Logger::getInstance().log(LogLevel::OPERATIONAL, "CONTROLLER", "User DECLINED request.");
                std::cout << "[OPERATIONAL] Connection Rejected." << std::endl;
                return true;
            }
        } catch (const std::exception& e) {
            Logger::getInstance().log(LogLevel::CRITICAL, "CONTROLLER", "Error handling request: " + std::string(e.what()));
            return true;
        }
    }

    // The main interactive chat loop using select() for non-blocking I/O
    bool startChatSession(int32_t targetId, bool isRedirection) {
        setStatus(NodeStatus::BUSY); 
        int sock = client->getSocket();
        if (sock < 0) { setStatus(NodeStatus::AVAILABLE); return false; }

        std::cout << "\n------------------------------------------------" << std::endl;
        if(isRedirection) std::cout << "[OPERATIONAL] Redirected -> Node " << targetId << std::endl;
        std::cout << "Connected. Type message or '/quit'." << std::endl;
        std::cout << "------------------------------------------------" << std::endl;

        fd_set readfds;
        char buffer[1024];
        bool sessionActive = true;
        bool cleanExit = true;
        std::cout << "[You]: " << std::flush;

        while(sessionActive) {
            try {
                FD_ZERO(&readfds);
                FD_SET(0, &readfds);    // Watch Keyboard
                FD_SET(sock, &readfds); // Watch Network Socket

                if (select(sock + 1, &readfds, NULL, NULL, NULL) < 0) break;

                // Scenario: Data arriving from the Network
                if (FD_ISSET(sock, &readfds)) {
                    ssize_t len = recv(sock, buffer, sizeof(buffer), 0);
                    if (len <= 0) {
                        std::cout << "\n[CRITICAL] Server Disconnected." << std::endl;
                        client->closeConnection();
                        cleanExit = false;
                        break; 
                    }

                    std::vector<uint8_t> enc(buffer, buffer + len);
                    std::vector<uint8_t> dec = SecurityUtils::decrypt(enc, secretKey);
                    PacketHeader head;
                    std::memcpy(&head, dec.data(), sizeof(PacketHeader));

                    if (head.type == (uint8_t)PacketType::CHAT_MSG) {
                        ChatPayload p;
                        std::memcpy(&p, dec.data() + sizeof(PacketHeader), sizeof(ChatPayload));
                        std::cout << "\r\033[K" << "[Node " << p.senderId << "]: " << p.message << std::endl;
                        std::cout << "[You]: " << std::flush;
                    }
                    else if (head.type == (uint8_t)PacketType::CHAT_QUIT) {
                        std::cout << "\n\r[OPERATIONAL] Partner left the chat." << std::endl;
                        sessionActive = false;
                    }
                    else if (head.type == (uint8_t)PacketType::SERVER_SHUTDOWN) {
                        std::cout << "\n\r[CRITICAL] GLOBAL SHUTDOWN." << std::endl;
                        cleanExit = false;
                        break;
                    }
                    else if (head.type == (uint8_t)PacketType::CONNECT_REQ) {
                        // Auto-Reject other calls while already in a chat
                        ConnectReqPayload req;
                        std::memcpy(&req, dec.data() + sizeof(PacketHeader), sizeof(ConnectReqPayload));
                        ConnectRespPayload resp = { nodeId, req.sourceId, 0 }; 
                        Packet pkt = Packet::create(PacketType::CONNECT_RESP, resp);
                        std::vector<uint8_t> encResp = SecurityUtils::encrypt(pkt.serialize(), secretKey);
                        send(sock, encResp.data(), encResp.size(), 0);
                        Logger::getInstance().log(LogLevel::OPERATIONAL, "CONTROLLER", "Auto-Rejected incoming call (Busy)");
                    }
                }

                // Scenario: Data arriving from the Keyboard
                if (FD_ISSET(0, &readfds)) {
                    std::string input;
                    std::getline(std::cin, input);
                    if (input.empty()) { std::cout << "[You]: " << std::flush; continue; }
                    
                    if (input == "/quit") {
                        ChatPayload p = { nodeId, targetId, "" };
                        Packet pkt = Packet::create(PacketType::CHAT_QUIT, p);
                        std::vector<uint8_t> enc = SecurityUtils::encrypt(pkt.serialize(), secretKey);
                        send(sock, enc.data(), enc.size(), 0);
                        sessionActive = false;
                    } else {
                        ChatPayload p = { nodeId, targetId, "" };
                        std::strncpy(p.message, input.c_str(), 255);
                        Packet pkt = Packet::create(PacketType::CHAT_MSG, p);
                        std::vector<uint8_t> enc = SecurityUtils::encrypt(pkt.serialize(), secretKey);
                        send(sock, enc.data(), enc.size(), 0);
                        std::cout << "[You]: " << std::flush;
                    }
                }
            } catch (const std::exception& e) {
                Logger::getInstance().log(LogLevel::ADVISORY, "CONTROLLER", "Chat Exception (Recovering): " + std::string(e.what()));
            }
        }
        setStatus(NodeStatus::AVAILABLE);
        return cleanExit;
    }
};

#endif