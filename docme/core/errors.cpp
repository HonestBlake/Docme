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

// ---- Public Special Methods ----

    // #METHOD: Error(const std::unordered_map<Code, std::string>&, const Code, std::format_args), Constructor
    // #BRIEF: Constructs Error from a message lookup table, error code, and context args
    // #PARAM: const std::unordered_map<Code, std::string>& p_errorMessages, Error message lookup table
    // #PARAM: const Code p_code, Error code
    // #PARAM: std::format_args p_contextArgs, Context format arguments
    Error::Error(const std::unordered_map<Code, std::string>& p_errorMessages, const Code p_code, std::format_args p_contextArgs): code(p_code), body(getErrorMessage(p_errorMessages, code, p_contextArgs)){

    } // #END: Error(const std::unordered_map<Code, std::string>&, const Code, std::format_args)

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

// ---- Protected Static Methods ----

    // #METHOD: getErrorMessage(const std::unordered_map<Code, std::string>&, const Code, std::format_args), Protected Static Method
    // #BRIEF: Gets the formatted error message body for a given error code
    // #PARAM: const std::unordered_map<Code, std::string>& p_errorMessages, Error message lookup table
    // #PARAM: const Code p_code, Error code for message lookup
    // #PARAM: std::format_args p_contextArgs, Context format arguments
    // #RETURN: std::string, Error message body
    std::string Error::getErrorMessage(const std::unordered_map<Code, std::string>& p_errorMessages, const Code p_code, std::format_args p_contextArgs){
        if(p_code == DOCME_INTERNAL) return std::vformat(INTERNAL_ERROR_MESSAGE, p_contextArgs); // Special case for internal error code
        if(auto it = p_errorMessages.find(p_code); it != p_errorMessages.end()){
            return std::vformat(it->second, p_contextArgs);
        }
        return UNKNOWN_ERROR_MESSAGE;
    } // #END: getErrorMessage(const std::unordered_map<Code, std::string>&, const Code, std::format_args)

// ---- Protected Methods ----

    // #METHOD: formatCode(), Const Instance Method
    // #BRIEF: Formats the error code into a string
    // #RETURN: std::string, Formatted error code string
    std::string Error::formatCode()const{
        if(code == DOCME_INTERNAL) return INTERNAL_ERROR_STRING; // Special case for internal error code
        if(code == DOCME_ERROR) return ANONYMOUS_ERROR_STRING; // Special case for anonymous error code
        const std::string codeString = std::to_string(code);
        return std::vformat(DEFAULT_CODE_FORMAT, std::make_format_args(codeString));
    } // #END: formatCode()

    // #METHOD: formatMessage(), Const Instance Method
    // #BRIEF: Formats the error code and body
    // #RETURN: std::string, Formatted message
    std::string Error::formatMessage()const{
        const std::string formattedCode = formatCode();
        return std::vformat(DEFAULT_MESSAGE_FORMAT, std::make_format_args(formattedCode, body));
    } // #END: formatCode()

// #END: Error

} // #END: docme::core
