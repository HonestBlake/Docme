
#include "commandLineParser.hpp"
#include "docmeInfo.hpp"
#include "parser.hpp"
#include "generator.hpp"

int main(int argc, char* argv[]){
    docme::CommandLineParser::get(argc, argv).parse();
    const void* stack = docme::Parser::get(docme::CommandLine::get().parserInfo()).parse();


    // docme::Generator::get(commandLine.generatorInfo(), ).generate();

    docme::CommandLine& commandLine = docme::CommandLine::get().parse(argc, argv);
    
    docme::Generator::get().generate(commandLine.generatorInfo(), docme::Parser::get().parse(commandLine.parserInfo()));
    return EXIT_SUCCESS;
}
