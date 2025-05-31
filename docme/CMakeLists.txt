# Docme package cmake Lists file

# Package variables
set(SOURCE_FILES 
    "${DOCME}/main.cpp"
    "${DOCME}/${SOURCE}/debugging.cpp"
    "${DOCME}/${SOURCE}/jsonTools.cpp"
    "${DOCME}/${SOURCE}/nodes.cpp"
    "${DOCME}/${SOURCE}/packets.cpp"
    "${DOCME}/${SOURCE}/commandLine.cpp"
    # "${DOCME}/${SOURCE}/docmeInfo.cpp"
    "${DOCME}/${SOURCE}/parser.cpp"
    "${DOCME}/${SOURCE}/generator.cpp"
)
set(HEADER_DIRECTORIES 
    "${DOCME}/${HEADER}"
    "${DOCME}/${SOURCE}" 
    "${DOCME}"
)

# Add the nlohmann_json library to the project
set(FETCHCONTENT_BASE_DIR "${DOCME}/${LIBRARY}/nlohmann_json")
FetchContent_Declare(
    nlohmann_json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG v3.12.0
)
FetchContent_MakeAvailable(nlohmann_json)

# Add the BetterDynamicLibraries library to the project
set(FETCHCONTENT_BASE_DIR "${DOCME}/${LIBRARY}/BetterDynamicLibraries")
FetchContent_Declare(
    BetterDynamicLibraries
    GIT_REPOSITORY https://github.com/HonestBlake/Better-Dynamic-Libraries.git
    GIT_TAG v1.1.2
)
FetchContent_MakeAvailable(BetterDynamicLibraries)

# Add the BetterLogger library to the project
set(FETCHCONTENT_BASE_DIR "${DOCME}/${LIBRARY}/BetterLogger")
FetchContent_Declare(
    BetterLogger
    GIT_REPOSITORY https://github.com/HonestBlake/Better-Logger.git
    GIT_TAG v1.0.3
)
FetchContent_MakeAvailable(BetterLogger)

# Add the Docme executable to the project
add_executable(Docme ${SOURCE_FILES})
set_target_properties(Docme PROPERTIES OUTPUT_NAME "docme")
target_include_directories(Docme PRIVATE ${HEADER_DIRECTORIES})
target_link_libraries(Docme PRIVATE 
    BetterLogger
    nlohmann_json::nlohmann_json
    BetterDynamicLibraries
)
target_compile_definitions(Docme PRIVATE 
    # WT_DOCME_DEBUG_TRACING
    WT_DOCME_DEBUGGING
    # WT_DOCME_DEBUG_TRACING_VERBOSE
)