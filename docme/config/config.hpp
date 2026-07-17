#pragma once

#include "docme.hpp" // #INCLUDE: docme.hpp, Project wide header

namespace docme{ // #SCOPE: docme

    // #NAMESPACE: config, Package Namespace
    // #BRIEF: Namespace for config package
    namespace config{

        // #NAMESPACE: key, Namespace
        // #BRIEF: Namespace for config file json keys
        namespace key{
            inline const std::string_view PROJECT_NAME = "project_name";
            inline const std::string_view SOURCE = "source";
            inline const std::string_view IGNORE = "ignore";
            inline const std::string_view OUTPUT = "output";
            inline const std::string_view LANGUAGE_HANDLER = "language_handler";
            inline const std::string_view RENDERER = "renderer";
            inline const std::unordered_set<std::string_view> SUPPORTED = {
                PROJECT_NAME,
                SOURCE,
                IGNORE,
                OUTPUT,
                LANGUAGE_HANDLER,
                RENDERER
            };
        } // #END: key

        // Config file
        inline constexpr std::string CONFIG_FILE_EXTENSION = ".json";
        inline constexpr std::string DEFAULT_CONFIG_FILE_NAME = "docme" + CONFIG_FILE_EXTENSION;
        inline const std::string TEMPLATE_CONFIG_FILE_NAME = "templateConfigFile" + CONFIG_FILE_EXTENSION;

        // #NAMESPACE: defaults, Namespace
        // #BRIEF: Namespace for default settings values
        namespace defaults{
            inline constexpr std::string_view PROJECT_NAME = "MyProject";
            inline const std_fs::path OUTPUT_DIR = {};
            inline const std::array<std_fs::path, 1> SOURCES = {std_fs::current_path()};
            inline constexpr std::array<std_fs::path, 0> IGNORES = {};
            inline constexpr std::array<std::string_view, 1> LANGUAGE_HANDLERS = {"cdoc"};
            inline constexpr std::array<std::string_view, 1> RENDERERS = {"json"};
        } // #END: defaults

    } // #END: config

} // #END: docme
