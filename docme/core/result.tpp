// #FILE: result.tpp, Component Template Implementation File
// #BRIEF: Template definitions for result component.

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

// ---- Public Special Methods ----

    // #METHOD: Result(const std_loc&), Default Constructor
    // #BRIEF: Construct from error type
    // #PARAM: const std_loc& p_callSite = std_loc::current(), Call site location should be left to default.
    template<class T_Success> Result<T_Success>::Result(const std_loc& p_callSite): m_warnings(Warning::pull(Warning::hash(p_callSite))){

    } // #END: Result(const std_loc&)

    // #METHOD: Result(const T_Success&), Constructor
    // #BRIEF: Construct from return type
    // #PARAM: const T_Success& p_success, Given success value
    // #PARAM: const std_loc& p_callSite = std_loc::current(), Call site location should be left to default.
    template<class T_Success> Result<T_Success>::Result(const T_Success& p_success, const std_loc& p_callSite): m_warnings(Warning::pull(Warning::hash(p_callSite))), m_result(p_success){

    } // #END: Result(const T_Success&)

    // #METHOD: Result(T_Success&&), Constructor
    // #BRIEF: Move construct from return type
    // #NOTE: This method takes ownership of given return
    // #PARAM: T_Success&& p_return, Moved success value
    // #PARAM: const std_loc& p_callSite = std_loc::current(), Call site location should be left to default
    template<class T_Success> Result<T_Success>::Result(T_Success&& p_success, const std_loc& p_callSite): m_warnings(Warning::pull(Warning::hash(p_callSite))), m_result(std::move(p_success)){

    } // #END: Result(T_Success&&)

    // #METHOD: Result(const Error&), Constructor
    // #BRIEF: Construct from error type
    // #PARAM: Error& p_error, Given error value
    // #PARAM: const std_loc& p_callSite = std_loc::current(), Call site location should be left to default
    template<class T_Success> Result<T_Success>::Result(const Error& p_error, const std_loc& p_callSite): m_warnings(Warning::pull(Warning::hash(p_callSite))), m_result(p_error){

    } // #END: Result(const Error&)

    // #METHOD: Result(Error&&), Constructor
    // #BRIEF: Move construct from error type
    // #NOTE: This method takes ownership of given error
    // #PARAM: Error&& p_error, Moved error value
    // #PARAM: const std_loc& p_callSite = std_loc::current(), Call site location should be left to default
    template<class T_Success> Result<T_Success>::Result(Error&& p_error, const std_loc& p_callSite): m_warnings(Warning::pull(Warning::hash(p_callSite))), m_result(std::move(p_error)){

    } // #END: Result(Error&&)

    // #METHOD: Result(Failure&&), Constructor
    // #BRIEF: Move construct from failure type
    // #NOTE: This method takes ownership of given failure
    // #PARAM: Failure&& p_failure, Moved failure value
    // #PARAM: const std_loc& p_callSite = std_loc::current(), Call site location should be left to default
    template<class T_Success> Result<T_Success>::Result(Failure&& p_failure, const std_loc& p_callSite): m_warnings(Warning::pull(Warning::hash(p_callSite))), m_result(p_failure.takeValue()){
        std::vector<Warning> warnings = p_failure.takeWarnings();
        for(Warning& warning: warnings){
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
        return std::get<T_Success>(m_result);
    } // #END: operator*()

    // #METHOD: operator*()&&, Const Operator
    // #BRIEF: Dereference operator to get successful state
    // #THROWS: std::bad_variant_access, If result is not a success state
    // #NOTE: Only call when type is know to be successful state
    // #NOTE: Moves internal success state
    template<class T_Success> T_Success Result<T_Success>::operator*()&&{
        return std::move(std::get<T_Success>(m_result));
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
    // #RETURN: const std::vector<Warning>&, Warning buffer.
    template<class T_Success> const std::vector<Warning>& Result<T_Success>::warnings()const{
        return m_warnings;
    } // #END: warnings()

    // #METHOD: warnings()&&, Instance Method
    // #BRIEF: Moves underlying warnings buffer out of object.
    // #NOTE: Moves internal state.
    // #RETURN: std::vector<Warning>, Moved warnings buffer.
    template<class T_Success> std::vector<Warning> Result<T_Success>::warnings()&&{
        return takeWarnings();
    } // #END: warnings()&&

    // #METHOD: takeWarnings(), Instance Method
    // #BRIEF: Moves underlying warnings buffer out of object.
    // #NOTE: Moves internal state.
    // #RETURN: std::vector<Warning>, Moved warnings buffer.
    template<class T_Success> std::vector<Warning> Result<T_Success>::takeWarnings(){
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
    // #PARAM: const std_loc& p_callSite = std_loc::current(), Call site location which should be left to default
    // #RETURN: Result<T_Success>&, Reference to self
    template<class T_Success> Result<T_Success>& Result<T_Success>::propagateWarnings(const std_loc& p_callSite){
        for(Warning& warning: m_warnings){
            Warning::propagate(std::move(warning), p_callSite);
        }
        m_warnings.clear();
        return *this;
    } // #END: propagateWarnings()
    // #METHOD: value(), Const Instance Method
    // #BRIEF: Gets success type.
    // #RETURN: const T_Success&, Internal success type
    template<class T_Success> const T_Success& Result<T_Success>::value()const{
        return std::get<T_Success>(m_result);
    } // #END: value()

    // #METHOD: takeValue(), Instance Method
    // #BRIEF: Takes success type and propagates warnings.
    // #NOTE: Moves internal state.
    // #PARAM: const std_loc& p_callSite = std_loc::current(), Call site location which should be left to default
    // #RETURN: T_Success, Internal success type
    template<class T_Success> T_Success Result<T_Success>::takeValue(const std_loc& p_callSite){
        propagateWarnings(p_callSite);
        return std::move(std::get<T_Success>(m_result));
    } // #END: takeValue()

// #END: Result<T_Success>


// ------------------------------------------------------------------------------
//                               class Result<void>
// ------------------------------------------------------------------------------

// #SCOPE: Result<void>

// #DIV: Public

// ---- Public Special Methods ----

    // #METHOD: Result(const std_loc&), Default Constructor
    // #BRIEF: Construct from error type
    // #PARAM: const std_loc& p_callSite = std_loc::current(), Call site location should be left to default.
    Result<void>::Result(const std_loc& p_callSite): m_warnings(Warning::pull(Warning::hash(p_callSite))){

    } // #END: Result(const std_loc&)

    // #METHOD: Result(const Error&), Constructor
    // #BRIEF: Construct from error type
    // #PARAM: Error& p_error, Given error value
    // #PARAM: const std_loc& p_callSite = std_loc::current(), Call site location should be left to default.
    Result<void>::Result(const Error& p_error, const std_loc& p_callSite): m_warnings(Warning::pull(Warning::hash(p_callSite))), m_error(p_error){

    } // #END: Result(const Error&)

    // #METHOD: Result(Error&&), Constructor
    // #BRIEF: Move construct from error type
    // #NOTE: This method takes ownership of given error
    // #PARAM: Error&& p_error, Moved error value
    // #PARAM: const std_loc& p_callSite = std_loc::current(), Call site location should be left to default.
    Result<void>::Result(Error&& p_error, const std_loc& p_callSite): m_warnings(Warning::pull(Warning::hash(p_callSite))), m_error(std::move(p_error)){

    } // #END: Result(Error&&)

    // #METHOD: Result(Failure&&, const std_loc& p_callSite), Constructor
    // #BRIEF: Construct from failure type.
    // #NOTE: This method takes ownership of given failure
    // #PARAM: Failure&& p_failure, Moved failure value
    // #PARAM: const std_loc& p_callSite = std_loc::current(), Call site location should be left to default
    Result<void>::Result(Failure&& p_failure, const std_loc& p_callSite): m_warnings(Warning::pull(Warning::hash(p_callSite))), m_error(std::move(p_failure).takeValue()){
        std::vector<Warning> warnings = p_failure.takeWarnings();
        for(Warning& warning: warnings){
            m_warnings.emplace_back(std::move(warning));
        }
    } // #END: Result(Failure&&, const std_loc&)


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
    // #RETURN: const std::vector<Warning>&, Warning buffer.
    const std::vector<Warning>& Result<void>::warnings()const{
        return m_warnings;
    } // #END: warnings()

    // #METHOD: warnings()&&, Instance Method
    // #BRIEF: Moves underlying warnings buffer out of object.
    // #NOTE: Moves internal state.
    // #RETURN: std::vector<Warning>, Moved warnings buffer.
    std::vector<Warning> Result<void>::warnings()&&{
        return takeWarnings();
    } // #END: warnings()&&

    // #METHOD: takeWarnings(), Instance Method
    // #BRIEF: Moves underlying warnings buffer out of object.
    // #NOTE: Moves internal state.
    // #RETURN: std::vector<Warning>, Moved warnings buffer.
    std::vector<Warning> Result<void>::takeWarnings(){
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
    // #PARAM: const std_loc& p_callSite = std_loc::current(), Call site location which should be left to default
    Result<void>& Result<void>::propagateWarnings(const std_loc& p_callSite){
        for(Warning& warning: m_warnings){
            Warning::propagate(std::move(warning), p_callSite);
        }
        m_warnings.clear();
        return *this;
    } // #END: propagateWarnings()


// #END: Result<void>

} // #END: docme::core
