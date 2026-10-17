# Register hooks before the outer project configures its component projects.
if(NOT WIN32)
    return()
endif()
list(APPEND CMAKE_PROJECT_INCLUDE
    "${CMAKE_CURRENT_LIST_DIR}/reactos-import-audit/deployment-project.cmake"
    "${CMAKE_CURRENT_LIST_DIR}/windows-common-controls/project.cmake")
set(CMAKE_PROJECT_INCLUDE "${CMAKE_PROJECT_INCLUDE}" PARENT_SCOPE)

# Platform setup supplies compatibility mode and output paths later.
function(ca2_add_windows_tools_targets)
    include("${CMAKE_CURRENT_FUNCTION_LIST_DIR}/reactos-import-audit/deployment-target.cmake")
endfunction()
if(CMAKE_VERSION VERSION_LESS 3.19)
    message(FATAL_ERROR "Windows tools require CMake 3.19 or newer")
endif()
cmake_language(DEFER DIRECTORY "${CMAKE_SOURCE_DIR}" CALL ca2_add_windows_tools_targets)
