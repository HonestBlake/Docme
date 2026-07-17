# CMakeLists.txt for CDOC language handler package

set(CDOC_INCLUDE_DIRS
    ${CDOC}
)
set(CDOC_SRC_FILES
    "${CDOC}/cdoc.cpp"
    "${CDOC}/handler.cpp"
)
set(CDOC_MOD_FILES
    "${CDOC}/cdoc.mpp"
    "${CDOC}/handler.mpp"
)
set(CDOC_PCH_FILES

)

# PCH not supported with modules on gcc
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set_source_files_properties(${CDOC_SRC_FILES} ${CDOC_MOD_FILES}
        PROPERTIES SKIP_PRECOMPILE_HEADERS ON
    )
endif()

add_library(cdoc SHARED)
target_sources(cdoc PRIVATE ${CDOC_SRC_FILES}
    PUBLIC
    FILE_SET cxx_modules
    TYPE CXX_MODULES
    BASE_DIRS ${CDOC}
    FILES ${CDOC_MOD_FILES}
)
target_include_directories(cdoc PRIVATE ${PLUGINS_INCLUDE_DIRS} ${CDOC_INCLUDE_DIRS})
if(NOT DOCME_CLANGD_BUILD)
    target_precompile_headers(cdoc PRIVATE ${PLUGINS_PCH_FILES} ${CDOC_PCH_FILES})
endif()
set_target_properties(cdoc PROPERTIES
    OUTPUT_NAME "cdoc"
    PREFIX ""
    RUNTIME_OUTPUT_DIRECTORY "${BIN_RELEASE}"
    LIBRARY_OUTPUT_DIRECTORY "${BIN_RELEASE}"
    ARCHIVE_OUTPUT_DIRECTORY "${LIB_RELEASE}"
)