// #FILE: logging.cpp, Component Source File
// #BRIEF: Source file for project logging component

module;

#include "docme.hpp" // #INCLUDE: docme.hpp, Project wide header

module docme.core; // #IMPLEMENTS: docme.core:logging
import :logging;

namespace docme::core{ // #SCOPE: docme::core

// #SCOPE: Logger

    // #METHOD: Logger(), Private Constructor
    // #BRIEF:
    Logger::Logger(): LoggerBase(NAME, s_outputStream){
        levelSpecificLogColor(pureLog::Log::Level::WARN, pureLog::Color::YELLOW);
        levelSpecificLogColor(pureLog::Log::Level::ERROR, pureLog::Color::RED);
    } // #END: logger

    // #METHOD: get(), Public Static Method
    // #BRIEF: Gets logger instance
    // #RETURN: Logger&, Reference to logger
    Logger& Logger::get(){
        return LoggerBase::get();
    } // #END: get()


// #END: Logger
    
} // #END: docme::core
