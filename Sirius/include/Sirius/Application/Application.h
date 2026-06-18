/* 
 * Copyright (c) Kaloyan Badankov
 */
 
#pragma once

#include "Sirius/Core/Core.h"
#include <string>

namespace Sirius {

class SIRIUS_API Application {
  public:
    Application();
    // Application(int argc = 0, char** argv = nullptr);
    virtual ~Application();

    void Run();
};

/*_ TO BE DEFINED BY THE API USER _*/
Application* CreateApplication();

} // namespace Sirius
