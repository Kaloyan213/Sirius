/* 
 * Copyright (c) Kaloyan Badankov
 */
 
#pragma once

#include "Sirius/Core/Core.h"

namespace Sirius {

class SIRIUS_API Application {
  public:
    Application();
    virtual ~Application();

    void Run();
};

/*_ TO BE DEFINED BY THE API USER _*/
Application* CreateApplication();

} // namespace Sirius
