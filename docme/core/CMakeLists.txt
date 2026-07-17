# CMakeLists.txt for CORE package

# Add nlohmann/json dependency with C++20 module support
set(DEPS_NLOHMANN_JSON_BUILD "${DEPS_BUILD}/nlohmann-json-build")
set(NLOHMANN_JSON_BUILD_MODULES ON CACHE BOOL "" FORCE) # Use modules for nlohmann json

# Module support is currently on nlohmann/json's develop branch, not a stable release.
# Pin the exact commit so normal re-configures do not need to contact GitHub.
# Update the commit below when you intentionally want to refresh this dependency.
set(DOCME_NLOHMANN_JSON_VERSION "develop-2026-06-23")
set(DOCME_NLOHMANN_JSON_COMMIT "25c58ac6bd88ccd55084e341f7ecb6ef88d527af")
fetchcontent_declare(
    nlohmann_json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG ${DOCME_NLOHMANN_JSON_COMMIT} # ${DOCME_NLOHMANN_JSON_VERSION}
    SOURCE_DIR "${DEPS}/nlohmann json"
    BINARY_DIR "${DEPS_NLOHMANN_JSON_BUILD}"
)
fetchcontent_makeavailable(nlohmann_json)
set_target_properties(nlohmann_json_modules PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${DEPS_NLOHMANN_JSON_BUILD}/lib/$<LOWER_CASE:$<CONFIG>>"
    LIBRARY_OUTPUT_DIRECTORY "${DEPS_NLOHMANN_JSON_BUILD}/lib/$<LOWER_CASE:$<CONFIG>>"
    RUNTIME_OUTPUT_DIRECTORY "${DEPS_NLOHMANN_JSON_BUILD}/bin/$<LOWER_CASE:$<CONFIG>>"
)

# Add PureLog dependency
set(PURE_LOG_USE_MODULES ON CACHE BOOL "" FORCE) # Use modules for pure log
set(PURE_LOG_IMPORT_STD OFF CACHE BOOL "" FORCE) # Use modules for pure log

fetchcontent_declare(
    PureLog
    GIT_REPOSITORY https://github.com/HonestBlake/Pure-Log.git
    GIT_TAG v1.1.1
    SOURCE_DIR "${DEPS}/Pure Log"
    BINARY_DIR "${DEPS_BUILD}/pure-log-build"
)
fetchcontent_makeavailable(PureLog)

set(CORE_INCLUDE_DIRS
    ${CORE}
)
set(CORE_SRC_FILES
    "${CORE}/library.cpp"
    "${CORE}/errors.cpp"
    "${CORE}/failure.cpp"
    "${CORE}/json.cpp"
    "${CORE}/logging.cpp"
    "${CORE}/success.cpp"
    "${CORE}/timer.cpp"
    "${CORE}/utils.cpp"
    "${CORE}/warnings.cpp"
)
set(CORE_MOD_FILES
    "${CORE}/core.mpp"
    "${CORE}/library.mpp"
    "${CORE}/errors.mpp"
    "${CORE}/failure.mpp"
    "${CORE}/json.mpp"
    "${CORE}/logging.mpp"
    "${CORE}/result.mpp"
    "${CORE}/success.mpp"
    "${CORE}/timer.mpp"
    "${CORE}/utils.mpp"
    "${CORE}/warnings.mpp"
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
    ${CMAKE_DL_LIBS}
)
set_target_properties(docme_core PROPERTIES
    OUTPUT_NAME "docme-core"
    PREFIX ""
)
if(WIN32)
    set_target_properties(docme_core PROPERTIES SUFFIX ".lib")
endif()
