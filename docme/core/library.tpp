// #FILE: library.tpp, Component Template Implementation File
// #BRIEF: Template definitions for library component.

#ifndef COMPILED_WITH_MODULE // Open in editor

module;

#include "core.hpp" // #INCLUDE: core.hpp, Package wide header

module docme.core; // #IMPLEMENTS: docme.core:library
import :library;

#endif

namespace docme::core{ // #SCOPE: docme::core

// ------------------------------------------------------------------------------
//                              class Library
// ------------------------------------------------------------------------------

// #SCOPE: Library

// #DIV: Public

// ---- Public Methods ----

    // #METHOD: getFunction(const std::string_view), Const Instance Method
    // #BRIEF: Gets a function pointer from the loaded dynamic library
    // #NOTE: Returns error codes: DOCME_E106, DOCME_E107
    // #TEMPLATE: class T_Function, Function signature type
    // #PARAM: const std::string_view p_functionName, Exported function name
    // #RETURN: Result<std::function<T_Function>>, Loaded function wrapper or error type
    template<class T_Function> Result<std::function<T_Function>> Library::getFunction(const std::string_view p_functionName)const{
        if(!m_loaded) return Error(Error::DOCME_E107, std::string(p_functionName), m_name);
        NativeFunctionPointer function = getNativeFunctionPointer(m_handle, p_functionName);
        if(!function) return Error(Error::DOCME_E106, std::string(p_functionName), m_name);
        return std::function<T_Function>(reinterpret_cast<T_Function*>(function));
    } // #END: getFunction(const std::string_view)

} // #END: docme::core