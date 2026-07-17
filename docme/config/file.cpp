// #FILE: file.cpp, Component Source File
// #BRIEF: Source file for file component

module;

#include "config.hpp" // #INCLUDE: engine.hpp, Package wide header

module docme.config; // #IMPLEMENTS: docme.config:file
import :file;

import docme.core; // #IMPORT: docme.core, Internal core library

namespace docme::config{ // #SCOPE: docme::config

// ------------------------------------------------------------------------------
//                                class File
// ------------------------------------------------------------------------------

// #SCOPE: File

// #DIV: Public

// ---- Public Static Methods ----
    // #METHOD: create(const std_fs::path&), Static Method
    // #BRIEF: Creates new template config file given location.
    // #NOTE: Returns error codes: DOCME_E200, DOCME_E201, DOCME_E202, DOCME_E203.
    // #NOTE: Returns warning codes: DOCME_W201
    // #ATTRIBUTE: [[nodiscard]]
    // #PARAM: const std_fs::path& p_path = DEFAULT_CONFIG_FILE, Normalized path to create template config file at
    // #RETURN: Result<>, Void on successful creation, Error on failure
    // #DETAIL: Creates new config file that copies from template config file, puts at root of current working directory
    Result<> File::create(const std_fs::path& p_path){
        // Check template being copied
        if(std::error_code _; !std_fs::is_regular_file(TEMPLATE_CONFIG_FILE, _)){ // Failed to find template file
            return Error(Error::DOCME_E200, TEMPLATE_CONFIG_FILE.string());
        }

        // Create and check new file path
        std_fs::path filePath;
        if(std::error_code error; std_fs::is_directory(p_path, error)){ // Given a directory
            filePath = p_path / DEFAULT_CONFIG_FILE_NAME;
        }else{ // Given a file path
            if(error && error != std::make_error_condition(std::errc::no_such_file_or_directory)) return Error(Error::DOCME_E201, p_path.string()); // Error checking template file path
            if(p_path.extension().string() != CONFIG_FILE_EXTENSION) return Error(Error::DOCME_E202, p_path.string()); // Given file is not correct type
            filePath = p_path;
        }

        // Copy template file to new file
        if(std::error_code error; !std_fs::copy_file(TEMPLATE_CONFIG_FILE, filePath, std_fs::copy_options::none, error)){ // Failed to copy file
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
    // #PARAM: const std_fs::path& p_path, Normalized path to load config file from
    // #RETURN: Result<File>, Loaded File on success, Error on failure
    // #DETAIL: Loads config file from given location then parses the content and creates a File object that gets returned
    Result<File> File::load(const std_fs::path& p_path){
        // Get file Path
        std_fs::path filePath;
        if(std::error_code error; std_fs::is_directory(p_path, error)){ // Given a directory
            filePath = p_path / DEFAULT_CONFIG_FILE_NAME;
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
        check(json, filePath).propagateWarnings();

        // Create config file
        File config;
        if(Result<> result = config.setValues(json, filePath); !result) return result.failure();

        return config;
    } // #END: load(const std_fs::path&)

    // #METHOD: foundDefault(), Static Method
    // #BRIEF: Checks if default config file can be found in expected location
    // #RETURN: bool, Weather default config file could be found
    bool File::foundDefault(){
        std::error_code _;
        return std_fs::is_regular_file(DEFAULT_CONFIG_FILE, _);
    } // #END: foundDefault()


// #DIV: Private

// ---- Private Static Methods ----

    // #METHOD: check(const Json&, const std_fs::path&), Static Method
    // #BRIEF: Validates given config file syntax by warning if unkown key
    // #NOTE: Returns warning codes: DOCME_W200
    // #PARAM: const Json& p_json, Json to check
    // #PARAM: const std_fs::path& p_file, Config file being checked
    Success<> File::check(const Json& p_json, const std_fs::path& p_file){
        for(Json::Node& node: p_json.nodes()){
            if(!key::SUPPORTED.contains(node.key)){
                Warning::propagate(Warning(Warning::DOCME_W200, node.key, p_file.string())); // Warning unknown key
            }
        }
        return {};
    } // #END: check(const Json&, const std_fs::path&)

    // #METHOD: makePath(const std::string_view, const std_fs::path&), Static Method
    // #BRIEF: Makes a path from given string and file path
    // #PARAM: const std::string_view p_path, String to make path from
    // #PARAM: const std_fs::path& p_file, File path to make path relative to
    // #RETURN: std_fs::path, Path made from given string and file path
    std_fs::path File::makePath(const std::string_view p_path, const std_fs::path& p_file){
        std_fs::path path = p_path;
        core::util::normalizePath(path, p_file.parent_path());
        return path;
    } // #END: makePath(const std::string_view, const std_fs::path&)


// ---- Private Methods ----

    // #METHOD: setValues(const Json&, const std_fs::path&), Instance Method
    // #BRIEF: Sets the values of the config
    // #NOTE: Returns error codes: DOCME_E205, DOCME_E206
    // #PARAM: const Json& p_json, Json to parse from
    // #PARAM: const std_fs::path& p_file, File setting values from
    // #RETURN: Result<>, Result type void on success error type on fail
    Result<> File::setValues(const Json& p_json, const std_fs::path& p_file){
        // Set project name
        if(Result<std::string> result = p_json.get<std::string>(key::PROJECT_NAME)){
            projectName = result.takeValue();
        }else if(Json::Error::isTypeError(result.error())) return Error(Error::DOCME_E205, std::string(key::PROJECT_NAME), p_file.string()); // Wrong type
        else if(result.error() != Error::DOCME_E101) [[unlikely]] return result.failure(); // Error other than not found

        // Set source files
        if(Result<std::vector<std::string>> result = p_json.get<std::vector<std::string>>(key::SOURCE)){
            sources = result.takeValue() 
                | std::views::transform([&](const std::string_view path){ 
                    return makePath(path, p_file); 
                })
                | std::ranges::to<std::vector>();
        }else if(Json::Error::isTypeError(result.error())) return Error(Error::DOCME_E206, std::string(key::SOURCE), p_file.string()); // Wrong type
        else if(result.error() != Error::DOCME_E101) [[unlikely]] return result.failure(); // Error other than not found

        // Set ignore files
        if(Result<std::vector<std::string>> result = p_json.get<std::vector<std::string>>(key::IGNORE)){
            ignores = result.takeValue() 
                | std::views::transform([&](const std::string_view path){ 
                    return makePath(path, p_file); 
                })
                | std::ranges::to<std::vector>();
        }else if(Json::Error::isTypeError(result.error())) return Error(Error::DOCME_E206, std::string(key::IGNORE), p_file.string()); // Wrong type
        else if(result.error() != Error::DOCME_E101) [[unlikely]] return result.failure(); // Error other than not found

        // Set output
        if(Result<std::string> result = p_json.get<std::string>(key::OUTPUT)){
            output = makePath(result.takeValue(), p_file);
        }else if(Json::Error::isTypeError(result.error())) return Error(Error::DOCME_E205, std::string(key::OUTPUT), p_file.string()); // Wrong type
        else if(result.error() != Error::DOCME_E101) [[unlikely]] return result.failure(); // Error other than not found

        // Set language handlers
        if(Result<std::vector<std::string>> result = p_json.get<std::vector<std::string>>(key::LANGUAGE_HANDLER)){
            languageHandlers = result.takeValue();
        }else if(Json::Error::isTypeError(result.error())) return Error(Error::DOCME_E206, std::string(key::LANGUAGE_HANDLER), p_file.string()); // Wrong type
        else if(result.error() != Error::DOCME_E101) [[unlikely]] return result.failure(); // Error other than not found

        // Set renderers
        if(Result<std::vector<std::string>> result = p_json.get<std::vector<std::string>>(key::RENDERER)){
            renderers = result.takeValue();
        }else if(Json::Error::isTypeError(result.error())) return Error(Error::DOCME_E206, std::string(key::RENDERER), p_file.string()); 
        else if(result.error() != Error::DOCME_E101) [[unlikely]] return result.failure(); // Error other than not found

        return {};
    } // #END: setValues(const Json&)


// ------------------------------------------------------------------------------
//                            class File::Error
// ------------------------------------------------------------------------------

// #SCOPE: Error

// #DIV: Public

// ---- Public Special Methods ----

    // #METHOD: Error<T_ContextArgs>(const Code, const std::string&), Constructor
    // #BRIEF: Constructs Error from an error code and context args
    // #TEMPLATE: class... T_ContextArgs, context arguments parameter pack
    // #PARAM: const Code p_code, Error code for error
    // #PARAM: const T_ContextArgs&... p_contextArgs, Context arguments parameter pack
    template<class... T_ContextArgs> File::Error::Error(const Code p_code, const T_ContextArgs&... p_contextArgs): core::Error(ERROR_MESSAGES, p_code, std::make_format_args(p_contextArgs...)){

    } // #END: Error(const Code)

    // Explicit template instantiations for File errors.
    template File::Error::Error(const core::Error::Code);
    template File::Error::Error(const core::Error::Code, const std::string&);
    template File::Error::Error(const core::Error::Code, const std::string&, const std::string&);
    template File::Error::Error(const core::Error::Code, const std::string&, const std::string&, const std::string&);


// #END: Error

// ------------------------------------------------------------------------------
//                           class File::Warning
// ------------------------------------------------------------------------------

// #SCOPE: Warning

// #DIV: Public

// --- Public Special Methods ----

    // #METHOD: Warning<T_ContextArgs>(const Code, const std::string&), Constructor
    // #BRIEF: Constructs Warning from a warning code and context args
    // #TEMPLATE: class... T_ContextArgs, context arguments parameter pack
    // #PARAM: const Code p_code, Warning code for warning
    // #PARAM: const T_ContextArgs&... p_contextArgs, Context arguments parameter pack
    template<class... T_ContextArgs> File::Warning::Warning(const Code p_code, const T_ContextArgs&... p_contextArgs): core::Warning(WARNING_MESSAGES, p_code, std::make_format_args(p_contextArgs...)){

    } // #END: Warning(const Code)

    // Explicit template instantiations for File warnings.
    template File::Warning::Warning(const core::Warning::Code);
    template File::Warning::Warning(const core::Warning::Code, const std::string&);
    template File::Warning::Warning(const core::Warning::Code, const std::string&, const std::string&);
    template File::Warning::Warning(const core::Warning::Code, const std::string&, const std::string&, const std::string&);


// #END: File

} // #END: docme::config
