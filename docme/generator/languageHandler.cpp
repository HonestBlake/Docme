// #FILE: languageHandler.cpp, Component Source File
// #BRIEF: Source file for languageHandler component

module;

#include "generator.hpp" // #INCLUDE: generator.hpp, Package wide header

module docme.generator; // #IMPLEMENTS: docme.generator:languageHandler
import :languageHandler;
import :utils;

namespace docme::generator{ // #SCOPE: docme::generator

// ------------------------------------------------------------------------------
//                            class LanguageHandler
// ------------------------------------------------------------------------------

// #SCOPE: LanguageHandler

// #DIV: Public

// ---- Public Static Methods ----

    // #METHOD: load(const std::string&), Static Method
    // #BRIEF: Loads a language handler from the given tag
    // #PARAM: const std::string& p_tag, The tag of the language handler to load
    // #RETURN: Result<LanguageHandler>, The loaded language handler result type
    Result<LanguageHandler> LanguageHandler::load(const std::string_view p_tag){
        // Load plugin registry file
        Json pluginRegistry;
        if(Result<Json> result = Json::parse(PLUGIN_REGISTRY_FILE)){
            pluginRegistry = result.takeValue();
        }else return result.failure(); // Failed to parse plugin registry file

        // Get metadata path
        std_fs::path metadataPath;
        if(Result<std::string> result = getMetadataPath(pluginRegistry, p_tag)){
            core::util::normalizePath(metadataPath = result.takeValue(), PLUGIN_REGISTRY_FILE.parent_path()); 
        }else return result.failure(); // Failed to get metadata path
        if(Result<> result = checkMetadataPath(metadataPath, p_tag); !result) return result.failure(); // Failed to check metadata path

        // Load metadata file
        Json metadata;
        if(Result<Json> result = Json::parse(metadataPath)){
            metadata = result.takeValue();
        }else return Error(Error::DOCME_E404, metadataPath.string(), p_tag); // Failed to parse metadata file

        // Build language handler from metadata
        LanguageHandler handler;
        if(Result<> result = handler.setValues(metadata, metadataPath.string(), p_tag); !result) return result.failure(); // Failed to set values from metadata
        if(Result<> result = handler.loadLibrary(metadata, metadataPath, p_tag); !result) return result.failure(); // Failed to load library
        if(Result<> result = handler.loadFunctions(p_tag); !result) return result.failure(); // Failed to load functions

        return handler;
    } // #END: load(const std::string&)

// ---- Public Methods ----

    // #METHOD: supportsFileType(const std::string_view), Method
    // #BRIEF: Checks if the language handler supports the given file type
    // #PARAM: const std::string_view p_fileType, The file type to check
    // #RETURN: bool, True if the language handler supports the file type, false otherwise
    bool LanguageHandler::supportsFileType(const std::string_view p_fileType)const{
        return m_supportsFileType(std::string(p_fileType).c_str());
    } // #END: supportsFileType(const std::string_view)


// #DIV: Private

// ---- Private Static Methods ----

    // #METHOD: getMetadataPath(const Json&, const std::string_view), Static Method
    // #BRIEF: Gets the metadata path for the language handler from the plugin registry
    // #PARAM: const Json& p_pluginRegistry, The plugin registry to search for the metadata path
    // #PARAM: const std::string_view p_tag, The tag of the language handler to find
    // #RETURN: Result<std::string>, Result type for retrieved metadata path
    Result<std::string> LanguageHandler::getMetadataPath(const Json& p_pluginRegistry, const std::string_view p_tag){
        for(Json::Node node: p_pluginRegistry.nodes()){
            const auto&[_, entry] = node;

            // Check tag
            if(const Result<std::string> result = entry.get<std::string>(key::TAG)){
                if(result.value() != p_tag) continue; 
            }else continue;

            // Check type 
            if(const Result<std::string> result = entry.get<std::string>(key::TYPE)){
                if(result.value() != VALID_TYPE) return Error(Error::DOCME_E400, result.value(), p_tag, std::string(VALID_TYPE)); // Wrong type for plugin
            }else return Error(Error::DOCME_INTERNAL, std::vformat(Error::COULD_NOT_FIND_FIELD_MESSAGE, std::make_format_args(key::METADATA, p_tag))); // Couldn't find type

            // Get metadata path
            if(Result<std::string> result = entry.get<std::string>(key::METADATA)){
                return result.takeValue();
            }else return Error(Error::DOCME_INTERNAL, std::vformat(Error::COULD_NOT_FIND_FIELD_MESSAGE, std::make_format_args(key::METADATA, p_tag))); // Couldn't find metadata path
        }
        return Error(Error::DOCME_E401, p_tag); // Couldn't find plugin with given tag
    } // #END: getMetadataPath(const Json&, const std::string_view)

    // #METHOD: checkMetadataPath(const std_fs::path&, const std::string_view), Static Method
    // #BRIEF: Checks if the metadata path exists and is right file type
    // #PARAM: const std::string_view p_metadataPath, The metadata path to check
    // #PARAM: const std::string_view p_tag, The tag of the language handler to check
    // #RETURN: Result<>, Result type for checking metadata path
    Result<> LanguageHandler::checkMetadataPath(const std_fs::path& p_metadataPath, const std::string_view p_tag){
        if(!std_fs::exists(p_metadataPath) || !std_fs::is_regular_file(p_metadataPath)) return Error(Error::DOCME_E402, p_metadataPath.string(), p_tag); // Metadata path does not exist
        if(p_metadataPath.extension() != METADATA_FILE_EXTENSION) return Error(Error::DOCME_E403, p_metadataPath.string(), p_tag, METADATA_FILE_EXTENSION); // Metadata path is not correct file type
        return {};
    } // #END: checkMetadataPath(const std_fs::path&, const std::string_view)


// ---- Private Methods ----

    // #METHOD: setValues(const Json&, const std::string_view, const std::string_view), Instance Method
    // #BRIEF: Sets values of the language handler from the given metadata
    // #PARAM: const Json& p_metadata, The metadata to set values from
    // #PARAM: const std::string_view p_metadataPath, The path to the metadata file
    // #PARAM: const std::string_view p_tag, The tag of the language handler to build
    // #RETURN: Result<>, Result type for setting values
    Result<> LanguageHandler::setValues(const Json& p_metadata, const std::string_view p_metadataPath, const std::string_view p_tag){
        // Set name
        if(Result<std::string> result = p_metadata.get<std::string>(key::NAME)){
            name = result.takeValue();
        }else if(Json::Error::isJsonTypeError(result.error())) return Error(Error::DOCME_E405, p_metadataPath, p_tag, key::NAME, "string"); // Name wrong type
        else return Error(Error::DOCME_E406, p_metadataPath, p_tag, key::NAME); // Cant find name

        // Set version
        if(Result<std::string> result = p_metadata.get<std::string>(key::VERSION)){
            version = result.takeValue();
        }else if(Json::Error::isJsonTypeError(result.error())) return Error(Error::DOCME_E405, p_metadataPath, p_tag, key::VERSION, "string"); // Version wrong type
        else return Error(Error::DOCME_E406, p_metadataPath, p_tag, key::VERSION); // Cant find version

        // Set description
        if(Result<std::string> result = p_metadata.get<std::string>(key::DESCRIPTION)){
            description = result.takeValue();
        }else if(Json::Error::isJsonTypeError(result.error())) return Error(Error::DOCME_E405, p_metadataPath, p_tag, key::DESCRIPTION, "string"); // Description wrong type
        else return Error(Error::DOCME_E406, p_metadataPath, p_tag, key::DESCRIPTION); // Cant find description

        // Set author
        if(Result<std::string> result = p_metadata.get<std::string>(key::AUTHOR)){
            author = result.takeValue();
        }else if(Json::Error::isJsonTypeError(result.error())) return Error(Error::DOCME_E405, p_metadataPath, p_tag, key::AUTHOR, "string"); // Author wrong type
        else return Error(Error::DOCME_E406, p_metadataPath, p_tag, key::AUTHOR); // Cant find author

        return {};
    } // #END: setValues(const Json&, const std::string_view, const std::string_view)

    // #METHOD: loadLibrary(const Json&, const std_fs::path&, const std::string_view), Instance Method
    // #BRIEF: Loads the library for the language handler from the given metadata
    // #PARAM: const Json& p_metadata, The metadata to load the library from
    // #PARAM: const std_fs::path& p_metadataPath, The path to the metadata file
    // #PARAM: const std::string_view p_tag, The tag of the language handler to load
    // #RETURN: Result<>, Result type for loading library
    Result<> LanguageHandler::loadLibrary(const Json& p_metadata, const std_fs::path& p_metadataPath, const std::string_view p_tag){
        // Load binary path
        std_fs::path binaryPath;
        if(Result<std::string> result = p_metadata.get<std::string>(key::BIN, key::OS)){
            core::util::normalizePath(binaryPath = result.takeValue(), p_metadataPath.parent_path());
        }else if(Json::Error::isJsonTypeError(result.error())) return Error(Error::DOCME_E405, p_metadataPath.string(), p_tag, key::BIN, "string"); // Wrong type for binary
        else return Error(Error::DOCME_E406, p_metadataPath.string(), p_tag, key::BIN); // Couldn't find binary

        if(Result<Library> result = Library::load(name, binaryPath)){
            m_library = result.takeValue();
        }else return Error(Error::DOCME_E407, binaryPath.string(), p_tag); // Failed to load library

        return {};
    } // #END: loadLibrary(const Json&, const std_fs::path&, const std::string_view)

    // #METHOD: loadFunctions(const std::string_view), Instance Method
    // #BRIEF: Loads functions from the language handler binary
    // #PARAM: const std::string_view p_tag, The tag of the language handler to load functions for
    // #RETURN: Result<>, Result type for loading functions
    Result<> LanguageHandler::loadFunctions(const std::string_view p_tag){
        // Load supportsFileType
        if(Result<std::function<plugin::api::supportsFileType::Type>> result = m_library.getFunction<plugin::api::supportsFileType::Type>(plugin::api::supportsFileType::NAME)){
            m_supportsFileType = result.takeValue();
        }else return Error(Error::DOCME_E408, plugin::api::supportsFileType::NAME, p_tag); // Failed to load function

        return {};
    } // #END: loadFunctions(const std::string_view)

    
// #END: LanguageHandler

} // #END: docme::generator
