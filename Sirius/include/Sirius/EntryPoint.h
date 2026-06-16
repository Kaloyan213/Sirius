#pragma once
#ifdef SIRIUS_PLATFORM_WINDOWS

extern Sirius::Application* Sirius::CreateApplication();

int main(int argc, char** argv) {
    printf("Sirius Engine");
    auto app = Sirius::CreateApplication();
    app->Run();
    delete app;
}

#endif
