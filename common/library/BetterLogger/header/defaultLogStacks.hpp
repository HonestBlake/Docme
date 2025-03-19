#pragma once

// #file: defaultLogStacks.hpp, header file
// #info: defines built in log stacks
// #attach: betterLogger.hpp, internal dependency
// #attach: logStacks.hpp, internal dependency

// project header
#include "betterLogger.hpp"
// log stack class
#include "logStacks.hpp"

namespace worTech::betterLogger::defaultLogStacks{

    // #namespace: loggerValues(logger), variable namespace
    // #scope: defaultLogStacks, component namespace
    // #info: holds values for log stack classes
    namespace loggerValues{
        const bool AUTO_FLUSH_TERMINATE_FLUSH = false;
        const bool AUTO_FLUSH_AUTO_FLUSH = true;
        const bool TERMINATE_FLUSH_TERMINATE_FLUSH = true;
        const bool TERMINATE_FLUSH_AUTO_FLUSH = false;
    }
    // #class: AutoFlush, singleton class
    // #scope: defaultLogStacks, component namespace
    // #info: default log stack that flushes automatically
    class AutoFlush: public LogStack{
    public:
        friend class LogStack;
    private:
        AutoFlush();
    };
    // #class: TerminateFlush, singleton class
    // #scope: defaultLogStacks, component namespace
    // #info: default log stack that flushes on termination
    class TerminateFlush: public LogStack{
    public:
        friend class LogStack;
    private:
        TerminateFlush();
    };

} // namespace worTech::betterLogger::defaultLogStacks