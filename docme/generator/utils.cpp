// #FILE: utils.cpp, Component Source File
// #BRIEF: Source file for utils component

module;

#include "generator.hpp" // #INCLUDE: generator.hpp, Package wide header

module docme.generator; // #IMPLEMENTS: docme.generator:utils
import :utils;

import docme.core; // #IMPORT: docme.core, Core module

namespace docme::generator{ // #SCOPE: docme::generator

// ------------------------------------------------------------------------------
//                                namespace util
// ------------------------------------------------------------------------------

// #SCOPE: utils

// ---- Debug Only Functions ----

#if DOCME_DEBUG

    // #FUNCTION: printLanguageHandler(const std::string&, const std::string_view, const LanguageHandler&), Free Function
    // #BRIEF: Debug prints the given language handler
    // #PARAM: const std::string& p_message, The message to print before the language handler
    // #PARAM: const std::string_view p_tag, The tag of the language handler to print
    // #PARAM: const LanguageHandler& p_handler, The language handler to print
    void util::printLanguageHandler(const std::string& p_message, const std::string_view p_tag, const LanguageHandler& p_handler){
        logger.debug(p_message + ": name={}; version={}; description={}; author={}",
            p_tag,
            p_handler.name,
            p_handler.version,
            p_handler.description,
            p_handler.author
        );
    } // #END: printLanguageHandler(const std::string&, const std::string_view, const LanguageHandler&)

#endif

// #END: util

} // #END: docme::generator
