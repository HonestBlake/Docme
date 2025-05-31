
#include "commandLine.hpp"
#include "parser.hpp"
#include "generator.hpp"

int main(int argc, char* argv[]){
    docme::CommandLine::get(argc, argv).parse();
    docme::Parser::get(docme::CommandLine::get().parserInfo()).parse();
    docme::Generator::get(docme::CommandLine::get().generatorInfo(), docme::Parser::get().nodeStack()).generate();
    return EXIT_SUCCESS;
}
