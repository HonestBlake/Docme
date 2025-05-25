#include "processor.hpp"

#include "nodes.hpp"

#include "parser.hpp" 

#include "packets.hpp"



// struct Dependency{
//     std::string type;
//     std::vector<Node*> node;
// };

// struct Trait{

// };


/*

    #class: DocmeTestClass(Test), test class
    #note: test note
    #inherit: public DocmeTestClassParent, body of blah

    #func: testFunction<T_input>(T_input input), private const override method
    #note: test note
    #return: std::string, test return
    #param: T_input input, test input
    #template: typename T_input, test input type

*/
namespace worTech::docme{

namespace dll{
    std::function<FileNode*(std::string, std::string)> newFileNode;
    std::function<ComponentNode*(std::string, std::string)> newComponentNode;
}

std::vector<Packet> packets;

void foo(){

// parsing step using gernerics with dll

for(Packet& packet: packets){

    std::vector<DocumentationFile> documentationFiles;

    for(auto& [fileSection, componentSections]: documentationFiles){
        FileNode* file = nullptr;
        // Create file node
        if(fileSection){ // Checking if fileSection is present
            auto& [fileName, fileType, fileLines] = *fileSection;
            file = packet.newFileNode(fileName, fileType);
            for(DocumentationLine& line: fileLines){
                file->addAttribute(std::move(line));
            }
        }
        // Create component nodes
        for(auto& [componentName, componentType, componentLines]: componentSections){
            ComponentNode* const component = packet.newComponentNode(componentName, componentType);
            component->linkFile(file);
            for(DocumentationLine& line: componentLines){
                component->addAttribute(std::move(line));
            }
        }
    }

    
}
}
}