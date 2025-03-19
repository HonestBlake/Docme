#pragma once

// #file: source/helpers.hpp, source file
// #info: defines functions of Helper class
// #attach: header/helpers.hpp, internal dependency

// header file
#include "header/helpers.hpp"

namespace worTech::betterLogger::helpers{

    // #func: getCurrentTime(), public static method
    // #scope: Helper, static class
    // #info: gets the current time as a time_t variable
    // #note: relies on RVO to avoid copying
    // #returns: time_t, current time 
    time_t Helper::getCurrentTime(){
        return std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    }

} // namespace worTech::betterLogger::helpers