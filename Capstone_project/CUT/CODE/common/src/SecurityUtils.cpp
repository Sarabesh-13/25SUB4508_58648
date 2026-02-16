/*
 * File: SecurityUtils.cpp
 * Purpose: Implementation of XOR encryption and data inspection.
 *
 * This file handles the security layer:
 * 1. toStringOrHex: Extracts printable text from packets while skipping headers.
 * 2. encrypt/decrypt: Uses a symmetric XOR cipher to scramble data.
 * 3. Logging: Logs detailed TRACE data specifically for Chat packets.
 */

#include <SecurityUtils.hpp>
#include <Logger.hpp>
#include <Protocol.hpp>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <cctype>
#include <cstring>
#include <algorithm>
#include <stdexcept>

// Intelligent helper to visualize packet data in logs
std::string SecurityUtils::toStringOrHex(const std::vector<uint8_t>& data) {
    try {
        if (data.empty()) return "[EMPTY]";

        std::stringstream ssHex;
        ssHex << "[HEX] ";
        ssHex << std::hex << std::uppercase << std::setfill('0');
        
        // Show only the first 20 bytes to keep logs clean
        size_t len = (data.size() > 20) ? 20 : data.size();
        for (size_t i = 0; i < len; ++i) {
            ssHex << std::setw(2) << static_cast<int>(data[i]) << " ";
        }
        if (data.size() > 20) ssHex << "... ";

        // Skip the 9-byte DCRM Header to find the actual message text
        std::string foundText = "";
        if (data.size() > 9) { 
            std::string currentSeq;
            std::string longestSeq;
            
            for (size_t i = 9; i < data.size(); ++i) {
                uint8_t byte = data[i];
                if (std::isprint(byte)) {
                    currentSeq += static_cast<char>(byte);
                } else {
                    if (currentSeq.length() > longestSeq.length()) longestSeq = currentSeq;
                    currentSeq.clear();
                }
            }
            if (currentSeq.length() > longestSeq.length()) longestSeq = currentSeq;
            if (longestSeq.length() > 1) foundText = longestSeq;
        }

        if (!foundText.empty()) return ssHex.str() + " [MSG]: \"" + foundText + "\"";
        return ssHex.str();
    } catch (...) {
        return "[FORMAT ERROR]";
    }
}

// Internal helper to identify if a packet contains chat data
bool isChatPacket(const std::vector<uint8_t>& data) {
    if (data.size() < sizeof(PacketHeader)) return false;
    // Offset 4 is the 'type' field in our PacketHeader
    uint8_t type = data[4]; 
    return (type == static_cast<uint8_t>(PacketType::CHAT_MSG));
}

std::vector<uint8_t> SecurityUtils::encrypt(const std::vector<uint8_t>& rawData, const std::string& key) {
    if (key.empty()) return rawData;

    try {
        bool shouldLog = isChatPacket(rawData);

        if (shouldLog) {
            Logger::getInstance().log(LogLevel::TRACE, "CRYPTO", "Encrypting CHAT MSG (" + std::to_string(rawData.size()) + " bytes)");
            Logger::getInstance().log(LogLevel::TRACE, "CRYPTO", "RAW IN   : " + toStringOrHex(rawData));
        }

        // Standard XOR Encryption
        std::vector<uint8_t> result = rawData;
        for (size_t i = 0; i < rawData.size(); ++i) {
            result[i] = rawData[i] ^ key[i % key.length()]; 
        }

        if (shouldLog) {
            std::stringstream ss;
            ss << std::hex << std::uppercase << std::setfill('0');
            size_t len = (result.size() > 32) ? 32 : result.size();
            for(size_t i=0; i<len; ++i) ss << std::setw(2) << (int)result[i] << " ";
            Logger::getInstance().log(LogLevel::TRACE, "CRYPTO", "ENC OUT  : " + ss.str() + "...");
        }
        return result;
    } catch (const std::exception& e) {
        Logger::getInstance().log(LogLevel::CRITICAL, "CRYPTO", "Encryption Failed: " + std::string(e.what()));
        return rawData; // Fail safe: return original data
    }
}

std::vector<uint8_t> SecurityUtils::decrypt(const std::vector<uint8_t>& encryptedData, const std::string& key) {
    if (key.empty()) return encryptedData;

    try {
        // Standard XOR Decryption (XORing twice returns the original value)
        std::vector<uint8_t> result = encryptedData;
        for (size_t i = 0; i < encryptedData.size(); ++i) {
            result[i] = encryptedData[i] ^ key[i % key.length()]; 
        }

        // Log the result if it was a chat packet
        if (isChatPacket(result)) {
            Logger::getInstance().log(LogLevel::TRACE, "CRYPTO", "Decrypting CHAT MSG (" + std::to_string(encryptedData.size()) + " bytes)");
            Logger::getInstance().log(LogLevel::TRACE, "CRYPTO", "RAW OUT  : " + toStringOrHex(result));
        }

        return result;
    } catch (const std::exception& e) {
        Logger::getInstance().log(LogLevel::CRITICAL, "CRYPTO", "Decryption Failed: " + std::string(e.what()));
        return encryptedData; // Fail safe
    }
}