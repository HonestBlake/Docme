# CMakeLists.txt for Docme project

cmake_minimum_required(VERSION 4.3.3)

# Create Docme project
project(
    "Docme"
    VERSION 1.0.0
    DESCRIPTION "An automatic documentation tool for software, provides built in as well as a platform to create customizable documentation parsing and generation"
    LANGUAGES CXX 
)
# CMake configurations
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent) # For fetching dependencies

# Show selected compiler
message(STATUS "Selected C++ Compiler: ${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION}")
message(STATUS "Selected Build Mode: ${CMAKE_BUILD_TYPE}")


# Create project directories
set(ROOT ${CMAKE_SOURCE_DIR})
set(DEPS "${ROOT}/dependencies")
set(LIB "${ROOT}/lib")
set(LIB_RELEASE "${LIB}/release")
set(LIB_DEBUG "${LIB}/debug")
set(BIN "${ROOT}/bin")
set(BIN_RELEASE "${BIN}/release")
set(BIN_DEBUG "${BIN}/debug")
set(DOCME "${ROOT}/docme")

add_subdirectory(${DOCME}) # Add Docme common