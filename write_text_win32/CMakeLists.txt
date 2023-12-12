cmake_minimum_required(VERSION 3.17)
project(write_text_win32 CXX)



list(APPEND library_source
        _.cpp
        _.h
        _factory.cpp
   font_enumeration.cpp
   font_enumeration.h
   fonts.cpp
   fonts.h

        framework.cpp
        framework.h
   write_text.cpp
   write_text.h
   write_text_win32_gdi.cpp
   write_text_win32_gdi.h
)




add_library(write_text_win32 SHARED ${library_source})

target_precompile_headers(write_text_win32 PRIVATE framework.h)

set_target_properties(write_text_win32 PROPERTIES LINKER_LANGUAGE CXX)

if (MSVC)
    target_compile_options(write_text_win32 PRIVATE "/MD$<$<CONFIG:Debug>:d>")
    target_link_options(write_text_win32 PRIVATE "/DEFAULTLIB:msvcrt$<$<CONFIG:Debug>:d>")
    target_link_options(write_text_win32 PRIVATE "/IMPLIB:${LIBRARY_OUTPUT_PATH}/write_text_win32.lib")
    target_link_options(write_text_win32 PRIVATE "/DEF:${CMAKE_CURRENT_SOURCE_DIR}/write_text_win32.def")
    target_link_libraries(write_text_win32 PRIVATE acme apex aqua aura Gdiplus)
elseif(LINUX)

    if(NOT DONT_USE_PKG_CONFIG)
        #pkg_check_modules(PKGCONFIG glib-2.0 gtk+-3.0 gdk-3.0 appindicator-0.1)
        pkg_check_modules(PKGCONFIG glib-2.0 freetype2 gtk+-3.0 gdk-3.0)
    endif()
    target_compile_options(write_text_win32 PRIVATE ${PKGCONFIG_CFLAGS})
    #target_compile_options(write_text_win32 PRIVATE -std=c++14)
    #target_link_options(write_text_win32 PRIVATE ${GTK_LDFLAGS})
    target_link_options(write_text_win32 PRIVATE -Wl,-rpath=\$ORIGIN)
    target_link_libraries(write_text_win32 PRIVATE z dl pthread ncurses X11 Xrender Xinerama Xft ${PKGCONFIG_LIBRARIES})
    target_link_options(write_text_win32 PRIVATE -Wl,-z,defs)
    message("PKGCONFIG_LIBRARIES is " ${PKGCONFIG_LIBRARIES})
endif()

target_link_directories(write_text_win32 PRIVATE ${LIBRARY_OUTPUT_PATH})
target_link_directories(write_text_win32 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../operating_system/storage-${OPERATING_SYSTEM_NAME}/library/x64/basis)
target_link_directories(write_text_win32 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../operating_system/storage-${OPERATING_SYSTEM_NAME}/third/library/x64/basis)


target_include_directories(write_text_win32 PRIVATE $ENV{HOME}/__config)
target_include_directories(write_text_win32 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../..)
target_include_directories(write_text_win32 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/..)
target_include_directories(write_text_win32 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../source)
target_include_directories(write_text_win32 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../source/app)
target_include_directories(write_text_win32 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../source/app/_include)
target_include_directories(write_text_win32 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../source/include)
target_include_directories(write_text_win32 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../operating_system/operating_system-${OPERATING_SYSTEM_NAME})
target_include_directories(write_text_win32 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../operating_system/operating_system-${OPERATING_SYSTEM_NAME}/_include)
target_include_directories(write_text_win32 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../operating_system/third-${OPERATING_SYSTEM_NAME}/include)
target_include_directories(write_text_win32 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../operating_system/third-${OPERATING_SYSTEM_NAME}/third/include)
target_include_directories(write_text_win32 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../operating_system/third-${OPERATING_SYSTEM_NAME}/third/include/include)
target_include_directories(write_text_win32 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})


target_compile_definitions(${PROJECT_NAME} PRIVATE _${PROJECT_NAME}_project)



