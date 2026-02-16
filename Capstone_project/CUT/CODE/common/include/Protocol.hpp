/*
 * File: Protocol.hpp
 * Purpose: Defines the network communication standards for DCRMS.
 *
 * This file acts as the single source of truth for the data structures
 * sent over the wire. It defines the Packet Header (Magic Number, Type, Size),
 * the various Payload types (Heartbeat, Chat, Admin), and the serialization
 * logic used to convert C++ structs into raw byte arrays for transmission.
 */

#ifndef PROTOCOL_HPP
#define PROTOCOL_HPP

#include <cstdint>
#include <vector>
#include <cstring>
#include <string>

enum class PacketType : uint8_t {
    HEARTBEAT       = 0x01,
    CONNECT_REQ     = 0x02,
    CONNECT_RESP    = 0x03,
    POLICY_UPDATE   = 0x04,
    CHAT_MSG        = 0x05,
    CHAT_QUIT       = 0x06,
    REGISTER_REQ    = 0x07,
    REGISTER_RESP   = 0x08,
    
    // --- ADMIN COMMANDS ---
    ADMIN_VIEW_NODES      = 0x10,
    ADMIN_VIEW_RESP       = 0x11,
    ADMIN_DEREGISTER_REQ  = 0x12, 
    ADMIN_DEREGISTER_RESP = 0x13,
    ADMIN_SHUTDOWN        = 0x99,
    
    SERVER_SHUTDOWN       = 0xFF 
};

enum class NodeStatus : uint8_t {
    AVAILABLE = 0,
    BUSY = 1
};

#pragma pack(push, 1) // Ensure no padding for network transmission
struct PacketHeader {
    uint32_t magicNumber = 0x4443524D; // "DCRM" in Hex
    uint8_t type;
    uint32_t payloadSize;
};

// Existing Payloads
struct HeartbeatPayload { int32_t nodeId; uint8_t status; };
struct PolicyUpdatePayload { int32_t nodeId; uint8_t mode; int32_t redirectId; };
struct ConnectReqPayload { int32_t sourceId; int32_t targetId; };
struct ConnectRespPayload { int32_t respondingNodeId; int32_t destinationId; uint8_t status; };
struct ChatPayload { int32_t senderId; int32_t targetId; char message[256]; };
struct RegisterReqPayload { int32_t nodeId; };
struct RegisterRespPayload { uint8_t success; }; 

// --- ADMIN PAYLOADS ---
struct AdminDeregisterPayload { int32_t nodeId; };
struct AdminDeregisterRespPayload { uint8_t success; };
#pragma pack(pop)

// Registry Record
struct NodeRecord {
    int32_t nodeId;
    uint8_t status;       
    uint8_t activePolicy;   
    int32_t redirectNodeId; 
    int clientSock;         
    uint64_t lastHeartbeat;
};



class Packet {
public:
    PacketHeader header;
    std::vector<uint8_t> payload;

    // Creates a packet from a fixed-size struct
    template<typename T>
    static Packet create(PacketType type, const T& data) {
        Packet p;
        p.header.type = static_cast<uint8_t>(type);
        p.header.payloadSize = sizeof(T);
        p.payload.resize(sizeof(T));
        std::memcpy(p.payload.data(), &data, sizeof(T));
        return p;
    }

    // Creates a packet from a variable-size byte vector (e.g., Admin View Response)
    static Packet create(PacketType type, const std::vector<uint8_t>& data) {
        Packet p;
        p.header.type = static_cast<uint8_t>(type);
        p.header.payloadSize = static_cast<uint32_t>(data.size());
        p.payload = data;
        return p;
    }

    // Converts the Packet object into a single byte array for network transmission
    std::vector<uint8_t> serialize() const {
        std::vector<uint8_t> buffer(sizeof(PacketHeader) + payload.size());
        std::memcpy(buffer.data(), &header, sizeof(PacketHeader));
        if (!payload.empty()) {
            std::memcpy(buffer.data() + sizeof(PacketHeader), payload.data(), payload.size());
        }
        return buffer;
    }
};

#endif