# CMakeLists.txt for ENGINE package

# Add boost dll and filesystem dependencies
set(DOCME_BOOST_VERSION 1.85.0)
set(DOCME_BOOST_ARCHIVE "boost-${DOCME_BOOST_VERSION}-cmake.tar.xz")
set(DOCME_BOOST_URL "https://github.com/boostorg/boost/releases/download/boost-${DOCME_BOOST_VERSION}/${DOCME_BOOST_ARCHIVE}")
set(DOCME_BOOST_URL_MD5 badea970931766604d4d5f8f4090b176)
set(DOCME_BOOST_SOURCE_DIR "${DEPS}/boost")
set(DOCME_BOOST_BUILD_DIR "${DEPS_BUILD}/boost/boost-build")
set(DOCME_BOOST_FETCHCONTENT_DIR "${DEPS_BUILD}/boost/fetchcontent")
set(DOCME_BOOST_STAMP_FILE "${DEPS_STAMPS}/boost-source.stamp")
set(DOCME_BOOST_STAMP_VALUE "URL=${DOCME_BOOST_URL}\nURL_HASH=MD5=${DOCME_BOOST_URL_MD5}\n")
set(BOOST_INCLUDE_LIBRARIES dll filesystem CACHE STRING "" FORCE)
set(BUILD_TESTING OFF CACHE BOOL "" FORCE)
set(BOOST_ENABLE_CMAKE ON)
FetchContent_Declare(
    Boost
    URL "${DOCME_BOOST_URL}"
    URL_HASH MD5=${DOCME_BOOST_URL_MD5}
    DOWNLOAD_EXTRACT_TIMESTAMP ON
    SOURCE_DIR "${DOCME_BOOST_SOURCE_DIR}"
    BINARY_DIR "${DOCME_BOOST_BUILD_DIR}"
    EXCLUDE_FROM_ALL
)
docme_fetchcontent_use_existing_if_current(
    Boost
    "${DOCME_BOOST_SOURCE_DIR}"
    "${DOCME_BOOST_STAMP_FILE}"
    "${DOCME_BOOST_STAMP_VALUE}"
)
docme_fetchcontent_make_available(Boost "${DOCME_BOOST_FETCHCONTENT_DIR}")
docme_fetchcontent_write_stamp("${DOCME_BOOST_STAMP_FILE}" "${DOCME_BOOST_STAMP_VALUE}")
foreach(BOOST_TARGET IN ITEMS
    boost_atomic
    boost_chrono
    boost_container
    boost_date_time
    boost_exception
    boost_filesystem
    boost_thread
)
    docme_set_external_target_output(${BOOST_TARGET} "${DOCME_BOOST_BUILD_DIR}")
endforeach()

set(ENGINE_INCLUDE_DIRS
    ${ENGINE}
)
set(ENGINE_SRC_FILES
    "${ENGINE}/configFile.cpp" 
)
set(ENGINE_MOD_FILES
    "${ENGINE}/engine.mpp"
    "${ENGINE}/configFile.mpp"
)
set(ENGINE_PCH_FILES

)
set_source_files_properties(${ENGINE_SRC_FILES} ${ENGINE_MOD_FILES}
    PROPERTIES SKIP_PRECOMPILE_HEADERS ON
)

add_library(docme_engine STATIC)
target_sources(docme_engine PRIVATE ${ENGINE_SRC_FILES}
    PUBLIC
    FILE_SET cxx_modules
    TYPE CXX_MODULES
    BASE_DIRS ${ENGINE}
    FILES ${ENGINE_MOD_FILES}
)
target_include_directories(docme_engine PUBLIC ${DOCME_INCLUDE_DIRS} ${ENGINE_INCLUDE_DIRS})
target_precompile_headers(docme_engine PRIVATE ${DOCME_PCH_FILES} ${ENGINE_PCH_FILES})
target_link_libraries(docme_engine PRIVATE
    docme_core
    Boost::dll
    Boost::filesystem
)
set_target_properties(docme_engine PROPERTIES
    OUTPUT_NAME "docme-engine"
    PREFIX ""
    SUFFIX ".lib"
)
