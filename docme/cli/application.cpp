// #FILE: configFile.cpp, Component Source File
// #BRIEF: Source file for configFile component

module;

#include "cli.hpp" // #INCLUDE: cli.hpp, Package wide header

module docme.cli; // #IMPLEMENTS: docme.cli:application
import :application; 

import docme.core; // #IMPORT: docme.core, Internal core library
import docme.engine; // #IMPORT: docme.engine, 

namespace docme::cli{ // #SCOPE: docme::engine

    // #FUNC: optionalStringConverter(const std::string&), Function
    // #BRIEF: String to optional string converter for simple cli
    // #PARAM: const std::string& p_string, String to convert
    // #RETURN: simpleCli::Result<std::optional<std::string>>, Converted type result type
    simpleCli::Result<std::optional<std::string>> optionalStringConverter(const std::string& p_string){
        return std::optional<std::string>(p_string);
    } // #END: optionalStringConverter(const std::string&)


// ------------------------------------------------------------------------------
//                               class Application
// ------------------------------------------------------------------------------

// #SCOPE: Application

// #DIV: Public

// ---- Public Factory Methods ----

    // #METHOD: Application(int, char**), Constructor
    // #BRIEF: Initialize application with command line args
    Application::Application(int p_argc, char** p_argv): m_args(p_argv, p_argv + p_argc){
        if(simpleCli::Result<> result = m_parser.addPositional(m_positionals); !result){
            logger.error(result.error().message());
        }
        if(simpleCli::Result<> result = m_parser.addOption<std::optional<std::string>>(CONFIG_TAGS, m_config, &optionalStringConverter); !result){
            logger.error(result.error().message());
        }
        if(simpleCli::Result<> result = m_parser.addExclusiveCommand(INIT_COMMAND, std::bind(&Application::init, this)); !result){
            logger.error(result.error().message());
        }
        if(simpleCli::Result<> result = m_parser.addExclusiveCommand(BUILD_COMMAND, std::bind(&Application::build, this)); !result){
            logger.error(result.error().message());
        }
        if(simpleCli::Result<> result = m_parser.addExclusiveCommand(RENDER_COMMAND, [](){logger.debug("render called");}); !result){
            logger.error(result.error().message());
        }
        if(simpleCli::Result<> result = m_parser.addExclusiveCommand(GENERATE_COMMAND, [](){logger.debug("generate called");}); !result){
            logger.error(result.error().message());
        }
        if(simpleCli::Result<> result = m_parser.addExclusiveCommand(CHECK_COMMAND, [](){logger.debug("check called");}); !result){
            logger.error(result.error().message());
        }
        if(simpleCli::Result<> result = m_parser.addExclusiveFlag(HELP_FLAGS, [](){logger.debug("help called");}); !result){
            logger.error(result.error().message());
        }
        if(simpleCli::Result<> result = m_parser.addExclusiveFlag(VERSION_FLAGS, [](){logger.debug("version called");}); !result){
            logger.error(result.error().message());
        }
    } // #END: Application(int, char**)


// ---- Public Methods ----

    // #METHOD: run(), Instance Method
    // #BRIEF: Begin CLI application.
    void Application::run(){
        if constexpr(DEBUGGING){
            logger.debug("Routing to Docme CLI");
        }
        if(simpleCli::Result<> result = m_parser.parse(m_args); !result){
            logger.error(result.error().message());
        }
    } // #END: run()


// #DIV: Private

// ---- Private Methods ----

    // #METHOD: init(), Instance Method
    // #BRIEF: Call and handles engine init command.
    void Application::init(){
        std::optional<std_fs::path> configFile;

        Result<> result = engine::Command::init(m_config);
 
        // Log warnings
        if(result.hasWarnings()){
            for(const core::Warn& warning: result.warnings()){
                logger.warn(warning.message());
            }
        }

        // Log error
        if(!result){
            logger.error(result.error().message());
        }
    } // #END: init()

    // #METHOD: build(), Instance Method
    // #BRIEF: Call and handles engine build command.
    void Application::build(){
        Result<> result = engine::Command::build(m_config);

        // Log warnings
        if(result.hasWarnings()){
            for(const core::Warn& warning: result.warnings()){
                logger.warn(warning.message());
            }
        }

        // Log error
        if(!result){
            logger.error(result.error().message());
        }
    } // #END: build()

    // #METHOD: getConfigOrPositional(), Const Instance Method
    // #BRIEF: Get config file path from config option or positional argument.
    // #RETURN: Result<std::optional<std_fs::path>>, Optional config file path result type
    Result<std::optional<std::string>> Application::getConfigOrPositional()const{
        if(m_config){
            if(!m_positionals.empty()) return Error(Error::DOCME_E400); // Positional arguments provided but aren't being used
            return m_config;
        }else{
            if(m_positionals.size() > 1) return Error(Error::DOCME_E401); // Too many positional arguments provided
            if(!m_positionals.empty()) return std::optional<std::string>{m_positionals[0]};
            return std::optional<std::string>{std::nullopt};
        }
    }


// ----------------------------------------------------------------------------
//                              class Application::Error
// ----------------------------------------------------------------------------

// #SCOPE: Error

// #DIV: Public

// ---- Public Factory Methods ----

    // #METHOD: Error(const Code), Constructor
    // #BRIEF: Constructs Error from an error code
    // #PARAM: const Code p_code, Error code for error
    Application::Error::Error(const Code p_code): docme::core::Error(){
        code = p_code;
        if(auto it = ERROR_MESSAGES.find(code); it != ERROR_MESSAGES.end()){
            body = it->second;
        }else{
            body = UNKNOWN_ERROR_MESSAGE;
        }
    } // #END: Error(const Code)

    // #METHOD: Error<T_ContextArgs>(const Code, const std::string&), Constructor
    // #BRIEF: Constructs Error from an error code and context args
    // #TEMPLATE: class... T_ContextArgs, context arguments parameter pack
    // #PARAM: const Code p_code, Error code for error
    // #PARAM: const T_ContextArgs&... p_contextArgs, Context arguments parameter pack
    template<class... T_ContextArgs> Application::Error::Error(const Code p_code, const T_ContextArgs&... p_contextArgs): docme::core::Error(){
        code = p_code;
        if(auto it = ERROR_MESSAGES.find(code); it != ERROR_MESSAGES.end()){
            body = std::vformat(it->second, std::make_format_args(p_contextArgs...));
        }else{
            body = UNKNOWN_ERROR_MESSAGE;
        }
    } // #END: Error(const Code)


// #END: Error

// ----------------------------------------------------------------------------
//                               class Application::Warn
// ----------------------------------------------------------------------------

// #SCOPE: Warn

// #DIV: Public

// ---- Public Factory Methods ----

    // #METHOD: Warn(const Code), Constructor
    // #BRIEF: Constructs Warn from a warn code
    // #PARAM: const Code p_code, Warn code for warn
    Application::Warn::Warn(const Code p_code): docme::core::Warn(){
        code = p_code;
        if(auto it = WARN_MESSAGES.find(code); it != WARN_MESSAGES.end()){
            body = it->second;
        }else{
            body = UNKNOWN_WARNING_MESSAGE;
        }
    } // #END: Warn(const Code)

    // #METHOD: Warn<T_ContextArgs>(const Code, const std::string&), Constructor
    // #BRIEF: Constructs Warn from a warn code and context args
    // #TEMPLATE: class... T_ContextArgs, context arguments parameter pack
    // #PARAM: const Code p_code, Warn code for warn
    // #PARAM: const T_ContextArgs&... p_contextArgs, Context arguments parameter pack
    template<class... T_ContextArgs> Application::Warn::Warn(const Code p_code, const T_ContextArgs&... p_contextArgs): docme::core::Warn(){
        code = p_code;
        if(auto it = WARN_MESSAGES.find(code); it != WARN_MESSAGES.end()){
            body = std::vformat(it->second, std::make_format_args(p_contextArgs...));
        }else{
            body = UNKNOWN_WARNING_MESSAGE;
        }
    } // #END: Warn(const Code)


// #END: Warn

// #END: Application

} // #END: cli
