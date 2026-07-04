// #FILE: logging.cpp, Component Source File
// #BRIEF: Source file for project logging component

module;

#include "core.hpp" // #INCLUDE: core.hpp, Package wide header
 
module docme.core; // #IMPLEMENTS: docme.core:logging
import :logging;

namespace docme::core{ // #SCOPE: docme::core

// ------------------------------------------------------------------------------
//                                  class Logger
// ------------------------------------------------------------------------------

// #SCOPE: Logger

// #DIV: Private

// ---- Private Factory Methods ----

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

    // #METHOD: makeCommaSeparated(const std::vector<std::string>&), Static Method
    // #BRIEF: Takes a list of strings and makes a single comma separated string
    // #PARAM: const std::vector<std::string>& p_list, Given list
    // #RETURN: std::string, Constructed string
    std::string Logger::makeCommaSeparated(const std::vector<std::string>& p_list){
        std::string string;
        for(size_t item = 0; item < p_list.size(); item++){
            if(item == p_list.size() - 1){ // Last item
                string += p_list[item];
            }else{
                string += (p_list[item] + ", ");
            }
        }
        return string;
    } // #END: makeCommaSeparated(const std::vector<std::string>&)

// #END: Logger

} // #END: docme::core
