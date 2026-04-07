cmake_minimum_required(VERSION 3.17)
project(subsystem_win32 CXX)


message(STATUS "CMAKE_SYSTEM_NAME is ${CMAKE_SYSTEM_NAME}")


if (MSVC)
   set(LIBCXX_TARGETING_MSVC ON)
else ()
   set(LIBCXX_TARGETING_MSVC OFF)
endif ()


list(APPEND library_source
   _.cpp
   _.h
   _factory.cpp
   node/security/SecurityDescriptor.cpp
   node/security/SecurityDescriptor.h
   node/security/SecurityIdentifier.cpp
   node/security/SecurityIdentifier.h
   node/security/SecurityAttributes.cpp
   node/security/SecurityAttributes.h
   node/_.cpp
   node/_.h
   #       node/_____debug.xcconfig
   #       node/_____release.xcconfig
   #       node/aaa_Environment.cpp
   #       node/aaa_Environment.h
   #       node/aaa_framework.cpp
   #       node/aaa_framework.h
   node/AnonymousPipe.cpp
   node/AnonymousPipe.h
   node/AnonymousPipeFactory.cpp
   node/AnonymousPipeFactory.h
   node/ApplicationCrashEvents.h
   node/AutoImpersonator.cpp
   node/AutoImpersonator.h
   node/Clipboard.cpp
   node/Clipboard.h
   node/Cursor.cpp
   node/Cursor.h
   #node/CMakeLists.txt
   node/Displays.cpp
   node/Displays.h
   node/LocalWindowsApplication.h
   #node/matter.txt
   node/NamedPipe.cpp
   node/NamedPipe.h
   node/OperatingSystemApplication.cpp
   node/OperatingSystemApplication.h
   node/OperatingSystemHook.cpp
   node/OperatingSystemHook.h
   node/ParentProcess.cpp
   node/ParentProcess.h
   node/Pipe.cpp
   node/Pipe.h
   node/PipeClient.cpp
   node/PipeClient.h
   node/PipeImpersonatedThread.cpp
   node/PipeImpersonatedThread.h
   node/PipeServer.cpp
   node/PipeServer.h
   node/Process.cpp
   node/Process.h
   node/ProcessCommandLine.cpp
   node/ProcessCommandLine.h
   node/ProcessHandle.cpp
   node/ProcessHandle.h
   #       node/remoting_win_system.vcxproj
   #       node/remoting_win_system.vcxproj.filters
   #       node/remoting_win_system.vcxproj.user
   node/resource.h
   node/Screen.cpp
   node/Screen.h
   #node/SecurityDescriptor.cpp
   #node/SecurityIdentifier.cpp
   node/Service.cpp
   node/Service.h
   node/ServiceControlManagerClient.cpp
   node/ServiceControlManagerClient.h
   node/SharedMemory.cpp
   node/SharedMemory.h
   node/Shell.cpp
   node/Shell.h
   #node/SystemException.cpp
   #node/SystemException.h
   node/SystemInformation.cpp
   node/SystemInformation.h
   node/ThemeLib.cpp
   node/ThemeLib.h
   node/UipiControl.cpp
   node/UipiControl.h
   node/VersionInfo.cpp
   node/VersionInfo.h
   #node/win_system.vcproj
   node/WindowsCommandLineArguments.cpp
   node/WindowsCommandLineArguments.h
   node/WindowsEvent.cpp
   node/WindowsEvent.h
   node/WindowsEventEx.cpp
   node/WindowsEventEx.h
   node/WindowsRegistry.cpp
   node/WindowsRegistry.h
   node/WindowsRegistryKey.cpp
   node/WindowsRegistryKey.h
   node/WinHandles.cpp
   node/WinHandles.h
   node/WinStaLibrary.cpp
   node/WinStaLibrary.h
   node/WinTimeMillis.cpp
   node/WinTimeMillis.h
   node/Workstation.cpp
   node/Workstation.h
   node/WsaStartup.cpp
   node/WsaStartup.h
   node/WTS.cpp
   node/WTS.h
   _.h
   _factory.cpp
   framework.cpp
   framework.h
   subsystem.cpp
   subsystem.h
)

if (MSVC)
   list(APPEND library_source deployment.rc)
endif ()

add_library(${PROJECT_NAME} SHARED ${library_source})
target_precompile_headers(${PROJECT_NAME} PRIVATE framework.h)

set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)


if (MSVC)
   target_compile_options(${PROJECT_NAME} PRIVATE "/MD$<$<CONFIG:Debug>:d>")
   target_link_options(${PROJECT_NAME} PRIVATE "/DEFAULTLIB:msvcrt$<$<CONFIG:Debug>:d>")
   target_link_options(${PROJECT_NAME} PRIVATE "/IMPLIB:${LIBRARY_OUTPUT_PATH}/${PROJECT_NAME}.lib")
   target_link_options(${PROJECT_NAME} PRIVATE "/DEF:${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}.def")
   target_link_libraries(${PROJECT_NAME} PRIVATE acme acme_windows Gdiplus)
elseif (${LINUX} OR ${__BSD__})

   pkg_check_modules(PKGCONFIG cairo xkbcommon wayland-client wayland-server wayland-cursor)
   target_compile_options(${PROJECT_NAME} PRIVATE ${PKGCONFIG_CFLAGS})
   #target_compile_options(${PROJECT_NAME} PRIVATE -std=c++14)
   #target_link_options(${PROJECT_NAME} PRIVATE ${GTK_LDFLAGS})
   target_link_options(${PROJECT_NAME} PRIVATE -Wl,-rpath=\$ORIGIN)
   target_link_libraries(${PROJECT_NAME} PRIVATE acme ${PKGCONFIG_LIBRARIES})
   target_link_options(${PROJECT_NAME} PRIVATE -Wl,-z,defs)
   message("PKGCONFIG_LIBRARIES is " ${PKGCONFIG_LIBRARIES})
endif ()

add_dependencies(${PROJECT_NAME} acme)

target_link_directories(${PROJECT_NAME} PRIVATE ${LIBRARY_OUTPUT_PATH})
target_link_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../operating_system/storage-${OPERATING_SYSTEM_NAME}/library/x64/basis)
target_link_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../operating_system/storage-${OPERATING_SYSTEM_NAME}/third/library/x64/basis)


##target_include_directories(${PROJECT_NAME} PRIVATE $HOME_AAA_DIR/__aaa_config)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../..)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/..)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../source)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../source/app)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../source/app/_include)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../source/include)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../operating_system/operating_system-${OPERATING_SYSTEM_NAME})
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../operating_system/operating_system-${OPERATING_SYSTEM_NAME}/_include)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../operating_system/third-${OPERATING_SYSTEM_NAME}/include)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../operating_system/third-${OPERATING_SYSTEM_NAME}/third/include)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../operating_system/third-${OPERATING_SYSTEM_NAME}/third/include/include)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})


target_compile_definitions(${PROJECT_NAME} PRIVATE _${PROJECT_NAME}_project)
target_compile_definitions(${PROJECT_NAME} PRIVATE UNICODE)
target_compile_definitions(${PROJECT_NAME} PRIVATE _UNICODE)
