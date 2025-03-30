#include "commandLineParser.hpp"

// TODO esure order of cml
// TODO fix relatice calls to file and dir for json

namespace worTech::docme::genorator::commandLineParser{

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
    CommandLineParser& CommandLineParser::parse(int p_argc, char** p_argv)noexcept{
        if constexpr(state::TRACING){ // Function tracing
            debug::trace(std::source_location::current());
        }
        // Move command line args to to string vector
        std::vector<std::string> args = {};
        for(int i = 1; i < p_argc; i++){
            args.emplace_back(p_argv[i]);
        }
        // Check if any command line args were provided
        if(args.empty()){
            debug::error(error::NO_COMMAND_LINE_ARGUMENTS);
        }
        // Parse command line args
        for(std::size_t arg = 0; arg < args.size(); arg++){
            Token token;
            try{
                token = commandLine::TOKENS.at(args[arg]);
            }catch(const std::out_of_range& e){
                if(arg == 0){ // First arg is not a command line tag
                    debug::error(error::UNRECONIZED_COMMAND_LINE_ARGUMENT, args[arg]);
                }
                handleToken(token, std::move(args[arg]));
            } // catch
        } // for
        return *this;
    }
    #ifdef WT_AUTODOC_DEBUGGING
    // #func: printInternalData(), public noexcept method
    void CommandLineParser::printInternalData()noexcept{
        if constexpr(state::TRACING){ // Function tracing
            debug::trace(std::source_location::current());
        }
        std::cout << "Root Directory: " << m_rootDirectory << std::endl;
        std::cout << "Config File: " << m_configFile << std::endl;
        std::cout << "Output Directory: " << m_outputDirectory << std::endl;
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
        m_rootDirectory = std::filesystem::current_path().string(); 
        //m_packets.emplace(Packet::get(packet::DOCME));
    }

// private methods

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
        std::filesystem::path source =  std::filesystem::path(p_source);
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
        std::filesystem::path ignore =  std::filesystem::path(p_ingore);
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
    // #func: handleTag(const Tag, std::string&&), private noexcept method

    // #param: const Tag p_tag, command line tag
    // #param: std::string&& p_arg, command line argument
    void CommandLineParser::handleToken(const Token p_token, std::string&& p_arg)noexcept{ 
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

} // namespace worTech::autoDoc::genorator::commandLineProccessor


// TODO change api to take a dir or file and handle