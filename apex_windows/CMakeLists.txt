cmake_minimum_required(VERSION 3.17)
project(apex_windows CXX)


list(APPEND library_source
   _.cpp
   _.h
   _factory.cpp
   framework.cpp
   framework.h
    gdi.cpp
   interprocess_base.cpp
   interprocess_base.h
   interprocess_caller.cpp
   interprocess_caller.h
   interprocess_target.cpp
   interprocess_target.h
   ip_enum.cpp
   ip_enum.h
   launcher.cpp
   launcher.h
   node.cpp
   node.h
   os_context.cpp
   os_context.h
   process.cpp
   process.h
   process_data.h
   #service.cpp
   #service.h
   service_handler.cpp
   service_handler.h
   shell_launcher.cpp
   shell_launcher.h
   tts_speaker.h
)


add_library(apex_windows SHARED ${library_source})


target_precompile_headers(apex_windows PRIVATE framework.h)


set_target_properties(apex_windows PROPERTIES LINKER_LANGUAGE CXX)


if (MSVC)
    target_compile_options(apex_windows PRIVATE "/MD$<$<CONFIG:Debug>:d>")
    target_link_options(apex_windows PRIVATE "/DEFAULTLIB:msvcrt$<$<CONFIG:Debug>:d>")
    target_link_options(apex_windows PRIVATE "/IMPLIB:${LIBRARY_OUTPUT_PATH}/apex_windows.lib")
    target_link_options(apex_windows PRIVATE "/DEF:${CMAKE_CURRENT_SOURCE_DIR}/apex_windows.def")
    target_link_libraries(apex_windows PRIVATE acme_windows acme_windows_common apex_windows_common acme apex aqua aura Gdiplus)
elseif(LINUX)

    if(NOT DONT_USE_PKG_CONFIG)
        #pkg_check_modules(PKGCONFIG glib-2.0 gtk+-3.0 gdk-3.0 appindicator-0.1)
        pkg_check_modules(PKGCONFIG glib-2.0 freetype2 gtk+-3.0 gdk-3.0)
    endif()
    target_compile_options(apex_windows PRIVATE ${PKGCONFIG_CFLAGS})
    #target_compile_options(apex_windows PRIVATE -std=c++14)
    #target_link_options(apex_windows PRIVATE ${GTK_LDFLAGS})
    target_link_options(apex_windows PRIVATE -Wl,-rpath=\$ORIGIN)
    target_link_libraries(apex_windows PRIVATE z dl pthread ncurses X11 Xrender Xinerama Xft ${PKGCONFIG_LIBRARIES})
    target_link_options(apex_windows PRIVATE -Wl,-z,defs)
    message("PKGCONFIG_LIBRARIES is " ${PKGCONFIG_LIBRARIES})
endif()


target_include_directories(apex_windows PRIVATE $ENV{HOME}/__config)
target_include_directories(apex_windows PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../..)
target_include_directories(apex_windows PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/..)
target_include_directories(apex_windows PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})


target_compile_definitions(${PROJECT_NAME} PRIVATE _${PROJECT_NAME}_project)



