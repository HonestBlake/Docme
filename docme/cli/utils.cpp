// #FILE: utils.cpp, Component Source File
// #BRIEF: Source file for utils component

module;

#include "cli.hpp" // #INCLUDE: cli.hpp, Package wide header
#include "config/config.hpp"
#include <filesystem>

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

    // #FUNC: print(const std::string_view), Function
    // #BRIEF: Prints the given message to the console
    // #PARAM: const std::string_view p_message, Message to print
    void util::print(const std::string_view p_message){
        logger.log(std::string(p_message));
    } // #END: print(const std::string_view)

    // #FUNC: printRunnningCommand(const std::string_view, const std::string_view, const std::optional<std_fs::path>&), Function
    // #BRIEF: Prints the build header to the console with the given config path
    // #PARAM: const std::string_view p_command, Command being run
    // #PARAM: const std::string_view p_context, Context of command being run
    // #PARAM: const std::optional<std_fs::path>& p_config, Config path being used for command
    void util::printRunningCommand(const std::string_view p_command, const std::string_view p_context, const std::optional<std_fs::path>& p_config){
        logger.log("Running {} command {}: {}", p_command, p_context, p_config? (std_fs::is_regular_file(*p_config)? p_config->string(): (*p_config / config::DEFAULT_CONFIG_FILE_NAME).string()): config::File::DEFAULT_CONFIG_FILE.string());
    } // #END: printRunnningCommand(const std::string_view, const std::string_view, const std::optional<std_fs::path>&)


// #END: utils

} // #END: docme::cli
