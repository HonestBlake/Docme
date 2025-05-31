# Project cmake Lists file

cmake_minimum_required(VERSION 4.0.2)
project(
    "Docme"
    VERSION 0.0.0
    DESCRIPTION "An automatic documentation tool for software, provides built in as well as a platform to create customizable documentation parsing and generation"
    LANGUAGES CXX 
)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
include(FetchContent)

add_compile_options(
    -Wno-inline-namespace-reopened-noninline 
    -Wall 
    -Wextra 
    -Wpedantic
    -Wno-switch
)


# Project wide variables
set(ROOT_DIR ${CMAKE_SOURCE_DIR})
set(BINARY "${ROOT_DIR}/binary")
set(DOCME "${ROOT_DIR}/docme")
set(SOURCE "source")
set(HEADER "header")
set(LIBRARY "library")
set(TEST "test")

# Set project wide output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BINARY})

add_subdirectory(${DOCME}) # Add docme package cmake list file