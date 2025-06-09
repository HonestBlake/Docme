// #file: parser.cpp, source file

#include "engine/header/parser.hpp" // declaration header

namespace docme::engine::parser{ // #scope: docme::parser

// #div: Private factory methods

    ProgramParser::ProgramParser(ParserInfo&& p_info)noexcept: m_info(std::move(p_info)){
        if constexpr(state::TRACING){ // Function tracing
            debug::trace();
        }
    }

// #div: Public methods

    ProgramParser& ProgramParser::parse(){
        if constexpr(state::TRACING){ // Function tracing
            debug::trace();
        }

        for(auto& packet: m_info.packets){ // Go through each packet and its paired files

            for(const std::filesystem::path& file: packet.files()){ // Go through each file in the packet

                std::ifstream fileStream = std::ifstream(file);
                
                if(!fileStream){
                    debug::error(error::FAILED_TO_OPEN_FILE, file.string());
                }

            //     std::optional<DocSection> fileSection;
            //     std::vector<DocSection> componentSections;

            //     DocSection currentSection;
            //     DocType currentType;

            //     std::string line;

            //     while(std::getline(fileStream, line)){

            //         DocLine = docLine;
                    
            //         DocType type = getLineType(line);



            //         if(!DocType::NONE){
            //             docLine = dll::createDocLine(line);
            //         }

            //         if(type == DocType::NEW_FILE){
            //             fileSection.name = dll::getFileName(line);
            //             fileSection.type = dll::getFileType(line);
            //         }else if(type == DocType::NEW_COMPONENT){
            //             fileSection.name = dll::getComponentName(line);
            //             fileSection.type = dll::getComponentType(line);
            //         }else if(type == DocType::ATTRIBUTE){

            //         }else if(type == DocType::CONTINUED_ATTRIBUTE){

            //         }
            //     }
            //     m_docFiles.emplace_back(std::move(fileSection), std::move(componentSections));
            }

        }


        return *this;
    }

} // #end docme::parser