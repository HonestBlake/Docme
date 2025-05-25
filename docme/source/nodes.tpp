// #file: nodes.tpp, template implementation file

#pragma once

#include "nodes.hpp"

namespace worTech::docme::nodes{

// Node, template method definitions

// public factory methods

    // #func: Node::Node(T_name&&, T_type&&), public template constructor
    // #template: StringType T_name, Type of p_name param
    // #template: StringType T_type, Type of p_type param
    // #param: T_name&& p_name, Name of node taken as a universal reference
    // #param: T_type&& p_type, Type of node taken as a universal reference
    // #note: All arguments are taken as a universal reference, taking ownership when a rvalue reference is passed to them
    template<StringType T_name, StringType T_type> Node::Node(T_name&& p_name, T_type&& p_type): m_name(std::forward<T_name>(p_name)), m_type(std::forward<T_type>(p_type)){
        if constexpr(state::TRACING){ // Function tracing
            debug::trace();
        }
    }

} // namespace worTech::docme::nodes