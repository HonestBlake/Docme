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

// ---- Public Static Methods ----

    // #METHOD: build(File&&, const Options&), Static Method
    // #BRIEF: Builds settings from the given config file and options
    // #PARAM: File&& p_config, Config file values to build settings from
    // #PARAM: const Options& p_options, Config option values to build settings from
    // #RETURN: Result<Settings>, The built settings result type
    Result<Settings> Settings::build(File&& p_config, const Options& p_options){
        return Settings(std::move(p_config), p_options);
    } // #END: build(File&&, const Options&)


// #DIV: Private

// --- Private Special Methods ----

    // #METHOD: Settings(File&&, const Options&), Constructor
    // #BRIEF: Constructs Settings from the given config file and options
    // #PARAM: File&& p_config, Config file values to construct settings from
    // #PARAM: const Options& p_options, Config option values to construct settings from
    Settings::Settings(File&& p_config, const Options& p_options){
        setDefaults();
        applyFile(std::move(p_config));
        applyOptions(std::move(p_options));
    } // #END: Settings(File&&, const Options&)


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

    // #METHOD: applyFile(File&&), Instance Method
    // #BRIEF: Applies config file values to the settings
    // #PARAM: File&& p_config, Config file values to apply
    void Settings::applyFile(File&& p_config){
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
    } // #END: applyFile(File&&)
    
    // #METHOD: applyOptions(const Options&), Instance Method
    // #BRIEF: Applies config option values to the settings
    // #PARAM: const Options& p_options, Config option values to apply
    void Settings::applyOptions(const Options& p_options){
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
    } // #END: applyOptions(const Options&)


// #END: Settings

} // #END: docme::config