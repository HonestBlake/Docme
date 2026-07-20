// #FILE: warnings.tpp, Component Template Implementation File
// #BRIEF: Template definitions for generator package warnings

#ifndef COMPILED_WITH_MODULE // Open in editor

module;

#include "generator.hpp" // #INCLUDE: generator.hpp, Package wide header

module docme.generator; // #IMPLEMENTS: docme.generator:warnings
import :warnings;

#endif

namespace docme::generator{ // #SCOPE: docme::generator

    template<class... T_ContextArgs> Warning::Warning(const Code p_code, const T_ContextArgs&... p_contextArgs): core::Warning(WARNING_MESSAGES, p_code, std::make_format_args(p_contextArgs...)){

    } // #END: Warning(const Code, const T_ContextArgs&...)

} // #END: docme::generator
