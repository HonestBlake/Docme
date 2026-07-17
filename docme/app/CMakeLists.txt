# CMakeLists.txt for APP package

set(APP_INCLUDE_DIRS
    ${APP}
)
set(APP_SRC_FILES
    "${APP}/commands.cpp"
)
set(APP_MOD_FILES
    "${APP}/app.mpp"
    "${APP}/commands.mpp"
)
set(APP_PCH_FILES

)

# PCH not supported with modules on gcc
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set_source_files_properties(${APP_SRC_FILES} ${DOCME_MOD_FILES} ${APP_MOD_FILES}
        PROPERTIES SKIP_PRECOMPILE_HEADERS ON
    )
endif()

add_library(docme_app STATIC)
target_sources(docme_app PRIVATE ${APP_SRC_FILES}
    PUBLIC
    FILE_SET cxx_modules
    TYPE CXX_MODULES
    BASE_DIRS ${APP}
    FILES ${APP_MOD_FILES}
)
target_include_directories(docme_app PRIVATE ${DOCME_INCLUDE_DIRS} ${APP_INCLUDE_DIRS})
if(NOT DOCME_CLANGD_BUILD)
    target_precompile_headers(docme_app PRIVATE ${DOCME_PCH_FILES} ${APP_PCH_FILES})
endif()
target_link_libraries(docme_app PRIVATE
    docme_core
    docme_config
    docme_generator
)
set_target_properties(docme_app PROPERTIES
    OUTPUT_NAME "docme-app"
    PREFIX ""
)
if(WIN32)
    set_target_properties(docme_app PROPERTIES SUFFIX ".lib")
endif()
