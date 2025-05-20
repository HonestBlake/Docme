#include "processor.hpp"

#include "nodes.hpp"



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

struct DocLine{
    std::string tag;
    std::string body;
};

struct DocSection{
    std::string name;
    std::string type;
    std::vector<DocLine> lines;
};

struct DocFile{
    std::optional<DocSection> file;
    std::vector<DocSection> components;
};


void foo(){

    
// parsing step using gernerics with dll

    

    
    std::vector<DocFile> docFiles;

    for(auto& [fileSection, componentSections]: docFiles){
        FileNode* file = nullptr;
        // Create file node
        if(fileSection){ // Checking if fileSection is present
            auto& [fileName, fileType, fileLines] = *fileSection;
            file = dll::newFileNode(fileName, fileType);
            for(DocLine& line: fileLines){
                file->addLine(std::move(line));
            }
        }
        // Create component nodes
        for(auto& [componentName, componentType, componentLines]: componentSections){
            ComponentNode* const component = dll::newComponentNode(componentName, componentType);
            component->linkFile(file);
            for(DocLine& line: componentLines){
                component->addLine(std::move(line));
            }
        }
    }

    

}
}