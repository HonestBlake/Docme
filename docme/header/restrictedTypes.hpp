// #file: header/restrictedTypes.hpp, Module header file

#pragma once // Include guard

#include "docme.hpp" // #include: docme.hpp, Project header file

namespace docme::restrictedTypes{ // #scope: docme::restrictedTypes

    // #concept: StringType, type concept
    template<typename Type> concept StringType = std::is_same<std::decay_t<Type>, std::string>::value;
    // #concept: StringVectorType, type concept
    template<typename Type> concept StringVectorType = std::is_same<std::decay_t<Type>, std::vector<std::string>>::value;
    // #concept: OptionStringType, type concept
    template<typename Type> concept OptionStringType = std::is_same<std::decay_t<Type>, std::optional<std::string>>::value || std::is_same<std::decay_t<Type>, std::string>::value;

} // #end: docme::restrictedTypes