// #FILE: result.tpp, Component Template Implementation File
// #BRIEF: Template definitions for result component.

#include <source_location>
#ifndef COMPILED_WITH_MODULE // Open in editor

module;

#include "core.hpp" // #INCLUDE: core.hpp, Package wide header

module docme.core; // #IMPLEMENTS: docme.core:result
import :result;

import :errors; // #IMPORT: docme.core:errors, Error type
import :warnings; // #IMPORT: docme.core:warnings, Project warning type
import :failure; // #IMPORT: docme.core:failure, Project failure type
import :success; // #IMPORT: docme.core:success, Project success type

#endif

namespace docme::core{ // #SCOPE: docme::core

// ------------------------------------------------------------------------------
//                            class Result<T_Success>
// ------------------------------------------------------------------------------

// #SCOPE: Result<T_Success>

// #DIV: Public

// ---- Public Factory Methods ----

    // #METHOD: Result(const std::source_location&), Default Constructor
    // #BRIEF: Construct from error type
    // #PARAM: const std::source_location& p_callSite = std::source_location::current(), Call site location should be left to default.
    template<class T_Success> Result<T_Success>::Result(const std::source_location& p_callSite): m_warnings(Warnings::pull(Warnings::hash(p_callSite))){

    } // #END: Result(const std::source_location&)

    // #METHOD: Result(const T_Success&), Constructor
    // #BRIEF: Construct from return type
    // #PARAM: const T_Success& p_success, Given success value
    // #PARAM: const std::source_location& p_callSite = std::source_location::current(), Call site location should be left to default.
    template<class T_Success> Result<T_Success>::Result(const T_Success& p_success, const std::source_location& p_callSite): m_warnings(Warnings::pull(Warnings::hash(p_callSite))), m_result(p_success){

    } // #END: Result(const T_Success&)

    // #METHOD: Result(T_Success&&), Constructor
    // #BRIEF: Move construct from return type
    // #NOTE: This method takes ownership of given return
    // #PARAM: T_Success&& p_return, Moved success value
    // #PARAM: const std::source_location& p_callSite = std::source_location::current(), Call site location should be left to default
    template<class T_Success> Result<T_Success>::Result(T_Success&& p_success, const std::source_location& p_callSite): m_warnings(Warnings::pull(Warnings::hash(p_callSite))), m_result(std::move(p_success)){

    } // #END: Result(T_Success&&)

    // #METHOD: Result(const Error&), Constructor
    // #BRIEF: Construct from error type
    // #PARAM: Error& p_error, Given error value
    // #PARAM: const std::source_location& p_callSite = std::source_location::current(), Call site location should be left to default
    template<class T_Success> Result<T_Success>::Result(const Error& p_error, const std::source_location& p_callSite): m_warnings(Warnings::pull(Warnings::hash(p_callSite))), m_result(p_error){

    } // #END: Result(const Error&)

    // #METHOD: Result(Error&&), Constructor
    // #BRIEF: Move construct from error type
    // #NOTE: This method takes ownership of given error
    // #PARAM: Error&& p_error, Moved error value
    // #PARAM: const std::source_location& p_callSite = std::source_location::current(), Call site location should be left to default
    template<class T_Success> Result<T_Success>::Result(Error&& p_error, const std::source_location& p_callSite): m_warnings(Warnings::pull(Warnings::hash(p_callSite))), m_result(std::move(p_error)){

    } // #END: Result(Error&&)

    // #METHOD: Result(Failure&&), Constructor
    // #BRIEF: Move construct from failure type
    // #NOTE: This method takes ownership of given failure
    // #PARAM: Failure&& p_failure, Moved failure value
    // #PARAM: const std::source_location& p_callSite = std::source_location::current(), Call site location should be left to default
    template<class T_Success> Result<T_Success>::Result(Failure&& p_failure, const std::source_location& p_callSite): m_warnings(Warnings::pull(Warnings::hash(p_callSite))), m_result(p_failure.takeValue()){
        Warnings::Buffer warnings = p_failure.takeWarnings();
        for(Warn& warning: warnings){
            m_warnings.emplace_back(std::move(warning));
        }
    } // #END: Result(Failure&&)


// ---- Public Operators ----

    // #METHOD: operator bool(), Const Operator
    // #BRIEF: Check if result is successful state
    template<class T_Success> Result<T_Success>::operator bool()const{
        return !isError();
    } // #END: operator bool()

    // #METHOD: operator*()const&, Const Operator
    // #BRIEF: Dereference operator to get successful state
    // #THROWS: std::bad_variant_access, If result is not a success state
    // #NOTE: Only call when type is know to be successful state
    template<class T_Success> const T_Success& Result<T_Success>::operator*()const&{
        return value();
    } // #END: operator*()

    // #METHOD: operator*()&&, Const Operator
    // #BRIEF: Dereference operator to get successful state
    // #THROWS: std::bad_variant_access, If result is not a success state
    // #NOTE: Only call when type is know to be successful state
    // #NOTE: Moves internal success state
    template<class T_Success> T_Success Result<T_Success>::operator*()&&{
        return takeValue();
    } // #END: operator*()


// ---- Public Methods ----

    // #METHOD: isError(), Const Instance Method
    // #BRIEF: Return if holds error.
    // #RETURN: bool, True if holds error, false otherwise.
    template<class T_Success> bool Result<T_Success>::isError()const{
        return std::holds_alternative<Error>(m_result);
    } // #END: isError()

    // #METHOD: hasWarnings(), Const Instance Method
    // #BRIEF: Returns if holds warnings.
    // #RETURN: bool, True if holds warnings, false otherwise.
    template<class T_Success> bool Result<T_Success>::hasWarnings()const{
        return !m_warnings.empty();
    } // #END: hasWarnings()

    // #METHOD: error(), Const Instance Method
    // #BRIEF: Get underlying error type
    // #THROWS: std::bad_variant_access, If result is not a error state
    // #NOTE: Only call when type is known to be error state
    template<class T_Success> const Error& Result<T_Success>::error()const{
        return std::get<Error>(m_result);
    } // #END: error()

    // #METHOD: warnings(), Const Instance Method
    // #BRIEF: Get underlying warnings buffer.
    // #RETURN: const Warnings::Buffer&, Warnings buffer.
    template<class T_Success> const Warnings::Buffer& Result<T_Success>::warnings()const{
        return m_warnings;
    } // #END: warnings()

    // #METHOD: warnings()&&, Instance Method
    // #BRIEF: Moves underlying warnings buffer out of object.
    // #NOTE: Moves internal state.
    // #RETURN: Warnings::Buffer, Moved warnings buffer.
    template<class T_Success> Warnings::Buffer Result<T_Success>::warnings()&&{
        return takeWarnings();
    } // #END: warnings()&&

    // #METHOD: takeWarnings(), Instance Method
    // #BRIEF: Moves underlying warnings buffer out of object.
    // #NOTE: Moves internal state.
    // #RETURN: Warnings::Buffer, Moved warnings buffer.
    template<class T_Success> Warnings::Buffer Result<T_Success>::takeWarnings(){
        return std::move(m_warnings);
    } // #END: takeWarnings()

    // #METHOD: failure(), Instance Method
    // #BRIEF: Moves error and warnings out of object into a failure state.
    // #NOTE: Moves internal state.
    // #RETURN: Failure, Constructed failure state
    template<class T_Success> Failure Result<T_Success>::failure(){
        return Failure(std::get<Error>(std::move(m_result)), std::move(m_warnings));
    } // #END: failure()

    // #METHOD: success(), Instance Method
    // #BRIEF: Moves warnings out of object into a success state.
    // #NOTE: Moves internal state.
    // #RETURN: Success<>, Constructed success state
    template<class T_Success> Success<> Result<T_Success>::success(){
        return Success<>(std::move(m_warnings));
    } // #END: success()

    // #METHOD: propagateWarnings(), Instance Method
    // #BRIEF: Move warnings back to warnings manager to propagate.
    // #NOTE: Moves internal state.
    // #PARAM: const std::source_location& p_callSite = std::source_location::current(), Call site location which should be left to default
    template<class T_Success> void Result<T_Success>::propagateWarnings(const std::source_location& p_callSite){
        for(Warn& warning: m_warnings){
            Warnings::add(std::move(warning), p_callSite);
        }
    } // #END: propagateWarnings()

    // #METHOD: value(), Const Instance Method
    // #BRIEF: Gets success type.
    // #RETURN: const T_Success&, Internal success type
    template<class T_Success> const T_Success& Result<T_Success>::value()const{
        return std::get<T_Success>(m_result);
    } // #END: value()

    // #METHOD: takeValue(), Instance Method
    // #BRIEF: Moves success type out of object.
    // #NOTE: Moves internal state.
    // #RETURN: T_Success, Internal success type
    template<class T_Success> T_Success Result<T_Success>::takeValue(){
        return std::move(std::get<T_Success>(m_result));
    } // #END: takeValue()

// #END: Result<T_Success>


// ------------------------------------------------------------------------------
//                               class Result<void>
// ------------------------------------------------------------------------------

// #SCOPE: Result<void>

// #DIV: Public

// ---- Public Factory Methods ----

    // #METHOD: Result(const std::source_location&), Default Constructor
    // #BRIEF: Construct from error type
    // #PARAM: const std::source_location& p_callSite = std::source_location::current(), Call site location should be left to default.
    Result<void>::Result(const std::source_location& p_callSite): m_warnings(Warnings::pull(Warnings::hash(p_callSite))){

    } // #END: Result(const std::source_location&)

    // #METHOD: Result(const Error&), Constructor
    // #BRIEF: Construct from error type
    // #PARAM: Error& p_error, Given error value
    // #PARAM: const std::source_location& p_callSite = std::source_location::current(), Call site location should be left to default.
    Result<void>::Result(const Error& p_error, const std::source_location& p_callSite): m_warnings(Warnings::pull(Warnings::hash(p_callSite))), m_error(p_error){

    } // #END: Result(const Error&)

    // #METHOD: Result(Error&&), Constructor
    // #BRIEF: Move construct from error type
    // #NOTE: This method takes ownership of given error
    // #PARAM: Error&& p_error, Moved error value
    // #PARAM: const std::source_location& p_callSite = std::source_location::current(), Call site location should be left to default.
    Result<void>::Result(Error&& p_error, const std::source_location& p_callSite): m_warnings(Warnings::pull(Warnings::hash(p_callSite))), m_error(std::move(p_error)){

    } // #END: Result(Error&&)

    // #METHOD: Result(Failure&&, const std::source_location& p_callSite), Constructor
    // #BRIEF: Construct from failure type.
    // #NOTE: This method takes ownership of given failure
    // #PARAM: Failure&& p_failure, Moved failure value
    // #PARAM: const std::source_location& p_callSite = std::source_location::current(), Call site location should be left to default
    Result<void>::Result(Failure&& p_failure, const std::source_location& p_callSite): m_warnings(Warnings::pull(Warnings::hash(p_callSite))), m_error(std::move(p_failure).takeValue()){
        Warnings::Buffer warnings = p_failure.takeWarnings();
        for(Warn& warning: warnings){
            m_warnings.emplace_back(std::move(warning));
        }
    } // #END: Result(Failure&&, const std::source_location&)


// ---- Public Operators ----

    // #METHOD: operator bool(), Const Operator
    // #BRIEF: Check if result is successful state
    Result<void>::operator bool()const{
        return !isError();
    } // #END: operator bool()


// ---- Public Methods ----

    // #METHOD: isError(), Const Instance Method
    // #BRIEF: Return if holds error.
    // #RETURN: bool, True if holds error, false otherwise.
    bool Result<void>::isError()const{
        return m_error.has_value();
    } // #END: isError()

    // #METHOD: hasWarnings(), Const Instance Method
    // #BRIEF: Returns if holds warnings.
    // #RETURN: bool, True if holds warnings, false otherwise.
    bool Result<void>::hasWarnings()const{
        return !m_warnings.empty();
    } // #END: hasWarnings()

    // #METHOD: error(), Const Instance Method
    // #BRIEF: Get underlying error type
    // #NOTE: Only call when type is known to be error state
    // #THROWS: std::bad_optional_access, If result is not a error state
    const Error& Result<void>::error()const{
        return *m_error;
    } // #END: error()

    // #METHOD: warnings(), Const Instance Method
    // #BRIEF: Get underlying warnings buffer.
    // #RETURN: const Warnings::Buffer&, Warnings buffer.
    const Warnings::Buffer& Result<void>::warnings()const{
        return m_warnings;
    } // #END: warnings()

    // #METHOD: warnings()&&, Instance Method
    // #BRIEF: Moves underlying warnings buffer out of object.
    // #NOTE: Moves internal state.
    // #RETURN: Warnings::Buffer, Moved warnings buffer.
    Warnings::Buffer Result<void>::warnings()&&{
        return takeWarnings();
    } // #END: warnings()&&

    // #METHOD: takeWarnings(), Instance Method
    // #BRIEF: Moves underlying warnings buffer out of object.
    // #NOTE: Moves internal state.
    // #RETURN: Warnings::Buffer, Moved warnings buffer.
    Warnings::Buffer Result<void>::takeWarnings(){
        return std::move(m_warnings);
    } // #END: takeWarnings()

    // #METHOD: failure(), Instance Method
    // #BRIEF: Moves error and warnings out of object into a failure state.
    // #NOTE: Moves internal state.
    // #RETURN: Failure, Constructed failure state
    Failure Result<void>::failure(){
        return Failure(std::move(*m_error), std::move(m_warnings));
    } // #END: failure()

    // #METHOD: success(), Instance Method
    // #BRIEF: Moves warnings out of object into a success state.
    // #NOTE: Moves internal state.
    // #RETURN: Success<>, Constructed success state
    Success<> Result<void>::success(){
        return Success<>(std::move(m_warnings));
    } // #END: success()

    // #METHOD: propagateWarnings(), Instance Method
    // #BRIEF: Move warnings back to warnings manager to propagate.
    // #NOTE: Moves internal state.
    // #PARAM: const std::source_location& p_callSite = std::source_location::current(), Call site location which should be left to default
    void Result<void>::propagateWarnings(const std::source_location& p_callSite){
        for(Warn& warning: m_warnings){
            Warnings::add(std::move(warning), p_callSite);
        }
    } // #END: propagateWarnings()


// #END: Result<void>

} // #END: docme::core
