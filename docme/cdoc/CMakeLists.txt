# CDoc package cmake lists file

set(CDOC_SOURCE_FILES
    "${CDOC}/${SOURCE}/nodes.cpp"
    "${CDOC}/${SOURCE}/packets.cpp"
)
set(CDOC_HEADER_DIRECTORIES
    "${CDOC}/${HEADER}"
    "${CDOC}/${SOURCE}"
)

add_library(CDoc SHARED 
    ${SOURCE_FILES} 
    ${CDOC_SOURCE_FILES}
) 
target_include_directories(CDoc PRIVATE 
    ${HEADER_DIRECTORIES} 
    ${CDOC_HEADER_DIRECTORIES}
)
set_target_properties(CDoc PROPERTIES OUTPUT_NAME "cdoc")