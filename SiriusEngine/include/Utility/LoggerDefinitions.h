/* 
 * Copyright (c) Kaloyan Badankov
 */

#pragma once
#include <memory.h>
#include <stdint.h>
#include "spdlog/spdlog.h"

inline namespace SiriusAPI
{

using LogLevel = spdlog::level::level_enum; //Default log level is info
using SpdLogger = std::shared_ptr<spdlog::logger>;

static constexpr const LogLevel defaultLogLevel = LogLevel::info;
} //namespace SiriusAPI