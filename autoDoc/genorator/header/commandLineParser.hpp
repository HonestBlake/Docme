#pragma once

#include "autoDoc.hpp"

// #file: commandLineProccessor.hpp, header file

// adoc -p docPacket -c path/to/config.doc -o path/to/output/dir/ -f path/to/single/file.cpp -d path/to/source/dir/ -i path/to/ingnored/file.cpp

namespace worTech::autoDoc::genorator::commandLineParser{


    const std::unordered_set<std::string> CDOC_VALID_FILE_EXTENTIONS = {
        ".cpp", 
        ".hpp", 
        ".h", 
        ".c", 
        ".cc", 
        ".cxx", 
        ".c++", 
        ".h++", 
        ".hh", 
        ".hxx", 
        ".h++"
    };
    const std::unordered_set<std::string> AUTO_DOC_VALID_FILE_EXTENTIONS = {
        ".doc",
        ".txt"
    };
    



    constexpr std::string VALID_CONFIG_FILE_EXTENSION = ".txt";

    // #enum: CommandLineTag, uint8_t enum class
    enum class CommandLineTag: uint8_t{
        DOC_PACKET,
        CONFIG_FILE,
        OUTPUT_DIRECTORY,
        SOURCE,
        IGNORE 
    };
    // #enum: DocPacket, uint8_t enum class
    enum class DocPacket: uint8_t{
        AUTO_DOC,
        CDOC
    };

    // TODO fix this function
    

    // #namespace: commandLineTags(tag), variable namespace
    namespace commandLineTags{
        constexpr std::string DOC_PACKET = "-p";
        constexpr std::string CONFIG_FILE = "-c";
        constexpr std::string OUTPUT_DIRECTORY = "-o";
        constexpr std::string SOURCE = "-s";
        constexpr std::string IGNORE = "-i";
    } namespace tag = commandLineTags;
    // #namespace: commandLineMaps(map), variable namespace
    namespace commandLineMaps{
        const std::unordered_map<std::string, CommandLineTag> COMMAND_LINE_TAGS = {
            {tag::DOC_PACKET, CommandLineTag::DOC_PACKET},
            {tag::CONFIG_FILE, CommandLineTag::CONFIG_FILE},
            {tag::OUTPUT_DIRECTORY, CommandLineTag::OUTPUT_DIRECTORY},
            {tag::SOURCE, CommandLineTag::SOURCE},
            {tag::IGNORE, CommandLineTag::IGNORE}
        };
        const std::unordered_map<std::string, DocPacket> DOC_PACKETS = {
            {"cdoc", DocPacket::CDOC}
        };
    } namespace map = commandLineMaps;
    // #class: CommandLineParser, singleton class
    class CommandLineParser{
    public:
    // public factory methods
        CommandLineParser(const CommandLineParser&) = delete; // delete copy constructor
        ~CommandLineParser() = default; // default destructor
    // public operators
        CommandLineParser& operator=(const CommandLineParser&) = delete; // delete copy assignment operator
    // public static methods
        static CommandLineParser& get()noexcept;
    // public methods
        CommandLineParser& parseCommandLine(int p_argc, char** p_argv)noexcept;
    private:
    // private factory methods
        CommandLineParser();
    // private methods
        bool isValidFileExtension(std::string&& p_fileExtension, DocPacket p_packet)noexcept;
        void handleDocPacket(const std::string& p_arg)noexcept;
        void handleConfigFile(const std::string& p_arg)noexcept;
        void handleOutputDirectory(const std::string& p_arg)noexcept;
        void handleSource(const std::string& p_arg)noexcept;
        void handleIgnore(const std::string& p_arg)noexcept;
        void handleTag(const CommandLineTag p_tag, const std::string& p_arg)noexcept;
    // private members
        std::vector<DocPacket> m_docPackets;
        std::string m_configFile;
        std::string m_outputDirectory;
        std::vector<std::string> m_sourceFiles;
        std::vector<std::string> m_soruceDirectories;
        std::vector<std::string> m_ignoreFiles;
    };

} // namespace worTech::autoDoc::genorator::commandLineProccessor