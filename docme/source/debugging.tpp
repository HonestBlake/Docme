// #file: source/debugging.tpp, Module template source file

#pragma once // Include guard

#include "header/debugging.hpp" // #include: header/debugging.hpp, Module header file

namespace docme::debugging{ // #scope: docme::debugging
 
// #scope: debugTools, function definitions

    // #func: message(const std::string&, T_args...), template function
    template<typename... T_args> std::string debugTools::message(const std::string& p_message, T_args... p_args){
        return std::vformat(p_message, std::make_format_args(p_args...));
    } // end: message(const std::string&, T_args...)

    // #func: debugTools::warn(const std::string&, T_args...), template function
    template<typename... T_args> void debugTools::warn(const std::string& p_warning, T_args... p_args){
        if constexpr(!state::WARNING_IS_ERROR){
            btr::Logger::get<DocmeDebug>().log<btr::Level::WARNING>(std::vformat(p_warning, std::make_format_args(p_args...)));
        }else{
            btr::Logger::get<DocmeDebug>().log<btr::Level::ERROR>(std::vformat(p_warning, std::make_format_args(p_args...)));
            std::exit(EXIT_FAILURE);
        }
    } // # end: debugTools::warn(const std::string&, T_args...)

    // #func: error(const std::string&), template function
    template<typename... T_args> void debugTools::error(const std::string& p_error, T_args... p_args){
        btr::Logger::get<DocmeDebug>().log<btr::Level::ERROR>(std::vformat(p_error, std::make_format_args(p_args...)));
        std::exit(EXIT_FAILURE);
    } // end: error(const std::string&)

// #end: debugTools

} // #end: docme::debugging