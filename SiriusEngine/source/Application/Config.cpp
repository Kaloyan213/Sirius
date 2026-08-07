#include "Application/Config.h"
#include "Utility/EnvParser.h"
#include "Utility/Logger.h"

#include <fstream>
#include <vector>

namespace {
    Logger& ConfigLogger () {
        static Logger instance ("ConfigLoger");
        return  instance;
    }
}

namespace Sirius {
    
std::unordered_map<std::string, std::string> Config::properties;

bool Config::ReadConfig(const FS::path& filePath, bool isAlwaysExpected) {
    if(filePath.empty() || !FS::exists(filePath)) {
        ConfigLogger().Log(LogLevel::err, "Could not find file ", filePath.string());
        if(isAlwaysExpected){
            //TODO Kalo - Introduce fatal errors, crash and so on  
        }
        return false;
    }

    std::ifstream file(filePath);
    if (!file.is_open()) {
        CoreLogger().Log(LogLevel::err, "Failed to open file ", filePath.string());
        return false;
    }

    std::string line;
    while (std::getline(file, line)) {
        // Trim whitespace
        std::string_view trimmed = StringUtil::Trim(line);

        // Skip empty lines and comments
        if (trimmed.empty() || trimmed.starts_with("#") || trimmed.starts_with("//") || trimmed.starts_with("[")) {
            continue;
        }

        // Find the '=' delimiter
        size_t equalPos = trimmed.find('=');
        if (equalPos != std::string_view::npos) {
            std::string_view key = StringUtil::Trim(trimmed.substr(0, equalPos));
            std::string_view value = StringUtil::Trim(trimmed.substr(equalPos + 1));

            if (!key.empty()) {

                properties.emplace (std::string(key), std::string(value));
            }
        }
    }

    ConfigLogger().Log(LogLevel::debug, "Loaded ", filePath.string());
    return true;
}

bool Config::ReadConfig(const std::string& filename, bool isAlwaysExpected)
{
    // Define the directories you want to search, in order of priority.
    std::vector<FS::path> searchPaths = {
        FS::path(filename),
        FS::path("Configs") / filename,        
    };

    FS::path targetPath;

    // Look for the file in the search paths
    for (const auto& path : searchPaths) {
        if (FS::exists(path) && FS::is_regular_file(path)) {
            targetPath = path;
            break;
        }
    }

    return ReadConfig (targetPath, isAlwaysExpected);
}

bool Config::ReadAllConfigs(bool isAlwaysExpected)
{
    bool loadedAny = false;
    
    const auto iterateDirectory = [&loadedAny](const FS::path& directory) {
        // Safety check: ensure the directory actually exists before iterating
        if (!FS::exists(directory) || !FS::is_directory(directory)) {
            return;
        }

        for (const auto& entry : FS::directory_iterator(directory)) {
            // Only attempt to read regular files with the .cfg extension
            if (entry.is_regular_file() && entry.path().extension() == ".cfg") {
                if (ReadConfig(entry.path(), false)) {
                    loadedAny = true;
                }
            }
        }
    };

    // Iterate through all files in the current directory
    iterateDirectory(FS::current_path());

    // Iterate through all files in the Config directory
    FS::path configDir("Configs");
    if (!FS::exists(configDir) || !FS::is_directory(configDir)) {
        ConfigLogger().Log(LogLevel::warn, "Configs directory not found at ", FS::absolute(configDir).string());
    } else {
        iterateDirectory(configDir);
    }

    if (!loadedAny) {
        ConfigLogger().Log(LogLevel::warn, "No .cfg files found in current or Configs directories.");
        if(isAlwaysExpected) {
            //TODO Kalo - Fatal error
        }
    }

    return loadedAny;
}

bool Config::IsInitialized()
{
    return properties.empty();
}

bool Config::HasProperty(std::string_view propertyName)
{
    return properties.find(std::string (propertyName)) != properties.end();
}
const std::string Config::GetPropertyValue(std::string_view propertyName, const std::string defaultValue)
{
    const auto envValue = EnvParser::Get(std::string(propertyName));
    if (envValue) {
        return *envValue; 
    }

    auto valItt = properties.find(std::string(propertyName));
    if (valItt != properties.end()) {
        return valItt->second; 
    }
    
    return defaultValue;
}

bool Sirius::Config::IsBooleanPropertyEnabled(const std::string &key)
{
    return GetPropertyValue (key, false);
}

}//namespace Sirius
