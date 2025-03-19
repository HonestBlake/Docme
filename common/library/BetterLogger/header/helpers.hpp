#pragma once

// #file: header/helpers.hpp, header file
// #info: defines Helper class
// #attach: betterLogger.hpp, internal dependency

// project include
#include "betterLogger.hpp"

namespace worTech::betterLogger::helpers{

    // #class: Helper, static class
    // #scope: helpers, component namespace
    // #info: holds helper functionality 
    class Helper{
    public:
        static time_t getCurrentTime();
    };

} // namespace worTech::betterLogger::helpers