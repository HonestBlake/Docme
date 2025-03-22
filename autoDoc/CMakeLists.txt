# Common Module CMake Lists file

# Common module variables
set(GENORATOR ${COMMON}/genorator)
set(CONFIG ${COMMON}/config)
set(COMMON_SOURCE_FILES)
set(COMMON_HEADER_INCLUDES ${COMMON}/${HEADER})

# Connect the genorator module to the project
add_subdirectory(${GENORATOR})