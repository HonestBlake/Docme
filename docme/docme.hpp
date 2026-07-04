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

namespace std{ namespace filesystem{} } // Forward decl for filesystem alias

// #NAMESPACE: docme, Project Namespace
// #BRIEF: Main project namespace
namespace docme{

    inline constexpr bool DEBUGGING = DOCME_DEBUG; // Set debugging state
    
    namespace std_fs = std::filesystem; // #ALIAS: std_fs = std::filesystem, Alias for std::filesystem.
    // using std_location = std::source_location; // #ALIAS: std_loc = std::source_location, Alias for std::source_location.

    namespace cli{}
    inline namespace core{}
    namespace engine{}
    namespace generator{}
    namespace gui{}

} // namespace docme

// TODO test nodes in json
// TODO test error check in config file
