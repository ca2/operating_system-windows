cmake_minimum_required(VERSION 3.17)
project(acme_windows CXX)


list(APPEND library_source
   _.cpp
   _.h
   _factory.cpp
   _file.cpp
   _no_pch.cpp
   create_process.cpp
   create_process.h
   directory_system.cpp
   directory_system.h
   file_system.cpp
   file_system.h
   path_system.cpp
   path_system.h
   application.cpp
   application.h
   console.cpp
   console.h
   directory_context.cpp
   directory_context.h
   #dir_system.cpp
   #dir_system.h
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
   #message_loop.cpp
   mmresult.cpp
   mmresult.h
   mmsystem.cpp
   node.cpp
   node.h
   pipe.cpp
   pipe.h
   registry.cpp
   registry.h
   #sapi.cpp
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

set_source_files_properties(_no_pch.cpp PROPERTIES SKIP_PRECOMPILE_HEADERS ON)

add_library(${PROJECT_NAME} SHARED ${library_source})
add_library(static_${PROJECT_NAME} STATIC ${library_source})

target_precompile_headers(${PROJECT_NAME} PRIVATE framework.h)
target_precompile_headers(static_${PROJECT_NAME} PRIVATE framework.h)

set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)
target_compile_definitions(static_${PROJECT_NAME} PRIVATE CUBE)

if (MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE "/MD$<$<CONFIG:Debug>:d>")
    target_link_options(${PROJECT_NAME} PRIVATE "/DEFAULTLIB:msvcrt$<$<CONFIG:Debug>:d>")
    target_link_options(${PROJECT_NAME} PRIVATE "/IMPLIB:${LIBRARY_OUTPUT_PATH}/${PROJECT_NAME}.lib")
    target_link_options(${PROJECT_NAME} PRIVATE "/DEF:${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}.def")
    target_link_libraries(${PROJECT_NAME} PRIVATE
       acme_windows_common
       acme
       Gdiplus
       Setupapi
       Credui)
elseif(LINUX)

    if(NOT DONT_USE_PKG_CONFIG)
        #pkg_check_modules(PKGCONFIG glib-2.0 gtk+-3.0 gdk-3.0 appindicator-0.1)
        pkg_check_modules(PKGCONFIG glib-2.0 freetype2 gtk+-3.0 gdk-3.0)
    endif()
    target_compile_options(${PROJECT_NAME} PRIVATE ${PKGCONFIG_CFLAGS})
    #target_compile_options(${PROJECT_NAME} PRIVATE -std=c++14)
    #target_link_options(${PROJECT_NAME} PRIVATE ${GTK_LDFLAGS})
    target_link_options(${PROJECT_NAME} PRIVATE -Wl,-rpath=\$ORIGIN)
    target_link_libraries(${PROJECT_NAME} PRIVATE z dl pthread ncurses X11 Xrender Xinerama Xft ${PKGCONFIG_LIBRARIES})
    target_link_options(${PROJECT_NAME} PRIVATE -Wl,-z,defs)
    message("PKGCONFIG_LIBRARIES is " ${PKGCONFIG_LIBRARIES})
endif()



list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/../..)
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/..)
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR})


target_include_directories(${PROJECT_NAME} PRIVATE ${library_include_directories})
target_include_directories(static_${PROJECT_NAME} PRIVATE ${library_include_directories})



target_compile_definitions(${PROJECT_NAME} PRIVATE _${PROJECT_NAME}_project)
