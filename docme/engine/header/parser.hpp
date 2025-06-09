// #file: parser.hpp, header file

#pragma once

#include "engine/engine.hpp" // project header

#include "engine/header/packets.hpp" // Packet header

namespace docme::engine::parser{

    // #struct: DocumentationLine, data structure
    struct DocumentationLine{
        std::string tag;
        std::string body;
    };

    // #struct: DocumentationSection, data structure
    struct DocumentationSection{
        std::string name;
        std::string type;
        std::vector<DocumentationLine> lines;
    };

    // #struct: DocumentationFile, data structure
    struct DocumentationFile{
        std::optional<DocumentationSection> file;
        std::vector<DocumentationSection> components;
    };

    // #enum: DocumentationType, uint8_t enum class
    enum struct DocumentationType: uint8_t{
        NONE,
        NEW_FILE,
        NEW_COMPONENT,
        ATTRIBUTE,
        CONTINUED_ATTRIBUTE
    };

    struct ParserInfo{
        std::vector<Packet> packets;
    };

    // #class: ProgramParser, singleton class
    class ProgramParser final{
    public:
    // public factory methods
        ProgramParser(ParserInfo&& p_parserInfo)noexcept;
        ProgramParser(const ProgramParser&)noexcept = default; // delete copy constructor
        ProgramParser(ProgramParser&&)noexcept = default; // delete move constructor
        ~ProgramParser()noexcept = default; // default destructor
    // public operators
        ProgramParser& operator=(const ProgramParser&)noexcept = default; // delete copy assignment operator
        ProgramParser& operator=(ProgramParser&&)noexcept = default; // delete move assignment operator
    // public methods
        ProgramParser& parse();
    private:
    // Private static methods
        static inline bool s_hasParsed = false; // If program files have been parsed
    // private members
        ParserInfo m_info;
        std::function<FileNode*(std::string, std::string)> m_newFileNode;
        std::function<ComponentNode*(std::string, std::string)> m_newComponentNode;
        
        std::vector<DocumentationFile> m_docFiles;

        void* m_nodes;
    }; // #end: class ProgramParser
    
} // namespace docme::processor::parser