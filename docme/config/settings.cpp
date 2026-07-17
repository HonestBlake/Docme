// #FILE: settings.cpp, Component Source File
// #BRIEF: Source file for settings component

module;

#include "config.hpp" // #INCLUDE: engine.hpp, Package wide header

module docme.config; // #IMPLEMENTS: docme.config:settings
import :settings;

namespace docme::config{ // #SCOPE: docme::config

// ------------------------------------------------------------------------------
//                              class Settings
// ------------------------------------------------------------------------------

// #SCOPE: Settings

// #DIV: Public

// ---- Public Special Methods ----

    // #METHOD: Settings(), Constructor
    // #BRIEF: Constructs Settings with default values
    Settings::Settings(){
        setDefaults();
    } // #END: Settings()

// ---- Public Methods ----

    // #METHOD: applyFile(File&&), Instance Method
    // #BRIEF: Applies config file values to the settings
    // #PARAM: File&& p_config, Config file values to apply
    // #RETURN: Settings&, This settings
    Settings& Settings::applyFile(File&& p_config){
        if(p_config.projectName){
            projectName = std::move(*p_config.projectName);
        }
        if(!p_config.sources.empty()){
            sources = std::move(p_config.sources);
        }
        if(!p_config.ignores.empty()){
            ignores = std::move(p_config.ignores);
        }
        if(p_config.output){
            output = std::move(*p_config.output);
        }
        if(!p_config.languageHandlers.empty()){
            languageHandlers = std::move(p_config.languageHandlers);
        }
        if(!p_config.renderers.empty()){
            renderers = std::move(p_config.renderers);
        }
        return *this;
    } // #END: applyFile(File&&)

    // #METHOD: applyOptions(Options&&), Instance Method
    // #BRIEF: Applies config option values to the settings
    // #PARAM: Options&& p_options, Config option values to apply
    // #RETURN: Settings&, This settings
    Settings& Settings::applyOptions(const Options& p_options){
        if(p_options.projectName){
            projectName = *p_options.projectName;
        }
        if(!p_options.sources.empty()){
            sources = p_options.sources;
        }
        if(!p_options.ignores.empty()){
            ignores = p_options.ignores;
        }
        if(p_options.output){
            output = *p_options.output;
        }
        if(!p_options.languageHandlers.empty()){
            languageHandlers = p_options.languageHandlers;
        }
        if(!p_options.renderers.empty()){
            renderers = p_options.renderers;
        }
        return *this;
    } // #END: applyOptions(Options&&)


// #DIV: Private

// ---- Private Methods ----

    // #METHOD: setDefaults(), Instance Method
    // #BRIEF: Sets default settings values
    void Settings::setDefaults(){
        projectName = defaults::PROJECT_NAME;
        sources = {defaults::SOURCES.begin(), defaults::SOURCES.end()};
        ignores = {defaults::IGNORES.begin(), defaults::IGNORES.end()};
        output = defaults::OUTPUT_DIR;
        languageHandlers = {defaults::LANGUAGE_HANDLERS.begin(), defaults::LANGUAGE_HANDLERS.end()};
        renderers = {defaults::RENDERERS.begin(), defaults::RENDERERS.end()};
    } // #END: setDefaults()


// #END: Settings

} // #END: docme::config