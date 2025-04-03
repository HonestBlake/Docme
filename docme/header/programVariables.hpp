// #file: programVariables.hpp, header file

#pragma once

namespace worTech::docme::programVariables{
    
    // #namespace: programStates(state), inline variable namespace
    namespace programStates{
        // set TRACING when macro defined 
        #ifdef WT_AUTODOC_DEBUG_TRACING
        constexpr bool TRACING = true;
        #else
        constexpr bool TRACING = false;
        #endif
        // set VERVOSE_TRACING when macro defined
        #ifdef WT_AUTODOC_DEBUG_VERVOSE_TRACING
        constexpr bool VERVOSE_TRACING = true;
        #else
        constexpr bool VERVOSE_TRACING = false;
        #endif
        // set WARNING_IS_ERROR when macro defined
        #ifdef WT_AUTODOC_DEBUG_WARNING_IS_ERROR
        constexpr bool WARNING_IS_ERROR = true;
        #else
        constexpr bool WARNING_IS_ERROR = false;
        #endif
    }

} // namespace worTech::docme::programVariables