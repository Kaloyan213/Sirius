/* 
 * Copyright (c) Kaloyan Badankov
 */
 
#include <Sirius/Core/SiriusCoreMinial.h>

class Sandbox : public Sirius::Application {
  public:
    Sandbox(){

    };

    ~Sandbox() {
    }
};

Sirius::Application* Sirius::CreateApplication() {
    return new Sandbox();
}