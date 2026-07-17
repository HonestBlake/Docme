// #FILE: failure.cpp, Component Source File
// #BRIEF: Source file for failure component.

module;

#include "core.hpp" // #INCLUDE: core.hpp, Package wide header

module docme.core; // #IMPLEMENTS: docme.core:failure
import :failure;

namespace docme::core{ // #SCOPE: docme::core

// ------------------------------------------------------------------------------
//                                 class Failure
// ------------------------------------------------------------------------------

// #SCOPE: Failure

// #DIV: Public

// ---- Public Special Methods ----

    // #METHOD: Failure(Error&&, std::vector<Warning>&&), Constructor
    // #BRIEF: Takes error and warnings and constructs a failure object.
    // #PARAM: Error&& p_error, Error state to move
    // #PARAM: std::vector<Warning>&& p_warnings, Warning buffer to move
    Failure::Failure(Error&& p_error, std::vector<Warning>&& p_warnings): m_error(std::move(p_error)), m_warnings(std::move(p_warnings)){

    } // #END: Failure(Error&&, std::vector<Warning>&&)

// ---- Public Operators ----

    // #METHOD: operator*()const&, Const Operator
    // #BRIEF: Dereference operator to get error value.
    // #RETURN: const Error&, Error value
    const Error& Failure::operator*()const&{
        return value();
    } // #END: operator*()

    // #METHOD: operator*()&&, Operator
    // #BRIEF: Dereference operator to move error value out of object.
    // #NOTE: Moves internal state.
    // #RETURN: Error, Moved error value
    Error Failure::operator*()&&{
        return takeValue();
    } // #END: operator*()&&


// ---- Public Methods ----

    // #METHOD: hasWarnings(), Const Instance Method
    // #BRIEF: Returns if holds warnings.
    // #RETURN: bool, True if holds warnings, false otherwise
    bool Failure::hasWarnings()const{
        return !m_warnings.empty();
    } // #END: hasWarnings()

    // #METHOD: error(), Const Instance Method
    // #BRIEF: Get underlying error type.
    // #RETURN: const Error&, Error type
    const Error& Failure::error()const{
        return m_error;
    } // #END: error()

    // #METHOD: warnings(), Const Instance Method
    // #BRIEF: Get underlying warnings buffer.
    // #RETURN: const std::vector<Warning>&, Warning buffer
    const std::vector<Warning>& Failure::warnings()const{
        return m_warnings;
    } // #END: warnings()

    // #METHOD: warnings()&&, Instance Method
    // #BRIEF: Moves underlying warnings buffer out of object.
    // #NOTE: Moves internal state.
    // #RETURN: std::vector<Warning>, Moved warnings buffer
    std::vector<Warning> Failure::warnings()&&{
        return takeWarnings();
    } // #END: warnings()&&

    // #METHOD: takeWarnings(), Instance Method
    // #BRIEF: Moves underlying warnings buffer out of object.
    // #NOTE: Moves internal state.
    // #RETURN: std::vector<Warning>, Moved warnings buffer
    std::vector<Warning> Failure::takeWarnings(){
        return std::move(m_warnings);
    } // #END: takeWarnings()

    // #METHOD: propagateWarnings(), Instance Method
    // #BRIEF: Moves warnings out of object into global warning state.
    // #NOTE: Moves internal state.
    // #PARAM: const std_loc& p_callSite = std_loc::current(), Call site location which should be left to default
    void Failure::propagateWarnings(const std_loc& p_callSite){
        for(Warning& warning: m_warnings){
            Warning::propagate(std::move(warning), p_callSite);
        }
        m_warnings.clear();
    } // #END: propagateWarnings()

    // #METHOD: value(), Const Instance Method
    // #BRIEF: Gets error type.
    // #RETURN: const Error&, Internal error type
    const Error& Failure::value()const{
        return m_error;
    } // #END: value()

    // #METHOD: takeValue(), Instance Method
    // #BRIEF: Moves error type out of object.
    // #NOTE: Moves internal state.
    // #RETURN: Error, Internal error type
    Error Failure::takeValue(){
        return std::move(m_error);
    } // #END: takeValue()

// #END: Failure

} // #END: docme::core
