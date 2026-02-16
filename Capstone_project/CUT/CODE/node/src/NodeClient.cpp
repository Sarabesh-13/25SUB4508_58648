/*
 * File: NodeClient.cpp
 * Purpose: Implementation of the network communication layer for nodes.
 *
 * This file handles the low-level socket work:
 * 1. Connecting to the Server IP and Port.
 * 2. Sending registration requests and waiting for a "Yes/No" response.
 * 3. Encrypting and transmitting data packets (Heartbeats, Policy Updates, etc.).
 */

#include <NodeClient.hpp>
#include <Logger.hpp>
#include <stdexcept>
#include <iostream>

NodeClient::NodeClient(const std::string& ip, int port, const std::string& key)
    : serverIp(ip), serverPort(port), secretKey(key), sock(-1) {
    // We try to open the connection as soon as this object is created
    connectToServer();
}

NodeClient::~NodeClient() {
    closeConnection();
}

bool NodeClient::connectToServer() {
    if (sock != -1) return true; // Already have a working socket

    try {
        sock = socket(AF_INET, SOCK_STREAM, 0);
        if (sock < 0) {
            Logger::getInstance().log(LogLevel::CRITICAL, "CLIENT", "Socket creation failed");
            return false;
        }

        struct sockaddr_in servAddr;
        servAddr.sin_family = AF_INET;
        servAddr.sin_port = htons(serverPort);
        
        // Convert the IP string (e.g., "127.0.0.1") into binary format
        if (inet_pton(AF_INET, serverIp.c_str(), &servAddr.sin_addr) <= 0) {
            Logger::getInstance().log(LogLevel::CRITICAL, "CLIENT", "Invalid Server Address provided");
            return false;
        }

        // Attempt to establish a link with the server
        if (connect(sock, (struct sockaddr*)&servAddr, sizeof(servAddr)) < 0) {
            Logger::getInstance().log(LogLevel::CRITICAL, "CLIENT", "Connection to Server Failed");
            return false;
        }
    } catch (const std::exception& e) {
        Logger::getInstance().log(LogLevel::CRITICAL, "CLIENT", "Connection Exception: " + std::string(e.what()));
        return false;
    }

    return true;
}

void NodeClient::closeConnection() {
    if (sock != -1) {
        close(sock);
        sock = -1;
    }
}

int NodeClient::getSocket() {
    return sock;
}

bool NodeClient::registerNode(int32_t nodeId) {
    if (sock == -1) connectToServer();
    if (sock == -1) return false;

    // 1. Prepare and send the registration packet
    RegisterReqPayload req;
    req.nodeId = nodeId;
    Packet p = Packet::create(PacketType::REGISTER_REQ, req);
    sendPacket(p);
    
    // 2. Wait for Response (This is blocking because we can't start the node without a 'Success')
    char buffer[1024];
    ssize_t valread = read(sock, buffer, 1024);
    
    if (valread > 0) {
        std::vector<uint8_t> encrypted(buffer, buffer + valread);
        try {
            // Decrypt the server's response
            std::vector<uint8_t> decrypted = SecurityUtils::decrypt(encrypted, secretKey);
            
            PacketHeader head;
            std::memcpy(&head, decrypted.data(), sizeof(PacketHeader));
            
            if (head.type == static_cast<uint8_t>(PacketType::REGISTER_RESP)) {
                RegisterRespPayload resp;
                std::memcpy(&resp, decrypted.data() + sizeof(PacketHeader), sizeof(RegisterRespPayload));
                return (resp.success == 1);
            }
        } catch (...) {
            Logger::getInstance().log(LogLevel::CRITICAL, "CLIENT", "Decryption failed during registration process");
        }
    }
    return false;
}

void NodeClient::sendHeartbeat(int32_t nodeId, int status) {
    HeartbeatPayload hb;
    hb.nodeId = nodeId;
    hb.status = status;
    Packet p = Packet::create(PacketType::HEARTBEAT, hb);
    sendPacket(p);
}

int32_t NodeClient::requestConnection(int32_t sourceId, int32_t targetId) {
    ConnectReqPayload req;
    req.sourceId = sourceId;
    req.targetId = targetId;
    Packet p = Packet::create(PacketType::CONNECT_REQ, req);
    sendPacket(p);
    return 0; // The actual response is handled by the Controller's listen loop later
}

bool NodeClient::updatePolicyOnServer(int32_t nodeId, uint8_t mode, int32_t redirectId) {
    PolicyUpdatePayload pol;
    pol.nodeId = nodeId;
    pol.mode = mode;
    pol.redirectId = redirectId;
    Packet p = Packet::create(PacketType::POLICY_UPDATE, pol);
    sendPacket(p);
    return true;
}

void NodeClient::sendPacket(const Packet& p) {
    if (sock != -1) {
        try {
            // Encrypt everything before it hits the wire
            std::vector<uint8_t> enc = SecurityUtils::encrypt(p.serialize(), secretKey);
            ssize_t sent = send(sock, enc.data(), enc.size(), MSG_NOSIGNAL);
            if (sent < 0) {
                Logger::getInstance().log(LogLevel::ADVISORY, "CLIENT", "Failed to send packet (Socket Error)");
            }
        } catch (const std::exception& e) {
            Logger::getInstance().log(LogLevel::CRITICAL, "CLIENT", "Encryption/Send Error: " + std::string(e.what()));
        }
    }
}