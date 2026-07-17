// #FILE: commands.cpp, Component Source File
// #BRIEF: Source file for commands component

module;

#include "app.hpp" // #INCLUDE: cli.hpp, Package wide header

module docme.app; // #IMPLEMENTS: docme.app:commands
import :commands;

import docme.core; // #IMPORT: docme.core, Internal core library
import docme.config; // #IMPORT: docme.config, Internal config library
import docme.generator; // #IMPORT: docme.generator, Internal generator library

namespace docme::app{ // #SCOPE: docme::app

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

        if(config::File::foundDefault()){
            if(p_config){
                Warning::propagate(Warning(Warning::DOCME_W201, p_config->string())); // A second config file will be created
            }else return Error(Error::DOCME_E300); // Default config file already exists
        }

        if(Result<> result = p_config? config::File::create(*p_config): config::File::create(); !result) return result.failure();

        return {};
    } // #END: init()

    // #METHOD: build(), Static Method
    // #BRIEF:
    // #NOTE: Retruns error codes: DOCME_E202, DOCME_E204, DOCME_E205, DOCME_E206
    // #NOTE: Returns warning codes: DOCME_W200
    // #PARAM: const std::optional<std_fs::path>& p_config, optional path to config file
    // #RETURN: Result<>, Optional error state
    Result<> Command::build(const std::optional<std_fs::path>& p_config, const config::Options& p_options){
        if constexpr(DEBUGGING){ // Debug log command call
            logger.debug("Called build command");
        }

        // Build settings
        config::Settings settings;
        if(Result<config::Settings> result = buildSettings(p_config, p_options)){
            settings = result.takeValue();
        }else return result.failure(); // Failed to build settings

        // Build a parser context
        generator::ParserContext parserContext;
        if(Result<generator::ParserContext> result = generator::ParserContext::build(settings)){
            parserContext = result.takeValue();
        }else return result.failure(); // Failed to build parser context

        return {};
    }


// #DIV: Private

// ---- Private Static Methods ----

    // #METHOD: buildSettings(const std_fs::path&, const config::Options&), Static Method
    // #BRIEF: Build configuration from config file and config options
    // #PARAM: const std::optional<std_fs::path>& p_config, optional path to config file
    // #PARAM: const config::Options& p_options, config options to apply
    // #RETURN: Result<config::Settings>, config::Settings result type
    Result<config::Settings> Command::buildSettings(const std::optional<std_fs::path>& p_config, const config::Options& p_options){
        config::Settings settings;
        if(Result<config::File> result = p_config? config::File::load(*p_config): config::File::load()){
            if constexpr(DEBUGGING){ // Debug log loaded config file
                config::util::printFile("Loaded Config File from \"{}\"", p_config? *p_config: config::File::DEFAULT_CONFIG_FILE, result.value());
            }

            settings.applyFile(result.takeValue());
        }else return result.failure();
        settings.applyOptions(p_options);

        if constexpr(DEBUGGING){ // Debug log built config settings
            config::util::printSettings("Built Config Settings", settings);
        }

        return settings;
    }


// ------------------------------------------------------------------------------
//                              class Command::Error
// ------------------------------------------------------------------------------

// #SCOPE: Error

// #DIV: Public

// ---- Public Special Methods ----

    // #METHOD: Error<T_ContextArgs>(const Code, const std::string&), Constructor
    // #BRIEF: Constructs Error from an error code and context args
    // #TEMPLATE: class... T_ContextArgs, context arguments parameter pack
    // #PARAM: const Code p_code, Error code for error
    // #PARAM: const T_ContextArgs&... p_contextArgs, Context arguments parameter pack
    template<class... T_ContextArgs> Command::Error::Error(const Code p_code, const T_ContextArgs&... p_contextArgs): core::Error(ERROR_MESSAGES, p_code, std::make_format_args(p_contextArgs...)){

    } // #END: Error(const Code)

    // Explicit template instantiations for Command errors.
    template Command::Error::Error(const core::Error::Code);
    template Command::Error::Error(const core::Error::Code, const std::string&);
    template Command::Error::Error(const core::Error::Code, const std::string&, const std::string&);
    template Command::Error::Error(const core::Error::Code, const std::string&, const std::string&, const std::string&);


// #END: Error

// ------------------------------------------------------------------------------
//                               class Command::Warning
// ------------------------------------------------------------------------------

// #SCOPE: Warning

// #DIV: Public

// ---- Public Special Methods ----

    // #METHOD: Warning<T_ContextArgs>(const Code, const std::string&), Constructor
    // #BRIEF: Constructs Warning from a warning code and context args
    // #TEMPLATE: class... T_ContextArgs, context arguments parameter pack
    // #PARAM: const Code p_code, Warning code for warning
    // #PARAM: const T_ContextArgs&... p_contextArgs, Context arguments parameter pack
    template<class... T_ContextArgs> Command::Warning::Warning(const Code p_code, const T_ContextArgs&... p_contextArgs): core::Warning(WARNING_MESSAGES, p_code, std::make_format_args(p_contextArgs...)){

    } // #END: Warning(const Code)

    // Explicit template instantiations for Command warnings.
    template Command::Warning::Warning(const core::Warning::Code);
    template Command::Warning::Warning(const core::Warning::Code, const std::string&);
    template Command::Warning::Warning(const core::Warning::Code, const std::string&, const std::string&);
    template Command::Warning::Warning(const core::Warning::Code, const std::string&, const std::string&, const std::string&);

// #END: Command

} // #END: docme::app
