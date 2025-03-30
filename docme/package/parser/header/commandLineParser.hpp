#pragma once

#include "parser.hpp"

#include "docPackets.hpp" 

// #file: commandLineProccessor.hpp, header file

// adoc -p docPacket -c path/to/config.doc -o path/to/output/dir/ -f path/to/single/file.cpp -d path/to/source/dir/ -i path/to/ingnored/file.cpp

namespace worTech::docme::genorator::commandLineParser{

    // #enum: CommandLineToken(Token), uint8_t enum class
    enum class CommandLineToken: uint8_t{
        ROOT_DIR,
        DOC_PACKET,
        CONFIG_FILE,
        OUTPUT_DIRECTORY,
        SOURCE,
        IGNORE,
        HELP,
        VERSION,
        CONFIGURE
    };
    // #namspace: commandLineVariables, variable namespace
    namespace commandLineVariables{
        constexpr std::string COMMAND_SPECIFIER = "--";
        constexpr std::string TAG_SPECIFIER = "-";
        constexpr std::string HELP = COMMAND_SPECIFIER + "help";
        constexpr std::string VERSION = COMMAND_SPECIFIER + "version";
        constexpr std::string CONFIGURE = COMMAND_SPECIFIER + "config";
        constexpr std::string ROOT_DIR = TAG_SPECIFIER + 'r';
        constexpr std::string DOC_PACKET = TAG_SPECIFIER + 'p';
        constexpr std::string CONFIG_FILE = TAG_SPECIFIER + 'c';
        constexpr std::string OUTPUT_DIRECTORY = TAG_SPECIFIER + 'o';
        constexpr std::string SOURCE = TAG_SPECIFIER + 's';
        constexpr std::string IGNORE = TAG_SPECIFIER + 'i';
        const std::unordered_map<std::string, Token> TOKENS = {
            {ROOT_DIR, Token::ROOT_DIR},
            {DOC_PACKET, Token::DOC_PACKET},
            {CONFIG_FILE, Token::CONFIG_FILE},
            {OUTPUT_DIRECTORY, Token::OUTPUT_DIRECTORY},
            {SOURCE, Token::SOURCE},
            {IGNORE, Token::IGNORE},
            {HELP, Token::HELP},
            {VERSION, Token::VERSION},
            {CONFIGURE, Token::CONFIGURE}
        };
        constexpr std::string CONFIG_FILE_TYPE = ".json";
    }
    // #class: CommandLineParser, singleton class
    class CommandLineParser{
    public:
    // public factory methods
        CommandLineParser(const CommandLineParser&) = delete; // delete copy constructor
        CommandLineParser(CommandLineParser&&) = delete; // delete move constructor
        ~CommandLineParser() = default; // default destructor
    // public operators
        CommandLineParser& operator=(const CommandLineParser&) = delete; // delete copy assignment operator
    // public static methods
        static CommandLineParser& get()noexcept;
    // public methods
        CommandLineParser& parse(int p_argc, char** p_argv)noexcept;
        #ifdef WT_AUTODOC_DEBUGGING
        void printInternalData()noexcept;
        #endif
    private:
    // private factory methods
        CommandLineParser();
    // private methods
        bool isValidFileType(const std::filesystem::path& p_file)noexcept;
        void handleRootDirectory(std::string&& p_directory)noexcept;
        void handlePacket(const std::string& p_packet)noexcept;
        void handleConfigFile(std::string&& p_file)noexcept;
        void handleOutputDirectory(std::string&& p_directory)noexcept;
        void handleSource(std::string&& p_source)noexcept;
        void handleIgnore(std::string&& p_ignore)noexcept;
        void handleToken(const Token p_token, std::string&& p_arg)noexcept;
    // private members
        bool m_handledSource;
        bool m_handledIgnore;
        std::string m_rootDirectory;
        std::string m_configFile;
        std::string m_outputDirectory;
        std::unordered_set<Packet> m_packets;
        std::unordered_set<std::string> m_sourceFiles;
        std::unordered_set<std::string> m_ignoreFiles;
    };

} // namespace worTech::autoDoc::genorator::commandLineProccessor