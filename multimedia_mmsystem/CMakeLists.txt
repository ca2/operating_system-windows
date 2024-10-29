cmake_minimum_required(VERSION 3.17)
project(multimedia_mmsystem CXX)





message(STATUS "CMAKE_SYSTEM_NAME is ${CMAKE_SYSTEM_NAME}")


if(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
    set(LINUX TRUE)
    set(OPERATING_SYSTEM_NAME "linux")
    include(FindPkgConfig)
elseif(WIN32)
    set(OPERATING_SYSTEM_NAME "windows")
endif()


set(LIBRARY_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../../time-${OPERATING_SYSTEM_NAME}/cmake)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../../time-${OPERATING_SYSTEM_NAME}/cmake)


list(APPEND multimedia_mmsystem_source
        _.cpp
        _.h
        bitmap.cpp
        bitmap.h
        brush.cpp
        brush.h
        _factory.cpp
        font.cpp
        font.h
        framework.cpp
        framework.h
        graphics.cpp
        graphics.h
        image.cpp
        image.h
        object.cpp
        object.h
        path.cpp
        path.h
        pen.cpp
        pen.h
        preview_dc.cpp
        region.cpp
        region.h
        text.cpp)



if (MSVC)
    set(LIBCXX_TARGETING_MSVC ON)
else()
    set(LIBCXX_TARGETING_MSVC OFF)
endif()


add_library(multimedia_mmsystem SHARED ${multimedia_mmsystem_source})

target_precompile_headers(multimedia_mmsystem PRIVATE framework.h)

set_target_properties(multimedia_mmsystem PROPERTIES LINKER_LANGUAGE CXX)

if (MSVC)
    target_compile_options(multimedia_mmsystem PRIVATE "/MD$<$<CONFIG:Debug>:d>")
    target_link_options(multimedia_mmsystem PRIVATE "/DEFAULTLIB:msvcrt$<$<CONFIG:Debug>:d>")
    target_link_options(multimedia_mmsystem PRIVATE "/IMPLIB:${LIBRARY_OUTPUT_PATH}/multimedia_mmsystem.lib")
    target_link_options(multimedia_mmsystem PRIVATE "/DEF:${CMAKE_CURRENT_SOURCE_DIR}/multimedia_mmsystem.def")
    target_link_libraries(multimedia_mmsystem PRIVATE acme apex aqua aura Gdiplus)
elseif(LINUX)

    if(NOT DONT_USE_PKG_CONFIG)
        #pkg_check_modules(PKGCONFIG glib-2.0 gtk+-3.0 gdk-3.0 appindicator-0.1)
        pkg_check_modules(PKGCONFIG glib-2.0 freetype2 gtk+-3.0 gdk-3.0)
    endif()
    target_compile_options(multimedia_mmsystem PRIVATE ${PKGCONFIG_CFLAGS})
    #target_compile_options(multimedia_mmsystem PRIVATE -std=c++14)
    #target_link_options(multimedia_mmsystem PRIVATE ${GTK_LDFLAGS})
    target_link_options(multimedia_mmsystem PRIVATE -Wl,-rpath=\$ORIGIN)
    target_link_libraries(multimedia_mmsystem PRIVATE z dl pthread ncurses X11 Xrender Xinerama Xft ${PKGCONFIG_LIBRARIES})
    target_link_options(multimedia_mmsystem PRIVATE -Wl,-z,defs)
    message("PKGCONFIG_LIBRARIES is " ${PKGCONFIG_LIBRARIES})
endif()

target_link_directories(multimedia_mmsystem PRIVATE ${LIBRARY_OUTPUT_PATH})
target_link_directories(multimedia_mmsystem PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../operating_system/storage-${OPERATING_SYSTEM_NAME}/library/x64/basis)
target_link_directories(multimedia_mmsystem PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../operating_system/storage-${OPERATING_SYSTEM_NAME}/third/library/x64/basis)


target_include_directories(multimedia_mmsystem PRIVATE $ENV{HOME}/__config)
target_include_directories(multimedia_mmsystem PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../..)
target_include_directories(multimedia_mmsystem PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/..)
target_include_directories(multimedia_mmsystem PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../source)
target_include_directories(multimedia_mmsystem PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../source/app)
target_include_directories(multimedia_mmsystem PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../source/app/_include)
target_include_directories(multimedia_mmsystem PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../source/include)
target_include_directories(multimedia_mmsystem PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../operating_system/operating_system-${OPERATING_SYSTEM_NAME})
target_include_directories(multimedia_mmsystem PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../operating_system/operating_system-${OPERATING_SYSTEM_NAME}/_include)
target_include_directories(multimedia_mmsystem PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../operating_system/third-${OPERATING_SYSTEM_NAME}/include)
target_include_directories(multimedia_mmsystem PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../operating_system/third-${OPERATING_SYSTEM_NAME}/third/include)
target_include_directories(multimedia_mmsystem PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../operating_system/third-${OPERATING_SYSTEM_NAME}/third/include/include)
target_include_directories(multimedia_mmsystem PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})


target_compile_definitions(${PROJECT_NAME} PRIVATE _${PROJECT_NAME}_project)
target_compile_definitions(multimedia_mmsystem PRIVATE UNICODE)
target_compile_definitions(multimedia_mmsystem PRIVATE _UNICODE)
