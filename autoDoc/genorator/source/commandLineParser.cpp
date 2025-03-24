#include "commandLineParser.hpp"

namespace worTech::autoDoc::genorator::commandLineParser{

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

    // #func: parseCommandLine(), public noexcept method

    // #param: p_argc, int, number of command line arguments
    // #param: p_argv, char**, command line arguments
    // #return: CommandLineParser&, reference to current instance
    CommandLineParser& CommandLineParser::parseCommandLine(int p_argc, char** p_argv)noexcept{
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
            CommandLineTag tag;
            try{
                tag = map::COMMAND_LINE_TAGS.at(args[arg]);
            }catch(const std::out_of_range& e){
                if(arg == 0){ // First arg is not a command line tag
                    debug::error(error::UNRECONIZED_COMMAND_LINE_ARGUMENT, args[arg]);
                }
                handleTag(tag, std::move(args[arg]));
            } // catch
        } // for
        return *this;
    }

// private factory methods

    // #func: CommandLineParser(), private constructor
    CommandLineParser::CommandLineParser(): m_packets{DocPacket::AUTO_DOC}{};

// private methods

    // #func: isValidFile(const std::filesystem::path&), private noexcept method

    // #param: const std::filesystem::path& p_file, file being checked
    // #return: bool, weather file extension is valid for packet
    bool CommandLineParser::isValidFileType(const std::filesystem::path& p_file)noexcept{
        if constexpr(state::TRACING){ // Function tracing
            debug::trace(std::source_location::current());
        }
        // Check each packet to see if file extension is valid
        for(const Packet packet: m_packets){
            switch(packet){
                case Packet::CDOC: {
                    return extentions::CDOC.find(p_file.extension().string()) != extentions::CDOC.end();
                }case Packet::AUTO_DOC: {
                    return extentions::AUTO_DOC.find(p_file.extension().string()) != extentions::AUTO_DOC.end();
                }
            } // switch
        } // for
        return false;
    }
    // #func: handlePacket(const std::string&), private noexcept method

    // #param: const std::string& p_packet, given packet
    void CommandLineParser::handlePacket(const std::string& p_packet)noexcept{
        if constexpr(state::TRACING){ // Function tracing
            debug::trace(std::source_location::current());
        }
        DocPacket packet;
        try{
            packet = map::DOC_PACKETS.at(p_packet);
        }catch(const std::out_of_range& e){
            debug::warn(error::UNRECONIZED_DOC_PACKET, p_packet);
            return;
        }
        m_packets.insert(packet);
    }
    // #func: handleConfigFile(std::string&&), private noexcept method

    // #param: std::string&& p_arg, given config file
    void CommandLineParser::handleConfigFile(std::string&& p_file)noexcept{
        if constexpr(state::TRACING){ // Function tracing
            debug::trace(std::source_location::current());
        }
        std::filesystem::path file =  std::filesystem::path(p_file);
        if(file.extension().string() != VALID_CONFIG_FILE_EXTENSION){ // Check if config file is invalid type
            debug::error(error::INVALID_CONFIG_FILE_TYPE, VALID_CONFIG_FILE_EXTENSION, p_file);
        }else if(!std::filesystem::exists(file)){ // Check if file cannot be found
            debug::error(error::COULD_NOT_FIND_CONFIG_FILE, p_file);
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
        if(!std::filesystem::exists(directory)){ // Check if file cannot be found
            if(m_outputDirectory.empty()){ // Check if output directory is default set
                debug::error(error::COULD_NOT_FIND_OUTPUT_DIRECTORY, p_directory);
            }else{
                debug::warn(error::COULD_NOT_FIND_OUTPUT_DIRECTORY, p_directory);
                return;
            }
        }else if(!std::filesystem::is_directory(directory)){ // Check if output directory is not a directory
            if(m_outputDirectory.empty()){ // Check if output directory is default set
                debug::error(error::OUTPUT_DIRECTORY_IS_NOT_DIRECTORY, p_directory);
            }else{
                debug::warn(error::OUTPUT_DIRECTORY_IS_NOT_DIRECTORY, p_directory); 
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
    void CommandLineParser::handleTag(const Tag p_tag, std::string&& p_arg)noexcept{
        if constexpr(state::TRACING){ // Function tracing
            debug::trace(std::source_location::current());
        }
        switch(p_tag){
            case Tag::DOC_PACKET: {
                handlePacket(std::forward<std::string>(p_arg));
                break;
            }case Tag::CONFIG_FILE: {
                handleConfigFile(std::forward<std::string>(p_arg));
                break;
            }case Tag::OUTPUT_DIRECTORY: {
                handleOutputDirectory(std::forward<std::string>(p_arg));
                break;
            }case Tag::SOURCE: {
                handleSource(std::forward<std::string>(p_arg));
                break;
            }case Tag::IGNORE: {
                handleIgnore(std::forward<std::string>(p_arg));
                break;
            }
        } // switch
    }

} // namespace worTech::autoDoc::genorator::commandLineProccessor


// TODO change api to take a dir or file and handle