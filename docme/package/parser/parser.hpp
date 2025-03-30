// #file: genorator.hpp, header file

#pragma once

#include "docme.hpp" // project general header

namespace worTech::docme{

    // #namespace: genorator, inline package namespace
    inline namespace genorator{
        // #namespace: commandLineParser, inline module namespace
        inline namespace commandLineParser{
            enum class CommandLineToken: uint8_t; 
            namespace commandLineVariables{}
            namespace commandLine = commandLineVariables; // alias commandLineVariables to var
            using Token = CommandLineToken; // alias CommandLineTag to Tag
            class CommandLineParser; 
            using CommandLine = CommandLineParser; // alias CommandLineParser to CommandLine
        }
        // #namespace: docPackets, inline module namespace
        inline namespace docPackets{
            class DocPacket;
            struct DocPacketHasher;
            using Packet = DocPacket; // alias DocPacket to Packet
            namespace packetVariables{}
            namespace packet = packetVariables; // alias packetVariables to var
        }
        // #
        inline namespace helpers{
            class Genorator; 
            class NodeStack;
            class FileStack;
        }
        // #
        inline namespace conceptTypes{}
        // #
        inline namespace nodes{
            // #namespace:
            namespace typeEnumerations{
                enum class DataType: uint8_t; 
                using Data = DataType; // alias DataType to Data
                enum class TypeSpecifier: uint8_t; 
                using Specifier = TypeSpecifier; // alias TypeSpecifier to Specifier
                enum class PublicityType: uint8_t; 
                using Publicity = PublicityType; // alias PublicityType to Publicity
                enum class NodeType: uint8_t; 
                using Node = NodeType; // alias NodeType to Node
                enum class NamespaceType: uint8_t; 
                using Namespace = NamespaceType; // alias NamespaceType to Namespace
                enum class ClassType: uint8_t; 
                using Class = ClassType; // alias ClassType to Class
                enum class FileType: uint8_t; 
                using File = FileType; // alias FileType to File
            } namespace type = typeEnumerations;
            struct DataType;
            struct ParameterType;
            struct ReturnType;
            struct TemplateType;
            struct InheritType;
            struct ThrowType;
            struct RequiredType;
            class GlobalSpace;
            class NamespaceNode; 
            class ClassNode; 
            class FunctionNode; 
            class EnumNode;
            class ConceptNode; 
            using AnyNode = std::variant<GlobalSpace, NamespaceNode, ClassNode, FunctionNode, EnumNode, ConceptNode>; // alias for variant of any Node derived class
        }
    }

} // namespace worTech::autoDoc