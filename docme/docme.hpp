// #file: autoDoc.hpp, header file

#pragma once

// include libraries globally
#include "standardLibs.hpp"
#include "externalLibs.hpp"

// #namespace: worTech, inline developer namespace
inline namespace worTech{
    // #namespace: docme, project namespace
    namespace docme{
        // #namespace: programVariables, inline module namespace
        inline namespace programVariables{
            namespace programConstants{}
            namespace program = programConstants; // alias programConstants to program
            namespace programStates{}
            namespace state = programStates; // alias programStates to state
        }
        // #namespace: debugging, inline module namespace
        inline namespace debugging{
            namespace errorMessages{}
            namespace error = errorMessages; // alias errorMessages to error
            namespace debugTools{}
            namespace debug = debugTools; // alias debugTools to debug
            namespace loggerValues{}
            namespace logger = loggerValues; // alias loggerValues to logger
            class AutoDocTracer;
            class AutoDocDebug;
        }
        // #namespace: jsonTools, inline module namespace
        inline namespace jsonTools{

        }
        inline namespace config{}
        inline namespace genorator{} 
        namespace gen = genorator; // alias genorator to gen
    } // namespace docme
} // inline namespace worTech
namespace wt = worTech; // alias worTech to wt

#include "debugging.hpp" // include debugging module globally
#include "programVariables.hpp" // include program variables module globally