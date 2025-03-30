#pragma once

#include "parser.hpp"

namespace worTech::docme::genorator::constants{

    enum class ReturnType{
        VOID,
        INT,
        FLOAT,
        DOUBLE,
        CHAR,
        STRING,
        BOOL
    };
    enum class PublicityType{
        PUBLIC,
        PRIVATE,
        PROTECTED
    };
    enum class DataType{
        INT,
        FLOAT,
        DOUBLE,
        CHAR,
        STRING,
        BOOL,
        VOID
    };
    enum class TypeSpecifier{
        REFERENCE,
        POINTER,
        CONST_POINTER,
        POINTER_TO_CONST,
        CONST_POINTER_TO_CONST
    };
    
    
}