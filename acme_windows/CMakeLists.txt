cmake_minimum_required(VERSION 3.17)
project(acme_windows CXX)


list(APPEND library_source
   _.cpp
   _.h
   acme_dir.cpp
   acme_dir.h
   acme_path.cpp
   acme_path.h
   argcargv.cpp
   callstack.cpp
   console.cpp
   console.h
   factory_exchange.cpp
   file.cpp
   file.h
   file_find.cpp
   file_memory_map.cpp
   file_memory_map.h
   framework.cpp
   framework.h
   list_serial_ports.cpp
   mutex.cpp
   mutex.h
   node.cpp
   node.h
   pipe.cpp
   pipe.h
   registry.cpp
   registry.h
   serial.cpp
   serial.h
   shared_memory.cpp
   shared_memory.h
   strdup_array.cpp
   timer.cpp
   trace.cpp
   uac_tools.cpp
   uac_tools.h
   windows_desktop.cpp
   )


add_library(acme_windows SHARED ${library_source})

target_precompile_headers(acme_windows PRIVATE framework.h)

set_target_properties(acme_windows PROPERTIES LINKER_LANGUAGE CXX)

if (MSVC)
    target_compile_options(acme_windows PRIVATE "/MD$<$<CONFIG:Debug>:d>")
    target_link_options(acme_windows PRIVATE "/DEFAULTLIB:msvcrt$<$<CONFIG:Debug>:d>")
    target_link_options(acme_windows PRIVATE "/IMPLIB:${LIBRARY_OUTPUT_PATH}/acme_windows.lib")
    target_link_options(acme_windows PRIVATE "/DEF:${CMAKE_CURRENT_SOURCE_DIR}/acme_windows.def")
    target_link_libraries(acme_windows PRIVATE acme apex aqua aura Gdiplus)
elseif(LINUX)
    #pkg_check_modules(PKGCONFIG glib-2.0 gtk+-3.0 gdk-3.0 appindicator-0.1)
    pkg_check_modules(PKGCONFIG glib-2.0 freetype2 gtk+-3.0 gdk-3.0)
    target_compile_options(acme_windows PRIVATE ${PKGCONFIG_CFLAGS})
    #target_compile_options(acme_windows PRIVATE -std=c++14)
    #target_link_options(acme_windows PRIVATE ${GTK_LDFLAGS})
    target_link_options(acme_windows PRIVATE -Wl,-rpath=\$ORIGIN)
    target_link_libraries(acme_windows PRIVATE z dl pthread ncurses X11 Xrender Xinerama Xft ${PKGCONFIG_LIBRARIES})
    target_link_options(acme_windows PRIVATE -Wl,-z,defs)
    message("PKGCONFIG_LIBRARIES is " ${PKGCONFIG_LIBRARIES})
endif()



target_include_directories(acme_windows PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../..)
target_include_directories(acme_windows PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/..)
target_include_directories(acme_windows PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})


target_compile_definitions(acme_windows PRIVATE _ACME_WINDOWS_LIBRARY)
target_compile_definitions(acme_windows PRIVATE UNICODE)
target_compile_definitions(acme_windows PRIVATE _UNICODE)
