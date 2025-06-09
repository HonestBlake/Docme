// #file: source/debugging.cpp, Module source file

#include "header/debugging.hpp" // #include: Module header file

namespace docme::debugging{ // #scope: docme::debugging

// #scope: debugTools, function definitions

    // #func: trace(std::source_location&&), Function
    void debugTools::trace(std::source_location&& p_location){
        btr::Logger::get<DocmeTracer>().log<btr::Level::TRACE>("", std::forward<std::source_location>(p_location));
    } // #end: trace(std::source_location&&)

// #end: debugTools

// ----------------------------------------------------------------------------------------------------------------------------------------

// #scope: DocmeTracer, Method definitions

// #div: Public factory methods

    // #func: DocmeTracer(), constructor
    DocmeTracer::DocmeTracer(): Logger(logger::TRACER_NAME, logger::TRACER_FORMAT){} // #end: DocmeTracer()

// #div: Private methods

    // #func: formatLocation(const btr::Level, const std::source_location&), Const override method
    std::string DocmeTracer::formatLocation(const btr::Level p_logLevel, const std::source_location& p_location)const{
        return getLogColor(p_logLevel) + p_location.function_name() + btr::log::SPACE + btr::ansii::RESET;
    } // #end: formatLocation(const btr::Level, const std::source_location&)

// #end: DocmeTracer

// ----------------------------------------------------------------------------------------------------------------------------------------

// #scope: DocmeDebug, Method definitions

// #div: Public factory methods

    // #func: DocmeDebug(), Constructor
    DocmeDebug::DocmeDebug(): Logger(logger::DEBUG_NAME){} // #end: DocmeDebug()

// #div: Private methods

    // #func: sendLog(std::string&&), Const override method
    const btr::Logger& DocmeDebug::sendLog(std::string&& p_log)const{
        btr::LogStack::get<btr::TerminateFlush>().pushLog(std::forward<std::string>(p_log));
        return *this;
    } // #end: sendLog(std::string&&)

// #end: DocmeDebug

} // namespace autoDoc::debugging