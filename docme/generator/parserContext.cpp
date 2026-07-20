// #FILE: parserContext.cpp, Component Source File
// #BRIEF: Source file for parser context component

module;

#include "generator.hpp" // #INCLUDE: generator.hpp, Package wide header

module docme.generator; // #IMPLEMENTS: docme.generator:parserContext
import :parserContext;

namespace docme::generator{ // #SCOPE: docme::generator

// ------------------------------------------------------------------------
//                        class ParserContext
// ------------------------------------------------------------------------

// #SCOPE: ParserContext

// #DIV: public

// ---- Public Static Methods ----

    // #METHOD: build(const config::Settings& p_config), Static Method
    // #BRIEF: Builds a parser context from the given configuration
    // #PARAM: const config::Settings& p_config, The configuration to build the context from
    // #RETURN: Result<ParserContext>, The built parser context result type
    Result<ParserContext> ParserContext::build(const config::Settings& p_config){
        ParserContext context;
        for(const std::string& handlerTag: p_config.languageHandlers){
            // Load language handler
            LanguageHandler handler;
            if(Result<LanguageHandler> result = LanguageHandler::load(handlerTag)){
                handler = result.takeValue();
            }else return result.failure();

            // Debug log loaded language handler
            if constexpr(DEBUGGING){
                util::printLanguageHandler("Loaded Language Handler \"{}\"", handlerTag, handler);
            }

            // Get files for language handler and add to context
            if(Result<std::unordered_set<std_fs::path>> result = discoverFiles(handler, p_config.sources, p_config.ignores)){
                context.languages.push_back({std::move(handler), result.takeValue()});
            }else return result.failure();
        }
        return context;
    } // #END: build(const config::Settings& p_config)


// #DIV: Private

// ---- Private Static Methods ----

    // #METHOD: discoverFiles(const LanguageHandler&, const std::vector<std_fs::path>&, const std::vector<std_fs::path>&), Static Method
    // #BRIEF: Discovers files for the given language handler from the provided sources and ignores
    // #PARAM: const LanguageHandler& p_handler, The language handler to check file types
    // #PARAM: const std::vector<std_fs::path>& p_sources, The source files and directories to search
    // #PARAM: const std::vector<std_fs::path>& p_ignores, The ignore files and directories to skip
    // #RETURN: Result<std::unordered_set<std_fs::path>>, The discovered files result type
    Result<std::unordered_set<std_fs::path>> ParserContext::discoverFiles(const LanguageHandler& p_handler, const std::vector<std_fs::path>& p_sources, const std::vector<std_fs::path>& p_ignores){
        std::unordered_set<std_fs::path> ignores = discoverIgnores(p_handler, p_ignores).takeValue();
        std::unordered_set<std_fs::path> files;
        for(const std_fs::path& source: p_sources){
            if(std::error_code _; !std_fs::exists(source, _)){ // Source does not exist
                Warning::propagate(Warning(Warning::DOCME_W401, source.string()));
            }else if(std::error_code _; std_fs::is_regular_file(source, _)){ // Source is a file
                if(p_handler.supportsFileType(source.extension().string()) && !ignores.contains(source)){
                    files.insert(source);
                }
            }else if(std::error_code _; std_fs::is_directory(source, _)){ // Source is a directory
                std::unordered_set<std_fs::path> sources =
                    std_fs::recursive_directory_iterator(source, std_fs::directory_options::skip_permission_denied, _) 
                    | std::views::filter(std::bind_front(&ParserContext::isValidFileEntry, std::cref(p_handler))) // Filter out not supported files
                    | std::views::filter([&](const std_fs::directory_entry& p_entry){ return !ignores.contains(p_entry.path()); }) // Filter out ignores
                    | std::views::transform([](const std_fs::directory_entry& p_entry){ return p_entry.path(); }) // Transform to path
                    | std::ranges::to<std::unordered_set>(); 
                files.insert(sources.begin(), sources.end());
            }
        }
        return files;
    } // #END: discoverFiles(const LanguageHandler&, const std::vector<std_fs::path>&, const std::vector<std_fs::path>&)

    // #METHOD: discoverIgnores(const LanguageHandler&, const std::vector<std_fs::path>&), Static Method
    // #BRIEF: Discovers ignore directories for the given language handler from the provided ignores
    // #PARAM: const LanguageHandler& p_handler, The language handler to check file types
    // #PARAM: const std::vector<std_fs::path>& p_ignores, The ignore files and directories to skip
    // #RETURN: Success<std::unordered_set<std_fs::path>>, The discovered ignore directories success type
    Success<std::unordered_set<std_fs::path>> ParserContext::discoverIgnores(const LanguageHandler& p_handler, const std::vector<std_fs::path>& p_ignores){
        std::unordered_set<std_fs::path> ignores;
        for(const std_fs::path& ignore: p_ignores){
            if(std::error_code _; !std_fs::exists(ignore, _)){ // Path does not exist
                Warning::propagate(Warning(Warning::DOCME_W401, ignore.string()));
            }else if(std::error_code _; std_fs::is_regular_file(ignore, _)){ // Path is a file
                if(p_handler.supportsFileType(ignore.extension().string())){
                    ignores.insert(ignore);
                }
            }else if(std::error_code _; std_fs::is_directory(ignore, _)){ // Path is a directory
                std::unordered_set<std_fs::path> files =
                    std_fs::recursive_directory_iterator(ignore, std_fs::directory_options::skip_permission_denied, _) 
                    | std::views::filter(std::bind_front(&ParserContext::isValidFileEntry, std::cref(p_handler))) // Filter out not supported files
                    | std::views::transform([](const std_fs::directory_entry& p_entry){ return p_entry.path(); }) // Transform to path
                    | std::ranges::to<std::unordered_set>();
                ignores.insert(files.begin(), files.end());
            }
        }
        return ignores;
    } // #END: discoverIgnores(const LanguageHandler&, const std::vector<std_fs::path>&)

    // #METHOD: isValidFile(const LanguageHandler&, const std_fs::directory_entry&), Static Method
    // #BRIEF: Checks if the given file is valid for the given language handler
    // #PARAM: const LanguageHandler& p_handler, The language handler to check file types
    // #PARAM: const std_fs::path& p_file, The file to check
    // #RETURN: bool, True if the file is valid for the language handler, false otherwise
    bool ParserContext::isValidFileEntry(const LanguageHandler& p_handler, const std_fs::directory_entry& p_file){
        if(std::error_code _; !std_fs::is_regular_file(p_file, _)) return false; // Not a regular file or does not exist
        if(!p_handler.supportsFileType(p_file.path().extension().string())) return false; // File type not supported by language handler
        return true;
    } // #END: isValidFile(const LanguageHandler&, const std_fs::directory_entry&)

// #END: ParserContext

} // #END: docme::generator
