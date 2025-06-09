// #file: generator.cpp, source file

#include "engine/header/generator.hpp" // declaration header

namespace docme::engine::generator{

// public static methods

    DocGenerator& DocGenerator::get()noexcept{
        if constexpr(state::TRACING){ // Function tracing
            debug::trace();
        }
        static DocGenerator instance = DocGenerator();
        return instance;
    }

// public methods

    void DocGenerator::generate(GeneratorInfo&& p_generatorInfo, const void*)noexcept{

    }
    
} // namespace docme::processor::generator