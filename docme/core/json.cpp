// #FILE: json.cpp, Component Source File
// #BRIEF: Source file for project json component

module;

#include "docme.hpp" // #INCLUDE: docme.hpp, Project wide header

module docme.core; // #IMPLEMENTS: docme.core:json
import :json; 

namespace docme::core{ // #SCOPE: docme::core

// #SCOPE: Json

// #DIV: Public Factory Methods

    // #METHOD: Json(const nlohmann::json&)
    Json::Json(const nlohmann::json& p_json): m_json(p_json){

    }

    Json::Json(nlohmann::json&& p_json): m_json(std::move(p_json)){

    }

// #DIV: Public Static Methods

    Json Json::parse(const std_fs::path& p_file){
        
    }


// #DIV: Public Methods



// #END: Json

} // #END: docme::core