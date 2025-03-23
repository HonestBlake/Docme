// #file: debugging.hpp

#pragma once

#include "genorator.hpp" // package general header

namespace worTech::autoDoc::debugging{

    // #namepace: debugStates, variable namespace
    namespace debugStates{
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
    // #namespace: errorMessages, variable namespace
    namespace errorMessages{
        constexpr std::string NO_COMMAND_LINE_ARGUMENTS = "No command line arguments provided";
    }
    // #namespace: debugTools, function namespace
    namespace debugTools{
        void warn(const std::string& p_warning)noexcept;
        void trace(std::source_location&& p_location)noexcept;
    }
    // #class: AutoDocTracer, singleton class 
    class AutoDocTracer: public btr::Logger{
    public:
        AutoDocTracer();
    private:
        std::string formatLocation(const btr::Level p_logLevel, const std::source_location& p_location)const override;
    };
    // #class: AutoDocError, singleton class
    class AutoDocDebug: public btr::Logger{
    public: 
        AutoDocDebug();
    private:
        const Logger& sendLog(std::string&& p_log)const override;
    };

} // namespace worTech::autoDoc::debugging
