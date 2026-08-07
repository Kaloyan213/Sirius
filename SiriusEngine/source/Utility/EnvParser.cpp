#include "Utility/EnvParser.h"
#include <cstdlib>

namespace Sirius {

std::optional<std::string> EnvParser::Get(const std::string& key) {
    if (const char* val = std::getenv(key.c_str())) {
        return std::string(val);
    }
    return std::nullopt;
}

std::string EnvParser::GetString(const std::string& key, const std::string& defaultValue) {
    auto val = Get(key);
    return val.has_value() ? val.value() : defaultValue;
}

std::string EnvParser::GetStringLower(const std::string& key, const std::string& defaultValue) {
    // StringUtil handles the copy and lowercase conversion cleanly
    return StringUtil::ToLowercase(GetString(key, defaultValue));
}

size_t EnvParser::GetInt(const std::string& key, size_t defaultValue) {
    auto val = Get(key);
    
    if (val.has_value()) {
        return StringUtil::FromString<int>(val.value(), defaultValue);
    }
    
    return defaultValue;
}

} // namespace Sirius