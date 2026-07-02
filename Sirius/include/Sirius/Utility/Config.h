/* 
 * Copyright (c) Kaloyan Badankov
 */
 
#pragma once
#include <optional>
#include <string> 
#include "Sirius/Core/Core.h"
#include "config-cxx/config.h"
 
namespace Sirius{

class SIRIUS_API Config final{
public:
    template <typename T>
    static std::optional<T> GetPropertyValue(std::string propertyName);

    template <typename T>
    static T GetPropertyValue(std::string propertyName, const T& defaultValue);

    static bool isBooleanPropertyEnabled (std::string propertyName);

    static int Init (const std::string& configName);

private:
	Config () = delete;
	~Config () = delete;

   inline static config::Config configObj;
};


template<typename T>
inline std::optional<T> Config::GetPropertyValue (std::string propertyName)
{
    return configObj.getOptional<T> (propertyName);
}

template<typename T>
inline T Config::GetPropertyValue (std::string propertyName, const T& defaultValue)
{
    return configObj.getOrDefault (propertyName, defaultValue);
}

}
