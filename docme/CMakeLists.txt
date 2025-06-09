# Docme common package cmake list file



add_compile_options(
    -Wno-inline-namespace-reopened-noninline 
    -Wall 
    -Wextra 
    -Wpedantic
    -Wno-switch
)

set(SOURCE_FILES
    "${DOCME}/${SOURCE}/debugging.cpp"
    "${DOCME}/${SOURCE}/jsonTools.cpp"
)

set(HEADER_DIRECTORIES
    "${DOCME}"
)

set(ENGINE "${DOCME}/engine")
set(CDOC "${DOCME}/cdoc")

add_subdirectory(${ENGINE}) # Add docme package cmake list file
add_subdirectory(${CDOC}) # Add cdoc package cmake list file 