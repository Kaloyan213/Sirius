/* 
 * Copyright (c) Kaloyan Badankov
 */
 
#pragma once

#include "Sirius/Utility/Logger.h"

extern Sirius::Application* Sirius::CreateApplication();

int main(int argc, char** argv) {
    Logger::Init();
    CoreLogger().Log(LogLevel::err, "Qbaaaa");
    auto app = Sirius::CreateApplication();
    app->Run();
    delete app;
}
