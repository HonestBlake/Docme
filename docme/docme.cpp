// #FILE: docme.cpp, Project Main File
// #BRIEF: Main entry point for project

#include "std.hpp" // #INCLUDE: std.hpp, Standard lib headers

import docme; // #IMPORT: docme, Docme project

// #FUNC: main(int, char**), Function
// #BRIEF: Entry point for project
// #PARAM: int p_argc, Argument count
// #PARAM: char** p_argv, Argument array
// #RETURN: int, Exit status
int main(int p_argc, char** p_argv){
    if(p_argc > 1){ // Args provided route CLI
        docme::cli::Application(p_argc, p_argv).run();
    }else{ // No args provided route GUI
        // ! GUI not yet implemented
        docme::Logger::get().error("No args provided routes to docme GUI, but GUI is not yet implemented");
    }
    docme::Logger::get().log("Exited Docme Successfully");
    return EXIT_SUCCESS;
} // END: main(int, char**)
