/* 
 * Copyright (c) Kaloyan Badankov
 */
 
#pragma once

#include "Sirius/Utility/Logger.h"
#include "Sirius/Utility/StringUtil.h"

extern Sirius::Application* Sirius::CreateApplication();

int main(int argc, char** argv) {
    Logger::Init();

    bool niceBool {true};
    uint32_t niceInt {45};
    std::string niceString = StringUtil::ToString (niceBool);
    std::string niceIntString = StringUtil::ToString (niceInt);
    uint32_t fromIntString = StringUtil::FromString <uint32_t>(niceIntString);

    CoreLogger().Log(LogLevel::err, fromIntString);
    auto app = Sirius::CreateApplication();
    app->Run();
    delete app;
}
