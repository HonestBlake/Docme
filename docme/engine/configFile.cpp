module;

// #FILE: configFile.cpp, Component Source File

#include "docme.hpp" // #INCLUDE: docme.hpp, Project Header File

module docme.engine; // #IMPLEMENTS: docme.engine, Component Module

import :configFile; // #IMPORT: config, Component Module Partition

namespace docme::engine{ // #SCOPE: docme::engine

// #SCOPE: ConfigFile

// #DIV: Public Static Methods

    // #FUNCTION: createTemplate(const std_fs::path&), Method
    // #BRIEF: Creates new template config file given location
    // #PARAM: const std_fs::path& p_path, Path to create template config file at
    // #RETURNS: std::expected<void, ConfigFile::Error>, Void on successful creation, Error on failure
    // #DETAIL: Creates new config file that copies from template config file, puts at root of current working directory
    std::expected<void, ConfigFile::Error> ConfigFile::createTemplate(const std_fs::path& p_path){
        // Check template being copied
        if(std::error_code _; !std_fs::is_regular_file(TEMPLATE_CONFIG_FILE, _)){ // Failed to find template file
            return std::unexpected(Error(Error::DOCME_100, TEMPLATE_CONFIG_FILE.string()));
        }
        // Create and check new file path
        std_fs::path path;
        if(std::error_code error; std_fs::is_directory(p_path, error)){ // Given a directory
            path = p_path / DEFAULT_CONFIG_FILE;
        }else{ // Given a file path
            if(error) return std::unexpected(Error(Error::DOCME_101, p_path.string())); // Error checking template file path
            if(p_path.extension() != CONFIG_FILE_EXTENSION) return std::unexpected(Error(Error::DOCME_102, p_path.string())); // Given file is not correct type
            path = p_path;
        }
        // Copy template file to new file
        if(std::error_code error; !std_fs::copy_file(TEMPLATE_CONFIG_FILE, path, std_fs::copy_options::none, error)){ // Failed to copy file
            if(error == std::make_error_condition(std::errc::file_exists)) return std::unexpected(Error(Error::DOCME_103, path.string())); // File already exists at given path
            return std::unexpected(Error(Error::DOCME_101, path.string())); 
        }
        return {}; // Success return void
    } // #END: createTemplate(const std_fs::path&)

    // #FUNCTION: load(const std_fs::path&), Method
    // #BRIEF: Creates a config file parsed from given location
    // #PARAM: const std_fs::path& p_path, Path to load config file from
    // #RETURNS: std::expected<ConfigFile, ConfigFile::Error>, Loaded ConfigFile on success, Error on failure
    // #DETAIL: Loads config file from given location then parses the content and creates a ConfigFile object that gets returned
    std::expected<ConfigFile, ConfigFile::Error> ConfigFile::load(const std_fs::path& p_path){
        std_fs::path filePath;
        if(std::error_code error; std_fs::is_directory(p_path, error)){ // Given a directory
            filePath = p_path / DEFAULT_CONFIG_FILE;
        }else{ // Given a file path
            if(error){ // Error checking config file path
                return std::unexpected(Error(Error::DOCME_104, p_path.string()));
            }
            if(p_path.extension() != CONFIG_FILE_EXTENSION){ // Given file is not correct type
                return std::unexpected(Error(Error::DOCME_102, p_path.string()));
            }
            filePath = p_path;
        }
        std::ifstream configFile = std::ifstream(filePath, std::ios::binary);
        if(!configFile){ // Could not open config file
            return std::unexpected(Error(Error::DOCME_104, filePath.string()));
        }
        /*
            TODO: Parse Json Logic
        */
        if(configFile.bad()){ // Error reading config file
            return std::unexpected(Error(Error::DOCME_104, filePath.string()));
        }
        ConfigFile config = ConfigFile();
        return config;
    } // #END: load(const std_fs::path&)

    // #FUNCTION: foundDefault(), Method
    // #BRIEF: Checks if default config file can be found in expected location
    // #RETURNS: bool, Weather default config file could be found
    bool ConfigFile::foundDefault(){
        std::error_code _;
        return std_fs::is_regular_file(DEFAULT_CONFIG_FILE, _);
    } // #END: foundDefault()

    
// #END: ConfigFile

// #SCOPE: ConfigFile::Error

    // #FUNCTION: Error(const Code), Constructor

    // #PARAM: const Code p_code, Error code for error
    ConfigFile::Error::Error(const Code p_code): docme::Error(p_code, ERROR_MESSAGES.at(p_code)){

    } // #END: Error(const Code)

    // #FUNCTION: Error(const Code, const std::string&), Constructor

    // #PARAM: const Code p_code, Error code for error
    // #PARAM: const std::string& p_context, Context string for error
    ConfigFile::Error::Error(const Code p_code, const std::string& p_context): docme::Error(p_code, ERROR_MESSAGES.at(p_code)){
        addContext(p_context);
    } // #END: Error(const Code)

    // #FUNCTION: message(), Public Override Method
    // #BRIEF: Overrides base functionality to provide specific error message formatting for Config errors
    // #OVERRIDE: Error::message()
    // #RETURNS: std::string, Formatted error message string
    std::string ConfigFile::Error::message(){
        const std::string codeString = formatCode();
        if(context.size() == 1){
            return std::vformat(MESSAGE_FORMAT_CONTEXT_1, std::make_format_args(codeString, body, context[0]));
        }else{
            return std::vformat(MESSAGE_FORMAT, std::make_format_args(codeString, body));
        }
    } // #END: message()

// #END: ConfigFile::Error

} // #END: docme::engine
