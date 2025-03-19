#include "nodes.hpp"

namespace worTech::cdocs::genorator::nodes{

// FileNode, method definitions

// public static methods

    // #func:
    FileNode* FileNode::build(const std::string& p_name, const type::File p_fileType)noexcept{
        FileNode* build = new FileNode();
        build->setName(p_name).setFileType(p_fileType);
        return build;
    }
    // #func:
    FileNode* FileNode::build(std::string&& p_name, const type::File p_fileType)noexcept{
        FileNode* build = new FileNode();
        build->setName(std::forward<std::string>(p_name)).setFileType(p_fileType);
        return build;
    }
    // #func:
    template <StringType T_name,OptionStringType T_brief, OptionStringType T_note, OptionStringType T_detail> 
    FileNode* FileNode::build(T_name&& p_name, const type::File p_fileType, T_brief&& p_brief, T_note&& p_note, T_detail&& p_detail)noexcept{
        FileNode* build = new FileNode();
        build->setName(std::forward<T_name>(p_name)).setFileType(p_fileType).complete(std::forward<T_brief>(p_brief), 
            std::forward<T_note>(p_note), std::forward<T_detail>(p_detail));
        return build;
    }

// public methods

    // #func:
    template<OptionStringType T_brief, OptionStringType T_note, OptionStringType T_detail> FileNode& FileNode::complete(T_brief&& p_brief, 
    T_note&& p_note, T_detail&& p_detail)noexcept{
        this->setBrief(std::forward<T_brief>(p_brief)).setNote(std::forward<T_note>(p_note)).setDetail(std::forward<T_detail>(p_detail))
            .setIsComplete(true);
        return *this;
    }
    // #func:
    inline const std::string& FileNode::name()const noexcept{
        return m_name;
    }
    // #func:
    inline type::File FileNode::fileType()const noexcept{
        return m_fileType;
    }
    // #func:
    inline const std::optional<std::string>& FileNode::brief()const noexcept{
        return m_brief;
    }
    // #func:
    inline const std::optional<std::string>& FileNode::note()const noexcept{
        return m_note;
    }
    // #func:
    inline const std::optional<std::string>& FileNode::detail()const noexcept{
        return m_detail;
    }
    // #func:
    inline const std::vector<FileNode*>& FileNode::dependencies()const noexcept{
        return m_depenendencies;
    }
    // #func:
    inline bool FileNode::isComplete()const noexcept{
        return m_isComplete;
    }

// private methods

    // #func:
    FileNode& FileNode::setName(const std::string& p_name)noexcept{
        m_name = p_name;
        return *this;
    }
    // #func:
    FileNode& FileNode::setName(std::string&& p_name)noexcept{
        m_name = std::forward<std::string>(p_name);
        return *this;
    }
    // #func:
    FileNode& FileNode::setFileType(const type::File p_fileType)noexcept{
        m_fileType = p_fileType;
        return *this;
    }
    // #func:
    FileNode& FileNode::setBrief(const std::optional<std::string>& p_brief)noexcept{
        m_brief = p_brief;
        return *this;
    }
    // #func:
    FileNode& FileNode::setBrief(std::optional<std::string>&& p_brief)noexcept{
        m_brief = std::forward<std::optional<std::string>>(p_brief);
        return *this;
    }
    // #func:
    FileNode& FileNode::setNote(const std::optional<std::string>& p_note)noexcept{
        m_note = p_note;
        return *this;
    }
    // #func:
    FileNode& FileNode::setNote(std::optional<std::string>&& p_note)noexcept{
        m_note = std::forward<std::optional<std::string>>(p_note);
        return *this;
    }
    // #func:
    FileNode& FileNode::setDetail(const std::optional<std::string>& p_detail)noexcept{
        m_detail = p_detail;
        return *this;
    }
    // #func:
    FileNode& FileNode::setDetail(std::optional<std::string>&& p_detail)noexcept{
        m_detail = std::forward<std::optional<std::string>>(p_detail);
        return *this;
    }
    // #func:
    FileNode& FileNode::addDependency(FileNode* const p_dependency)noexcept{
        m_depenendencies.push_back(p_dependency);
        return *this;
    }
    // #func:
    FileNode& FileNode::setIsComplete(const bool p_isComplete)noexcept{
        m_isComplete = p_isComplete;
        return *this;
    }

// ----------------------------------------------------------------------------------------------------------------------------------------

// GlobalSpace, method definitions

// public static methods

    // #func: getInstance(), public static noecxept method
    // #return: GlobalSpace&, reference to GlobalSpace instance
    GlobalSpace& GlobalSpace::getInstance()noexcept{
        static GlobalSpace instance;
        return instance;
    }

// public methods

    // #func: type(), public noecxept method
    // #return: type::Node, type of the node
    inline type::Node GlobalSpace::type()const noexcept{
        return type::Node::GLOBAL_SPACE;
    }

// ----------------------------------------------------------------------------------------------------------------------------------------

// Node, method definitions

// public methods

    // #func: isComplete(), public const noexcept method
    // #return: bool, member m_isComplete
    template<DerivedType T_derived> inline bool Node<T_derived>::isComplete()const noexcept{
        return m_isComplete;
    }
    // #func: file(), public const noexcept method
    // #return: FileNode*, member m_file
    template<DerivedType T_derived> inline FileNode* Node<T_derived>::file()const noexcept{
        return m_file;
    }
    // #func: name(), public const noexcept method
    // #return: const std::string&, member m_name
    template<DerivedType T_derived> inline const std::string& Node<T_derived>::name()const noexcept{
        return m_name;
    }
    // #func: alias(), public const noexcept method
    // #return: const std::optional<std::string>&, member m_alias
    template<DerivedType T_derived> inline const std::optional<std::string>& Node<T_derived>::alias()const noexcept{
        return m_alias;
    }
    // #func: brief(), public const noexcept method
    // #return: const std::optional<std::string>&, member m_brief
    template<DerivedType T_derived> inline const std::optional<std::string>& Node<T_derived>::brief()const noexcept{
        return m_brief;
    }
    // #func: note(), public const noexcept method
    // #return: const std::optional<std::string>&, member m_note
    template<DerivedType T_derived> inline const std::optional<std::string>& Node<T_derived>::note()const noexcept{
        return m_note; 
    }
    // #func: detail(), public const noexcept method
    // #return: const std::optional<std::string>&, member m_detail
    template<DerivedType T_derived> inline const std::optional<std::string>& Node<T_derived>::detail()const noexcept{
        return m_detail;
    }
    // #func: memberOf(), public const noexcept method
    // #return: AnyNode*, member m_memberOf
    template<DerivedType T_derived> inline AnyNode* Node<T_derived>::memberOf()const noexcept{
        return m_memberOf;
    }
    // #func: usedNamespaces(), public const noexcept method
    // #return: const std::vector<NamespaceNode*>&, member m_usedNamespaces
    template<DerivedType T_derived> inline const std::vector<NamespaceNode*>& Node<T_derived>::usedNamespaces()const noexcept{
        return m_usedNamespaces;
    }
    // #func: usedClasses(), public const noexcept method
    // #return: const std::vector<ClassNode*>&, member m_usedClasses
    template<DerivedType T_derived> inline const std::vector<ClassNode*>& Node<T_derived>::usedClasses()const noexcept{
        return m_usedClasses;
    }
    // #func: usedFunctions(), public const noexcept method
    // #return: const std::vector<FunctionNode*>&, member m_usedFunctions
    template<DerivedType T_derived> inline const std::vector<FunctionNode*>& Node<T_derived>::usedFunctions()const noexcept{
        return m_usedFunctions;
    }
    // #func: usedEnums(), public const noexcept method
    // #return: const std::vector<EnumNode*>&, member m_usedEnums
    template<DerivedType T_derived> inline const std::vector<EnumNode*>& Node<T_derived>::usedEnums()const noexcept{
        return m_usedEnums;
    }

// protected methods

    // #func: setIsComplete(bool), protected noexcept method
    // #param: const bool p_isComplete, value to set m_isComplete
    // #return: T_derived&, reference to current instance
    template<DerivedType T_derived> T_derived& Node<T_derived>::setIsComplete(const bool p_isComplete)noexcept{
        m_isComplete = p_isComplete;
        return *dynamic_cast<T_derived*>(this);
    }
    // #func: setFile(FileNode*), protected noexcept method
    // #param: FileNode* const p_file, value to set m_file
    // #return: T_derived&, reference to current instance
    template<DerivedType T_derived> T_derived& Node<T_derived>::setFile(FileNode* const p_file)noexcept{
        m_file = p_file;
        return *dynamic_cast<T_derived*>(this);
    }
    // #func: setName(std::string), protected noexcept method
    // #param: const std::string& p_name, value to set m_name
    // #return: T_derived&, reference to current instance
    template<DerivedType T_derived> T_derived& Node<T_derived>::setName(const std::string& p_name)noexcept{
        m_name = p_name;
        return *dynamic_cast<T_derived*>(this); 
    }
    // #
    template<DerivedType T_derived> T_derived& Node<T_derived>::setName(std::string&& p_name)noexcept{
        m_name = std::forward<std::string>(p_name);
        return *dynamic_cast<T_derived*>(this); 
    }
    // #
    template<DerivedType T_derived> T_derived& Node<T_derived>::setAlias(const std::optional<std::string>& p_alias)noexcept{
        m_alias = p_alias;
        return *dynamic_cast<T_derived*>(this); 
    }
    // #
    template<DerivedType T_derived> T_derived& Node<T_derived>::setAlias(std::optional<std::string>&& p_alias)noexcept{
        m_alias = std::forward<std::optional<std::string>>(p_alias);
        return *dynamic_cast<T_derived*>(this); 
    }
    // #
    template<DerivedType T_derived> T_derived& Node<T_derived>::setBrief(const std::optional<std::string>& p_brief)noexcept{
        m_brief = p_brief;
        return *dynamic_cast<T_derived*>(this); 
    }
    // #
    template<DerivedType T_derived> T_derived& Node<T_derived>::setBrief(std::optional<std::string>&& p_brief)noexcept{
        m_brief = std::forward<std::optional<std::string>>(p_brief);
        return *dynamic_cast<T_derived*>(this); 
    }
    // #
    template<DerivedType T_derived> T_derived& Node<T_derived>::setNote(const std::optional<std::string>& p_note)noexcept{
        m_note = p_note;
        return *dynamic_cast<T_derived*>(this); 
    }
    // #
    template<DerivedType T_derived> T_derived& Node<T_derived>::setNote(std::optional<std::string>&& p_note)noexcept{
        m_note = std::forward<std::optional<std::string>>(p_note);
        return *dynamic_cast<T_derived*>(this); 
    }
    // #
    template<DerivedType T_derived> T_derived& Node<T_derived>::setDetail(const std::optional<std::string>& p_detail)noexcept{
        m_detail = p_detail;
        return *dynamic_cast<T_derived*>(this); 
    }
    // #
    template<DerivedType T_derived> T_derived& Node<T_derived>::setDetail(std::optional<std::string>&& p_detail)noexcept{
        m_detail = std::forward<std::optional<std::string>>(p_detail);
        return *dynamic_cast<T_derived*>(this); 
    }
    // #
    template<DerivedType T_derived> T_derived& Node<T_derived>::setMemberOf(AnyNode* const p_memberOf)noexcept{
        m_memberOf = p_memberOf;
        return *dynamic_cast<T_derived*>(this);
    }
    // #
    template<DerivedType T_derived> T_derived& Node<T_derived>::addUsedNamespace(NamespaceNode* const p_usedNamespace)noexcept{
        m_usedNamespaces.push_back(p_usedNamespace);
        return *dynamic_cast<T_derived*>(this);
    }
    // #
    template<DerivedType T_derived> T_derived& Node<T_derived>::addUsedClass(ClassNode* const p_usedClass)noexcept{
        m_usedClasses.push_back(p_usedClass);
        return *dynamic_cast<T_derived*>(this);
    }
    // #
    template<DerivedType T_derived> T_derived& Node<T_derived>::addUsedFunction(FunctionNode* const p_usedFunction)noexcept{
        m_usedFunctions.push_back(p_usedFunction);
        return *dynamic_cast<T_derived*>(this);
    }
    // #
    template<DerivedType T_derived> T_derived& Node<T_derived>::addUsedEnum(EnumNode* const p_usedEnum)noexcept{
        m_usedEnums.push_back(p_usedEnum);
        return *dynamic_cast<T_derived*>(this);
    }

// ----------------------------------------------------------------------------------------------------------------------------------------

// NamespaceNode, method definitions

// public static methods

    // #
    template<StringType T_name, OptionStringType T_alias, OptionStringType T_brief, OptionStringType T_note, OptionStringType T_detail> 
    NamespaceNode* NamespaceNode::build(T_name&& p_name, T_alias&& p_alias, T_brief&& p_brief, T_note&& p_note, T_detail&& p_detail, 
    AnyNode* const p_memberOf, const std::optional<type::Namespace>& p_namespaceType, const bool p_isInline, FileNode* const p_file)noexcept{
        NamespaceNode* build = new NamespaceNode();
        build->setName(std::forward<T_name>(p_name)).complete(std::forward<T_alias>(p_alias), std::forward<T_brief>(p_brief), 
            std::forward<T_note>(p_note), std::forward<T_detail>(p_detail), p_memberOf, p_namespaceType, p_isInline, p_file);
        return build;
    }
    // #
    NamespaceNode* NamespaceNode::build(const std::string& p_name)noexcept{
        NamespaceNode* build = new NamespaceNode();
        build->setName(p_name);
        return build;
    }
    // #
    NamespaceNode* NamespaceNode::build(std::string&& p_name)noexcept{
        NamespaceNode* build = new NamespaceNode();
        build->setName(std::forward<std::string>(p_name));
        return build;
    }
    
// public methods

    // #
    inline type::Node NamespaceNode::type()const noexcept{
        return type::Node::NAMESPACE;
    }
    // #
    template<OptionStringType T_alias, OptionStringType T_brief, OptionStringType T_note, OptionStringType T_detail> 
    NamespaceNode& NamespaceNode::complete(T_alias&& p_alias, T_brief&& p_brief, T_note&& p_note, T_detail&& p_detail, AnyNode* const p_memberOf, 
    const std::optional<type::Namespace>& p_namespaceType, const bool p_isInline, FileNode* const p_file)noexcept{
        this->setAlias(std::forward<T_alias>(p_alias)).setBrief(std::forward<T_brief>(p_brief)).setNote(std::forward<T_note>(p_note))
            .setDetail(std::forward<T_detail>(p_detail)).setMemberOf(p_memberOf).setIsInline(p_isInline).setFile(p_file).setIsComplete(true);
        return *this;
    }
    // #
    inline const std::optional<type::Namespace>& NamespaceNode::namespaceType()const noexcept{
        return m_namespaceType;
    }
    // #
    inline bool NamespaceNode::isInline()const noexcept{
        return m_isInline;
    }
    // #
    inline const std::vector<NamespaceNode*>& NamespaceNode::heldNamespaces()const noexcept{
        return m_heldNamespaces;
    }
    // #
    inline const std::vector<ClassNode*>& NamespaceNode::heldClasses()const noexcept{
        return m_heldClasses;
    }
    // #
    inline const std::vector<FunctionNode*>& NamespaceNode::heldFunctions()const noexcept{
        return m_heldFunctions;
    }
    // #
    inline const std::vector<EnumNode*>& NamespaceNode::heldEnums()const noexcept{
        return m_heldEnums;
    }

// private methods
    
    // #
    NamespaceNode& NamespaceNode::setNamespaceType(const std::optional<type::Namespace>& p_namespaceType)noexcept{
        m_namespaceType = p_namespaceType;
        return *this;
    }
    // #
    NamespaceNode& NamespaceNode::setIsInline(const bool p_isInline)noexcept{
        m_isInline = p_isInline;
        return *this;
    }
    // #
    NamespaceNode& NamespaceNode::addHeldNamespace(NamespaceNode* const p_namespaceNode)noexcept{
        m_heldNamespaces.push_back(p_namespaceNode);
        return *this;
    }
    // #
    NamespaceNode& NamespaceNode::addHeldClass(ClassNode* const p_classNode)noexcept{
        m_heldClasses.push_back(p_classNode);
        return *this;
    }
    // #
    NamespaceNode& NamespaceNode::addHeldFunction(FunctionNode* const p_functionNode)noexcept{
        m_heldFunctions.push_back(p_functionNode);
        return *this;
    }
    // #
    NamespaceNode& NamespaceNode::addHeldEnum(EnumNode* const p_enumNode)noexcept{
        m_heldEnums.push_back(p_enumNode);
        return *this;
    }

// ----------------------------------------------------------------------------------------------------------------------------------------

// ClassNode, method definitions

// public static methods

    // #
    template<StringType T_name, OptionStringType T_alias, OptionStringType T_brief, OptionStringType T_note, OptionStringType T_detail> 
    ClassNode* ClassNode::build(T_name&& p_name, T_alias&& p_alias, T_brief&& p_brief, T_note&& p_note, T_detail&& p_detail, 
    AnyNode* const p_memberOf, const std::optional<type::Class>& p_classType, FileNode* const p_file)noexcept{
        ClassNode* build = new ClassNode();
        build->setName(std::forward<T_name>(p_name)).complete(std::forward<T_alias>(p_alias), std::forward<T_brief>(p_brief), 
            std::forward<T_note>(p_note), std::forward<T_detail>(p_detail), p_memberOf, p_classType, p_file);
        return build;
    }
    // #
    ClassNode* ClassNode::build(const std::string& p_name)noexcept{
        ClassNode* build = new ClassNode();
        build->setName(p_name);
        return build;
    }
    // #
    ClassNode* ClassNode::build(std::string&& p_name)noexcept{
        ClassNode* build = new ClassNode();
        build->setName(std::forward<std::string>(p_name));
        return build;
    }

// public methods

    // #
    inline type::Node ClassNode::type()const noexcept{
        return type::Node::CLASS;
    }
    // #
    template<OptionStringType T_alias, OptionStringType T_brief, OptionStringType T_note, OptionStringType T_detail> 
    ClassNode& ClassNode::complete(T_alias&& p_alias, T_brief&& p_brief, T_note&& p_note, T_detail&& p_detail, AnyNode* const p_memberOf, 
    const std::optional<type::Class>& p_classType, FileNode* const p_file)noexcept{
        this->setAlias(std::forward<T_alias>(p_alias)).setBrief(std::forward<T_brief>(p_brief)).setNote(std::forward<T_note>(p_note))
            .setDetail(std::forward<T_detail>(p_detail)).setMemberOf(p_memberOf).setClassType(p_classType).setFile(p_file).setIsComplete(true);
        return *this;
    }
    // #
    inline const std::optional<type::Class>& ClassNode::classType()const noexcept{
        return m_classType;
    } 
    // #
    inline const std::vector<TemplateType>& ClassNode::templates()const noexcept{
        return m_templates;
    }
    // #
    inline const std::vector<InheritType>& ClassNode::inheritedClasses()const noexcept{
        return m_inheritedClasses;
    }
    // #
    inline const std::vector<FunctionNode*>& ClassNode::friendFunctions()const noexcept{
        return m_friendFunctions;
    }
    // #
    inline const std::vector<ClassNode*>& ClassNode::friendClasses()const noexcept{
        return m_friendClasses;
    }
    // #
    inline const std::vector<ClassNode*>& ClassNode::heldClasses()const noexcept{
        return m_heldClasses;
    }
    // #
    inline const std::vector<FunctionNode*>& ClassNode::heldFunctions()const noexcept{
        return m_heldFunctions;
    }

// private methods

    // #
    ClassNode& ClassNode::setClassType(const type::Class p_classType)noexcept{
        m_classType = p_classType;
        return *this;
    }
    // #
    ClassNode& ClassNode::addTemplate(const TemplateType& p_template)noexcept{
        m_templates.push_back(p_template);
        return *this;
    }
    // #
    ClassNode& ClassNode::addTemplate(TemplateType&& p_template)noexcept{
        m_templates.push_back(std::forward<TemplateType>(p_template));
        return *this;
    }
    // #
    ClassNode& ClassNode::addInheritedClass(const InheritType& p_inheritedClass)noexcept{
        m_inheritedClasses.push_back(p_inheritedClass);
        return *this;
    }
    // #
    ClassNode& ClassNode::addFriendFunction(FunctionNode* const p_friendFunction)noexcept{
        m_friendFunctions.push_back(p_friendFunction);
        return *this;
    }
    // #
    ClassNode& ClassNode::addFriendClass(ClassNode* const p_friendClass)noexcept{
        m_friendClasses.push_back(p_friendClass);
        return *this;
    }
    // #
    ClassNode& ClassNode::addHeldClass(ClassNode* const p_heldClass)noexcept{
        m_heldClasses.push_back(p_heldClass);
        return *this;
    }
    // #
    ClassNode& ClassNode::addHeldFunction(FunctionNode* const p_heldFunction)noexcept{
        m_heldFunctions.push_back(p_heldFunction);
        return *this;
    }
    
// ----------------------------------------------------------------------------------------------------------------------------------------

// FunctionNode, method definitions

// public static methods
    
    // #
    template<StringType T_name, OptionStringType T_alias, OptionStringType T_brief, OptionStringType T_note, OptionStringType T_detail, 
    DataVectorType T_signiture> FunctionNode* FunctionNode::build(T_name&& p_name, T_alias&& p_alias, T_brief&& p_brief, 
    T_note&& p_note, T_detail&& p_detail, const bool p_isVirtual, const bool p_isOverride, const bool p_isInline, const bool p_isConstExpr, 
    const bool p_isNoExcept, const bool p_isConst, const type::Publicity p_publicityType, T_signiture&& p_signiture, 
    FileNode* const p_file)noexcept{
        FunctionNode* build = new FunctionNode();
        build->setName(std::forward<T_name>(p_name)).setSigniture(std::forward<T_signiture>(p_signiture)).complete(std::forward<T_alias>(p_alias), 
            std::forward<T_brief>(p_brief), std::forward<T_note>(p_note), std::forward<T_detail>(p_detail), p_isVirtual, p_isOverride, p_isInline, 
            p_isConstExpr, p_isNoExcept, p_isConst, p_publicityType, p_file);
        return build;
    }
    // #
    template<StringType T_name, DataVectorType T_signature> FunctionNode* FunctionNode::build(T_name&& p_name, 
    T_signature&& p_signiture)noexcept{
        FunctionNode* build = new FunctionNode();
        build->setName(std::forward<T_name>(p_name)).setSigniture(std::forward<T_signature>(p_signiture));
        return build;
    }

// public methods

    // #
    inline type::Node FunctionNode::type()const noexcept{
        return type::Node::FUNCTION;
    }
    // # 
    template<OptionStringType T_alias, OptionStringType T_brief, OptionStringType T_note, OptionStringType T_detail>
    FunctionNode& FunctionNode::complete(T_alias&& p_alias, T_brief&& p_brief, T_note&& p_note, T_detail&& p_detail, const bool p_isVirtual,
    const bool p_isOverride, const bool p_isInline, const bool p_isConstExpr, const bool p_isNoExcept, const bool p_isConst, 
    const type::Publicity p_publicityType, FileNode* const p_file)noexcept{
        this->setAlias(std::forward<T_alias>(p_alias)).setBrief(std::forward<T_brief>(p_brief)).setNote(std::forward<T_note>(p_note))
            .setDetail(std::forward<T_detail>(p_detail)).setIsVirtual(p_isVirtual).setIsOverride(p_isOverride).setIsInline(p_isInline)
            .setIsConstExpr(p_isConstExpr).setIsNoExcept(p_isNoExcept).setIsConst(p_isConst).setPublicityType(p_publicityType).setFile(p_file)
            .setIsComplete(true);
        return *this;
    }
    // #
    inline bool FunctionNode::isVirtual()const noexcept{
        return m_isVirtual;
    }
    // #
    inline bool FunctionNode::isOverride()const noexcept{
        return m_isOverride;
    }
    // #
    inline bool FunctionNode::isInline()const noexcept{
        return m_isInline;
    }
    // #
    inline bool FunctionNode::isConstExpr()const noexcept{
        return m_isConstExpr;
    }
    // #
    inline bool FunctionNode::isNoExcept()const noexcept{
        return m_isNoExcept;
    }
    // #
    inline bool FunctionNode::isConst()const noexcept{
        return m_isConst;
    }
    // #
    inline type::Publicity FunctionNode::publicityType()const noexcept{
        return m_publicityType;
    }
    // #
    inline const std::vector<DataType>& FunctionNode::signiture()const noexcept{
        return m_signiture;
    }
    // #
    inline const std::vector<FunctionNode*>& FunctionNode::overloads()const noexcept{
        return m_overloads;
    }
    // #
    inline const std::vector<TemplateType>& FunctionNode::templates()const noexcept{
        return m_templates;
    }
    // #
    inline const std::vector<ThrowType>& FunctionNode::throws()const noexcept{
        return m_throws;
    }
    // #
    inline const std::vector<RequiredType>& FunctionNode::getRequires()const noexcept{
        return m_requires;
    }
    // #
    inline const std::vector<FunctionNode*>& FunctionNode::calls()const noexcept{
        return m_calls;
    }
    // #
    inline const std::vector<ParameterType>& FunctionNode::parameters()const noexcept{
        return m_parameters;
    }
    // #
    inline const ReturnType& FunctionNode::returnType()const noexcept{
        return m_returnType;
    }

// private methods

    // #
    FunctionNode& FunctionNode::setIsVirtual(const bool p_isVirtual)noexcept{
        m_isVirtual = p_isVirtual;
        return *this;
    }
    // #
    FunctionNode& FunctionNode::setIsOverride(const bool p_isOverride)noexcept{
        m_isOverride = p_isOverride;
        return *this;
    }
    // #
    FunctionNode& FunctionNode::setIsInline(const bool p_isInline)noexcept{
        m_isInline = p_isInline;
        return *this;
    }
    // #
    FunctionNode& FunctionNode::setIsConstExpr(const bool p_isConstExpr)noexcept{
        m_isConstExpr = p_isConstExpr;
        return *this;
    }
    // #
    FunctionNode& FunctionNode::setIsNoExcept(const bool p_isNoExcept)noexcept{
        m_isNoExcept = p_isNoExcept;
        return *this;
    }
    // #
    FunctionNode& FunctionNode::setIsConst(const bool p_isConst)noexcept{
        m_isConst = p_isConst;
        return *this;
    }
    // #
    FunctionNode& FunctionNode::setPublicityType(const type::Publicity p_publicityType)noexcept{
        m_publicityType = p_publicityType;
        return *this;
    }
    // #
    FunctionNode& FunctionNode::setSigniture(const std::vector<DataType>& p_signiture)noexcept{
        m_signiture = p_signiture;
        return *this;
    }
    // #
    FunctionNode& FunctionNode::setSigniture(std::vector<DataType>&& p_signiture)noexcept{
        m_signiture = std::forward<std::vector<DataType>>(p_signiture);
        return *this;
    }
    // #
    FunctionNode& FunctionNode::addOverload(FunctionNode* const p_overload)noexcept{
        m_overloads.push_back(p_overload);
        return *this;
    }
    // #
    FunctionNode& FunctionNode::addTemplate(const TemplateType& p_generic)noexcept{
        m_templates.push_back(p_generic);
        return *this;
    }
    // #
    FunctionNode& FunctionNode::addTemplate(TemplateType&& p_generic)noexcept{
        m_templates.push_back(std::forward<TemplateType>(p_generic));
        return *this;
    }
    // #
    FunctionNode& FunctionNode::addThrow(const ThrowType& p_throw)noexcept{
        m_throws.push_back(p_throw);
        return *this;
    }
    // #
    FunctionNode& FunctionNode::addThrow(ThrowType&& p_throw)noexcept{
        m_throws.push_back(std::forward<ThrowType>(p_throw));
        return *this;
    }
    // #
    FunctionNode& FunctionNode::addRequired(const RequiredType& p_require)noexcept{
        m_requires.push_back(p_require);
        return *this;
    }
    // #
    FunctionNode& FunctionNode::addRequired(RequiredType&& p_require)noexcept{
        m_requires.push_back(std::forward<RequiredType>(p_require));
        return *this;
    }
    // #
    FunctionNode& FunctionNode::addCall(FunctionNode* const p_call)noexcept{
        m_calls.push_back(p_call);
        return *this;
    }
    // #
    FunctionNode& FunctionNode::addParameter(const ParameterType& p_parameter)noexcept{
        m_parameters.push_back(p_parameter);
        return *this;
    }
    // #
    FunctionNode& FunctionNode::addParameter(ParameterType&& p_parameter)noexcept{
        m_parameters.push_back(std::forward<ParameterType>(p_parameter));
        return *this;
    }
    // #
    FunctionNode& FunctionNode::setReturnType(const ReturnType& p_returnType)noexcept{
        m_returnType = p_returnType;
        return *this;
    }
    // #
    FunctionNode& FunctionNode::setReturnType(ReturnType&& p_returnType)noexcept{
        m_returnType = std::forward<ReturnType>(p_returnType);
        return *this;
    }

// ----------------------------------------------------------------------------------------------------------------------------------------

// EnumNode, method definitions

// public static methods

    // #
    template<StringType T_name, OptionStringType T_alias, OptionStringType T_brief, OptionStringType T_note, OptionStringType T_detail> 
    EnumNode* EnumNode::build(T_name&& p_name, T_alias&& p_alias, T_brief&& p_brief, T_note&& p_note, T_detail&& p_detail, 
    const bool p_isClass, const std::optional<type::Data>& p_enumType, FileNode* const p_file)noexcept{
        EnumNode* build = new EnumNode();
        build->setName(std::forward<T_name>(p_name)).complete(std::forward<T_alias>(p_alias), std::forward<T_brief>(p_brief), 
            std::forward<T_note>(p_note), std::forward<T_detail>(p_detail), p_isClass, p_enumType, p_file);
        return build;
    }
    // #
    EnumNode* EnumNode::build(const std::string& p_name)noexcept{
        EnumNode* build = new EnumNode();
        build->setName(p_name);
        return build;
    }
    // #
    EnumNode* EnumNode::build(std::string&& p_name)noexcept{
        EnumNode* build = new EnumNode();
        build->setName(std::forward<std::string>(p_name));
        return build;
    }

// public methods

    // #
    inline type::Node EnumNode::type()const noexcept{
        return type::Node::ENUM;
    }
    // #
    template<OptionStringType T_alias, OptionStringType T_brief, OptionStringType T_note, OptionStringType T_detail> 
    EnumNode& EnumNode::complete(T_alias&& p_alias, T_brief&& p_brief, T_note&& p_note, T_detail&& p_detail, const bool p_isClass,
    const std::optional<type::Data>& p_enumType, FileNode* const p_file)noexcept{
        this->setAlias(std::forward<T_alias>(p_alias)).setBrief(std::forward<T_brief>(p_brief)).setNote(std::forward<T_note>(p_note))
            .setDetail(std::forward<T_detail>(p_detail)).setIsClass(p_isClass).setEnumType(p_enumType).setFile(p_file).setIsComplete(true);
        return *this;
    }
    // #
    inline bool EnumNode::isClass()const noexcept{
        return m_isClass;
    }
    // #
    inline const std::optional<type::Data>& EnumNode::enumType()const noexcept{
        return m_enumType;
    }

// private methods

    // #
    EnumNode& EnumNode::setIsClass(const bool p_isClass)noexcept{
        m_isClass = p_isClass;
        return *this;
    }
    // #
    EnumNode& EnumNode::setEnumType(const std::optional<type::Data>& p_enumType)noexcept{
        m_enumType = p_enumType;
        return *this;
    }

// ----------------------------------------------------------------------------------------------------------------------------------------

// ConceptNode, method definitions

// public static methods

    // #
    template<StringType T_name, OptionStringType T_alias, OptionStringType T_brief, OptionStringType T_note, OptionStringType T_detail> 
    ConceptNode* ConceptNode::build(T_name&& p_name, T_alias&& p_alias, T_brief&& p_brief, T_note&& p_note, T_detail&& p_detail, 
    const TemplateType& p_template, FileNode* const p_file)noexcept{
        ConceptNode* build = new ConceptNode();
        build->setName(std::forward<T_name>(p_name)).complete(std::forward<T_alias>(p_alias), std::forward<T_brief>(p_brief), 
            std::forward<T_note>(p_note), std::forward<T_detail>(p_detail), p_template, p_file);
        return build;
    }
    // #
    ConceptNode* ConceptNode::build(const std::string& p_name)noexcept{
        ConceptNode* build = new ConceptNode();
        build->setName(p_name);
        return build;
    }
    // #
    ConceptNode* ConceptNode::build(std::string&& p_name)noexcept{
        ConceptNode* build = new ConceptNode();
        build->setName(std::forward<std::string>(p_name));
        return build;
    }

// public methods

    // #
    inline type::Node ConceptNode::type()const noexcept{
        return type::Node::CONCEPT;
    }
    // #
    template<OptionStringType T_alias, OptionStringType T_brief, OptionStringType T_note, OptionStringType T_detail> 
    ConceptNode& ConceptNode::complete(T_alias&& p_alias, T_brief&& p_brief, T_note&& p_note, T_detail&& p_detail, 
    const TemplateType& p_template, FileNode* const p_file)noexcept{
        this->setAlias(std::forward<T_alias>(p_alias)).setBrief(std::forward<T_brief>(p_brief)).setNote(std::forward<T_note>(p_note))
            .setDetail(std::forward<T_detail>(p_detail)).setTemplates(p_template).setFile(p_file).setIsComplete(true);
        return *this;
    }
    // #
    inline const TemplateType& ConceptNode::templates()const noexcept{
        return m_templates;
    }

// private methods

    // #
    ConceptNode& ConceptNode::setTemplates(const TemplateType& p_template)noexcept{
        m_templates = p_template;
        return *this;
    }
    // #
    ConceptNode& ConceptNode::setTemplates(TemplateType&& p_template)noexcept{
        m_templates = std::forward<TemplateType>(p_template);
        return *this;
    }

} // namespace worTech::cdocs::genorator::nodes