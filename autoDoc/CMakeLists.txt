# Common Module CMake Lists file

# Common module variables
set(GENORATOR ${COMMON}/genorator)
set(CONFIG ${COMMON}/config)
set(COMMON_SOURCE_FILES ${COMMON}/source/debugging.cpp)
set(COMMON_HEADER_INCLUDES ${COMMON}/${HEADER} ${COMMON})

# Connect the genorator module to the project
add_subdirectory(${GENORATOR})