# CMakeLists.txt for CORE package

set(CORE_INCLUDE_DIRS
    ${CORE}
)
set(CORE_SRC_FILES

)
set(CORE_MOD_FILES
    "${CORE}/core.mpp"
)
set(CORE_PCH_FILES

)
set_source_files_properties(${DOCME_SRC_FILES} ${DOCME_MOD_FILES} ${CORE_MOD_FILES}
    PROPERTIES SKIP_PRECOMPILE_HEADERS ON
)

add_library(docme_core)
target_sources(docme_core PRIVATE ${DOCME_SRC_FILES} ${CORE_SRC_FILES}
    PUBLIC
    FILE_SET cxx_modules
    TYPE CXX_MODULES
    BASE_DIRS ${DOCME}
    FILES ${DOCME_MOD_FILES} ${CORE_MOD_FILES}
)
target_include_directories(docme_core PUBLIC ${DOCME_INCLUDE_DIRS} ${CORE_INCLUDE_DIRS})
target_precompile_headers(docme_core PRIVATE ${DOCME_PCH_FILES} ${CORE_PCH_FILES})
set_target_properties(docme_core PROPERTIES
    OUTPUT_NAME "docme-core"
    PREFIX ""
    SUFFIX ".lib"
)
