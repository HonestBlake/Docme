// #file: source/jsonTools.cpp, Module source file

#include "header/jsonTools.hpp" // #include: Module header file

namespace docme::jsonTools{ // #scope: docme::jsonTools

// #scope: Json, method definitions

// #div: Public factory methods

    // #func: Json(const std::string&, const nlohmann::json&&), explicit constructor
    Json::Json(const std::string& p_file, nlohmann::json&& p_json): m_file(p_file), m_json(std::forward<nlohmann::json>(p_json)){
        if constexpr(state::TRACING){ // Function tracing
            debug::trace(std::source_location::current());
        }
    } // #end: Json(const std::string&, const nlohmann::json&&)

// #div: Public static methods

    // #func: parse(const std::filesystem::path&), method
    std::expected<Json, std::string> Json::parse(const std::filesystem::path& p_filePath){
        if constexpr(state::TRACING){ // Function tracing
            debug::trace(std::source_location::current());
        }
        nlohmann::json json;
        std::ifstream file = std::ifstream(p_filePath);
        if(!file) return std::unexpected<std::string>(debug::message(error::FAILED_TO_OPEN_FILE, p_filePath.string()));
        try{
            file >> json;
        }catch(const nlohmann::json::parse_error& e){
            return std::unexpected<std::string>(debug::message(error::FAILED_TO_PARSE_JSON, p_filePath.string()));
        }
        return(Json(p_filePath.string(), std::move(json)));
    } // #end: parse(const std::filesystem::path&)
    
// #div: Public methods

    // #func: getString(const std::string&), const method
    std::expected<std::string, std::string> Json::getString(const std::string& p_key)const{
        if constexpr(state::TRACING){ // Function tracing
            debug::trace(std::source_location::current());
        }
        if(!m_json.contains(p_key)) return std::unexpected<std::string>(debug::message(error::COULD_NOT_FIND_JSON_KEY, p_key, m_file)); // Error if key is not in json
        if(!m_json[p_key].is_string()) return std::unexpected<std::string>(debug::message(error::JSON_TYPE_ERROR_STRING, p_key, m_file)); // Error if key is not a string
        return m_json[p_key].get<std::string>(); // return string at key
    } // #end: getString(const std::string&)

    // #func: getUnorderedSet(const std::string&), const method
    std::expected<std::unordered_set<std::string>, std::string> Json::getUnorderedStringSet(const std::string& p_key)const{
        if constexpr(state::TRACING){ // Function tracing
            debug::trace(std::source_location::current());
        }
        if(!m_json.contains(p_key)) return std::unexpected<std::string>(debug::message(error::COULD_NOT_FIND_JSON_KEY, p_key, m_file)); // Error if key is not in json
        if(!m_json[p_key].is_array()) return std::unexpected<std::string>(debug::message(error::JSON_TYPE_ERROR_ARRAY, p_key, m_file)); // Error if element is not an array
        for(const nlohmann::json& element : m_json[p_key]){ // Check if each element in array is a string
            if(!element.is_string()) return std::unexpected<std::string>(debug::message(error::JSON_TYPE_ERROR_STRING, p_key, m_file));
        }
        return m_json[p_key].get<std::unordered_set<std::string>>(); // return unordered set from json array
    } // #end: getUnorderedStringSet(const std::string&)

    // #func: getStringArray(const std::string&), const method
    std::expected<std::vector<std::string>, std::string> Json::getStringArray(const std::string& p_key)const{
        if constexpr(state::TRACING){ // Function tracing
            debug::trace();
        }
        if(!m_json.contains(p_key)) return std::unexpected<std::string>(debug::message(error::COULD_NOT_FIND_JSON_KEY, p_key, m_file)); // Error if key is not in json
        if(!m_json[p_key].is_array()) return std::unexpected<std::string>(debug::message(error::JSON_TYPE_ERROR_ARRAY, p_key, m_file)); // Error if element is not an array
        for(const nlohmann::json& element : m_json[p_key]){ // Check if each element in array is a string
            if(!element.is_string()) return std::unexpected<std::string>(debug::message(error::JSON_TYPE_ERROR_STRING, p_key, m_file));
        }
        return m_json[p_key].get<std::vector<std::string>>(); // return vector from json array
    } // #end: getStringArray(const std::string&)

// #end: Json

} // #end: docme::jsonTools