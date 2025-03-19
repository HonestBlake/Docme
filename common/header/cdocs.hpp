#pragma once

// #class: f
// #note: f
// f

/*

  
    #struct: DataType, data structure
*/


// #class: f
#include <string>
#include <vector>
#include <variant>
#include <optional>
#include <unordered_map>
#include <iostream>
#include <utility>
#include <stdint.h>
#include <fstream>
#include <cctype>
#include <unordered_set>
#include <array>
#include <utility>

// #
inline namespace worTech{
    // #
    namespace cdocs{
        // #
        inline namespace config{
            
        }
        // #
        inline namespace genorator{
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
                using AnyNode = std::variant<GlobalSpace, NamespaceNode, ClassNode, FunctionNode, EnumNode, ConceptNode>;
            }
        } namespace gen = genorator;
    } namespace cdoc = cdocs;
} namespace wt = worTech;

