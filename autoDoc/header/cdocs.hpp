#pragma once

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
#include <format>
#include <filesystem>
#include <unordered_set>

// project wide external lib
#include "better/logger.hpp"

// #
inline namespace worTech{
    // #
    namespace autoDoc{
        // #
        inline namespace config{
            
        }
        // #
        inline namespace genorator{
            inline namespace commandLineParser{
                class CommandLineParser; using CLParser = CommandLineParser;
                enum class DocPacket: uint8_t;
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
    } namespace adoc = autoDoc;
} namespace wt = worTech;


// TODO put this somewhere else
namespace worTech::autoDoc{
    class CDocTracer: public btr::Logger{
    public:
        CDocTracer(): Logger("CDoc Tracer", {btr::Format::LOGGER, btr::Format::LEVEL, btr::Format::LOCATION, btr::Format::TIME, btr::Format::MESSAGE}){}
    private:
        std::string formatLocation(const btr::Level p_logLevel, const std::source_location& p_location)const override{
            return getLogColor(p_logLevel) + p_location.function_name() + btr::log::SPACE + btr::ansii::RESET;
        }
    };

    class AutoDocError: public btr::Logger{
    public: 
        AutoDocError(): Logger("AutoDoc Error"){}
    private:
        const Logger& sendLog(std::string&& p_log)const override{
            btr::LogStack::get<btr::TerminateFlush>().pushLog(std::forward<std::string>(p_log));
            return *this;
        }
    };
} 
// TODO make this a seperate tool
namespace worTech{
    namespace debugTools{

        inline void trace(std::source_location&& p_location){
            btr::Logger::get<adoc::CDocTracer>().log<btr::Level::TRACE>("", std::forward<std::source_location>(p_location), btr::Help::getCurrentTime());
        }
    } namespace debug = debugTools;

}


