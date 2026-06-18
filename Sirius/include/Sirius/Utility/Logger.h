/* 
 * Copyright (c) Kaloyan Badankov
 */
 
#pragma once

#include <sstream>   

#include "Sirius/Core/Core.h"
#include "LoggerDefinitions.h"

inline namespace SiriusAPI {

class SIRIUS_API Logger {
public:
    Logger(const std::string loggerName);

    static void Init ();

    template <typename... Args>
    inline void Log(LogLevel logLevel, Args&&... args);

protected:
    void logMsg(LogLevel logLevel, std::string msg);

private:
    SpdLogger coreLogger;
    std::string loggerName{};
};

/*_ Common, global logger instance, used where no specific logger is declared _*/
SIRIUS_API Logger& gLogger();


/*_ Common, engine logger instance, used where no specific logger is declared _*/
SIRIUS_API Logger& CoreLogger();


template <typename... Args>
inline void Logger::Log(LogLevel logLevel, Args&&... args) {
    std::stringstream ss;
    (ss << ... << args);
    logMsg(logLevel, ss.str());
};
} // namespace SiriusAPI

