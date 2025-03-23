#pragma once

#include "autoDoc.hpp"
#include "conceptTypes.hpp"
#include "nodes.hpp"


namespace worTech::autoDoc::genorator::helpers{

    enum class LineType: uint8_t{
        FLUSH,
        NO_DOCUMENTATION,
        START_OF_DOCUMENTATION,
        DOCUMENTATION,
        CONTINUED_DOCUMENTATION
    };
    enum class SectionType: uint8_t{
        NONE,
        NAMESPACE,
        CLASS,
        FUNCTION,
        ENUM,
        CONCEPT
    };
    namespace documentationTags{
        const std::string NAMESPACE = "namespace";
        const std::string CLASS = "class";
        const std::string STRUCT = "struct";
        const std::string FUNCTION = "func";
        const std::string ENUM = "enum";
        const std::string CONCEPT = "concept";
        const std::string BRIEF = "brief";
        const std::string NOTE = "note";
        const std::string DETAIL = "detail";
        const std::string PARAM = "param";
        const std::string RETURN = "return";
        const std::string TEMPLATE = "template";
        const std::string INHERITS = "inherits";
        const std::string THROWS = "throws";
        const std::string REQUIRES = "requires";
        const std::string CALLS = "calls";
        const std::string USES = "uses";
        const std::string MEMBER_OF = "memberof";
        const std::string FRIEND = "friend";
        const std::string OVERLOAD = "overload";
    } namespace tag = documentationTags;
    namespace documentationMaps{
        const std::unordered_map<std::string, SectionType> SECTION_TYPE {
            {tag::NAMESPACE, SectionType::NAMESPACE},
            {tag::CLASS, SectionType::CLASS},
            {tag::STRUCT, SectionType::CLASS},
            {tag::FUNCTION, SectionType::FUNCTION},
            {tag::ENUM, SectionType::ENUM},
            {tag::CONCEPT, SectionType::CONCEPT}
        };
        const std::unordered_map<SectionType, std::unordered_set<std::string>> VALID_TAGS = {
            {SectionType::NAMESPACE, {tag::BRIEF, tag::NOTE, tag::DETAIL, tag::MEMBER_OF}},
            {SectionType::CLASS, {tag::BRIEF, tag::NOTE, tag::DETAIL, tag::INHERITS, tag::MEMBER_OF, tag::FRIEND, tag::USES, tag::TEMPLATE}},
            {SectionType::FUNCTION, {tag::BRIEF, tag::NOTE, tag::DETAIL, tag::PARAM, tag::RETURN, tag::THROWS, tag::REQUIRES, tag::CALLS, tag::OVERLOAD, 
                tag::MEMBER_OF, tag::TEMPLATE, tag::USES}},
            {SectionType::ENUM, {tag::BRIEF, tag::NOTE, tag::DETAIL, tag::MEMBER_OF}},
            {SectionType::CONCEPT, {tag::BRIEF, tag::NOTE, tag::DETAIL, tag::MEMBER_OF}}
        };
        const std::unordered_set<std::string> CONTINUABLE_TAGS = {
            tag::BRIEF,
            tag::NOTE,
            tag::DETAIL,
            tag::PARAM,
            tag::RETURN,
            tag::THROWS,
            tag::REQUIRES,
            tag::TEMPLATE
        };
        const std::unordered_set<std::string> START_TAGS = {
            tag::NAMESPACE, 
            tag::CLASS, 
            tag::FUNCTION, 
            tag::ENUM, 
            tag::CONCEPT
        };
    } namespace map = documentationMaps;
    
    namespace documentationTokens{
        const char COMMENT = '/';
        const char MULTI_COMMENT = '*';
        const char TAG_START = '#';
        const char TAG_END = ':';
        const char SPACE = ' ';
        const std::string CONTINUED_LINE_BUFFER = " ";
        const std::string MULTI_COMMENT_END = "*/";
    } namespace token = documentationTokens;

    struct LineInfo{
        LineType type;
        size_t start;
        LineInfo() = default;
        LineInfo(const LineType p_type);
        LineInfo(const LineType p_type, size_t p_startingIndex);
        ~LineInfo() = default;
    };


    // #class: NodeStack, singleton class
    class NodeStack{
    public:
    // public factory methods
        NodeStack(const NodeStack&) = delete;
        ~NodeStack() = default;
    // public operators
        NodeStack& operator=(const NodeStack&) = delete;
    // public static methods
        static NodeStack& getInstance()noexcept;
    // public methods
        NodeStack& addNode(AnyNode* const p_node);
        inline const std::vector<AnyNode*>& nodes()const;
    private:
    // private factory methods
        NodeStack() = default;
    // private members
        std::vector<AnyNode*> m_nodes;
    };
    // #class: FileStack, singleton class
    class FileStack{
    public:
    // public factory methods
        FileStack(const FileStack&) = delete;
        ~FileStack() = default;
    // public operators
        FileStack& operator=(const FileStack&) = delete;
    // public static methods
        static FileStack& getInstance()noexcept;
    // public methods
        FileStack& addFile(FileNode* const p_file);
        inline const std::vector<FileNode*>& files()const;
    private:
    // private factory methods
        FileStack() = default;
    // private members
        std::vector<FileNode*> m_files;
    };
    // #class: NodeCreator, static class
    class NodeCreator{
    public:
    // public factory methods
        NodeCreator() = delete;
        ~NodeCreator() = delete;
    // public operators
        NodeCreator& operator=(const NodeCreator&) = delete;
    // public static methods
        static std::vector<std::vector<std::string>> getDocumentation(const std::string& p_file);
        static void createNodes(std::vector<std::vector<std::string>>&& p_documentation);
    private:
    // private static methods
        static size_t findComment(const std::string& p_line, size_t p_currentIndex, bool* p_currentIsComment);
        static size_t findStartTag(const std::string& p_line, size_t p_currentIndex);
        static std::string getTag(const std::string& p_line, size_t p_currentIndex, size_t* p_startOfLine);
        static inline bool isValidTag(const std::string& p_tag, const SectionType p_currentSectionType);
        static inline bool isContinuableTag(const std::string& p_tag);
        static inline bool isStartTag(const std::string& p_tag);
        static inline bool foundMultiCommentEnd(const std::string& p_line);
        static inline bool isAtComment(const std::string& p_line, size_t p_currentIndex);
        static LineInfo getLineInfo(const std::string& p_line);
        static void handleLine(const LineInfo& p_lineInfo, std::string&& p_line, std::vector<std::vector<std::string>>* p_documentation);
        static std::string cleanUpLine(std::string&& p_line, const size_t p_startingIndex);
    };
    // #class: Genorator, singleton class
    class Genorator{
    public:
    // public factory methods
        Genorator(const Genorator&) = delete;
        ~Genorator() = default;
    // public operators
        Genorator& operator=(const Genorator&) = delete;
    // public static methods
        static Genorator& getInstance()noexcept;
    // public methods
        Genorator& setLocations(int p_argc, char** p_argv);
        // template<StringType T_outputLocation, StringType T_docsTxtLocation, StringVectorType T_files>
        //     Genorator& setLocations(T_outputLocation&& p_outputLocation, T_docsTxtLocation&& p_docsTxtLocation, T_files&& p_files);
        Genorator& parseProgramFiles();
        Genorator& generateDocumentation();
    private:
    // private factory methods
        Genorator() = default;
    // private methods
        Genorator& setOutputLocation(const std::string& p_outputLocation);
        Genorator& setOutputLocation(std::string&& p_outputLocation);
        Genorator& setDocsTxtLocation(const std::string& p_docsTxtLocation);
        Genorator& setDocsTxtLocation(std::string&& p_docsTxtLocation);
        Genorator& addFileLocation(const std::string& p_fileLocation);
        Genorator& addFileLocation(std::string&& p_fileLocation);
        Genorator& setFileLocations(const std::vector<std::string>& p_files);
        Genorator& setFileLocations(std::vector<std::string>&& p_files);
    // private members
        std::string m_outputLocation;
        std::string m_docsTxtLocation;
        std::vector<std::string> m_fileLocations;
    };

}