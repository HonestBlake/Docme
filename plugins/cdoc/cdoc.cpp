// #FILE: cdoc.cpp, Plugin Entry Source File
// #BRIEF: Entry source file for CDoc language handler plugin

#include "plugins.hpp" // #INCLUDE: cdoc.hpp, Program wide header

import docme.cdoc;

PLUGIN_EXPORT bool supportsFileType(const char* p_fileType)noexcept{
    return p_fileType != nullptr && docme::cdoc::Handler::supportsFileType(p_fileType);
}