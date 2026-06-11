# CMakeLists.txt for GENERATOR package

set(GENERATOR_INCLUDE_DIRS
    ${GENERATOR}
)
set(GENERATOR_SRC_FILES

)
set(GENERATOR_MOD_FILES
    "${GENERATOR}/generator.mpp"
)
set(GENERATOR_PCH_FILES

)

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set_source_files_properties(${GENERATOR_SRC_FILES} ${DOCME_MOD_FILES} ${GENERATOR_MOD_FILES}
        PROPERTIES SKIP_PRECOMPILE_HEADERS ON
    )
endif()

add_library(docme_generator)
target_sources(docme_generator PRIVATE ${DOCME_SRC_FILES} ${GENERATOR_SRC_FILES}
    PUBLIC
    FILE_SET cxx_modules
    TYPE CXX_MODULES
    BASE_DIRS ${DOCME}
    FILES ${DOCME_MOD_FILES} ${GENERATOR_MOD_FILES}
)
target_include_directories(docme_generator PUBLIC ${DOCME_INCLUDE_DIRS} ${GENERATOR_INCLUDE_DIRS})
if(NOT DOCME_CLANGD_BUILD)
    target_precompile_headers(docme_generator PRIVATE ${DOCME_PCH_FILES} ${GENERATOR_PCH_FILES})
endif()
target_link_libraries(docme_cli PRIVATE nlohmann_json_modules)
set_target_properties(docme_generator PROPERTIES
    OUTPUT_NAME "docme-generator"
    PREFIX ""
    SUFFIX ".lib"
)
