#pragma once

// #file: logStack.hpp, header file
// #info: holds definition for LogStack class
// #attach: betterLogger.hpp, internal dependency

// project header
#include "betterLogger.hpp"

namespace worTech::betterLogger::logStacks{

    // #namespace: defaultFormats(deflt), variable namespace
    // #scope: logStacks, component namespace
    // #info: holds default values for log stack
    namespace defaultFormats{
        const bool TERMINATE_FLUSH = false;
        const bool INSTANT_FLUSH = true;
    }
    // #class: LogStack, abstract singleton class
    // #info: data structure for log buffering
    // #scope: logStacks, component namespace
    // #uses: deflt, variable namespace
    class LogStack{
    public:
    // #div: public factory methods
        virtual ~LogStack() = 0;
    // #div: public static methods
        template<class T_derived> static LogStack& get();
    // #div: public methods
        LogStack& pushLog(const std::string& p_log);
        LogStack& pushLog(std::string&& p_log);
        LogStack& flush();
    protected:
    // #div: protected factory methods
        LogStack() = default;
        LogStack(bool p_terminateFlush, bool p_instantFlush);
        LogStack(const LogStack&) = delete;
        LogStack(LogStack&&) = delete;
    // #div: protected operators
        LogStack& operator=(const LogStack&) = delete;
        LogStack& operator=(LogStack&&) = delete;
    // #div: protected members
        std::vector<std::string> m_logBuffer;
        bool m_terminateFlush = deflt::TERMINATE_FLUSH;
        bool m_instantFlush = deflt::INSTANT_FLUSH;
    // #div: protected methods
        virtual void recordLog(std::string&& p_log);
    };

} // namespace worTech::betterLogger::logStacks