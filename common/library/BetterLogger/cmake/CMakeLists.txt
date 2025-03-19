cmake_minimum_required(VERSION 3.29)
project(BetterLogger VERSION 1.9 DESCRIPTION "A better Logger for C++"  LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# set environment variables
set(ROOT_DIR ${CMAKE_SOURCE_DIR}/..)
# set(HEADER ${ROOT_DIR}/header)
# set(SOURCE ${ROOT_DIR}/source)
set(INCLUDE ${ROOT_DIR}/include)
# set library
add_library(BetterLogger INTERFACE)
set_target_properties(BetterLogger PROPERTIES INTERFACE_INCLUDE_DIRECTORIES ${INCLUDE})
target_include_directories(BetterLogger INTERFACE ${ROOT_DIR})
target_precompile_headers(BetterLogger INTERFACE ${ROOT_DIR}/header/includes.hpp)
# set tester
add_executable(Tester ${ROOT_DIR}/tester/tester.cpp)
target_link_libraries(Tester PRIVATE BetterLogger)
set_target_properties(Tester PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${ROOT_DIR}/tester)
