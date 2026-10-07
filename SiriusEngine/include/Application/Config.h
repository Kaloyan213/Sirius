/* 
 * Copyright (c) Kaloyan Badankov
 */

#pragma once

#include "Core/Core.h"
#include "Utility/StringUtil.h"
#include <string_view>
#include <unordered_map>
#include <filesystem>

/**
 * @brief Static Config class responsible for collecting data from all configs, or just some instances. The config should be either in the main build directory of the project subdirectory of the build folder called Configs 
 * 
 */
 
namespace FS = std::filesystem;

namespace Sirius {

class SIRIUS_API Config {
public:
    // Loads and parses a .cfg file. Returns true if successful.
    /**
     * @brief Loads and parses a .cfg file. Returns true if successful.
     * 
     * @param filename String containing the path to the config file to be read.
     * @param isAlwaysExpected Is config file always expected to be present. If true, will log an error if the file is not found.
     * @return bool Results of the operation. True if successful, false otherwise. 
     */
    static bool ReadConfig(const std::string& filename, bool isAlwaysExpected = false);
    
    /**
     * @brief 
     * 
     * @param filename std::filesystem::path containing the path to the config file to be read.
     * @param isAlwaysExpected Is config file always expected to be present. If true, will log an error if the file is not found.
     * @return bool Results of the operation. True if successful, false otherwise. 
     */
    static bool ReadConfig(const FS::path& filename, bool isAlwaysExpected = false);

    /**
     * @brief Read all configs from the Configs directory. Returns true if successful.
     * 
     * @param isAlwaysExpected Is config file always expected to be present. If true, will log an error if the file is not found.
     * @return bool Results of the operation. True if successful, false otherwise.
     */
    static bool ReadAllConfigs(bool isAlwaysExpected);
    
    /**
     * @brief Is the config system initialized and ready to be used.
     *  
     * @return bool True if the config system is initialized, false otherwise. 
     */
    static bool IsInitialized ();

    /**
     * @brief Has the property been set in the config files. Note that the config should be initialized.
     * 
     * @param propertyName std::string_view containing the name of the property to check.
     * @return bool True if the property exists, false otherwise.
     */
    static bool HasProperty (std::string_view propertyName);

    /**
     * @brief Checks if a boolean property is enabled (i.e., set to "true" or "1") in the config files. Note that the config should be initialized.
     * 
     * @param key Std::string containing the name of the property to check.
     * @return bool True if the property is enabled, false otherwise. 
     */
    static bool IsBooleanPropertyEnabled(const std::string& key);

    /**
     * @brief Gets the value of a property from the config files. Note that the config should be initialized. 
     * 
     * @param propertyName Property name to retrieve the value for.
     * @param defaultValue Default value to return if the property is not found.
     * @return const std::string If the property is not found, it will return the provided default value. Note that the config should be initialized.
     */
    static const std::string GetPropertyValue (std::string_view propertyName, const std::string defaultValue);

    /**
     * @brief Template function to get the value of a property from the config files and convert it to the specified type. Note that the config should be initialized.
     * 
     * @param propertyName Property name to retrieve the value for.
     * @param defaultValue Default value to return if the property is not found or if the conversion fails.
     * @return T Return type of the property value. The function will attempt to convert the string value to this type.
     */
    template<typename T>
	static T GetPropertyValue (std::string_view propertyName, const T& defaultValue);

private:
    static std::unordered_map<std::string, std::string> properties;
};

template <typename T>
inline T Sirius::Config::GetPropertyValue(std::string_view propertyName, const T &defaultValue)
{
    const std::string str = Config::GetPropertyValue (propertyName, "");
    if(str.empty()){
        return StringUtil::FromString<T> (nullptr, defaultValue);
    }
    return StringUtil::FromString<T> (str, defaultValue);
}

} // namespace Sirius