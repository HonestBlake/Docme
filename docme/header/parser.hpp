// #file: parser.hpp, header file

#pragma once

#include "processor.hpp" // package header
#include "docmeInfo.hpp" // used for ParserInfo
#include "packets.hpp" // used for Packet class

namespace worTech::docme::processor::parser{

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

    // #class: ProgramParser, singleton class
    class ProgramParser final{
    public:
    // public factory methods
        ProgramParser(const ProgramParser&)noexcept = delete; // delete copy constructor
        ProgramParser(ProgramParser&&)noexcept = delete; // delete move constructor
        ~ProgramParser()noexcept = default; // default destructor
    // public operators
        ProgramParser& operator=(const ProgramParser&)noexcept = delete; // delete copy assignment operator
        ProgramParser& operator=(ProgramParser&&)noexcept = delete; // delete move assignment operator
    // public static methods
        static ProgramParser& get(ParserInfo&& p_parserInfo = ParserInfo());
    // public methods
        ProgramParser& parse();
    private:
    // private factory methods
        ProgramParser(ParserInfo&& p_parserInfo)noexcept;
    // private static members
        static inline bool s_isInitialized = false; // If object has been initialized
        static inline bool s_hasParsed = false; // If program files have been parsed
    // private members
        std::unordered_set<Packet> m_packets;
        std::function<FileNode*(std::string, std::string)> m_newFileNode;
        std::function<ComponentNode*(std::string, std::string)> m_newComponentNode;
        
        std::vector<DocumentationFile> m_docFiles;

        void* m_nodes;
    }; // #end: class ProgramParser
    
} // namespace worTech::docme::processor::parser