// #file: jsonTools.hpp, header file

#include "docme.hpp" // project general header

#pragma once

namespace worTech::docme::jsonTools{

    class Json{
    public:
    // public factory methods
        explicit Json(const std::string& p_fileName, nlohmann::json&& p_json);
    // public static methods
        static std::expected<Json, std::string> parse(const std::string& p_fileName)noexcept; 
    // public methods
        std::expected<std::string, std::string> getString(const std::string& p_key)const noexcept;
        std::expected<std::unordered_set<std::string>, std::string> getUnorderedSet(const std::string& p_key)const noexcept;
    private:
    // private members
        std::string m_fileName;
        nlohmann::json m_json;
    };
    
} // namespace worTech::docme::jsonTools
