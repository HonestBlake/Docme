// #file: commandLineParser.cpp, source file

#include "commandLineParser.hpp" // declaration header

namespace worTech::docme::processor::commandLineParser{

// CommandLineParser singleton class, method definitions

// public static methods

    CommandLineParser& CommandLineParser::get(int p_argc, char* p_argv[]){
        if constexpr(state::TRACING){ // Function tracing
            debug::trace(std::source_location::current());
        }
        if(!s_isInitialized){ // Check if object has been initialized
            debug::error();
        }
        static CommandLineParser instance = CommandLineParser(p_argc, p_argv);
        return instance;
    }

// public methods

    // #func: parse(), public noexcept method

    // #param: p_argc, int, number of command line arguments
    // #param: p_argv, char**, command line arguments
    // #return: CommandLineParser&, reference to current instance
    CommandLineParser& CommandLineParser::parse()noexcept{
        if constexpr(state::TRACING){ // Function tracing
            debug::trace(std::source_location::current());
        }
        
        handleCommandLine(tokenizeCommandLine(args)); 
        if(m_parserInfo.sourceFiles.empty()){ // No source files provided
            debug::error(error::NO_SOURCE_FILES_PROVIDED);
        }
        removeIgnoreFiles(); 
        return *this;
    }
    // #func: parserInfo(), public noexcept method

    // #return: ParserInfo, parser info member
    ParserInfo CommandLineParser::parserInfo()const noexcept{
        if constexpr(state::TRACING){ // Function tracing
            debug::trace(std::source_location::current());
        }
        return std::move(m_parserInfo);
    }
    // #func: generatorInfo(), public noexcept method

    // #return: GeneratorInfo, generator info member
    GeneratorInfo CommandLineParser::generatorInfo()const noexcept{
        if constexpr(state::TRACING){ // Function tracing
            debug::trace(std::source_location::current());
        }
        return std::move(m_generatorInfo);
    }
    #ifdef WT_DOCME_DEBUGGING
    // #func: printInternalData(), public noexcept method
    void CommandLineParser::printInternalData()noexcept{
        if constexpr(state::TRACING){ // Function tracing
            debug::trace(std::source_location::current());
        }
        std::cout << "Root Directory: " << m_rootDirectory.string() << std::endl;
        std::cout << "Config File: " << m_configFile.string() << std::endl;
        std::cout << "Output Directory: " << m_generatorInfo.outputDirectory.string() << std::endl;
        std::cout << "Packets: ";
        for(const Packet packet: m_parserInfo.packets){
        std::cout << packet.name() << " ";
        }
        std::cout << std::endl;
        std::cout << "Source Files: ";
        for(const std::filesystem::path& file: m_parserInfo.sourceFiles){
            std::cout << file.string() << " ";
        }
        std::cout << std::endl;
        std::cout << "Ignore Files: ";
        for(const std::filesystem::path& file: m_ignoreFiles){
            std::cout << file.string() << " ";
        }
        std::cout << std::endl;
    }
    #endif

// private factory methods

    // #func: CommandLineParser(int, char*[]), constructor
    CommandLineParser::CommandLineParser(int p_argc, char* p_argv[]){
        if constexpr(state::TRACING){ // Function tracing
            debug::trace();
        }
        s_isInitialized = true; // Set initialized to true
        if(p_argc < 2){ // Check if any command line args were provided
            debug::error(error::NO_COMMAND_LINE_ARGUMENTS);
        }
        if(p_argv == nullptr){ // Check if command line args are null
            debug::error(error::NULL_COMMAND_LINE_ARGUMENTS);
        }
        m_args = std::vector<std::string>(p_argv, p_argv + p_argc); // Move command line args to string vector
        setDefaultValues();
    } // #end: CommandLineParser(int, char*[])

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

    // #func: tokenizeCommandLine(std::vector<std::string>&), private noexcept method

    // #param: std::vector<std::string>& p_args, command line args
    // #return: std::unordered_map<Token, std::vector<std::string>>, vector of tokenized command line options
    std::unordered_map<Token, std::vector<std::string>> CommandLineParser::tokenizeCommandLine(std::vector<std::string>& p_args)noexcept{
        if constexpr(state::TRACING){ // Function tracing
            debug::trace(std::source_location::current());
        }
        Token flag;
        std::unordered_map<Token, std::vector<std::string>> commandLine;
        for(size_t arg = 0; arg < p_args.size(); arg++){
            if(commandLine::SPECIAL_FLAGS.contains(p_args[arg])){ // Arg is a command line special flag
                if(p_args.size() < 2){ // Command line has other args
                    debug::error(error::ARGS_WITH_SPECIAL_FLAG_CALL, p_args[arg]);
                }
                handleSpecialFlag(commandLine::SPECIAL_FLAGS.at(p_args[arg])); 
            }else if(commandLine::FLAGS.contains(p_args[arg])){ // Arg is a command line flag
                flag = commandLine::FLAGS.at(p_args[arg]); // Set flag to command line flag 
            }else{ // Arg is an argument
                if(arg == 0){ // Argument has no flag
                    debug::error(error::UNRECOGNIZED_COMMAND_LINE_ARGUMENT, p_args[arg]);
                }
                commandLine[flag].emplace_back(std::move(p_args[arg])); // Add argument to command line
            }
        }
        return commandLine; 
    }
    // #func: setDefaultValues(), private noexcept method
    void CommandLineParser::setDefaultValues()noexcept{
        if constexpr(state::TRACING){ // Function tracing
            debug::trace(std::source_location::current());
        }
        m_rootDirectory = std::filesystem::current_path(); // Set default root directory to program call site
        m_generatorInfo.outputDirectory = m_rootDirectory; // Set default output directory to root directory
        m_parserInfo.packets.emplace(Packet::get(packet::DOCME)); // Add default docme packet to packets
    }
    // #func: removeIgnoreFiles(), private noexcept method
    void CommandLineParser::removeIgnoreFiles()noexcept{
        if constexpr(state::TRACING){ // Function tracing
            debug::trace(std::source_location::current());
        }
        for(const std::filesystem::path& ignore: m_ignoreFiles){ // Remove each ignore file from source files
            if(!std::filesystem::is_directory(ignore)){ // Ignore is a file
                m_parserInfo.sourceFiles.erase(ignore);
            }else{ // Ignore is a directory
                // For each file in ignore directory, remove from source files
                for(const std::filesystem::directory_entry& entry: std::filesystem::recursive_directory_iterator(ignore)){
                    m_parserInfo.sourceFiles.erase(entry.path());
                }
            }
        }
    }
    // #func: isValidFile(const std::filesystem::path&), private noexcept method

    // #param: const std::filesystem::path& p_file, file being checked
    // #return: bool, weather file extension is valid for packet
    bool CommandLineParser::isValidFileType(const std::filesystem::path& p_file)noexcept{
        if constexpr(state::TRACING){ // Function tracing
            debug::trace(std::source_location::current());
        }
        // Check file type against each file type in each packet 
        for(const Packet& packet: m_parserInfo.packets){
            for(const std::string& fileType: packet.fileTypes()){
                if(p_file.extension().string() == fileType) return true; // File type found in packets 
            }
        }
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
        m_rootDirectory = std::filesystem::current_path() / std::filesystem::path(std::forward<std::string>(p_directory));
    }
    // #func: handlePacket(const std::string&), private noexcept method

    // #param: const std::string& p_packet, given packet
    void CommandLineParser::handlePacket(const std::string& p_packet)noexcept{
        if constexpr(state::TRACING){ // Function tracing
            debug::trace(std::source_location::current());
        }
        m_parserInfo.packets.insert(Packet::get(p_packet)); // Get packet and add to packets
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

    // #param: std::string&& p_directory, given output directory
    void CommandLineParser::handleOutputDirectory(std::string&& p_directory)noexcept{
        if constexpr(state::TRACING){ // Function tracing
            debug::trace(std::source_location::current());
        }
        std::filesystem::path directory = m_rootDirectory / std::filesystem::path(p_directory);
        if(!std::filesystem::exists(directory)){ // Check if output directory cannot be found
            if(m_generatorInfo.outputDirectory.empty()){ // Check if output directory is default set
                debug::error(error::COULD_NOT_FIND_OUTPUT_DIRECTORY, p_directory);
            }else{
                debug::warn(error::COULD_NOT_FIND_OUTPUT_DIRECTORY, p_directory); 
                return;
            }
        }else if(!std::filesystem::is_directory(directory)){ // Check if output directory is valid
            if(m_generatorInfo.outputDirectory.empty()){ // Check if output directory is default set
                debug::error(error::INVALID_OUTPUT_DIRECTORY, p_directory);
            }else{
                debug::warn(error::INVALID_OUTPUT_DIRECTORY, p_directory); 
                return;
            }
        }
        m_generatorInfo.outputDirectory = std::forward<std::filesystem::path>(directory);
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
            for(const std::filesystem::directory_entry& entry: std::filesystem::recursive_directory_iterator(source)){
                if(isValidFileType(entry.path())){
                    m_parserInfo.sourceFiles.emplace(std::move(entry.path()));
                }
            }
        }else{ // Source is a file
            if(isValidFileType(source)){
                m_parserInfo.sourceFiles.emplace(std::move(source));
            }else{
                debug::warn(error::INVALID_SOURCE_FILE_TYPE, p_source);
                return;
            }
        }
    }
    // #func: handleIgnore(std::string&&), private noexcept method
    
    // #param: std::string&& p_ignore, given ignore
    void CommandLineParser::handleIgnore(std::string&& p_ignore)noexcept{
        if constexpr(state::TRACING){ // Function tracing
            debug::trace(std::source_location::current());
        }
        std::filesystem::path ignore =  m_rootDirectory / std::filesystem::path(p_ignore);
        if(!std::filesystem::exists(ignore)){ // Check if ignore cannot be found
            debug::warn(error::COULD_NOT_FIND_IGNORE, ignore.string());
            return;
        }
        if(std::filesystem::is_directory(ignore)){ // Ignore is a directory
            // Find each file in directory
            for(const std::filesystem::directory_entry& entry : std::filesystem::recursive_directory_iterator(ignore)){
                if(isValidFileType(entry.path())){ // Check if file type is valid
                    m_ignoreFiles.emplace(std::move(entry.path()));
                }
            }
        }else{ // Ignore is a file
            if(isValidFileType(ignore)){
                m_ignoreFiles.emplace(std::move(ignore));
            }
        }
    }
    // #func: handleCommand(const Token), private noexcept method

    // #param: const Token p_command, command line command
    void CommandLineParser::handleSpecialFlag(const Token p_specialFlag)noexcept{
        if constexpr(state::TRACING){ // Function tracing
            debug::trace(std::source_location::current());
        }
        switch(p_specialFlag){
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
        } // switch
    }
    // #func: handleCommandLine(std::unordered_set<Option>&&), private noexcept method

    // #param: std::unordered_set<Option>&& p_commandLine, command line options
    void CommandLineParser::handleCommandLine(std::unordered_map<Token, std::vector<std::string>>&& p_commandLine)noexcept{
        if constexpr(state::TRACING){ // Function tracing
            debug::trace(std::source_location::current());
        }
        // Handle each flag in given evaluation order
        for(Token flag: commandLine::EVALUATION_ORDER){ 
            if(!p_commandLine.contains(flag)) continue; // Skip if flag is not in command line
            // Handle each argument for given flag
            for(std::string& argument: p_commandLine.at(flag)){ 
                handleArgument(flag, std::move(argument));
            }
        }
    }

} // namespace worTech::docme::generator::commandLineParser