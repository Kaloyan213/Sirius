/* 
 * Copyright (c) Kaloyan Badankov
 */
 
#include "Utility/Logger.h"
#include "Application/Config.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/cfg/env.h"

namespace {
    LogLevel getLogLevel () {
    std::string level = Sirius::Config::GetPropertyValue ("log_level", std::string ("info"));

    if (level == "trace") {
        return LogLevel::trace;
    } 
    else if (level == "debug") {
        return LogLevel::debug;
    } 
    else if (level == "info") {
        return LogLevel::info;
    } 
    else if (level == "warn" || level == "warning") {
        return LogLevel::warn;
    } 
    else if (level == "err" || level == "error") {
        return LogLevel::err;
    } 
    else if (level == "critical") {
        return LogLevel::critical;
    } 
    else if (level == "off") {
        return LogLevel::off;
    }

    return LogLevel::debug; 
    }

}

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
    spdlog::set_level(getLogLevel());
}

void Logger::ChangeLogLevel(const LogLevel newLogLevel)
{
    spdlog::set_level(newLogLevel);
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

