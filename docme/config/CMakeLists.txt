# CMakeLists.txt for CONFIG package

set(CONFIG_INCLUDE_DIRS
    ${CONFIG}
)
set(CONFIG_SRC_FILES
    "${CONFIG}/errors.cpp"
    "${CONFIG}/file.cpp"
    "${CONFIG}/settings.cpp"
    "${CONFIG}/utils.cpp"
    "${CONFIG}/warnings.cpp"
)
set(CONFIG_MOD_FILES
    "${CONFIG}/config.mpp"
    "${CONFIG}/errors.mpp"
    "${CONFIG}/schema.mpp"
    "${CONFIG}/file.mpp"
    "${CONFIG}/options.mpp"
    "${CONFIG}/settings.mpp"
    "${CONFIG}/utils.mpp"
    "${CONFIG}/warnings.mpp"
)
set(CONFIG_PCH_FILES

)

# PCH not supported with modules on gcc
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set_source_files_properties(${CONFIG_SRC_FILES} ${DOCME_MOD_FILES} ${CONFIG_MOD_FILES}
        PROPERTIES SKIP_PRECOMPILE_HEADERS ON
    )
endif()

add_library(docme_config STATIC)
target_sources(docme_config PRIVATE ${CONFIG_SRC_FILES}
    PUBLIC
    FILE_SET cxx_modules
    TYPE CXX_MODULES
    BASE_DIRS ${CONFIG}
    FILES ${CONFIG_MOD_FILES}
)
target_include_directories(docme_config PRIVATE ${DOCME_INCLUDE_DIRS} ${CONFIG_INCLUDE_DIRS})
if(NOT DOCME_CLANGD_BUILD)
    target_precompile_headers(docme_config PRIVATE ${DOCME_PCH_FILES} ${CONFIG_PCH_FILES})
endif()
target_link_libraries(docme_config PRIVATE
    docme_core
)
set_target_properties(docme_config PROPERTIES
    OUTPUT_NAME "docme-config"
    PREFIX ""
)
if(WIN32)
    set_target_properties(docme_config PROPERTIES SUFFIX ".lib")
endif()
