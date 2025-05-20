// #file: parser.cpp, source file

#include "parser.hpp" // declaration header

namespace worTech::docme::processor::parser{

// public static methods

    ProgramParser& ProgramParser::get()noexcept{
        if constexpr(state::TRACING){ // Function tracing
            debug::trace();
        }
        static ProgramParser instance = ProgramParser();
        return instance;
    }

// public methods

    const void* ProgramParser::parse(ParserInfo&& p_parserInfo)noexcept{
        if constexpr(state::TRACING){ // Function tracing
            debug::trace();
        }
        for(const auto& [packet, files]: p_parserInfo.fileSets){

            for(const std::filesystem::path& file: files){
                std::ifstream fileStream;
                fileStream.open(file);
                if(!fileStream.is_open()){
                    debug::error(error::FAILED_TO_OPEN_FILE, file.string());
                }

                std::string line;
                while(std::getline(fileStream, line)){
                    handleLine(std::move(line), &packet);
                }
                fileStream.close();
            }

        }


        return nullptr;
    }

} // namespace worTech::docme::processor::parser