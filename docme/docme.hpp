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

namespace std{ namespace filesystem{} } // Forward delc for filesystem alias

// #NAMESPACE: docme, Project Namespace
// #BRIEF: Main project namespace
namespace docme{

    namespace std_fs = std::filesystem; // #ALIAS: std_fs = std::filesystem, Alias for std::filesystem

    namespace cli{}
    inline namespace core{}
    namespace engine{}
    namespace generator{}
    namespace gui{}

} // namespace docme

// TODO test nodes in json
// TODO test error check in config file