// #FILE: commands.cpp, Component Source File
// #BRIEF: Source file for commands component

module;

#include "engine.hpp" // #INCLUDE: cli.hpp, Package wide header

module docme.engine; // #IMPLEMENTS: docme.engine:commands
import :commands; 

import docme.core; // #IMPORT: docme.core, Internal core library

namespace docme::engine{ // #SCOPE: docme::engine

// ------------------------------------------------------------------------------
//                                 class Command
// ------------------------------------------------------------------------------

// #SCOPE: Command

// #DIV: Public

// ---- Public Static Methods ----

    // #METHOD: init(const std_fs::path&), Static Method
    // #BRIEF: Create a template config file at dir
    // #NOTE: Returns error codes: DOCME_E200, DOCME_E201, DOCME_E202, DOCME_E203.
    // #NOTE: Returns warning codes: DOCME_W201
    // #PARAM: const std::optional<std_fs::path>& p_config, optional path to create template
    // #RETURN: Result<>, Optional error state
    Result<> Command::init(const std::optional<std_fs::path>& p_config){
        if constexpr(DEBUGGING){
            logger.debug("Called init command");
        }

        if(ConfigFile::foundDefault()){
            if(p_config){
                Warnings::add(Warn(Warn::DOCME_W201, p_config->string())); // A second config file will be created
            }else return Error(Error::DOCME_E207); // Default config file already exists
        }

        if(Result<> result = p_config? ConfigFile::create(*p_config): ConfigFile::create(); !result) return result.failure();

        return {};
    } // #END: init()

    // #METHOD: build(), Static Method
    // #BRIEF: 
    // #NOTE: Retruns error codes: DOCME_E202, DOCME_E204, DOCME_E205, DOCME_E206
    // #NOTE: Returns warning codes: DOCME_W200
    // #PARAM: const std::optional<std_fs::path>& p_config, optional path to config file
    // #RETURN: Result<>, Optional error state
    Result<> Command::build(const std::optional<std_fs::path>& p_config){
        if constexpr(DEBUGGING){
            logger.debug("Called build command");
        }

        // Load config file
        ConfigFile config;
        if(Result<ConfigFile> result = p_config? ConfigFile::load(*p_config): ConfigFile::load()){
            if(result.hasWarnings()){
                result.propagateWarnings();
            }
            config = result.takeValue();
        }else return result.failure();

        // Build a parser info

        return {};
    }


// #DIV: Private

// ---- Private Static Methods ----

    // #METHOD: loadConfig(const std::optional<std_fs::path>&), Static Method
    // #BRIEF: Load config file from path or default location
    // #PARAM: const std::optional<std_fs::path>& p_config = std::nullopt, optional path to config file
    // #RETURN: Result<ConfigFile>, Config file result type
    Result<ConfigFile> Command::loadConfig(const std::optional<std_fs::path>& p_config){
        if constexpr(DEBUGGING){
            logger.debug("Loading config file");
        }

        if(p_config){
            return ConfigFile::load(*p_config);
        }else{
            return ConfigFile::load();
        }
    } // #END: loadConfig(const std::optional<std_fs::path>&)

    
// ------------------------------------------------------------------------------
//                              class Command::Error
// ------------------------------------------------------------------------------

// #SCOPE: Error

// #DIV: Public

// ---- Public Factory Methods ----

    // #METHOD: Error(const Code), Constructor
    // #BRIEF: Constructs Error from an error code
    // #PARAM: const Code p_code, Error code for error
    Command::Error::Error(const Code p_code): docme::core::Error(){
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
    template<class... T_ContextArgs> Command::Error::Error(const Code p_code, const T_ContextArgs&... p_contextArgs): docme::core::Error(){
        code = p_code;
        if(auto it = ERROR_MESSAGES.find(code); it != ERROR_MESSAGES.end()){
            body = std::vformat(it->second, std::make_format_args(p_contextArgs...));
        }else{
            body = UNKNOWN_ERROR_MESSAGE;
        }
    } // #END: Error(const Code)

    
// #END: Error

// ------------------------------------------------------------------------------
//                               class Command::Warn
// ------------------------------------------------------------------------------

// #SCOPE: Warn

// #DIV: Public

// ---- Public Factory Methods ----

    // #METHOD: Warn(const Code), Constructor
    // #BRIEF: Constructs Warn from a warning code
    // #PARAM: const Code p_code, Warning code for warning
    Command::Warn::Warn(const Code p_code): docme::core::Warn(){
        code = p_code;
        if(auto it = WARN_MESSAGES.find(code); it != WARN_MESSAGES.end()){
            body = it->second;
        }else{
            body = UNKNOWN_WARNING_MESSAGE;
        }
    } // #END: Warn(const Code)

    // #METHOD: Warn<T_ContextArgs>(const Code, const std::string&), Constructor
    // #BRIEF: Constructs Warn from a warning code and context args
    // #TEMPLATE: class... T_ContextArgs, context arguments parameter pack
    // #PARAM: const Code p_code, Warning code for warning
    // #PARAM: const T_ContextArgs&... p_contextArgs, Context arguments parameter pack
    template<class... T_ContextArgs> Command::Warn::Warn(const Code p_code, const T_ContextArgs&... p_contextArgs): docme::core::Warn(){
        code = p_code;
        if(auto it = WARN_MESSAGES.find(code); it != WARN_MESSAGES.end()){
            body = std::vformat(it->second, std::make_format_args(p_contextArgs...));
        }else{
            body = UNKNOWN_WARNING_MESSAGE;
        }
    } // #END: Warn(const Code)

// #END: Command

} // #END: docme::engine
