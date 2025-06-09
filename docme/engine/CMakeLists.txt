# Docme package cmake Lists file

# Package variables
set(ENGINE_SOURCE_FILES 
    # "${DOCME_ENGINE}/${SOURCE}/nodes.cpp"
    "${ENGINE}/${SOURCE}/packets.cpp"
    "${ENGINE}/${SOURCE}/parser.cpp"
    "${ENGINE}/${SOURCE}/generator.cpp"
    "${ENGINE}/${SOURCE}/docmeEngine.cpp"
    "${ENGINE}/${SOURCE}/commandLine.cpp"
)
set(ENGINE_HEADER_DIRECTORIES 
    "${ENGINE}"
)

# Add the nlohmann_json library to the project
set(FETCHCONTENT_BASE_DIR "${LIB}/nlohmann_json")
FetchContent_Declare(
    nlohmann_json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG v3.12.0
)
FetchContent_MakeAvailable(nlohmann_json)

# Add the BetterDynamicLibraries library to the project
set(FETCHCONTENT_BASE_DIR "${LIB}/BetterDynamicLibraries")
FetchContent_Declare(
    BetterDynamicLibraries
    GIT_REPOSITORY https://github.com/HonestBlake/Better-Dynamic-Libraries.git
    GIT_TAG v1.1.2
)
FetchContent_MakeAvailable(BetterDynamicLibraries)

# Add the BetterLogger library to the project
set(FETCHCONTENT_BASE_DIR "${LIB}/BetterLogger")
FetchContent_Declare(
    BetterLogger
    GIT_REPOSITORY https://github.com/HonestBlake/Better-Logger.git
    GIT_TAG v1.0.4
)
FetchContent_MakeAvailable(BetterLogger)

# Add the GoogleTest library to the project
set(FETCHCONTENT_BASE_DIR "${LIB}/GoogleTest")
FetchContent_Declare(
  GoogleTest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.17.0
)
FetchContent_MakeAvailable(GoogleTest)

if(BUILD_TESTING)
    enable_testing()
    set(TEST_FILES
        "${ENGINE}/${TEST}/commandLine.cpp"
    )
    add_executable(DocmeTest 
        ${TEST_FILES} 
        ${SOURCE_FILES}
        "${ENGINE}/${SOURCE}/packets.cpp"
        "${ENGINE}/${SOURCE}/commandLine.cpp"
        "${ENGINE}/${SOURCE}/parser.cpp"
    )
    set_target_properties(DocmeTest PROPERTIES OUTPUT_NAME "docme-test")
    target_include_directories(DocmeTest PRIVATE ${HEADER_DIRECTORIES} ${ENGINE_HEADER_DIRECTORIES})
    target_link_libraries(DocmeTest PRIVATE 
        BetterLogger
        nlohmann_json::nlohmann_json
        BetterDynamicLibraries
        GTest::gtest_main
    )
    include(GoogleTest)
    gtest_discover_tests(DocmeTest
    EXTRA_ARGS
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    )
endif()


# Add the Docme executable to the project
add_executable(DocmeEngine 
    "${ENGINE}/main.cpp" 
    ${ENGINE_SOURCE_FILES}
    ${SOURCE_FILES}
)
target_include_directories(DocmeEngine PRIVATE 
    ${HEADER_DIRECTORIES} 
    ${ENGINE_HEADER_DIRECTORIES}
)
set_target_properties(DocmeEngine PROPERTIES OUTPUT_NAME "docme")
target_link_libraries(DocmeEngine PRIVATE 
    BetterLogger
    nlohmann_json::nlohmann_json
    BetterDynamicLibraries
)
target_compile_definitions(DocmeEngine PRIVATE 
    # WT_DOCME_DEBUG_TRACING
    WT_DOCME_DEBUGGING
    WT_DOCME_DEBUG_TRACING
    # WT_DOCME_DEBUG_TRACING_VERBOSE
)