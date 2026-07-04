// #FILE: configFile.cpp, Component Source File
// #BRIEF: Source file for configFile component

module;

#include "engine.hpp" // #INCLUDE: engine.hpp, Package wide header

module docme.engine; // #IMPLEMENTS: docme.engine:configFile
import :configFile;

import docme.core; // #IMPORT: docme.core, Internal core library

namespace docme::engine{ // #SCOPE: docme::engine

// ------------------------------------------------------------------------------
//                                class ConfigFile
// ------------------------------------------------------------------------------

// #SCOPE: ConfigFile

// #DIV: Public

// ---- Public Static Methods ----

    // #METHOD: create(const std_fs::path&), Static Method
    // #BRIEF: Creates new template config file given location.
    // #NOTE: Returns error codes: DOCME_E200, DOCME_E201, DOCME_E202, DOCME_E203.
    // #NOTE: Returns warning codes: DOCME_W201
    // #ATTRIBUTE: [[nodiscard]]
    // #PARAM: const std_fs::path& p_path = std_fs::current_path() / DEFAULT_CONFIG_FILE, Path to create template config file at
    // #RETURN: Result<>, Void on successful creation, Error on failure
    // #DETAIL: Creates new config file that copies from template config file, puts at root of current working directory
    Result<> ConfigFile::create(const std_fs::path& p_path){
        const std_fs::path templatePath = RESOURCES_DIR / TEMPLATE_CONFIG_FILE;
        
        // Check template being copied
        if(std::error_code _; !std_fs::is_regular_file(templatePath, _)){ // Failed to find template file
            return Error(Error::DOCME_E200, templatePath.string());
        }

        // Create and check new file path
        std_fs::path filePath;
        if(std::error_code error; std_fs::is_directory(p_path, error)){ // Given a directory
            filePath = p_path / DEFAULT_CONFIG_FILE;
        }else{ // Given a file path
            if(error && error != std::make_error_condition(std::errc::no_such_file_or_directory)) return Error(Error::DOCME_E201, p_path.string()); // Error checking template file path
            if(p_path.extension().string() != CONFIG_FILE_EXTENSION) return Error(Error::DOCME_E202, p_path.string()); // Given file is not correct type
            filePath = p_path;
        }

        // Copy template file to new file
        if(std::error_code error; !std_fs::copy_file(templatePath, filePath, std_fs::copy_options::none, error)){ // Failed to copy file
            if(error == std::make_error_condition(std::errc::file_exists)) return Error(Error::DOCME_E203, filePath.string()); // File already exists at given file
            return Error(Error::DOCME_E201, filePath.string());
        }

        // Debug log created file
        if constexpr(DEBUGGING){
            logger.debug("Created config file at \"{}\"", filePath.string());
        }

        return {}; // Success return void
    } // #END: create(const std_fs::path&)

    // #METHOD: load(const std_fs::path&), Static Method
    // #BRIEF: Creates a config file parsed from given location
    // #NOTE: Retruns error codes: DOCME_E202, DOCME_E204, DOCME_E205, DOCME_E206
    // #NOTE: Returns warning codes: DOCME_W200
    // #ATTRIBUTE: [[nodiscard]]
    // #PARAM: const std_fs::path& p_path, Path to load config file from
    // #RETURN: Result<ConfigFile>, Loaded ConfigFile on success, Error on failure
    // #DETAIL: Loads config file from given location then parses the content and creates a ConfigFile object that gets returned
    Result<ConfigFile> ConfigFile::load(const std_fs::path& p_path){
        // Get file Path
        std_fs::path filePath;
        if(std::error_code error; std_fs::is_directory(p_path, error)){ // Given a directory
            filePath = p_path / DEFAULT_CONFIG_FILE;
        }else{ // Given a file path
            if(error) return Error(Error::DOCME_E204, p_path.string()); // Error checking config file path
            if(p_path.extension().string() != CONFIG_FILE_EXTENSION) return Error(Error::DOCME_E202, p_path.string()); // Given file is not correct type
            filePath = p_path;
        }

        // Parse json
        Json json;
        if(Result<Json> result = Json::parse(filePath)){
            json = result.takeValue();
        }else return Error(Error::DOCME_E204, filePath.string()); // Could not open config file

        // Check config file
        if(Success<> success = check(json, filePath); success.hasWarnings()){
            success.propagateWarnings();
        }

        // Create config file
        ConfigFile config;
        if(Result<> result = config.setValues(json, filePath); !result) return result.failure();

        // Debug log loaded file data
        if constexpr(DEBUGGING){
            logger.debug("Loaded config file from \"{}\"", filePath.string());
            logger.debug("Config File: project_name={}; sources={}; ignores={}; output={}; language_handlers={}; renderers={}",
                config.projectName,
                Logger::makeCommaSeparated(config.sources),
                Logger::makeCommaSeparated(config.ignores),
                config.output,
                Logger::makeCommaSeparated(config.languageHandlers),
                Logger::makeCommaSeparated(config.renderers)
            );
        }

        return config;
    } // #END: load(const std_fs::path&)

    // #METHOD: foundDefault(), Static Method
    // #BRIEF: Checks if default config file can be found in expected location
    // #RETURN: bool, Weather default config file could be found
    bool ConfigFile::foundDefault(){
        std::error_code _;
        return std_fs::is_regular_file(DEFAULT_CONFIG_FILE, _);
    } // #END: foundDefault()


// #DIV: Private

// ---- Private Static Methods ----

    // #METHOD: check(const Json&, const std_fs::path&), Static Method
    // #BRIEF: Validates given config file syntax by warning if unkown key
    // #NOTE: Returns warning codes: DOCME_W200
    // #ATTRIBUTE: [[nodiscard]]
    // #PARAM: const Json& p_json, Json to check
    // #PARAM: const std_fs::path& p_file, Config file being checked
    Success<> ConfigFile::check(const Json& p_json, const std_fs::path& p_file){
        for(Json::Node& node: p_json.nodes()){
            if(!VALID_KEYS.contains(node.key)){
                Warnings::add(Warn(Warn::DOCME_W200, node.key, p_file.string())); // Warn unknown key
            }
        }
        return {};
    }

// ---- Private Methods ----

    // #METHOD: setValues(const Json&, const std_fs::path&), Instance Method
    // #BRIEF: Sets the values of the config
    // #NOTE: Returns error codes: DOCME_E205, DOCME_E206
    // #ATTRIBUTE: [[nodiscard]]
    // #PARAM: const Json& p_json, Json to parse from
    // #PARAM: const std_fs::path& p_file, File setting values from
    // #RETURN: Result<>, Result type void on success error type on fail
    Result<> ConfigFile::setValues(const Json& p_json, const std_fs::path& p_file){
        // Set project name
        if(Result<std::string> result = p_json.get<std::string>(PROJECT_NAME_KEY)){
            projectName = result.takeValue();
        }else return Error(Error::DOCME_E205, PROJECT_NAME_KEY, p_file.string()); // Failed to parse project name

        // Set source files
        if(Result<std::vector<std::string>> result = p_json.get<std::vector<std::string>>(SOURCE_KEY)){
            sources = result.takeValue();
        }else return Error(Error::DOCME_E206, SOURCE_KEY, p_file.string()); // Failed to parse sources

        // Set ignore files
        if(Result<std::vector<std::string>> result = p_json.get<std::vector<std::string>>(IGNORE_KEY)){
            ignores = result.takeValue();
        }else return Error(Error::DOCME_E206, IGNORE_KEY, p_file.string()); // Failed to parse ignore

        // Set output
        if(Result<std::string> result = p_json.get<std::string>(OUTPUT_KEY)){
            output = result.takeValue();
        }else return Error(Error::DOCME_E205, OUTPUT_KEY, p_file.string()); // Failed to parse output

        // Set language handlers
        if(Result<std::vector<std::string>> result = p_json.get<std::vector<std::string>>(LANGUAGE_HANDLER_KEY)){
            languageHandlers = result.takeValue();
        }else return Error(Error::DOCME_E206, LANGUAGE_HANDLER_KEY, p_file.string()); // Failed to parse language handlers

        // Set renderers
        if(Result<std::vector<std::string>> result = p_json.get<std::vector<std::string>>(RENDERER_KEY)){
            renderers = result.takeValue();
        }else return Error(Error::DOCME_E206, RENDERER_KEY, p_file.string()); // Failed to parse ignore

        return {};
    } // #END: setValues(const Json&)


// ------------------------------------------------------------------------------
//                            class ConfigFile::Error
// ------------------------------------------------------------------------------

// #SCOPE: Error

// #DIV: Public

// ---- Public Factory Methods ----

    // #METHOD: Error(const Code), Constructor
    // #BRIEF: Constructs Error from an error code
    // #PARAM: const Code p_code, Error code for error
    ConfigFile::Error::Error(const Code p_code): docme::core::Error(){
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
    template<class... T_ContextArgs> ConfigFile::Error::Error(const Code p_code, const T_ContextArgs&... p_contextArgs): docme::core::Error(){
        code = p_code;
        if(auto it = ERROR_MESSAGES.find(code); it != ERROR_MESSAGES.end()){
            body = std::vformat(it->second, std::make_format_args(p_contextArgs...));
        }else{
            body = UNKNOWN_ERROR_MESSAGE;
        }
    } // #END: Error(const Code)


// #END: Error

// ------------------------------------------------------------------------------
//                           class ConfigFile::Warn
// ------------------------------------------------------------------------------

// #SCOPE: Warn

// #DIV: Public

// --- Public Factory Methods ----

    // #METHOD: Warn(const Code), Constructor
    // #BRIEF: Constructs Warn from a warning code
    // #PARAM: const Code p_code, Warning code for warning
    ConfigFile::Warn::Warn(const Code p_code): docme::core::Warn(){
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
    template<class... T_ContextArgs> ConfigFile::Warn::Warn(const Code p_code, const T_ContextArgs&... p_contextArgs): docme::core::Warn(){
        code = p_code;
        if(auto it = WARN_MESSAGES.find(code); it != WARN_MESSAGES.end()){
            body = std::vformat(it->second, std::make_format_args(p_contextArgs...));
        }else{
            body = UNKNOWN_WARNING_MESSAGE;
        }
    } // #END: Warn(const Code)


// #END: ConfigFile

} // #END: docme::engine