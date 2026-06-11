# CMakeLists.txt for docme base

# Package dirs
set(CLI "${DOCME}/cli")
set(GUI "${DOCME}/gui")
set(CORE "${DOCME}/core")
set(ENGINE "${DOCME}/engine")
set(GENERATOR "${DOCME}/generator")

# Project files
set(DOCME_INCLUDE_DIRS
    ${DOCME}
)
set(DOCME_SRC_FILES
    "${DOCME}/docme.cpp"
)
set(DOCME_MOD_FILES
    "${DOCME}/docme.mpp"
)
set(DOCME_PCH_FILES
    "${DOCME}/std.hpp"
)

# PCH not supported with modules on gcc
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set_source_files_properties(${DOCME_MOD_FILES}
        PROPERTIES SKIP_PRECOMPILE_HEADERS ON
    )
endif()

# Add package subdirectories
add_subdirectory(${CLI})
# add_subdirectory(${GUI})
add_subdirectory(${CORE})
add_subdirectory(${ENGINE})
# add_subdirectory(${GENERATOR})

add_executable(docme)
target_sources(docme PRIVATE ${DOCME_SRC_FILES}
    PRIVATE
    FILE_SET cxx_modules
    TYPE CXX_MODULES
    BASE_DIRS ${DOCME}
    FILES ${DOCME_MOD_FILES}
)
target_include_directories(docme PRIVATE ${DOCME_INCLUDE_DIRS})
if(NOT DOCME_CLANGD_BUILD)
    target_precompile_headers(docme PRIVATE ${DOCME_PCH_FILES})
endif()
target_link_libraries(docme PRIVATE 
    docme_cli 
)
set_target_properties(docme PROPERTIES
    OUTPUT_NAME "docme"
    PREFIX ""
    SUFFIX ".exe"
)
