// #FILE: json.cpp, Component Source File
// #BRIEF: Source file for project json component

module;

#include "core.hpp" // #INCLUDE: core.hpp, Package wide header

module docme.core; // #IMPLEMENTS: docme.core:json
import :json; 

namespace docme::core{ // #SCOPE: docme::core

// #SCOPE: Json

// #DIV: Public Factory Methods

    // #METHOD: Json(const nlohmann::json&), Constructor
    // #BRIEF: Constructs from nlohmann json object
    Json::Json(const nlohmann::json& p_json): m_json(p_json){
        
    } // #END: Json(const nlohmann::json&)

    // #METHOD: Json(nlohmann::json&&), Constructor
    // #BRIEF: Constructs from a moved nlohmann json object
    // #NOTE: Takes ownership of json object
    Json::Json(nlohmann::json&& p_json): m_json(std::move(p_json)){
        
    } // #END: Json(nlohmann::json&&)

// #DIV: Public Static Methods

    // #METHOD: parse(const std_fs::path&), Method
    // #BRIEF: Parses file into nlohmann json object then creates a json wrapper and returns
    // #NOTE: Returns error codes: DOCME_100, DOCME_104
    // #PARAM: const std_fs::path& p_file, Json file to parse
    // #RETURN: Result<Json>, Result object containing either the parsed json or error type
    Result<Json> Json::parse(const std_fs::path& p_file){
        std::ifstream file = std::ifstream(p_file);
        if(!file) return Error(Error::DOCME_100, p_file.string()); // Failed tp open json file
        nlohmann::json json;
        try{ 
            file >> json;
        }catch(nlohmann::json::parse_error& e){ // Failed to parse json
            return Error(Error::DOCME_104, p_file.string());
        } 
        if(file.bad()) return Error(Error::DOCME_100, p_file.string()); // Error reading json file
        return Json(std::move(json));
    } // #END: parse(const std_fs::path&)

// #DIV: Public Methods

    // #METHOD: get<std::string(const std::string_view), Const Method
    // #BRIEF: Get string value from json at given key
    // #NOTE: Returns error codes: DOCME_101, DOCME_102    
    // #SPECIAL: get<T_Value>(const std::string_view), T_Value = std::string
    // #PARAM: const std::string_view p_key, Key of value
    // #RETURN: Result<std::string>, String if successful, error type if failed
    template<> Result<std::string> Json::get<std::string>(const std::string_view p_key)const{
        if(!m_json.contains(p_key)) return Error(Error::DOCME_101, p_key); // Error if key is not in json
        if(!m_json[p_key].is_string()) return Error(Error::DOCME_102, p_key); // Error if key is not a string
        return m_json[p_key].get<std::string>(); // return string at key
    } // #END: get(const std::string_view)

    // #METHOD: get<std::vector<std::string>>(const std::string_view), Const Method
    // #BRIEF: Get string list value from json at given key
    // #NOTE: Returns error codes: DOCME_101, DOCME_102, DOCME_103
    // #SPECIAL: get<T_Value>(const std::string_view), T_Value = std::vector<std::string>
    // #PARAM: const std::string_view p_key, Key of value
    // #RETURN: Result<std::vector<std::string>>, List of strings if successful, error type if failed
    template<> Result<std::vector<std::string>> Json::get<std::vector<std::string>>(const std::string_view p_key)const{
        if(!m_json.contains(p_key)) return Error(Error::DOCME_101, p_key); // Error if key is not in json
        if(!m_json[p_key].is_array()) return Error(Error::DOCME_103, p_key); // Error if element is not an array
        for(const nlohmann::json& element : m_json[p_key]){ // Check if each element in array is a string
            if(!element.is_string()) return Error(Error::DOCME_102, p_key);
        }
        return m_json[p_key].get<std::vector<std::string>>(); // return vector from json array
    } // #END: get(const std::string_view)

    // #METHOD: nodes(), Const Method
    // #BRIEF: Create a list of nodes from json items
    // #RETURN: std::vector<Node>, List of nodes
    std::vector<Json::Node> Json::nodes()const{
        std::vector<Node> nodes;
        for(const auto& node: m_json.items()){
            nodes.emplace_back(node.key());
        }
        return nodes;
    } // #END: nodes

// #SCOPE: Node

    // #METHOD: Node(const std::string&), Public Constructor
    // #BRIEF: Constructs node from key
    Json::Node::Node(const std::string& p_key): key(p_key){

    } // #END: Node(const std::string&)

// #END: Node

// #SCOPE: Error

    // #METHOD: Error(const Code), Public Constructor
    // #BRIEF: Constructor given a code
    // #PARAM: const Code p_code, Error code
    Json::Error::Error(const Code p_code): Error(){
        code = p_code;
    } // #END: Error(const Code)

    // #METHOD: Error<...T_ContextArgs>(const Code, const T_ContextArgs&...), Public Template Constructor
    // #BRIEF: Template constructor for error with context arguments
    // #PARAM: const Code p_code, Error code
    // #PARMA: const T_ContextArgs&... p_contextArgs, Context arguments bundle
    // #TEMPLATE: class... T_ContextArgs, 
    template<class... T_ContextArgs> Json::Error::Error(const Code p_code, const T_ContextArgs&... p_contextArgs): Error(){
        code = p_code;
        body = std::vformat(ERROR_MESSAGES.at(p_code), std::make_format_args(p_contextArgs...));
    } // #END: Error<...T_ContextArgs>(const Code, const T_ContextArgs&...)

// #END: Error

// #END: Json

} // #END: docme::core