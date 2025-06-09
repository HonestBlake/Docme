#include "engine/header/nodes.hpp" // declaration header

namespace docme::engine::nodes{

// Node, method definitions

// public methods

    // #func: Node::name(), public const method
    // #return: std::string, Name of node
    std::string Node::name()const{
        if constexpr(state::TRACING){ // Function tracing
            debug::trace();
        }
        return m_name;
    }
    // #func: Node::type(), public const method
    // #return: std::string, Name of node
    std::string Node::type()const{
        if constexpr(state::TRACING){ // Function tracing
            debug::trace();
        }
        return m_type;
    }

// ------------------------------------------------------------------------------------------------------------------------------------------

// DirectoryNode, method definitions

// public factory methods

    // #func: DirectoryNode::DirectoryNode(const std::string&), public constructor
    // #param: const std::string& p_name, Name of node
    DirectoryNode::DirectoryNode(const std::string& p_name): Node(p_name, node::DIRECTORY_TYPE){
        if constexpr(state::TRACING){ // Function tracing
            debug::trace();
        }
    }

    // #func: DirectoryNode::DirectoryNode(std::string&&), public constructor
    // #param: std::string&& p_name, Name of node
    DirectoryNode::DirectoryNode(std::string&& p_name): Node(std::forward<std::string>(p_name), node::DIRECTORY_TYPE){
        if constexpr(state::TRACING){ // Function tracing
            debug::trace();
        }
    }
    
// ------------------------------------------------------------------------------------------------------------------------------------------

// DocumentedNode, method definitions
    
// ------------------------------------------------------------------------------------------------------------------------------------------

// FileNode, method definitions
    
// ------------------------------------------------------------------------------------------------------------------------------------------

// ComponentNode, method definitions

// public methods

    // #func: ComponentNode::linkFile(FileNode* const p_file), public method
    void ComponentNode::linkFile(FileNode* const p_file){
        if constexpr(state::TRACING){ // Function tracing
            debug::trace();
        }
        m_file = p_file;
    }

// --------------------------------------------------------------------------------------------------------------------------------------------
    
// GlobalNode, method definitions

// public static methods

    // #func: GlobalNode::get(), public static method
    // #return: GlobalNode*, pointer to the singleton instance of GlobalNode
    GlobalNode* GlobalNode::get(){
        if constexpr(state::TRACING){ // Function tracing
            debug::trace();
        }
        static GlobalNode instance = GlobalNode();
        return &instance;
    }
    
// private factory methods

    // #func: GlobalNode::GlobalNode(), private constructor
    GlobalNode::GlobalNode(): Node(node::GLOBAL_NAME, node::GLOBAL_TYPE){
        if constexpr(state::TRACING){ // Function tracing
            debug::trace();
        }
    }

} // namespace docme::nodes