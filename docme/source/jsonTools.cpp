// #file: jsonTools.cpp, source file

#include "jsonTools.hpp"
#include <expected>

namespace worTech::docme::jsonTools{

// public factory methods

    // #func: Json(const nlohmann::json&), public explicit constructor

    // #param: const nlohmann::json& p_json, given json object
    Json::Json(const std::string& p_file, nlohmann::json&& p_json): m_file(p_file), m_json(std::forward<nlohmann::json>(p_json)){
        if constexpr(state::TRACING){ // Function tracing
            debug::trace(std::source_location::current());
        }
    }

// public static methods

    // #func: parse(const std::string&), public static noexcept method
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
    }
    
// public methods

    // #func: getString(const std::string&), public const noexcept method
    std::expected<std::string, std::string> Json::getString(const std::string& p_key)const{
        if constexpr(state::TRACING){ // Function tracing
            debug::trace(std::source_location::current());
        }
        if(!m_json.contains(p_key)) return std::unexpected<std::string>(debug::message(error::COULD_NOT_FIND_JSON_KEY, p_key, m_file)); // Error if key is not in json
        if(!m_json[p_key].is_string()) return std::unexpected<std::string>(debug::message(error::JSON_TYPE_ERROR_STRING, p_key, m_file)); // Error if key is not a string
        return m_json[p_key].get<std::string>(); // return string at key
    }
    // #func: getUnorderedSet(const std::string&), public const noexcept method
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
    }

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
    }

} // namespace worTech::docme::jsonTools