cmake_minimum_required(VERSION 3.17)
project(innate_subsystem_windows CXX)


list(APPEND library_source
   drawing/Bitmap.cpp
   drawing/Bitmap.h
   drawing/BitmapGraphics.cpp
   drawing/BitmapGraphics.h
   drawing/Brush.cpp
   drawing/Brush.h
   drawing/Cursor.cpp
   drawing/Cursor.h
   drawing/DeviceContext.cpp
   drawing/DeviceContext.h
   drawing/Font.cpp
   drawing/Font.h
   drawing/Graphics.cpp
   drawing/Graphics.h
   drawing/Icon.cpp
   drawing/Icon.h
   drawing/Pen.cpp
   drawing/Pen.h
   drawing/SolidBrush.cpp
   drawing/SolidBrush.h
   #framebuffer/DibFramebuffer.cpp
   #framebuffer/DibFramebuffer.h
   framebuffer/DibSection.cpp
   framebuffer/DibSection.h
   #framebuffer/Framebuffer.cpp
   #framebuffer/Framebuffer.h
   #framebuffer/PixelFormat.cpp
   #framebuffer/PixelFormat.h
   gui/CheckBox.cpp
   gui/CheckBox.h
   gui/ComboBox.cpp
   gui/ComboBox.h
   gui/CommonControlsEx.cpp
   gui/CommonControlsEx.h
   gui/Control.cpp
   gui/Control.h
   gui/Dialog.cpp
   gui/Dialog.h
   gui/FilteredTextBox.cpp
   gui/FilteredTextBox.h
   gui/ImagedButton.cpp
   gui/ImagedButton.h
   gui/ImageList.cpp
   gui/ImageList.h
   gui/KeyboardLayout.cpp
   gui/KeyboardLayout.h
   gui/ListBox.cpp
   gui/ListBox.h
   gui/ListView.cpp
   gui/ListView.h
   gui/Menu.cpp
   gui/Menu.h
   #gui/MessageWindow.cpp
   #gui/MessageWindow.h
   gui/NotifyIcon.cpp
   gui/NotifyIcon.h
   gui/NotifyIconWindow.cpp
   gui/NotifyIconWindow.h
   #gui/PaintWindow.cpp
   #gui/PaintWindow.h
   gui/ProgressBar.cpp
   gui/ProgressBar.h
   gui/ScrollBar.cpp
   gui/ScrollBar.h
   gui/SpinControl.cpp
   gui/SpinControl.h
   gui/StringFilter.cpp
   gui/StringFilter.h
   gui/SystemMetrics.cpp
   gui/SystemMetrics.h
   gui/Tab.cpp
   gui/Tab.h
   gui/TabContainer.cpp
   gui/TabContainer.h
   gui/TabControl.cpp
   gui/TabControl.h
   gui/TextBox.cpp
   gui/TextBox.h
   gui/ThemeLib.cpp
   gui/ThemeLib.h
   gui/Toolbar.cpp
   gui/Toolbar.h
   gui/Tooltip.cpp
   gui/Tooltip.h
   gui/Trackbar.cpp
   gui/Trackbar.h
   gui/Window.cpp
   gui/Window.h
   gui/window_implementation.h
   gui/WindowCache.cpp
   gui/WindowCache.h
   gui/WindowFinder.cpp
   gui/WindowFinder.h
   gui/WindowMessageHandler.h
   gui/WindowProcHolder.cpp
   gui/WindowProcHolder.h
   platform/ResourceLoader.cpp
   platform/ResourceLoader.h
   platform/subsystem.cpp
   platform/subsystem.h
   _.cpp
   _.h
   _common_header.h
   _factory.cpp
   #button.cpp
   #button.h
   #dialog.cpp
   #dialog.h
   _factory.cpp
   #BalloonTip.cpp
   #BalloonTip.h
   framework.cpp
   framework.h
   )


add_library(${PROJECT_NAME} SHARED ${library_source})

target_precompile_headers(${PROJECT_NAME} PRIVATE framework.h)



set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)

if (MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE "/MD$<$<CONFIG:Debug>:d>")
    target_link_options(${PROJECT_NAME} PRIVATE "/DEFAULTLIB:msvcrt$<$<CONFIG:Debug>:d>")
    target_link_options(${PROJECT_NAME} PRIVATE "/IMPLIB:${LIBRARY_OUTPUT_PATH}/${PROJECT_NAME}.lib")
    target_link_options(${PROJECT_NAME} PRIVATE "/DEF:${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}.def")
    target_link_libraries(${PROJECT_NAME} PRIVATE acme  subsystem subsystem_bsd_sockets subsystem_windows apex innate_subsystem Gdiplus)
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



target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../..)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/..)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})


target_compile_definitions(${PROJECT_NAME} PRIVATE _${PROJECT_NAME}_project)
