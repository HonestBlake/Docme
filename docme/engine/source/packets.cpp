// #file: packetManager.cpp, source file

#include "engine/header/packets.hpp" // Module header

namespace std{ 

// #from: hash<docme::DocPacket>, method definitions 

    // #func: operator()(const docme::Packet&), const operator
    // #param: const docme::Packet& p_packet, given packet
    // #return: std::size_t, hashed value of packet
    // #brief: Hasher for docme::Packet
    // #detail: Hashes docme::Packet by using std::string hash on packet name
    std::size_t hash<docme::Packet>::operator()(const docme::Packet& p_packet)const{
        if constexpr(docme::state::TRACING){ // Function tracing
            docme::debug::trace();
        }
        return std::hash<std::string>{}(p_packet.m_name); // Hash packet name
    } // #end: operator()(const docme::Packet&)

} // namespace std

namespace docme::engine::packets{

// #from: Packet, method definitions

// #div: public factory methods

    Packet::Packet(const std::string& p_packetFile)noexcept{
        if constexpr(state::TRACING){ // Function tracing
            debug::trace();
        }
        // Parse json file
        std::expected<Json, std::string> json = Json::parse(packet::PATH_TO / std::filesystem::path(p_packetFile + packet::FILE_EXTENSION));
        if(!json){ // Check if error parsing json file
            debug::error(json.error());
        }
        // Get packet name from json
        std::expected<std::string, std::string> name = json->getString(key::NAME);
        if(!name){ // Check if error getting name from json
            debug::error(name.error());
        }
        m_name = *name;
        // Get library name from json
        std::expected<std::string, std::string> libraryName = json->getString(key::LIBRARY_NAME);
        if(!libraryName){ // Check if error getting library name from json
            debug::error(libraryName.error());
        }
        // Load library
        m_library = btr::DynamicLibrary::load(packet::PATH_TO / std::filesystem::path(*libraryName));
        if(!m_library){ // Check if error loading library
            debug::error(error::FAILED_TO_LOAD_DLL, *libraryName);
        }
        loadLibraryFunctions();
    } // #end: Packet(const std::string&)

// #div: public operators

    // #func: operator==(const Packet&), const operator

    // #param: const DocPacket& p_packet, given packet
    // #return: bool, weather packets have same name
    bool Packet::operator==(const Packet& p_packet)const{
        if constexpr(state::TRACING){ // Function tracing
            debug::trace();
        }
        return m_name == p_packet.name();
    }

// #div: public methods

    // #func: name(), const method
    // #return: const std::string&, packet name
    const std::string& Packet::name()const{
        if constexpr(state::TRACING){ // Function tracing
            debug::trace(); 
        }
        return m_name;
    } // #end: name()

    // #func: files(), const method
    // #return: const std::unordered_set<std::filesystem::path>&, packet files
    std::vector<std::filesystem::path>& Packet::files(){
        if constexpr(state::TRACING){ // Function tracing
            debug::trace(); 
        }        
        return m_files;
    } // #end: files()

    // #func: addFileIfValid(const std::filesystem::path&), method
    // #param: const std::filesystem::path& p_file, given file path
    // #return: Packet&, reference to current packet
    Packet& Packet::addFileIfValid(const std::filesystem::path& p_file){
        if constexpr(state::TRACING){ // Function tracing
            debug::trace(); 
        }
        if(m_isValidFileType(p_file.extension().string().c_str())){ 
            m_files.emplace_back(p_file);
        }
        return *this;
    } // #end: addFileIfValid(const std::filesystem::path&)

    // #func: removeIfContainsFile(const std::filesystem::path&), method
    Packet& Packet::removeIfContainsFile(const std::filesystem::path& p_file){
        if constexpr(state::TRACING){ // Function tracing
            debug::trace(); 
        }
        m_files.erase(std::remove(m_files.begin(), m_files.end(), p_file), m_files.end());
        return *this;
    } // #end: removeIfContainsFile(const std::filesystem::path&)

    // #func: hasNoFiles(), const method
    bool Packet::hasNoFiles()const{
        if constexpr(state::TRACING){ // Function tracing
            debug::trace(); 
        }
        return m_files.empty();
    } // #end: hasNoFiles()

    // #func: isTagSymbol(const char), const method
    // #param: const char p_char, given character
    // #return: bool, weather character is a tag symbol
    bool Packet::isTagSymbol(const char p_char)const{
        if constexpr(state::TRACING){ // Function tracing
            debug::trace(); 
        }
        return m_isTagSymbol(p_char);
    } // #end: isTagSymbol(const char)

    // #func: isSingleLineComment(const std::string&), const method
    // #param: const std::string& p_line, given line
    // #return: bool, weather line is a single line comment
    bool Packet::isSingleLineComment(const std::string& p_line)const{
        if constexpr(state::TRACING){ // Function tracing
            debug::trace(); 
        }
        return m_isSingleLineComment(p_line.c_str());
    } // #end: isSingleLineComment(const std::string&)

    // #func: isMultiLineCommentStart(const std::string&), const method
    // #param: const std::string& p_line, given line
    // #return: bool, weather line is a multi line comment start
    bool Packet::isMultiLineCommentStart(const std::string& p_line)const{
        if constexpr(state::TRACING){ // Function tracing
            debug::trace(); 
        }
        return m_isMultiLineCommentStart(p_line.c_str());
    } // #end: isMultiLineCommentStart(const std::string&)

    // #func: isMultiLineCommentEnd(const std::string&), const method
    // #param: const std::string& p_line, given line
    // #return: bool, weather line is a multi line comment end
    bool Packet::isMultiLineCommentEnd(const std::string& p_line)const{
        if constexpr(state::TRACING){ // Function tracing
            debug::trace(); 
        }
        return m_isMultiLineCommentEnd(p_line.c_str());
    } // #end: isMultiLineCommentEnd(const std::string&)

    // #func: isValidTag(const std::string&), const method
    // #param: const std::string& p_tag, given tag
    // #return: bool, weather tag is valid
    bool Packet::isValidTag(const std::string& p_tag)const{
        if constexpr(state::TRACING){ // Function tracing
            debug::trace(); 
        }
        return m_isValidTag(p_tag.c_str());
    } // #end: isValidTag(const std::string&)

    // #func: isContinuableTag(const std::string&), const method
    // #param: const std::string& p_tag, given tag
    // #return: bool, weather tag is continuable
    bool Packet::isContinuableTag(const std::string& p_tag)const{
        if constexpr(state::TRACING){ // Function tracing
            debug::trace(); 
        }
        return m_isContinuableTag(p_tag.c_str());
    } // #end: isContinuableTag(const std::string&)

    // #func: isNewFileTag(const std::string&), const method
    // #param: const std::string& p_tag, given tag
    // #return: bool, weather tag is a new file tag
    bool Packet::isNewFileTag(const std::string& p_tag)const{
        if constexpr(state::TRACING){ // Function tracing
            debug::trace(); 
        }
        return m_isNewFileTag(p_tag.c_str());
    } // #end: isNewFileTag(const std::string&)

    // #func: isNewCommonentTag(const std::string&), const method
    // #param: const std::string& p_tag, given tag
    // #return: bool, weather tag is a new component tag
    bool Packet::isNewCommonentTag(const std::string& p_tag)const{
        if constexpr(state::TRACING){ // Function tracing
            debug::trace(); 
        }
        return m_isNewComponentTag(p_tag.c_str());
    } // #end: isNewCommonentTag(const std::string&)

    // #func: newFileNode(const std::string&, const std::string&), const method
    // #param: const std::string& p_name, given file name
    // #param: const std::string& p_type, given file type
    // #return: FileNode*, new file node
    FileNode* Packet::newFileNode(const std::string& p_name, const std::string& p_type)const{
        if constexpr(state::TRACING){ // Function tracing
            debug::trace(); 
        }
        return m_newFileNode(p_name.c_str(), p_type.c_str());
    } // #end: newFileNode(const std::string&, const std::string&)

    // #func: newComponentNode(const std::string&, const std::string&), const method
    // #param: const std::string& p_name, given component name  
    // #param: const std::string& p_type, given component type
    // #return: ComponentNode*, new component node
    ComponentNode* Packet::newComponentNode(const std::string& p_name, const std::string& p_type)const{
        if constexpr(state::TRACING){ // Function tracing
            debug::trace(); 
        }
        return m_newComponentNode(p_name.c_str(), p_type.c_str());
    } // #end: newComponentNode(const std::string&, const std::string&)

// #div: private methods
    
    // #func: loadLibraryFunctions(), method
    // #brief: Loads external functions from packet library
    // #detail: Loads external functions by assigning function pointer members to functions pointers from packets dll library
    void Packet::loadLibraryFunctions(){
        if constexpr(state::TRACING){ // Function tracing
            debug::trace(); 
        }
        // Set isValidFileType function pointer
        auto isValidFileType = m_library.getFunction<IsValidFileType>(func::IS_VALID_FILE_TYPE);
        if(!isValidFileType){ // Check if error getting isValidFileType function
            debug::error(isValidFileType.error());
        }
        m_isValidFileType = *isValidFileType;
        // Set isTagSymbol function pointer
        auto isTagSymbol = m_library.getFunction<IsTagSymbol>(func::IS_TAG_SYMBOL);
        if(!isTagSymbol){ // Check if error getting isTagSymbol function
            debug::error(isTagSymbol.error());
        }
        m_isTagSymbol = *isTagSymbol;
        // Set isSingleLineComment function pointer
        auto isSingleLineComment = m_library.getFunction<IsSingleLineComment>(func::IS_SINGLE_LINE_COMMENT);
        if(!isSingleLineComment){ // Check if error getting isSingleLineComment function
            debug::error(isSingleLineComment.error());
        }
        m_isSingleLineComment = *isSingleLineComment;
        // Set isMultiLineCommentStart function pointer
        auto isMultiLineCommentStart = m_library.getFunction<IsMultiLineCommentStart>(func::IS_MULTI_LINE_COMMENT_START);
        if(!isMultiLineCommentStart){ // Check if error getting isMultiLineCommentStart function
            debug::error(isMultiLineCommentStart.error());
        }
        m_isMultiLineCommentStart = *isMultiLineCommentStart;
        // Set isMultiLineCommentEnd function pointer
        auto isMultiLineCommentEnd = m_library.getFunction<IsMultiLineCommentEnd>(func::IS_MULTI_LINE_COMMENT_END);
        if(!isMultiLineCommentEnd){ // Check if error getting isMultiLineCommentEnd function
            debug::error(isMultiLineCommentEnd.error());
        }
        m_isMultiLineCommentEnd = *isMultiLineCommentEnd;
        // Set isValidTag function pointer
        auto isValidTag = m_library.getFunction<IsValidTag>(func::IS_VALID_TAG);
        if(!isValidTag){ // Check if error getting isValidTag function
            debug::error(isValidTag.error());
        }
        m_isValidTag = *isValidTag;
        // Set isContinuableTag function pointer
        auto isContinuableTag = m_library.getFunction<IsContinuableTag>(func::IS_CONTINUABLE_TAG);
        if(!isContinuableTag){ // Check if error getting isContinuableTag function
            debug::error(isContinuableTag.error());
        }
        m_isContinuableTag = *isContinuableTag;
        // Set isNewFileTag function pointer
        auto isNewFileTag = m_library.getFunction<IsNewFileTag>(func::IS_NEW_FILE_TAG);
        if(!isNewFileTag){ // Check if error getting isNewFileTag function
            debug::error(isNewFileTag.error());
        }
        m_isNewFileTag = *isNewFileTag;
        // Set isNewComponentTag function pointer
        auto isNewComponentTag = m_library.getFunction<IsNewComponentTag>(func::IS_NEW_COMPONENT_TAG);
        if(!isNewComponentTag){ // Check if error getting isNewComponentTag function
            debug::error(isNewComponentTag.error());
        }
        m_isNewComponentTag = *isNewComponentTag;
    } // #end: loadLibraryFunctions()

} // namespace docme::processor::packetManager

