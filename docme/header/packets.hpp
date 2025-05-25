// #file: packets.hpp, header file
// #directory: docme/header

// TODO rework to match new standards from parser
// TODO shift focus to code not assets, remove as much metadata as possible

// TODO support new additions with getters and setters
// TODO add parsing and building for new additions


#pragma once

#include "docme.hpp" // Project header
//#include "dynamicLibraries.hpp" // TODO make extern lib

namespace std{

    // #struct: hash<docme::DocPacket>, hash structure
    // #memberof: std, standard library namespace
    template<> struct hash<docme::Packet>{
        std::size_t operator()(const docme::Packet& p_packet)const;
    }; // #end: hash<docme::DocPacket>

}

namespace worTech::docme::packets{

    // #namespace: packetVariables(packet), variable namespace
    namespace packetVariables{
        inline const std::filesystem::path PATH_TO = std::filesystem::path(std::source_location::current().file_name()).parent_path().parent_path().parent_path().parent_path() / std::filesystem::path("resource/doc packets/");
        inline constexpr std::string DOCME = "docme";
        inline constexpr std::string FILE_EXTENSION = ".json";
    } // #end: packetVariables

    // #namespace: packetFileKeys(key), variable namespace
    namespace packetFileKeys{
        inline constexpr std::string NAME = "packet_name";
        inline const std::string FILE_TYPES = "accepted_file_types";
        inline constexpr std::string LIBRARY_NAME = "library_name";
    } // #end: packetFileKeys

    // #namespace: packetFunctions(func), variable namespace
    namespace packetFunctions{
        inline constexpr std::string IS_TAG_SYMBOL = "isTagSymbol";
        inline const std::string IS_SINGLE_LINE_COMMENT = "isSingleLineComment";
        inline const std::string IS_MULTI_LINE_COMMENT_START = "isMultiLineCommentStart";
        inline const std::string IS_MULTI_LINE_COMMENT_END = "isMultiLineCommentEnd";  
        inline constexpr std::string IS_VALID_TAG = "isValidTag";
        inline const std::string IS_CONTINUABLE_TAG = "isContinuableTag";
        inline constexpr std::string IS_NEW_FILE_TAG = "isNewFileTag";
        inline const std::string IS_NEW_COMPONENT_TAG = "isNewComponentTag";
        inline constexpr std::string NEW_FILE_NODE = "newFileNode";
        inline const std::string NEW_COMPONENT_NODE = "newComponentNode";
    } // #end: packetFunctions

    // Function type aliases
    using IsTagSymbol = bool(const char);
    using IsSingleLineComment = bool(const char*);
    using IsMultiLineCommentStart = bool(const char*);
    using IsMultiLineCommentEnd = bool(const char*);
    using IsValidTag = bool(const char*);
    using IsContinuableTag = bool(const char*);
    using IsNewFileTag = bool(const char*);
    using IsNewComponentTag = bool(const char*);\
    using NewFileNode = FileNode*(const char*, const char*);
    using NewComponentNode = ComponentNode*(const char*, const char*);

    // #class: Packet, final class object
    class Packet final{
    // friend classes
        friend struct std::hash<Packet>; // #friend: std::hash<Packet>, friend class
    public:
    // public factory methods
        Packet(std::string&& p_name)noexcept;
        Packet()noexcept = default; // #default: Packet(), default constructor
        Packet(const Packet&)noexcept = default; // #default: Packet(const Packet&), default copy constructor
        Packet(Packet&&)noexcept = default; // #default: Packet(Packet&&), default move constructor
        ~Packet()noexcept = default; // #default: ~Packet(), default destructor
    // public operators
        Packet& operator=(const Packet&)noexcept = default; // #default: operator=(const Packet&), default copy assignment operator
        Packet& operator=(Packet&&)noexcept = default; // #default: operator=(Packet&&), default move assignment operator
        bool operator==(const Packet& p_packet)const;
    // public methods
        const std::string& name()const;
        const std::unordered_set<std::filesystem::path>& files()const;
        Packet& addFile(const std::filesystem::path& p_file);
        bool isTagSymbol(const char p_char)const;
        bool isSingleLineComment(const std::string& p_line)const;
        bool isMultiLineCommentStart(const std::string& p_line)const;
        bool isMultiLineCommentEnd(const std::string& p_line)const;
        bool isValidTag(const std::string& p_tag)const;
        bool isContinuableTag(const std::string& p_tag)const;
        bool isNewFileTag(const std::string& p_tag)const;
        bool isNewCommonentTag(const std::string& p_tag)const;
        FileNode* newFileNode(const std::string& p_name, const std::string& p_type)const;
        ComponentNode* newComponentNode(const std::string& p_name, const std::string& p_type)const;
    private:
    // private method
        void loadLibraryFunctions();
    // private members
        std::string m_name;
        std::unordered_set<std::filesystem::path> m_files;
        DynamicLibrary m_library;
        std::function<IsTagSymbol> m_isTagSymbol;
        std::function<IsSingleLineComment> m_isSingleLineComment;
        std::function<IsMultiLineCommentStart> m_isMultiLineCommentStart;
        std::function<IsMultiLineCommentEnd> m_isMultiLineCommentEnd;
        std::function<IsValidTag> m_isValidTag;
        std::function<IsContinuableTag> m_isContinuableTag;
        std::function<IsNewFileTag> m_isNewFileTag;
        std::function<IsNewComponentTag> m_isNewComponentTag;
        std::function<NewFileNode> m_newFileNode;
        std::function<NewComponentNode> m_newComponentNode;
    }; // #end: Packet

} // namespace worTech::docme::packets

