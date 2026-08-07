/* 
 * Copyright (c) Kaloyan Badankov
 */
 
#include "Application/Application.h"
#include "Utility/Logger.h"
#include "Application/Config.h"

namespace SiriusAPI {

Application::Application() {

}


int Application::Run() {
    while (!exitRequested) {
        OnTick ();
    };

    Deinit ();
    return true;
}

int Application::Initialize()
{
    Sirius::Config::ReadAllConfigs (true);
    Logger::Init();
    CoreLogger().Log(LogLevel::info, "Engine Initialized!");
    
    OnInit ();
    return 0;
}

void Application::OnInit()
{
}

void Application::OnTick()
{
}

void Application::Shutdown()
{
    exitRequested = true;
}

void Application::Deinit()
{
    
}

} // namespace SiriusAPI
