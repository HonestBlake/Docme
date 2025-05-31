// #file: debugging.hpp

#pragma once

#include "docme.hpp" // project general header

namespace worTech::docme::debugging{

    // #namespace: errorMessages, variable namespace
    namespace errorMessages{
        inline const std::string UNNAMED_ERROR = "An unnamed error occurred";
        inline const std::string UNNAMED_WARNING = "An unnamed warning occurred";
        inline const std::string NO_COMMAND_LINE_ARGUMENTS = "No command line arguments provided";
        inline const std::string ARGUMENT_HAS_NO_FLAG = "Command line argument has no flag: {}";
        inline const std::string UNRECOGNIZED_DOC_PACKET = "Unrecognized doc packet: {}";
        inline const std::string COULD_NOT_FIND_CONFIG_FILE = "Could not locate config file: {}";
        inline const std::string INVALID_CONFIG_FILE_TYPE = "Provided config file is not a valid {} file: {}";
        inline const std::string COULD_NOT_FIND_OUTPUT_DIRECTORY = "Could not locate output directory: {}";
        inline const std::string INVALID_OUTPUT_DIRECTORY = "Provided output directory is not a valid directory: {}";
        inline const std::string INVALID_SOURCE_FILE_TYPE = "Provided source file is not a valid file type from given doc packets: {}";
        inline const std::string COULD_NOT_FIND_SOURCE = "Could not locate provided source path: {}";
        inline const std::string COULD_NOT_FIND_IGNORE = "Could not locate provided ignore path: {}";
        inline const std::string COULD_NOT_FIND_ROOT_DIRECTORY = "Could not locate provided root directory: {}";
        inline const std::string INVALID_ROOT_DIRECTORY = "Provided root directory is not a valid directory: {}";
        inline const std::string FAILED_TO_OPEN_FILE = "Failed to open file: {}";
        inline const std::string FAILED_TO_PARSE_JSON = "Failed to parse json file: {}";
        inline const std::string COULD_NOT_FIND_JSON_KEY = "Could not find json key: {}, in file: {}";
        inline const std::string JSON_TYPE_ERROR_STRING = "Json type error, expected string from key: {}, in file: {}";
        inline const std::string JSON_TYPE_ERROR_ARRAY = "Json type error, expected array from key: {}, in file: {}";
        inline const std::string ARGS_WITH_SPECIAL_FLAG = "Cannot use any other arguments or flags when using special flag: {}";
        inline const std::string NO_SOURCE_FILES_PROVIDED = "No source files provided";
        inline const std::string FAILED_TO_LOAD_DLL = "Failed to load dynamic link library: {}";
        inline const std::string NULL_COMMAND_LINE_ARGUMENTS = "Command line arguments cannot be null";
        inline const std::string FAILED_TO_PARSE_CONFIG_FILE = "Failed to parse config file: {}";
    }
    // #namespace: debugTools, function namespace
    namespace debugTools{
        template<typename... T_args> std::string message(const std::string& p_message, T_args... p_args)noexcept;
        template<typename... T_args> void warn(const std::string& p_warning = error::UNNAMED_WARNING, T_args... p_args)noexcept;
        template<typename... T_args> void error(const std::string& p_error = error::UNNAMED_ERROR, T_args... p_args)noexcept;
        void trace(std::source_location&& p_location = std::source_location::current())noexcept;
    }
    // #namespace: loggerValues, variable namespace
    namespace loggerValues{
        const std::string TRACER_NAME = "AutoDoc Tracer";
        const std::string DEBUG_NAME = "AutoDoc";
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