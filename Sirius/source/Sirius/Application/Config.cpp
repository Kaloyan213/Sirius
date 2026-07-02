#include "Sirius/Utility/Config.h"

namespace Sirius {

int Config::Init(const std::string &configName)
{
    if (!configName.empty()){
        configObj.initialize (configName);
    }
    return 0;
}

bool Config::isBooleanPropertyEnabled(std::string propertyName)
{
    return GetPropertyValue (propertyName, false);
}
}