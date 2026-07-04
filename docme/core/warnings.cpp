// #FILE: warnings.cpp, Component Source File
// #BRIEF: Source file for project warnings component

module;

#include "core.hpp" // #INCLUDE: core.hpp, Package wide header

module docme.core; // #IMPLEMENTS: docme.core:warnings
import :warnings; 

namespace docme::core{ // #SCOPE: docme::core

// ------------------------------------------------------------------------------
//                                  class Warn
// ------------------------------------------------------------------------------

// #SCOPE: Warn

// #DIV: Public

// ---- Public Factory Methods ----

    // #METHOD: Warn(const std::string&, const std::string&), Constructor
    // #BRIEF: Constructor for Warn class given formats
    // #PARAM: const std::string& p_codeFormat, Format for warning code
    // #PARAM: const std::string& p_messageFormat, Format for message
    Warn::Warn(const std::string& p_codeFormat, const std::string& p_messageFormat): m_codeFormat(p_codeFormat), m_messageFormat(p_messageFormat){

    } // #END: Warn(const Code, const std::string&)

// ---- Public Operators ----

    // #METHOD: operator==(const Warn::Code&), Operator
    // #BRIEF: Checks if warning code is equal to given code
    // #PARAM: p_code, Code to compare warning code to
    // #RETURN: bool, True if warning code is equal to given code, false otherwise
    bool Warn::operator==(const Warn::Code& p_code)const{
        return code == p_code;
    } // #END: operator==(const Warn::Code&)

    // #METHOD: operator!=(const Warn::Code&), Operator
    // #BRIEF: Checks if warning code is not equal to given code
    // #PARAM: p_code, Code to compare warning code to
    // #RETURN: bool, True if warning code is not
    bool Warn::operator!=(const Warn::Code& p_code)const{
        return code != p_code;
    } // #END: operator!=(const Warn::Code&)

// ---- Public Methods ----

    // #METHOD: message(), Const Instance Method
    // #BRIEF: Returns a constructed warning message
    // #RETURN: std::string, Constructed warning message
    std::string Warn::message()const{
        return formatMessage();
    } // #END: message

// #DIV: Protected

// ---- Protected Methods ----

    // #METHOD: formatCode(), Const Instance Method
    // #BRIEF: Formats the warning code into a string
    // #RETURN: std::string, Formatted warning code string
    std::string Warn::formatCode()const{
        const std::string codeString = std::to_string(code);
        return std::vformat(m_codeFormat, std::make_format_args(codeString));
    } // #END: formatCode()

    // #METHOD: formatMessage(), Const Instance Method
    // #BRIEF: Formats the warning code and body
    // #RETURN: std::string, Formatted message
    std::string Warn::formatMessage()const{
        const std::string formattedCode = formatCode();
        return std::vformat(m_messageFormat, std::make_format_args(formattedCode, body));
    } // #END: formatCode()

// #END: Warn

// ------------------------------------------------------------------------------
//                                  class Warnings
// ------------------------------------------------------------------------------

// #SCOPE: Warnings

// #DIV: Public

// ---- Public Static Methods ----

    // #METHOD: add(const Warn&, const std::source_location&), Static Method
    // #BRIEF: Adds a warning to the warning buffer based on call site
    // #PARAM: const Warn& p_warning, Warning to add
    // #PARAM: const std::source_location& p_callSite, Call site of warning
    void Warnings::add(const Warn& p_warning, const std::source_location& p_callSite){
        s_warnings[hash(p_callSite)].push_back(p_warning);
    } // #END: add(const Warn&, const std::source_location&)

    // #METHOD: pull(), Static Method
    // #BRIEF: Takes all warning buffers
    // #RETURN: Warnings::Buffer, All warning buffers
    Warnings::Buffer Warnings::pull(){
        Buffer warnings;
        for(auto& [_, buffer]: s_warnings){
            for(Warn& warning: buffer){
                warnings.emplace_back(std::move(warning));
            }
        }
        clear();
        return warnings;
    } // #END: pull()

    // #METHOD: pull(const Warnings::Hash), Static Method
    // #BRIEF: Takes warning buffer at given hash
    // #PARAM: const Warnings::Hash p_callSite, Call site hash
    // #RETURN: Warnings::Buffer, Warning buffer at call site hash
    Warnings::Buffer Warnings::pull(const Warnings::Hash p_callSite){
        const auto warningsIt = s_warnings.find(p_callSite);
        if(warningsIt == s_warnings.end()) return {}; // Return empty when cant find

        // Take buffer & erase entry
        Buffer warnings = std::move(warningsIt->second);
        s_warnings.erase(warningsIt);

        return warnings;
    } // #END: pull(const Warnings::Hash)

    // #METHOD: clear(), Static Method
    // #BRIEF: Clears all warning buffers
    void Warnings::clear(){
        s_warnings.clear();
    } // #END: clear()

    // #METHOD: clear(const Warnings::Hash), Static Method
    // #BRIEF: Clears the warning buffer at call site hash
    // #PARAM: const Warnings::Hash p_callSite, Call site hash
    void Warnings::clear(const Warnings::Hash p_callSite){
        const auto warningsIt = s_warnings.find(p_callSite);
        if(warningsIt == s_warnings.end()) return; // Return when cant find
        s_warnings.erase(warningsIt);
    } // #END: clear(const Warnings::Hash)

    // #METHOD: empty(), Static Method
    // #BRIEF: Checks if all warning buffers are empty
    // #RETURN: bool, Whether all warning buffers are empty
    bool Warnings::empty(){
        for(const auto& [_, buffer]: s_warnings){
            if(!buffer.empty()) return false;
        }
        return true;
    } // #END: empty()

    // #METHOD: empty(const Warnings::Hash), Static Method
    // #BRIEF: Checks if buffer at call site hash is empty
    // #PARAM: const Warnings::Hash p_callSite, Call site hash
    // #RETURN: bool, Whether warning buffer at hash is empty
    bool Warnings::empty(const Warnings::Hash p_callSite){
        const auto warningsIt = s_warnings.find(p_callSite);
        if(warningsIt == s_warnings.end()) return true; // Return true when cant find
        const Buffer& buffer = warningsIt->second;
        return buffer.empty();
    } // #END: empty(const Warnings::Hash)

    // #METHOD: hash(const std::source_location&), Static Method
    // #BRIEF: Computes a hash from call site information.
    // #SEE: Based on Boost's hash_combine algorithm.
    // #PARAM: const std::source_location& p_callSite = std::source_location::current(), Call site info to hash from
    // #RETURN: Warnings::Hash, Hash of call site info
    // #DETAIL: Combines the hashes of the function name and source file into a single hash.
    Warnings::Hash Warnings::hash(const std::source_location& p_callSite){
        constexpr Hash OFFSET = 0x9e3779b97f4a7c15;
        const Hash function = std::hash<std::string_view>{}(p_callSite.function_name());
        const Hash file = std::hash<std::string_view>{}(p_callSite.file_name());
        return function ^ (file + OFFSET + (function << 6) + (function >> 2));
    } // #END: hash(const std::source_location&);

// #END: Warnings

} // #END: docme::core