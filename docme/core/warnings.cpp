// #FILE: warnings.cpp, Component Source File
// #BRIEF: Source file for project warnings component

module;

#include "core.hpp" // #INCLUDE: core.hpp, Package wide header

module docme.core; // #IMPLEMENTS: docme.core:warnings
import :warnings; 

namespace docme::core{ // #SCOPE: docme::core

// ------------------------------------------------------------------------------
//                                  class Warning
// ------------------------------------------------------------------------------

// #SCOPE: Warning

// #DIV: Public

// ---- Public Special Methods ----

    // #METHOD: Warning(const std::unordered_map<Code, std::string>&, const Code, std::format_args), Constructor
    // #BRIEF: Constructs Warning from a message lookup table, warning code, and context args
    // #PARAM: const std::unordered_map<Code, std::string>& p_warningMessages, Warning message lookup table
    // #PARAM: const Code p_code, Warning code
    // #PARAM: std::format_args p_contextArgs, Context format arguments
    Warning::Warning(const std::unordered_map<Code, std::string>& p_warningMessages, const Code p_code, std::format_args p_contextArgs): code(p_code), body(getWarningMessage(p_warningMessages, code, p_contextArgs)){

    } // #END: Warning(const std::unordered_map<Code, std::string>&, const Code, std::format_args)

// ---- Public Operators ----

    // #METHOD: operator==(const Warning::Code&), Operator
    // #BRIEF: Checks if warning code is equal to given code
    // #PARAM: p_code, Code to compare warning code to
    // #RETURN: bool, True if warning code is equal to given code, false otherwise
    bool Warning::operator==(const Warning::Code& p_code)const{
        return code == p_code;
    } // #END: operator==(const Warning::Code&)

    // #METHOD: operator!=(const Warning::Code&), Operator
    // #BRIEF: Checks if warning code is not equal to given code
    // #PARAM: p_code, Code to compare warning code to
    // #RETURN: bool, True if warning code is not
    bool Warning::operator!=(const Warning::Code& p_code)const{
        return code != p_code;
    } // #END: operator!=(const Warning::Code&)

// ---- Public Methods ----

    // #METHOD: message(), Const Instance Method
    // #BRIEF: Returns a constructed warning message
    // #RETURN: std::string, Constructed warning message
    std::string Warning::message()const{
        return formatMessage();
    } // #END: message

// #DIV: Protected

// ---- Protected Static Methods ----

    // #METHOD: getWarningMessage(const std::unordered_map<Code, std::string>&, const Code, std::format_args), Protected Static Method
    // #BRIEF: Gets the formatted warning message body for a given warning code
    // #PARAM: const std::unordered_map<Code, std::string>& p_warningMessages, Warning message lookup table
    // #PARAM: const Code p_code, Warning code for message lookup
    // #PARAM: std::format_args p_contextArgs, Context format arguments
    // #RETURN: std::string, Warning message body
    std::string Warning::getWarningMessage(const std::unordered_map<Code, std::string>& p_warningMessages, const Code p_code, std::format_args p_contextArgs){
        if(auto it = p_warningMessages.find(p_code); it != p_warningMessages.end()){
            return std::vformat(it->second, p_contextArgs);
        }
        return UNKNOWN_WARNING_MESSAGE;
    } // #END: getWarningMessage(const std::unordered_map<Code, std::string>&, const Code, std::format_args)

// ---- Protected Methods ----

    // #METHOD: formatCode(), Const Instance Method
    // #BRIEF: Formats the warning code into a string
    // #RETURN: std::string, Formatted warning code string
    std::string Warning::formatCode()const{
        if(code == DOCME_WARNING) return ANONYMOUS_WARNING_STRING; // Special case for anonymous warning code
        const std::string codeString = std::to_string(code);
        return std::vformat(DEFAULT_CODE_FORMAT, std::make_format_args(codeString));
    } // #END: formatCode()

    // #METHOD: formatMessage(), Const Instance Method
    // #BRIEF: Formats the warning code and body
    // #RETURN: std::string, Formatted message
    std::string Warning::formatMessage()const{
        const std::string formattedCode = formatCode();
        return std::vformat(DEFAULT_MESSAGE_FORMAT, std::make_format_args(formattedCode, body));
    } // #END: formatCode()

// #DIV: Public

// ---- Public Static Methods ----

    // #METHOD: propagate(const Warning&, const std_loc&), Static Method
    // #BRIEF: Propagates a warning to the warning buffer based on call site
    // #PARAM: const Warning& p_warning, Warning to propagate
    // #PARAM: const std_loc& p_callSite, Call site of warning
    void Warning::propagate(const Warning& p_warning, const std_loc& p_callSite){
        s_warningBuffer[hash(p_callSite)].push_back(p_warning);
    } // #END: propagate(const Warning&, const std_loc&)

    // #METHOD: propagate(Warning&&, const std_loc&), Static Method
    // #BRIEF: Propagates a warning to the warning buffer based on call site
    // #PARAM: Warning&& p_warning, Warning to propagate
    // #PARAM: const std_loc& p_callSite, Call site of warning
    void Warning::propagate(Warning&& p_warning, const std_loc& p_callSite){
        s_warningBuffer[hash(p_callSite)].push_back(std::move(p_warning));
    } // #END: propagate(Warning&&, const std_loc&)

    // #METHOD: pull(), Static Method
    // #BRIEF: Takes all warning buffers
    // #RETURN: std::vector<Warning>, All warning buffers
    std::vector<Warning> Warning::pull(){
        std::vector<Warning> warnings;
        for(auto& [_, buffer]: s_warningBuffer){
            for(Warning& warning: buffer){
                warnings.emplace_back(std::move(warning));
            }
        }
        clear();
        return warnings;
    } // #END: pull()

    // #METHOD: pull(const Warning::Hash), Static Method
    // #BRIEF: Takes warning buffer at given hash
    // #PARAM: const Warning::Hash p_callSite, Call site hash
    // #RETURN: std::vector<Warning>, Warning buffer at call site hash
    std::vector<Warning> Warning::pull(const Warning::Hash p_callSite){
        const auto warningsIt = s_warningBuffer.find(p_callSite);
        if(warningsIt == s_warningBuffer.end()) return {}; // Return empty when cant find

        // Take buffer & erase entry
        std::vector<Warning> warnings = std::move(warningsIt->second);
        s_warningBuffer.erase(warningsIt);

        return warnings;
    } // #END: pull(const Warning::Hash)

    // #METHOD: clear(), Static Method
    // #BRIEF: Clears all warning buffers
    void Warning::clear(){
        s_warningBuffer.clear();
    } // #END: clear()

    // #METHOD: clear(const Warning::Hash), Static Method
    // #BRIEF: Clears the warning buffer at call site hash
    // #PARAM: const Warning::Hash p_callSite, Call site hash
    void Warning::clear(const Warning::Hash p_callSite){
        const auto warningsIt = s_warningBuffer.find(p_callSite);
        if(warningsIt == s_warningBuffer.end()) return; // Return when cant find
        s_warningBuffer.erase(warningsIt);
    } // #END: clear(const Warning::Hash)

    // #METHOD: empty(), Static Method
    // #BRIEF: Checks if all warning buffers are empty
    // #RETURN: bool, Whether all warning buffers are empty
    bool Warning::empty(){
        for(const auto& [_, buffer]: s_warningBuffer){
            if(!buffer.empty()) return false;
        }
        return true;
    } // #END: empty()

    // #METHOD: empty(const Warning::Hash), Static Method
    // #BRIEF: Checks if buffer at call site hash is empty
    // #PARAM: const Warning::Hash p_callSite, Call site hash
    // #RETURN: bool, Whether warning buffer at hash is empty
    bool Warning::empty(const Warning::Hash p_callSite){
        const auto warningsIt = s_warningBuffer.find(p_callSite);
        if(warningsIt == s_warningBuffer.end()) return true; // Return true when cant find
        const std::vector<Warning>& buffer = warningsIt->second;
        return buffer.empty();
    } // #END: empty(const Warning::Hash)

    // #METHOD: hash(const std_loc&), Static Method
    // #BRIEF: Computes a hash from call site information.
    // #SEE: Based on Boost's hash_combine algorithm.
    // #PARAM: const std_loc& p_callSite = std_loc::current(), Call site info to hash from
    // #RETURN: Warning::Hash, Hash of call site info
    // #DETAIL: Combines the hashes of the function name and source file into a single hash.
    Warning::Hash Warning::hash(const std_loc& p_callSite){
        constexpr Hash OFFSET = 0x9e3779b97f4a7c15;
        const Hash function = std::hash<std::string_view>{}(p_callSite.function_name());
        const Hash file = std::hash<std::string_view>{}(p_callSite.file_name());
        return function ^ (file + OFFSET + (function << 6) + (function >> 2));
    } // #END: hash(const std_loc&)

// #DIV: Private

// ---- Private Static Fields ----

    thread_local std::unordered_map<Warning::Hash, std::vector<Warning>> Warning::s_warningBuffer;

// #END: Warning
} // #END: docme::core
