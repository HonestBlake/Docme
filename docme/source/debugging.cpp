// #file: debugging.cpp, source file

#include "debugging.hpp"

namespace worTech::docme::debugging{

// debugTools, function definitions

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
    // #return: std::string, formatted location
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