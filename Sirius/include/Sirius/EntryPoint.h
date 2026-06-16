/* 
 * Copyright (c) Kaloyan Badankov
 */
 
#pragma once
#ifdef SIRIUS_PLATFORM_WINDOWS

#include "Sirius/Utility/Logger.h"

extern Sirius::Application* Sirius::CreateApplication();

int main(int argc, char** argv) {
    Logger::Init();

    CoreLogger().Log(LogLevel::info, "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.");

    auto app = Sirius::CreateApplication();
    app->Run();
    delete app;
}

#endif
