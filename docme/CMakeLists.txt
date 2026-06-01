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

# Put FetchContent downloads deps folder
set(FETCHCONTENT_BASE_DIR "${DEPS}/boost")

# Add boost dll and filesystem dependencies
set(BOOST_INCLUDE_LIBRARIES dll filesystem)
set(BOOST_ENABLE_CMAKE ON)
FetchContent_Declare(
    Boost
    URL https://github.com/boostorg/boost/releases/download/boost-1.85.0/boost-1.85.0-cmake.tar.xz
    DOWNLOAD_EXTRACT_TIMESTAMP ON
)
FetchContent_MakeAvailable(Boost)



# Add package subdirectories
add_subdirectory(${CLI})
add_subdirectory(${GUI})
add_subdirectory(${CORE})
add_subdirectory(${ENGINE})
add_subdirectory(${GENERATOR})
