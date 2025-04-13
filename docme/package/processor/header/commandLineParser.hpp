#pragma once

#include "processor.hpp"

#include "docPackets.hpp" 
#include "docmeInfo.hpp" 

// #file: commandLineParser.hpp, header file

namespace worTech::docme::processor::commandLineParser{

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
    // #namespace: commandLineVariables(commandLine), variable namespace
    namespace commandLineVariables{
        constexpr std::string COMMAND_SPECIFIER = "--";
        constexpr std::string TAG_SPECIFIER = "-";
        constexpr std::string HELP = COMMAND_SPECIFIER + "help";
        constexpr std::string VERSION = COMMAND_SPECIFIER + "version";
        constexpr std::string CONFIGURE = COMMAND_SPECIFIER + "configure";
        constexpr std::string ROOT_DIR = TAG_SPECIFIER + 'r';
        constexpr std::string DOC_PACKET = TAG_SPECIFIER + 'p';
        constexpr std::string CONFIG_FILE = TAG_SPECIFIER + 'c';
        constexpr std::string OUTPUT_DIRECTORY = TAG_SPECIFIER + 'o';
        constexpr std::string SOURCE = TAG_SPECIFIER + 's';
        constexpr std::string IGNORE = TAG_SPECIFIER + 'i';
        const std::unordered_map<std::string, Token> FLAGS = {
            {ROOT_DIR, Token::ROOT_DIR},
            {DOC_PACKET, Token::DOC_PACKET},
            {CONFIG_FILE, Token::CONFIG_FILE},
            {OUTPUT_DIRECTORY, Token::OUTPUT_DIRECTORY},
            {SOURCE, Token::SOURCE},
            {IGNORE, Token::IGNORE}
        };
        const std::unordered_map<std::string, Token> SPECIAL_FLAGS = {
            {HELP, Token::HELP},
            {VERSION, Token::VERSION},
            {CONFIGURE, Token::CONFIGURE}
        };
        constexpr std::string CONFIG_FILE_TYPE = ".json";
        constexpr std::array<Token, 6> EVALUATION_ORDER = {
            Token::ROOT_DIR,
            Token::DOC_PACKET,
            Token::CONFIG_FILE,
            Token::OUTPUT_DIRECTORY,
            Token::SOURCE,
            Token::IGNORE
        };
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
        CommandLineParser& parse(int p_argc, char* p_argv[])noexcept;
        ParserInfo parserInfo()const noexcept;
        GeneratorInfo generatorInfo()const noexcept;
        #ifdef WT_DOCME_DEBUGGING
        void printInternalData()noexcept;
        #endif
    private:
    // private factory methods
        CommandLineParser();
    // private static methods
        void help()const noexcept;
        void version()const noexcept;
        void configure()const noexcept;
    // private methods
        std::unordered_map<Token, std::vector<std::string>> tokenizeCommandLine(std::vector<std::string>& p_args)noexcept;
        void setDefaultValues()noexcept;
        void removeIgnoreFiles()noexcept;
        bool isValidFileType(const std::filesystem::path& p_file)noexcept;
        void handleRootDirectory(std::string&& p_directory)noexcept;
        void handlePacket(const std::string& p_packet)noexcept;
        void handleConfigFile(std::string&& p_file)noexcept;
        void handleOutputDirectory(std::string&& p_directory)noexcept;
        void handleSource(std::string&& p_source)noexcept;
        void handleIgnore(std::string&& p_ignore)noexcept;
        void handleSpecialFlag(const Token p_specialFlag)noexcept;
        void handleArgument(const Token p_flag, std::string&& p_arg)noexcept;
        void handleCommandLine(std::unordered_map<Token, std::vector<std::string>>&& p_commandLine)noexcept;
    // private members
        std::filesystem::path m_rootDirectory;
        std::unordered_set<std::filesystem::path> m_ignoreFiles;
        ParserInfo m_parserInfo;
        GeneratorInfo m_generatorInfo;

        std::filesystem::path m_configFile;
        // std::filesystem::path m_outputDirectory;
        // std::unordered_set<Packet> m_packets;
        // std::unordered_set<std::filesystem::path> m_sourceFiles;
    };

} // namespace worTech::autoDoc::generator::commandLineParser