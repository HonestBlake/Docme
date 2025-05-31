// #file: docme.hpp, project header file

#pragma once

// include libraries globally
#include "standardLibs.hpp"
#include "externalLibs.hpp"

#include "cppTools.hpp" // C++ dev tools

// #namespace: worTech, inline developer namespace
inline namespace worTech{

    // #namespace: docme, project namespace
    namespace docme{

        // #namespace: programVariables, inline module namespace
        inline namespace programVariables{
            namespace programConstants{}
            namespace program = programConstants; // alias programConstants to program
            namespace programStates{}
            namespace state = programStates; // alias programStates to state
        } // #end: programVariables

        // #namespace: debugging, inline module namespace
        inline namespace debugging{
            namespace errorMessages{}
            namespace error = errorMessages; // alias errorMessages to error
            namespace debugTools{}
            namespace debug = debugTools; // alias debugTools to debug
            namespace loggerValues{}
            namespace logger = loggerValues; // alias loggerValues to logger
            class AutoDocTracer;
            class AutoDocDebug;
        } // #end: debugging

        // #namespace: restrictedTypes, inline module namespace
        inline namespace restrictedTypes{

        } // #end: restrictedTypes

        // #namespace: jsonTools, inline module namespace
        inline namespace jsonTools{
            class Json;
        } // #end: jsonTools

        // #namespace: packets, inline module namespace
        inline namespace packets{
            class Packet;
            struct PacketHasher;
            namespace packetVariables{}
            namespace packet = packetVariables; // alias packetVariables to packet
            namespace packetFileKeys{}
            namespace key = packetFileKeys; // alias packetFileKeys to key
            namespace packetFunctions{}
            namespace func = packetFunctions; // alias packetFunctions to func
        } // #end: packets

        // #namespace: nodes, inline module namespace
        inline namespace nodes{
            namespace nodeDefaultValues{}
            namespace node = nodeDefaultValues; // alias nodeDefaultValues to node
            class Node;
            class DirectoryNode;
            class DocumentedNode;
            class FileNode;
            class ComponentNode;
            class GlobalNode;
        } // #end: nodes

        // #namespace: nodeManagers, inline module namespace
        inline namespace nodeManagers{
            class ComponentManager;
            class FileManager;
        } // #end: nodeManagers

        // #namespace: commandLine, inline module namespace
        inline namespace commandLine{
            enum struct CommandLineFlag: std::uint8_t; 
            using Flag = CommandLineFlag; // alias CommandLineFlag to Flag
            namespace commandLineVariables{}
            namespace cmdLine = commandLineVariables; // alias commandLineVariables to cmdLine
            namespace configFileKeys{}
            namespace key = configFileKeys; // alias configFileKeys to key
            struct CommandLineFlagComparer;
            using FlagComparer = CommandLineFlagComparer; // alias CommandLineFlagComparer to FlagComparer
            class CommandLineParser; 
            using CommandLine = CommandLineParser; // alias CommandLineParser to CommandLine
        } // #end: commandLine

        // #namespace: docmeInfo, inline module namespace
        inline namespace docmeInfo{
            enum class OutputType: std::uint8_t;
            struct ParserInfo;
            struct GeneratorInfo;
        } // #end: docmeInfo

        // #namespace: parser, inline module namespace
        inline namespace parser{
            class ProgramParser; 
            using Parser = ProgramParser; // alias ProgramParser to Parser
        } // #end: parser

        // #namespace: generator, inline module namespace
        inline namespace generator{
            class DocumentationGenerator; 
            using Generator = DocumentationGenerator; // alias DocumentationGenerator to Generator
        } // #end: generator

    } // #end: docme
    
} // #end: worTech
namespace wt = worTech; // alias worTech to wt

#include "debugging.hpp" // Include debugging module globally
#include "programVariables.hpp" // Include program variables module globally