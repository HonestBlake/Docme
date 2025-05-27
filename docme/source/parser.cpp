// #file: parser.cpp, source file

#include "parser.hpp" // declaration header

namespace worTech::docme::processor::parser{

// public static methods

    ProgramParser& ProgramParser::get(ParserInfo&& p_parserInfo)noexcept{
        if constexpr(state::TRACING){ // Function tracing
            debug::trace();
        }
        if(!s_isInitialized){ // Check if object has been initialized
            debug::error();
        }
        static ProgramParser instance = ProgramParser(std::move(p_parserInfo));
        return instance;
    }

// public methods

    const void* ProgramParser::parse(){
        if constexpr(state::TRACING){ // Function tracing
            debug::trace();
        }
        
        for(auto& [packet, files]: m_fileSets){ // Go through each packet and its paired files

            // TODOD Load packet dll and assign function pointers

            for(const std::filesystem::path& file: files){ // Go through each file in the packet
                std::ifstream fileStream = std::ifstream(file);
                if(!fileStream){
                    debug::error(error::FAILED_TO_OPEN_FILE, file.string());
                }

                std::optional<DocSection> fileSection;
                std::vector<DocSection> componentSections;

                DocSection currentSection;
                DocType currentType;

                std::string line;

                while(std::getline(fileStream, line)){

                    DocLine = docLine;
                    
                    DocType type = getLineType(line);



                    if(!DocType::NONE){
                        docLine = dll::createDocLine(line);
                    }

                    if(type == DocType::NEW_FILE){
                        fileSection.name = dll::getFileName(line);
                        fileSection.type = dll::getFileType(line);
                    }else if(type == DocType::NEW_COMPONENT){
                        fileSection.name = dll::getComponentName(line);
                        fileSection.type = dll::getComponentType(line);
                    }else if(type == DocType::ATTRIBUTE){

                    }else if(type == DocType::CONTINUED_ATTRIBUTE){

                    }
                }
                m_docFiles.emplace_back(std::move(fileSection), std::move(componentSections));
            }

        }


        return nullptr;
    }

    // #div: private factory methods

        ProgramParser::ProgramParser(ParserInfo&& p_parserInfo)noexcept: m_packets(std::move(p_parserInfo.packets)){
            if constexpr(state::TRACING){ // Function tracing
                debug::trace();
            }
            s_isInitialized = true; // Set initialized to true
        }

} // namespace worTech::docme::processor::parser