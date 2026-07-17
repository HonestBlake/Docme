// #FILE: utils.cpp, Component Source File
// #BRIEF: Source file for utils component

module;

#include "cli.hpp" // #INCLUDE: cli.hpp, Package wide header

module docme.cli; // #IMPLEMENTS: docme.cli:utils
import :utils;

namespace docme::cli{ // #SCOPE: docme::cli

// ------------------------------------------------------------------------------
//                                namespace util
// ------------------------------------------------------------------------------

// #SCOPE: utils

    // #FUNC: optionalStringConverter(const std::string&), Function
    // #BRIEF: String to optional string converter for simple cli
    // #PARAM: const std::string& p_string, String to convert
    // #RETURN: simpleCli::Result<std::optional<std::string>>, Converted type result type
    simpleCli::Result<std::optional<std::string>> util::optionalStringConverter(const std::string& p_string){
        return std::optional<std::string>(p_string);
    } // #END: optionalStringConverter(const std::string&)

    // #FUNC: optionalPathConverter(const std::string&), Function
    // #BRIEF: String to optional normalized path converter for simple cli
    // #PARAM: const std::string& p_string, String to convert
    // #RETURN: simpleCli::Result<std::optional<std_fs::path>>, Converted type result type
    simpleCli::Result<std::optional<std_fs::path>> util::optionalPathConverter(const std::string& p_string){
        std_fs::path path = p_string;
        core::util::normalizePath(path, std_fs::current_path());
        return std::optional<std_fs::path>(std::move(path));
    } // #END: optionalPathConverter(const std::string&)

    // #FUNC: pathConverter(const std::string&), Function
    // #BRIEF: String to optional path converter for simple cli
    // #PARAM: const std::string& p_string, String to convert   
    // #RETURN: simpleCli::Result<std::optional<std_fs::path>>, Converted type result type
    simpleCli::Result<std_fs::path> util::pathConverter(const std::string& p_string){
        std_fs::path path = p_string;
        core::util::normalizePath(path, std_fs::current_path());
        return path;
    } // #END: pathConverter(const std::string&)

    // #FUNC: handleWarnings(const std::vector<core::Warning>&), Function
    // #BRIEF: Handle warnings by logging them to logger
    // #PARAM: const std::vector<core::Warning>& p_warnings, Warnings to handle
    void util::handleWarnings(const std::vector<core::Warning>& p_warnings){
        for(const core::Warning& warning: p_warnings){
            logger.warn(warning.message());
        }
    } // #END: handleWarnings(const std::vector<core::Warning>&)

    // #FUNC: handleError(const core::Error&), Function
    // #BRIEF: Handle error by logging it to logger and exiting with failure
    // #PARAM: const core::Error& p_error, Error to handle
    void util::handleError(const core::Error& p_error){
        logger.error(p_error.message());
        std::exit(EXIT_FAILURE);
    } // #END: handleError(const core::Error&)

    // #FUNC: printTimer(const std::string_view, const core::Timer&), Function
    // #BRIEF: Prints the time from the given timer with the given message
    // #PARAM: const std::string_view p_message, Message to print with time
    // #PARAM: const core::Timer& p_timer, Timer to print time from
    void util::printTimer(const std::string_view p_message, const core::Timer& p_timer){
        const std::int64_t time = p_timer.time().milliseconds();
        const std::int64_t minutes = time / 60'000;
        const std::int64_t seconds = time / 1'000 % 60;
        const std::int64_t milliseconds = time % 1'000;
        logger.log(std::string(p_message), p_timer.name(), std::format("{:02}:{:02}:{:03}", minutes, seconds, milliseconds));
    } // #END: printTimer(const core::Timer&)


// #END: utils

} // #END: docme::cli
