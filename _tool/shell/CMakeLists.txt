cmake_minimum_required(VERSION 3.21)
project(ca2_shell LANGUAGES CXX)

if(NOT WIN32)
    message(FATAL_ERROR "The Git Bash launcher requires Windows")
endif()

if(NOT CMAKE_CONFIGURATION_TYPES AND NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build configuration" FORCE)
endif()

# MSVC reports the compiler target, including when Ninja cross-compiles.
string(TOLOWER "${CMAKE_CXX_COMPILER_ARCHITECTURE_ID}" architecture)
if(architecture MATCHES "^(x86|win32)$")
    set(architecture x86)
elseif(architecture MATCHES "^(x64|amd64)$")
    set(architecture x64)
elseif(architecture STREQUAL "arm64")
    set(architecture arm64)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    execute_process(COMMAND "${CMAKE_CXX_COMPILER}" -dumpmachine
        OUTPUT_VARIABLE target_triple OUTPUT_STRIP_TRAILING_WHITESPACE COMMAND_ERROR_IS_FATAL ANY)
    if(target_triple MATCHES "^x86_64")
        set(architecture x64)
    elseif(target_triple MATCHES "^i[3-6]86")
        set(architecture x86)
    elseif(target_triple MATCHES "^(aarch64|arm64)")
        set(architecture arm64)
    endif()
endif()
if(NOT architecture MATCHES "^(x86|x64|arm64)$")
    message(FATAL_ERROR "Unsupported Windows compiler architecture: ${architecture}")
endif()

get_filename_component(checkout "${CMAKE_CURRENT_LIST_DIR}/../../../.." ABSOLUTE)
set(output_dir "${checkout}/time-windows/${architecture}/$<CONFIG>")

add_executable(shell_launcher WIN32 shell.cpp)
target_compile_features(shell_launcher PRIVATE cxx_std_17)
target_link_libraries(shell_launcher PRIVATE advapi32 user32)
if(MINGW)
    target_link_options(shell_launcher PRIVATE -municode -static)
endif()
set_target_properties(shell_launcher PROPERTIES
    OUTPUT_NAME shell
    MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>"
    RUNTIME_OUTPUT_DIRECTORY "${output_dir}"
    PDB_OUTPUT_DIRECTORY "${output_dir}")

add_custom_target(shell ALL
    COMMAND "${CMAKE_COMMAND}" -E copy_if_different "$<TARGET_FILE:shell_launcher>" "${checkout}/shell.exe"
    DEPENDS shell_launcher
    VERBATIM)
