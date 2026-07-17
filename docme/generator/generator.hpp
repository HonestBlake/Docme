// #FILE: generator.hpp, Package Header File

#pragma once

#include "docme.hpp" // #INCLUDE: docme.hpp, Project Header File

namespace docme{ // #SCOPE: docme

    // #NAMESPACE: generator, Package Namespace
    namespace generator{

        // Plugin registry file
        inline constexpr std::string PLUGIN_REGISTRY_FILE_EXTENSION = ".json";
        inline const std::string PLUGIN_REGISTRY_FILE_PATH = "pluginRegistry" + PLUGIN_REGISTRY_FILE_EXTENSION;
        inline const std_fs::path PLUGIN_REGISTRY_FILE = RESOURCES_DIR / PLUGIN_REGISTRY_FILE_PATH; 

        // Metadata file 
        inline constexpr std::string METADATA_FILE_EXTENSION = ".json";

        // OS keys
        inline constexpr std::string_view WINDOWS_KEY = "windows";
        inline constexpr std::string_view LINUX_KEY = "linux";
        inline constexpr std::string_view MACOS_KEY = "macos";

        // #METHOD: getOSKey(), Static Consteval Method
        // #BRIEF: Gets the OS key for the current operating system
        // #RETURN: std::string_view, The OS key for the current operating system
        consteval std::string_view getOSKey(){
            if constexpr(os::isWindows()) return WINDOWS_KEY;
            else if constexpr(os::isLinux()) return LINUX_KEY;
            else if constexpr(os::isMacOS()) return MACOS_KEY;
            else return "";
        } // #END: getOSKey()

        // #NAMESPACE: key, Namespace
        // #BRIEF: Namespace for plugin registry & metadata file keys
        namespace key{
        // Plugin registry keys
            inline constexpr std::string_view TAG = "tag";
            inline constexpr std::string_view METADATA = "metadata";
        // Metadata keys
            inline constexpr std::string_view NAME = "name";
            inline constexpr std::string_view VERSION = "version";
            inline constexpr std::string_view DESCRIPTION = "description";
            inline constexpr std::string_view AUTHOR = "author";
            inline constexpr std::string_view BIN = "binary";
            inline constexpr std::string_view TYPE = "type";
            inline constexpr std::string_view OS = getOSKey();
        } // #END: key

        inline constexpr std::string_view VALID_TYPE = "languageHandler";

    } // #END: generator

} // #END: docme

