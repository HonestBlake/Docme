#include "nodes.hpp" // declaration header

namespace worTech::docme::nodes{

// Node, method definitions

// ------------------------------------------------------------------------------------------------------------------------------------------

// DirectoryNode, method definitions

// public factory methods

    // #func: DirectoryNode(const std::string&), public constructor
    // #param: const std::string& p_name, Name of node
    DirectoryNode::DirectoryNode(const std::string& p_name): Node(p_name, node::DIRECTORY_TYPE){
        if constexpr(state::TRACING){ // Function tracing
            debug::trace();
        }
    }

    // #func: DirectoryNode(std::string&&), public constructor
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

    // #func: linkFile(FileNode* const p_file), public method
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

    // #func: GlobalNode(), private constructor
    GlobalNode::GlobalNode(): Node(node::GLOBAL_NAME, node::GLOBAL_TYPE){
        if constexpr(state::TRACING){ // Function tracing
            debug::trace();
        }
    }

} // namespace worTech::docme::nodes