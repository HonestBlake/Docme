// #file: header/jsonTools.hpp, Module header file

#pragma once // Include guard

#include "docme.hpp" // project general header

namespace docme::jsonTools{ // #scope: docme::jsonTools

    // #class: Json, Final object class
    class Json final{
    public:
    // Public factory methods
        Json(const std::string& p_file, nlohmann::json&& p_json);
    // Public static methods
        static std::expected<Json, std::string> parse(const std::filesystem::path& p_filePath); 
    // Public methods
        const std::string& file()const;
        std::expected<std::string, std::string> getString(const std::string& p_key)const;
        std::expected<std::unordered_set<std::string>, std::string> getUnorderedStringSet(const std::string& p_key)const;
        std::expected<std::vector<std::string>, std::string> getStringArray(const std::string& p_key)const;
    private:
    // Private members
        std::string m_file;
        nlohmann::json m_json;
    }; // #end: class Json
    
} // #end: docme::jsonTools
