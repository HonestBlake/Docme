# Project Cmake Lists file

# setup AutoDoc project
cmake_minimum_required(VERSION 3.31)
project(
    AutoDoc 
    VERSION 1.0 
    DESCRIPTION "An automatic documentation tool for C/C++ prgrams, uses Doxygen or JavaDoc style comment tags to help generate documentation files."  
    LANGUAGES CXX 
)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Project wide variables
set(COMMON ${CMAKE_SOURCE_DIR}/autoDoc)
set(EXECUTABLE ${CMAKE_SOURCE_DIR}/executable)
set(SOURCE source)
set(HEADER header)
set(LIBRARY library)
set(TEST test)

# Set project wide output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${EXECUTABLE})

# Setup Better Logger library
add_library(BetterLogger INTERFACE)
target_include_directories(BetterLogger INTERFACE ${COMMON}/${LIBRARY}/BetterLogger ${COMMON}/${LIBRARY}/BetterLogger/include)
target_compile_features(BetterLogger INTERFACE cxx_std_20)

# Connect the common module to the project
add_subdirectory(${COMMON})