// #file: header/debugging.hpp, Module header file

#pragma once // Include guard

#include "docme.hpp" // Project header file

namespace docme::debugging{ // #scope: docme::debugging

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
        inline const std::string COMMAND_LINE_NOT_INITIALIZED_WITH_ARGS = "Command line parser has not been initialized with necessary parameters";
        inline const std::string PARSER_NOT_INITIALIZED_WITH_ARGS = "Program parser has not been initialized with necessary parameters";
    } // #end: errorMessages

    // #namespace: debugTools, function namespace
    namespace debugTools{
        template<typename... T_args> std::string message(const std::string& p_message, T_args... p_args);
        template<typename... T_args> void warn(const std::string& p_warning = error::UNNAMED_WARNING, T_args... p_args);
        template<typename... T_args> void error(const std::string& p_error = error::UNNAMED_ERROR, T_args... p_args);
        void trace(std::source_location&& p_location = std::source_location::current());
    } // #end: debugTools

    // #namespace: loggerValues, variable namespace
    namespace loggerValues{
        const std::string TRACER_NAME = "DocmeTrace";
        const std::string DEBUG_NAME = "Docme";
        const std::array<btr::Format, 5> TRACER_FORMAT = {
            btr::Format::LOGGER, 
            btr::Format::LEVEL, 
            btr::Format::LOCATION, 
            btr::Format::TIME, 
            btr::Format::MESSAGE
        };
    } // #end: loggerValues

    // #class: DocmeTracer, singleton class 
    class DocmeTracer: public btr::Logger{
    public:
        DocmeTracer();
    private:
        std::string formatLocation(const btr::Level p_logLevel, const std::source_location& p_location)const override;
    }; // #end: DocmeTracer
    
    // #class: DocmeDebug, singleton class
    class DocmeDebug: public btr::Logger{
    public: 
        DocmeDebug();
    private:
        const Logger& sendLog(std::string&& p_log)const override;
    }; // #end: DocmeDebug

} // #end: autoDoc::debugging

#include "source/debugging.tpp" // #include: source/debugging.tpp, template source file