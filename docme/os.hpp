// #FILE: os.hpp, Header File
// #BRIEF: Project wide os tools

#pragma once

#include "std.hpp" // #INCLUDE: std.hpp, Project wide std libs

namespace docme{ // #SCOPE: docme

    // #NAMESPACE: os, Namespace
    // #BRIEF: Project wide os tools
    namespace os{

        // #ENUM: OperatingSystem, std::uint8_t Enum Class
        // #BRIEF: Enum class for operating system types
        enum OperatingSystem: std::uint8_t{ 
            WINDOWS, 
            LINUX, 
            MACOS
        }; // #END: OperatingSystem

        inline constexpr OperatingSystem OPERATING_SYSTEM = 
        #if defined(_WIN32)
            WINDOWS;
        #elif defined(__linux__)
            LINUX;
        #elif defined(__APPLE__) && defined(__MACH__)
            MACOS;
        #else
            #error "Unsupported operating system"
        #endif
        
        // #FUNCTION: isWindows(), Constexpr Function
        // #BRIEF: Checks if the current operating system is Windows
        // #RETURN: bool, True if the current operating system is Windows, false otherwise
        constexpr bool isWindows(){
            return OPERATING_SYSTEM == WINDOWS;
        } // #END: isWindows()

        // #FUNCTION: isLinux(), Constexpr Function
        // #BRIEF: Checks if the current operating system is Linux
        // #RETURN: bool, True if the current operating system is Linux, false otherwise
        constexpr bool isLinux(){
            return OPERATING_SYSTEM == LINUX;
        } // #END: isLinux()

        // #FUNCTION: isMacOS(), Constexpr Function
        // #BRIEF: Checks if the current operating system is MacOS
        // #RETURN: bool, True if the current operating system is MacOS, false otherwise
        constexpr bool isMacOS(){
            return OPERATING_SYSTEM == MACOS;
        } // #END: isMacOS()

    } // #END: os

} // #END: docme