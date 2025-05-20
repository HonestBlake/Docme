
#include "commandLineParser.hpp"
#include "docmeInfo.hpp"
#include "parser.hpp"
#include "generator.hpp"

int main(int argc, char* argv[]){
    docme::CommandLine& commandLine = docme::CommandLine::get().parse(argc, argv);
    if constexpr(docme::state::DEBUGGING){ // print debug info for command line
        commandLine.printInternalData();
    }
    docme::Generator::get().generate(commandLine.generatorInfo(), docme::Parser::get().parse(commandLine.parserInfo()));
    return EXIT_SUCCESS;
}