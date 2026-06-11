# CDoc Standard

CDoc is the standard Docme language handler for C and C++.

CDoc tags describe source elements using a simple comment form:

```cpp
// #TAG: <body>
```

Tags can declare an element or add attributes to an existing element.

Tags are not case sensitive, but this standard shows tags in uppercase. Tags should use one tag per comment line.

Tags can start with either `#` or `@`. Both are accepted, but `#` is used throughout this standard.

Tags are followed by `:`. The colon does not need to be immediately after the tag and may be preceded by whitespace.

```cpp
// #TAG    : this is allowed
```

Commas `,` are often used to separate the parts of a tag, such as an identifier and a type or description. Commas are not reserved characters and may still appear inside body text when the tag allows free text.

```cpp
// #CLASS: MyClass, Exported Final Class
// #BRIEF: Here is a description, including a comma.
export class MyClass final{
    // Some code
};
```

The parser should trim preceding and trailing whitespace around body parts.

```cpp
// #TAG:       some body here   ,    second part here
```

Body parts should parse to:

    "some body here"
    "second part here"

Some tags can extend to other lines. Those tags are documented as extendable.

```cpp
// #EXTENDABLE_TAG: <body>
// <body_continued>
```

Tags can use single-line comments or multi-line comments.

```cpp
/*
    #TAG: <body>
    #TAG2: <body>
*/
```

Tags do not need to be on a stand-alone comment line. They may be inline with code.

```cpp
import docme.core; // #IMPORT: docme.core, Project core module
```

## Tag Body Conventions

Most tags use one of these body forms:

    #TAG: <body>
    #TAG: <identifier>, <description>
    #TAG: <identifier>, <type_or_kind>
    #TAG: <signature>, <type_or_kind>

When the first body part contains commas as part of C++ syntax, the parser should preserve the full signature whenever possible.

```cpp
// #METHOD: Error<T_ContextArgs>(const Code, const T_ContextArgs&...), Public Template Constructor
```

## Tag Index

| Tag | Kind | Purpose |
| --- | --- | --- |
| `#FILE` | Declaration | Declares the current file. |
| `#MODULE` | Declaration | Declares a C++ module or module partition. |
| `#NAMESPACE` | Declaration | Declares a namespace element. |
| `#CLASS` | Declaration | Declares a class element. |
| `#STRUCT` | Declaration | Declares a struct element. |
| `#ENUM` | Declaration | Declares an enum element. |
| `#FUNCTION` | Declaration | Declares a free function element. |
| `#METHOD` | Declaration | Declares a member function, constructor, destructor, or operator element. |
| `#ALIAS` | Declaration | Declares an alias element. |
| `#BRIEF` | Attribute | Adds a short description. |
| `#DETAIL` | Attribute | Adds a detailed description. |
| `#NOTE` | Attribute | Adds an important note. |
| `#INCLUDE` | Attribute | Documents an included file. |
| `#IMPORT` | Attribute | Documents an imported module. |
| `#EXPORT` | Attribute | Documents an exported import. |
| `#IMPLEMENTS` | Attribute | Documents which module or partition a source file implements. |
| `#DERIVES` | Attribute | Documents a base type relationship. |
| `#SPECIALIZES` | Attribute | Documents a type specialization relationship. |
| `#SPECIAL` | Attribute | Documents a specialized function or method implementation. |
| `#TEMPLATE` | Attribute | Documents template parameters. |
| `#PARAM` | Attribute | Documents a callable parameter. |
| `#RETURN` | Attribute | Documents a return type and return meaning. |
| `#THROWS` | Attribute | Documents an exception condition. |
| `#DEFAULT` | Attribute | Documents a defaulted declaration. |
| `#DELETE` | Attribute | Documents a deleted declaration. |
| `#SCOPE` | Structural | Opens or selects a documentation scope. |
| `#END` | Structural | Closes a documentation scope or element. |
| `#DIV` | Structural | Adds an organizational division inside the current scope. |

## General Attributes

General attributes can be attached to any documented element.

### `#BRIEF`

Adds a short description to an element.

**Syntax**

    #BRIEF: <body>

**Example**

```cpp
// #BRIEF: Loads the project configuration.
```

### `#DETAIL`

Adds a detailed description to an element.

**Extendable**

Yes.

**Syntax**

    #DETAIL: <body>

**Example**

```cpp
// #DETAIL: Reads the config file, validates required keys, and stores normalized paths.
```

### `#NOTE`

Adds an important note to an element.

Multiple notes may be attached to the same element.

**Syntax**

    #NOTE: <body>

**Example**

```cpp
// #NOTE: Returns error codes: DOCME_200, DOCME_201, DOCME_202, DOCME_203
```

## File Elements

File elements document source, header, module, template implementation, and other project files.

### Declaration Tags

Declaration tags create the documented element.

#### `#FILE`

Declares the current file.

The first body part is the file name. The second body part is the file type or role.

**Syntax**

    #FILE: <file_name>, <file_type>

**Examples**

```cpp
// #FILE: docme.cpp, Project Main File
// #FILE: result.tpp, Component Template Implementation File
// #FILE: configFile.mpp, Component Module Interface File
```

### Special Attribute Tags

Attribute tags add metadata to a file element or to the declaration on the same line.

#### `#INCLUDE`

Documents an included file.

This tag is usually written inline with the `#include` directive.

**Syntax**

    #INCLUDE: <include_name>, <include_description>

**Examples**

```cpp
#include "core.hpp" // #INCLUDE: core.hpp, Package wide header
#include <cpplocate/cpplocate.h> // #INCLUDE: cpplocate/cpplocate.h, External lib for bin dir
```

#### `#IMPORT`

Documents an imported module.

This tag is usually written inline with an `import` statement.

**Syntax**

    #IMPORT: <import_name>, <import_description>

**Examples**

```cpp
import docme.core; // #IMPORT: docme.core, Project error type
import nlohmann.json; // #IMPORT: nlohmann.json, External json library
```

#### `#EXPORT`

Documents an exported import.

This tag is usually written inline with an `export import` statement.

**Syntax**

    #EXPORT: <export_name>, <export_description>

**Example**

```cpp
export import :errors; // #EXPORT: :errors, Import export errors component
```

#### `#IMPLEMENTS`

Documents the module or module partition implemented by a source or template implementation file.

This tag is usually written inline with the implementation `module` declaration.

**Syntax**

    #IMPLEMENTS: <module_name>
    #IMPLEMENTS: <module_name>, <description>

**Examples**

```cpp
module docme.core; // #IMPLEMENTS: docme.core:json
module docme.engine; // #IMPLEMENTS: docme.engine:configFile
```

## Module And Namespace Elements

Module and namespace tags document C++ module and namespace declarations.

### Declaration Tags

#### `#MODULE`

Declares a C++ module or module partition.

The first body part is the module name. The second body part is the module role.

**Syntax**

    #MODULE: <module_name>, <module_type>

**Examples**

```cpp
// #MODULE: docme, Project Module
export module docme;

// #MODULE: docme.core:json, Component Module Partition
export module docme.core:json;
```

#### `#NAMESPACE`

Declares a namespace element.

The first body part is the namespace name. The second body part is the namespace role.

**Syntax**

    #NAMESPACE: <namespace_name>, <namespace_type>

**Example**

```cpp
// #NAMESPACE: core, Package Namespace
namespace core{
}
```

### Structural Tags

#### `#SCOPE`

Opens or selects a documentation scope.

Use this when implementation code enters a namespace, class, struct, enum, specialization, or other named scope without redeclaring the element.

This tag can be written inline with the scope-opening code or on a stand-alone comment line.

**Syntax**

    #SCOPE: <scope_name>

**Examples**

```cpp
namespace docme::core{ // #SCOPE: docme::core

// #SCOPE: Result<T_Return>
```

#### `#END`

Closes a documentation scope or element.

The body should match the currently closing scope or the signature of the declaration being closed.

**Syntax**

    #END: <scope_name_or_signature>

**Examples**

```cpp
}; // #END: Json
} // #END: docme::core

// #END: Result<T_Return>
```

#### `#DIV`

Adds an organizational division inside the current scope.

This tag is used for sections such as public methods, private methods, public operators, or factory methods.

**Syntax**

    #DIV: <division_title>

**Examples**

```cpp
// #DIV: Public Factory Methods
// #DIV: Private Static Methods
// #DIV: Public Operators
```

## Type Elements

Type elements document classes, structs, enums, inheritance, templates, and specializations.

### Declaration Tags

#### `#CLASS`

Declares a class element.

The first body part is the class name. The second body part is the class role, qualifiers, or kind.

**Syntax**

    #CLASS: <class_name>, <class_type>

**Examples**

```cpp
// #CLASS: Json, Exported Final Class
export class Json final{
};

// #CLASS: ConfigFile::Error, Final Class
class ConfigFile::Error final: public core::Error{
};
```

#### `#STRUCT`

Declares a struct element.

The first body part is the struct name. The second body part is the struct role, qualifiers, or kind.

**Syntax**

    #STRUCT: <struct_name>, <struct_type>

**Example**

```cpp
// #STRUCT: Node, Struct
struct Node{
};
```

#### `#ENUM`

Declares an enum element.

The first body part is the enum name. The second body part is the enum role, underlying type, or kind.

**Syntax**

    #ENUM: <enum_name>, <enum_type>

**Example**

```cpp
// #ENUM: Code, Exported std::uint16_t Enum class
enum class Code: std::uint16_t{
};
```

#### `#ALIAS`

Declares an alias element.

The first body part should contain the alias expression. The second body part is the alias description.

**Syntax**

    #ALIAS: <alias_name> = <target_name>, <alias_description>

**Example**

```cpp
namespace std_fs = std::filesystem; // #ALIAS: std_fs = std::filesystem, Alias for std::filesystem
```

### Attribute Tags

#### `#DERIVES`

Documents a base type relationship.

The first body part is the inheritance expression. The second body part describes the base type role.

**Syntax**

    #DERIVES: <access> <base_type>, <base_description>

**Examples**

```cpp
// #DERIVES: public docme::core::Error, Base project error type
// #DERIVES: public pureLog::Logger<Logger>, Base logger
```

#### `#TEMPLATE`

Documents template parameters for the current type, method, function, or specialization.

The first body part is the template parameter list. The second body part describes the parameter list.

**Syntax**

    #TEMPLATE: <template_parameters>, <description>

**Examples**

```cpp
// #TEMPLATE: class T_Return = void, Success type default to void
// #TEMPLATE: class... T_ContextArgs, Context arguments parameter pack
```

#### `#SPECIALIZES`

Documents that the current type specializes another type or template.

**Syntax**

    #SPECIALIZES: <specialized_type>

**Example**

```cpp
// #CLASS: Result<void>, Exported Final Template Class Specialization
// #SPECIALIZES: Result<T_Return>
```

#### `#SPECIAL`

Documents a specialized function or method implementation.

The first body part is the primary template signature. Additional body parts describe the specialization mapping.

**Syntax**

    #SPECIAL: <primary_signature>, <specialization_detail>

**Examples**

```cpp
// #SPECIAL: get<T_Value>(const std::string_view), T_Value = std::string
// #SPECIAL: get<T_Value>(const std::string_view), T_Value = std::vector<std::string>
```

## Callable Elements

Callable elements document free functions, member functions, constructors, destructors, and operators.

### Declaration Tags

#### `#FUNCTION`

Declares a free function element.

The first body part is the function signature. The second body part is optional and may describe the function role.

**Syntax**

    #FUNCTION: <function_signature>
    #FUNCTION: <function_signature>, <function_type>

**Examples**

```cpp
// #FUNCTION: main(int, int**)
// #FUNCTION: main, Main function
```

#### `#METHOD`

Declares a member function, constructor, destructor, or operator element.

The first body part is the method signature. The second body part is the method type or role.

**Syntax**

    #METHOD: <method_signature>, <method_type>

**Examples**

```cpp
// #METHOD: Json(const nlohmann::json&), Constructor
// #METHOD: operator bool(), Const Operator
// #METHOD: error(), Const Method
// #METHOD: Error<T_ContextArgs>(const Code, const std::string&), Constructor
```

### Attribute Tags

#### `#PARAM`

Documents a function or method parameter.

The first body part is the parameter declaration or name. The second body part describes the parameter.

**Syntax**

    #PARAM: <parameter>, <description>

**Examples**

```cpp
// #PARAM: const std_fs::path& p_path, Path to load config file from
// #PARAM: p_code, Code to compare error code to
// #PARAM: char** p_argv, Argument array
```

#### `#RETURN`

Documents a return type and return meaning.

The first body part is the return type. The second body part describes the returned value.

**Syntax**

    #RETURN: <return_type>, <description>

**Examples**

```cpp
// #RETURN: int, Exit status
// #RETURN: Result<Json>, Result object containing either the parsed json or error type
// #RETURN: std::string, Constructed error message
```

#### `#THROWS`

Documents an exception type and the condition that causes it.

The first body part is the exception type. The second body part describes when it is thrown.

**Syntax**

    #THROWS: <exception_type>, <condition>

**Examples**

```cpp
// #THROWS: std::bad_variant_access, If result is not a success state
// #THROWS: std::bad_optional_access, If result is not a error state
```

## Declaration State Tags

Declaration state tags document compiler-generated or disabled declarations.

These tags are usually written inline with the declaration.

### `#DEFAULT`

Documents a defaulted declaration.

The first body part is the declaration signature. The second body part is the declaration type or role.

**Syntax**

    #DEFAULT: <signature>, <declaration_type>

**Examples**

```cpp
Json() = default; // #DEFAULT: Json(), Default Constructor
~Error() = default; // #DEFAULT: ~Error(), Destructor
Error& operator=(Error&&) = default; // #DEFAULT: operator=(Error&&), Move Assignment Operator
```

### `#DELETE`

Documents a deleted declaration.

The first body part is the declaration signature. The second body part is the declaration type or role.

**Syntax**

    #DELETE: <signature>, <declaration_type>

**Examples**

```cpp
template<class T_Value> Result<T_Value> get(const std::string_view p_key)const = delete; // #DELETE: get<T_Value>(const std::string_view), Non-specialized method
Logger(const Logger&) = delete; // #DELETE: Logger(const Logger&), Copy Constructor
Logger(Logger&&) = delete; // #DELETE: Logger(Logger&&), Move Constructor
```

## Compatibility Tags And Current Variants

The following spellings are present in the current codebase or may be useful for compatibility, but the canonical standard should prefer the forms above.

### `#RETURNS`

Alias for `#RETURN`.

Prefer `#RETURN` in new documentation.

**Syntax**

    #RETURNS: <return_type>, <description>

**Example**

```cpp
// #RETURNS: Result<ConfigFile>, Loaded ConfigFile on success, Error on failure
```

### `#PARMA`

Observed misspelling of `#PARAM`.

This should be treated as non-standard. Prefer `#PARAM` in new documentation.

**Syntax**

    #PARAM: <parameter>, <description>

**Example**

```cpp
// #PARAM: const T_ContextArgs&... p_contextArgs, Context arguments bundle
```

### Missing Colon On `#DERIVES`

Existing code contains `#DERIVES, ...` in a few places.

The canonical form should use a colon.

**Syntax**

    #DERIVES: <access> <base_type>, <base_description>

**Example**

```cpp
// #DERIVES: public core::Error, Base project error type
```
