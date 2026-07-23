#ifndef CONFIG_PARSER_HPP
#define CONFIG_PARSER_HPP

#include <string>
#include <unordered_map>

class ConfigParser {
private:
    std::unordered_map<std::string, std::string> configMap;
    std::string trim(const std::string& str);

public:
    ConfigParser() = default;
    bool LoadConfigFile(const std::string& filePath);
    std::string GetValue(const std::string& key, const std::string& defaultValue);
    float GetFloatValue(const std::string& key, float defaultValue);
};

#endif // CONFIG_PARSER_HPP
