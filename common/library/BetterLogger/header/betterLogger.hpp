#pragma once

// #file: betterLogger.hpp, header file
// #info: defines outline for project namespaces and class declorations
// #attach: includes.hpp, project includes

// project wide includes
#include "includes.hpp"

// #namespace: worTech(wt), developer namespace
// #info: holds all projects of worTech group
// #scope: global space
inline namespace worTech{
    // #namespace: betterLogger(better)(btr), project namespace
    // #info: holds all comonents of betterLogger project
    // #scope: worTech, developer namespace
    namespace betterLogger{
        // #namespace: helpers, component namespace
        // #info: holds helper classes
        // #scope: betterLogger, project namespace
        inline namespace helpers{
            class Helper; using Help = Helper;
        }
        // #namespace: logStacks, component namespace
        // #info: holds log stack class and related namespace
        // #scope: betterLogger, project namespace
        inline namespace logStacks{
            namespace defaultFormats{} namespace deflt = defaultFormats;
            class LogStack;
        } namespace stacks = logStacks;
        // #namespace: formats, component namespace
        // #info: holds log formatting enums and related namespaces
        // #scope: betterLogger, project namespace
        inline namespace formats{
            namespace ansiiColorCodes{} namespace ansii = ansiiColorCodes;
            enum class LogLevel: uint8_t; using Level = LogLevel;
            enum class FormatType: uint8_t; using Format = FormatType;
            namespace logFormatting{} namespace log = logFormatting;
        }
        // #namespace: loggers, component namespace
        // #info: holds logger class and related namespace
        // #scope: betterLogger, project namespace
        inline namespace loggers{
            namespace defaultFormats{} namespace deflt = defaultFormats;
            class Logger;
        } namespace logs = loggers;
        // #namespace: defaultLogStacks, component namespace
        //#info: holds built in log stacks
        // #scope: betterLogger, project namespace
        inline namespace defaultLogStacks{
            namespace loggerValues{} namespace logger = loggerValues;
            class AutoFlush;
            class TerminateFlush;
        }
        // #namespace: defaultLoggers, component namespace
        // #info: holds built in loggers and related namespace
        // #scope: betterLogger, project namespace
        inline namespace defaultLoggers{
            namespace loggerValues{} namespace logger = loggerValues;
            class Main;
            class Debug;
        }
    } namespace better = betterLogger; namespace btr = betterLogger;
} namespace wt = worTech;