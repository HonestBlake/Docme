# WorTech CDocs 

# setup cmake
cmake_minimum_required(VERSION 3.29)
project(CDocs VERSION 1.9 DESCRIPTION "C++ doc genorator"  LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# Other build vars
set(ROOT_DIR ${CMAKE_SOURCE_DIR}/..)
>
set(COMMON ${ROOT_DIR}/common)
set(CONFIG ${ROOT_DIR}/config)
set(GENORATOR ${ROOT_DIR}/genorator)

set(BUILD ${ROOT_DIR}/build)
set(SOURCE source)
set(HEADER header)
set(LIBRARY library)

# Set source and header files
set(S_COMMON)
set(S_CONFIG)
set(GENORATOR_SOURCE_FILES ${GENORATOR}/main.cpp ${GENORATOR}/${SOURCE}/nodes.cpp ${GENORATOR}/${SOURCE}/helpers.cpp)
set(COMMON_HEADER_INCLUDES ${COMMON}/${HEADER})
set(H_CONFIG)
set(GENORATOR_HEADER_INCLUDES ${GENORATOR}/${HEADER})

# Setup Better Logger library
add_library(BetterLogger INTERFACE)
target_include_directories(BetterLogger INTERFACE ${COMMON}/${LIBRARY}/BetterLogger ${COMMON}/${LIBRARY}/BetterLogger/include)
target_compile_features(BetterLogger INTERFACE cxx_std_20)

# Build Genorator
add_executable(Genorator ${GENORATOR_SOURCE_FILES})
target_include_directories(Genorator PRIVATE ${GENORATOR_HEADER_INCLUDES} ${COMMON_HEADER_INCLUDES})
target_link_libraries(Genorator PRIVATE BetterLogger)
set_target_properties(Genorator PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${BUILD})
