// #file: nodeManagers.hpp, Module header file

#pragma once // Include guard

#include "engine/engine.hpp" // Project header

#include "engine/header/nodes.hpp" // Nodes header

namespace docme::engine::nodeManagers{ // #scope: docme::nodeManagers

    // #class: FileManager, Class object
    class FileManager{
    public:
    // Public factory methods
        FileManager() = default; // #default: FileManager(), Default constructor
        FileManager(const FileManager&) = default; // #default: FileManager(const FileManager&), Default copy constructor
        FileManager(FileManager&&) = default; // #default: FileManager(FileManager&&), Default move constructor
        ~FileManager() = default; // #default: ~FileManager(), Default destructor
    // Public operators
        FileManager& operator=(const FileManager&) = default; // #default: operator=(const FileManager&), Default copy assignment operator
        FileManager& operator=(FileManager&&) = default; // #default: operator=(FileManager&&), Default move assignment operator
    private:
    // Private members
        std::set<FileNode> m_fileNodes; 
    }; // #end: FileManager

    // #class: ComponentManager, Class object
    class ComponentManager{
    public:
    // Public factory methods
        ComponentManager() = default; // #default: ComponentManager(), Default constructor
        ComponentManager(const ComponentManager&) = default; // #default: ComponentManager(const ComponentManager&), Default copy constructor
        ComponentManager(ComponentManager&&) = default; // #default: ComponentManager(ComponentManager&&), Default move constructor
        ~ComponentManager() = default; // #default: ~ComponentManager(), Default destructor
    // Public operators
        ComponentManager& operator=(const ComponentManager&) = default; // #default: operator=(const ComponentManager&), Default copy assignment operator
        ComponentManager& operator=(ComponentManager&&) = default; // #default: operator=(ComponentManager&&), Default move assignment operator
    // Public methods
        ComponentManager& add();
    private:
    // Private members
        std::map<std::string, std::map<std::string, std::set<ComponentNode>>> m_componentNodes; 
    }; // #end: ComponentManager

} // #end: docme::nodeManagers