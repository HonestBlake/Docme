# CMakeLists.txt for PLUGIN package

set(PLUGIN_INCLUDE_DIRS
    ${PLUGIN}
)
set(PLUGIN_SRC_FILES
    "${PLUGIN}/languageHandler.cpp"
)
set(PLUGIN_MOD_FILES
    "${PLUGIN}/plugin.mpp"
    "${PLUGIN}/languageHandler.mpp"
)
set(PLUGIN_PCH_FILES

)

# PCH not supported with modules on gcc
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set_source_files_properties(${DOCME_MOD_FILES} ${PLUGIN_SRC_FILES} ${PLUGIN_MOD_FILES}
        PROPERTIES SKIP_PRECOMPILE_HEADERS ON
    )
endif()

add_library(docme_plugin STATIC)
target_sources(docme_plugin PRIVATE ${PLUGIN_SRC_FILES}
    PUBLIC
    FILE_SET cxx_modules
    TYPE CXX_MODULES
    BASE_DIRS ${PLUGIN}
    FILES ${PLUGIN_MOD_FILES}
)
target_include_directories(docme_plugin PRIVATE ${DOCME_INCLUDE_DIRS} ${PLUGIN_INCLUDE_DIRS})
if(NOT DOCME_CLANGD_BUILD)
    target_precompile_headers(docme_plugin PRIVATE ${DOCME_PCH_FILES} ${PLUGIN_PCH_FILES})
endif()
set_target_properties(docme_plugin PROPERTIES
    OUTPUT_NAME "docme-plugin"
    PREFIX ""
)
if(WIN32)
    set_target_properties(docme_plugin PROPERTIES SUFFIX ".lib")
endif()
