// #FILE: configFile.cpp, Component Source File
// #BRIEF: Source file for configFile component

module;

#include "engine.hpp" // #INCLUDE: engine.hpp, Package wide header

module docme.engine; // #IMPLEMENTS: docme.engine:configFile
import :configFile; 

namespace docme::engine{ // #SCOPE: docme::engine

// #SCOPE: ConfigFile

// #DIV: Public Static Methods

    // #METHOD: createTemplate(const std_fs::path&), Method
    // #BRIEF: Creates new template config file given location
    // #NOTE: Returns error codes: DOCME_200, DOCME_201, DOCME_202, DOCME_203
    // #PARAM: const std_fs::path& p_path, Path to create template config file at
    // #RETURNS: Result<>, Void on successful creation, Error on failure
    // #DETAIL: Creates new config file that copies from template config file, puts at root of current working directory
    Result<> ConfigFile::createTemplate(const std_fs::path& p_path){
        // Check template being copied
        if(std::error_code _; !std_fs::is_regular_file(TEMPLATE_CONFIG_FILE, _)){ // Failed to find template file
            return Error(Error::DOCME_200, TEMPLATE_CONFIG_FILE.string());
        }

        // Create and check new file path
        std_fs::path path;
        if(std::error_code error; std_fs::is_directory(p_path, error)){ // Given a directory
            path = p_path / DEFAULT_CONFIG_FILE;
        }else{ // Given a file path
            if(error && error != std::make_error_condition(std::errc::no_such_file_or_directory)) return Error(Error::DOCME_201, p_path.string()); // Error checking template file path
            if(p_path.extension() != CONFIG_FILE_EXTENSION) return Error(Error::DOCME_202, p_path.string()); // Given file is not correct type
            path = p_path;
        }

        // Copy template file to new file
        if(std::error_code error; !std_fs::copy_file(TEMPLATE_CONFIG_FILE, path, std_fs::copy_options::none, error)){ // Failed to copy file
            if(error == std::make_error_condition(std::errc::file_exists)) return Error(Error::DOCME_203, path.string()); // File already exists at given path
            return Error(Error::DOCME_201, path.string()); 
        }

        return {}; // Success return void
    } // #END: createTemplate(const std_fs::path&)

    // #METHOD: load(const std_fs::path&), Method
    // #BRIEF: Creates a config file parsed from given location
    // #NOTE: Retruns error codes: DOCME_202, DOCME_204, DOCME_205, DOCME_206
    // #PARAM: const std_fs::path& p_path, Path to load config file from
    // #RETURNS: Result<ConfigFile>, Loaded ConfigFile on success, Error on failure
    // #DETAIL: Loads config file from given location then parses the content and creates a ConfigFile object that gets returned
    Result<ConfigFile> ConfigFile::load(const std_fs::path& p_path){
        // Get file Path
        std_fs::path filePath;
        if(std::error_code error; std_fs::is_directory(p_path, error)){ // Given a directory
            filePath = p_path / DEFAULT_CONFIG_FILE;
        }else{ // Given a file path
            if(error) return Error(Error::DOCME_204, p_path.string()); // Error checking config file path
            if(p_path.extension() != CONFIG_FILE_EXTENSION) return Error(Error::DOCME_202, p_path.string()); // Given file is not correct type
            filePath = p_path;
        }

        // Parse json
        Json json;
        if(Result<Json> result = Json::parse(filePath); !result){
            return Error(Error::DOCME_204, filePath.string()); // Could not open config file
        }else{
            json = *std::move(result);
        }
        check(json, filePath);

        // Create config file
        ConfigFile config = ConfigFile();
        if(Result<> result = config.setValues(json, filePath); !result){
            return result.error();
        }

        return config;
    } // #END: load(const std_fs::path&)

    // #METHOD: foundDefault(), Method
    // #BRIEF: Checks if default config file can be found in expected location
    // #RETURNS: bool, Weather default config file could be found
    bool ConfigFile::foundDefault(){
        std::error_code _;
        return std_fs::is_regular_file(DEFAULT_CONFIG_FILE, _);
    } // #END: foundDefault()

// #DIV: Private Static Methods

    // #METHOD: check(const Json&, const std_fs::path&), Method
    // #BRIEF: Validates given config file syntax by warning if unkown key
    // #PARAM: const Json& p_json, Json to check
    // #PARAM: const std_fs::path& p_file, Config file being checked
    void ConfigFile::check(const Json& p_json, const std_fs::path& p_file){
        for(Json::Node& node: p_json.nodes()){
            if(!VALID_KEYS.contains(node.key)){
                logger.warn(UNKNOWN_ENTRY_MESSAGE, node.key, p_file.string());
            }
        }
    }

// #DIV: Private Methods

    // #METHOD: setValues(const Json&, const std_fs::path&), Method
    // #BRIEF: Sets the values of the config
    // #NOTE: Returns error codes: DOCME_205, DOCME_206
    // #PARAM: const Json& p_json, Json to parse from
    // #PARAM: const std_fs::path& p_file, File setting values from
    // #RETURN: Result<>, Result type void on success error type on fail
    Result<> ConfigFile::setValues(const Json& p_json, const std_fs::path& p_file){
        // Set project name
        if(Result<std::string> result = p_json.get<std::string>(PROJECT_NAME_KEY); result){
            m_projectName = *std::move(result);
        }else return Error(Error::DOCME_205, PROJECT_NAME_KEY, p_file.string()); // Failed to parse project name

        // Set source files
        if(Result<std::vector<std::string>> result = p_json.get<std::vector<std::string>>(SOURCE_KEY); result){
            m_sources = *std::move(result);
        }else return Error(Error::DOCME_206, SOURCE_KEY, p_file.string()); // Failed to parse sources

        // Set ignore files
        if(Result<std::vector<std::string>> result = p_json.get<std::vector<std::string>>(IGNORE_KEY); result){
            m_ignores = *std::move(result);
        }else return Error(Error::DOCME_206, IGNORE_KEY, p_file.string()); // Failed to parse ignore

        // Set output
        if(Result<std::string> result = p_json.get<std::string>(OUTPUT_KEY); result){
            m_output = *std::move(result);
        }else return Error(Error::DOCME_205, OUTPUT_KEY, p_file.string()); // Failed to parse output

        // Set language handlers
        if(Result<std::vector<std::string>> result = p_json.get<std::vector<std::string>>(LANGUAGE_HANDLER_KEY); result){
            m_languageHandlers = *std::move(result);
        }else return Error(Error::DOCME_206, LANGUAGE_HANDLER_KEY, p_file.string()); // Failed to parse language handlers

        // Set renderers
        if(Result<std::vector<std::string>> result = p_json.get<std::vector<std::string>>(RENDERER_KEY); result){
            m_renderers = *std::move(result);
        }else return Error(Error::DOCME_206, RENDERER_KEY, p_file.string()); // Failed to parse ignore

        return {};
    } // #END: setValues(const Json&)

// #SCOPE: Error

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
    // #PARAM: const T_ContextArgs&... p_contextArgs, Context arguments parameter pack
    template<class... T_ContextArgs> ConfigFile::Error::Error(const Code p_code, const T_ContextArgs&... p_contextArgs): docme::core::Error(){
        code = p_code;
        body = std::vformat(ERROR_MESSAGES.at(code), std::make_format_args(p_contextArgs...));
    } // #END: Error(const Code)

// #END: Error

// #END: ConfigFile

} // #END: docme::engine
