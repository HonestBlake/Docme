# CMakeLists.txt for CLI package

set(CLI_INCLUDE_DIRS
    ${CLI}
)
set(CLI_SRC_FILES
    "${CLI}/cli.cpp"
)
set(CLI_MOD_FILES
    "${CLI}/cli.mpp"
)
set(CLI_PCH_FILES

)
set_source_files_properties(${DOCME_SRC_FILES} ${DOCME_MOD_FILES} ${CLI_MOD_FILES}
    PROPERTIES SKIP_PRECOMPILE_HEADERS ON
)

add_executable(docme_cli)
target_sources(docme_cli PRIVATE ${DOCME_SRC_FILES} ${CLI_SRC_FILES}
    PRIVATE
    FILE_SET cxx_modules
    TYPE CXX_MODULES
    BASE_DIRS ${DOCME}
    FILES ${DOCME_MOD_FILES} ${CLI_MOD_FILES}
)
target_include_directories(docme_cli PUBLIC ${DOCME_INCLUDE_DIRS} ${CLI_INCLUDE_DIRS})
target_precompile_headers(docme_cli PRIVATE ${DOCME_PCH_FILES} ${CLI_PCH_FILES})
set_target_properties(docme_cli PROPERTIES
    OUTPUT_NAME "docme"
    PREFIX ""
    SUFFIX ".exe"
)
