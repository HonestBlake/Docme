// #FILE: cli.hpp, Package Header File
// #BRIEF: Package wide header file

#pragma once

#include "docme.hpp" // #INCLUDE: docme.hpp, Project wide header

namespace docme{ // #SCOPE: docme
    
    // #NAMESPACE: cli, Package Namespace
    namespace cli{

        // #NAMESPACE: commands, Namespace
        // #BRIEF: Namespace for CLI commands
        namespace commands{
            inline constexpr std::array<std::string, 1> INIT = {"init"};
            inline constexpr std::array<std::string, 1> BUILD = {"build"};
            inline constexpr std::array<std::string, 1> RENDER = {"render"};
            inline constexpr std::array<std::string, 1> GENERATE = {"generate"};
            inline constexpr std::array<std::string, 1> CHECK = {"check"};
        } // #END: commands

        // #NAMESPACE: flags, Namespace
        // #BRIEF: Namespace for CLI flags
        namespace flags{
            inline constexpr std::array<std::string, 2> HELP = {"--help", "-h"};
            inline constexpr std::array<std::string, 2> VERSION = {"--version", "-v"};
        } // #END: flags

        // #NAMESPACE: tags, Namespace
        // #BRIEF: Namespace for CLI option tags
        namespace tags{
            inline constexpr std::array<std::string, 2> CONFIG = {"--config", "-c"};
            inline constexpr std::array<std::string, 2> PROJECT_NAME = {"--project", "-p"};
            inline constexpr std::array<std::string, 2> SOURCE = {"--source", "-s"};
            inline constexpr std::array<std::string, 2> IGNORE = {"--ignore", "-i"};
            inline constexpr std::array<std::string, 2> OUTPUT = {"--output", "-o"};
            inline constexpr std::array<std::string, 2> LANGUAGE_HANDLER = {"--language", "-l"};
            inline constexpr std::array<std::string, 2> RENDERER = {"--render", "-r"};
        } // #END: tags
        

    } // #END: cli

} // #END: docme