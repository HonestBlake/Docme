#pragma once

#include "cdocs.hpp"

// #file: conceptTypes.hpp, header file

namespace worTech::autoDoc::genorator::conceptTypes{

    // #concept: StringType, type concept
    template<typename Type> concept StringType = std::is_same<std::decay_t<Type>, std::string>::value;
    // #concept: StringVectorType, type concept
    template<typename Type> concept StringVectorType = std::is_same<std::decay_t<Type>, std::vector<std::string>>::value;
    // #concept: OptionStringType, type concept
    template<typename Type> concept OptionStringType = std::is_same<std::decay_t<Type>, std::optional<std::string>>::value
        || std::is_same<std::decay_t<Type>, std::string>::value;
    // #concept: DerivedType, type concept
    template<typename Type> concept DerivedType = std::is_same<Type, NamespaceNode>::value 
        || std::is_same<Type, ClassNode>::value || std::is_same<Type, FunctionNode>::value || std::is_same<Type, EnumNode>::value 
        || std::is_same<Type, ConceptNode>::value;
    // #concept: DataVectorType, type concept
    template<typename Type> concept DataVectorType = std::is_same<std::decay_t<Type>, std::vector<DataType>>::value;

} // namespace worTech::cdocs::genorator::conceptTypes