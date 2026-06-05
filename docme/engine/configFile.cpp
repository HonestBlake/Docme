// #FILE: configFile.cpp, Component Source File
// #BRIEF: Source file for configFile component

module;

#include "docme.hpp" // #INCLUDE: docme.hpp, Project wide header

module docme.engine; // #IMPLEMENTS: docme.engine:configFile
import :configFile; 

namespace docme::engine{ // #SCOPE: docme::engine

// #SCOPE: ConfigFile

// #DIV: Public Static Methods

    // #METHOD: createTemplate(const std_fs::path&), Method
    // #BRIEF: Creates new template config file given location
    // #PARAM: const std_fs::path& p_path, Path to create template config file at
    // #RETURNS: std::expected<void, ConfigFile::Error>, Void on successful creation, Error on failure
    // #DETAIL: Creates new config file that copies from template config file, puts at root of current working directory
    std::expected<void, ConfigFile::Error> ConfigFile::createTemplate(const std_fs::path& p_path){
        // Check template being copied
        if(std::error_code _; !std_fs::is_regular_file(TEMPLATE_CONFIG_FILE, _)){ // Failed to find template file
            return std::unexpected(Error(Error::DOCME_200, TEMPLATE_CONFIG_FILE.string()));
        }
        // Create and check new file path
        std_fs::path path;
        if(std::error_code error; std_fs::is_directory(p_path, error)){ // Given a directory
            path = p_path / DEFAULT_CONFIG_FILE;
        }else{ // Given a file path
            if(error && error != std::make_error_condition(std::errc::no_such_file_or_directory)) return std::unexpected(Error(Error::DOCME_201, p_path.string())); // Error checking template file path
            if(p_path.extension() != CONFIG_FILE_EXTENSION) return std::unexpected(Error(Error::DOCME_202, p_path.string())); // Given file is not correct type
            path = p_path;
        }
        // Copy template file to new file
        if(std::error_code error; !std_fs::copy_file(TEMPLATE_CONFIG_FILE, path, std_fs::copy_options::none, error)){ // Failed to copy file
            if(error == std::make_error_condition(std::errc::file_exists)) return std::unexpected(Error(Error::DOCME_203, path.string())); // File already exists at given path
            return std::unexpected(Error(Error::DOCME_201, path.string())); 
        }
        return {}; // Success return void
    } // #END: createTemplate(const std_fs::path&)

    // #METHOD: load(const std_fs::path&), Method
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
                return std::unexpected(Error(Error::DOCME_204, p_path.string()));
            }
            if(p_path.extension() != CONFIG_FILE_EXTENSION){ // Given file is not correct type
                return std::unexpected(Error(Error::DOCME_202, p_path.string()));
            }
            filePath = p_path;
        }
        std::ifstream configFile = std::ifstream(filePath, std::ios::binary);
        if(!configFile){ // Could not open config file
            return std::unexpected(Error(Error::DOCME_204, filePath.string()));
        }
        /*
            TODO: Parse Json Logic
        */
        if(configFile.bad()){ // Error reading config file
            return std::unexpected(Error(Error::DOCME_204, filePath.string()));
        }
        ConfigFile config = ConfigFile();
        return config;
    } // #END: load(const std_fs::path&)

    // #METHOD: foundDefault(), Method
    // #BRIEF: Checks if default config file can be found in expected location
    // #RETURNS: bool, Weather default config file could be found
    bool ConfigFile::foundDefault(){
        std::error_code _;
        return std_fs::is_regular_file(DEFAULT_CONFIG_FILE, _);
    } // #END: foundDefault()
    
// #END: ConfigFile

// #SCOPE: ConfigFile::Error

    // #METHOD: Error(const Code), Constructor
    // #BRIEF: Constructs Error from an error code
    // #PARAM: const Code p_code, Error code for error
    ConfigFile::Error::Error(const Code p_code): docme::core::Error(){
        code = p_code;
    } // #END: Error(const Code)

    // #METHOD: Error<T_ContextArgs>(const Code, const std::string&), Constructor
    // #BRIEF: Constructs Error from an error code and context args
    // #TEMPLATE: class... T_ContextArgs, context arguments parameter pack
    // #PARAM: const Code p_code, Error code for error
    // #PARAM: const T_ContextArgs&&... p_contextArgs, Context arguments parameter pack
    template<class... T_ContextArgs> ConfigFile::Error::Error(const Code p_code, const T_ContextArgs&&... p_contextArgs): docme::core::Error(){
        code = p_code;
        body = std::vformat(ERROR_MESSAGES.at(code), std::make_format_args(p_contextArgs...));
    } // #END: Error(const Code)

// #END: ConfigFile::Error

} // #END: docme::engine
