// #file: commandLine.hpp, module header file

#pragma once

#include "engine/engine.hpp" // Project header

#include "header/jsonTools.hpp" // JsonTools header

#include "engine/header/packets.hpp" // Packet header
#include "engine/header/parser.hpp" // Parser header
#include "engine/header/generator.hpp" // Generator header
#include "engine/header/docmeEngine.hpp" // DocmeEngine header


// #file: commandLineParser.hpp, header file

namespace docme::engine::commandLine{

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
        inline const std::map<Flag, std::string> FLAG_NAMES = {
            {Flag::ROOT_DIR, ROOT_DIR},
            {Flag::DOC_PACKET, DOC_PACKET},
            {Flag::CONFIG_FILE, CONFIG_FILE},
            {Flag::OUTPUT_DIRECTORY, OUTPUT_DIRECTORY},
            {Flag::SOURCE, SOURCE},
            {Flag::IGNORE, IGNORE},
            {Flag::HELP, HELP},
            {Flag::VERSION, VERSION},
            {Flag::CONFIGURE, CONFIGURE}
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
        CommandLineParser(const int p_argc, const char* p_argv[])noexcept;
        CommandLineParser(const CommandLineParser&)noexcept = default; // #default: CommandLineParser(const CommandLineParser&)noexcept, default copy constructor
        CommandLineParser(CommandLineParser&&)noexcept = default; // #default: CommandLineParser(CommandLineParser&&)noexcept, default move constructor
        ~CommandLineParser()noexcept = default; // #default: ~CommandLineParser()noexcept, default destructor
    // public operators
        CommandLineParser& operator=(const CommandLineParser&)noexcept = default; // #default: operator=(const CommandLineParser&)noexcept, default copy assignment operator
        CommandLineParser& operator=(CommandLineParser&&)noexcept = default; // #default: operator=(CommandLineParser&&)noexcept, default move assignment operator
    // public methods
        CommandLineParser& parse()&; 
        CommandLineParser parse()&&;
        const EngineInfo& info()const&;
        EngineInfo& info()&; 
        EngineInfo info()&&;
    #ifdef WT_DOCME_DEBUGGING
        void printInternalData();
    #endif
    private:
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
    // private members
        std::vector<std::string> m_args;
        std::map<Flag, std::vector<std::string>, FlagComparer> m_commandLine;
        std::filesystem::path m_rootDirectory;
        
        EngineInfo m_info;
        // ParserInfo m_parserInfo;
        // GeneratorInfo m_generatorInfo;
        
        // std::filesystem::path m_outputDirectory;
        // std::unordered_set<Packet> m_packets;
        // std::unordered_set<std::filesystem::path> m_sourceFiles;

    }; // #end: CommandLineParser

} // namespace generator::commandLineParser