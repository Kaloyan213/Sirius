/* 
 * Copyright (c) Kaloyan Badankov
 */
 
#include "Sirius/Utility/Logger.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/cfg/env.h"


namespace SiriusAPI {

Logger::Logger(const std::string loggerName) : loggerName{loggerName} {
    coreLogger = spdlog::stdout_color_mt(loggerName);
    spdlog::cfg::load_env_levels(loggerName.c_str());
}

void Logger::logMsg(LogLevel logLevel, std::string msg)
{
    if (coreLogger) {
        coreLogger->log(logLevel, msg);
    }
}

void Logger::Init() {
    spdlog::set_pattern("[%H:%M:%S] [Thread: %t] [%n] [%L] %^%v%$");
    spdlog::set_level(LogLevel::info);
}

Logger& gLogger()
{
    static Logger instance("Default");
    return instance;
}

Logger& CoreLogger()
{
    static Logger instance("Sirius");
    return instance;
}

} // namespace SiriusAPI

