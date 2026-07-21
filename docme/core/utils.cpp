// #FILE: utils.cpp, Component Source File
// #BRIEF: Source file for utils component

module;

#include "core.hpp" // #INCLUDE: core.hpp, Package wide header

module docme.core; // #IMPLEMENTS: docme.core:utils
import :utils;

namespace docme::core{ // #SCOPE: docme::core

// ------------------------------------------------------------------------------
//                                namespace util
// ------------------------------------------------------------------------------

    // #FUNCTION: normalizePath(const std_fs::path&, const std_fs::path&), Function
    // #BRIEF: Normalizes given path relative to given base path
    // #PARAM: const std_fs::path& p_path, Path to normalize    
    // #PARAM: const std_fs::path& p_base, Base path to normalize relative to
    // #RETURN: std_fs::path, Normalized path
    std_fs::path util::normalizePath(const std_fs::path& p_path, const std_fs::path& p_base){
        if(p_path.is_relative()){
            return (p_base / p_path).lexically_normal();
        }else{
            return p_path.lexically_normal();
        }
    } // #END: normalizePath(const std_fs::path&, const std_fs::path&)

    // #FUNCTION: makeCommaSeparated(const std::vector<std::string>&), Function
    // #BRIEF: Takes a list of strings and makes a single comma separated string
    // #PARAM: const std::vector<std::string>& p_list, Given list
    // #RETURN: std::string, Constructed string
    std::string util::makeCommaSeparated(const std::vector<std::string>& p_list){
        if(p_list.empty()) return "[]";
        std::string string;
        for(size_t item = 0; item < p_list.size(); item++){
            if(item == p_list.size() - 1){ // Last item
                string += p_list[item];
            }else{
                string += (p_list[item] + ", ");
            }
        }
        return string;
    } // #END: makeCommaSeparated(const std::vector<std::string>&)

    // #FUNCTION: makeCommaSeparated(const std::vector<std_fs::path>&), Function
    // #BRIEF: Takes a list of paths and makes a single comma separated string
    // #PARAM: const std::vector<std_fs::path>& p_list, Given list
    // #RETURN: std::string, Constructed string
    std::string util::makeCommaSeparated(const std::vector<std_fs::path>& p_list){
        if(p_list.empty()) return "[]";
        std::string string;
        for(size_t item = 0; item < p_list.size(); item++){
            if(item == p_list.size() - 1){ // Last item
                string += p_list[item].string();
            }else{
                string += (p_list[item].string() + ", ");
            }
        }
        return string;
    } // #END: makeCommaSeparated(const std::vector<std_fs::path>&)


// #END: util
    
} // #END: docme::core
