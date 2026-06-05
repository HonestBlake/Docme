# CMakeLists.txt for CLI package

# Add Simple CLI dependency
set(DOCME_SIMPLECLI_REPOSITORY https://github.com/HonestBlake/Simple-CLI.git)
set(DOCME_SIMPLECLI_TAG v1.1.0)
set(DOCME_SIMPLECLI_SOURCE_DIR "${DEPS}/SimpleCLI")
set(DOCME_SIMPLECLI_BUILD_DIR "${DEPS_BUILD}/SimpleCLI/simplecli-build")
set(DOCME_SIMPLECLI_FETCHCONTENT_DIR "${DEPS_BUILD}/SimpleCLI/fetchcontent")
set(DOCME_SIMPLECLI_STAMP_FILE "${DEPS_STAMPS}/SimpleCLI-source.stamp")
set(DOCME_SIMPLECLI_STAMP_VALUE "GIT_REPOSITORY=${DOCME_SIMPLECLI_REPOSITORY}\nGIT_TAG=${DOCME_SIMPLECLI_TAG}\n")
FetchContent_Declare(
    SimpleCLI
    GIT_REPOSITORY ${DOCME_SIMPLECLI_REPOSITORY}
    GIT_TAG ${DOCME_SIMPLECLI_TAG}
    SOURCE_DIR "${DOCME_SIMPLECLI_SOURCE_DIR}"
    BINARY_DIR "${DOCME_SIMPLECLI_BUILD_DIR}"
)
set(SIMPLE_CLI_USE_MODULES ON CACHE BOOL "" FORCE)
docme_fetchcontent_use_existing_if_current(
    SimpleCLI
    "${DOCME_SIMPLECLI_SOURCE_DIR}"
    "${DOCME_SIMPLECLI_STAMP_FILE}"
    "${DOCME_SIMPLECLI_STAMP_VALUE}"
)
docme_fetchcontent_make_available(SimpleCLI "${DOCME_SIMPLECLI_FETCHCONTENT_DIR}")
docme_fetchcontent_write_stamp("${DOCME_SIMPLECLI_STAMP_FILE}" "${DOCME_SIMPLECLI_STAMP_VALUE}")

set(CLI_INCLUDE_DIRS
    ${CLI}
)
set(CLI_SRC_FILES
)
set(CLI_MOD_FILES
    "${CLI}/cli.mpp"
)
set(CLI_PCH_FILES

)
set_source_files_properties(${CLI_SRC_FILES} ${CLI_MOD_FILES}
    PROPERTIES SKIP_PRECOMPILE_HEADERS ON
)

add_library(docme_cli STATIC)
target_sources(docme_cli PRIVATE ${CLI_SRC_FILES}
    PUBLIC
    FILE_SET cxx_modules
    TYPE CXX_MODULES
    BASE_DIRS ${CLI}
    FILES ${CLI_MOD_FILES}
)
target_include_directories(docme_cli PUBLIC ${DOCME_INCLUDE_DIRS} ${CLI_INCLUDE_DIRS})
target_precompile_headers(docme_cli PRIVATE ${DOCME_PCH_FILES} ${CLI_PCH_FILES})
target_link_libraries(docme_cli PUBLIC 
    docme_core 
    docme_engine
)
set_target_properties(docme_cli PROPERTIES
    OUTPUT_NAME "docme-cli"
    PREFIX ""
    SUFFIX ".lib"
)
