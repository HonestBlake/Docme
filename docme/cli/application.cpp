// #FILE: configFile.cpp, Component Source File
// #BRIEF: Source file for configFile component

module;

#include "cli.hpp" // #INCLUDE: cli.hpp, Package wide header

module docme.cli; // #IMPLEMENTS: docme.cli:application
import :application; 

namespace docme::cli{ // #SCOPE: docme::cli

// ------------------------------------------------------------------------------
//                               class Application
// ------------------------------------------------------------------------------
   
// #SCOPE: Application

// #DIV: Public

// ---- Public Special Methods ----

    // #METHOD: Application(int, char**), Constructor
    // #BRIEF: Initialize application with command line args
    Application::Application(int p_argc, char** p_argv): m_args(p_argv, p_argv + p_argc){
        if(Result<> result = setupCliParser(); !result){
            util::handleError(result.error());
        }
    } // #END: Application(int, char**)


// ---- Public Methods ----

    // #METHOD: run(), Instance Method
    // #BRIEF: Begin CLI application.
    void Application::run(){
        util::print("Starting Docme CLI");

        // Parse command line arguments
        if(simpleCli::Result<> result = m_parser.parse(m_args); !result){
            util::handleError(Error(Error::DOCME_INTERNAL, result.error().message()));
        }

        // Handle help and version flags
        if(m_help){
            help();
        }
        if(m_version){
            version();
        }
    } // #END: run()


// #DIV: Private

// ---- Private Methods ----

    // #METHOD: setupCliParser(), Instance Method
    // #BRIEF: Setup CLI parser with commands and options
    // #RETURN: Result<>, Optional error state
    Result<> Application::setupCliParser(){
        // Positionals
        if(simpleCli::Result<> result = m_parser.addPositional(m_positionals); !result) return Error(Error::DOCME_INTERNAL, result.error().message());
        //continuous
        // Options
        if(simpleCli::Result<> result = m_parser.addOption<std::optional<std_fs::path>>(tags::CONFIG, m_config, &util::optionalPathConverter); !result) return Error(Error::DOCME_INTERNAL, result.error().message());
        if(simpleCli::Result<> result = m_parser.addOption<std::optional<std::string>>(tags::PROJECT_NAME, m_options.projectName, &util::optionalStringConverter); !result) return Error(Error::DOCME_INTERNAL, result.error().message());
        if(simpleCli::Result<> result = m_parser.addContinuousOption<std_fs::path>(tags::SOURCE, m_options.sources, &util::pathConverter); !result) return Error(Error::DOCME_INTERNAL, result.error().message());
        if(simpleCli::Result<> result = m_parser.addContinuousOption<std_fs::path>(tags::IGNORE, m_options.ignores, &util::pathConverter); !result) return Error(Error::DOCME_INTERNAL, result.error().message());
        if(simpleCli::Result<> result = m_parser.addOption<std::optional<std_fs::path>>(tags::OUTPUT, m_options.output, &util::optionalPathConverter); !result) return Error(Error::DOCME_INTERNAL, result.error().message());
        if(simpleCli::Result<> result = m_parser.addContinuousOption<std::string>(tags::LANGUAGE_HANDLER, m_options.languageHandlers); !result) return Error(Error::DOCME_INTERNAL, result.error().message());
        if(simpleCli::Result<> result = m_parser.addContinuousOption<std::string>(tags::RENDERER, m_options.renderers); !result) return Error(Error::DOCME_INTERNAL, result.error().message());

        // Commands
        if(simpleCli::Result<> result = m_parser.addExclusiveCommand(commands::INIT, std::bind(&Application::init, this)); !result) return Error(Error::DOCME_INTERNAL, result.error().message());
        if(simpleCli::Result<> result = m_parser.addExclusiveCommand(commands::BUILD, std::bind(&Application::build, this)); !result) return Error(Error::DOCME_INTERNAL, result.error().message());
        if(simpleCli::Result<> result = m_parser.addExclusiveCommand(commands::RENDER, [](){logger.debug("render called");}); !result) return Error(Error::DOCME_INTERNAL, result.error().message());
        if(simpleCli::Result<> result = m_parser.addExclusiveCommand(commands::GENERATE, [](){logger.debug("generate called");}); !result) return Error(Error::DOCME_INTERNAL, result.error().message());
        if(simpleCli::Result<> result = m_parser.addExclusiveCommand(commands::CHECK, [](){logger.debug("check called");}); !result) return Error(Error::DOCME_INTERNAL, result.error().message());

        // Flags
        if(simpleCli::Result<> result = m_parser.addExclusiveFlag(flags::HELP, m_help); !result) return Error(Error::DOCME_INTERNAL, result.error().message());
        if(simpleCli::Result<> result = m_parser.addExclusiveFlag(flags::VERSION, m_version); !result) return Error(Error::DOCME_INTERNAL, result.error().message());

        return {};
    } // #END: setupCliParser()

    // #METHOD: help(), Const Instance Method
    // #BRIEF: Print help message to console
    void Application::help()const{
        output.log(
            "Docme v{} - automatic software documentation\n\n"
            "Usage:\n"
            "  docme <command> [options]\n"
            "  docme --help\n"
            "  docme --version\n\n"
            "Commands:\n"
            "  init       Create a template Docme configuration file\n"
            "  build      Build documentation using the resolved configuration\n"
            "  generate   Generate documentation from configured source files\n"
            "  render     Render generated documentation\n"
            "  check      Check the project documentation configuration\n\n"
            "Options:\n"
            "  -c, --config <path>       Use the specified configuration file\n"
            "  -p, --project <name>      Override the project name\n"
            "  -s, --source <path...>    Override source files and directories\n"
            "  -i, --ignore <path...>    Override ignored files and directories\n"
            "  -o, --output <path>       Override the documentation output directory\n"
            "  -l, --language <name...>  Override language handlers\n"
            "  -r, --render <name...>    Override renderers\n\n"
            "Flags:\n"
            "  -h, --help                 Show this help message\n"
            "  -v, --version              Show version and build information\n",
            VERSION
        );
    } // #END: help()

    // #METHOD: version(), Const Instance Method
    // #BRIEF: Print version message to console
    void Application::version()const{
        output.log(
            "Docme version v{}\n"
            "{} built with {} C++{}\n\n"
            "Docme is an open source documentation generator\n"
            "Licensed under the MIT License\n"
            "Copyright (c) 2026 Blake Worthington\n",
            VERSION, BUILD_MODE, COMPILER, CXX_STANDARD
        );
    } // #END: version()

    // #METHOD: init(), Instance Method
    // #BRIEF: Call and handles app init command.
    void Application::init(){
        Timer timer = Timer::start("Init"); // Start init timer

        // Get config path
        std::optional<std_fs::path> config;
        if(Result<std::optional<std_fs::path>> result = getConfigOrPositional()){
            config = result.takeValue();
        }else{ // Error getting config
            util::handleError(result.error());
        }

       util::printRunningCommand("Init", "with config path", config);

        Result<> result = app::Command::init(config);
        if(result.hasWarnings()){
            util::handleWarnings(result.warnings());
        }
        if(!result){
            util::handleError(result.error());
        }

        util::printTimer("{} ran for {}", timer.stop()); // Stop and print init timer
    } // #END: init()

    // #METHOD: build(), Instance Method
    // #BRIEF: Call and handles app build command.
    void Application::build(){
        if constexpr(DEBUGGING){ // Debug log config options
            config::util::printOptions("Loaded Config Options From CLI", m_options);
        }

        Timer timer = Timer::start("Build"); // Start build timer

        // Get config path
        std::optional<std_fs::path> config;
        if(Result<std::optional<std_fs::path>> result = getConfigOrPositional()){
            if(result.hasWarnings()){
                util::handleWarnings(result.warnings());
            }
            config = result.takeValue();
        }else{ // Error getting config
            util::handleError(result.error());
        }

        util::printRunningCommand("Build", "from config path", config);

        Result<> result = app::Command::build(config, config::Options(m_options));
        if(result.hasWarnings()){
            util::handleWarnings(result.warnings());
        }
        if(!result){
            util::handleError(result.error());
        }

        util::printTimer("{} ran for {}", timer.stop()); // Stop and print build timer
    } // #END: build()

    // #METHOD: getConfigOrPositional(), Const Instance Method
    // #BRIEF: Get config file path from config option or positional argument.
    // #RETURN: Result<std::optional<std_fs::path>>, Optional config file path result type
    Result<std::optional<std_fs::path>> Application::getConfigOrPositional()const{
        if(m_config){ // Config option provided
            if(!m_positionals.empty()) { // Positional arguments provided but aren't being used
                Warning::propagate(Warning(Warning::DOCME_W500)); 
            }
            return m_config;
        }else{ 
            if(m_positionals.size() > 1){ // Too many positional arguments provided
                Warning::propagate(Warning(Warning::DOCME_W501));
            }
            if(!m_positionals.empty()){
                std_fs::path config = m_positionals[0];
                core::util::normalizePath(config, std_fs::current_path());
                return {config};
            }
        }
        return {std::nullopt}; // No config provided
    } // #END: getConfigOrPositional()

// #END: Application

} // #END: docme::cli
