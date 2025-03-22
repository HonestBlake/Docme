#include "cdocs.hpp"
#include "helpers.hpp"

#include "commandLineParser.hpp"





int main(int argc, char** argv){
    // Function tracing
    #ifdef WT_AUTODOC_DEBUG_TRACING
    debug::trace(std::source_location::current());
    #endif

    adoc::CLParser& parser = adoc::CLParser::get().parseCommandLine(argc, argv);

    // std::vector<std::string> fileLocations = {"genorator/include/nodes.hpp"};
    // std::string outputLocation = "g";
    // adoc::Genorator::getInstance().setLocations(argc, argv).parseProgramFiles().generateDocumentation();
    return 0;
}