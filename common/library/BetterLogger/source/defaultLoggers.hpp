#pragma once

// #file: defaultLoggers.hpp, source file
// #info: holds class definitions for built in loggers
// #attach: header/defaultLoggers.hpp, internal dependency

// decloration header
#include "header/defaultLoggers.hpp"

namespace worTech::betterLogger::defaultLoggers{

// #div: Main, singleton class

    // #func: Main, public constructor
    // #scope: defaultLoggers, component namespace
    // #info: deault constuctor for Main class given a name
    Main::Main(): Logger(std::move(logger::MAIN_NAME)){}

// #div: Debug, singleton class
    
    // #func: Debug, public constructor
    // #scope: defaultLoggers, component namespace
    // #info: deault constuctor for Debug class given a name
    Debug::Debug(): Logger(std::move(logger::DEBUG_NAME)){}
    
} // namespace worTech::betterLogger::defaultLoggers