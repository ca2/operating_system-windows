cmake_minimum_required(VERSION 3.17)
project(aura_windows CXX)
list(APPEND library_source
   _.cpp
   _.h
   _factory.cpp
   framework.cpp
   framework.h)

add_library(aura_windows SHARED ${library_source})

target_precompile_headers(aura_windows PRIVATE framework.h)

set_target_properties(aura_windows PROPERTIES LINKER_LANGUAGE CXX)

if (MSVC)
    target_compile_options(aura_windows PRIVATE "/MD$<$<CONFIG:Debug>:d>")
    target_link_options(aura_windows PRIVATE "/DEFAULTLIB:msvcrt$<$<CONFIG:Debug>:d>")
    target_link_options(aura_windows PRIVATE "/IMPLIB:${LIBRARY_OUTPUT_PATH}/aura_windows.lib")
    target_link_options(aura_windows PRIVATE "/DEF:${CMAKE_CURRENT_SOURCE_DIR}/aura_windows.def")
    target_link_libraries(aura_windows PRIVATE acme apex aqua aura Gdiplus)
elseif(${LINUX})

    if(NOT DONT_USE_PKG_CONFIG)
        #pkg_check_modules(PKGCONFIG glib-2.0 gtk+-3.0 gdk-3.0 appindicator-0.1)
        pkg_check_modules(PKGCONFIG glib-2.0 freetype2 gtk+-3.0 gdk-3.0)
    endif()
    target_compile_options(aura_windows PRIVATE ${PKGCONFIG_CFLAGS})
    #target_compile_options(aura_windows PRIVATE -std=c++14)
    #target_link_options(aura_windows PRIVATE ${GTK_LDFLAGS})
    target_link_options(aura_windows PRIVATE -Wl,-rpath=\$ORIGIN)
    target_link_libraries(aura_windows PRIVATE z dl pthread ncurses X11 Xrender Xinerama Xft ${PKGCONFIG_LIBRARIES})
    target_link_options(aura_windows PRIVATE -Wl,-z,defs)
    message("PKGCONFIG_LIBRARIES is " ${PKGCONFIG_LIBRARIES})
endif()

target_link_directories(aura_windows PRIVATE ${LIBRARY_OUTPUT_PATH})
target_link_directories(aura_windows PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../operating_system/storage-${OPERATING_SYSTEM_NAME}/library/x64/basis)
target_link_directories(aura_windows PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../operating_system/storage-${OPERATING_SYSTEM_NAME}/third/library/x64/basis)


target_include_directories(aura_windows PRIVATE $ENV{HOME}/__config)
target_include_directories(aura_windows PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../..)
target_include_directories(aura_windows PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/..)
target_include_directories(aura_windows PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../source)
target_include_directories(aura_windows PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../source/app)
target_include_directories(aura_windows PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../source/app/_include)
target_include_directories(aura_windows PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../source/include)
target_include_directories(aura_windows PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../operating_system/operating_system-${OPERATING_SYSTEM_NAME})
target_include_directories(aura_windows PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../operating_system/operating_system-${OPERATING_SYSTEM_NAME}/_include)
target_include_directories(aura_windows PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../operating_system/third-${OPERATING_SYSTEM_NAME}/include)
target_include_directories(aura_windows PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../operating_system/third-${OPERATING_SYSTEM_NAME}/third/include)
target_include_directories(aura_windows PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../operating_system/third-${OPERATING_SYSTEM_NAME}/third/include/include)
target_include_directories(aura_windows PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})


target_compile_definitions(aura_windows PRIVATE _AURA_WINDOWS_LIBRARY)
target_compile_definitions(aura_windows PRIVATE UNICODE)
target_compile_definitions(aura_windows PRIVATE _UNICODE)
