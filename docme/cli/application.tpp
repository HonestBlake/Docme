// #FILE: application.tpp, Component Template Implementation File
// #BRIEF: Template definitions for CLI application

#ifndef COMPILED_WITH_MODULE // Open in editor

module;

#include "cli.hpp" // #INCLUDE: cli.hpp, Package wide header

module docme.cli; // #IMPLEMENTS: docme.cli:application
import :application;

#endif

namespace docme::cli{ // #SCOPE: docme::cli

// ------------------------------------------------------------------------------
//                               class Application
// ------------------------------------------------------------------------------

// #SCOPE: Application

// #DIV: Private

    // #METHOD: setIncludeCode(), Template Instance Method
    // #BRIEF: Set includeCode option based on template parameter
    template<bool t_set> constexpr void Application::setIncludeCode(){
        m_options.includeCode = t_set;
    } // #END: setIncludeCode()

    // #METHOD: setIncludePublic(), Template Instance Method
    // #BRIEF: Set includePublic option based on template parameter
    template<bool t_set> constexpr void Application::setIncludePublic(){
        m_options.includePublic = t_set;
    } // #END: setIncludePublic()

    // #METHOD: setIncludePrivate(), Template Instance Method
    // #BRIEF: Set includePrivate option based on template parameter
    template<bool t_set> constexpr void Application::setIncludePrivate(){
        m_options.includePrivate = t_set;
    } // #END: setIncludePrivate()

    // #METHOD: setIncludeProtected(), Template Instance Method
    // #BRIEF: Set includeProtected option based on template parameter
    template<bool t_set> constexpr void Application::setIncludeProtected(){
        m_options.includeProtected = t_set;
    } // #END: setIncludeProtected()


// #END: Application

} // #END: docme::cli
