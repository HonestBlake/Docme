# Project cmake list file

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
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_USE_RESPONSE_FILE_FOR_INCLUDES OFF)
include(FetchContent)
include(CTest)


set(ROOT_DIR ${CMAKE_SOURCE_DIR})
set(DOCME "${ROOT_DIR}/docme")
set(BIN "${ROOT_DIR}/bin")
set(LIB "${ROOT_DIR}/lib")
set(SOURCE "source")
set(HEADER "header")
set(TEST "test")

add_subdirectory(${DOCME}) # Add project cmake list file