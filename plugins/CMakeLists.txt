# CMakeLists.txt for PLUGINS package

set(PLUGINS_INCLUDE_DIRS
    ${PLUGINS}
    ${DOCME}
)
set(PLUGINS_PCH_FILES
    "${PLUGINS}/std.hpp"
)

# Plugin dirs
set(CDOC "${PLUGINS}/cdoc")

# Add plugin subdirectories
add_subdirectory(${CDOC})