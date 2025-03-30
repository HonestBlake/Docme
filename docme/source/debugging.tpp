// #file: debugging.tpp, template source file

#pragma once

#include "debugging.hpp" // decloration header

namespace worTech::docme::debugging{

// debugTools, function definitions

    // #func: message(const std::string&, T_args...), noexcept template function

    // #template: typename... T_args, variadic template for formating arguments
    // #param: const std::string& p_message, message to log
    // #param: T_args... p_args, formating arguments
    template<typename... T_args> std::string debugTools::message(const std::string& p_message, T_args... p_args)noexcept{
        return std::vformat(p_message, std::make_format_args(p_args...));
    }
    // #func: warn(const std::string&, std::source_location&&), noexcept template function

    // #template: typename... T_args, variadic template for formating arguments
    // #param: const std::string& p_warning, warning message
    // #param: T_args... p_args, formating arguments
    template<typename... T_args> void debugTools::warn(const std::string& p_warning, T_args... p_args)noexcept{
        if constexpr(!state::WARNING_IS_ERROR){
            btr::Logger::get<AutoDocDebug>().log<btr::Level::WARNING>(std::vformat(p_warning, std::make_format_args(p_args...)));
        }else{
            btr::Logger::get<AutoDocDebug>().log<btr::Level::ERROR>(std::vformat(p_warning, std::make_format_args(p_args...)));
            std::exit(EXIT_FAILURE);
        }
    }
    // #func: error(const std::string&), noexcept template function

    // #template: typename... T_args, variadic template for formating arguments
    // #param: const std::string& p_error, error message
    // #param: T_args... p_args, formating arguments
    template<typename... T_args> void debugTools::error(const std::string& p_error, T_args... p_args)noexcept{
        btr::Logger::get<AutoDocDebug>().log<btr::Level::ERROR>(std::vformat(p_error, std::make_format_args(p_args...)));
        std::exit(EXIT_FAILURE);
    }

} // namespace worTech::autoDoc::debugging