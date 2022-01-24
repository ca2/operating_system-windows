cmake_minimum_required(VERSION 3.17)
project(node_windows CXX)


list(APPEND library_source
   _.cpp
   _.h
   _factory.cpp
   framework.cpp
   framework.h)


add_library(node_windows SHARED ${library_source})

target_precompile_headers(node_windows PRIVATE framework.h)

set_target_properties(node_windows PROPERTIES LINKER_LANGUAGE CXX)

if (MSVC)
    target_compile_options(node_windows PRIVATE "/MD$<$<CONFIG:Debug>:d>")
    target_link_options(node_windows PRIVATE "/DEFAULTLIB:msvcrt$<$<CONFIG:Debug>:d>")
    target_link_options(node_windows PRIVATE "/IMPLIB:${LIBRARY_OUTPUT_PATH}/node_windows.lib")
    target_link_options(node_windows PRIVATE "/DEF:${CMAKE_CURRENT_SOURCE_DIR}/node_windows.def")
    target_link_libraries(node_windows PRIVATE acme apex aqua aura Gdiplus)
elseif(LINUX)
    #pkg_check_modules(PKGCONFIG glib-2.0 gtk+-3.0 gdk-3.0 appindicator-0.1)
    pkg_check_modules(PKGCONFIG glib-2.0 freetype2 gtk+-3.0 gdk-3.0)
    target_compile_options(node_windows PRIVATE ${PKGCONFIG_CFLAGS})
    #target_compile_options(node_windows PRIVATE -std=c++14)
    #target_link_options(node_windows PRIVATE ${GTK_LDFLAGS})
    target_link_options(node_windows PRIVATE -Wl,-rpath=\$ORIGIN)
    target_link_libraries(node_windows PRIVATE z dl pthread ncurses X11 Xrender Xinerama Xft ${PKGCONFIG_LIBRARIES})
    target_link_options(node_windows PRIVATE -Wl,-z,defs)
    message("PKGCONFIG_LIBRARIES is " ${PKGCONFIG_LIBRARIES})
endif()

target_link_directories(node_windows PRIVATE ${LIBRARY_OUTPUT_PATH})
target_link_directories(node_windows PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../operating-system/storage-${PLATFORM_NAME}/library/x64/basis)
target_link_directories(node_windows PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../operating-system/storage-${PLATFORM_NAME}/third/library/x64/basis)


target_include_directories(node_windows PRIVATE $ENV{HOME}/__config)
target_include_directories(node_windows PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../..)
target_include_directories(node_windows PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/..)
target_include_directories(node_windows PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../source)
target_include_directories(node_windows PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../source/app)
target_include_directories(node_windows PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../source/app/_include)
target_include_directories(node_windows PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../source/include)
target_include_directories(node_windows PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../operating-system/operating-system-${PLATFORM_NAME})
target_include_directories(node_windows PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../operating-system/operating-system-${PLATFORM_NAME}/_include)
target_include_directories(node_windows PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../operating-system/third-${PLATFORM_NAME}/include)
target_include_directories(node_windows PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../operating-system/third-${PLATFORM_NAME}/third/include)
target_include_directories(node_windows PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../operating-system/third-${PLATFORM_NAME}/third/include/include)
target_include_directories(node_windows PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})


target_compile_definitions(node_windows PRIVATE _NODE_WINDOWS_LIBRARY)
target_compile_definitions(node_windows PRIVATE UNICODE)
target_compile_definitions(node_windows PRIVATE _UNICODE)
