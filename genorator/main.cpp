#include "cdocs.hpp"
#include "helpers.hpp"

int main(int argc, char** argv){
    // another test
    #ifdef WT_AUTODOC_DEBUG_TRACING
        debug::trace(std::source_location::current());
    #endif
    std::vector<std::string> fileLocations = {"genorator/include/nodes.hpp"};
    std::string outputLocation = "g";
    adoc::Genorator::getInstance().setLocations(argc, argv).parseProgramFiles().generateDocumentation();
    return 0;
}