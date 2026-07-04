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

// ---- Public Factory Methods ----

    // #METHOD: Failure(Error&&, Warnings::Buffer&&), Constructor
    // #BRIEF: Takes error and warnings and constructs a failure object.
    // #PARAM: Error&& p_error, Error state to move
    // #PARAM: Warnings::Buffer&& p_warnings, Warnings to move
    Failure::Failure(Error&& p_error, Warnings::Buffer&& p_warnings): m_error(std::move(p_error)), m_warnings(std::move(p_warnings)){

    } // #END: Failure(Error&&, Warnings::Buffer&&)

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
    // #RETURN: const Warnings::Buffer&, Warnings buffer
    const Warnings::Buffer& Failure::warnings()const{
        return m_warnings;
    } // #END: warnings()

    // #METHOD: warnings()&&, Instance Method
    // #BRIEF: Moves underlying warnings buffer out of object.
    // #NOTE: Moves internal state.
    // #RETURN: Warnings::Buffer, Moved warnings buffer
    Warnings::Buffer Failure::warnings()&&{
        return takeWarnings();
    } // #END: warnings()&&

    // #METHOD: takeWarnings(), Instance Method
    // #BRIEF: Moves underlying warnings buffer out of object.
    // #NOTE: Moves internal state.
    // #RETURN: Warnings::Buffer, Moved warnings buffer
    Warnings::Buffer Failure::takeWarnings(){
        return std::move(m_warnings);
    } // #END: takeWarnings()

    // #METHOD: propagateWarnings(), Instance Method
    // #BRIEF: Moves warnings out of object into global warning state.
    // #NOTE: Moves internal state.
    // #PARAM: const std::source_location& p_callSite = std::source_location::current(), Call site location which should be left to default
    void Failure::propagateWarnings(const std::source_location& p_callSite){
        for(Warn& warning: m_warnings){
            Warnings::add(std::move(warning), p_callSite);
        }
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