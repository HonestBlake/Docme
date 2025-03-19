#pragma once

// #file: formats.hpp, header file
// #info: defines variable constants for log formatting
// #attach: betterLogger.hpp, internal dependency

// project include
#include "betterLogger.hpp"

namespace worTech::betterLogger::formats{

    // #namespace: ansiiColorCodes(ansii), variable namespace
    // #scope: loggers, component namespace
    // #info: holds ansii color codes for different char colors
    namespace ansiiColorCodes{
        const std::string RESET = "\033[0m";
        const std::string BLACK = "\033[30m";
        const std::string RED = "\033[31m";
        const std::string GREEN = "\033[32m";
        const std::string YELLOW = "\033[33m";
        const std::string BLUE = "\033[34m";
        const std::string MAGENTA = "\033[35m";
        const std::string CYAN = "\033[36m";
        const std::string WHITE = "\033[37m";
        const std::string BOLD_BLACK = "\033[1;30m";
        const std::string BOLD_RED = "\033[1;31m";
        const std::string BOLD_GREEN = "\033[1;32m";
        const std::string BOLD_YELLOW = "\033[1;33m";
        const std::string BOLD_BLUE = "\033[1;34m";
        const std::string BOLD_MAGENTA = "\033[1;35m";
        const std::string BOLD_CYAN = "\033[1;36m";
        const std::string BOLD_WHITE = "\033[1;37m";
    }
    // #enum: LogLevel(Level), uint8_t enum class
    // #scope: loggers, component namespace
    // #info: holds enumerated log levels
    enum class LogLevel: uint8_t{
        NONE,
        INFO,
        TRACE,
        WARNING,
        ERROR,
        CRITICAL
    }; 
    // #enum: FormatType(Format), uint8_t enum class
    // #scope: loggers, component namespace
    // #info: holds enumerated log formatting types
    enum class FormatType: uint8_t{
        LOGGER,
        LEVEL,
        TIME,
        MESSAGE,
        LOCATION
    };
    // #namespace: logFormatting(log), variable namespace
    // #scope: loggers, component namespace
    // #info: holds log formatting values and maps
    namespace logFormatting{
        const std::string LOGGER_BEGIN = "[";
        const std::string LOGGER_END = "]";
        const std::string TIME_BEGIN = "(";
        const std::string TIME_END = ")";
        const std::string TIME_SPACE = ":";
        const std::string LEVEL_END = ":";
        const std::string LINE_BEGIN = "line";
        const std::string SPACE = " ";
        const size_t FORMAT_SIZE = 5;
        const std::unordered_map<Level, std::string> LEVEL_NAME = {
            {Level::NONE, ""},
            {Level::INFO, "Info"},
            {Level::TRACE, "Trace"},
            {Level::WARNING, "Warning"},
            {Level::ERROR, "Error"},
            {Level::CRITICAL, "Critical"}
        };
        const std::unordered_map<Level, std::string> LEVEL_COLOR = {
            {Level::NONE, ansii::WHITE},
            {Level::INFO, ansii::CYAN},
            {Level::TRACE, ansii::GREEN},
            {Level::WARNING, ansii::YELLOW},
            {Level::ERROR, ansii::RED},
            {Level::CRITICAL, ansii::MAGENTA}
        };
        const std::unordered_map<Level, std::string> LEVEL_COLOR_BOLD = {
            {Level::NONE, ansii::BOLD_WHITE},
            {Level::INFO, ansii::BOLD_CYAN},
            {Level::TRACE, ansii::BOLD_GREEN},
            {Level::WARNING, ansii::BOLD_YELLOW},
            {Level::ERROR, ansii::BOLD_RED},
            {Level::CRITICAL, ansii::BOLD_MAGENTA}
        };
    }
    
} // namespace worTech::betterLogger::formats