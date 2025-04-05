# Parser package CMake Lists file

# Parser package variables
set(
    SOURCE_FILES ${PARSER}/main.cpp 
    # ${PARSER}/${SOURCE}/helpers.cpp 
    ${PARSER}/${SOURCE}/nodes.cpp 
    ${PARSER}/${SOURCE}/commandLineParser.cpp
    ${PARSER}/${SOURCE}/docPackets.cpp
    )

set(HEADER_INCLUDES ${PARSER}/${HEADER} ${PARSER})

# Add Genorator target
add_executable(Docme ${SOURCE_FILES} ${COMMON_SOURCE_FILES})
set_target_properties(Docme PROPERTIES OUTPUT_NAME "docme")
target_include_directories(Docme PRIVATE ${HEADER_INCLUDES} ${COMMON_HEADER_INCLUDES})
target_link_libraries(Docme PRIVATE 
    # better_logger::better_logger
    BetterLogger
    nlohmann_json::nlohmann_json
)


# target_compile_options(Genorator PRIVATE -fmodules-ts)
target_compile_definitions(Docme PRIVATE 
    # WT_AUTODOC_DEBUG_TRACING
    WT_AUTODOC_DEBUGGING
    # WT_AUTODOC_DEBUG_TRACING_VERBOSE
)
