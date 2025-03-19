#pragma once

// #file: logStack.hpp, source file
// #info: holds function definitions 
// #attach: header/logStacks.hpp, internal dependency

// decloration header
#include "header/logStacks.hpp"

namespace worTech::betterLogger::logStacks{

// #div: public factory methods

    // #func: ~LogStack(), virtual public destructor
    // #scope: LogStack, abstact singleton class
    // #info: destuctor for LogStack base class that conditionally calls a log flush
    // #calls: flush();
    LogStack::~LogStack(){
        if(m_terminateFlush){
            flush();
        }
    }

// #div: public static methods

    // #func: get<T_derived>(), public static method
    // #scope: LogStack, abstact singleton class
    // #info: creates and returns a static instance of a LogStack derived class
    // #template: class T_derived, derived class of LogStack
    // #calls: T_derived();
    template<class T_derived> LogStack& LogStack::get(){
        static T_derived instance = T_derived();
        return instance;
    }

// #div: public methods

    // #func: pushLog(std::string&), public method
    // #scope: LogStack, abstact singleton class
    // #info: pushes a log into the log buffer and conditionally flushes buffer
    // #overload: pushLog(std::string&&)
    // #param: const std::string& p_log, log to be pushed into buffer
    // #returns: LogStack&, current instance
    LogStack& LogStack::pushLog(const std::string& p_log){
        m_logBuffer.push_back(p_log);
        if(m_instantFlush){
            flush();
        }
        return *this;
    }
    // #func: pushLog(std::string&&), public method
    // #scope: LogStack, abstact singleton class
    // #info: pushes a log into the log buffer and conditionally flushes buffer
    // #note: takes ownership of passed log
    // #overload: pushLog(std::string&)
    // #param: const std::string& p_log, log to be pushed into buffer
    // #returns: LogStack&, current instance
    LogStack& LogStack::pushLog(std::string&& p_log){
        m_logBuffer.push_back(std::forward<std::string>(p_log));
        if(m_instantFlush){
            flush();
        }
        return *this;
    }
    // #func: flush(), public method
    // #scope: LogStack, abstact singleton class
    // #info: flushes the log buffer
    // #note: transfers ownership of logs on buffer outside of function
    // #returns: LogStack&, current instance
    LogStack& LogStack::flush(){
        for(std::string& log: m_logBuffer){
            recordLog(std::move(log));
        }
        m_logBuffer.clear();
        return *this;
    }

// #div: protected factory methods

    // #func: LogStack(bool, bool), protected constructor
    // #scope: LogStack, abstact singleton class
    // #info: creates a LogStack instance with given flush conditions
    // #param: bool p_terminateFlush, condition to flush buffer on destruction
    // #param: bool p_instantFlush, condition to flush buffer on log push
    LogStack::LogStack(bool p_terminateFlush, bool p_instantFlush): m_terminateFlush(p_terminateFlush), m_instantFlush(p_instantFlush){}

// #div: protected methods

    // #func: recordLog(std::string&&), protected virtual method
    // #scope: LogStack, abstact singleton class
    // #info: records a log
    // #note: can be overriden to change log recording method
    // #note: takes ownership of passed log
    // #param: std::string&& p_log, log to be recorded
    void LogStack::recordLog(std::string&& p_log){
        std::cout << p_log << std::endl;
    }
    
} // namespace worTech::betterLogger::logStacks