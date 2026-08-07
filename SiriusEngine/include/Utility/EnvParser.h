#pragma once

#include "Core/Core.h"
#include "Utility/StringUtil.h"

#include <optional>

namespace Sirius {

class SIRIUS_API EnvParser {
public:
    // Parses the env string. If there is sush key, returns the value, if not, return std::nullopt
    static std::optional<std::string> Get(const std::string& key);

    // Parses the env string and gets its contents. Returns defaultValue if missing or invalid.
    static std::string GetString(const std::string& key, const std::string& defaultValue = "");

    // Parses the env string and gets its contents. Returns defaultValue if missing or invalid. Result is in lower case
    static std::string GetStringLower(const std::string& key, const std::string& defaultValue = "");

    // Parses the env var as an integer. Returns defaultValue if missing or invalid.
    static size_t GetInt(const std::string& key, size_t defaultValue = 0);
};

} // namespace Sirius