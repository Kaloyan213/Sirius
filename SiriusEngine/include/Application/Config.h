#pragma once

#include "Core/Core.h"
#include "Utility/StringUtil.h"
#include <string_view>
#include <unordered_map>
#include <filesystem>

/*_Static Config class responsible for collecting data from all configs, or just some instances_ */
/*_The config should be either in the main build directory of the project subdirectory of the build folder called Configs_ */
namespace FS = std::filesystem;

namespace Sirius {

class SIRIUS_API Config {
public:
    // Loads and parses a .cfg file. Returns true if successful.
    static bool ReadConfig(const std::string& filename, bool isAlwaysExpected = false);
    
    static bool ReadConfig(const FS::path& filename, bool isAlwaysExpected = false);

    static bool ReadAllConfigs(bool isAlwaysExpected);
    
    static bool IsInitialized ();
    static bool HasProperty (std::string_view propertyName);
    static bool IsBooleanPropertyEnabled(const std::string& key);

    static const std::string GetPropertyValue (std::string_view propertyName, const std::string defaultValue);

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