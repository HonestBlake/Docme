// #FILE: cli.cpp, Main File
// #BRIEF: CLI package main file entry point

import docme.cli; // #IMPORT: docme, Project Module

import docme.engine; 

#include <iostream> 

// #FUNCTION: main(int, char**), Main function
// #BRIEF: Entry point for cli application
// #PARAM: argc, Argument count
// #PARAM: argv, Argument array
// #RETURN: int, Exit status
int main(int argc, char** argv){
    std::cout << docme::engine::ConfigFile::Error(docme::Error::DOCME_100, "test").message() << std::endl;
    std::cout << docme::engine::ConfigFile::Error(docme::Error::DOCME_101, "test").message() << std::endl;
    std::cout << docme::engine::ConfigFile::Error(docme::Error::DOCME_102, "test").message() << std::endl;
    std::cout << docme::engine::ConfigFile::Error(docme::Error::DOCME_103, "test").message() << std::endl;
    return EXIT_SUCCESS;
} // #END: main(int, char**)