# CMakeLists.txt for ENGINE package

set(ENGINE_INCLUDE_DIRS
    ${ENGINE}
)
set(ENGINE_SRC_FILES
    "${ENGINE}/configFile.cpp"
)
set(ENGINE_MOD_FILES
    "${ENGINE}/engine.mpp"
    "${ENGINE}/configFile.mpp"
)
set(ENGINE_PCH_FILES

)
set_source_files_properties(${DOCME_SRC_FILES} ${DOCME_MOD_FILES} ${ENGINE_MOD_FILES} ${ENGINE_SRC_FILES}
    PROPERTIES SKIP_PRECOMPILE_HEADERS ON
)

add_library(docme_engine)
target_sources(docme_engine PRIVATE ${DOCME_SRC_FILES} ${ENGINE_SRC_FILES}
    PUBLIC
    FILE_SET cxx_modules
    TYPE CXX_MODULES
    BASE_DIRS ${DOCME}
    FILES ${DOCME_MOD_FILES} ${ENGINE_MOD_FILES}
)
target_include_directories(docme_engine PUBLIC ${DOCME_INCLUDE_DIRS} ${ENGINE_INCLUDE_DIRS})
target_precompile_headers(docme_engine PRIVATE ${DOCME_PCH_FILES} ${ENGINE_PCH_FILES})
set_target_properties(docme_engine PROPERTIES
    OUTPUT_NAME "docme-engine"
    PREFIX ""
    SUFFIX ".lib"
)
