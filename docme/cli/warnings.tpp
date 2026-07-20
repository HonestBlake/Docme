// #FILE: warnings.tpp, Component Template Implementation File
// #BRIEF: Template definitions for CLI package warnings

#ifndef COMPILED_WITH_MODULE // Open in editor

module;

#include "cli.hpp" // #INCLUDE: cli.hpp, Package wide header

module docme.cli; // #IMPLEMENTS: docme.cli:warnings
import :warnings;

#endif

namespace docme::cli{ // #SCOPE: docme::cli

    template<class... T_ContextArgs> Warning::Warning(const Code p_code, const T_ContextArgs&... p_contextArgs): core::Warning(WARNING_MESSAGES, p_code, std::make_format_args(p_contextArgs...)){

    } // #END: Warning(const Code, const T_ContextArgs&...)

} // #END: docme::cli
