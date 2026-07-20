// #FILE: library.cpp, Component Source File
// #BRIEF: Source file for project library component

module;

#include "core.hpp" // #INCLUDE: core.hpp, Package wide header

#ifdef _WIN32
    #include <libloaderapi.h>
#else
    #include <dlfcn.h>
#endif

module docme.core; // #IMPLEMENTS: docme.core:library
import :library;

namespace docme::core{ // #SCOPE: docme::core

// ------------------------------------------------------------------------------
//                              class Library
// ------------------------------------------------------------------------------

// #SCOPE: Library

// #DIV: Public

// ---- Public Special Methods ----

    // #METHOD: Library(Library&&), Move Constructor
    // #BRIEF: Moves native library ownership from another wrapper
    // #PARAM: Library&& p_other, Other dynamic library wrapper
    Library::Library(Library&& p_other)noexcept: m_name(std::move(p_other.m_name)), m_loaded(std::exchange(p_other.m_loaded, false)), m_handle(std::exchange(p_other.m_handle, nullptr)){
        
    } // #END: Library(Library&&)

    // #METHOD: ~Library(), Destructor
    // #BRIEF: Releases loaded native library handle
    Library::~Library()noexcept{
        freeLibrary();
    } // #END: ~Library()

// ---- Public Operators ----

    // #METHOD: operator=(Library&&), Move Assignment Operator
    // #BRIEF: Moves native library ownership from another wrapper
    // #PARAM: Library&& p_other, Other dynamic library wrapper
    // #RETURN: Library&, Reference to this object
    Library& Library::operator=(Library&& p_other) noexcept{
        if (this == &p_other) return *this;

        freeLibrary();

        m_name = std::move(p_other.m_name);
        m_loaded = std::exchange(p_other.m_loaded, false);
        m_handle = std::exchange(p_other.m_handle, nullptr);

        return *this;
    } // #END: operator=(Library&&)


// ---- Public Static Methods ----

    // #METHOD: load(const std_fs::path&), Static Method
    // #BRIEF: Loads a dynamic library from the given file path
    // #NOTE: Returns error code: DOCME_E105
    // #PARAM: const std::string_view p_name, Name of the library
    // #PARAM: const std_fs::path& p_file, Dynamic library file path
    // #RETURN: Result<Library>, Loaded dynamic library or error type
    Result<Library> Library::load(const std::string_view p_name, const std_fs::path& p_file){
        NativeHandle handle = getNativeHandle(p_file);
        if(!handle) return Error(Error::DOCME_E105, std::string(p_name), p_file.string());
        return Library(p_name, handle);
    } // #END: load(const std_fs::path&)


// ---- Public Methods ----

    // #METHOD: freeLibrary(), Instance Method
    // #BRIEF: Releases the loaded dynamic library if present
    void Library::freeLibrary(){
        if(m_handle == nullptr) return;
        #ifdef _WIN32
            FreeLibrary(static_cast<HMODULE>(m_handle));
        #else
            dlclose(m_handle);
        #endif
        m_handle = nullptr;
        m_loaded = false;
    } // #END: freeLibrary()


// #DIV: Private

// ---- Private Special Methods ----

    // #METHOD: Library(NativeHandle), Noexcept Constructor
    // #BRIEF: Constructs a library wrapper from a native handle
    // #PARAM: const std::string_view p_name, Name of the library
    // #PARAM: NativeHandle p_handle, Native dynamic library handle
    Library::Library(const std::string_view p_name, NativeHandle p_handle)noexcept: m_name(p_name), m_handle(p_handle), m_loaded(p_handle){

    } // #END: Library(NativeHandle)

// --- Private Static Methods ---

    // #METHOD: getNativeHandle(), Const Instance Method
    // #BRIEF: Gets the native library handle
    // #RETURN: LibraryHandle, Native library handle
    Library::NativeHandle Library::getNativeHandle(const std_fs::path& p_file){
        #ifdef _WIN32
            return LoadLibraryA(p_file.string().c_str());
        #else
            return dlopen(p_file.c_str(), RTLD_LAZY);
        #endif
    } // #END: getNativeHandle()

    // #METHOD: getNativeFunctionPointer(NativeHandle, const std::string_view), Const Instance Method
    // #BRIEF: Gets the native function pointer from the loaded library
    // #NOTE: Returns error codes: DOCME_E106, DOCME_E107
    // #PARAM: NativeHandle p_handle, Native library handle
    // #PARAM: const std::string_view p_functionName, Exported function name
    // #RETURN: NativeFunctionPointer, Native function pointer or nullptr if not found
    Library::NativeFunctionPointer Library::getNativeFunctionPointer(NativeHandle p_handle, const std::string_view p_functionName){
        #ifdef _WIN32
            return reinterpret_cast<NativeFunctionPointer>(GetProcAddress(static_cast<HMODULE>(p_handle), p_functionName.data()));
        #else
            return reinterpret_cast<NativeFunctionPointer>(dlsym(p_handle, p_functionName.data()));
        #endif
    } // #END: getNativeFunctionPointer(NativeHandle, const std::string_view)

// #END: Library

} // #END: docme::core
