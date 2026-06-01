module;

// #FILE: configFile.cpp, Component Source File

#include "docme.hpp" // #INCLUDE: docme.hpp, Project Header File

module docme.engine; // #IMPLEMENTS: docme.engine, Component Module

import :configFile; // #IMPORT: config, Component Module Partition

namespace docme::engine{ // #SCOPE: docme::engine

// #SCOPE: ConfigFile

// #DIV: Public Static Methods

    // #FUNCTION: createTemplate(), Method

    // #RETURNS: std::expected<void, ConfigFile::Error>, Void on successful creation, Error on failure
    std::expected<void, ConfigFile::Error> ConfigFile::createTemplate(){

    } // #END: createTemplate()

    // #FUNCTION: createTemplate(const std::filesystem::path&), Method

    // #PARAM: const std::filesystem::path& path, Path to create template config file at
    // #RETURNS: std::expected<void, ConfigFile::Error>, Void on successful creation, Error on failure
    std::expected<void, ConfigFile::Error> ConfigFile::createTemplate(const std::filesystem::path& path){

    } // #END: createTemplate(const std::filesystem::path&)

    // #FUNCTION: load(), Method

    // #RETURNS: std::expected<ConfigFile, ConfigFile::Error>, Loaded ConfigFile on success, Error on failure
    std::expected<ConfigFile, ConfigFile::Error> ConfigFile::load(){

    } // #END: load()

    // #FUNCTION: load(const std::filesystem::path&), Method
    
    // #PARAM: const std::filesystem::path& path, Path to load config file from
    // #RETURNS: std::expected<ConfigFile, ConfigFile::Error>, Loaded ConfigFile on success, Error on failure
    std::expected<ConfigFile, ConfigFile::Error> ConfigFile::load(const std::filesystem::path& path){

    } // #END: load(const std::filesystem::path&)

    // #FUNCTION: foundDefault(), Method

    // #RETURNS: bool, Weather default config file could be found
    bool ConfigFile::foundDefault(){
        
    } // #END: foundDefault()

    
// #END: ConfigFile

// #SCOPE: Config::Error

    // #FUNCTION: message(), Public Override Method
    // #BRIEF: Overrides base functionality to provide specific error message formatting for Config errors
    // #OVERRIDE: Error::message()
    // #RETURNS: std::string, Formatted error message string
    std::string ConfigFile::Error::message(){
        return "";
    } // #END: message()

// #END: ConfigFile::Error

} // #END: docme::engine
