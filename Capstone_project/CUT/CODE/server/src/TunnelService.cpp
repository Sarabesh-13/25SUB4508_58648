/*
 * File: TunnelService.cpp
 * Purpose: Implementation of the Central Hub (Server).
 *
 * This file handles all network traffic for the DCRMS system.
 * It uses the 'epoll' system to efficiently handle many connections at once.
 * It receives encrypted packets, decrypts them, and routes them to the 
 * correct destination based on the Registry and Policy Engine.
 * * Updates:
 * - Added Global Exception Handling (try-catch) to prevent crashes.
 * - Added valgrind-safe resource cleanup.
 */

#include <TunnelService.hpp>
#include <Logger.hpp>
#include <SecurityUtils.hpp>
#include <Protocol.hpp>

#include <sys/epoll.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <fcntl.h>
#include <cstring>
#include <iostream>
#include <sstream>
#include <vector>
#include <iomanip> // For table formatting
#include <ctime>   // For time conversion
#include <stdexcept> // For std::exception

// --- Constructor ---
TunnelService::TunnelService(int port, int events, RegistryManager& reg, PolicyEngine& pol)
    : serverPort(port),    
      maxEvents(events),
      listenSock(-1),      
      epollFd(-1),
      registry(reg),       
      policy(pol),
      isRunning(false)
{
}

// --- Destructor ---
TunnelService::~TunnelService() {
    // Ensure all resources are released to satisfy Valgrind
    if (listenSock != -1) close(listenSock);
    if (epollFd != -1) close(epollFd);
}

// --- Socket Setup ---
void TunnelService::setupServerSocket() {
    try {
        listenSock = socket(AF_INET, SOCK_STREAM, 0);
        if (listenSock < 0) {
            throw std::runtime_error("Failed to create socket");
        }

        // Set Non-Blocking Mode
        int flags = fcntl(listenSock, F_GETFL, 0);
        if (fcntl(listenSock, F_SETFL, flags | O_NONBLOCK) < 0) {
            throw std::runtime_error("Failed to set non-blocking mode");
        }
        
        // Allow immediate restart on same port
        int opt = 1;
        if (setsockopt(listenSock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
            throw std::runtime_error("Failed to set SO_REUSEADDR");
        }

        struct sockaddr_in addr;
        std::memset(&addr, 0, sizeof(addr));
        addr.sin_family = AF_INET;
        addr.sin_addr.s_addr = INADDR_ANY;
        addr.sin_port = htons(serverPort);

        if (bind(listenSock, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
            throw std::runtime_error("Bind failed on port " + std::to_string(serverPort));
        }

        if (listen(listenSock, SOMAXCONN) < 0) {
            throw std::runtime_error("Listen failed");
        }

        // Create Epoll Instance
        epollFd = epoll_create1(0);
        if (epollFd < 0) {
            throw std::runtime_error("Failed to create epoll instance");
        }

        struct epoll_event ev;
        ev.events = EPOLLIN | EPOLLET; // Edge Triggered
        ev.data.fd = listenSock;
        if (epoll_ctl(epollFd, EPOLL_CTL_ADD, listenSock, &ev) < 0) {
            throw std::runtime_error("Failed to add listen socket to epoll");
        }

    } catch (const std::exception& e) {
        Logger::getInstance().log(LogLevel::CRITICAL, "TUNNEL", std::string("Setup Error: ") + e.what());
        exit(EXIT_FAILURE);
    }
}

// --- Main Loop ---
void TunnelService::start() {
    setupServerSocket();
    Logger::getInstance().log(LogLevel::OPERATIONAL, "TUNNEL", "DCRMS Server Online. Listening on Port " + std::to_string(serverPort));
    
    isRunning = true;
    std::vector<struct epoll_event> events(maxEvents);

    while (isRunning) {
        try {
            // Wait for events (Timeout 1000ms to allow checking isRunning)
            int nfds = epoll_wait(epollFd, events.data(), maxEvents, 1000); 
            
            if (nfds == -1) {
                if (errno == EINTR) continue; // Handle signal interruption
                throw std::runtime_error("epoll_wait failed");
            }

            for (int i = 0; i < nfds; ++i) {
                try {
                    if (events[i].data.fd == listenSock) {
                        handleNewConnection();
                    } else {
                        handleClientData(events[i].data.fd);
                    }
                } catch (const std::exception& e) {
                    // Catch per-client errors so one bad client doesn't crash the server
                    Logger::getInstance().log(LogLevel::ADVISORY, "TUNNEL", "Client Handler Error: " + std::string(e.what()));
                }
            }
        } catch (const std::exception& e) {
            // Catch main loop errors
            if (isRunning) {
                Logger::getInstance().log(LogLevel::CRITICAL, "TUNNEL", "Main Loop Exception: " + std::string(e.what()));
            }
        }
    }
    
    Logger::getInstance().log(LogLevel::OPERATIONAL, "TUNNEL", "Server Main Loop Stopped.");
}

// --- Graceful Shutdown ---
void TunnelService::shutdown() {
    if (!isRunning.exchange(false)) return; // Already stopped (atomic check)
    
    Logger::getInstance().log(LogLevel::ADVISORY, "TUNNEL", "Initiating Global Shutdown Sequence...");

    try {
        // 1. Create the Shutdown Packet
        std::vector<uint8_t> empty;
        Packet p = Packet::create(PacketType::SERVER_SHUTDOWN, empty);
        std::vector<uint8_t> enc = SecurityUtils::encrypt(p.serialize(), "MY_SECURE_KEY_123");

        // 2. Broadcast to ALL Nodes (and Admin if connected)
        auto nodes = registry.getAllNodes();
        int count = 0;
        
        for (const auto& node : nodes) {
            if (node.clientSock > 0) {
                send(node.clientSock, enc.data(), enc.size(), 0);
                count++;
            }
        }

        Logger::getInstance().log(LogLevel::OPERATIONAL, "TUNNEL", "Shutdown Signal sent to " + std::to_string(count) + " active clients.");
        
        // 3. CRITICAL: Wait for network buffer flush
        usleep(200000); // 200ms delay
        
        // 4. Clean up Resources
        if (listenSock != -1) { close(listenSock); listenSock = -1; }
        if (epollFd != -1) { close(epollFd); epollFd = -1; }
        
        Logger::getInstance().log(LogLevel::OPERATIONAL, "TUNNEL", "Resources released. Goodbye.");

    } catch (const std::exception& e) {
        Logger::getInstance().log(LogLevel::CRITICAL, "TUNNEL", "Shutdown Error: " + std::string(e.what()));
    }
}

// --- Connection Handling ---
void TunnelService::handleNewConnection() {
    struct sockaddr_in clientAddr;
    socklen_t clientLen = sizeof(clientAddr);
    int clientSock = accept(listenSock, (struct sockaddr*)&clientAddr, &clientLen);

    if (clientSock >= 0) {
        // Set Non-Blocking
        int flags = fcntl(clientSock, F_GETFL, 0);
        fcntl(clientSock, F_SETFL, flags | O_NONBLOCK);

        // Add to Epoll
        struct epoll_event ev;
        ev.events = EPOLLIN | EPOLLET;
        ev.data.fd = clientSock;
        if (epoll_ctl(epollFd, EPOLL_CTL_ADD, clientSock, &ev) < 0) {
            close(clientSock); // Clean up if epoll fails
            Logger::getInstance().log(LogLevel::ADVISORY, "TUNNEL", "Failed to add new client to epoll");
        }
    }
}

// --- Data Handling ---
void TunnelService::handleClientData(int clientSock) {
    char buffer[4096];
    ssize_t bytesRead = recv(clientSock, buffer, sizeof(buffer), 0);

    if (bytesRead <= 0) {
        // Remove from Registry IMMEDIATELY on disconnect
        registry.removeNodeBySocket(clientSock);
        close(clientSock); 
        // Note: epoll automatically removes closed file descriptors
    } else {
        try {
            std::vector<uint8_t> encrypted(buffer, buffer + bytesRead);
            // Encryption might throw if data is corrupted
            std::vector<uint8_t> decrypted = SecurityUtils::decrypt(encrypted, "MY_SECURE_KEY_123");
            processPacket(clientSock, decrypted);
        } catch (const std::exception& e) {
            Logger::getInstance().log(LogLevel::ADVISORY, "TUNNEL", "Packet Processing Failed (Dropping): " + std::string(e.what()));
        }
    }
}

// --- Packet Processing Logic ---
void TunnelService::processPacket(int clientSock, const std::vector<uint8_t>& rawData) {
    if (rawData.size() < sizeof(PacketHeader)) return;

    PacketHeader head;
    std::memcpy(&head, rawData.data(), sizeof(PacketHeader));

    // verify Magic Number
    if (head.magicNumber != 0x4443524D) return; 

    // 1. HEARTBEAT
    if (head.type == static_cast<uint8_t>(PacketType::HEARTBEAT)) {
        HeartbeatPayload pulse;
        std::memcpy(&pulse, rawData.data() + sizeof(PacketHeader), sizeof(HeartbeatPayload));
        registry.updateNode(pulse.nodeId, pulse.status, clientSock);
    }
    
    // 2. REGISTER REQUEST
    else if (head.type == static_cast<uint8_t>(PacketType::REGISTER_REQ)) {
        RegisterReqPayload req;
        std::memcpy(&req, rawData.data() + sizeof(PacketHeader), sizeof(RegisterReqPayload));
        
        bool isDuplicate = registry.isNodeResponsive(req.nodeId);
        RegisterRespPayload resp;
        
        if (isDuplicate) {
            Logger::getInstance().log(LogLevel::ADVISORY, "TUNNEL", "Registration DENIED: Node " + std::to_string(req.nodeId));
            resp.success = 0;
        } else {
            Logger::getInstance().log(LogLevel::OPERATIONAL, "TUNNEL", "Registration APPROVED: Node " + std::to_string(req.nodeId));
            resp.success = 1;
            registry.updateNode(req.nodeId, 0, clientSock);
        }

        Packet p = Packet::create(PacketType::REGISTER_RESP, resp);
        std::vector<uint8_t> enc = SecurityUtils::encrypt(p.serialize(), "MY_SECURE_KEY_123");
        send(clientSock, enc.data(), enc.size(), 0);
    }
    
    // 3. CONNECT REQUEST (Handshake Start)
    else if (head.type == static_cast<uint8_t>(PacketType::CONNECT_REQ)) {
        ConnectReqPayload req;
        std::memcpy(&req, rawData.data() + sizeof(PacketHeader), sizeof(ConnectReqPayload));
        
        int32_t finalTargetId = policy.resolveTarget(req.targetId);
        NodeRecord targetNode;
        if (finalTargetId != -1 && registry.getNode(finalTargetId, targetNode)) {
            if (targetNode.clientSock > 0) {
                std::vector<uint8_t> reEncrypted = SecurityUtils::encrypt(rawData, "MY_SECURE_KEY_123");
                send(targetNode.clientSock, reEncrypted.data(), reEncrypted.size(), 0);
            }
        } else {
            ConnectRespPayload resp = { 0, req.sourceId, 0 }; // 0 = Failed
            Packet p = Packet::create(PacketType::CONNECT_RESP, resp);
            std::vector<uint8_t> enc = SecurityUtils::encrypt(p.serialize(), "MY_SECURE_KEY_123");
            send(clientSock, enc.data(), enc.size(), 0);
        }
    }
    
    // 4. CONNECT RESPONSE (Handshake Reply)
    else if (head.type == static_cast<uint8_t>(PacketType::CONNECT_RESP)) {
        ConnectRespPayload resp;
        std::memcpy(&resp, rawData.data() + sizeof(PacketHeader), sizeof(ConnectRespPayload));
        
        NodeRecord requesterNode;
        // Correctly route back to the original source (Destination ID in the payload)
        if (registry.getNode(resp.destinationId, requesterNode)) {
             if (requesterNode.clientSock > 0) {
                 std::vector<uint8_t> reEncrypted = SecurityUtils::encrypt(rawData, "MY_SECURE_KEY_123");
                 send(requesterNode.clientSock, reEncrypted.data(), reEncrypted.size(), 0);
             }
        }
    }
    
    // 5. CHAT MESSAGES & QUIT
    else if (head.type == static_cast<uint8_t>(PacketType::CHAT_MSG) || 
             head.type == static_cast<uint8_t>(PacketType::CHAT_QUIT)) {
        ChatPayload msg;
        std::memcpy(&msg, rawData.data() + sizeof(PacketHeader), sizeof(ChatPayload));
        
        NodeRecord target;
        if (registry.getNode(msg.targetId, target)) {
            if (target.clientSock > 0) {
                std::vector<uint8_t> reEncrypted = SecurityUtils::encrypt(rawData, "MY_SECURE_KEY_123");
                send(target.clientSock, reEncrypted.data(), reEncrypted.size(), 0);
            }
        }
    }
    
    // 6. POLICY UPDATE
    else if (head.type == static_cast<uint8_t>(PacketType::POLICY_UPDATE)) {
        PolicyUpdatePayload pol;
        std::memcpy(&pol, rawData.data() + sizeof(PacketHeader), sizeof(PolicyUpdatePayload));
        registry.setNodePolicy(pol.nodeId, pol.mode, pol.redirectId);
    }

    // --- ADMIN SECTION ---
    
    // 7. ADMIN: VIEW NODES
    else if (head.type == static_cast<uint8_t>(PacketType::ADMIN_VIEW_NODES)) {
        Logger::getInstance().log(LogLevel::OPERATIONAL, "ADMIN", "Received View Request");
        
        std::vector<NodeRecord> nodes = registry.getAllNodes();
        std::stringstream ss;
        
        ss << "\n--- DCRMS NETWORK STATUS ---\n";
        ss << "Total Nodes: " << nodes.size() << "\n";
        ss << "------------------------------------------------------------------------\n";
        ss << "ID    | Status    | Policy Mode | Redir Target | Last Active (IST)\n";
        ss << "------------------------------------------------------------------------\n";
        
        for (const auto& n : nodes) {
            // --- 1. Format Time (IST) ---
            time_t t = n.lastHeartbeat / 1000;
            std::tm* tm = std::localtime(&t); // Uses system time (now set to IST)
            
            char timeBuffer[30];
            if (tm) {
                std::strftime(timeBuffer, sizeof(timeBuffer), "%Y-%m-%d %H:%M:%S", tm);
            } else {
                std::strcpy(timeBuffer, "UNKNOWN");
            }

            // --- 2. Format Policy Mode (Human Readable) ---
            std::string policyStr;
            if (n.activePolicy == 0) policyStr = "DISABLED";
            else if (n.activePolicy == 1) policyStr = "LOCAL";  // Was: Conditional
            else if (n.activePolicy == 2) policyStr = "GLOBAL"; // Was: Active Override
            else policyStr = "UNKNOWN";

            ss << std::left << std::setw(6) << n.nodeId 
               << "| " << std::setw(10) << (n.status == 0 ? "AVAILABLE" : "BUSY") 
               << "| " << std::setw(12) << policyStr
               << "| " << std::setw(13) << n.redirectNodeId
               << "| " << timeBuffer << "\n";
        }
        if (nodes.empty()) ss << "No nodes connected.\n";
        ss << "------------------------------------------------------------------------\n";

        std::string respStr = ss.str();
        std::vector<uint8_t> strData(respStr.begin(), respStr.end());
        Packet resp = Packet::create(PacketType::ADMIN_VIEW_RESP, strData);
        
        std::vector<uint8_t> encrypted = SecurityUtils::encrypt(resp.serialize(), "MY_SECURE_KEY_123");
        send(clientSock, encrypted.data(), encrypted.size(), 0);
    }
    
    // 8. ADMIN: DEREGISTER NODE
    else if (head.type == static_cast<uint8_t>(PacketType::ADMIN_DEREGISTER_REQ)) {
        AdminDeregisterPayload req;
        std::memcpy(&req, rawData.data() + sizeof(PacketHeader), sizeof(AdminDeregisterPayload));
        
        Logger::getInstance().log(LogLevel::ADVISORY, "ADMIN", "Processing Purge Request for Node " + std::to_string(req.nodeId));
        
        bool success = registry.removeNode(req.nodeId);
        
        AdminDeregisterRespPayload resp = { (uint8_t)(success ? 1 : 0) };
        Packet pkt = Packet::create(PacketType::ADMIN_DEREGISTER_RESP, resp);
        std::vector<uint8_t> enc = SecurityUtils::encrypt(pkt.serialize(), "MY_SECURE_KEY_123");
        send(clientSock, enc.data(), enc.size(), 0);
    }

    // 9. ADMIN: SHUTDOWN
    else if (head.type == static_cast<uint8_t>(PacketType::ADMIN_SHUTDOWN)) {
        Logger::getInstance().log(LogLevel::ADVISORY, "ADMIN", "Remote Shutdown Command Received.");
        shutdown(); 
    }
}