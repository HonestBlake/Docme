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

# Create project directories
set(ROOT ${CMAKE_SOURCE_DIR})
set(DEPS "${ROOT}/deps")
set(DEPS_BUILD "${CMAKE_BINARY_DIR}/deps")
set(DEPS_STAMPS "${DEPS}/.docme-stamps")
set(LIB "${ROOT}/lib")
set(LIB_RELEASE "${LIB}/release")
set(LIB_DEBUG "${LIB}/debug")
set(BIN "${ROOT}/bin")
set(BIN_RELEASE "${BIN}/release")
set(BIN_DEBUG "${BIN}/debug")
set(DOCME "${ROOT}/docme")

include(FetchContent) # For fetching dependencies
set(FETCHCONTENT_BASE_DIR "${CMAKE_BINARY_DIR}/_deps" CACHE PATH "Default FetchContent cache" FORCE)
set(FETCHCONTENT_UPDATES_DISCONNECTED ON CACHE BOOL "" FORCE) # Don't download deps on every config

# Show selected compiler
message(STATUS "Selected C++ Compiler: ${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION}")
message(STATUS "Selected Build Mode: ${CMAKE_BUILD_TYPE}")

function(docme_set_external_target_output target output_root)
    if(TARGET ${target})
        set_target_properties(${target} PROPERTIES
            ARCHIVE_OUTPUT_DIRECTORY "${output_root}/lib/$<LOWER_CASE:$<CONFIG>>"
            LIBRARY_OUTPUT_DIRECTORY "${output_root}/lib/$<LOWER_CASE:$<CONFIG>>"
            RUNTIME_OUTPUT_DIRECTORY "${output_root}/bin/$<LOWER_CASE:$<CONFIG>>"
        )
    endif()
endfunction()

macro(docme_fetchcontent_make_available content_name fetchcontent_base_dir)
    set(_DOCME_PREVIOUS_FETCHCONTENT_BASE_DIR "${FETCHCONTENT_BASE_DIR}")
    set(FETCHCONTENT_BASE_DIR "${fetchcontent_base_dir}")
    FetchContent_MakeAvailable(${content_name})
    set(FETCHCONTENT_BASE_DIR "${_DOCME_PREVIOUS_FETCHCONTENT_BASE_DIR}")
    unset(_DOCME_PREVIOUS_FETCHCONTENT_BASE_DIR)
endmacro()

function(docme_fetchcontent_use_existing_if_current content_name source_dir stamp_file stamp_value)
    string(TOUPPER "${content_name}" _DOCME_CONTENT_UPPER)
    set(_DOCME_SOURCE_OVERRIDE "FETCHCONTENT_SOURCE_DIR_${_DOCME_CONTENT_UPPER}")
    unset(${_DOCME_SOURCE_OVERRIDE} CACHE)

    if(EXISTS "${source_dir}/CMakeLists.txt" AND EXISTS "${stamp_file}")
        set(_DOCME_USE_EXISTING_SOURCE ON)

        file(READ "${stamp_file}" _DOCME_EXISTING_STAMP)
        if(NOT "${_DOCME_EXISTING_STAMP}" STREQUAL "${stamp_value}")
            set(_DOCME_USE_EXISTING_SOURCE OFF)
        endif()

        if(_DOCME_USE_EXISTING_SOURCE)
            set(${_DOCME_SOURCE_OVERRIDE} "${source_dir}" CACHE PATH "Use existing ${content_name} source" FORCE)
        endif()
    endif()
endfunction()

function(docme_fetchcontent_write_stamp stamp_file stamp_value)
    get_filename_component(_DOCME_STAMP_DIR "${stamp_file}" DIRECTORY)
    file(MAKE_DIRECTORY "${_DOCME_STAMP_DIR}")
    file(WRITE "${stamp_file}" "${stamp_value}")
endfunction()

add_subdirectory(${DOCME}) # Add Docme common
