// #file: autoDoc.hpp, header file

#pragma once

#include "macroSetup.hpp" // include macro setup globally

// include libraries globally
#include "standardLibs.hpp"
#include "externalLibs.hpp"

// #namespace: worTech, inline developer namespace
inline namespace worTech{
    // #namespace: autoDoc, project namespace
    namespace autoDoc{
        // #namespace: debugging, inline module namespace
        inline namespace debugging{
            namespace debugStates{}
            namespace state = debugStates; // alias debugStates to debug
            namespace errorMessages{}
            namespace error = errorMessages; // alias errorMessages to error
            namespace debugTools{}
            namespace debug = debugTools; // alias debugTools to debug
            class AutoDocTracer;
            class AutoDocDebug;
        }
        inline namespace config{}
        inline namespace genorator{} 
        namespace gen = genorator; // alias genorator to gen
    } // namespace autoDoc
    namespace adoc = autoDoc; // alias  autoDoc to adoc
} // inline namespace worTech
namespace wt = worTech; // alias worTech to wt

#include "debugging.hpp" // include debugging module globally