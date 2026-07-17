#pragma once

#include "std.hpp" // #INCLUDE: std.hpp, Standard library headers

#ifdef _WIN32 // Windows
    
    #define PLUGIN_EXPORT extern "C" __declspec(dllexport)

#else

    #define PLUGIN_EXPORT extern "C" __attribute__((visibility("default")))

#endif