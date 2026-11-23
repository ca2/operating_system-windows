cmake_minimum_required(VERSION 3.21)
project(initialize_project_root LANGUAGES CXX)

if(NOT WIN32)
    message(FATAL_ERROR "initialize_project_root requires Windows")
endif()

if(NOT CMAKE_CONFIGURATION_TYPES AND NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build configuration" FORCE)
endif()

string(TOLOWER "${CMAKE_CXX_COMPILER_ARCHITECTURE_ID}" architecture)
if(architecture MATCHES "^(win32|x86)$")
    set(architecture x86)
elseif(architecture STREQUAL "amd64")
    set(architecture x64)
endif()
if(NOT architecture MATCHES "^(x86|x64|arm64)$")
    message(FATAL_ERROR "Unsupported Windows compiler architecture: ${architecture}")
endif()

get_filename_component(checkout "${CMAKE_CURRENT_LIST_DIR}/../../../.." ABSOLUTE)
set(storage_binary_dir "${checkout}/../operating_system/storage-windows/${architecture}/$<CONFIG>/binary"
    CACHE STRING "Directory for staged Windows binaries")

add_executable(initialize_project_root initialize_project_root.cpp)
target_compile_features(initialize_project_root PRIVATE cxx_std_17)
set_target_properties(initialize_project_root PROPERTIES
    MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>"
    RUNTIME_OUTPUT_DIRECTORY "${storage_binary_dir}")

add_custom_target(deploy_initialize_project_root ALL
    COMMAND "${CMAKE_COMMAND}" -E copy_if_different "$<TARGET_FILE:initialize_project_root>"
        "${checkout}/operating_system/initialize_project_root.exe"
    DEPENDS initialize_project_root
    VERBATIM)
