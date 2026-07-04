# CMakeLists.txt for ENGINE package

# Add cpplocate dependency
set(CMAKE_POLICY_VERSION_MINIMUM 3.5) # cpplocate uses older cmake
set(BUILD_SHARED_LIBS OFF CACHE BOOL "Build shared libraries" FORCE) # Make cpplocate build a static lib
fetchcontent_declare(
    cpplocate
    GIT_REPOSITORY https://github.com/cginternals/cpplocate.git
    GIT_TAG v2.3.0
    SOURCE_DIR "${DEPS}/cpplocate"
    BINARY_DIR "${DEPS_BUILD}/cpplocate-build"
)
fetchcontent_makeavailable(cpplocate)

set(ENGINE_INCLUDE_DIRS
    ${ENGINE}
)
set(ENGINE_SRC_FILES
    "${ENGINE}/configFile.cpp"
    "${ENGINE}/commands.cpp"
    "${ENGINE}/options.cpp"
    "${ENGINE}/settings.cpp"
)
set(ENGINE_MOD_FILES
    "${ENGINE}/engine.mpp"
    "${ENGINE}/configFile.mpp"
    "${ENGINE}/commands.mpp"
    "${ENGINE}/options.mpp"
    "${ENGINE}/settings.mpp"
)
set(ENGINE_PCH_FILES

)

# PCH not supported with modules on gcc
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set_source_files_properties(${ENGINE_SRC_FILES} ${DOCME_MOD_FILES} ${ENGINE_MOD_FILES}
        PROPERTIES SKIP_PRECOMPILE_HEADERS ON
    )
endif()

add_library(docme_engine STATIC)
target_sources(docme_engine PRIVATE ${ENGINE_SRC_FILES}
    PUBLIC
    FILE_SET cxx_modules
    TYPE CXX_MODULES
    BASE_DIRS ${ENGINE}
    FILES ${ENGINE_MOD_FILES}
)
target_include_directories(docme_engine PRIVATE ${DOCME_INCLUDE_DIRS} ${ENGINE_INCLUDE_DIRS})
if(NOT DOCME_CLANGD_BUILD)
    target_precompile_headers(docme_engine PRIVATE ${DOCME_PCH_FILES} ${ENGINE_PCH_FILES})
endif()
target_link_libraries(docme_engine PRIVATE
    docme_core
    cpplocate::cpplocate
)
set_target_properties(docme_engine PROPERTIES
    OUTPUT_NAME "docme-engine"
    PREFIX ""
    SUFFIX ".lib"
)