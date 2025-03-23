// #file: genorator.hpp, header file

#pragma once

#include "autoDoc.hpp" // project general header

namespace worTech::autoDoc{

    // #namespace: genorator, inline package namespace
    inline namespace genorator{
        // #namespace: commandLineParser, inline module namespace
        inline namespace commandLineParser{
            enum class CommandLineTag: uint8_t; 
            using Tag = CommandLineTag; // alias CommandLineTag to Tag
            enum class DocPacket: uint8_t; 
            using Packet = DocPacket; // alias DocPacket to Packet
            class CommandLineParser; 
            using Parser = CommandLineParser; // alias CommandLineParser to parser
        }
        // #
        inline namespace helpers{
            class Genorator; 
            class NodeStack;
            class FileStack;
        }
        // #
        inline namespace conceptTypes{

        }
        // #
        inline namespace nodes{
            // #namespace:
            namespace typeEnumerations{
                enum class DataType: uint8_t; using Data = DataType;
                enum class TypeSpecifier: uint8_t; using Specifier = TypeSpecifier;
                enum class PublicityType: uint8_t; using Publicity = PublicityType;
                enum class NodeType: uint8_t; using Node = NodeType;
                enum class NamespaceType: uint8_t; using Namespace = NamespaceType;
                enum class ClassType: uint8_t; using Class = ClassType;
                enum class FileType: uint8_t; using File = FileType;
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