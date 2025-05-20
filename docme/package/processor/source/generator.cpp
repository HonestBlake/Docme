// #file: generator.cpp, source file

#include "generator.hpp" // declaration header

namespace worTech::docme::processor::generator{

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
    
} // namespace worTech::docme::processor::generator