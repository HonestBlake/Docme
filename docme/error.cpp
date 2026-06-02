module;

// #FILE: error.cpp, Component Source File
// #BRIEF: Source file for project error type component

#include "docme.hpp" // #INCLUDE: docme.hpp, Project Header File

module docme; // #IMPLEMENTS: docme, Component Module

import :error; // #IMPORT: error, Component Module Partition

namespace docme{ // #SCOPE: docme

// #SCOPE: Error

// #DIV: Public Factory Methods

    // #FUNCTION: Error(const Code, const std::string&), Constructor

    // #PARAM: p_code, Error code
    // #PARAM: p_body, Error body message
    Error::Error(const Code p_code, const std::string& p_body): code(p_code), body(p_body){

    } // #END: Error(const Code, const std::string&)

// #DIV: Public Operators

    // #FUNCTION: operator==(const Error::Code&), Equality Operator
    // #BRIEF: Checks if error code is equal to given code
    // #PARAM: p_code, Code to compare error code to
    // #RETURN: bool, True if error code is equal to given code, false otherwise
    bool Error::operator==(const Error::Code& p_code)const{
        return code == p_code;
    } // #END: operator==(const Error::Code&)

// #DIV: Public Methods

    // #FUNCTION: message(), Virtual Method
    // #BRIEF: Returns a constructed error message
    // #RETURN: std::string, Constructed error message
    std::string Error::message(){
        const std::string codeString = formatCode();
        return std::vformat(DEFAULT_MESSAGE_FORMAT, std::make_format_args(codeString, body));
    } // #END: message

    // #FUNCTION: addContext(std::string&&), Method
    // #BRIEF: Adds a string context to the error
    // #NOTE: Takes possession of the context string
    // #OVERLOAD: addContext(const std::string&)
    // #PARAM: p_context, Context string to add
    // #RETURN: Error&, Reference to current object
    Error& Error::addContext(std::string&& p_context){
        context.push_back(std::move(p_context));
        return *this;
    } // #END: addContext(std::string&&)

    // #FUNCTION: addContext(const std::string&), Method
    // #BRIEF: Adds a string context to the error
    // #OVERLOAD: addContext(std::string&&)
    // #PARAM: p_context, Context string to add
    // #RETURN: Error&, Reference to current object
    Error& Error::addContext(const std::string& p_context){
        context.push_back(p_context);
        return *this;
    } // #END: addContext(const std::string&)

// #DIV: Protected Methods

    // #FUNCTION: formatCode(), Method
    // #BRIEF: Formats the error code into a string
    // #RETURN: std::string, Formatted error code string
    std::string Error::formatCode(){
        const std::string codeString = std::to_string(code);
        return std::vformat(CODE_STRING_FORMAT, std::make_format_args(codeString));
    } // #END: formatCode()

// #END: Error

} // #END: docme