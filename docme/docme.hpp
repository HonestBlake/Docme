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
        inline namespace jsonTools{}
        // #namespace: nodes, inline module namespace
        inline namespace nodes{
            namespace nodeDefaultValues{}
            namespace node = nodeDefaultValues; // alias nodeDefaultValues to node
            class Node;
            class DirectoryNode;
            class DocumentedNode;
            class FileNode;
            class ComponentNode;
            class GlobalNode;
        }
        // #namespace: restrictedTypes, inline component namespace
        inline namespace restrictedTypes{}
        // #namespace: config, inline package namespace
        inline namespace config{}
        // #namespace: processor, inline package namespace
        inline namespace processor{}
    } // namespace docme
} // inline namespace worTech
namespace wt = worTech; // alias worTech to wt

#include "debugging.hpp" // Include debugging module globally
#include "programVariables.hpp" // Include program variables module globally

#define WT_C_LINKAGE \
    extern "C" // Force C linkage
#define WT_PURE_VIRTUAL \
    0 // Pure virtual marker
