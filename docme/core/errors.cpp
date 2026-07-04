// #FILE: errors.cpp, Component Source File
// #BRIEF: Source file for project errors component

module;

#include "core.hpp" // #INCLUDE: core.hpp, Package wide header

module docme.core; // #IMPLEMENTS: docme.core:errors
import :errors; 

namespace docme::core{ // #SCOPE: docme::core

// ------------------------------------------------------------------------------
//                                  class Error
// ------------------------------------------------------------------------------

// #SCOPE: Error

// #DIV: Public

// ---- Public Factory Methods ----

    // #METHOD: Error(const std::string&, const std::string&), Constructor

    // #PARAM: const std::string& p_codeFormat, Format for error code
    // #PARAM: const std::string& p_messageFormat, Format for message
    Error::Error(const std::string& p_codeFormat, const std::string& p_messageFormat): m_codeFormat(p_codeFormat), m_messageFormat(p_messageFormat){

    } // #END: Error(const Code, const std::string&)

// ---- Public Operators ----

    // #METHOD: operator==(const Error::Code&), Operator
    // #BRIEF: Checks if error code is equal to given code
    // #PARAM: p_code, Code to compare error code to
    // #RETURN: bool, True if error code is equal to given code, false otherwise
    bool Error::operator==(const Error::Code& p_code)const{
        return code == p_code;
    } // #END: operator==(const Error::Code&)

    // #METHOD: operator!=(const Error::Code&), Operator
    // #BRIEF: Checks if error code is not equal to given code
    // #PARAM: p_code, Code to compare error code to
    // #RETURN: bool, True if error code is not
    bool Error::operator!=(const Error::Code& p_code)const{
        return code != p_code;
    } // #END: operator!=(const Error::Code&)

// ---- Public Methods ----

    // #METHOD: message(), Const Instance Method
    // #BRIEF: Returns a constructed error message
    // #RETURN: std::string, Constructed error message
    std::string Error::message()const{
        return formatMessage();
    } // #END: message

// #DIV: Protected

// ---- Protected Methods ----

    // #METHOD: formatCode(), Const Instance Method
    // #BRIEF: Formats the error code into a string
    // #RETURN: std::string, Formatted error code string
    std::string Error::formatCode()const{
        const std::string codeString = std::to_string(code);
        return std::vformat(m_codeFormat, std::make_format_args(codeString));
    } // #END: formatCode()

    // #METHOD: formatMessage(), Const Instance Method
    // #BRIEF: Formats the error code and body
    // #RETURN: std::string, Formatted message
    std::string Error::formatMessage()const{
        const std::string formattedCode = formatCode();
        return std::vformat(m_messageFormat, std::make_format_args(formattedCode, body));
    } // #END: formatCode()

// #END: Error

} // #END: docme::core
