#include "engine/header/docmeEngine.hpp" 
#include "engine/header/commandLine.hpp"


int main(const int p_argc, const char* p_argv[]){
    docme::EngineInfo info = docme::CommandLine(p_argc, p_argv).parse().info();
    docme::Engine(std::move(info)).run();


    // docme::Generator(info.generator, Parser(info.parser).parse().nodeStack()).generate();

    // docme::CommandLine commandLine = docme::CommandLine(argc, argv);
    // commandLine.parse(); 
    // docme::Parser parser = docme::Parser(commandLine.parserInfo());
    // parser.parse(); 
    // docme::Generator generator = docme::Generator(commandLine.generatorInfo(), parser.nodeStack());
    // generator.generate();
    return EXIT_SUCCESS;
}
