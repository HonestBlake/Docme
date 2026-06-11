# CMakeLists.txt for CORE package

# Add nlohmann/json dependency with C++20 module support
set(DEPS_NLOHMANN_JSON "${DEPS}/nlohmann json")
set(NLOHMANN_JSON_BUILD_MODULES ON CACHE BOOL "" FORCE) # Use modules for nlohmann json
fetchcontent_declare(
    nlohmann_json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG develop # module support is currently on develop, not v3.12.0
    SOURCE_DIR "${DEPS_NLOHMANN_JSON}"
    BINARY_DIR "${DEPS_NLOHMANN_JSON}/build"
)
fetchcontent_makeavailable(nlohmann_json)
set_target_properties(nlohmann_json_modules PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${DEPS_NLOHMANN_JSON_BUILD}/lib/$<LOWER_CASE:$<CONFIG>>"
    LIBRARY_OUTPUT_DIRECTORY "${DEPS_NLOHMANN_JSON_BUILD}/lib/$<LOWER_CASE:$<CONFIG>>"
    RUNTIME_OUTPUT_DIRECTORY "${DEPS_NLOHMANN_JSON_BUILD}/bin/$<LOWER_CASE:$<CONFIG>>"
)

# Add PureLog dependency
set(DEPS_PURELOG "${DEPS}/Pure Log")
set(PURE_LOG_USE_MODULES ON CACHE BOOL "" FORCE) # Use modules for pure log
fetchcontent_declare(
    PureLog
    GIT_REPOSITORY https://github.com/HonestBlake/Pure-Log.git
    GIT_TAG v1.1.0
    SOURCE_DIR "${DEPS_PURELOG}"
    BINARY_DIR "${DEPS_PURELOG}/build"
)
fetchcontent_makeavailable(PureLog)

set(CORE_INCLUDE_DIRS
    ${CORE}
)
set(CORE_SRC_FILES
    "${CORE}/errors.cpp"
    "${CORE}/json.cpp"
    "${CORE}/logging.cpp"
)
set(CORE_MOD_FILES
    "${CORE}/core.mpp"
    "${CORE}/errors.mpp"
    "${CORE}/json.mpp"
    "${CORE}/logging.mpp"
    "${CORE}/result.mpp"
)
set(CORE_PCH_FILES

)

# PCH not supported with modules on gcc
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set_source_files_properties(${CORE_SRC_FILES} ${DOCME_MOD_FILES} ${CORE_MOD_FILES}
        PROPERTIES SKIP_PRECOMPILE_HEADERS ON
    )
endif()

add_library(docme_core STATIC)
target_sources(docme_core PRIVATE ${CORE_SRC_FILES}
    PUBLIC
    FILE_SET cxx_modules
    TYPE CXX_MODULES
    BASE_DIRS ${CORE}
    FILES ${CORE_MOD_FILES}
)
target_include_directories(docme_core PRIVATE ${DOCME_INCLUDE_DIRS} ${CORE_INCLUDE_DIRS})
if(NOT DOCME_CLANGD_BUILD)
    target_precompile_headers(docme_core PRIVATE ${DOCME_PCH_FILES} ${CORE_PCH_FILES})
endif()
target_link_libraries(docme_core PRIVATE 
    PureLog
    nlohmann_json_modules
)
set_target_properties(docme_core PROPERTIES
    OUTPUT_NAME "docme-core"
    PREFIX ""
    SUFFIX ".lib"
)
