# Included by project() in each component, so POST_BUILD belongs to its target's directory.
if(NOT __REACTOS__ OR NOT MINGW OR NOT CMAKE_SIZEOF_VOID_P EQUAL 4)
    return()
endif()
if(CMAKE_VERSION VERSION_LESS 3.19)
    message(FATAL_ERROR "Automatic ReactOS deployment requires CMake 3.19 or newer")
endif()
set(CA2_REACTOS_DEPLOY_DIRECTORY "${CMAKE_SOURCE_DIR}/../_stripped_output" CACHE PATH "ReactOS binaries without DWARF debug sections")
get_filename_component(CA2_REACTOS_DEPLOY_DIRECTORY "${CA2_REACTOS_DEPLOY_DIRECTORY}" ABSOLUTE BASE_DIR "${CMAKE_SOURCE_DIR}")
if(NOT CMAKE_OBJCOPY)
    message(FATAL_ERROR "ReactOS deployment requires the toolchain's objcopy")
endif()
get_property(deploy_scheduled DIRECTORY PROPERTY CA2_DEPLOY_SCHEDULED)
if(NOT deploy_scheduled)
    set_property(DIRECTORY PROPERTY CA2_DEPLOY_SCHEDULED TRUE)
    function(ca2_deploy_directory_targets)
        get_property(targets DIRECTORY PROPERTY BUILDSYSTEM_TARGETS)
        foreach(target IN LISTS targets)
            get_target_property(type ${target} TYPE)
            if(NOT type MATCHES "^(EXECUTABLE|SHARED_LIBRARY|MODULE_LIBRARY)$")
                continue()
            endif()
            add_custom_command(TARGET ${target} POST_BUILD
                COMMAND "${CMAKE_COMMAND}"
                    "-DSOURCE_FILE=$<TARGET_FILE:${target}>"
                    "-DDESTINATION=${CA2_REACTOS_DEPLOY_DIRECTORY}"
                    "-DOBJCOPY=${CMAKE_OBJCOPY}"
                    -P "${CMAKE_SOURCE_DIR}/operating_system/operating_system-windows/tools/reactos-import-audit/deployment-copy.cmake"
                COMMENT "Preparing ReactOS deployment: ${target}"
                VERBATIM)
            if(type STREQUAL "EXECUTABLE")
                add_custom_command(TARGET ${target} POST_BUILD
                    COMMAND "${CMAKE_COMMAND}"
                        "-DSOURCE_DIRECTORY=$<TARGET_FILE_DIR:${target}>"
                        "-DDESTINATION=${CA2_REACTOS_DEPLOY_DIRECTORY}"
                        "-DOBJCOPY=${CMAKE_OBJCOPY}"
                        -DRUNTIME_ONLY=ON
                        -P "${CMAKE_SOURCE_DIR}/operating_system/operating_system-windows/tools/reactos-import-audit/deployment-copy.cmake"
                    VERBATIM)
            endif()
        endforeach()
    endfunction()
    cmake_language(DEFER CALL ca2_deploy_directory_targets)
endif()
