#pragma once
#include <memory.h>
#include <stdint.h>
#include "spdlog/spdlog.h"

inline namespace SiriusAPI
{

using LogLevel = spdlog::level::level_enum;
using SpdLogger = std::shared_ptr<spdlog::logger>;

}