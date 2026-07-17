// #FILE: timer.cpp, Component Source File
// #BRIEF: Source file for timer component

module;

#include "core.hpp" // #INCLUDE: core.hpp, Package wide header

module docme.core; // #IMPLEMENTS: docme.core:timer
import :timer;

namespace docme::core{ // #SCOPE: docme::core

// ------------------------------------------------------------------------------
//                                class Timer
// ------------------------------------------------------------------------------

// #SCOPE: Timer

// #DIV: Public

// ---- Public Static Methods ----

    // #METHOD: start(const std::string_view), Static Method
    // #BRIEF: Starts a named timer
    // #ATTRIBUTE: [[nodiscard]]
    // #PARAM: const std::string_view p_name, Timer display name
    // #RETURN: Timer, Started named timer
    Timer Timer::start(const std::string_view p_name){
        return Timer(p_name);
    } // #END: start(const std::string_view)


// ---- Public Methods ----

    // #METHOD: reset(), Instance Method
    // #BRIEF: Resets the timer to the current time
    // #RETURN: Timer&, Reference to the timer instance
    Timer& Timer::reset(){
        m_start = Clock::now();
        m_end = m_start;
        m_running = true;
        return *this;
    } // #END: reset()

    // #METHOD: stop(), Instance Method
    // #BRIEF: Stops the timer and returns elapsed time
    // #RETURN: Timer&, Reference to the timer instance
    Timer& Timer::stop(){
        if(!m_running) return *this; // Timer already stopped
        m_end = Clock::now();
        m_running = false;
        return *this;
    } // #END: stop()

    // #METHOD: name(), Const Instance Method
    // #BRIEF: Returns the name of the timer
    // #ATTRIBUTE: [[nodiscard]]
    // #RETURN: const std::string&, Timer display name
    const std::string& Timer::name()const{
        return m_name;
    } // #END: name()

    // #METHOD: time(), Const Instance Method
    // #BRIEF: Returns the elapsed time as a Timer::Time struct
    // #ATTRIBUTE: [[nodiscard]]
    // #RETURN: Timer::Time, Elapsed time struct
    Timer::Time Timer::time()const{
        const TimePoint end = m_running ? Clock::now() : m_end;
        return Time{std::chrono::duration_cast<Duration>(end - m_start)};
    } // #END: time()


// #DIV: Private

// ---- Private Special Methods ----

    // #METHOD: Timer(const std::string_view), Constructor
    // #BRIEF: Starts a named reporting timer
    // #PARAM: const std::string_view p_name, Timer display name
    Timer::Timer(const std::string_view p_name): m_start(Clock::now()), m_end(m_start), m_name(p_name){

    } // #END: Timer(const std::string_view)


// ------------------------------------------------------------------------------
//                       struct Timer::Time
// ------------------------------------------------------------------------------

// #SCOPE: Timer::Time

// #DIV: Public

// ---- Public Methods ----

    // #METHOD: seconds(), Const Instance Method
    // #BRIEF: Returns the elapsed time in seconds
    // #ATTRIBUTE: [[nodiscard]]
    // #RETURN: double, Elapsed time in seconds
    double Timer::Time::seconds()const{
        return elapsed.count();
    } // #END: seconds()

    // #METHOD: milliseconds(), Const Instance Method
    // #BRIEF: Returns the elapsed time in milliseconds
    // #ATTRIBUTE: [[nodiscard]]
    // #RETURN: std::int64_t, Elapsed time in milliseconds
    std::int64_t Timer::Time::milliseconds()const{
        return std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count();
    } // #END: milliseconds()


// #END: Timer::Time

// #END: Timer

} // #END: docme::core
