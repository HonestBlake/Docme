# Genorator package CMake Lists file

# Genorator package variables
set(SOURCE_FILES ${GENORATOR}/main.cpp 
# ${GENORATOR}/${SOURCE}/helpers.cpp 
# ${GENORATOR}/${SOURCE}/nodes.cpp
 ${GENORATOR}/${SOURCE}/commandLineParser.cpp)

set(HEADER_INCLUDES ${GENORATOR}/${HEADER} ${GENORATOR})

# Add Genorator target
add_executable(Genorator ${SOURCE_FILES} ${COMMON_SOURCE_FILES})
target_include_directories(Genorator PRIVATE ${HEADER_INCLUDES} ${COMMON_HEADER_INCLUDES})
target_link_libraries(Genorator PRIVATE BetterLogger)

# target_compile_options(Genorator PRIVATE -fmodules-ts)
target_compile_definitions(Genorator PRIVATE 
    WT_AUTODOC_DEBUG_TRACING
    # WT_AUTODOC_DEBUG_TRACING_VERBOSE
)
