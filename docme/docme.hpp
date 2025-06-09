// #file: docme.hpp, Project header file

#pragma once // Include guard

#include "header/standardLibs.hpp" // #include: header/standardLibs.hpp, Standard library headers
#include "header/externalLibs.hpp" // #include: header/externalLibs.hpp, External library headers
#include "header/cppTools.hpp" // #include: header/cppTools.hpp, C++ dev tools

// #namespace: docme, project namespace
namespace docme{

    // #namespace: programVariables, inline module namespace
    inline namespace programVariables{
        namespace programConstants{}
        namespace program = programConstants; // alias programConstants to program
        namespace programStates{}
        namespace state = programStates; // alias programStates to state
    } // #end: programVariables

    // #namespace: debugging, inline module namespace
    inline namespace debugging{
        namespace errorMessages{}
        namespace error = errorMessages; // alias errorMessages to error
        namespace debugTools{}
        namespace debug = debugTools; // alias debugTools to debug
        namespace loggerValues{}
        namespace logger = loggerValues; // alias loggerValues to logger
        class DocmeTracer;
        class DocmeDebug;
    } // #end: debugging

    // #namespace: restrictedTypes, inline module namespace
    inline namespace restrictedTypes{

    } // #end: restrictedTypes

    // #namespace: jsonTools, inline module namespace
    inline namespace jsonTools{
        class Json;
    } // #end: jsonTools

    // #namespace: engine, inline package namespace
    inline namespace engine{
        inline namespace packets{}
        inline namespace nodes{}
        inline namespace nodeManagers{}
        inline namespace parser{}
        inline namespace generator{}
        inline namespace docmeEngine{}
        inline namespace commandLine{}
    } // #end: engine

    // #namespace: cdoc, inline package namespace
    inline namespace cdoc{

    } // #end: cdoc

} // #end: docme

// Globally included modules
#include "header/programVariables.hpp" // #include: header/programVariables.hpp, Module header file
#include "header/debugging.hpp" // #include: header/debugging.hpp, Module header file

