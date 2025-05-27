# Project Cmake Lists file

set(PROJECT_NAME Docme)
set(PROJECT_DESCRIPTION "An automatic documentation tool for software, provides built in as well as a platform to create customizable documentation parsing and generation" )
set(PROJECT_VERSION 0.0.0)

# setup Docme project
cmake_minimum_required(VERSION 3.31)
project(
    ${PROJECT_NAME} 
    VERSION ${PROJECT_VERSION}
    DESCRIPTION ${PROJECT_DESCRIPTION}
    LANGUAGES CXX 
)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
include(FetchContent)

# Project wide variables
set(COMMON ${CMAKE_SOURCE_DIR}/docme)
set(BINARY ${CMAKE_SOURCE_DIR}/binary)
set(SOURCE source)
set(HEADER header)
set(LIBRARY library)
set(TEST test)
set(PACKAGE package)

# Set project wide output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BINARY})

# Connect the common module to the project
add_subdirectory(${COMMON})