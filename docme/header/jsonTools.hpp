// #file: jsonTools.hpp, header file

#include "docme.hpp" // project general header

#pragma once

namespace worTech::docme::jsonTools{

    class Json{
    public:
    // public factory methods
        Json(const std::string& p_file, nlohmann::json&& p_json);
    // public static methods
        static std::expected<Json, std::string> parse(const std::filesystem::path& p_filePath); 
    // public methods
        const std::string& file()const;
        std::expected<std::string, std::string> getString(const std::string& p_key)const;
        std::expected<std::unordered_set<std::string>, std::string> getUnorderedStringSet(const std::string& p_key)const;
        std::expected<std::vector<std::string>, std::string> getStringArray(const std::string& p_key)const;
    private:
    // private members
        std::string m_file;
        nlohmann::json m_json;
    };
    
} // namespace worTech::docme::jsonTools
