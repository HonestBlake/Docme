// #FILE: docme.hpp, Project Header File
// #BRIEF: Project wide header file

//  ██████████                  
// ▒▒███▒▒▒▒███                                            
//  ▒███   ▒▒███  ██████   ██████  █████████████    ██████ 
//  ▒███    ▒███ ███▒▒███ ███▒▒███▒▒███▒▒███▒▒███  ███▒▒███
//  ▒███    ▒███▒███ ▒███▒███ ▒▒▒  ▒███ ▒███ ▒███ ▒███████ 
//  ▒███    ███ ▒███ ▒███▒███  ███ ▒███ ▒███ ▒███ ▒███▒▒▒  
//  ██████████  ▒▒██████ ▒▒██████  █████▒███ █████▒▒██████ 
// ▒▒▒▒▒▒▒▒▒▒    ▒▒▒▒▒▒   ▒▒▒▒▒▒  ▒▒▒▒▒ ▒▒▒ ▒▒▒▒▒  ▒▒▒▒▒▒  
//         An open source documentation generator       

#pragma once

#include "std.hpp" // #INCLUDE: std.hpp, Project wide std libs
#include "os.hpp" // #INCLUDE: os.hpp, Project wide os tools

// #NAMESPACE: docme, Project Namespace
// #BRIEF: Main project namespace
namespace docme{

    // Std lib aliases
    namespace std_fs = std::filesystem; // #ALIAS: std_fs = std::filesystem, Alias for std::filesystem
    using std_loc = std::source_location; // #ALIAS: std_loc = std::source_location, Alias for std::source_location

    // Project global constants
    inline constexpr bool DEBUGGING = DOCME_DEBUG; // Set debugging state
    inline constexpr std::string_view VERSION = DOCME_VERSION; // Set project version
    inline constexpr std::string_view COMPILER = DOCME_COMPILER; // Set compiler name
    inline constexpr std::string_view BUILD_MODE = DOCME_BUILD_MODE; // Set build mode
    inline constexpr std::string_view CXX_STANDARD = DOCME_CXX_STANDARD; // Set C++ standard
    inline constexpr std::string_view ROOT_DIR = DOCME_ROOT_DIR; // Set project root directory
    inline const std_fs::path RESOURCES_DIR = std_fs::path(DOCME_ROOT_DIR) / std::string("resources"); // Set project resources directory

    // Package namespaces
    namespace cli{}
    inline namespace core{}
    namespace app{}
    namespace config{}
    namespace generator{}
    namespace gui{}
    namespace plugin{}

} // namespace docme
