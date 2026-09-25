/* 
 * Copyright (c) Kaloyan Badankov
 */

#pragma once

#include "Core/Core.h"
#include <string>
#include <optional>

namespace Sirius {

class SIRIUS_API EnvParser {
public:
    /**
     * @brief Parses the env string. If there is such key, returns the value, if not, return std::nullopt
     * 
     * @param key The value of the env variable to get
     * @return std::optional<std::string> If result is found, returns the value, if not, returns std::nullopt
     */
    static std::optional<std::string> Get(const std::string& key);

    /**
     * @brief Parses the env string and gets its contents. Returns defaultValue if missing or invalid.
     * 
     * @param key The value of the env variable to get 
     * @param defaultValue Value to return if the env variable is missing or invalid
     * @return std::string Value of the env variable or defaultValue if missing or invalid
     */
    static std::string GetString(const std::string& key, const std::string& defaultValue = "");

    /**
     * @brief Parses the env string and gets its contents. Returns defaultValue if missing or invalid. Result is in lower case
     * 
     * @param key The value of the env variable to get
     * @param defaultValue Value to return if the env variable is missing or invalid
     * @return std::string String value of the env variable or defaultValue if missing or invalid, in lower case
     */
    static std::string GetStringLower(const std::string& key, const std::string& defaultValue = "");

    /**
     * @brief Parses the env var as an integer. Returns defaultValue if missing or invalid.
     * 
     * @param key The value of the env variable to get 
     * @param defaultValue Value to return if the env variable is missing or invalid
     * @return size_t Integer value of the env variable or defaultValue if missing or invalid
     */
    static size_t GetInt(const std::string& key, size_t defaultValue = 0);
};

} // namespace Sirius