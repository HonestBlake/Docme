// #file: debugging.hpp

#pragma once

#include "docme.hpp" // project general header

namespace worTech::docme::debugging{

    // #namespace: errorMessages, variable namespace
    namespace errorMessages{
        const std::string NO_COMMAND_LINE_ARGUMENTS = "No command line arguments provided";
        const std::string UNRECONIZED_COMMAND_LINE_ARGUMENT = "Unreconized command line argument: {}";
        const std::string UNRECONIZED_DOC_PACKET = "Unreconized doc packet: {}";
        const std::string COULD_NOT_FIND_CONFIG_FILE = "Could not locate config file: {}";
        const std::string INVALID_CONFIG_FILE_TYPE = "Provided config file is not a valid {} file: {}";
        const std::string COULD_NOT_FIND_OUTPUT_DIRECTORY = "Could not locate output directory: {}";
        const std::string INVALID_OUTPUT_DIRECTORY = "Provided output directory is not a valid directory: {}";
        const std::string INVALID_SOURCE_FILE_TYPE = "Provided source file is not a valid file type from given doc packets: {}";
        const std::string COULD_NOT_FIND_SOURCE = "Could not locate provided source path: {}";
        const std::string COULD_NOT_FIND_IGNORE = "Could not locate provided ignore path: {}";
        const std::string COULD_NOT_FIND_ROOT_DIRECTORY = "Could not locate provided root directory: {}";
        const std::string INVALID_ROOT_DIRECTORY = "Provided root directory is not a valid directory: {}";
        const std::string FAILED_TO_OPEN_FILE = "Failed to open file: {}";
        const std::string FAILED_TO_PARSE_JSON = "Failed to parse json file: {}";
        const std::string COULD_NOT_FIND_JSON_KEY = "Could not find json key: {}, in file: {}";
        const std::string JSON_TYPE_ERROR_STRING = "Json type error, expected string from key: {}, in file: {}";
        const std::string JSON_TYPE_ERROR_ARRAY = "Json type error, expected array from key: {}, in file: {}";
        const std::string ARGS_WITH_SPECIAL_FLAG_CALL = "Cannot call a command line special flag with any arguments or flags";
        const std::string NO_ARGS_GIVEN_TO_FLAG = "No arguments given to command line flag: {}";
    }
    // #namespace: debugTools, function namespace
    namespace debugTools{
        template<typename... T_args> std::string message(const std::string& p_message, T_args... p_args)noexcept;
        template<typename... T_args> void warn(const std::string& p_warning, T_args... p_args)noexcept;
        template<typename... T_args> void error(const std::string& p_error, T_args... p_args)noexcept;
        void trace(std::source_location&& p_location)noexcept;
    }
    // #namespace: loggerValues, variable namespace
    namespace loggerValues{
        const std::string TRACER_NAME = "AutoDoc Tracer";
        const std::string DEBUG_NAME = "AutoDoc Debug";
        const std::array<btr::Format, 5> TRACER_FORMAT = {
            btr::Format::LOGGER, 
            btr::Format::LEVEL, 
            btr::Format::LOCATION, 
            btr::Format::TIME, 
            btr::Format::MESSAGE
        };
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

#include "source/debugging.tpp" // template function definitions