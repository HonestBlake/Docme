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

# Set debug mode var
set(DOCME_DEBUG OFF)
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(DOCME_DEBUG ON)
endif()
add_compile_definitions(DOCME_DEBUG=$<CONFIG:Debug>)

add_compile_options(
    $<$<CONFIG:Release>:-O3>
)

# Clangd configurations
option(DOCME_CLANGD_BUILD "Enable build settings used for clangd indexing." OFF)
if(DOCME_CLANGD_BUILD)
    set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
endif()

# Create project directories
set(ROOT ${CMAKE_SOURCE_DIR})
set(DEPS "${ROOT}/deps")
set(DEPS_BUILD "${CMAKE_BINARY_DIR}/_deps")
set(LIB "${ROOT}/lib")
set(LIB_RELEASE "${LIB}/release")
set(LIB_DEBUG "${LIB}/debug")
set(BIN "${ROOT}/bin")
set(BIN_RELEASE "${BIN}/release")
set(BIN_DEBUG "${BIN}/debug")
set(DOCME "${ROOT}/docme")

include(FetchContent) # For fetching dependencies

# Show selected compiler
message(STATUS "Selected C++ Compiler: ${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION}")
message(STATUS "Selected Build Mode: ${CMAKE_BUILD_TYPE}")
message(STATUS "Docme Debug Mode: ${DOCME_DEBUG}")

# Reopen inline namespace is used in project so suppress that warning
if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    add_compile_options(-Wno-inline-namespace-reopened-noninline)
endif()

# Temp fix for gcc bug
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    add_link_options(-Wl,--allow-multiple-definition)
endif()

add_subdirectory(${DOCME}) # Add Docme common
