// #FILE: success.cpp, Component Source File
// #BRIEF: Source file for success component.

module;

#include "core.hpp" // #INCLUDE: core.hpp, Package wide header

module docme.core; // #IMPLEMENTS: docme.core:success
import :success;

namespace docme::core{ // #SCOPE: docme::core

// ------------------------------------------------------------------------------
//                              class Success<void>
// ------------------------------------------------------------------------------

// #SCOPE: Success<void>

// #DIV: Public

// ---- Public Special Methods ----

    // #METHOD: Success(const std_loc&), Constructor
    // #BRIEF: Constructs a success object from a call site location.
    // #PARAM: const std_loc& p_callSite = std_loc::current(), Call site location which should be left to default
    Success<void>::Success(const std_loc& p_callSite): m_warnings(Warning::pull(Warning::hash(p_callSite))){

    } // #END: Success(const std_loc&)

    // #METHOD: Success(std::vector<Warning>&&), Constructor
    // #BRIEF: Takes warnings and constructs a success object.
    // #PARAM: std::vector<Warning>&& p_warnings, Warning buffer to move
    Success<void>::Success(std::vector<Warning>&& p_warnings): m_warnings(std::move(p_warnings)){

    } // #END: Success(std::vector<Warning>&&)

// ---- Public Methods ----

    // #METHOD: hasWarnings(), Const Instance Method
    // #BRIEF: Returns if holds warnings.
    // #RETURN: bool, True if holds warnings, false otherwise
    bool Success<void>::hasWarnings()const{
        return !m_warnings.empty();
    } // #END: hasWarnings()

    // #METHOD: warnings(), Const Instance Method
    // #BRIEF: Get underlying warnings buffer.
    // #RETURN: const std::vector<Warning>&, Warning buffer
    const std::vector<Warning>& Success<void>::warnings()const{
        return m_warnings;
    } // #END: warnings()

    // #METHOD: warnings()&&, Instance Method
    // #BRIEF: Moves underlying warnings buffer out of object.
    // #NOTE: Moves internal state.
    // #RETURN: std::vector<Warning>, Moved warnings buffer
    std::vector<Warning> Success<void>::warnings()&&{
        return takeWarnings();
    } // #END: warnings()&&

    // #METHOD: takeWarnings(), Instance Method
    // #BRIEF: Moves underlying warnings buffer out of object.
    // #NOTE: Moves internal state.
    // #RETURN: std::vector<Warning>, Moved warnings buffer
    std::vector<Warning> Success<void>::takeWarnings(){
        return std::move(m_warnings);
    } // #END: takeWarnings()

    // #METHOD: propagateWarnings(), Instance Method
    // #BRIEF: Moves warnings out of object to global buffer.
    // #NOTE: Moves internal state.
    // #PARAM: const std_loc& p_callSite = std_loc::current(), Call site location which should be left to default
    void Success<void>::propagateWarnings(const std_loc& p_callSite){
        for(Warning& warning: m_warnings){
            Warning::propagate(std::move(warning), p_callSite);
        }
        m_warnings.clear();
    } // #END: propagateWarnings()

// #END: Success<void>

} // #END: docme::core