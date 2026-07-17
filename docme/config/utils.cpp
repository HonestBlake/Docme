// #FILE: utils.cpp, Component Source File
// #BRIEF: Source file for utils component

module;

#include "config.hpp" // #INCLUDE: config.hpp, Package wide header

module docme.config; // #IMPLEMENTS: docme.config:utils
import :utils;

namespace docme::config{ // #SCOPE: docme::config

// ------------------------------------------------------------------------------
//                                namespace util
// ------------------------------------------------------------------------------

// #SCOPE: utils

// ---- Debug Only Functions ----

#if DOCME_DEBUG

    // #FUNCTION: printOptions(const std::string&, const Options&), Free Function
    // #BRIEF: Debug prints the given config options
    // #PARAM: const std::string& p_message, The message to print before the options
    // #PARAM: const Options& p_options, The config options to print
    void util::printOptions(const std::string& p_message, const Options& p_options){
        logger.debug(p_message + ": project_name={}; sources={}; ignores={}; output={}; language_handlers={}; renderers={}",
            p_options.projectName.value_or(""),
            core::util::makeCommaSeparated(p_options.sources),
            core::util::makeCommaSeparated(p_options.ignores),
            p_options.output? p_options.output->string(): "",
            core::util::makeCommaSeparated(p_options.languageHandlers),
            core::util::makeCommaSeparated(p_options.renderers)
        );
    } // #END: printOptions(const std::string&, const Options&)

    // #FUNCTION: printFile(const std::string&, const std_fs::path&, const File&), Free Function
    // #BRIEF: Debug prints the given config file
    // #PARAM: const std::string& p_message, The message to print before the file
    // #PARAM: const std_fs::path& p_path, The path of the config file to print
    // #PARAM: const File& p_file, The config file to print
    void util::printFile(const std::string& p_message, const std_fs::path& p_path, const File& p_file){
        logger.debug(p_message + ": project_name={}; sources={}; ignores={}; output={}; language_handlers={}; renderers={}",
            (std_fs::is_regular_file(p_path))? p_path.string(): p_path.string() + DEFAULT_CONFIG_FILE_NAME,
            p_file.projectName.value_or(""),
            core::util::makeCommaSeparated(p_file.sources),
            core::util::makeCommaSeparated(p_file.ignores),
            p_file.output? p_file.output->string(): "",
            core::util::makeCommaSeparated(p_file.languageHandlers),
            core::util::makeCommaSeparated(p_file.renderers)
        );
    } // #END: printFile(const std::string&, const std_fs::path&, const File&)

    // #FUNCTION: printSettings(const std::string&, const Settings&), Free Function
    // #BRIEF: Debug prints the given config settings
    // #PARAM: const std::string& p_message, The message to print before the settings
    // #PARAM: const Settings& p_settings, The config settings to print
    void util::printSettings(const std::string& p_message, const Settings& p_settings){
        logger.debug(p_message + ": project_name={}; sources={}; ignores={}; output={}; language_handlers={}; renderers={}",
            p_settings.projectName,
            core::util::makeCommaSeparated(p_settings.sources),
            core::util::makeCommaSeparated(p_settings.ignores),
            p_settings.output.string(),
            core::util::makeCommaSeparated(p_settings.languageHandlers),
            core::util::makeCommaSeparated(p_settings.renderers)
        );
    } // #END: printSettings(const std::string&, const Settings&)


#endif

// #END: util

} // #END: docme::config
