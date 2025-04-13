
#include "commandLineParser.hpp"
#include "docmeInfo.hpp"
#include "parser.hpp"
#include "generator.hpp"

int main(int argc, char* argv[]){
    docme::CommandLine& commandLine = docme::CommandLine::get().parse(argc, argv);
    #ifdef WT_DOCME_DEBUGGING
    commandLine.printInternalData();
    #endif
    docme::Generator::get().generate(commandLine.generatorInfo(), docme::Parser::get().parse(commandLine.parserInfo()));
    return EXIT_SUCCESS;
}     