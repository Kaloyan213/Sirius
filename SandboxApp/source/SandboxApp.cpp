/* 
 * Copyright (c) Kaloyan Badankov
 */
 
#include <Core/SiriusCoreMinial.h>
#include "SandboxLogger.h"

class SandboxApp : public Application {
protected:
    void OnInit() override {
        SandboxLogger().Log(LogLevel::info, "Sandbox ready!");        
    }

    void OnTick() override {
        SandboxLogger().Log(LogLevel::debug, "Sandbox ready!");
      }
};

int main([[maybe_unused]]int argc, [[maybe_unused]]char** argv) {
    SandboxApp app;
    app.Initialize();
    
    app.Run (); 

    return 0;
}