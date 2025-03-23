// #file: debugging.cpp, source file

#include "debugging.hpp"

namespace worTech::autoDoc::debugging{

// debugTools, function definitions

    // #func: warn(const std::string&, std::source_location&&), void noexcept function
    void debugTools::warn(const std::string& p_warning)noexcept{
        if constexpr(state::WARNING_IS_ERROR){
            btr::Logger::get<AutoDocDebug>().log<btr::Level::WARNING>(p_warning);
        }else{
            btr::Logger::get<AutoDocDebug>().log<btr::Level::ERROR>(p_warning);
            std::exit(EXIT_FAILURE);
        }
    }
    // #func: trace(std::source_location&&), public noexcept function
    void debugTools::trace(std::source_location&& p_location)noexcept{
        btr::Logger::get<AutoDocTracer>().log<btr::Level::TRACE>("", p_location);
    }

// --------------------------------------------------------------------------------------------------------------------------------

// AutoDocTracer, method definitions

// public factory methods

    // #func: AutoDocTracer(), public constructor
    AutoDocTracer::AutoDocTracer(): Logger("CDoc Tracer", {btr::Format::LOGGER, btr::Format::LEVEL, btr::Format::LOCATION, btr::Format::TIME, btr::Format::MESSAGE}){}

// private methods

    // #func: formatLocation(const btr::Level, const std::source_location&), private const override method
    std::string AutoDocTracer::formatLocation(const btr::Level p_logLevel, const std::source_location& p_location)const{
        return getLogColor(p_logLevel) + p_location.function_name() + btr::log::SPACE + btr::ansii::RESET;
    }

// --------------------------------------------------------------------------------------------------------------------------------

// AutoDocError, method definitions

// public factory methods

    // #func: AutoDocError(), public constructor
    AutoDocDebug::AutoDocDebug(): Logger("AutoDoc Debug"){}

// private methods

    // #func: sendLog(std::string&&), private const override method
    const btr::Logger& AutoDocDebug::sendLog(std::string&& p_log)const{
        btr::LogStack::get<btr::TerminateFlush>().pushLog(std::forward<std::string>(p_log));
        return *this;
    }

} // namespace worTech::autoDoc::debugging