# Common Module CMake Lists file

# Common module variables
set(PROCESSOR ${COMMON}/${PACKAGE}/processor)
set(SOURCE_FILES 
    ${COMMON}/${SOURCE}/debugging.cpp
    ${COMMON}/${SOURCE}/jsonTools.cpp
    ${COMMON}/${SOURCE}/nodes.cpp
    ${COMMON}/${SOURCE}/packets.cpp
)
set(COMMON_HEADER_INCLUDES ${COMMON}/${HEADER} ${COMMON}/${SOURCE} ${COMMON})

# Add the nlohmann_json library to the project
set(FETCHCONTENT_BASE_DIR ${COMMON}/${LIBRARY}/nlohmann_json)
FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz)
FetchContent_MakeAvailable(json)
set(FETCHCONTENT_BASE_DIR ${COMMON}/${LIBRARY}/BetterDynamicLibraries)
FetchContent_Declare(
    BetterDynamicLibraries
    GIT_REPOSITORY https://github.com/HonestBlake/Better-Dynamic-Libraries.git
    GIT_TAG v1.0.5
)
FetchContent_MakeAvailable(BetterDynamicLibraries)

# Add the BetterLogger library to the project
add_library(BetterLogger INTERFACE)
target_include_directories(
    BetterLogger INTERFACE 
    ${COMMON}/${LIBRARY}/BetterLogger/include 
    ${COMMON}/${LIBRARY}/BetterLogger
)

# Connect the processor module to the project
add_subdirectory(${PROCESSOR})