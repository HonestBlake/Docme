// #FILE: errors.tpp, Component Template Implementation File
// #BRIEF: Template definitions for generator package errors

#ifndef COMPILED_WITH_MODULE // Open in editor

module;

#include "generator.hpp" // #INCLUDE: generator.hpp, Package wide header

module docme.generator; // #IMPLEMENTS: docme.generator:errors
import :errors;

#endif

namespace docme::generator{ // #SCOPE: docme::generator

    template<class... T_ContextArgs> Error::Error(const Code p_code, const T_ContextArgs&... p_contextArgs): core::Error(ERROR_MESSAGES, p_code, std::make_format_args(p_contextArgs...)){

    } // #END: Error(const Code, const T_ContextArgs&...)

} // #END: docme::generator
