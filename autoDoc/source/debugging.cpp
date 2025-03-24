// #file: debugging.cpp, source file

#include "debugging.hpp"

namespace worTech::autoDoc::debugging{

// debugTools, function definitions

    // #func: warn(const std::string&, std::source_location&&), noexcept template function

    // #template: typename... T_args, variadic template for formating arguments
    // #param: const std::string& p_warning, warning message
    // #param: T_args... p_args, formating arguments
    template<typename... T_args> void debugTools::warn(const std::string& p_warning, T_args... p_args)noexcept{
        if constexpr(state::WARNING_IS_ERROR){
            btr::Logger::get<AutoDocDebug>().log<btr::Level::WARNING>(std::vformat(p_warning, std::make_format_args(p_args...)));
        }else{
            btr::Logger::get<AutoDocDebug>().log<btr::Level::ERROR>(std::vformat(p_warning, std::make_format_args(p_args...)));
            std::exit(EXIT_FAILURE);
        }
    }
    // #func: error(const std::string&), noexcept template function

    // #template: typename... T_args, variadic template for formating arguments
    // #param: const std::string& p_error, error message
    // #param: T_args... p_args, formating arguments
    template<typename... T_args> void debugTools::error(const std::string& p_error, T_args... p_args)noexcept{
        btr::Logger::get<AutoDocDebug>().log<btr::Level::ERROR>(std::vformat(p_error, std::make_format_args(p_args...)));
        std::exit(EXIT_FAILURE);
    }
    // #func: trace(std::source_location&&), noexcept function

    // #param: std::source_location&& p_location, call location
    void debugTools::trace(std::source_location&& p_location)noexcept{
        btr::Logger::get<AutoDocTracer>().log<btr::Level::TRACE>("", std::forward<std::source_location>(p_location));
    }

// --------------------------------------------------------------------------------------------------------------------------------

// AutoDocTracer, method definitions

// public factory methods

    // #func: AutoDocTracer(), public constructor
    AutoDocTracer::AutoDocTracer(): Logger(logger::TRACER_NAME, logger::TRACER_FORMAT){}

// private methods

    // #func: formatLocation(const btr::Level, const std::source_location&), private const override method

    // #param: const btr::Level p_logLevel, log level
    // #param: const std::source_location& p_location, call location
    // #return: std::string, formated location
    std::string AutoDocTracer::formatLocation(const btr::Level p_logLevel, const std::source_location& p_location)const{
        return getLogColor(p_logLevel) + p_location.function_name() + btr::log::SPACE + btr::ansii::RESET;
    }

// --------------------------------------------------------------------------------------------------------------------------------

// AutoDocError, method definitions

// public factory methods

    // #func: AutoDocError(), public constructor
    AutoDocDebug::AutoDocDebug(): Logger(logger::DEBUG_NAME){}

// private methods

    // #func: sendLog(std::string&&), private const override method

    // #param: std::string&& p_log, log message
    // #return: const Logger&, reference to current instance
    const btr::Logger& AutoDocDebug::sendLog(std::string&& p_log)const{
        btr::LogStack::get<btr::TerminateFlush>().pushLog(std::forward<std::string>(p_log));
        return *this;
    }

} // namespace worTech::autoDoc::debugging