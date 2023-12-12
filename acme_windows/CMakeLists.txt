cmake_minimum_required(VERSION 3.17)
project(acme_windows CXX)


list(APPEND library_source
   _.cpp
   _.h
   _factory.cpp
   _file.cpp
   acme_directory.cpp
   acme_directory.h
   acme_file.cpp
   acme_file.h
   acme_path.cpp
   acme_path.h
   application.cpp
   application.h
   console.cpp
   console.h
   dir_context.cpp
   dir_context.h
   dir_system.cpp
   dir_system.h
   exclusive.cpp
   exclusive.h
   file_context.cpp
   file_context.h
   file_dialog.cpp
   file_find.cpp
   file_find.h
   file_link.cpp
   file_link.h
   file_memory_map.cpp
   file_memory_map.h
   file_system.cpp
   file_system.h
   file_watcher.cpp
   file_watcher.h
   folder_dialog.cpp
   framework.cpp
   framework.h
   integration_context.cpp
   integration_context.h
   itemidlist.cpp
   itemidlist.h
   known_folder_struct.cpp
   known_folder_struct.h
   language.cpp
   list_serial_ports.cpp
   main_window.cpp
   main_window.h
   message_loop.cpp
   mmresult.cpp
   mmresult.h
   mmsystem.cpp
   node.cpp
   node.h
   pipe.cpp
   pipe.h
   registry.cpp
   registry.h
   sapi.cpp
   serial.cpp
   serial.h
   shared_memory.cpp
   shared_memory.h
   strdup_array.cpp
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
    target_link_libraries(acme_windows PRIVATE
       acme_windows_common
       acme
       apex
       aqua
       aura
       Gdiplus
       Setupapi
       Credui)
elseif(LINUX)

    if(NOT DONT_USE_PKG_CONFIG)
        #pkg_check_modules(PKGCONFIG glib-2.0 gtk+-3.0 gdk-3.0 appindicator-0.1)
        pkg_check_modules(PKGCONFIG glib-2.0 freetype2 gtk+-3.0 gdk-3.0)
    endif()
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


target_compile_definitions(${PROJECT_NAME} PRIVATE _${PROJECT_NAME}_project)
