// #FILE: success.cpp, Component Source File
// #BRIEF: Source file for success component.

module;

#include "core.hpp" // #INCLUDE: core.hpp, Package wide header

module docme.core; // #IMPLEMENTS: docme.core:success
import :success;

namespace docme::core{ // #SCOPE: docme::core

// ------------------------------------------------------------------------------
//                            class Success<T_Success>
// ------------------------------------------------------------------------------

// #SCOPE: Success<T_Success>

// #DIV: Public

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
        return takeValue();
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
    // #RETURN: const Warnings::Buffer&, Warnings buffer
    template<class T_Success> const Warnings::Buffer& Success<T_Success>::warnings()const{
        return m_warnings;
    } // #END: warnings()

    // #METHOD: warnings()&&, Instance Method
    // #BRIEF: Moves underlying warnings buffer out of object.
    // #NOTE: Moves internal state.
    // #RETURN: Warnings::Buffer, Moved warnings buffer
    template<class T_Success> Warnings::Buffer Success<T_Success>::warnings()&&{
        return takeWarnings();
    } // #END: warnings()&&

    // #METHOD: takeWarnings(), Instance Method
    // #BRIEF: Moves underlying warnings buffer out of object.
    // #NOTE: Moves internal state.
    // #RETURN: Warnings::Buffer, Moved warnings buffer
    template<class T_Success> Warnings::Buffer Success<T_Success>::takeWarnings(){
        return std::move(m_warnings);
    } // #END: takeWarnings()

    // #METHOD: propagateWarnings(), Instance Method
    // #BRIEF: Moves warnings out of object to global buffer.
    // #NOTE: Moves internal state.
    // #PARAM: const std::source_location& p_callSite = std::source_location::current(), Call site location which should be left to default
    template<class T_Success> void Success<T_Success>::propagateWarnings(const std::source_location& p_callSite){
        for(Warn& warning: m_warnings){
            Warnings::add(std::move(warning), p_callSite);
        }
    } // #END: propagateWarnings()

    // #METHOD: value(), Const Instance Method
    // #BRIEF: Gets success value.
    // #RETURN: const T_Success&, Success value
    template<class T_Success> const T_Success& Success<T_Success>::value()const{
        return m_success;
    } // #END: value()

    // #METHOD: takeValue(), Instance Method
    // #BRIEF: Moves success value out of object.
    // #NOTE: Moves internal state.
    // #RETURN: T_Success, Moved success value
    template<class T_Success> T_Success Success<T_Success>::takeValue(){
        return std::move(m_success);
    } // #END: takeValue()

// #END: Success<T_Success>


// ------------------------------------------------------------------------------
//                              class Success<void>
// ------------------------------------------------------------------------------

// #SCOPE: Success<void>

// #DIV: Public

// ---- Public Factory Methods ----

    // #METHOD: Success(const std::source_location&), Constructor
    // #BRIEF: Constructs a success object from a call site location.
    // #PARAM: const std::source_location& p_callSite = std::source_location::current(), Call site location which should be left to default
    Success<void>::Success(const std::source_location& p_callSite): m_warnings(Warnings::pull(Warnings::hash(p_callSite))){

    } // #END: Success(const std::source_location&)

    // #METHOD: Success(Warnings::Buffer&&), Constructor
    // #BRIEF: Takes warnings and constructs a success object.
    // #PARAM: Warnings::Buffer&& p_warnings, Warnings to move
    Success<void>::Success(Warnings::Buffer&& p_warnings): m_warnings(std::move(p_warnings)){

    } // #END: Success(Warnings::Buffer&&)

// ---- Public Methods ----

    // #METHOD: hasWarnings(), Const Instance Method
    // #BRIEF: Returns if holds warnings.
    // #RETURN: bool, True if holds warnings, false otherwise
    bool Success<void>::hasWarnings()const{
        return !m_warnings.empty();
    } // #END: hasWarnings()

    // #METHOD: warnings(), Const Instance Method
    // #BRIEF: Get underlying warnings buffer.
    // #RETURN: const Warnings::Buffer&, Warnings buffer
    const Warnings::Buffer& Success<void>::warnings()const{
        return m_warnings;
    } // #END: warnings()

    // #METHOD: warnings()&&, Instance Method
    // #BRIEF: Moves underlying warnings buffer out of object.
    // #NOTE: Moves internal state.
    // #RETURN: Warnings::Buffer, Moved warnings buffer
    Warnings::Buffer Success<void>::warnings()&&{
        return takeWarnings();
    } // #END: warnings()&&

    // #METHOD: takeWarnings(), Instance Method
    // #BRIEF: Moves underlying warnings buffer out of object.
    // #NOTE: Moves internal state.
    // #RETURN: Warnings::Buffer, Moved warnings buffer
    Warnings::Buffer Success<void>::takeWarnings(){
        return std::move(m_warnings);
    } // #END: takeWarnings()

    // #METHOD: propagateWarnings(), Instance Method
    // #BRIEF: Moves warnings out of object to global buffer.
    // #NOTE: Moves internal state.
    // #PARAM: const std::source_location& p_callSite = std::source_location::current(), Call site location which should be left to default
    void Success<void>::propagateWarnings(const std::source_location& p_callSite){
        for(Warn& warning: m_warnings){
            Warnings::add(std::move(warning), p_callSite);
        }
    } // #END: propagateWarnings()

// #END: Success<void>

} // #END: docme::core