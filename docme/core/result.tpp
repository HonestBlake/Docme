// #FILE: result.tpp, Component Template Implementation File
// #BRIEF: Template definitions for result component

#ifndef COMPILED_WITH_MODULE // Open in editor

module;

#include "core.hpp" // #INCLUDE: core.hpp, Package wide header

module docme.core; // #IMPLEMENTS: docme.core:result
import :result;

import :errors; // #IMPORT: docme.core:errors, Error type
import std; // #IMPORT: std, Standard library

#endif // ifndef COMPILED_WITH_MODULE

namespace docme::core{ // #SCOPE: docme::core

// #SCOPE: Result<T_Return>

// #DIV: Public Factory Methods

    // #METHOD: Result(const T_Return&), Constructor
    // #BRIEF: Construct from return type
    // #PARAM: const T_Return& p_success, Given success value 
    template<class T_Return> Result<T_Return>::Result(const T_Return& p_success): m_result(p_success){

    } // #END: Result(const T_Return&)

    // #METHOD: Result(T_Return&&), Constructor
    // #BRIEF: Move construct from return type
    // #NOTE: This method takes ownership of given return
    // #PARAM: T_Return&& p_return, Moved success value 
    template<class T_Return> Result<T_Return>::Result(T_Return&& p_success): m_result(std::move(p_success)){

    } // #END: Result(T_Return&&)

    // #METHOD: Result(const Error&), Constructor
    // #BRIEF: Construct from error type
    // #PARAM: Error& p_error, Given error value 
    template<class T_Return> Result<T_Return>::Result(const Error& p_error): m_result(p_error){

    } // #END: Result(const Error&)

    // #METHOD: Result(Error&&), Constructor
    // #BRIEF: Move construct from error type
    // #NOTE: This method takes ownership of given error
    // #PARAM: Error&& p_error, Moved error value
    template<class T_Return> Result<T_Return>::Result(Error&& p_error): m_result(std::move(p_error)){

    } // #END: Result(Error&&)

// #DIV: Public Operators

    // #METHOD: operator bool(), Const Operator
    // #BRIEF: Check if result is successful state
    template<class T_Return> Result<T_Return>::operator bool()const{
        return std::holds_alternative<T_Return>(m_result);
    } // #END: operator bool()

    // #METHOD: operator*()const &, Const Operator
    // #BRIEF: Dereference operator to get successful state
    // #THROWS: std::bad_variant_access, If result is not a success state
    // #NOTE: Only call when type is know to be successful state
    template<class T_Return> T_Return Result<T_Return>::operator*()const&{
        return std::get<T_Return>(m_result);
    } // #END: operator*()

    // #METHOD: operator*()&&, Const Operator
    // #BRIEF: Dereference operator to get successful state
    // #THROWS: std::bad_variant_access, If result is not a success state
    // #NOTE: Only call when type is know to be successful state
    // #NOTE: Moves internal success state
    template<class T_Return> T_Return Result<T_Return>::operator*()&&{
        return std::get<T_Return>(std::move(m_result));
    } // #END: operator*()

// #DIV: Public Methods

    // #METHOD: error(), Const Method
    // #BRIEF: Get underlying error type
    // #THROWS: std::bad_variant_access, If result is not a error state
    // #NOTE: Only call when type is known to be error state
    template<class T_Return> const Error& Result<T_Return>::error()const{
        return std::get<Error>(m_result);
    } // #END: error()

// #END: Result<T_Return>


// #SCOPE: Result<void>

// #DIV: Public Factory Methods

    // #METHOD: Result(const Error&), Constructor
    // #BRIEF: Construct from error type
    // #PARAM: Error& p_error, Given error value 
    Result<void>::Result(const Error& p_error): m_result(p_error){

    } // #END: Result(const Error&)

    // #METHOD: Result(Error&&), Constructor
    // #BRIEF: Move construct from error type
    // #NOTE: This method takes ownership of given error
    // #PARAM: Error&& p_error, Moved error value
    Result<void>::Result(Error&& p_error): m_result(std::move(p_error)){

    } // #END: Result(Error&&)

// #DIV: Public Operators

    // #METHOD: operator bool(), Const Operator
    // #BRIEF: Check if result is successful state
    Result<void>::operator bool()const{
        return !m_result;
    } // #END: operator bool()

// #DIV: Public Methods

    // #METHOD: error(), Const Method
    // #BRIEF: Get underlying error type
    // #THROWS: std::bad_optional_access, If result is not a error state
    // #NOTE: Only call when type is known to be error state
    const Error& Result<void>::error()const{
        return *m_result;
    } // #END: error()

// #END: Result<void>

} // #END: docme::core
