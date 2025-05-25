// #file: generator.hpp, header file

#pragma once

#include "docme.hpp" // project header

namespace worTech::docme{

    // #namespace: processor, inline package namespace
    inline namespace processor{
        // #namespace: commandLineParser, inline module namespace
        inline namespace commandLineParser{
            enum class CommandLineToken: std::uint8_t; 
            namespace commandLineVariables{}
            namespace commandLine = commandLineVariables; // alias commandLineVariables to var
            using Token = CommandLineToken; // alias CommandLineTag to Tag
            class CommandLineParser; 
            using CommandLine = CommandLineParser; // alias CommandLineParser to CommandLine
        }
        // #namespace: docmeInfo, inline module namespace
        inline namespace docmeInfo{
            enum class OutputType: std::uint8_t;
            struct ParserInfo;
            struct GeneratorInfo;
        }
        // #namespace: generator, inline module namespace
        inline namespace generator{
            class DocGenerator; 
            using Generator = DocGenerator; // alias DocGenerator to Generator
        }
        // #namespace: parser, inline module namespace
        inline namespace parser{
            class ProgramParser; 
            using Parser = ProgramParser; // alias ProgramParser to Parser
        }
    }

} // namespace worTech::autoDoc