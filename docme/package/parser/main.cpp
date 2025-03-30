#include "commandLineParser.hpp"

int main(int argc, char** argv){

    docme::CommandLine& commandLine = docme::CommandLine::get().parse(argc, argv);
    
    commandLine.printInternalData();

    // std::vector<std::string> fileLocations = {"genorator/include/nodes.hpp"};
    // std::string outputLocation = "g";
    // adoc::Genorator::getInstance().setLocations(argc, argv).parseProgramFiles().generateDocumentation();

    return EXIT_SUCCESS;
}