/*
 * File: ConfigParser.hpp
 * Purpose: Simple utility to read and manage configuration files.
 *
 * This class parses files containing "key=value" pairs. It allows the
 * server, nodes, and admin tools to load settings (like IP addresses, 
 * ports, and security keys) from external .conf files rather than 
 * hardcoding them into the binary.
 */

#ifndef CONFIG_PARSER_HPP
#define CONFIG_PARSER_HPP

#include <map>
#include <string>

class ConfigParser {
private:
    // Internal storage for settings: Maps a "Key" name to its "Value" string
    std::map<std::string, std::string> configMap;

    // Helper function to remove unnecessary spaces around keys and values
    std::string trim(const std::string& str);

public:
    // Opens a file, reads it line by line, and populates the internal map
    // Returns true if the file was opened and read successfully
    bool load(const std::string& filename);

    // Retrieves a value as a string. If the key doesn't exist, returns the default.
    std::string getString(const std::string& key, const std::string& defaultValue = "");

    // Retrieves a value and converts it to an integer (useful for Port numbers)
    int getInt(const std::string& key, int defaultValue = 0);
};

#endif