// #file: docmeInfo.hpp, header file

#pragma once

#include "processor.hpp" // decloation header

namespace worTech::docme::processor::docmeInfo{

    // #enum: OutputType, uint8_t enum class
    enum class OutputType: uint8_t{
        JSON,
        MARKDOWN,
        HTML,
        PDF,
        DOCX,
        LATEX
    };
    // #struct: ParserInfo, data structure
    struct ParserInfo{
        std::unordered_map<Packet, std::unordered_set<std::filesystem::path>> fileSets;
    };
    // #struct: GeneratorInfo, data structure
    struct GeneratorInfo{
        std::filesystem::path outputDirectory; 
        std::unordered_set<OutputType> generationTypes;
    };

} // namespace worTech::docme::processor::docmeInfo