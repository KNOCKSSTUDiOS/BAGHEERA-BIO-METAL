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
    std::string GetValue(const std::string& key, const std::string& defaultValue) const;
    float GetFloatValue(const std::string& key, float defaultValue) const;
    int GetIntValue(const std::string& key, int defaultValue) const;
};

#endif // CONFIG_PARSER_HPP
