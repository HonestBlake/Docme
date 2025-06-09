// #file: docmeEngine.cpp, Module source file

#include "engine/header/docmeEngine.hpp" // #include: engine/header/docmeEngine.hpp, Module header file

namespace docme::engine::docmeEngine{ // #scope: docme::engine::docmeEngine

// #scope: DocmeEngine, method definitions

// #div: Public factory methods

    // #func: Engine(EngineInfo&&), Constructor
    DocmeEngine::DocmeEngine(EngineInfo&& p_info)noexcept: m_info(std::move(p_info)){ 
        if constexpr(state::TRACING){ // Function tracing
            debug::trace(); 
        }
    } // #end: Engine(EngineInfo&&)

// #div: Public methods

    // #func: run(), Method
    void DocmeEngine::run(){
        if constexpr(state::TRACING){ // Function tracing
            debug::trace();
        }
        //Generator(m_info.generator, Parser(std::move(m_info.parser)).parse().packets()).generate();
    } // #end: run()

} // #end: docme::engine::docmeEngine
