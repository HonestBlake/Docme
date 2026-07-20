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
    Result<> Command::build(const std::optional<std_fs::path>& p_configFile, config::Options&& p_configOptions){
        // Load config file
        config::File configFile;
        if(Result<config::File> result = p_configFile? config::File::loadForBuild(*p_configFile): config::File::loadForBuild()){
            configFile = result.takeValue();
        }else return result.failure(); // Failed to load config file

        // Build settings
        config::Settings settings;
        if(Result<config::Settings> result = config::Settings::build(std::move(configFile), std::move(p_configOptions))){
            settings = result.takeValue();
        }else return result.failure(); // Failed to build settings

        // Build a parser context
        generator::ParserContext context;
        if(Result<generator::ParserContext> result = generator::ParserContext::build(settings)){
            context = result.takeValue();
        }else return result.failure(); // Failed to build parser context

        // Parse
        generator::Parser parser = generator::Parser::build(std::move(context));
        if(Result<> result = parser.parse(); !result) return result.failure(); // Failed to parse

        return {};
    } // #END: build(const std::optional<std_fs::path>&, const config::Options&)

// #END: Command

} // #END: docme::app
