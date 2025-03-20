#include "helpers.hpp"

// #file: helpers.hpp, header file

namespace worTech::autoDoc::genorator::helpers{

// LineInfo, method definitions

// public factory methods

// #func: LineInfo(LineType), public constructor
// #brief: LineInfo constructor taking a LineType
// #param: LineType p_type, enum representing documentation type held in line
// #overload: LineInfo(LineType, size_t)
// #detail: LineInfo constructor taking a LineType and defaulting start to 0
LineInfo::LineInfo(const LineType p_type): type(p_type), start(0){
    #ifdef WT_AUTODOC_DEBUG_TRACING
        debug::trace(std::source_location::current());
    #endif
};
// #func: LineInfo(LineType, size_t), public constructor
// #brief: LineInfo constructor taking a LineType and a starting index
// #param: LineType p_type, enum representing documentation type held in line
// #param: size_t p_startingIndex, starting index of the documentation in the line
// #overload: LineInfo(LineType)
LineInfo::LineInfo(const LineType p_type, size_t p_startingIndex): type(p_type), start(p_startingIndex){
    #ifdef WT_AUTODOC_DEBUG_TRACING
        debug::trace(std::source_location::current());
    #endif
};

// ----------------------------------------------------------------------------------------------------------------------------------------

// NodeStack, method definitions

// public static methods
    // #
    NodeStack& NodeStack::getInstance()noexcept{
        #ifdef WT_AUTODOC_DEBUG_TRACING
            debug::trace(std::source_location::current());
        #endif
        static NodeStack instance = NodeStack();
        return instance;
    }

// public methods

    // #
    NodeStack& NodeStack::addNode(AnyNode* const p_node){
        #ifdef WT_AUTODOC_DEBUG_TRACING
            debug::trace(std::source_location::current());
        #endif
        m_nodes.push_back(p_node);
        return *this;
    }
    // #
    inline const std::vector<AnyNode*>& NodeStack::nodes()const{
        #ifdef WT_AUTODOC_DEBUG_TRACING
            debug::trace(std::source_location::current());
        #endif
        return m_nodes;
    }

// ----------------------------------------------------------------------------------------------------------------------------------------

// FileStack, method definitions

// public static methods

    // #
    FileStack& FileStack::getInstance()noexcept{
        #ifdef WT_AUTODOC_DEBUG_TRACING
            debug::trace(std::source_location::current());
        #endif
        static FileStack instance = FileStack();
        return instance;
    }

// public methods

    // #
    FileStack& FileStack::addFile(FileNode* const p_file){
        #ifdef WT_AUTODOC_DEBUG_TRACING
            debug::trace(std::source_location::current());
        #endif
        m_files.push_back(p_file);
        return *this;
    }
    // #
    inline const std::vector<FileNode*>& FileStack::files()const{
        #ifdef WT_AUTODOC_DEBUG_TRACING
            debug::trace(std::source_location::current());
        #endif
        return m_files;
    }

// ----------------------------------------------------------------------------------------------------------------------------------------

// NodeCreator, method definitions

// public static methods

    // #
    std::vector<std::vector<std::string>> NodeCreator::getDocumentation(const std::string& p_file){
        #ifdef WT_AUTODOC_DEBUG_TRACING
            debug::trace(std::source_location::current());
        #endif
        std::ifstream file;
        file.open(p_file);
        if(!file.is_open()){
            // TODO log error
            std::cerr << "Error: could not open file " << p_file << std::endl;
            return std::vector<std::vector<std::string>>();
        }
        std::string line;
        std::vector<std::vector<std::string>> documentation;
        while(std::getline(file, line)){ 
            handleLine(getLineInfo(line), std::move(line), &documentation);
        }
        handleLine(LineType::FLUSH, std::string(), &documentation); // flush last section
        file.close();
        return documentation;
    }
    // #
    void NodeCreator::createNodes(std::vector<std::vector<std::string>>&& p_documentation){
        #ifdef WT_AUTODOC_DEBUG_TRACING
            debug::trace(std::source_location::current());
        #endif
        for(const std::vector<std::string>& section: p_documentation){
            for(const std::string& line: section){
                std::cout << line << std::endl;
            }
        }
    }

// private methods

    // #
    size_t NodeCreator::findComment(const std::string& p_line, size_t p_currentIndex, bool* p_currentIsComment){
        #ifdef WT_AUTODOC_DEBUG_TRACING
            debug::trace(std::source_location::current());
        #endif
        do{
            p_currentIndex = p_line.find(token::COMMENT, p_currentIndex);
            if(p_currentIndex == std::string::npos || p_currentIndex + 2 > p_line.size()) return std::string::npos;
            p_currentIndex += 2;
            if(p_line[p_currentIndex - 1] == token::MULTI_COMMENT){
                *p_currentIsComment = true;
                return p_currentIndex;
            }
        }while(p_line[p_currentIndex - 1] != token::COMMENT);
        return p_currentIndex;
    }
    // #
    size_t NodeCreator::findStartTag(const std::string& p_line, size_t p_currentIndex){
        #ifdef WT_AUTODOC_DEBUG_TRACING
            debug::trace(std::source_location::current());
        #endif
        if((p_currentIndex = p_line.find_first_not_of(token::SPACE, p_currentIndex)) == std::string::npos) return std::string::npos;
        if(p_line[p_currentIndex] != token::TAG_START) return std::string::npos;
        p_currentIndex++;
        return p_currentIndex;
    }
    // #  class:
    std::string NodeCreator::getTag(const std::string& p_line, size_t p_currentIndex, size_t* p_startOfLine){
        #ifdef WT_AUTODOC_DEBUG_TRACING
            debug::trace(std::source_location::current());
        #endif
        size_t startOfTag;
        if((p_currentIndex = p_line.find_first_not_of(token::SPACE, p_currentIndex)) == std::string::npos) return std::string();
        startOfTag = p_currentIndex;
        *p_startOfLine = startOfTag;
        if((p_currentIndex = p_line.find(token::TAG_END, p_currentIndex)) == std::string::npos) return std::string();
        return p_line.substr(startOfTag, p_currentIndex - startOfTag);
    }
    // #
    inline bool NodeCreator::isValidTag(const std::string& p_tag, const SectionType p_currentSectionType){
        #ifdef WT_AUTODOC_DEBUG_TRACING
            debug::trace(std::source_location::current());
        #endif
        if(p_currentSectionType == SectionType::NONE){
            return map::START_TAGS.find(p_tag) != map::START_TAGS.end();
        }
        return map::VALID_TAGS.at(p_currentSectionType).find(p_tag) != map::VALID_TAGS.at(p_currentSectionType).end();
    }
    // #
    inline bool NodeCreator::isContinuableTag(const std::string& p_tag){
        #ifdef WT_AUTODOC_DEBUG_TRACING
            debug::trace(std::source_location::current());
        #endif
        return map::CONTINUABLE_TAGS.find(p_tag) != map::CONTINUABLE_TAGS.end();
    }
    // #
    inline bool NodeCreator::isStartTag(const std::string& p_tag){
        #ifdef WT_AUTODOC_DEBUG_TRACING
            debug::trace(std::source_location::current());
        #endif
        return map::START_TAGS.find(p_tag) != map::START_TAGS.end();
    }
    // #
    inline bool NodeCreator::foundMultiCommentEnd(const std::string& p_line){
        return p_line.find(token::MULTI_COMMENT_END) != std::string::npos;
    }
    // #
    inline bool NodeCreator::isAtComment(const std::string& p_line, size_t p_currentIndex){
        #ifdef WT_AUTODOC_DEBUG_TRACING
            debug::trace(std::source_location::current());
        #endif
        return p_line[p_currentIndex] == token::COMMENT && (p_line[p_currentIndex + 1] == token::COMMENT 
            || p_line[p_currentIndex + 1] == token::MULTI_COMMENT);
    }
    // #
    LineInfo NodeCreator::getLineInfo(const std::string& p_line){
        #ifdef WT_AUTODOC_DEBUG_TRACING
            debug::trace(std::source_location::current());
        #endif
        static bool previousCanContinue = false; // track result of previous line
        static bool currentIsComment = false; // track if current line is a comment
        static SectionType currentSectionType = SectionType::NONE; // track current section type
        size_t currentIndex = 0;
        size_t startOfLine = 0;
        std::string tag;
        if((currentIndex = p_line.find_first_not_of(token::SPACE)) == std::string::npos){
            previousCanContinue = false;
            return LineType::NO_DOCUMENTATION;
        }
        startOfLine = currentIndex;
        if(currentIsComment){
            if(foundMultiCommentEnd(p_line)){
                currentIsComment = false;
                // TODO add doc reading to the end of multi comment
                return LineType::NO_DOCUMENTATION;
            }
            if(previousCanContinue){
                if(p_line[currentIndex] != token::TAG_START) return {LineType::CONTINUED_DOCUMENTATION, startOfLine};
                currentIndex++;
            }else{
                if(p_line[currentIndex] != token::TAG_START){
                    previousCanContinue = false;
                    return LineType::NO_DOCUMENTATION;
                }
                currentIndex++;
                startOfLine = currentIndex;
            }
        }else{
            if(previousCanContinue){
                if(isAtComment(p_line, currentIndex) && (currentIndex = findStartTag(p_line, currentIndex + 2)) == std::string::npos){
                    return {LineType::CONTINUED_DOCUMENTATION, startOfLine + 2};
                }
                startOfLine = currentIndex;
            }else{
                if((currentIndex = findComment(p_line, currentIndex, &currentIsComment)) == std::string::npos){
                    previousCanContinue = false;
                    return LineType::NO_DOCUMENTATION;
                }
                startOfLine = currentIndex;
                if((currentIndex = findStartTag(p_line, currentIndex)) == std::string::npos){
                    previousCanContinue = false;
                    return LineType::NO_DOCUMENTATION;
                }
                startOfLine = currentIndex;
            }
        }
        if((tag = getTag(p_line, currentIndex, &startOfLine)).empty()){
            previousCanContinue = false;
            return LineType::NO_DOCUMENTATION;
        }
        if(isStartTag(tag)){
            currentSectionType = map::SECTION_TYPE.at(tag);
            previousCanContinue = false;
            return {LineType::START_OF_DOCUMENTATION, startOfLine};
        } 
        if(!isValidTag(tag, currentSectionType)){
            previousCanContinue = false;
            return LineType::NO_DOCUMENTATION;
        }
        previousCanContinue = isContinuableTag(tag);
        return {LineType::DOCUMENTATION, startOfLine};
    }
    // #
    void NodeCreator::handleLine(const LineInfo& p_lineInfo, std::string&& p_line, std::vector<std::vector<std::string>>* p_documentation){
        #ifdef WT_AUTODOC_DEBUG_TRACING
            debug::trace(std::source_location::current());
        #endif
        // TODO time test with if blocks
        static std::vector<std::string> currentSection;
        switch(p_lineInfo.type){
            case LineType::FLUSH:{
                if(!currentSection.empty()){
                    p_documentation->push_back(currentSection);
                }
                break;
            }
            case LineType::NO_DOCUMENTATION:{
                break;
            }  
            case LineType::CONTINUED_DOCUMENTATION:{
                currentSection[currentSection.size() - 1]
                    .append(token::CONTINUED_LINE_BUFFER).append(cleanUpLine(std::forward<std::string>(p_line), p_lineInfo.start));
                break;
            }
            case LineType::START_OF_DOCUMENTATION:{
                if(!currentSection.empty()){
                    p_documentation->push_back(currentSection);
                    currentSection.clear();
                }
                currentSection.push_back(cleanUpLine(std::forward<std::string>(p_line), p_lineInfo.start));
                break;
            }
            case LineType::DOCUMENTATION:{
                currentSection.push_back(cleanUpLine(std::forward<std::string>(p_line), p_lineInfo.start));
                break;
            }
        }
    }
    // TODO doble chcek how && work for this
    // TODO remove lagging spaces
    // TODO chcek why somethimes double spacing
    // #
    std::string NodeCreator::cleanUpLine(std::string&& p_line, const size_t p_startingIndex){
        #ifdef WT_AUTODOC_DEBUG_TRACING
            debug::trace(std::source_location::current());
        #endif
        p_line.erase(0, p_startingIndex);
        size_t index; 
        if((index = p_line.find_first_not_of(token::SPACE)) != std::string::npos){
            p_line.erase(0, index);
        }
        if((index = p_line.find_last_not_of(token::SPACE)) != std::string::npos){
            p_line.erase(index + 1, p_line.size() - index);
        }
        return p_line;
    }

// ----------------------------------------------------------------------------------------------------------------------------------------

// Genorator, method definitions

// public static methods    

    // #
    Genorator& Genorator::getInstance()noexcept{
        #ifdef WT_AUTODOC_DEBUG_TRACING
            debug::trace(std::source_location::current());
        #endif
        static Genorator instance = Genorator();
        return instance;
    }

// public methods

    // #
    Genorator& Genorator::setLocations(int p_argc, char** p_argv){
        #ifdef WT_AUTODOC_DEBUG_TRACING
            debug::trace(std::source_location::current());
        #endif
        this->setOutputLocation(p_argv[0]).setDocsTxtLocation(p_argv[1]);
        for(int i = 3; i < p_argc; i++){
            this->addFileLocation(p_argv[i]);
        }
        return *this;
    }
    // // #
    // template<StringType T_outputLocation, StringType T_docsTxtLocation, StringVectorType T_files> 
    // Genorator& Genorator::setFileLocations(T_outputLocation&& p_outputLocation, T_docsTxtLocation&& p_docsTxtLocation, T_files&& p_files){
    //     this->setOutputLocation(std::forward<T_outputLocation>(p_outputLocation))
    //         .setDocsTxtLocation(std::forward<T_docsTxtLocation>(p_docsTxtLocation)).setFileLocations(std::forward<T_files>(p_files));
    //     return *this;
    // }
    // #
    Genorator& Genorator::parseProgramFiles(){
        #ifdef WT_AUTODOC_DEBUG_TRACING
            debug::trace(std::source_location::current());
        #endif
        // for(std::vector<std::string> g: NodeCreator::getDocumentation("genorator/include/nodes.hpp")){
        //     for(const std::string& line: g){
        //         std::cout << line << std::endl;
        //     }
        // }
        for(const std::string& file: m_fileLocations){
            NodeCreator::createNodes(NodeCreator::getDocumentation(file));
        }
        return *this;
    }
    // #
    Genorator& Genorator::generateDocumentation(){
        #ifdef WT_AUTODOC_DEBUG_TRACING
            debug::trace(std::source_location::current());
        #endif
        
        return *this;
    }

// private methods

    // #
    Genorator& Genorator::setOutputLocation(const std::string& p_outputLocation){
        #ifdef WT_AUTODOC_DEBUG_TRACING
            debug::trace(std::source_location::current());
        #endif
        m_outputLocation = p_outputLocation;
        return *this;
    }
    // #
    Genorator& Genorator::setOutputLocation(std::string&& p_outputLocation){
        #ifdef WT_AUTODOC_DEBUG_TRACING
            debug::trace(std::source_location::current());
        #endif
        m_outputLocation = std::forward<std::string>(p_outputLocation);
        return *this;
    }
    // #
    Genorator& Genorator::setDocsTxtLocation(const std::string& p_docsTxtLocation){
        #ifdef WT_AUTODOC_DEBUG_TRACING
            debug::trace(std::source_location::current());
        #endif
        m_docsTxtLocation = p_docsTxtLocation;
        return *this;
    }
    // #
    Genorator& Genorator::setDocsTxtLocation(std::string&& p_docsTxtLocation){
        #ifdef WT_AUTODOC_DEBUG_TRACING
            debug::trace(std::source_location::current());
        #endif
        m_docsTxtLocation = std::forward<std::string>(p_docsTxtLocation);
        return *this;
    }
    // #
    Genorator& Genorator::addFileLocation(const std::string& p_fileLocation){
        #ifdef WT_AUTODOC_DEBUG_TRACING
            debug::trace(std::source_location::current());
        #endif
        m_fileLocations.push_back(p_fileLocation);
        return *this;
    }
    // #
    Genorator& Genorator::addFileLocation(std::string&& p_fileLocation){
        #ifdef WT_AUTODOC_DEBUG_TRACING
            debug::trace(std::source_location::current());
        #endif
        m_fileLocations.push_back(std::forward<std::string>(p_fileLocation));
        return *this;
    }
    // #
    Genorator& Genorator::setFileLocations(const std::vector<std::string>& p_fileLocations){
        #ifdef WT_AUTODOC_DEBUG_TRACING
            debug::trace(std::source_location::current());
        #endif
        m_fileLocations = p_fileLocations;
        return *this;
    }
    // #
    Genorator& Genorator::setFileLocations(std::vector<std::string>&& p_fileLocations){
        #ifdef WT_AUTODOC_DEBUG_TRACING
            debug::trace(std::source_location::current());
        #endif
        m_fileLocations = std::forward<std::vector<std::string>>(p_fileLocations);
        return *this;
    }

} // worTech::cdocs::genorator::helpers