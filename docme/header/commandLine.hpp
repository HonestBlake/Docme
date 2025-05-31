// #file: commandLine.hpp, module header file

#pragma once

#include "docme.hpp" // Project header

#include "packets.hpp" 
#include "docmeInfo.hpp" 
#include "jsonTools.hpp" // Json parsing tools

// #file: commandLineParser.hpp, header file

namespace worTech::docme::commandLine{

    // #enum: CommandLineFlag, uint8_t enum struct
    enum struct CommandLineFlag: uint8_t{
        ROOT_DIR,
        DOC_PACKET,
        CONFIG_FILE,
        OUTPUT_DIRECTORY,
        SOURCE,
        IGNORE,
        HELP,
        VERSION,
        CONFIGURE
    }; // #end: CommandLineFlag

    // #namespace: commandLineVariables, variable namespace
    namespace commandLineVariables{
        inline constexpr std::string COMMAND_SPECIFIER = "--";
        inline constexpr std::string TAG_SPECIFIER = "-";
        inline constexpr std::string HELP = COMMAND_SPECIFIER + "help";
        inline constexpr std::string VERSION = COMMAND_SPECIFIER + "version";
        inline constexpr std::string CONFIGURE = COMMAND_SPECIFIER + "configure";
        inline constexpr std::string ROOT_DIR = TAG_SPECIFIER + 'r';
        inline constexpr std::string DOC_PACKET = TAG_SPECIFIER + 'p';
        inline constexpr std::string CONFIG_FILE = TAG_SPECIFIER + 'c';
        inline constexpr std::string OUTPUT_DIRECTORY = TAG_SPECIFIER + 'o';
        inline constexpr std::string SOURCE = TAG_SPECIFIER + 's';
        inline constexpr std::string IGNORE = TAG_SPECIFIER + 'i';
        inline const std::map<std::string, Flag> FLAGS = {
            {ROOT_DIR, Flag::ROOT_DIR},
            {DOC_PACKET, Flag::DOC_PACKET},
            {CONFIG_FILE, Flag::CONFIG_FILE},
            {OUTPUT_DIRECTORY, Flag::OUTPUT_DIRECTORY},
            {SOURCE, Flag::SOURCE},
            {IGNORE, Flag::IGNORE}
        };
        inline const std::map<std::string, Flag> SPECIAL_FLAGS = {
            {HELP, Flag::HELP},
            {VERSION, Flag::VERSION},
            {CONFIGURE, Flag::CONFIGURE}
        };
        inline constexpr std::string CONFIG_FILE_TYPE = ".json";
        inline constexpr std::array<Flag, 6> EVALUATION_ORDER = {
            Flag::CONFIG_FILE,
            Flag::ROOT_DIR,
            Flag::DOC_PACKET,
            Flag::OUTPUT_DIRECTORY,
            Flag::SOURCE,
            Flag::IGNORE
        };
    } // #end: commandLineVariables

    namespace configFileKeys{
        inline constexpr std::string PACKETS = "packets";
        inline constexpr std::string ROOT_DIRECTORY = "root_directory";
        inline const std::string OUTPUT_DIRECTORY = "output_directory";
        inline constexpr std::string SOURCE = "sources";
        inline constexpr std::string IGNORE = "ignores";
    }

    // #struct: CommandLineFlagComparer, Comparison struct
    struct CommandLineFlagComparer{
        bool operator()(const Flag& p_lhs, const Flag& p_rhs)const;
    }; // #end: CommandLineFlagComparer

    // #class: CommandLineParser, Final singleton class
    class CommandLineParser final{
    public:
    // public factory methods
        CommandLineParser(const CommandLineParser&)noexcept = delete; // #delete: CommandLineParser(const CommandLineParser&)noexcept, deleted copy constructor
        CommandLineParser(CommandLineParser&&)noexcept = delete; // #delete: CommandLineParser(CommandLineParser&&)noexcept, deleted move constructor
        ~CommandLineParser()noexcept = default; // #default: ~CommandLineParser()noexcept, default destructor
    // public operators
        CommandLineParser& operator=(const CommandLineParser&)noexcept = delete; // #delete: operator=(const CommandLineParser&)noexcept, deleted copy assignment operator
        CommandLineParser& operator=(CommandLineParser&&)noexcept = delete; // #delete: operator=(CommandLineParser&&)noexcept, deleted move assignment operator
    // public static methods
        static CommandLineParser& get(int p_argc = 0, char* p_argv[] = nullptr);
    // public methods
        CommandLineParser& parse();
        ParserInfo parserInfo()const;
        GeneratorInfo generatorInfo()const;
    #ifdef WT_DOCME_DEBUGGING
        void printInternalData();
    #endif
    private:
    // private factory methods
        CommandLineParser(int p_argc, char* p_argv[])noexcept;
    // private static methods
        static void help();
        static void version();
        static void configure();
    // private methods
        void setDefaultValues();
        void parseCommandLine();
        void parseArgument(std::string& p_arg, std::optional<Flag>& p_flag);
        void handleSpecialFlag(const Flag p_specialFlag);
        void handleCommandLine();
        void handleArgument(const Flag p_flag, std::string&& p_arg);
        void handleRootDirectory(std::string&& p_directory);
        void handlePacket(std::string&& p_packet);
        void handleConfigFile(std::string&& p_file);
        void parseConfigFile(const std::filesystem::path& p_file);
        void handleOutputDirectory(std::string&& p_directory);
        void handleSource(std::string&& p_source);
        void handleIgnore(std::string&& p_ignore);
    // private static members
        static inline bool s_isInitialized = false; // If object has been initialized
    // private members
        std::vector<std::string> m_args;
        std::map<Flag, std::vector<std::string>, FlagComparer> m_commandLine;
        std::filesystem::path m_rootDirectory;
        ParserInfo m_parserInfo;
        GeneratorInfo m_generatorInfo;
        
        // std::filesystem::path m_outputDirectory;
        // std::unordered_set<Packet> m_packets;
        // std::unordered_set<std::filesystem::path> m_sourceFiles;

    }; // #end: CommandLineParser

} // namespace worTech::autoDoc::generator::commandLineParser