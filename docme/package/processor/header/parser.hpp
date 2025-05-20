// #file: parser.hpp, header file

#pragma once

#include "processor.hpp" // package header
#include "docmeInfo.hpp" // used for ParserInfo

namespace worTech::docme::processor::parser{

    // #class: ProgramParser, singleton class
    class ProgramParser{
    public:
    // public factory methods
        ProgramParser(const ProgramParser&) = delete; // delete copy constructor
        ProgramParser(ProgramParser&&) = delete; // delete move constructor
        ~ProgramParser() = default; // default destructor
    // public operators
        ProgramParser& operator=(const ProgramParser&) = delete; // delete copy assignment operator
        ProgramParser& operator=(ProgramParser&&) = delete; // delete move assignment operator
    // public static methods
        static ProgramParser& get()noexcept;
    // public methods
        const void* parse(ParserInfo&& p_parserInfo)noexcept;
    private:
    // private factory methods
        ProgramParser() = default; // default constructor
    };
    
} // namespace worTech::docme::processor::parser