

if(CMAKE_SIZEOF_VOID_P EQUAL 8)
   set(PLATFORM_CONFIGURATION "x64")
elseif(CMAKE_SIZEOF_VOID_P EQUAL 4)
   set(PLATFORM_CONFIGURATION "Win32")
endif()

#message(STATUS "CMAKE_GENERATOR_PLATFORM is ${CMAKE_GENERATOR_PLATFORM}")

message(STATUS "PLATFORM_CONFIGURATION is ${PLATFORM_CONFIGURATION}")

set(PLATFORM_NAME "windows")
set(OPERATING_SYSTEM_NAME "windows")
set(WIN32 TRUE)
set(UWP FALSE)
set(LINUX FALSE)
set(FREEBSD FALSE)


set(default_node "node_windows")
set(default_draw2d "draw2d_gdiplus")
set(default_write_text "write_text_win32")
set(default_imaging "imaging_wic")
set(default_gpu "gpu_opengl")
set(default_audio "audio_mmsystem")
set(default_input "input_win32")
set(default_networking "networking_bsd")


add_compile_definitions(UNICODE)


list(APPEND app_common_dependencies
acme_windows_common
   acme_windows
   apex_windows_common
   apex_windows
   aura_windows_common
   aura_windows
   windowing_win32
)


#set(LIBRARY_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/time-${OPERATING_SYSTEM_NAME}/x64/basis)
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/output)
#set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/time-${OPERATING_SYSTEM_NAME}/x64/basis)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/output)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/library)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/output)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/output)


message(STATUS "CMAKE_BINARY_DIR is ${CMAKE_BINARY_DIR}")
message(STATUS "LIBRARY_OUTPUT_PATH is ${LIBRARY_OUTPUT_PATH}")

link_directories(${LIBRARY_OUTPUT_PATH})
link_directories(${WORKSPACE_FOLDER}/../operating_system/storage-${OPERATING_SYSTEM_NAME}/${PLATFORM_CONFIGURATION}/${CMAKE_BUILD_TYPE}/library)
link_directories(${WORKSPACE_FOLDER}/../operating_system/storage-${OPERATING_SYSTEM_NAME}/${PLATFORM_CONFIGURATION}/${CMAKE_BUILD_TYPE}/third/library)

include_directories(${WORKSPACE_FOLDER})
include_directories($ENV{HOME}/__config)
include_directories(${WORKSPACE_FOLDER}/source)
include_directories(${WORKSPACE_FOLDER}/source/app)
include_directories(${WORKSPACE_FOLDER}/source/app/include)
include_directories(${WORKSPACE_FOLDER}/source/include)
include_directories(${WORKSPACE_FOLDER}/port/_)
include_directories(${WORKSPACE_FOLDER}/port/include)
include_directories(${WORKSPACE_FOLDER}/operating_system)
if (OPERATING_SYSTEM_POSIX)
   include_directories(${WORKSPACE_FOLDER}/operating_system/operating_system-posix)
   include_directories(${WORKSPACE_FOLDER}/operating_system/operating_system-posix/include)
endif ()
include_directories(${WORKSPACE_FOLDER}/operating_system/operating_system-windows_common)
include_directories(${WORKSPACE_FOLDER}/operating_system/operating_system-windows_common/include)
include_directories(${WORKSPACE_FOLDER}/operating_system/operating_system-${OPERATING_SYSTEM_NAME})
include_directories(${WORKSPACE_FOLDER}/operating_system/operating_system-${OPERATING_SYSTEM_NAME}/include)
include_directories(${WORKSPACE_FOLDER}/operating_system/operating_system-${OPERATING_SYSTEM_NAME}/include/configuration_selection/${CMAKE_BUILD_TYPE})
include_directories(${WORKSPACE_FOLDER}/operating_system/operating_system-${OPERATING_SYSTEM_NAME}/operating_system/${SLASHED_OPERATING_SYSTEM})
include_directories(${WORKSPACE_FOLDER}/operating_system/operating_system-${OPERATING_SYSTEM_NAME}/operating_system/${DISTRO})
