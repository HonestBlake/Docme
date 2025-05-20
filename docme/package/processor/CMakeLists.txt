# Processor package CMake Lists file

# Processor package variables
set(
    SOURCE_FILES ${PROCESSOR}/main.cpp 
    # ${PARSER}/${SOURCE}/helpers.cpp 
    # ${PROCESSOR}/${SOURCE}/nodes.cpp 
    ${PROCESSOR}/${SOURCE}/commandLineParser.cpp
    ${PROCESSOR}/${SOURCE}/docPackets.cpp 
    ${PROCESSOR}/${SOURCE}/docmeInfo.cpp
    ${PROCESSOR}/${SOURCE}/parser.cpp
    ${PROCESSOR}/${SOURCE}/generator.cpp
)

set(HEADER_INCLUDES ${PROCESSOR}/${HEADER} ${PROCESSOR})

# Add Processor target
add_executable(Processor ${SOURCE_FILES} ${COMMON_SOURCE_FILES})
set_target_properties(Processor PROPERTIES OUTPUT_NAME "docme")
target_include_directories(Processor PRIVATE ${HEADER_INCLUDES} ${COMMON_HEADER_INCLUDES})
target_link_libraries(Processor PRIVATE 
    # better_logger::better_logger
    BetterLogger
    nlohmann_json::nlohmann_json
)


# target_compile_options(Genorator PRIVATE -fmodules-ts)
target_compile_definitions(Processor PRIVATE 
    # WT_DOCME_DEBUG_TRACING
    WT_DOCME_DEBUGGING
    # WT_DOCME_DEBUG_TRACING_VERBOSE
)
