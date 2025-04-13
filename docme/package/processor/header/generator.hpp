// #file: generator.hpp, header file

#pragma once

#include "processor.hpp" // package header

namespace worTech::docme::processor::generator{

    // #class: DocGenerator, singleton class
    class DocGenerator{
    public:
    // public factory methods
        DocGenerator(const DocGenerator&) = delete; // delete copy constructor
        DocGenerator(DocGenerator&&) = delete; // delete move constructor
        ~DocGenerator() = default; // default destructor
    // public operators
        DocGenerator& operator=(const DocGenerator&) = delete; // delete copy assignment operator
        DocGenerator& operator=(DocGenerator&&) = delete; // delete move assignment operator
    // public static methods
        static DocGenerator& get()noexcept;
    // public methods
        void generate(GeneratorInfo&& p_generatorInfo, const void*)noexcept; 
    private:
    // private factory methods
        DocGenerator();
    };
    
} // namespace worTech::docme::processor::generator