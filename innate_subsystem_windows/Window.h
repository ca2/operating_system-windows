// Copyright (C) 2011,2012 GlavSoft LLC.
// All rights reserved.
//
//-------------------------------------------------------------------------
// This file is part of the TightVNC software.  Please visit our Web site:
//
//                       http://www.tightvnc.com/
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License along
// with this program; if not, write to the Free Software Foundation, Inc.,
// 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
//-------------------------------------------------------------------------
//
// Changed by camilo on beginning of 2024-April <3ThomasBorregaardSørensen!!
#pragma once


#include "acme/operating_system/windows/window.h"
#include "innate_subsystem/Window.h"


#define WM_REFLECT_NOTIFY_EX (105 + 0x2000 + WM_NOTIFY)


namespace innate_subsystem_win32
{

   struct windows_reflect_notify_t
   {
      ::lresult &m_lresult;
      bool m_bHandled;
      ::wparam m_wparam;
      int m_iControl;
      ::lparam m_lparam;
      LPNMHDR m_lpnmhdr;
      windows_reflect_notify_t(::lresult & lresult, ::wparam wparam, ::lparam lparam):
      m_lresult(lresult)
      {
         m_bHandled = false;
         m_wparam = wparam;
         m_iControl = LOWORD(m_wparam);
         m_lparam = lparam;
         m_lpnmhdr = lparam.raw_cast<LPNMHDR>();
      }
      template < typename WINDOWS_NOTIFICATION_STRUCT_POINTER >
      WINDOWS_NOTIFICATION_STRUCT_POINTER * raw_cast()
      {
         return m_lparam.raw_cast<WINDOWS_NOTIFICATION_STRUCT_POINTER>();
      }
   };

   class CLASS_DECL_INNATE_SUBSYSTEM_WIN32 notification_handler :
   virtual public ::subsystem_apex::notification_handler
   {
   public:


      // virtual bool _001OnAction();
      // virtual bool _001OnKeyDownNotification(::user::enum_key ekey);
      // virtual bool _001OnColumnClick(int iColumn);
      //
      //
      //
      // virtual bool _002OnAction(int iControl);
      // virtual bool _002OnKeyDownNotification(int iControl, ::user::enum_key ekey);
      // virtual bool _002OnColumnClick(int iControl, int iColumn);

      virtual bool _000OnNotify(::lresult & lresult, ::wparam wparam, ::lparam lparam);
      virtual void _000OnNotify(windows_reflect_notify_t & notify);
      virtual void _000OnNotifyReflect(windows_reflect_notify_t & notify);


      virtual bool onListViewNotification(windows_reflect_notify_t & notify);



   };


   class CLASS_DECL_INNATE_SUBSYSTEM_WIN32 Window :
      virtual public ::subsystem::implementation< ::subsystem_apex::WindowInterface >,
      virtual public ::windows::window,
      virtual public notification_handler
   {
   public:


   ///protected:
      //HWND m_hWnd;
      //HWND           m_hwnd;
      ::string       m_strClassName;
      ::string       m_strWindowName;
      HICON          m_hicon;
      bool           m_bWndCreated;
      //WNDPROC        m_wndprocDefault;
      bool m_sizeIsChanged;
      ::string m_strTooltip;
      ::wstring m_wstrToolTip;
      bool           m_bShowCursor;
      bool m_bHasClipboardViewerInterest = false;
      HWND m_hwndNextViewer = nullptr;
      bool m_bDoubleBuffering = false;
      bool m_bMinimized = false;
      bool m_isFullScr = false;
      bool m_isMinimizedFromFullScreen = false;
      // It's size of work-area in windowed mode. It is necessary for restore size of window.
      WINDOWPLACEMENT   m_windowplacementWorkArea;
      //WINDOWPLACEMENT m_workArea;
      // It's size of optimal size of work-area in windowed mode.
      ::int_rectangle m_rectangleNormal;


      ::int_rectangle m_clientArea;

      ::int_size m_sizeBuffer = {};
      HDC m_hdcBuffer = nullptr;
      HBITMAP m_hbitmapOld = nullptr;
      HBITMAP m_hbitmapBuffer = nullptr;
      ::pointer < ::innate_subsystem_win32::Bitmap > m_pbitmapBuffer;
      ::pointer < ::innate_subsystem_win32::DeviceContext > m_pdevicecontextBuffer;

      bool m_bIsDraw;
      PAINTSTRUCT m_paintStruct;
      //HDC m_hdc;

      ::pointer < ::innate_subsystem_win32::DeviceContext > m_pdevicecontext;


      struct notification
      {
         ::subsystem_apex::enum_control m_econtrol = ::subsystem_apex::e_control_none;
         int_array   m_iaNotification;
      };

      ::int_map < notification > m_mapControlNotification;

      Window();

      ~Window() override;


      void * _HWND() const override;
      void _setHWND(void *) override;


      void * _WNDPROC_default() const override;

      // getWindow()
      // Get a handle of the window
      ::operating_system::window operating_system_window() const override;
      void set_operating_system_window(const ::operating_system::window & operatingsystemwindow) override;

      ::subsystem_apex::WindowInterface * get_window_implementation() override;

      // createWindow()
      // Create window with windowName and setted style
      // other parameters can by changed
      bool createWindow(const ::scoped_string & scopedstrWindowName, unsigned int style, const ::operating_system::window & operatingsystemwindowParent = 0,
                        int xPos = WINDOW_WIDTH_USE_DEFAULT, int yPos = WINDOW_WIDTH_USE_DEFAULT,
                        int width = WINDOW_WIDTH_USE_DEFAULT, int height = WINDOW_WIDTH_USE_DEFAULT) override;
      bool destroyWindow() override;


      void setClipboardViewerInterest() override;
      bool onDrawClipboard() override;
      // setClass()
      // Set a class name only to the new window created by createWindow
      void setClass(const ::scoped_string  & scopedstrWindowClassName) override;


      void setShowCursor(bool bShowCursor) override;
      bool shouldShowCursor() override;

      void setDoubleBuffering(bool bDoubleBuffering) override;
      bool isDoubleBuffering() override;

      // basic window manipulation procedures
      void show() override;
      void hide() override;
      void enableWindow(bool bEnable) override;
      void setEnabled(bool bEnable) override;
      void updateWindow() override;
      bool setSize(const ::int_size & size) override;
      bool setPosition(const ::int_point & point) override;
      bool setPlacement(const ::int_rectangle & rectangle) override;
      void setWindowText(const ::scoped_string  & scopedstrText) override;


      //
      // Sets input focus to this control
      //

      void setFocus() override;

      //
      // Return true if window has input focus
      //

      bool hasFocus() override;

      //
      // Puts this control foreground and activates it
      //

      bool setForeground() override;

      // //
      // // Changes visible state of this control
      // //
      //
      // void setVisible(bool visible) override;
      //
      //
      // Checks if this control is active (not disabled)
      //

      bool isEnabled() override;

      bool isWindow() override;

      bool isVisible() override;

      bool isIconic() override;

      bool isMinimized() override;

      bool isFullScreen() override;

      //
      // Invalidates control
      //

      void invalidate() override;

      //
      // Gets text associated with window
      //

      ::string getText() override;

      // loadIcon()
      // Set the icon of application where id can be from resource or handle HICON
      void loadIcon(unsigned int id) override;

      // setParent()
      // Making child window by changing parent of the window
      void setParent(const ::operating_system::window & operatingsystemwindow) override;


      ::operating_system::window dialog_item_operating_system_window(int iDlgItem) override;

      // for changing registered class parameters of created window
      void setClassStyle(unsigned int style) override;
      void setClassCursor(::subsystem_apex::CursorInterface * pcursor) override;
      void setClassBackground(::subsystem_apex::BrushInterface * pbrush) override;
      void setClassMenu(::subsystem_apex::MenuInterface * pmenu) override;

      bool we_want_WM_KEYDOWN_when_enter_is_pressed() const override;

      // for changing or get style and exstyle of window
      long long getStyle() override;
      void setStyle(unsigned int style) override;
      void addStyle(unsigned int styleFlag) override;
      void removeStyle(unsigned int styleFlag) override;
      bool isStyleEnabled(unsigned int styleFlags) override;


      long long getExStyle() override;
      void setExStyle(unsigned int exstyle) override;
      void addExStyle(unsigned int styleFlag) override;
      void removeExStyle(unsigned int styleFlag) override;
      bool isExStyleEnabled(unsigned int styleFlag) override;

      // full redraw of window area
      void redraw(const ::int_rectangle &rcArea ={}) override;

      // set or kill timer, with identifactor ident
      // and time in milliseconds
      void setTimer(::uptr ident, unsigned int time) override;
      void killTimer(::uptr ident) override;

      // set foreground window
      void setForegroundWindow() override;

      // post message to this window
      void postMessage(unsigned int Msg, ::wparam wparam = 0, ::lparam lparam = 0) override;

      ::int_rectangle getClientRect() override;
      ::int_rectangle getFullScreenRect() override;
      ::int_size getBorderSize() override;
      ::int_rectangle getScreenWorkArea() override;


      //void doRestoreFromFullScreen() override;
      void minimizeWindow() override;
      void restoreWindow() override;
      void doFullScreen() override;
      void doUnFullScreen() override;
      void adjustWindowSize() override;

      virtual void _doRestoreFromFullScreen();
      virtual void _setSizeFullScreenWindow();
      virtual void _doMinimizeFromFullScreen();
      virtual void _doRestoreToFullScreen();
      virtual bool _applyScreenChanges(int fullscreen);

      //static LRESULT CALLBACK s_window_procedure(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam);
      //virtual bool on_window_procedure(LRESULT &lresult, UINT message, WPARAM wparam, LPARAM lparam) override;

      // static const int MOUSE_LDOWN  = 1;
      // static const int MOUSE_MDOWN  = 2;
      // static const int MOUSE_RDOWN  = 4;
      // static const int MOUSE_WUP    = 8;
      // static const int MOUSE_WDOWN  = 16;

      // private:
      // This function may be implement in child class.
      // Here is stub function, always returned false.
      virtual bool onCommand(::wparam wparam, ::lparam lparam) override;
      virtual bool onSysCommand(::wparam wparam, ::lparam lparam) override;
      virtual bool onMessage(unsigned int message, ::wparam wparam, ::lparam lparam) override;
      virtual bool onMouse(unsigned char mouseButtons, unsigned short wheelSpeed, const ::int_point & position) override;

      virtual bool onCreate(void * pCreateStruct) override;

      virtual bool on_window_procedure(::lresult & lresult, unsigned int message, ::wparam wparam, ::lparam lparam) override;


      virtual void _defer_update_double_buffering();


      void onDraw(::subsystem_apex::GraphicsInterface * pgraphics, const ::int_rectangle & rectangle) override;


      virtual void doPaint();
      void onBeforeFullScreen(bool bRestore) override;
      void onAfterFullScreen(bool bRestore) override;
      void onBeforeUnFullScreen(bool bMinimizing) override;
      void onAfterUnFullScreen(bool bMinimizing) override;
      bool onGetTooltip(int iControl, string &strTooltip) override;
      bool onCalculateDefaultSize(int_rectangle &rectangleDefaultSize) override;
      void onAdjustWindowSize() override;

   };



} //  namespace innate_subsystem_win32


