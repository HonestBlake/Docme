// #file: nodes.hpp, header file

#pragma once

#include "docme.hpp" // project header
#include "restrictedTypes.hpp" // used for StringType concept

#include "parser.hpp" // TODO move documentation obj out

namespace worTech::docme{
    class DocLine;
}

namespace worTech::docme::nodes{

    // #namespace: nodes::nodeDefaultValues, inline variable namespace
    namespace nodeDefaultValues{
        constexpr std::string GLOBAL_NAME = "Global";
        constexpr std::string GLOBAL_TYPE = "Scope";
        constexpr std::string DIRECTORY_TYPE = "Directory";
    }

    // #class: nodes::Node, abstract class
    class Node{
    public:
    // public factory methods
        Node() = default; // #default: Node(), default constructor
        template<StringType T_name, StringType T_type> Node(T_name&& p_name, T_type&& p_type);
        Node(const Node&) = default; // #default: Node(const Node&), default copy constructor
        Node(Node&&) = default; // #default: Node(Node&&), default move constructor
        virtual ~Node() = default; // #default: virtual ~Node(), default destructor
    // public operators
        Node& operator=(const Node&) = default; // #default: operator=(const Node&), default copy assignment operator
        Node& operator=(Node&&) = default; // #default: operator=(Node&&), default move assignment operator
    //public methods
        std::string name()const;
        std::string type()const;
    protected:
    // protected members
        std::string m_name;
        std::string m_type; // primary type e.g. class, function, header file
    };

    // #class: nodes::DirectoryNode, final object class
    class DirectoryNode final: public Node{
    public:
    // public factory methods
        DirectoryNode() = default; // #default: DirectoryNode(), default constructor
        DirectoryNode(const std::string& p_name);
        DirectoryNode(std::string&& p_name);
        DirectoryNode(const DirectoryNode&) = default; // #default: DirectoryNode(const DirectoryNode&), default copy constructor
        DirectoryNode(DirectoryNode&&) = default; // #default: DirectoryNode(DirectoryNode&&), default move constructor
        ~DirectoryNode() = default; // #default: ~DirectoryNode(), default destructor
    // public operators
        DirectoryNode& operator=(const DirectoryNode&) = default; // #default: operator=(const DirectoryNode&), default copy assignment operator
        DirectoryNode& operator=(DirectoryNode&&) = default; // #default: operator=(DirectoryNode&&), default move assignment operator
    };

    // #class: nodes::DocumentedNode, abstract class
    class DocumentedNode: public Node{
    public:
    // public factory methods
        DocumentedNode() = default; // #default: DocumentedNode(), default constructor
        DocumentedNode(const DocumentedNode&) = default; // #default: DocumentedNode(const DocumentedNode&), default copy constructor
        DocumentedNode(DocumentedNode&&) = default; // #default: DocumentedNode(DocumentedNode&&), default move constructor
        virtual ~DocumentedNode() = default; // #default: virtual ~DocumentedNode(), default destructor
    // public operators
        DocumentedNode& operator=(const DocumentedNode&) = default; // #default: operator=(const DocumentedNode&), default copy assignment operator
        DocumentedNode& operator=(DocumentedNode&&) = default; // #default: operator=(DocumentedNode&&), default move assignment operator
    // public methods
        virtual void addAttribute(DocumentationLine&& p_line) = WT_PURE_VIRTUAL; // #abstract: addAttribute(DocLine&&), pure virtual method
    };

    // #class: nodes::FileNode, abstract class
    class FileNode: public DocumentedNode{
    public:
    // public factory methods
        FileNode() = default; // #default: FileNode(), default constructor
        FileNode(const FileNode&) = default; // #default: FileNode(const FileNode&), default copy constructor
        FileNode(FileNode&&) = default; // #default: FileNode(FileNode&&), default move constructor
        virtual ~FileNode() = default; // #default: virtual ~FileNode(), default destructor
    // public operators
        FileNode& operator=(const FileNode&) = default; // #default: operator=(const FileNode&), default copy assignment operator
        FileNode& operator=(FileNode&&) = default; // #default: operator=(FileNode&&), default move assignment operator
    };

    // #class: nodes::ComponentNode, abstract class
    class ComponentNode: public DocumentedNode{
    public:
    // public factory methods
        ComponentNode() = default; // #default: ComponentNode(), default constructor
        ComponentNode(const ComponentNode&) = default; // #default: ComponentNode(const ComponentNode&), default copy constructor
        ComponentNode(ComponentNode&&) = default; // #default: ComponentNode(ComponentNode&&), default move constructor
        virtual ~ComponentNode() = default; // #default: virtual ~ComponentNode(), default destructor
    // public operators
        ComponentNode& operator=(const ComponentNode&) = default; // #default: operator=(const ComponentNode&), default copy assignment operator
        ComponentNode& operator=(ComponentNode&&) = default; // #default: operator=(ComponentNode&&), default move assignment operator
    // public methods
        void linkFile(FileNode* const p_file);
    protected:
    // protected members
        FileNode* m_file;
    };
    
    // #class: nodes::GlobalNode, final singleton class
    class GlobalNode final: public Node{
    public:
    // public factory methods
        ~GlobalNode() = default; // #default: ~GlobalNode(), default destructor
        GlobalNode(const GlobalNode&) = delete; // #delete: GlobalNode(const GlobalNode&), deleted copy constructor
        GlobalNode(GlobalNode&&) = delete; // #delete: GlobalNode(GlobalNode&&), deleted move constructor
    // public operators
        GlobalNode& operator=(const GlobalNode&) = delete; // #delete: operator=(const GlobalNode&), deleted copy assignment operator
        GlobalNode& operator=(GlobalNode&&) = delete; // #delete: operator=(GlobalNode&&), deleted move assignment operator
    // public static methods
        static GlobalNode* get();
    private:
    // private factory methods
        GlobalNode();
    };

};

#include "nodes.tpp" // template implementations