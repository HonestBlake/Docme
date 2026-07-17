// #FILE: success.tpp, Component Template Implementation File
// #BRIEF: Template definitions for success component.

#ifndef COMPILED_WITH_MODULE // Open in editor

module;

#include "core.hpp" // #INCLUDE: core.hpp, Package wide header

module docme.core; // #IMPLEMENTS: docme.core:success
import :success;

import :warnings; // #IMPORT: docme.core:warnings, Project warning type

#endif

namespace docme::core{ // #SCOPE: docme::core

// ------------------------------------------------------------------------------
//                            class Success<T_Success>
// ------------------------------------------------------------------------------

// #SCOPE: Success<T_Success>

// #DIV: Public

// ---- Public Special Methods ----

    // #METHOD: Success(const T_Success&, const std_loc&), Constructor
    // #BRIEF: Copy constructs a success object from a success value.
    // #PARAM: const T_Success& p_success, Success value to copy
    // #PARAM: const std_loc& p_callSite = std_loc::current(), Call site location which should be left to default
    template<class T_Success> Success<T_Success>::Success(const T_Success& p_success, const std_loc& p_callSite): m_success(p_success), m_warnings(Warning::pull(Warning::hash(p_callSite))){

    } // #END: Success(const T_Success&, const std_loc&)

    // #METHOD: Success(T_Success&&, const std_loc&), Constructor
    // #BRIEF: Move constructs a success object from a success value.
    // #NOTE: This method takes ownership of given success value.
    // #PARAM: T_Success&& p_success, Success value to move
    // #PARAM: const std_loc& p_callSite = std_loc::current(), Call site location which should be left to default
    template<class T_Success> Success<T_Success>::Success(T_Success&& p_success, const std_loc& p_callSite): m_success(std::move(p_success)), m_warnings(Warning::pull(Warning::hash(p_callSite))){

    } // #END: Success(T_Success&&, const std_loc&)

// ---- Public Operators ----

    // #METHOD: operator*()const&, Const Operator
    // #BRIEF: Dereference operator to get success value.
    // #RETURN: const T_Success&, Success value
    template<class T_Success> const T_Success& Success<T_Success>::operator*()const&{
        return value();
    } // #END: operator*()

    // #METHOD: operator*()&&, Operator
    // #BRIEF: Dereference operator to move success value out of object.
    // #NOTE: Moves internal state.
    // #RETURN: T_Success, Moved success value
    template<class T_Success> T_Success Success<T_Success>::operator*()&&{
        return std::move(m_success);
    } // #END: operator*()


// ---- Public Methods ----

    // #METHOD: hasWarnings(), Const Instance Method
    // #BRIEF: Returns if holds warnings.
    // #RETURN: bool, True if holds warnings, false otherwise
    template<class T_Success> bool Success<T_Success>::hasWarnings()const{
        return !m_warnings.empty();
    } // #END: hasWarnings()

    // #METHOD: warnings(), Const Instance Method
    // #BRIEF: Get underlying warnings buffer.
    // #RETURN: const std::vector<Warning>&, Warning buffer
    template<class T_Success> const std::vector<Warning>& Success<T_Success>::warnings()const{
        return m_warnings;
    } // #END: warnings()

    // #METHOD: warnings()&&, Instance Method
    // #BRIEF: Moves underlying warnings buffer out of object.
    // #NOTE: Moves internal state.
    // #RETURN: std::vector<Warning>, Moved warnings buffer
    template<class T_Success> std::vector<Warning> Success<T_Success>::warnings()&&{
        return takeWarnings();
    } // #END: warnings()&&

    // #METHOD: takeWarnings(), Instance Method
    // #BRIEF: Moves underlying warnings buffer out of object.
    // #NOTE: Moves internal state.
    // #RETURN: std::vector<Warning>, Moved warnings buffer
    template<class T_Success> std::vector<Warning> Success<T_Success>::takeWarnings(){
        return std::move(m_warnings);
    } // #END: takeWarnings()

    // #METHOD: propagateWarnings(), Instance Method
    // #BRIEF: Moves warnings out of object to global buffer.
    // #NOTE: Moves internal state.
    // #PARAM: const std_loc& p_callSite = std_loc::current(), Call site location which should be left to default
    template<class T_Success> void Success<T_Success>::propagateWarnings(const std_loc& p_callSite){
        for(Warning& warning: m_warnings){
            Warning::propagate(std::move(warning), p_callSite);
        }
        m_warnings.clear();
    } // #END: propagateWarnings()

    // #METHOD: value(), Const Instance Method
    // #BRIEF: Gets success value.
    // #RETURN: const T_Success&, Success value
    template<class T_Success> const T_Success& Success<T_Success>::value()const{
        return m_success;
    } // #END: value()

    // #METHOD: takeValue(), Instance Method
    // #BRIEF: Moves success value out of object and propagates warnings.
    // #NOTE: Moves internal state.
    // #PARAM: const std_loc& p_callSite = std_loc::current(), Call site location which should be left to default
    // #RETURN: T_Success, Moved success value
    template<class T_Success> T_Success Success<T_Success>::takeValue(const std_loc& p_callSite){
        propagateWarnings(p_callSite);
        return std::move(m_success);
    } // #END: takeValue()

// #END: Success<T_Success>

} // #END: docme::core
