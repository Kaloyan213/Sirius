/* 
 * Copyright (c) Kaloyan Badankov
 */
 
#pragma once

#ifdef SIRIUS_PLATFORM_WINDOWS
#ifdef SIRIUS_BUILD_DLL
#define SIRIUS_API __declspec(dllexport)
#else
#define SIRIUS_API __declspec(dllimport)
#endif
#elif SIRIUS_PLATFORM_LINUX
    #ifdef SIRIUS_BUILD_DLL
        #define SIRIUS_API __attribute__((visibility("default")))
    #else
        #define SIRIUS_API
    #endif
#else
#error Sirius only supports Windows and Linux!
#endif
