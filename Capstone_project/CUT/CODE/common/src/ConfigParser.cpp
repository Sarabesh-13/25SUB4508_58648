/*
 * File: ConfigParser.cpp
 * Purpose: Implementation of the configuration file reader.
 *
 * This file contains the logic to open .conf files, strip out comments 
 * starting with '#', and split lines into keys and values. 
 * It ensures that whitespace is removed so that "port = 8080" is 
 * read exactly the same as "port=8080".
 */

#include <ConfigParser.hpp>
#include <fstream>
#include <algorithm>
#include <iostream>

// Helper: Removes spaces and tabs from the beginning and end of a string
std::string ConfigParser::trim(const std::string& str) {
    if (str.empty()) return str;
    auto first = str.find_first_not_of(" \t");
    if (std::string::npos == first) return str;
    auto last = str.find_last_not_of(" \t");
    return str.substr(first, (last - first + 1));
}

bool ConfigParser::load(const std::string& filename) {
    try {
        std::ifstream file(filename);
        if (!file.is_open()) return false;

        std::string line;
        while (std::getline(file, line)) {
            // 1. Ignore comments (anything after a #)
            size_t commentPos = line.find('#');
            if (commentPos != std::string::npos) {
                line = line.substr(0, commentPos);
            }

            // 2. Clean the line
            line = trim(line);
            if (line.empty()) continue;

            // 3. Find the '=' delimiter and split the string
            size_t delimiterPos = line.find('=');
            if (delimiterPos != std::string::npos) {
                std::string key = trim(line.substr(0, delimiterPos));
                std::string value = trim(line.substr(delimiterPos + 1));
                configMap[key] = value;
            }
        }
        return true;
    } catch (...) {
        return false;
    }
}

// Looks up a string value in the map
std::string ConfigParser::getString(const std::string& key, const std::string& defaultValue) {
    try {
        if (configMap.find(key) != configMap.end()) {
            return configMap[key];
        }
    } catch (...) {}
    return defaultValue;
}

// Looks up a value and attempts to convert it to an integer
int ConfigParser::getInt(const std::string& key, int defaultValue) {
    if (configMap.find(key) != configMap.end()) {
        try {
            return std::stoi(configMap[key]);
        } catch (...) {
            // If the value in the file isn't a number, use the default
            return defaultValue; 
        }
    }
    return defaultValue;
}