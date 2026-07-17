// #FILE: logging.tpp, Component Template Implementation File
// #BRIEF: Template definitions for logging component.

#ifndef COMPILED_WITH_MODULE // Open in editor

module;

#include "core.hpp" // #INCLUDE: core.hpp, Package wide header

module docme.core; // #IMPLEMENTS: docme.core:logging
import :logging;

import pureLog; // #IMPORT: pureLog, External logging lib

#endif

namespace docme::core{ // #SCOPE: docme::core

// ------------------------------------------------------------------------------
//                                  class Logger
// ------------------------------------------------------------------------------

// #SCOPE: Logger

// #DIV: Public

// ---- Public Methods ----

    // #METHOD: debug(), Template Instance Method
    // #BRIEF: Debug log method with formatting
    // #TEMPLATE: class... T_Args, Variadic template parameter pack
    // #PARAM: const std::string&& p_message, Message to log
    // #PARAM: T_Args&&... p_args, Variadic template parameter pack of formatting arguments
    template<class... T_Args> void Logger::debug(const std::string&& p_message, T_Args&&... p_args){
        initiateLog(pureLog::Log::Level::DEBUG, std::move(p_message), std::forward<T_Args>(p_args)...);
        flushBuffer();
    } // #END: debug(const std::string&&, T_Args&&...)


// #END: Logger

} // #END: docme::core
