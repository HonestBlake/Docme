#pragma once

#include "autoDoc.hpp"
#include "conceptTypes.hpp"

// #class: g
// #note: g
// g
// g
// #brief: gff

/*

  
    #class:  DataType,  data  structure
    #note:  DataType
    ffd
    #brief:  DataType 
*/

// TODO continuation doesnt work and multi line comments are not handled

namespace worTech::autoDoc::genorator::nodes{

    // #namespace: typeEnumerations(type), variable namespace
    namespace typeEnumerations{
        // #enum: DataType(Data), uint8_t enum class
        enum class DataType: uint8_t{
            VOID,
            INT,
            UINT,
            FLOAT,
            DOUBLE,
            CHAR,
            STRING,
            BOOL,
            SHORT,
            USHORT,
            LONG,
            ULONG,
            LONGLONG,
            ULONGLONG,
            UCHAR,
            LONGDOUBLE,
            INT64,
            INT32,
            INT16,
            INT8,
            UINT64,
            UINT32,
            UINT16,
            UINT8,
            CLASS, // special type for templates
            TYPENAME, // special type for templates
            CONSTRUCTOR, // special type for constructor returns
            DESTRUCTOR // special type for destructor returns
        };
        // #TypeSpecifier(Specifier), uint8_t enum class
        enum class TypeSpecifier: uint8_t{
            REFERENCE, 
            RVALUE_REFERENCE,
            POINTER,
            POINTER_TO_CONST
        }; 
        // #enum: PublicityType(Publicity), uint8_t enum class
        enum class PublicityType: uint8_t{
            PUBLIC,
            PUBLIC_STATIC,
            PRIVATE,
            PRIVATE_STATIC,
            PROTECTED,
            PROTECTED_STATIC,
            NON_MEMEBER
        };
        // #enum: NodeType(Node), uint8_t enum class
        enum class NodeType: uint8_t{
            GLOBAL_SPACE,
            NAMESPACE,
            CLASS,
            FUNCTION,
            ENUM,
            CONCEPT
        };
        // #enum: NamespaceType(Namespace), uint8_t enum class
        enum class NamespaceType: uint8_t{
            DEVELOPER,
            PROJECT,
            MODULE,
            COMPONENT,
            FUNCTION,
            VARIABLE
        };
        // #enum: ClassType(Class), uint8_t enum class
        enum class ClassType: uint8_t{
            OBJECT_CLASS, 
            ABSTRACT_CLASS,
            STATIC_CLASS,
            ABSTRACT_STATIC_CLASS,
            FACTORY_CLASS,
            ABSTRACT_FACTORY_CLASS,
            SINGLETON_CLASS,
            ABSTRACT_SINGLETON_CLASS,  
            DATA_STRUCT
        };
        // #enum: FileType(File), uint8_t enum class
        enum class FileType: uint8_t{
            HEADER,
            EXTERNAL,
            SOURCE,
            MAIN
        };
    }
    // #struct: DataType, data structure
    struct DataType{
        std::variant<type::Data, std::string> type;
        bool isConst;                                                                 
        std::optional<type::Specifier> specifier;
        DataType() = default;
        ~DataType() = default;
    };
    // #struct: ParameterType, data structure
    struct ParameterType{
        DataType type;
        std::string name;
        std::optional<std::string> body;         //      DataType-v name-v  v-default v-body
        std::optional<std::string> defaultValue; // #param: const int p_num(0), num param
        ParameterType() = default;
        ~ParameterType() = default;
    };
    // #struct: ReturnType, data structure
    struct ReturnType{
        DataType type;                          //             v-DataType         v-body                     
        std::optional<std::string> body;        // #return: const std::string&, returns value
        ReturnType() = default;
        ~ReturnType() = default;
    };
    // #stuct: TemplateType, data structure
    struct TemplateType{  
        std::string type;                   //         type-v    v-name   v-body
        std::string name;                   // #template: class T_name, type of name
        std::optional<std::string> body;
        TemplateType() = default;
        ~TemplateType() = default;
    };
    // #struct: InheritType, data structure
    struct InheritType{ 
        ClassNode* inherits;                //      publicity-v    v-inherits
        type::Publicity publicity;          // #inherits: public BaseClass, class
        InheritType() = default;
        ~InheritType() = default;
    };
    // #struct: ThrowType, data structure
    struct ThrowType{
        std::string exception;                  //              v-exception       v-body
        std::string body;                       // #throw: std::runtime_error, error when lala             
        ThrowType() = default;
        ~ThrowType() = default;
    };
    // #struct: RequiredType, data structure
    struct RequiredType{
        std::string required;                   //              v-required          v-body
        std::string body;                       // #requires: checkSomthing(), check if something is true
        RequiredType() = default;
        ~RequiredType() = default;
    };
    // #class: FileNode, class object
    class FileNode{
    public:
    // public factory methods
        ~FileNode() = default;
    // public static methods
        static FileNode* build(const std::string& p_name, const type::File p_fileType)noexcept;
        static FileNode* build(std::string&& p_name, const type::File p_fileType)noexcept;
        template <StringType T_name,OptionStringType T_brief, OptionStringType T_note, OptionStringType T_detail> 
            static FileNode* build(T_name&& p_name, const type::File p_fileType, T_brief&& p_brief, T_note&& p_note, T_detail&& p_detail)noexcept;
    // public methods
        template<OptionStringType T_brief, OptionStringType T_note, OptionStringType T_detail> FileNode& complete(T_brief&& p_brief, 
            T_note&& p_note, T_detail&& p_detail)noexcept;
        inline const std::string& name()const noexcept;
        inline type::File fileType()const noexcept;
        inline const std::optional<std::string>& brief()const noexcept;
        inline const std::optional<std::string>& note()const noexcept;
        inline const std::optional<std::string>& detail()const noexcept;
        inline const std::vector<FileNode*>& dependencies()const noexcept;
        inline bool isComplete()const noexcept;
    private:
    // private members
        std::string m_name;
        type::File m_fileType;
        std::optional<std::string> m_brief;
        std::optional<std::string> m_note;
        std::optional<std::string> m_detail;
        std::vector<FileNode*> m_depenendencies;
        bool m_isComplete;
    // private factory methods
        FileNode() = default;
    // private methods
        FileNode& setName(const std::string& p_name)noexcept;
        FileNode& setName(std::string&& p_name)noexcept;
        FileNode& setFileType(const type::File p_fileType)noexcept;
        FileNode& setBrief(const std::optional<std::string>& p_brief)noexcept;
        FileNode& setBrief(std::optional<std::string>&& p_brief)noexcept;
        FileNode& setNote(const std::optional<std::string>& p_note)noexcept;
        FileNode& setNote(std::optional<std::string>&& p_note)noexcept;
        FileNode& setDetail(const std::optional<std::string>& p_detail)noexcept;
        FileNode& setDetail(std::optional<std::string>&& p_detail)noexcept;
        FileNode& addDependency(FileNode* const p_dependency)noexcept;
        FileNode& setIsComplete(const bool p_isComplete)noexcept;
    };
    // #class: GlobalSpace, signleton class
    class GlobalSpace{
    public:
    // public factory methods
        ~GlobalSpace() = default;
    // public static methods
        static GlobalSpace& getInstance()noexcept;
    // public methods
        inline type::Node type()const noexcept;
    private:
    // private factory methods
        GlobalSpace() = default;
    };
    // #class: Node, abstract class
    template<DerivedType T_derived> class Node{
    public:
    // public factory methods
        virtual ~Node() = default;
    // public methods
        inline virtual type::Node type()const noexcept = 0;
        inline bool isComplete()const noexcept;
        inline FileNode* file()const noexcept;
        inline const std::string& name()const noexcept;
        inline const std::optional<std::string>& alias()const noexcept;
        inline const std::optional<std::string>& brief()const noexcept;
        inline const std::optional<std::string>& note()const noexcept;
        inline const std::optional<std::string>& detail()const noexcept;
        inline AnyNode* memberOf()const noexcept;
        inline const std::vector<NamespaceNode*>& usedNamespaces()const noexcept;
        inline const std::vector<ClassNode*>& usedClasses()const noexcept;
        inline const std::vector<FunctionNode*>& usedFunctions()const noexcept;
        inline const std::vector<EnumNode*>& usedEnums()const noexcept;
    protected:
    // protected members
        bool m_isComplete;
        FileNode* m_file;
        std::string m_name; 
        std::optional<std::string> m_alias;
        std::optional<std::string> m_brief;
        std::optional<std::string> m_note;
        std::optional<std::string> m_detail;
        AnyNode* m_memberOf;
        std::vector<NamespaceNode*> m_usedNamespaces;
        std::vector<ClassNode*> m_usedClasses;
        std::vector<FunctionNode*> m_usedFunctions;
        std::vector<EnumNode*> m_usedEnums;
    // protected factory methods
        Node()noexcept = default;
    // protected methods
        T_derived& setIsComplete(const bool p_isComplete)noexcept;
        T_derived& setFile(FileNode* const p_file)noexcept;
        T_derived& setName(const std::string& p_name)noexcept;
        T_derived& setName(std::string&& p_name)noexcept;
        T_derived& setAlias(const std::optional<std::string>& p_alias)noexcept;
        T_derived& setAlias(std::optional<std::string>&& p_alias)noexcept;
        T_derived& setBrief(const std::optional<std::string>& p_brief)noexcept;
        T_derived& setBrief(std::optional<std::string>&& p_brief)noexcept;
        T_derived& setNote(const std::optional<std::string>& p_note)noexcept;
        T_derived& setNote(std::optional<std::string>&& p_note)noexcept;
        T_derived& setDetail(const std::optional<std::string>& p_detail)noexcept;
        T_derived& setDetail(std::optional<std::string>&& p_detail)noexcept;
        T_derived& setMemberOf(AnyNode* const p_memberOf)noexcept;
        T_derived& addUsedNamespace(NamespaceNode* const p_usedNamespace)noexcept;
        T_derived& addUsedClass(ClassNode* const p_usedClass)noexcept;
        T_derived& addUsedFunction(FunctionNode* const p_usedFunction)noexcept;
        T_derived& addUsedEnum(EnumNode* const p_usedEnum)noexcept;
    };
    // #class: NamespaceNode, class object
    class NamespaceNode: public Node<NamespaceNode>{
    public:
    // public facotry methods
        ~NamespaceNode() = default;
    // public static methods
        template<StringType T_name, OptionStringType T_alias, OptionStringType T_brief, OptionStringType T_note, OptionStringType T_detail> 
            static NamespaceNode* build(T_name&& p_name, T_alias&& p_alias, T_brief&& p_brief, T_note&& p_note, T_detail&& p_detail, 
            AnyNode* const p_memberOf, const std::optional<type::Namespace>& p_namespaceType, const bool p_isInline, FileNode* const p_file)noexcept;
        static NamespaceNode* build(const std::string& p_name)noexcept;
        static NamespaceNode* build(std::string&& p_name)noexcept;
    // public methods    
        inline type::Node type()const noexcept override;
        template<OptionStringType T_alias, OptionStringType T_brief, OptionStringType T_note, OptionStringType T_detail> 
            NamespaceNode& complete(T_alias&& p_alias, T_brief&& p_brief, T_note&& p_note, T_detail&& p_detail, AnyNode* const p_memberOf, 
            const std::optional<type::Namespace>& p_namespaceType, const bool p_isInline, FileNode* const p_file)noexcept;
        inline const std::optional<type::Namespace>& namespaceType()const noexcept;
        inline bool isInline()const noexcept;
        inline const std::vector<NamespaceNode*>& heldNamespaces()const noexcept;
        inline const std::vector<ClassNode*>& heldClasses()const noexcept;
        inline const std::vector<FunctionNode*>& heldFunctions()const noexcept;
        inline const std::vector<EnumNode*>& heldEnums()const noexcept;
    private:
    // private members
        std::optional<type::Namespace> m_namespaceType;
        bool m_isInline;
        std::vector<NamespaceNode*> m_heldNamespaces;
        std::vector<ClassNode*> m_heldClasses;
        std::vector<FunctionNode*> m_heldFunctions; 
        std::vector<EnumNode*> m_heldEnums;
    // private factory methods
        NamespaceNode()noexcept = default;
    // private methods
        NamespaceNode& setNamespaceType(const std::optional<type::Namespace>& p_namespaceType)noexcept;
        NamespaceNode& setIsInline(const bool p_isInline)noexcept;
        NamespaceNode& addHeldNamespace(NamespaceNode* const p_namespaceNode)noexcept;
        NamespaceNode& addHeldClass(ClassNode* const p_classNode)noexcept;
        NamespaceNode& addHeldFunction(FunctionNode* const p_functionNode)noexcept;
        NamespaceNode& addHeldEnum(EnumNode* const p_enumNode)noexcept;
    };
    // #class: ClassNode, class object
    class ClassNode: public Node<ClassNode>{
    public:
    // public factory method
        ~ClassNode() = default;
    // public static methods
        template<StringType T_name, OptionStringType T_alias, OptionStringType T_brief, OptionStringType T_note, OptionStringType T_detail> 
            static ClassNode* build(T_name&& p_name, T_alias&& p_alias, T_brief&& p_brief, T_note&& p_note, T_detail&& p_detail, 
            AnyNode* const p_memberOf, const std::optional<type::Class>& p_classType, FileNode* const p_file)noexcept;
        static ClassNode* build(const std::string& p_name)noexcept;
        static ClassNode* build(std::string&& p_name)noexcept;
    // public methods
        inline type::Node type()const noexcept override;
        template<OptionStringType T_alias, OptionStringType T_brief, OptionStringType T_note, OptionStringType T_detail> 
        ClassNode& complete(T_alias&& p_alias, T_brief&& p_brief, T_note&& p_note, T_detail&& p_detail, 
        AnyNode* const p_memberOf, const std::optional<type::Class>& p_classType, FileNode* const p_file)noexcept;
        inline const std::optional<type::Class>& classType()const noexcept;
        inline const std::vector<TemplateType>& templates()const noexcept;
        inline const std::vector<InheritType>& inheritedClasses()const noexcept;
        inline const std::vector<FunctionNode*>& friendFunctions()const noexcept;
        inline const std::vector<ClassNode*>& friendClasses()const noexcept;
        inline const std::vector<FunctionNode*>& heldFunctions()const noexcept;
        inline const std::vector<ClassNode*>& heldClasses()const noexcept;
    private:
    // private members
        std::optional<type::Class> m_classType;   
        // TODO add tempalte and other needs specialazation?
        std::vector<TemplateType> m_templates;
        std::vector<InheritType> m_inheritedClasses;
        std::vector<FunctionNode*> m_friendFunctions;
        std::vector<ClassNode*> m_friendClasses;
        std::vector<FunctionNode*> m_heldFunctions;
        std::vector<ClassNode*> m_heldClasses;
    // private factory methods
        ClassNode()noexcept = default;
    // private 
        ClassNode& setClassType(const type::Class p_classType)noexcept;
        ClassNode& addTemplate(const TemplateType& p_template)noexcept;
        ClassNode& addTemplate(TemplateType&& p_template)noexcept;
        ClassNode& addInheritedClass(const InheritType& p_inheritedClass)noexcept;
        ClassNode& addFriendFunction(FunctionNode* const p_friendFunction)noexcept;
        ClassNode& addFriendClass(ClassNode* const p_friendClass)noexcept;
        ClassNode& addHeldClass(ClassNode* const p_class)noexcept;
        ClassNode& addHeldFunction(FunctionNode* const p_function)noexcept;
    };
    //# class: FunctionNode, class object
    class FunctionNode: public Node<FunctionNode>{
    public:
    // public factory methods
        ~FunctionNode() = default;
    // public static methods
        template<StringType T_name, OptionStringType T_alias, OptionStringType T_brief, OptionStringType T_note, OptionStringType T_detail, 
            DataVectorType T_signiture> static FunctionNode* build(T_name&& p_name, T_alias&& p_alias, T_brief&& p_brief, T_note&& p_note, 
            T_detail&& p_detail, const bool p_isVirtual, const bool p_isOverride, const bool p_isInline, const bool p_isConstExpr, 
            const bool p_isNoExcept, const bool p_isConst, const type::Publicity p_publicityType, T_signiture&& p_signiture, FileNode* const p_file)noexcept;
        template<StringType T_name, DataVectorType T_signature> static FunctionNode* build(T_name&& p_name, 
            T_signature&& p_signiture)noexcept;
    // public methods
        inline type::Node type()const noexcept override;
        template<OptionStringType T_alias, OptionStringType T_brief, OptionStringType T_note, OptionStringType T_detail>
            FunctionNode& complete(T_alias&& p_alias, T_brief&& p_brief, T_note&& p_note, T_detail&& p_detail, const bool p_isVirtual,
            const bool p_isOverride, const bool p_isInline, const bool p_isConstExpr, const bool p_isNoExcept, const bool p_isConst, 
            const type::Publicity p_publicityType, FileNode* const p_file)noexcept;
        inline bool isVirtual()const noexcept;
        inline bool isOverride()const noexcept;
        inline bool isInline()const noexcept;
        inline bool isConstExpr()const noexcept;
        inline bool isNoExcept()const noexcept;
        inline bool isConst()const noexcept;
        inline type::Publicity publicityType()const noexcept;
        inline const std::vector<DataType>& signiture()const noexcept;
        inline const std::vector<FunctionNode*>& overloads()const noexcept;
        inline const std::vector<TemplateType>& templates()const noexcept;
        inline const std::vector<ThrowType>& throws()const noexcept;
        inline const std::vector<RequiredType>& getRequires()const noexcept;
        inline const std::vector<FunctionNode*>& calls()const noexcept;
        inline const std::vector<ParameterType>& parameters()const noexcept;
        inline const ReturnType& returnType()const noexcept;
    private:
    // private members
        bool m_isVirtual;
        bool m_isOverride;
        bool m_isInline;
        bool m_isConstExpr;
        bool m_isNoExcept;
        bool m_isConst;
        type::Publicity m_publicityType;
        std::vector<DataType> m_signiture;
        std::vector<FunctionNode*> m_overloads;
        std::vector<TemplateType> m_templates;
        std::vector<ThrowType> m_throws;
        std::vector<RequiredType> m_requires;
        std::vector<FunctionNode*> m_calls;
        std::vector<ParameterType> m_parameters;
        ReturnType m_returnType;
    // private factory methods
        FunctionNode()noexcept;
    // private methods
        FunctionNode& setIsVirtual(const bool p_isVirtual)noexcept;
        FunctionNode& setIsOverride(const bool p_isOverride)noexcept;
        FunctionNode& setIsInline(const bool p_isInline)noexcept;
        FunctionNode& setIsConstExpr(const bool p_isConstExpr)noexcept;
        FunctionNode& setIsNoExcept(const bool p_isNoExcept)noexcept;
        FunctionNode& setIsConst(const bool p_isConst)noexcept;
        FunctionNode& setPublicityType(const type::Publicity p_publicityType)noexcept;
        FunctionNode& setSigniture(const std::vector<DataType>& p_signiture)noexcept;
        FunctionNode& setSigniture(std::vector<DataType>&& p_signiture)noexcept;
        FunctionNode& addOverload(FunctionNode* const p_overload)noexcept;
        FunctionNode& addTemplate(const TemplateType& p_template)noexcept;
        FunctionNode& addTemplate(TemplateType&& p_template)noexcept;
        FunctionNode& addThrow(const ThrowType& p_throw)noexcept;
        FunctionNode& addThrow(ThrowType&& p_throw)noexcept;
        FunctionNode& addRequired(const RequiredType& p_require)noexcept;
        FunctionNode& addRequired(RequiredType&& p_require)noexcept;
        FunctionNode& addCall(FunctionNode* const p_call)noexcept;
        FunctionNode& addParameter(const ParameterType& p_parameter)noexcept;
        FunctionNode& addParameter(ParameterType&& p_parameter)noexcept;
        FunctionNode& setReturnType(const ReturnType& p_returnType)noexcept;
        FunctionNode& setReturnType(ReturnType&& p_returnType)noexcept;
    };
    // #class: EnumNode, class object
    class EnumNode: public Node<EnumNode>{
    public:
    // public factory methods
        ~EnumNode() = default;
    // public static methods
        template<StringType T_name, OptionStringType T_alias, OptionStringType T_brief, OptionStringType T_note, OptionStringType T_detail> 
            static EnumNode* build(T_name&& p_name, T_alias&& p_alias, T_brief&& p_brief, T_note&& p_note, T_detail&& p_detail, 
            const bool p_isClass, const std::optional<type::Data>& p_enumType, FileNode* const p_file)noexcept;
        static EnumNode* build(const std::string& p_name)noexcept;
        static EnumNode* build(std::string&& p_name)noexcept;
    // public methods
        inline type::Node type()const noexcept override;
        template<OptionStringType T_alias, OptionStringType T_brief, OptionStringType T_note, OptionStringType T_detail> 
            EnumNode& complete(T_alias&& p_alias, T_brief&& p_brief, T_note&& p_note, T_detail&& p_detail, 
            const bool p_isClass, const std::optional<type::Data>& p_enumType, FileNode* const p_file)noexcept;
        inline bool isClass()const noexcept;
        inline const std::optional<type::Data>& enumType()const noexcept;
    private:
    // private members
        bool m_isClass;
        std::optional<type::Data> m_enumType;
    // private factory methods
        EnumNode() = default;
    // private methods
        EnumNode& setIsClass(const bool p_isClass)noexcept;
        EnumNode& setEnumType(const std::optional<type::Data>& p_enumType)noexcept;
    };
    // #
    class ConceptNode: public Node<ConceptNode>{
    public:
    // public factory methods
        ~ConceptNode() = default;
    // public static methods
        template<StringType T_name, OptionStringType T_alias, OptionStringType T_brief, OptionStringType T_note, OptionStringType T_detail> 
            static ConceptNode* build(T_name&& p_name, T_alias&& p_alias, T_brief&& p_brief, T_note&& p_note, T_detail&& p_detail, 
            const TemplateType& p_template, FileNode* const p_file)noexcept;
        static ConceptNode* build(const std::string& p_name)noexcept;
        static ConceptNode* build(std::string&& p_name)noexcept;
    // public methods
        inline type::Node type()const noexcept override;
        template<OptionStringType T_alias, OptionStringType T_brief, OptionStringType T_note, OptionStringType T_detail> 
            ConceptNode& complete(T_alias&& p_alias, T_brief&& p_brief, T_note&& p_note, T_detail&& p_detail, 
            const TemplateType& p_template, FileNode* const p_file)noexcept;
        inline const TemplateType& templates()const noexcept;
    private:
    // private members
        TemplateType m_templates;
    // private factory methods
        ConceptNode() = default;
    // private methods
        ConceptNode& setTemplates(const TemplateType& p_template)noexcept;
        ConceptNode& setTemplates(TemplateType&& p_template)noexcept;
    };

} // namespace worTech::cdocs::genorator::nodes