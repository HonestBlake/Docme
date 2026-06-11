// #FILE: logging.cpp, Component Source File
// #BRIEF: Source file for project logging component

module;

#include "core.hpp" // #INCLUDE: core.hpp, Package wide header
 
module docme.core; // #IMPLEMENTS: docme.core:logging
import :logging;

namespace docme::core{ // #SCOPE: docme::core
    
    // #METHOD: Logger(), Private Constructor
    // #BRIEF: Default constructor for logger 
    Logger::Logger(): LoggerBase(NAME, s_outputStream){
        levelSpecificLogColor(pureLog::Log::Level::WARN, pureLog::Color::YELLOW);
        levelSpecificLogColor(pureLog::Log::Level::ERROR, pureLog::Color::RED);
    } // #END: Logger()

    // #METHOD: get(), Public Method
    // #BRIEF: Returns the instance of the logger 
    // #RETURN: Logger&, Reference to current logger
    Logger& Logger::get(){
        return LoggerBase::get();
    } // #END: get()

} // #END: docme::core
