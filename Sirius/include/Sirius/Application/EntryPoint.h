/* 
 * Copyright (c) Kaloyan Badankov
 */
 
#pragma once

#include "Sirius/Utility/Logger.h"
#include "Sirius/Utility/StringUtil.h"

extern Sirius::Application* Sirius::CreateApplication();

int main(int argc, char** argv) {
    Logger::Init();
    CoreLogger().Log(LogLevel::warn, "Start ", "your ", "engines!");

    auto app = Sirius::CreateApplication();
    app->Run();
    delete app;
}
