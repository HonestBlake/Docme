#include "commandLineParser.hpp"

// TODO esure order of cml
// TODO fix relatice calls to file and dir for json

namespace worTech::docme::genorator::commandLineParser{

// CommandLineOption data struct, method definitions

    // #func: operator==(), public const noexcept method4

    // #param: const CommandLineOption& p_option, given command line option
    // #return: bool, weather command line options are equal
    bool CommandLineOption::operator==(const CommandLineOption& p_option)const noexcept{
        if constexpr(state::TRACING){ // Function tracing
            debug::trace(std::source_location::current());
        }
        return flag == p_option.flag;
    }
    // #func: hash(), public const noexcept method

    // #return: size_t, hash of command line option
    size_t CommandLineOption::hash()const noexcept{
        if constexpr(state::TRACING){ // Function tracing
            debug::trace(std::source_location::current());
        }
        return std::hash<std::underlying_type_t<Token>>{}(static_cast<std::underlying_type_t<Token>>(*flag));
    }


// -------------------------------------------------------------------------------------------------------------------------------------

// CommandLineParser singleton class, method definitions

// public static methods

    // #func: get(), public static noexcept method

    // #return: CommandLineParser&, singleton instance of CommandLineParser
    CommandLineParser& CommandLineParser::get()noexcept{
        if constexpr(state::TRACING){ // Function tracing
            debug::trace(std::source_location::current());
        }
        static CommandLineParser instance = CommandLineParser();
        return instance;
    }

// public methods

    // #func: parse(), public noexcept method

    // #param: p_argc, int, number of command line arguments
    // #param: p_argv, char**, command line arguments
    // #return: CommandLineParser&, reference to current instance
    CommandLineParser& CommandLineParser::parse(const int p_argc, char* p_argv[])noexcept{
        if constexpr(state::TRACING){ // Function tracing
            debug::trace(std::source_location::current());
        }
        if(p_argc < 2){ // Check if any command line args were provided
            debug::error(error::NO_COMMAND_LINE_ARGUMENTS);
        }
        // Move command line args to to string vector
        std::vector<std::string> args;
        args.reserve(p_argc - 1); 
        for(int i = 1; i < p_argc; i++){
            args.emplace_back(p_argv[i]);
        }
        setDefaultValues();
        handleCommandLine(tokenizeCommandLine(args)); 
        return *this;
    }
    #ifdef WT_AUTODOC_DEBUGGING
    // #func: printInternalData(), public noexcept method
    void CommandLineParser::printInternalData()noexcept{
        if constexpr(state::TRACING){ // Function tracing
            debug::trace(std::source_location::current());
        }
        std::cout << "Root Directory: " << m_rootDirectory.string() << std::endl;
        std::cout << "Config File: " << m_configFile.string() << std::endl;
        std::cout << "Output Directory: " << m_outputDirectory.string() << std::endl;
        std::cout << "Packets: ";
        for(const Packet packet: m_packets){
        std::cout << packet.name() << " ";
        }
        std::cout << std::endl;
        std::cout << "Source Files: ";
        for(const std::string& file: m_sourceFiles){
            std::cout << file << " ";
        }
        std::cout << std::endl;
        std::cout << "Ignore Files: ";
        for(const std::string& file: m_ignoreFiles){
            std::cout << file << " ";
        }
        std::cout << std::endl;
    }
    #endif

// private factory methods

    // #func: CommandLineParser(), private constructor
    CommandLineParser::CommandLineParser(){
        if constexpr(state::TRACING){ // Function tracing
            debug::trace(std::source_location::current());
        }
        // m_rootDirectory = std::filesystem::current_path().string();
    }

// private static methods

    // #func: help(), private noexcept method
    void CommandLineParser::help()const noexcept{
        if constexpr(state::TRACING){ // Function tracing
            debug::trace(std::source_location::current());
        }
        debug::warn("Command help is not implemented yet");
    }
    // #func: version(), private noexcept method
    void CommandLineParser::version()const noexcept{
        if constexpr(state::TRACING){ // Function tracing
            debug::trace(std::source_location::current());
        }
        debug::warn("Version is not implemented yet");
    }
    // #func: configure(), private noexcept method
    void CommandLineParser::configure()const noexcept{
        if constexpr(state::TRACING){ // Function tracing
            debug::trace(std::source_location::current());
        }
        debug::warn("Command configure is not implemented yet");
    }

// private methods

    // #func: addOption(std::unordered_set<Option>&, Option&), private noexcept method

    // #param: std::unordered_set<Option>& p_options, command line options
    // #param: Option& p_option, command line option
    void CommandLineParser::addOptionToCommandLine(std::unordered_set<Option>& p_commandLine, Option& p_option)noexcept{
        if constexpr(state::TRACING){ // Function tracing
            debug::trace(std::source_location::current());
        }
        if(p_commandLine.contains(p_option)){ // Check if option already exists in options
            const_cast<Option&>(*p_commandLine.find(p_option)).arguments.insert(p_option.arguments.end(), std::make_move_iterator(p_option.arguments.begin()), std::make_move_iterator(p_option.arguments.end())); // Merge arguments with existing option
        }else{ // Option does not exist in options
            p_commandLine.emplace(p_option.flag, std::move(p_option.arguments)); // Emplace a Option object with flags and arguments
        }
        // Reset option arguements
        p_option.arguments.clear(); 
        p_option.arguments.shrink_to_fit();
    }
    // #func: tokenizeCommandLine(std::vector<std::string>&), private noexcept method

    // #param: std::vector<std::string>& p_args, command line args
    // #return: std::unordered_set<Option>, vector of tokenized command line options
    std::unordered_set<Option> CommandLineParser::tokenizeCommandLine(std::vector<std::string>& p_args)noexcept{
        if constexpr(state::TRACING){ // Function tracing
            debug::trace(std::source_location::current());
        }
        Option option;
        std::unordered_set<Option> commandLine;
        for(std::string& arg: p_args){
            if(commandLine::SPECIAL_FLAGS.contains(arg)){ // Check if arg is a command line special flag
                if(p_args.size() < 2){ // Check if command line command has any other args or flags
                    debug::error(error::ARGS_WITH_SPECIAL_FLAG_CALL, arg);
                }
                handleCommand(commandLine::SPECIAL_FLAGS.at(arg)); 
            }
            if(commandLine::FLAGS.contains(arg)){ // Check if arg is a command line flag
                if(!option.arguments.empty()){
                    addOptionToCommandLine(commandLine, option); // Add option to command line
                }else{
                    debug::warn(error::NO_ARGS_GIVEN_TO_FLAG, arg); 
                }
                option.flag = commandLine::FLAGS.at(arg); 
            }else{ // Arg is an argument
                if(!option.flag){ // Check if flag is not set
                    debug::error(error::UNRECONIZED_COMMAND_LINE_ARGUMENT, arg);
                }
                option.arguments.emplace_back(std::move(arg)); // Move arg to arguments
            }
        }
        if(!option.arguments.empty()){
            addOptionToCommandLine(commandLine, option); // Add last option to command line
        }else{
            debug::warn(error::NO_ARGS_GIVEN_TO_FLAG); 
        }
        return commandLine; 
    }
    // TODO handle error with reverse map to find flag from token


    // #func: setDefaultValues(), private noexcept method
    void CommandLineParser::setDefaultValues()noexcept{
        if constexpr(state::TRACING){ // Function tracing
            debug::trace(std::source_location::current());
        }
        m_rootDirectory = std::filesystem::current_path(); // Set default root directory to program call site
        m_packets.emplace(Packet::get(packet::DOCME)); // Add default docme packet to packets
    }
    // #func: isValidFile(const std::filesystem::path&), private noexcept method

    // #param: const std::filesystem::path& p_file, file being checked
    // #return: bool, weather file extension is valid for packet
    bool CommandLineParser::isValidFileType(const std::filesystem::path& p_file)noexcept{
        if constexpr(state::TRACING){ // Function tracing
            debug::trace(std::source_location::current());
        }
        // Check file type against each file type in each packet 
        for(const Packet& packet: m_packets){
            for(const std::string& fileType: packet.fileTypes()){
                if(p_file.extension().string() == fileType) return true; // File type found in packets 
            }
        } // for
        return false; // File type not found in packets
    }
    // #func: handleRootDirectory(std::string&&), private noexcept method

    // #param: std::string&& p_directory, given root directory
    void CommandLineParser::handleRootDirectory(std::string&& p_directory)noexcept{
        if constexpr(state::TRACING){ // Function tracing
            debug::trace(std::source_location::current());
        }
        std::filesystem::path directory =  std::filesystem::path(p_directory);
        if(!std::filesystem::exists(directory)){ // Check if directory cannot be found
            debug::error(error::COULD_NOT_FIND_ROOT_DIRECTORY, p_directory);
        }else if(!std::filesystem::is_directory(directory)){ // Check if directory is valid
            debug::error(error::INVALID_ROOT_DIRECTORY, p_directory);
        }
        m_rootDirectory = std::forward<std::string>(p_directory);
    }
    // #func: handlePacket(const std::string&), private noexcept method

    // #param: const std::string& p_packet, given packet
    void CommandLineParser::handlePacket(const std::string& p_packet)noexcept{
        if constexpr(state::TRACING){ // Function tracing
            debug::trace(std::source_location::current());
        }
        m_packets.insert(Packet::get(p_packet)); // Get packet and add to packets
    }
    // #func: handleConfigFile(std::string&&), private noexcept method

    // #param: std::string&& p_arg, given config file
    void CommandLineParser::handleConfigFile(std::string&& p_file)noexcept{
        if constexpr(state::TRACING){ // Function tracing
            debug::trace(std::source_location::current());
        }
        std::filesystem::path file =  std::filesystem::path(p_file);
        if(!std::filesystem::exists(file)){ // Check if file cannot be found
            debug::error(error::COULD_NOT_FIND_CONFIG_FILE, p_file);
        }else if(file.extension().string() != commandLine::CONFIG_FILE_TYPE){ // Check if config file is invalid type
            debug::error(error::INVALID_CONFIG_FILE_TYPE, commandLine::CONFIG_FILE_TYPE, p_file);
        }
        m_configFile = std::forward<std::string>(p_file);
    }
    // #func: handleOutputDirectory(std::string&&), private noexcept method

    // #param: std::string&& p_directory, given ourput directory
    void CommandLineParser::handleOutputDirectory(std::string&& p_directory)noexcept{
        if constexpr(state::TRACING){ // Function tracing
            debug::trace(std::source_location::current());
        }
        std::filesystem::path directory =  std::filesystem::path(p_directory);
        if(!std::filesystem::exists(directory)){ // Check if output directory cannot be found
            if(m_outputDirectory.empty()){ // Check if output directory is default set
                debug::error(error::COULD_NOT_FIND_OUTPUT_DIRECTORY, p_directory);
            }else{
                debug::warn(error::COULD_NOT_FIND_OUTPUT_DIRECTORY, p_directory); 
                return;
            }
        }else if(!std::filesystem::is_directory(directory)){ // Check if output directory is valid
            if(m_outputDirectory.empty()){ // Check if output directory is default set
                debug::error(error::INVALID_OUTPUT_DIRECTORY, p_directory);
            }else{
                debug::warn(error::INVALID_OUTPUT_DIRECTORY, p_directory); 
                return;
            }
        }
        m_outputDirectory = std::forward<std::string>(p_directory);
    }
    // #func: handleSource(std::string&&), private noexcept method

    // #param: std::string&& p_source, given source
    void CommandLineParser::handleSource(std::string&& p_source)noexcept{
        if constexpr(state::TRACING){ // Function tracing
            debug::trace(std::source_location::current());
        }
        std::filesystem::path source =  m_rootDirectory / std::filesystem::path(p_source);
        if(!std::filesystem::exists(source)){ // Check if source cannot be found
            debug::warn(error::COULD_NOT_FIND_SOURCE, p_source);
            return;
        }
        if(std::filesystem::is_directory(source)){ // Source is a directory
            // Check each file in directory to see if the file type is valid
            for(const std::filesystem::directory_entry& entry : std::filesystem::recursive_directory_iterator(source)){
                if(isValidFileType(entry.path())){
                    m_sourceFiles.emplace(entry.path().string());
                }
            }
        }else{ // Source is a file
            if(isValidFileType(source)){
                m_sourceFiles.emplace(std::forward<std::string>(p_source));
            }else{
                debug::warn(error::INVALID_SOURCE_FILE_TYPE, p_source);
                return;
            }
        }
    }
    // #func: handleIgnore(std::string&&), private noexcept method
    
    // #param: std::string&& p_ingore, given ignore
    void CommandLineParser::handleIgnore(std::string&& p_ingore)noexcept{
        if constexpr(state::TRACING){ // Function tracing
            debug::trace(std::source_location::current());
        }
        std::filesystem::path ignore =  m_rootDirectory / std::filesystem::path(p_ingore);
        if(!std::filesystem::exists(ignore)){ // Check if ignore cannot be found
            debug::warn(error::COULD_NOT_FIND_IGNORE, p_ingore);
            return;
        }
        if(std::filesystem::is_directory(ignore)){ // Ignore is a directory
            // Find each file in directory
            for(const std::filesystem::directory_entry& entry : std::filesystem::recursive_directory_iterator(ignore)){
                if(isValidFileType(entry.path())){ // Check if file type is valid
                    m_ignoreFiles.emplace(entry.path().string());
                }
            }
        }else{ // Ignore is a file
            if(isValidFileType(ignore)){
                m_ignoreFiles.emplace(std::forward<std::string>(p_ingore));
            }
        }
    }
    // #func: handleCommand(const Token), private noexcept method

    // #param: const Token p_command, command line command
    void CommandLineParser::handleCommand(const Token p_command)noexcept{
        if constexpr(state::TRACING){ // Function tracing
            debug::trace(std::source_location::current());
        }
        switch(p_command){
        case Token::HELP:
            help();
            break;
        case Token::VERSION:
            version();
            break;
        case Token::CONFIGURE:
            configure();
            break;
        } // switch
    }
    // #func: handleArgument(const Tag, std::string&&), private noexcept method

    // #param: const Tag p_tag, command line tag
    // #param: std::string&& p_arg, command line argument
    void CommandLineParser::handleArgument(const Token p_token, std::string&& p_arg)noexcept{ 
        if constexpr(state::TRACING){ // Function tracing
            debug::trace(std::source_location::current());
        }
        switch(p_token){
        case Token::ROOT_DIR:
            handleRootDirectory(std::forward<std::string>(p_arg));
            break;
        case Token::DOC_PACKET:
            handlePacket(std::forward<std::string>(p_arg));
            break;
        case Token::CONFIG_FILE: 
            handleConfigFile(std::forward<std::string>(p_arg));
            break;
        case Token::OUTPUT_DIRECTORY: 
            handleOutputDirectory(std::forward<std::string>(p_arg));
            break;
        case Token::SOURCE: 
            handleSource(std::forward<std::string>(p_arg));
            break;
        case Token::IGNORE: 
            handleIgnore(std::forward<std::string>(p_arg));
            break;
        }// switch
    }
    // #func: handleCommandLine(std::unordered_set<Option>&&), private noexcept method

    // #param: std::unordered_set<Option>&& p_commandLine, command line options
    void CommandLineParser::handleCommandLine(std::unordered_set<Option>&& p_commandLine)noexcept{
        if constexpr(state::TRACING){ // Function tracing
            debug::trace(std::source_location::current());
        }
        for(Option& option: p_commandLine){
            for(std::string& argument: option.arguments){
                handleArgument(*option.flag, std::move(argument)); 
            }
        }
    }

} // namespace worTech::autoDoc::genorator::commandLineProccessor

namespace std{

    // #func: operator(), public inline const noexcept method
    
    // #param: const docme::CommandLineOption& p_packet, given packet
    // #return: std::size_t, hash of packet
    std::size_t hash<docme::CommandLineOption>::operator()(const docme::CommandLineOption& p_packet)const noexcept{
        if constexpr(docme::state::TRACING){ // Function tracing
            docme::debug::trace(std::source_location::current());
        }
        return p_packet.hash();
    }

} // namespace std