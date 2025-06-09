// #file: engine/header/engine.hpp, Module header file

#pragma once // Include guard

#include "engine/engine.hpp" // #incude: engine/engine.hpp, Package header file

#include "engine/header/parser.hpp" // Parser header
#include "engine/header/generator.hpp" // Generator header

namespace docme::engine::docmeEngine{ // #scope: docme::engine::engine

    // #struct: EngineInfo, data structure
    struct EngineInfo{
        ParserInfo parser; 
        GeneratorInfo generator;  
    }; // #end: EngineInfo

    // #class: DocmeEngine, Final object class
    class DocmeEngine final{
    public:
    // public factory methods
        DocmeEngine(EngineInfo&& p_info)noexcept;
        DocmeEngine(const DocmeEngine&)noexcept = default; // #default: Engine(const Engine&)noexcept, default copy constructor
        DocmeEngine(DocmeEngine&&)noexcept = default; // #default: Engine(Engine&&)noexcept, default move constructor
        ~DocmeEngine()noexcept = default; // #default: ~Engine()noexcept, default destructor
    // public operators
        DocmeEngine& operator=(const DocmeEngine&)noexcept = default; // #default: operator=(const Engine&)noexcept, default copy assignment operator
        DocmeEngine& operator=(DocmeEngine&&)noexcept = default; // #default: operator=(Engine&&)noexcept, default move assignment operator
    // public methods
        void run();
    private:
    // Private members
        EngineInfo m_info;
    }; // #end: DocmeEngine

} // #end: docme::engine::engine