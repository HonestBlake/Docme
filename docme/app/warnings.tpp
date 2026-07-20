// #FILE: warnings.tpp, Component Template Implementation File
// #BRIEF: Template definitions for app package warnings

#ifndef COMPILED_WITH_MODULE // Open in editor

module;

#include "app.hpp" // #INCLUDE: app.hpp, Package wide header

module docme.app; // #IMPLEMENTS: docme.app:warnings
import :warnings;

#endif

namespace docme::app{ // #SCOPE: docme::app

    template<class... T_ContextArgs> Warning::Warning(const Code p_code, const T_ContextArgs&... p_contextArgs): core::Warning(WARNING_MESSAGES, p_code, std::make_format_args(p_contextArgs...)){

    } // #END: Warning(const Code, const T_ContextArgs&...)

} // #END: docme::app
