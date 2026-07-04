# CMakeLists.txt for CLI package

# Add Simple CLI dependency
set(SIMPLE_CLI_USE_MODULES ON CACHE BOOL "" FORCE) # Use modules for simple cli
fetchcontent_declare(
    SimpleCLI
    GIT_REPOSITORY https://github.com/HonestBlake/Simple-CLI.git
    GIT_TAG v1.2.1
    SOURCE_DIR "${DEPS}/Simple CLI"
    BINARY_DIR "${DEPS_BUILD}/simple-cli-build"
)
fetchcontent_makeavailable(SimpleCLI)

set(CLI_INCLUDE_DIRS
    ${CLI}
)
set(CLI_SRC_FILES
    "${CLI}/application.cpp"
)
set(CLI_MOD_FILES
    "${CLI}/cli.mpp"
    "${CLI}/application.mpp"
)
set(CLI_PCH_FILES

)

# PCH not supported with modules on gcc
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set_source_files_properties(${CLI_SRC_FILES} ${DOCME_MOD_FILES} ${CLI_MOD_FILES}
        PROPERTIES SKIP_PRECOMPILE_HEADERS ON
    )
endif()

add_library(docme_cli STATIC)
target_sources(docme_cli PRIVATE ${CLI_SRC_FILES}
    PUBLIC
    FILE_SET cxx_modules
    TYPE CXX_MODULES
    BASE_DIRS ${CLI}
    FILES ${CLI_MOD_FILES}
)
target_include_directories(docme_cli PRIVATE ${DOCME_INCLUDE_DIRS} ${CLI_INCLUDE_DIRS})
if(NOT DOCME_CLANGD_BUILD)
    target_precompile_headers(docme_cli PRIVATE ${DOCME_PCH_FILES} ${CLI_PCH_FILES})
endif()
target_link_libraries(docme_cli PUBLIC 
    docme_core 
    docme_engine
    SimpleCLI
)
set_target_properties(docme_cli PROPERTIES
    OUTPUT_NAME "docme-cli"
    PREFIX ""
    SUFFIX ".lib"
)
