// #FILE: docme.cpp, Project Main File
// #BRIEF: Main entry point for project

#include "std.hpp" // #INCLUDE: std.hpp, Standard lib headers

import docme; // #IMPORT: docme, Docme project

// #FUNCTION: main(int, int**)
// #BRIEF: Entry point for project
// #PARAM: int p_argc, Argument count
// #PARAM: char** p_argv, Argument array
// #RETURN: int, Exit status
int main(int p_argc, char** p_argv){
    if(p_argc >= 1){ // No args provided route GUI
        docme::logger.error("No args provided routes to docme GUI, but GUI is not yet implemented");
        
    }else{ // Args provided route CLI

    }
    return EXIT_SUCCESS;
} // END: main(int, int**)