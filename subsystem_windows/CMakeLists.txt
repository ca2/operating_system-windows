cmake_minimum_required(VERSION 3.17)
project(subsystem_windows CXX)


message(STATUS "CMAKE_SYSTEM_NAME is ${CMAKE_SYSTEM_NAME}")
message(STATUS "PROJECT_NAME is ${PROJECT_NAME}")
message(STATUS "CMAKE_CURRENT_SOURCE_DIR is ${CMAKE_CURRENT_SOURCE_DIR}")


if (MSVC)
   set(LIBCXX_TARGETING_MSVC ON)
else ()
   set(LIBCXX_TARGETING_MSVC OFF)
endif ()


list(APPEND library_source
   _.cpp
   _.h
   _factory.cpp
   #io/_.cpp
   #io/_.h
   #io/_____debug.xcconfig
   #io/_____release.xcconfig
   #io/aaa_framework.cpp
   #io/aaa_framework.h
   #io/aaa_io_exception.h
   #io/BufferedInputStream.cpp
   #io/BufferedInputStream.h
   #io/BufferedOutputStream.cpp
   #io/BufferedOutputStream.h
   #io/ByteArrayInputStream.cpp
   #io/ByteArrayInputStream.h
   #io/ByteArrayOutputStream.cpp
   #io/ByteArrayOutputStream.h
   #io/Channel.cpp
   #io/Channel.h
   #io/CMakeLists.txt
   #io/DataCopy.cpp
   #io/DataCopy.h
   #io/DataInputStream.cpp
   #io/DataInputStream.h
   #io/DataOutputStream.cpp
   #io/DataOutputStream.h
   #io/InputStream.cpp
   #io/InputStream.h
   #io/io_exception.cpp
   #io/io_lib.vcproj
   #io/matter.txt
   #io/OutputStream.cpp
   #io/OutputStream.h
   #io/remoting_io.vcxproj
   #io/remoting_io.vcxproj.filters
   #io/remoting_io.vcxproj.user
   #io/resource.h
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
   node/CommandLineArguments.cpp
   node/CommandLineArguments.h
   node/Cursor.cpp
   node/Cursor.h
   #node/CMakeLists.txt
   node/Displays.cpp
   node/Displays.h
   node/DynamicLibrary.cpp
   node/DynamicLibrary.h
   node/EmulatedAnonymousPipeFactory.cpp
   node/EmulatedAnonymousPipeFactory.h
   node/File.cpp
   node/File.h
   node/Impersonator.cpp
   node/Impersonator.h
   node/InputInjector.cpp
   node/InputInjector.h
   node/Keyboard.cpp
   node/Keyboard.h
   node/LocalOperatingSystemApplication.cpp
   node/LocalOperatingSystemApplication.h
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
   thread/_.cpp
   thread/_.h
   #thread/_____debug.xcconfig
   #thread/_____release.xcconfig
   #thread/aaa_framework.cpp
   #thread/aaa_framework.h
   #thread/aaa_ZombieKiller.cpp
   #thread/aaa_ZombieKiller.h
   thread/AutoLock.cpp
   thread/AutoLock.h
   #thread/CMakeLists.txt
   thread/DesktopSelector.cpp
   thread/DesktopSelector.h
   thread/GlobalMutex.cpp
   thread/GlobalMutex.h
   thread/GuiThread.cpp
   thread/GuiThread.h
   thread/LocalMutex.cpp
   thread/LocalMutex.h
   thread/Lockable.h
   #thread/matter.txt
   #thread/remoting_thread.vcxproj
   #thread/remoting_thread.vcxproj.filters
   #thread/remoting_thread.vcxproj.user
   thread/resource.h
   thread/Thread.cpp
   thread/Thread.h
   #thread/thread.vcproj
   thread/ThreadCollector.cpp
   thread/ThreadCollector.h
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
   target_link_libraries(${PROJECT_NAME} PRIVATE acme acme_windows subsystem_bsd_sockets ws2_32 Version)
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
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})


target_compile_definitions(${PROJECT_NAME} PRIVATE _${PROJECT_NAME}_project)
target_compile_definitions(${PROJECT_NAME} PRIVATE UNICODE)
target_compile_definitions(${PROJECT_NAME} PRIVATE _UNICODE)
