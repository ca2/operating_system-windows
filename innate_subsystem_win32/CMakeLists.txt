cmake_minimum_required(VERSION 3.17)
project(innate_subsystem_win32 CXX)


list(APPEND library_source
   drawing/Bitmap.cpp
   drawing/DeviceContext.h
   drawing/Bitmap.h
   drawing/Graphics.cpp
   drawing/Brush.h
   drawing/BitmapGraphics.h
   drawing/Icon.h
   drawing/SolidBrush.h
   drawing/DeviceContext.cpp
   drawing/Brush.cpp
   drawing/Pen.h
   drawing/SolidBrush.cpp
   drawing/Pen.cpp
   drawing/Icon.cpp
   drawing/Graphics.h
   drawing/BitmapGraphics.cpp
   _.cpp
   _.h
   _factory.cpp
   button.cpp
   button.h
   dialog.cpp
   dialog.h
   framework.cpp
   framework.h
   _factory.cpp
   BalloonTip.cpp
   BalloonTip.h
   CheckBox.cpp
   CheckBox.h
   ComboBox.cpp
   ComboBox.h
   CommonControlsEx.cpp
   CommonControlsEx.h
   Control.cpp
   Control.h
   Dialog.cpp
   Dialog.h
   DibFrameBuffer.cpp
   DibFrameBuffer.h
   FilteredTextBox.cpp
   FilteredTextBox.h
   ImagedButton.cpp
   ImagedButton.h
   ImageList.cpp
   ImageList.h
   ListBox.cpp
   ListBox.h
   ListView.cpp
   ListView.h
   Menu.cpp
   Menu.h
   MessageWindow.cpp
   MessageWindow.h
   NotifyIcon.cpp
   NotifyIcon.h
   NotifyIconWindow.cpp
   NotifyIconWindow.h
   PaintWindow.cpp
   PaintWindow.h
   ProgressBar.cpp
   ProgressBar.h
   ScrollBar.cpp
   ScrollBar.h
   SpinControl.cpp
   SpinControl.h
   StringFilter.cpp
   StringFilter.h
   subsystem.cpp
   subsystem.h
   SystemMetrics.cpp
   SystemMetrics.h
   Tab.cpp
   Tab.h
   TabContainer.cpp
   TabContainer.h
   TabControl.cpp
   TabControl.h
   TextBox.cpp
   TextBox.h
   ThemeLib.cpp
   ThemeLib.h
   ToolBar.cpp
   ToolBar.h
   Tooltip.cpp
   Tooltip.h
   Trackbar.cpp
   Trackbar.h
   Window.cpp
   Window.h
   WindowFinder.cpp
   WindowFinder.h
   WindowMessageHandler.h
   WindowProcHolder.cpp
   WindowProcHolder.h
   )


add_library(${PROJECT_NAME} SHARED ${library_source})

target_precompile_headers(${PROJECT_NAME} PRIVATE framework.h)

set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)

if (MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE "/MD$<$<CONFIG:Debug>:d>")
    target_link_options(${PROJECT_NAME} PRIVATE "/DEFAULTLIB:msvcrt$<$<CONFIG:Debug>:d>")
    target_link_options(${PROJECT_NAME} PRIVATE "/IMPLIB:${LIBRARY_OUTPUT_PATH}/${PROJECT_NAME}.lib")
    target_link_options(${PROJECT_NAME} PRIVATE "/DEF:${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}.def")
    target_link_libraries(${PROJECT_NAME} PRIVATE acme apex innate_ui_win32 Gdiplus)
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
