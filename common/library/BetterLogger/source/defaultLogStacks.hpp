#pragma once

// #file: defaultLogStacks.hpp, source file
// #info: defines methods for built in log stacks
// #attach: defaultLogStacks.hpp, internal dependency

// decloration header
#include "header/defaultLogStacks.hpp"

namespace worTech::betterLogger::defaultLogStacks{

// #div: AutoFlush, singleton class

    // #func: AutoFlush, private constructor
    // #scope: defaultLogStacks, component namespace
    // #info: deault constuctor for AutoFlush class
    AutoFlush::AutoFlush(): LogStack(logger::AUTO_FLUSH_TERMINATE_FLUSH, logger::AUTO_FLUSH_AUTO_FLUSH){}

// #div: TerminateFlush, singleton class

    // #func: TerminateFlush, private constructor
    // #scope: defaultLogStacks, component namespace
    // #info: deault constuctor for TerminateFlush class
    TerminateFlush::TerminateFlush(): LogStack(logger::TERMINATE_FLUSH_TERMINATE_FLUSH, logger::TERMINATE_FLUSH_AUTO_FLUSH){}

} // namespace worTech::betterLogger::defaultLogStacks