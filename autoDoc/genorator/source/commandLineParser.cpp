#include "commandLineParser.hpp"

namespace worTech::autoDoc::genorator::commandLineParser{

// public static methods

    // #func: get(), public static noexcept method

    // #return: CommandLineParser&, singleton instance of CommandLineParser
    CommandLineParser& CommandLineParser::get()noexcept{
        // Function tracing
        #ifdef WT_AUTODOC_DEBUG_TRACING
        debug::trace(std::source_location::current());
        #endif
        static CommandLineParser instance = CommandLineParser();
        return instance;
    }

// public methods

    // #func: parseCommandLine(), public noexcept method
    CommandLineParser& CommandLineParser::parseCommandLine(int p_argc, char** p_argv)noexcept{
        #ifdef WT_AUTODOC_DEBUG_TRACING
        debug::trace(std::source_location::current()); // Function tracing
        #endif
        // Move command line args to to string vector
        std::vector<std::string> args = {};
        for(int i = 1; i < p_argc; i++){    
            args.emplace_back(p_argv[i]);
        }
        // Check if any command line args were provided
        if(args.empty()){
            btr::Logger::get<AutoDocError>().log<btr::Level::ERROR>("No command line arguments provided");
            std::exit(EXIT_FAILURE); 
        }
        // Parse command line args
        for(std::size_t arg = 0; arg < args.size(); arg++){
            CommandLineTag tag;
            try{
                tag = map::COMMAND_LINE_TAGS.at(args[arg]);
            }catch(const std::out_of_range& e){
                if(arg == 0){ // First arg is not a command line tag
                    btr::Logger::get<AutoDocError>().log<btr::Level::ERROR>(std::format("Unreconized command line argument: {}", args[arg]));
                    std::exit(EXIT_FAILURE);
                }
                handleTag(tag, args[arg]);
            } // catch
        } // for
        return *this;
    }
// private factory methods
    CommandLineParser::CommandLineParser(): m_docPackets{DocPacket::AUTO_DOC}{};
// private methods

    // #func: isValidFileExtension(), private noexcept method
    bool CommandLineParser::isValidFileExtension(std::string&& p_fileExtension, DocPacket p_packet)noexcept{
        if(p_packet == DocPacket::CDOC){
            return CDOC_VALID_FILE_EXTENTIONS.find(p_fileExtension) != CDOC_VALID_FILE_EXTENTIONS.end();
        }else if(p_packet == DocPacket::AUTO_DOC){
            return AUTO_DOC_VALID_FILE_EXTENTIONS.find(p_fileExtension) != AUTO_DOC_VALID_FILE_EXTENTIONS.end();
        }
        return false;
    }
    // #func: handleDocPacket(), private noexcept method
    void CommandLineParser::handleDocPacket(const std::string& p_arg)noexcept{
        #ifdef WT_AUTODOC_DEBUG_TRACING
        debug::trace(std::source_location::current()); // Function tracing
        #endif
        DocPacket packet;
        try{
            packet = map::DOC_PACKETS.at(p_arg);
        }catch(const std::out_of_range& e){
            btr::Logger::get<AutoDocError>().log<btr::Level::ERROR>(std::format("Unreconized command doc packet: {}", p_arg));
            std::exit(EXIT_FAILURE);
        }
        m_docPackets.push_back(packet);
    }
    // #func: handleConfigFile(), private noexcept method
    void CommandLineParser::handleConfigFile(const std::string& p_arg)noexcept{
        #ifdef WT_AUTODOC_DEBUG_TRACING
        debug::trace(std::source_location::current()); // Function tracing
        #endif
        std::filesystem::path file =  std::filesystem::path(p_arg);
        if(file.extension().string() != VALID_CONFIG_FILE_EXTENSION){ // Check if config file is invalid type
            btr::Logger::get<AutoDocError>().log<btr::Level::ERROR>(std::format("Provided config file is not a valid {} file: {}", VALID_CONFIG_FILE_EXTENSION, p_arg));
            std::exit(EXIT_FAILURE);
        }else if(!std::filesystem::exists(file)){ // Check if file cannot be found
            btr::Logger::get<AutoDocError>().log<btr::Level::ERROR>(std::format("Could not locate config file: {}", p_arg));
            std::exit(EXIT_FAILURE);
        }
        m_configFile = p_arg;
    }
    // #func: handleOutputDirectory(), private noexcept method
    void CommandLineParser::handleOutputDirectory(const std::string& p_arg)noexcept{
        #ifdef WT_AUTODOC_DEBUG_TRACING
        debug::trace(std::source_location::current()); // Function tracing
        #endif
        std::filesystem::path directory =  std::filesystem::path(p_arg);
        if(!std::filesystem::exists(directory)){ // Check if file cannot be found
            btr::Logger::get<AutoDocError>().log<btr::Level::ERROR>(std::format("Could not locate output directory: {}", p_arg));
            std::exit(EXIT_FAILURE);
        }else if(!std::filesystem::is_directory(directory)){ // Check if output directory is not a directory
            btr::Logger::get<AutoDocError>().log<btr::Level::ERROR>(std::format("Provided output directory is not a valid directory: {}", p_arg));
            std::exit(EXIT_FAILURE);
        } 
        m_outputDirectory = p_arg;
    }
    // #func: handleSourceFile(), private noexcept method
    void CommandLineParser::handleSource(const std::string& p_arg)noexcept{
        #ifdef WT_AUTODOC_DEBUG_TRACING
        debug::trace(std::source_location::current()); // Function tracing
        #endif



        
        std::filesystem::path source =  std::filesystem::path(p_arg);

        if(!std::filesystem::exists(source)){ // Check if source cannot be found
            debug::warn(std::format("Could not locate source file: {}", p_arg));
            return;
        }
        if(std::filesystem::is_directory(source)){ // Source is a directory
            // Check each file in directory to see if the file type is valid
            for(const std::filesystem::directory_entry& entry : std::filesystem::recursive_directory_iterator(source)){
                if(isValidFileType(source)){
                    m_sourceFiles.push_back(source.string());
                }
            }
        }else{ // Source is a file
            if(isValidFileType(source)){
                m_sourceFiles.push_back(source.string());
            }else{
                debug::warn(std::format("Provided source file is not a valid file type from given doc packets: {}", p_arg));
                return;
            }
        }



        // Check each doc packet to see if the file extension is valid
        for(const DocPacket packet : m_docPackets){
            if(isValidFileExtension(entry.path().extension().string(), packet)){
                std::cout << "Added:" << entry.path().string() << std::endl;
                m_sourceFiles.push_back(entry.path().string());
                break;
            }
        } // for
 
        // Check each doc packet to see if the file extension is valid
        for(std::size_t packet = 0; packet < m_docPackets.size(); packet++){
            if(isValidFileExtension(file.extension().string(), m_docPackets[packet])) break;
            if(packet == m_docPackets.size() - 1){ // When at last packet
                btr::Logger::get<AutoDocError>().log<btr::Level::ERROR>(std::format("Provided source file is not a valid file type from given doc packets: {}", p_arg));
                std::exit(EXIT_FAILURE);
            }
        }

       
        
        m_sourceFiles.push_back(p_arg);



        
         
        



    }
    // #func: handleIgnoreFile(), private noexcept method
    void CommandLineParser::handleIgnore(const std::string& p_arg)noexcept{
        #ifdef WT_AUTODOC_DEBUG_TRACING
        debug::trace(std::source_location::current()); // Function tracing
        #endif








        std::filesystem::path file =  std::filesystem::path(p_arg);
        // Check each doc packet to see if the file extension is valid
        for(std::size_t packet = 0; packet < m_docPackets.size(); packet++){
            if(isValidFileExtension(file.extension().string(), m_docPackets[packet])) break;
            if(packet == m_docPackets.size() - 1){ // When at last packet
                btr::Logger::get<AutoDocError>().log<btr::Level::ERROR>(std::format("Provided source file is not a valid file type from given doc packets: {}", p_arg));
                std::exit(EXIT_FAILURE);
            }
        }
        if(!std::filesystem::exists(file)){ // Check if file cannot be found
            btr::Logger::get<AutoDocError>().log<btr::Level::ERROR>(std::format("Could not find ignore file: {}", p_arg));
            std::exit(EXIT_FAILURE);
        }
        m_ignoreFiles.push_back(p_arg);
    }
    // 
    void CommandLineParser::handleTag(const CommandLineTag p_tag, const std::string& p_arg)noexcept{
        #ifdef WT_AUTODOC_DEBUG_TRACING
        debug::trace(std::source_location::current()); // Function tracing
        #endif
        switch(p_tag){
            case CommandLineTag::DOC_PACKET: {
                handleDocPacket(p_arg);
                break;
            }case CommandLineTag::CONFIG_FILE: {
                handleConfigFile(p_arg);
                break;
            }case CommandLineTag::OUTPUT_DIRECTORY: {
                handleOutputDirectory(p_arg);
                break;
            }case CommandLineTag::SOURCE: {
                handleSource(p_arg);
                break;
            }case CommandLineTag::IGNORE: {
                handleIgnore(p_arg);
                break;
            }
        } // switch
    }

} // namespace worTech::autoDoc::genorator::commandLineProccessor


// TODO change api to take a dir or file and handle