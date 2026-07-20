// #FILE: json.tpp, Component Template Implementation File
// #BRIEF: Template definitions for json component.

#ifndef COMPILED_WITH_MODULE // Open in editor

module;

#include "core.hpp" // #INCLUDE: core.hpp, Package wide header

module docme.core; // #IMPLEMENTS: docme.core:json
import :json;

#endif

namespace docme::core{ // #SCOPE: docme::core

    template<class... T_ContextArgs> Json::Error::Error(const Code p_code, const T_ContextArgs&... p_contextArgs): docme::core::Error(ERROR_MESSAGES, p_code, std::make_format_args(p_contextArgs...)){

    } // #END: Error(const Code, const T_ContextArgs&...)

} // #END: docme::core
