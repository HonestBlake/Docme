// #FILE: handler.cpp, Component Source File
// #BRIEF: Source file for handler component

module;

#include "cdoc.hpp" // #INCLUDE: cdoc.hpp, Package wide header

module docme.cdoc; // #IMPLEMENTS: docme.cdoc:handler
import :handler;

namespace docme::cdoc{ // #SCOPE: docme::cdoc

// ------------------------------------------------------------------------
//                          class Handler 
// ------------------------------------------------------------------------

// #SCOPE: Handler

// #DIV: public

// ---- Public Static Methods ----

    // #METHOD: supportsFileType(const std::string_view p_fileType), Static Method
    // #BRIEF: Checks if the given file type is supported by this handler
    // #PARAM: const std::string_view p_fileType, The file type to check
    // #RETURN: bool, True if the file type is supported, false otherwise
    bool Handler::supportsFileType(const std::string_view p_fileType){
        return SUPPORTED_FILE_TYPES.contains(p_fileType);
    } // #END: supportsFileType(const std::string_view p_fileType)
    

} // #END: docme::cdoc