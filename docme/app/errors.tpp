// #FILE: errors.tpp, Component Template Implementation File
// #BRIEF: Template definitions for app package errors

#ifndef COMPILED_WITH_MODULE // Open in editor

module;

#include "app.hpp" // #INCLUDE: app.hpp, Package wide header

module docme.app; // #IMPLEMENTS: docme.app:errors
import :errors;

#endif

namespace docme::app{ // #SCOPE: docme::app

    template<class... T_ContextArgs> Error::Error(const Code p_code, const T_ContextArgs&... p_contextArgs): core::Error(ERROR_MESSAGES, p_code, std::make_format_args(p_contextArgs...)){

    } // #END: Error(const Code, const T_ContextArgs&...)

} // #END: docme::app
