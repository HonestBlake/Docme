# CMakeLists.txt for docme common

# Package dirs
set(CLI "${DOCME}/cli")
set(GUI "${DOCME}/gui")
set(CORE "${DOCME}/core")
set(ENGINE "${DOCME}/engine")
set(GENERATOR "${DOCME}/generator")

# Project common files
set(DOCME_INCLUDE_DIRS
    ${DOCME}
)
set(DOCME_SRC_FILES
    "${DOCME}/error.cpp"
)
set(DOCME_MOD_FILES
    "${DOCME}/docme.mpp"
    "${DOCME}/error.mpp"
)
set(DOCME_PCH_FILES
    "${DOCME}/std.hpp"
)

set(FETCHCONTENT_UPDATES_DISCONNECTED ON CACHE BOOL "" FORCE) # Dont download on every config

# Add boost dll and filesystem dependencies
set(FETCHCONTENT_BASE_DIR "${DEPS}/boost") # Put in deps dir
set(BOOST_INCLUDE_LIBRARIES dll filesystem CACHE STRING "" FORCE)
set(BUILD_TESTING OFF CACHE BOOL "" FORCE)
set(BOOST_INCLUDE_LIBRARIES dll filesystem)
set(BOOST_ENABLE_CMAKE ON)
FetchContent_Declare(
    Boost
    URL https://github.com/boostorg/boost/releases/download/boost-1.84.0/boost-1.84.0.tar.xz
    URL_MD5 893b5203b862eb9bbd08553e24ff146a
    DOWNLOAD_EXTRACT_TIMESTAMP ON

    # CMake 3.28+
    EXCLUDE_FROM_ALL
)
FetchContent_MakeAvailable(Boost)


# Add PureLog dependency
set(FETCHCONTENT_BASE_DIR "${DEPS}/PureLog") # Put in deps dir
FetchContent_Declare(
    PureLog
    GIT_REPOSITORY https://github.com/HonestBlake/Pure-Log.git
    GIT_TAG v1.1.0
)
set(PURE_LOG_USE_MODULES ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(PureLog)



# Add Simple CLI dependency
set(FETCHCONTENT_BASE_DIR "${DEPS}/SimpleCLI") # Put in deps dir
FetchContent_Declare(
    SimpleCLI
    GIT_REPOSITORY https://github.com/HonestBlake/Simple-CLI.git
    GIT_TAG v1.1.0
)
set(SIMPLE_CLI_USE_MODULES ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(SimpleCLI)



# Add package subdirectories
add_subdirectory(${CLI})
add_subdirectory(${GUI})
add_subdirectory(${CORE})
add_subdirectory(${ENGINE})
add_subdirectory(${GENERATOR})
