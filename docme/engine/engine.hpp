// #file: docme.hpp, project header file

#pragma once

#include "docme.hpp"

namespace docme{

    // #namespace: docme, project namespace
    inline namespace engine{

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

        // #namespace: parser, inline module namespace
        inline namespace parser{
            struct ParserInfo;
            class ProgramParser; 
            using Parser = ProgramParser; // alias ProgramParser to Parser
        } // #end: parser

        // #namespace: generator, inline module namespace
        inline namespace generator{
            struct GeneratorInfo;
            class DocumentationGenerator; 
            using Generator = DocumentationGenerator; // alias DocumentationGenerator to Generator
        } // #end: generator

        // #namespace: docmeEngine, inline module namespace
        inline namespace docmeEngine{
            struct EngineInfo;
            class DocmeEngine; 
            using Engine = DocmeEngine; // alias DocmeEngine to Engine
        } // #end: docmeEngine
    
    } // #end: docme
    
} // #end: docme

// #include "engine/header/nodes.hpp"

// #include "engine/header/nodeManagers.hpp"

// #include "engine/header/packets.hpp"

// #include "engine/header/parser.hpp"

// #include "engine/header/generator.hpp"

// #include "engine/header/docmeEngine.hpp" 

// #include "engine/header/commandLine.hpp"
