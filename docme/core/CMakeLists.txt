# CMakeLists.txt for CORE package

# Add nlohmann/json dependency with C++20 module support
set(DOCME_NLOHMANN_JSON_REPOSITORY https://github.com/nlohmann/json.git)
set(DOCME_NLOHMANN_JSON_TAG develop)
set(DOCME_NLOHMANN_JSON_SOURCE_DIR "${DEPS}/nlohmann_json")
set(DOCME_NLOHMANN_JSON_BUILD_DIR "${DEPS_BUILD}/nlohmann_json/nlohmann-json-build")
set(DOCME_NLOHMANN_JSON_FETCHCONTENT_DIR "${DEPS_BUILD}/nlohmann_json/fetchcontent")
set(DOCME_NLOHMANN_JSON_STAMP_FILE "${DEPS_STAMPS}/nlohmann_json-source.stamp")
set(DOCME_NLOHMANN_JSON_STAMP_VALUE "GIT_REPOSITORY=${DOCME_NLOHMANN_JSON_REPOSITORY}\nGIT_TAG=${DOCME_NLOHMANN_JSON_TAG}\n")
set(NLOHMANN_JSON_BUILD_MODULES ON CACHE BOOL "" FORCE)
set(JSON_BuildTests OFF CACHE INTERNAL "")
set(JSON_Install OFF CACHE INTERNAL "")
FetchContent_Declare(
    nlohmann_json
    GIT_REPOSITORY ${DOCME_NLOHMANN_JSON_REPOSITORY}
    GIT_TAG ${DOCME_NLOHMANN_JSON_TAG} # module support is currently on develop, not v3.12.0
    SOURCE_DIR "${DOCME_NLOHMANN_JSON_SOURCE_DIR}"
    BINARY_DIR "${DOCME_NLOHMANN_JSON_BUILD_DIR}"
)
docme_fetchcontent_use_existing_if_current(
    nlohmann_json
    "${DOCME_NLOHMANN_JSON_SOURCE_DIR}"
    "${DOCME_NLOHMANN_JSON_STAMP_FILE}"
    "${DOCME_NLOHMANN_JSON_STAMP_VALUE}"
)
docme_fetchcontent_make_available(nlohmann_json "${DOCME_NLOHMANN_JSON_FETCHCONTENT_DIR}")
docme_fetchcontent_write_stamp("${DOCME_NLOHMANN_JSON_STAMP_FILE}" "${DOCME_NLOHMANN_JSON_STAMP_VALUE}")
docme_set_external_target_output(nlohmann_json_modules "${DOCME_NLOHMANN_JSON_BUILD_DIR}")

# Add PureLog dependency
set(DOCME_PURELOG_REPOSITORY https://github.com/HonestBlake/Pure-Log.git)
set(DOCME_PURELOG_TAG v1.1.0)
set(DOCME_PURELOG_SOURCE_DIR "${DEPS}/PureLog")
set(DOCME_PURELOG_BUILD_DIR "${DEPS_BUILD}/PureLog/purelog-build")
set(DOCME_PURELOG_FETCHCONTENT_DIR "${DEPS_BUILD}/PureLog/fetchcontent")
set(DOCME_PURELOG_STAMP_FILE "${DEPS_STAMPS}/PureLog-source.stamp")
set(DOCME_PURELOG_STAMP_VALUE "GIT_REPOSITORY=${DOCME_PURELOG_REPOSITORY}\nGIT_TAG=${DOCME_PURELOG_TAG}\n")
FetchContent_Declare(
    PureLog
    GIT_REPOSITORY ${DOCME_PURELOG_REPOSITORY}
    GIT_TAG ${DOCME_PURELOG_TAG}
    SOURCE_DIR "${DOCME_PURELOG_SOURCE_DIR}"
    BINARY_DIR "${DOCME_PURELOG_BUILD_DIR}"
)
set(PURE_LOG_USE_MODULES ON CACHE BOOL "" FORCE)
docme_fetchcontent_use_existing_if_current(
    PureLog
    "${DOCME_PURELOG_SOURCE_DIR}"
    "${DOCME_PURELOG_STAMP_FILE}"
    "${DOCME_PURELOG_STAMP_VALUE}"
)
docme_fetchcontent_make_available(PureLog "${DOCME_PURELOG_FETCHCONTENT_DIR}")
docme_fetchcontent_write_stamp("${DOCME_PURELOG_STAMP_FILE}" "${DOCME_PURELOG_STAMP_VALUE}")

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
)
set(CORE_PCH_FILES

)
set_source_files_properties(${CORE_SRC_FILES} ${CORE_MOD_FILES}
    PROPERTIES SKIP_PRECOMPILE_HEADERS ON
)

add_library(docme_core STATIC)
target_sources(docme_core PRIVATE ${CORE_SRC_FILES}
    PUBLIC
    FILE_SET cxx_modules
    TYPE CXX_MODULES
    BASE_DIRS ${CORE}
    FILES ${CORE_MOD_FILES}
)
target_include_directories(docme_core PUBLIC ${DOCME_INCLUDE_DIRS} ${CORE_INCLUDE_DIRS})
target_precompile_headers(docme_core PRIVATE ${DOCME_PCH_FILES} ${CORE_PCH_FILES})
target_link_libraries(docme_core PRIVATE 
    PureLog
    nlohmann_json_modules
)
set_target_properties(docme_core PROPERTIES
    OUTPUT_NAME "docme-core"
    PREFIX ""
    SUFFIX ".lib"
)
