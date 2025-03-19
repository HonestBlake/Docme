#pragma once

// #file: defaultLoggers.hpp, header file
// #info: holds class definitions for built in loggers
// #attach: betterLogger.hpp, internal dependency
// #attach: loggers.hpp, internal dependency

// project header
#include "betterLogger.hpp"
// Logger class header
#include "loggers.hpp"

namespace worTech::betterLogger::defaultLoggers{

    // #namespace: loggerValues(logger), variable namespace
    // #scope: defaultLoggers, component namespace
    // #info: holds values for default log stack classes
    namespace loggerValues{
        const std::string MAIN_NAME = "main";
        const std::string DEBUG_NAME = "debug";
    }
    // #class: Main, singleton class
    // #scope: defaultLoggers, component namespace
    // #info: default main logger
    class Main: public Logger{
    public:
        Main();
    };
    // #class: Debug, singleton class
    // #scope: defaultLoggers, component namespace
    // #info: default debug logger
    class Debug: public Logger{
    public:
        Debug();
    };

} // namespace worTech::betterLogger::defaultLoggers