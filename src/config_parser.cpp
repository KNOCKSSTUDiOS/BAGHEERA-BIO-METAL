#include "config_parser.hpp"
#include <fstream>
#include <iostream>

std::string ConfigParser::trim(const std::string& str) {
    size_t first = str.find_first_not_of(" \t\r\n");
    if (first == std::string::npos) return "";
    size_t last = str.find_last_not_of(" \t\r\n");
    return str.substr(first, (last - first + 1));
}

bool ConfigParser::LoadConfigFile(const std::string& filePath) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "[CONFIG] Target file not found: " << filePath << " | Using engine hardware defaults." << std::endl;
        return false;
    }

    std::string line;
    while (std::getline(file, line)) {
        line = trim(line);
        if (line.empty() || line[0] == '#') continue;

        std::size_t delimiterPos = line.find(':');
        if (delimiterPos != std::string::npos) {
            std::string key = trim(line.substr(0, delimiterPos));
            std::string value = trim(line.substr(delimiterPos + 1));
            configMap[key] = value;
        }
    }
    file.close();
    std::cout << "[CONFIG] Configuration file parsed successfully (" << configMap.size()
              << " keys loaded) completely offline." << std::endl;
    return true;
}

std::string ConfigParser::GetValue(const std::string& key, const std::string& defaultValue) const {
    auto it = configMap.find(key);
    if (it != configMap.end()) return it->second;
    return defaultValue;
}

float ConfigParser::GetFloatValue(const std::string& key, float defaultValue) const {
    auto it = configMap.find(key);
    if (it != configMap.end()) {
        try {
            return std::stof(it->second);
        } catch (...) {
            return defaultValue;
        }
    }
    return defaultValue;
}

int ConfigParser::GetIntValue(const std::string& key, int defaultValue) const {
    auto it = configMap.find(key);
    if (it != configMap.end()) {
        try {
            return std::stoi(it->second);
        } catch (...) {
            return defaultValue;
        }
    }
    return defaultValue;
}
