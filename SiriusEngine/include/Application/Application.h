/* 
 * Copyright (c) Kaloyan Badankov
 */
 
#pragma once

#include "Core/Core.h"
#include <string>

inline namespace SiriusAPI {

class SIRIUS_API Application {
  public:
    Application();
    //TODO Kalo - Add the options parser
    // Application(int argc = 0, char** argv = nullptr);
    virtual ~Application() = default;
    
    // Initializes the engine subsystems, should be called before application run
    int Initialize ();

    // Contains the main engine loop
    int Run ();

    // Shutdowns the application gracefully
    void Shutdown ();

protected:
    //Gets called once all the modules are initialized
    virtual void OnInit ();

    //Gets called on every loop of the application
    virtual void OnTick ();

private:
  void Deinit ();

private:
  bool exitRequested {false};
};
} // namespace SiriusAPI