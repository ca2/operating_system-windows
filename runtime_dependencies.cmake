# Runtime deployment belongs to the target platform, not to individual applications.
# These filenames describe the 32-bit GCC MinGW runtime, not MSVC or 64-bit MinGW.
if(NOT MINGW OR NOT CMAKE_SIZEOF_VOID_P EQUAL 4
   OR NOT CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    return()
endif()

set(runtime_manifest "${CMAKE_CURRENT_LIST_DIR}/operating_system/windows/Win32/run_time_dependencies.txt")
file(STRINGS "${runtime_manifest}" runtime_names)
set_property(DIRECTORY APPEND PROPERTY CMAKE_CONFIGURE_DEPENDS "${runtime_manifest}")
if(NOT CMAKE_OBJCOPY)
    message(FATAL_ERROR "MinGW runtime deployment requires the toolchain's objcopy")
endif()
if(NOT CA2_REACTOS_DEPLOY_DIRECTORY)
    set(CA2_REACTOS_DEPLOY_DIRECTORY "${CMAKE_SOURCE_DIR}/../_stripped_output"
        CACHE PATH "ReactOS binaries without DWARF debug sections")
endif()
get_filename_component(CA2_REACTOS_DEPLOY_DIRECTORY "${CA2_REACTOS_DEPLOY_DIRECTORY}"
    ABSOLUTE BASE_DIR "${CMAKE_SOURCE_DIR}")
set(runtime_stage "${CMAKE_CURRENT_BINARY_DIR}/mingw-runtime-stamps")
set(runtime_deploy_script "${CMAKE_CURRENT_LIST_DIR}/tools/reactos-import-audit/deployment-copy.cmake")
set(runtime_stamps)

foreach(runtime_name IN LISTS runtime_names)
    string(STRIP "${runtime_name}" runtime_name)
    if(runtime_name STREQUAL "" OR runtime_name MATCHES "^[#;]")
        continue()
    endif()
    if(runtime_name MATCHES "[/\\\\:]" OR runtime_name MATCHES "^[-.]"
       OR NOT runtime_name MATCHES "\\.dll$")
        message(FATAL_ERROR "Invalid runtime DLL filename in ${runtime_manifest}: ${runtime_name}")
    endif()
    execute_process(COMMAND "${CMAKE_CXX_COMPILER}" "-print-file-name=${runtime_name}"
        RESULT_VARIABLE runtime_result OUTPUT_VARIABLE runtime_source
        ERROR_VARIABLE runtime_error OUTPUT_STRIP_TRAILING_WHITESPACE)
    if(NOT runtime_result EQUAL 0 OR NOT IS_ABSOLUTE "${runtime_source}" OR NOT EXISTS "${runtime_source}")
        get_filename_component(runtime_compiler_directory "${CMAKE_CXX_COMPILER}" DIRECTORY)
        set(runtime_source "${runtime_compiler_directory}/${runtime_name}")
    endif()
    if(NOT EXISTS "${runtime_source}")
        message(FATAL_ERROR "Missing runtime DLL for ${CMAKE_CXX_COMPILER}: ${runtime_name}. ${runtime_error}")
    endif()
    set(runtime_stamp "${runtime_stage}/${runtime_name}.stamp")
    add_custom_command(OUTPUT "${runtime_stamp}"
        BYPRODUCTS
            "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${runtime_name}"
            "${CA2_REACTOS_DEPLOY_DIRECTORY}/${runtime_name}"
        COMMAND "${CMAKE_COMMAND}" -E make_directory
            "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}" "${runtime_stage}"
        COMMAND "${CMAKE_COMMAND}" -E copy_if_different
            "${runtime_source}" "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${runtime_name}"
        COMMAND "${CMAKE_COMMAND}"
            "-DSOURCE_FILE=${runtime_source}"
            "-DDESTINATION=${CA2_REACTOS_DEPLOY_DIRECTORY}"
            "-DOBJCOPY=${CMAKE_OBJCOPY}"
            -P "${runtime_deploy_script}"
        COMMAND "${CMAKE_COMMAND}" -E touch "${runtime_stamp}"
        DEPENDS "${runtime_source}" "${runtime_manifest}"
            "${CMAKE_CURRENT_LIST_FILE}" "${runtime_deploy_script}"
        COMMENT "Staging MinGW32 runtime ${runtime_name}"
        VERBATIM)
    list(APPEND runtime_stamps "${runtime_stamp}")
endforeach()

add_custom_target(mingw_runtime ALL DEPENDS ${runtime_stamps})
# acme is the common base of the framework, including explicit application builds.
if(TARGET acme)
    add_dependencies(acme mingw_runtime)
endif()
