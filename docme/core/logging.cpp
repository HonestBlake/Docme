// #FILE: logging.cpp, Component Source File
// #BRIEF: Source file for project logging component

module;

#include "core.hpp" // #INCLUDE: core.hpp, Package wide header
 
module docme.core; // #IMPLEMENTS: docme.core:logging
import :logging;

namespace docme::core{ // #SCOPE: docme::core

    Logger& logger = Logger::get();
    Output& output = Output::get();

// ------------------------------------------------------------------------------
//                                  class Logger
// ------------------------------------------------------------------------------

// #SCOPE: Logger

// #DIV: Private

// ---- Private Special Methods ----

    // #METHOD: Logger(), Private Constructor
    // #BRIEF: Default constructor for logger 
    Logger::Logger(): LoggerBase(NAME, s_outputStream){
        levelSpecificLogColor(pureLog::Log::Level::WARN, pureLog::Color::YELLOW);
        levelSpecificLogColor(pureLog::Log::Level::ERROR, pureLog::Color::RED);
        levelSpecificLogColor(pureLog::Log::Level::DEBUG, pureLog::Color::BLUE);
    } // #END: Logger()


// #DIV: Public

// ---- Public Static Methods ----

    // #METHOD: get(), Static Method
    // #BRIEF: Returns the instance of the logger 
    // #RETURN: Logger&, Reference to current logger
    Logger& Logger::get(){
        return LoggerBase::get();
    } // #END: get()


// #END: Logger

// ------------------------------------------------------------------------------
//                                  class Output
// ------------------------------------------------------------------------------

// #SCOPE: Output

// #DIV: Private

// ---- Private Special Methods ----

    // #METHOD: Output(), Private Constructor
    // #BRIEF: Default constructor for output 
    Output::Output(): OutputBase(NAME, s_outputStream){
        nameFormat("");
    } // #END: Output()


// #DIV: Public

// ---- Public Static Methods ----

    // #METHOD: get(), Static Method
    // #BRIEF: Returns the instance of the output 
    // #RETURN: Output&, Reference to current output
    Output& Output::get(){
        return OutputBase::get();
    } // #END: get()


// #END: Output

} // #END: docme::core
