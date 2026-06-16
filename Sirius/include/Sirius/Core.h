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
#else
#error Sirius only supports Windows!
#endif
