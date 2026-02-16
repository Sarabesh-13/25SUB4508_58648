/*
 * File: SecurityUtils.hpp
 * Purpose: Utility for data encryption and formatting.
 *
 * This class provides the security layer for the DCRMS project. 
 * Every packet sent over the network (from Node to Server or Admin to Server)
 * is encrypted using these functions. It also includes a helper to 
 * convert raw binary data into a readable string or Hex format for logging.
 */

#ifndef SECURITY_UTILS_HPP
#define SECURITY_UTILS_HPP

#include <string>
#include <vector>
#include <cstdint> 

class SecurityUtils {
public:
    // Formats raw data for display. If the data is printable text, it returns it;
    // otherwise, it returns a Hexadecimal representation (e.g., "0xAF 0x12").
    static std::string toStringOrHex(const std::vector<uint8_t>& data);

    // --- Encryption / Decryption ---

    // Encrypts a buffer using a shared secret key.
    static std::vector<uint8_t> encrypt(const std::vector<uint8_t>& rawData, const std::string& key);

    // Decrypts an encrypted buffer back to its original raw form.
    static std::vector<uint8_t> decrypt(const std::vector<uint8_t>& encryptedData, const std::string& key);
};

#endif