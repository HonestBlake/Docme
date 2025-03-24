#include "commandLineParser.hpp"

int main(int argc, char** argv){
    // Function tracing
    

    adoc::Parser& parser = adoc::Parser::get().parseCommandLine(argc, argv);

    // std::vector<std::string> fileLocations = {"genorator/include/nodes.hpp"};
    // std::string outputLocation = "g";
    // adoc::Genorator::getInstance().setLocations(argc, argv).parseProgramFiles().generateDocumentation();
    return 0;
}