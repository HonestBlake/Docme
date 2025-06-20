// #file: header/programVariables.hpp, Module header file

#pragma once // Include guard

#include "docme.hpp" // #include: Project header file

namespace docme::programVariables{ // #scope: docme::programVariables
    
    // #namespace: programStates, inline variable namespace
    namespace programStates{
        // set TRACING when macro defined 
        #ifdef WT_DOCME_DEBUG_TRACING
        constexpr bool TRACING = true;
        #else
        constexpr bool TRACING = false;
        #endif
        // set VERBOSE_TRACING when macro defined
        #ifdef WT_DOCME_DEBUG_VERVOSE_TRACING
        constexpr bool VERBOSE_TRACING = true;
        #else
        constexpr bool VERBOSE_TRACING = false;
        #endif
        // set WARNING_IS_ERROR when macro defined
        #ifdef WT_DOCME_DEBUG_WARNING_IS_ERROR
        constexpr bool WARNING_IS_ERROR = true;
        #else
        constexpr bool WARNING_IS_ERROR = false;
        #endif
        // set DEBUGGING when macro defined
        #ifdef WT_DOCME_DEBUGGING
        constexpr bool DEBUGGING = true;
        #else
        constexpr bool DEBUGGING = false;
        #endif
    } // #end: programStates

} // #end: docme::programVariables