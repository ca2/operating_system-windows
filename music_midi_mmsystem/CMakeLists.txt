cmake_minimum_required(VERSION 3.17)
project(music_midi_mmsystem CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_EXTENSIONS OFF)


message(STATUS "CMAKE_SYSTEM_NAME is ${CMAKE_SYSTEM_NAME}")


if(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
    set(LINUX TRUE)
    set(PLATFORM_NAME "linux")
    include(FindPkgConfig)
elseif(WIN32)
    set(PLATFORM_NAME "windows")
endif()


set(LIBRARY_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../../time-${PLATFORM_NAME}/cmake)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../../time-${PLATFORM_NAME}/cmake)


list(APPEND music_midi_mmsystem_source
        _.cpp
        _.h
        _factory.cpp
        framework.cpp
        framework.h)



if (MSVC)
    set(LIBCXX_TARGETING_MSVC ON)
else()
    set(LIBCXX_TARGETING_MSVC OFF)
endif()


add_library(music_midi_mmsystem SHARED ${music_midi_mmsystem_source})

target_precompile_headers(music_midi_mmsystem PRIVATE framework.h)

set_target_properties(music_midi_mmsystem PROPERTIES LINKER_LANGUAGE CXX)

if (MSVC)
    target_compile_options(music_midi_mmsystem PRIVATE "/MD$<$<CONFIG:Debug>:d>")
    target_link_options(music_midi_mmsystem PRIVATE "/DEFAULTLIB:msvcrt$<$<CONFIG:Debug>:d>")
    target_link_options(music_midi_mmsystem PRIVATE "/IMPLIB:${LIBRARY_OUTPUT_PATH}/music_midi_mmsystem.lib")
    target_link_options(music_midi_mmsystem PRIVATE "/DEF:${CMAKE_CURRENT_SOURCE_DIR}/music_midi_mmsystem.def")
    target_link_libraries(music_midi_mmsystem PRIVATE acme apex aqua aura Gdiplus)
elseif(LINUX)
    #pkg_check_modules(PKGCONFIG glib-2.0 gtk+-3.0 gdk-3.0 appindicator-0.1)
    pkg_check_modules(PKGCONFIG glib-2.0 freetype2 gtk+-3.0 gdk-3.0)
    target_compile_options(music_midi_mmsystem PRIVATE ${PKGCONFIG_CFLAGS})
    #target_compile_options(music_midi_mmsystem PRIVATE -std=c++14)
    #target_link_options(music_midi_mmsystem PRIVATE ${GTK_LDFLAGS})
    target_link_options(music_midi_mmsystem PRIVATE -Wl,-rpath=\$ORIGIN)
    target_link_libraries(music_midi_mmsystem PRIVATE z dl pthread ncurses X11 Xrender Xinerama Xft ${PKGCONFIG_LIBRARIES})
    target_link_options(music_midi_mmsystem PRIVATE -Wl,-z,defs)
    message("PKGCONFIG_LIBRARIES is " ${PKGCONFIG_LIBRARIES})
endif()

target_link_directories(music_midi_mmsystem PRIVATE ${LIBRARY_OUTPUT_PATH})
target_link_directories(music_midi_mmsystem PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../archive/storage-${PLATFORM_NAME}/library/x64/basis)
target_link_directories(music_midi_mmsystem PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../archive/storage-${PLATFORM_NAME}/third/library/x64/basis)


target_include_directories(music_midi_mmsystem PRIVATE $ENV{HOME}/__config)
target_include_directories(music_midi_mmsystem PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../..)
target_include_directories(music_midi_mmsystem PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/..)
target_include_directories(music_midi_mmsystem PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../source)
target_include_directories(music_midi_mmsystem PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../source/app)
target_include_directories(music_midi_mmsystem PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../source/app/_include)
target_include_directories(music_midi_mmsystem PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../source/include)
target_include_directories(music_midi_mmsystem PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../archive/platform-${PLATFORM_NAME})
target_include_directories(music_midi_mmsystem PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../archive/platform-${PLATFORM_NAME}/_include)
target_include_directories(music_midi_mmsystem PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../archive/third-${PLATFORM_NAME}/include)
target_include_directories(music_midi_mmsystem PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../archive/third-${PLATFORM_NAME}/third/include)
target_include_directories(music_midi_mmsystem PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../archive/third-${PLATFORM_NAME}/third/include/include)
target_include_directories(music_midi_mmsystem PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})


target_compile_definitions(music_midi_mmsystem PRIVATE _music_midi_mmsystem_LIBRARY)
target_compile_definitions(music_midi_mmsystem PRIVATE UNICODE)
target_compile_definitions(music_midi_mmsystem PRIVATE _UNICODE)
