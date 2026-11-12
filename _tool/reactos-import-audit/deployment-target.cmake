if(NOT __REACTOS__ OR NOT MINGW OR NOT CMAKE_SIZEOF_VOID_P EQUAL 4)
    return()
endif()
set(CA2_REACTOS_DEPLOY_DIRECTORY "${CMAKE_SOURCE_DIR}/../_stripped_output" CACHE PATH "ReactOS binaries without DWARF debug sections")
add_custom_target(reactos_deploy
    COMMAND "${CMAKE_COMMAND}"
        "-DSOURCE_DIRECTORY=${EXECUTABLE_OUTPUT_PATH}"
        "-DDESTINATION=${CA2_REACTOS_DEPLOY_DIRECTORY}"
        "-DOBJCOPY=${CMAKE_OBJCOPY}"
        -P "${CMAKE_CURRENT_LIST_DIR}/deployment-copy.cmake"
    COMMENT "Refreshing ReactOS deployment folder"
    VERBATIM)
