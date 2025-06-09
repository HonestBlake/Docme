// #file: commandLine.cpp, Module source file

#include "engine/header/commandLine.hpp" // #include: commandLine.hpp, Module header

namespace docme::engine::commandLine{ // #scope: docme::commandLine

// #scope: CommandLineFlagComparer

    // #func: operator()(const Flag&, const Flag&), Const operator
    bool CommandLineFlagComparer::operator()(const Flag& p_leftFlag, const Flag& p_rightFlag)const{
        if constexpr(state::TRACING){ // Function tracing
            debug::trace();
        }
        // Find left and right positions in evaluation order and compare them
        return std::find(cmdLine::EVALUATION_ORDER.begin(), cmdLine::EVALUATION_ORDER.end(), p_leftFlag) < std::find(cmdLine::EVALUATION_ORDER.begin(), cmdLine::EVALUATION_ORDER.end(), p_rightFlag);
    } // #end: operator()(const Flag&, const Flag&)


// #scope: CommandLineParser

// #div: Public factory methods

    // #func: CommandLineParser(const int, const char*[]), Constructor
    CommandLineParser::CommandLineParser(const int p_argc, const char* p_argv[])noexcept{
        if constexpr(state::TRACING){ // Function tracing
            debug::trace();
        }
        if(p_argc < 2){ // Check if any command line args were provided
            debug::error(error::NO_COMMAND_LINE_ARGUMENTS);
        }
        if(p_argv == nullptr){ // Check if command line args are null
            debug::error(error::NULL_COMMAND_LINE_ARGUMENTS);
        }
        m_args = std::vector<std::string>(p_argv + 1, p_argv + p_argc); // Move command line args to string vector
        setDefaultValues();
    } // #end: CommandLineParser(const int, const char*[])

// #div: Public methods

    // #func: parse()&, &-qualified method
    CommandLineParser& CommandLineParser::parse()&{
        if constexpr(state::TRACING){ // Function tracing
            debug::trace();
        }
        parseCommandLine();
        handleCommandLine(); 
        for(const Packet& packet: m_info.parser.packets){ 
            if(packet.hasNoFiles()){ // No source files provided
                debug::error(error::NO_SOURCE_FILES_PROVIDED);
            }
        }
        return *this; // Return reference to this object
    } // #end: parse()&

    // #func: parse(), Method
    CommandLineParser CommandLineParser::parse()&&{
        if constexpr(state::TRACING){ // Function tracing
            debug::trace();
        }
        parseCommandLine();
        handleCommandLine(); 
        for(const Packet& packet: m_info.parser.packets){ 
            if(packet.hasNoFiles()){ // No source files provided
                debug::error(error::NO_SOURCE_FILES_PROVIDED);
            }
        }
        return std::move(*this);
    } // #end: parse()

    // #func: info()const&, Const &-qualified method
    const EngineInfo& CommandLineParser::info()const&{
        if constexpr(state::TRACING){ // Function tracing
            debug::trace();
        }
        return m_info; // Return const reference to EngineInfo
    } // #end: info()const&

    // #func: info()&, &-qualified method
    EngineInfo& CommandLineParser::info()&{
        if constexpr(state::TRACING){ // Function tracing
            debug::trace();
        }
        return m_info; // Return reference to EngineInfo
    } // #end: info()&

    // #func: info()&&, &&-qualified method 
    EngineInfo CommandLineParser::info()&&{
        if constexpr(state::TRACING){ // Function tracing
            debug::trace();
        }
        return std::move(m_info);
    } // #end: info()&&

    #ifdef WT_DOCME_DEBUGGING
    // #func: printInternalData(), Method
    void CommandLineParser::printInternalData(){
        // if constexpr(state::TRACING){ // Function tracing
        //     debug::trace(std::source_location::current());
        // }
        // std::cout << "Root Directory: " << m_rootDirectory.string() << std::endl;
        // std::cout << "Config File: " << m_configFile.string() << std::endl;
        // std::cout << "Output Directory: " << m_generatorInfo.outputDirectory.string() << std::endl;
        // std::cout << "Packets: ";
        // for(const Packet& packet: m_parserInfo.packets){
        //     std::cout << packet.name() << " ";
        // }
        // std::cout << std::endl;
        // std::cout << "Source Files: ";
        // for(const std::filesystem::path& file: m_parserInfo.sourceFiles){
        //     std::cout << file.string() << " ";
        // }
        // std::cout << std::endl;
        // std::cout << "Ignore Files: ";
        // for(const std::filesystem::path& file: m_ignoreFiles){
        //     std::cout << file.string() << " ";
        // }
        // std::cout << std::endl;
    } // #end: printInternalData()
    #endif

// #div: Private static methods

    // #func: help(), Method
    void CommandLineParser::help(){
        if constexpr(state::TRACING){ // Function tracing
            debug::trace();
        }
        debug::warn("Command help is not implemented yet");
    } // #end: help()

    // #func: version(), Method
    void CommandLineParser::version(){
        if constexpr(state::TRACING){ // Function tracing
            debug::trace();
        }
        debug::warn("Version is not implemented yet");
    } // #end: version()

    // #func: configure(), Method
    void CommandLineParser::configure(){
        if constexpr(state::TRACING){ // Function tracing
            debug::trace();
        }
        debug::warn("Command configure is not implemented yet");
    } // #end: configure()

// #div: Private methods

    // #func: setDefaultValues(), Method
    void CommandLineParser::setDefaultValues(){
        if constexpr(state::TRACING){ // Function tracing
            debug::trace(std::source_location::current());
        }
        m_rootDirectory = std::filesystem::current_path(); // Set default root directory to program call site
        // m_generatorInfo.outputDirectory = m_rootDirectory; // Set default output directory to root directory
        // m_parserInfo.packets.push_back(Packet(packet::DOCME)); // Add default docme packet to packets
    } // #end: setDefaultValues()

    // #func: parseCommandLine(), Method
    void CommandLineParser::parseCommandLine(){
        if constexpr(state::TRACING){ // Function tracing
            debug::trace();
        }
        std::optional<Flag> flag;
        for(std::string& arg: m_args){ 
            parseArgument(arg, flag); // Parse each argument
        }
    } // #end: parseCommandLine()

    // #func: parseArgument(std::string&, std::optional<Flag>&), Method
    void CommandLineParser::parseArgument(std::string& p_arg, std::optional<Flag>& p_flag){
        if constexpr(state::TRACING){ // Function tracing
            debug::trace();
        }
        if(cmdLine::SPECIAL_FLAGS.contains(p_arg)){ // Arg is a command line special flag
            if(m_args.size() > 1){ // Command line has other args
                debug::error(error::ARGS_WITH_SPECIAL_FLAG, p_arg);
            }
            handleSpecialFlag(cmdLine::SPECIAL_FLAGS.at(p_arg)); 
        }else if(cmdLine::FLAGS.contains(p_arg)){ // Arg is a command line flag
            p_flag = cmdLine::FLAGS.at(p_arg); // Set flag
        }else{ // Arg is an argument
            if(!p_flag){ // Argument has no flag
                debug::error(error::ARGUMENT_HAS_NO_FLAG, p_arg);
            }
            m_commandLine[*p_flag].push_back(std::move(p_arg)); // Add argument to command line
        }
    } // #end: parseArgument(std::string&, std::optional<Flag>&)

    // #func: handleCommand(const Flag), Method
    void CommandLineParser::handleSpecialFlag(const Flag p_specialFlag){
        if constexpr(state::TRACING){ // Function tracing
            debug::trace();
        }
        switch(p_specialFlag){
        case Flag::HELP: 
            help();
            break;
        case Flag::VERSION: 
            version();
            break;
        case Flag::CONFIGURE: 
            configure();
            break;
        } // switch
    } // #end: handleCommand(const Flag)

    // #func: handleCommandLine(), Method
    void CommandLineParser::handleCommandLine(){
        if constexpr(state::TRACING){ // Function tracing
            debug::trace();
        }
        // Handle each flag in given evaluation order
        for(auto& [flag, args]: m_commandLine){
            for(std::string& arg: args){ // Handle each argument for given flag
                handleArgument(flag, std::move(arg));
            }
        }
    } // #end: handleCommandLine()

    // #func: handleArgument(const Tag, std::string&&), private noexcept Method
    void CommandLineParser::handleArgument(const Flag p_flag, std::string&& p_arg){ 
        if constexpr(state::TRACING){ // Function tracing
            debug::trace();
        }
        switch(p_flag){
        case Flag::ROOT_DIR:
            handleRootDirectory(std::move(p_arg));
            break;
        case Flag::DOC_PACKET:
            handlePacket(std::move(p_arg));
            break;
        case Flag::CONFIG_FILE: 
            handleConfigFile(std::move(p_arg));
            break;
        case Flag::OUTPUT_DIRECTORY: 
            handleOutputDirectory(std::move(p_arg));
            break;
        case Flag::SOURCE: 
            handleSource(std::move(p_arg));
            break;
        case Flag::IGNORE: 
            handleIgnore(std::move(p_arg));
            break;
        } // switch
    } // #end: handleArgument(const Tag, std::string&&)

    // #func: handleRootDirectory(std::string&&), Method
    void CommandLineParser::handleRootDirectory(std::string&& p_directory){
        if constexpr(state::TRACING){ // Function tracing
            debug::trace();
        }
        std::filesystem::path directory = std::filesystem::path(std::move(p_directory));
        if(!std::filesystem::exists(directory)){ // Check if directory cannot be found
            debug::error(error::COULD_NOT_FIND_ROOT_DIRECTORY, directory.string());
        }else if(!std::filesystem::is_directory(directory)){ // Check if directory is valid
            debug::error(error::INVALID_ROOT_DIRECTORY, directory.string());
        }
        m_rootDirectory = std::filesystem::current_path() / std::move(directory); 
    } // #end: handleRootDirectory(std::string&&)

    // #func: handlePacket(std::string&&), Method
    void CommandLineParser::handlePacket(std::string&& p_packetName){
        if constexpr(state::TRACING){ // Function tracing
            debug::trace();
        }
        for(const Packet& packet: m_info.parser.packets){ // Check if packet already exists
            if(packet.name() == p_packetName) return;
        }
        m_info.parser.packets.emplace_back(std::move(p_packetName)); // Emplace packet into packets
    } // #end: handlePacket(std::string&&)

    // #func: handleConfigFile(std::string&&), Method
    void CommandLineParser::handleConfigFile(std::string&& p_file){
        if constexpr(state::TRACING){ // Function tracing
            debug::trace();
        }
        std::filesystem::path file =  std::filesystem::path(std::move(p_file));
        if(!std::filesystem::exists(file)){ // Check if file cannot be found
            debug::error(error::COULD_NOT_FIND_CONFIG_FILE, file.string());
        }else if(file.extension().string() != cmdLine::CONFIG_FILE_TYPE){ // Check if config file is invalid type
            debug::error(error::INVALID_CONFIG_FILE_TYPE, cmdLine::CONFIG_FILE_TYPE, file.string());
        }
        parseConfigFile(file);
    } // #end: handleConfigFile(std::string&&)

    // #func: parseConfigFile(std::filesystem::path&&), Method
    void CommandLineParser::parseConfigFile(const std::filesystem::path& p_file){
        if constexpr(state::TRACING){ // Function tracing
            debug::trace();
        }
        // Parse config file
        auto configFile = Json::parse(p_file); 
        if(!configFile){ // Check if couldn't open config file
            debug::warn(error::FAILED_TO_PARSE_CONFIG_FILE, p_file.string());
            return;
        }
        // Get packets
        auto packets = configFile->getStringArray(key::PACKETS);
        if(!packets){ // Check if packets could not be found
            debug::warn(packets.error());
        }else{
            for(const std::string& packet: *packets){ // Add each packet to packets
                m_info.parser.packets.emplace_back(std::move(packet));
            }
        }
        // Get root directory 
        auto rootDirectory = configFile->getString(key::ROOT_DIRECTORY);
        if(!rootDirectory){ 
            debug::warn(rootDirectory.error());
        }else{
            m_commandLine[Flag::ROOT_DIR].push_back(std::move(*rootDirectory)); 
        }
        // Get output directory
        auto outputDirectory = configFile->getString(key::OUTPUT_DIRECTORY);
        if(!outputDirectory){ 
            debug::warn(outputDirectory.error());
        }else{
            m_commandLine[Flag::OUTPUT_DIRECTORY].push_back(std::move(*outputDirectory));
        }
        // Get sources
        auto sources = configFile->getStringArray(key::SOURCE);
        if(!sources){ 
            debug::warn(sources.error());
        }else{
            for(const std::string& source: *sources){ // Add each source to command line
                m_commandLine[Flag::SOURCE].push_back(std::move(source));
            }
        }
        // Get ignores
        auto ignores = configFile->getStringArray(key::IGNORE);
        if(!ignores){ 
            debug::warn(ignores.error());
        }else{
            for(const std::string& ignore: *ignores){ // Add each ignore to command line
                m_commandLine[Flag::IGNORE].push_back(std::move(ignore));
            }
        }
    } // #end: parseConfigFile(std::filesystem::path&&)

    // #func: handleOutputDirectory(std::string&&), Method
    void CommandLineParser::handleOutputDirectory(std::string&& p_directory){
        if constexpr(state::TRACING){ // Function tracing
            debug::trace();
        }
        std::filesystem::path directory = m_rootDirectory / std::filesystem::path(std::move(p_directory));
        if(!std::filesystem::exists(directory)){ // Check if output directory cannot be found
            debug::warn(error::COULD_NOT_FIND_OUTPUT_DIRECTORY, directory.string()); 
            return;
        }else if(!std::filesystem::is_directory(directory)){ // Check if output directory is not valid
            debug::warn(error::INVALID_OUTPUT_DIRECTORY, directory.string()); 
            return;
        }
        //m_generatorInfo.outputDirectory = std::move(directory);
    } // #end: handleOutputDirectory(std::string&&)

    // #func: handleSource(std::string&&), Method
    void CommandLineParser::handleSource(std::string&& p_source){
        if constexpr(state::TRACING){ // Function tracing
            debug::trace();
        }
        std::filesystem::path source =  m_rootDirectory / std::filesystem::path(std::move(p_source));
        if(!std::filesystem::exists(source)){ // Check if source cannot be found
            debug::warn(error::COULD_NOT_FIND_SOURCE, p_source);
            return;
        }
        if(std::filesystem::is_directory(source)){ // Source is a directory
            for(const std::filesystem::directory_entry& entry: std::filesystem::recursive_directory_iterator(source)){ // Get each file from directory
                for(Packet& packet: m_info.parser.packets){ // Add if valid type for each packet
                    packet.addFileIfValid(entry.path());
                }
            }
        }else{ // Source is a file
            for(Packet& packet: m_info.parser.packets){ // Add if valid type for each packet
                packet.addFileIfValid(source);
            }
        }
    } // #end: handleSource(std::string&&)

    // #func: handleIgnore(std::string&&), Method
    void CommandLineParser::handleIgnore(std::string&& p_ignore){
        if constexpr(state::TRACING){ // Function tracing
            debug::trace();
        }
        std::filesystem::path ignore =  m_rootDirectory / std::filesystem::path(std::move(p_ignore));
        if(!std::filesystem::exists(ignore)){ // Check if ignore cannot be found
            debug::warn(error::COULD_NOT_FIND_IGNORE, ignore.string());
            return;
        }
        if(std::filesystem::is_directory(ignore)){ // Ignore is a directory
            for(const std::filesystem::directory_entry& entry : std::filesystem::recursive_directory_iterator(ignore)){ // Get each file from directory
                for(Packet& packet: m_info.parser.packets){ // Check each packet and remove file if held
                    packet.removeIfContainsFile(entry.path()); 
                }
            }
        }else{ // Ignore is a file
            
        }
    } // #end: handleIgnore(std::string&&)

} // #end: docme::generator::commandLineParser