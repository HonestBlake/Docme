# CMakeLists.txt for GUI package

set(GUI_INCLUDE_DIRS
    ${GUI}
)
set(GUI_SRC_FILES
    "${GUI}/main.cpp"
)
set(GUI_MOD_FILES
    "${GUI}/gui.mpp"
)
set(GUI_PCH_FILES

)
set_source_files_properties(${DOCME_SRC_FILES} ${DOCME_MOD_FILES} ${GUI_MOD_FILES}
    PROPERTIES SKIP_PRECOMPILE_HEADERS ON
)

add_executable(docme_gui)
target_sources(docme_gui PRIVATE ${DOCME_SRC_FILES} ${GUI_SRC_FILES}
    PRIVATE
    FILE_SET cxx_modules
    TYPE CXX_MODULES
    BASE_DIRS ${DOCME}
    FILES ${DOCME_MOD_FILES} ${GUI_MOD_FILES}
)
target_include_directories(docme_gui PUBLIC ${DOCME_INCLUDE_DIRS} ${GUI_INCLUDE_DIRS})
target_precompile_headers(docme_gui PRIVATE ${DOCME_PCH_FILES} ${GUI_PCH_FILES})
set_target_properties(docme_gui PROPERTIES
    OUTPUT_NAME "docme-gui"
    PREFIX ""
    SUFFIX ".exe"
)
