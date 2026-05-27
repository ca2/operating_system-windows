// Copyright (C) 2011,2012 GlavSoft LLC.
// All rights reserved.
//
//-------------------------------------------------------------------------
// This file is part of the T i g h t V N C software.  Please visit our Web site:
//
//                       http://www.t i g h t v n c.com/
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
#include "innate_subsystem/gui/Window.h"


#define WM_REFLECT_NOTIFY_EX (105 + 0x2000 + WM_NOTIFY)


namespace innate_subsystem_windows
{

   struct windows_reflect_notify_t
   {
      ::lresult &m_lresult;
      bool m_bHandled;
      ::wparam m_wparam;
      ::innate_subsystem::enum_control m_econtrol;
      ::i32 m_iControl;
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

   class CLASS_DECL_INNATE_SUBSYSTEM_WINDOWS notification_handler :
   virtual public ::innate_subsystem::notification_handler
   {
   public:


      // virtual bool _001OnAction();
      // virtual bool _001OnKeyDownNotification(::user::enum_key ekey);
      // virtual bool _001OnColumnClick(::i32 iColumn);
      //
      //
      //
      // virtual bool _002OnAction(::i32 iControl);
      // virtual bool _002OnKeyDownNotification(::i32 iControl, ::user::enum_key ekey);
      // virtual bool _002OnColumnClick(::i32 iControl, ::i32 iColumn);

      virtual bool _000OnNotify(::lresult & lresult, ::wparam wparam, ::lparam lparam);
      virtual void _000OnNotify(windows_reflect_notify_t & notify);
      virtual void _000OnNotifyReflect(windows_reflect_notify_t & notify);


      virtual bool onListViewNotification(windows_reflect_notify_t & notify);
      virtual bool onTabNotification(windows_reflect_notify_t & notify);



   };


   class CLASS_DECL_INNATE_SUBSYSTEM_WINDOWS Window :
      virtual public Implementation< ::innate_subsystem::WindowCallback >,
      virtual public ::windows::window,
      virtual public notification_handler
   {
   public:


   ///protected:
      //HWND m_hWnd;
      //HWND           m_hwnd;
      ::string       m_strClassName;
      ::string       m_strWindowName;
      ::string       m_strResourceName;
      ::i32          m_iResourceId;
      HICON          m_hicon;
      bool           m_bWndCreated;
      //WNDPROC        m_wndprocDefault;
      ::pointer<::innate_subsystem::WindowInterface> m_pwindowDeferredParent;
      bool m_sizeIsChanged;
      ::string m_strTooltip;
      HCURSOR m_hcursorArrow = nullptr;
      ::wstring m_wstrToolTip;
      enum_cursor       m_ecursor;
      bool m_bHasClipboardViewerInterest = false;
      bool m_bHasOnDrawInterest = false;
      HWND m_hwndNextViewer = nullptr;
      bool m_bDoubleBuffering = false;
      bool m_bMinimized = false;
      bool m_isFullScr = false;
      bool m_isMinimizedFromFullScreen = false;
      // It's size of work-area in windowed mode. It is necessary for restore size of window.
      WINDOWPLACEMENT   m_windowplacementWorkArea;
      //WINDOWPLACEMENT m_workArea;
      // It's size of optimal size of work-area in windowed mode.
      ::i32_rectangle m_rectangleNormal;
      ::innate_subsystem::enum_control m_econtrol = innate_subsystem::e_control_none;

      ::i32_rectangle m_clientArea;

      ::i32_size m_sizeBuffer = {};
      HDC m_hdcBuffer = nullptr;
      HBITMAP m_hbitmapOld = nullptr;
      HBITMAP m_hbitmapBuffer = nullptr;
      ::pointer < ::innate_subsystem_windows::Bitmap > m_pbitmapBuffer;
      ::pointer < ::innate_subsystem_windows::DeviceContext > m_pdevicecontextBuffer;

      bool m_bIsDraw;
      PAINTSTRUCT m_paintStruct;

      ::string m_strWindowTextOffline;
      ::u32 m_uAddStyleOffline = 0;
      ::u32 m_uEraseStyleOffline = 0xffffffffu;
      ::u32 m_uAddStyleExOffline = 0;
      ::u32 m_uEraseStyleExOffline = 0xffffffffu;
      //HDC m_hdc;

      ::pointer < ::innate_subsystem_windows::DeviceContext > m_pdevicecontext;


      struct notification
      {
         ::innate_subsystem::enum_control m_econtrol = ::innate_subsystem::e_control_none;
         i32_array   m_iaNotification;
      };

      ::i32_map < notification > m_mapControlNotification;

      Window();

      ~Window() override;






      void setMouseCursor(enum_cursor ecursor) override;

      void * _WNDPROC_default() const override;

      virtual void _setWindowClassGeneric();
      virtual void _setWindowClassViewer();


      void * _HWND() const override;
      // getWindow()
      // Get a handle of the window
      ::operating_system::window operating_system_window() const override;
      void set_operating_system_window(const ::operating_system::window & operatingsystemwindow) override;

      ::innate_subsystem::WindowInterface * get_window_implementation() override;


      // Set resource name for the window
      void setResourceName(const ::scoped_string & scopedstr) override;
      // Set resource id for the window
      void setResourceId(::u32 uId) override;
      // Get resource name for the window
      ::string getResourceName() override;
      // Get resource id for the window
      ::u32 getResourceId() override;


      // createWindow()
      // Create window with windowName and setted style
      // other parameters can by changed
      bool createWindow(const ::scoped_string & scopedstrWindowName, ::u32 style, const ::operating_system::window & operatingsystemwindowParent = 0,
                        ::i32 xPos = WINDOW_WIDTH_USE_DEFAULT, ::i32 yPos = WINDOW_WIDTH_USE_DEFAULT,
                        ::i32 width = WINDOW_WIDTH_USE_DEFAULT, ::i32 height = WINDOW_WIDTH_USE_DEFAULT) override;
      bool destroyWindow() override;


      virtual void _addChildNotification(::i32 iControl, ::i32 iNotification);
      virtual void _setChildControlType(::i32 iControl, innate_subsystem::enum_control econtrol);


      void setClipboardViewerInterest() override;
      void setOnDrawInterest() override;
      bool onDrawClipboard() override;
      // setClass()
      // Set a class name only to the new window created by createWindow
      //void setClass(const ::scoped_string  & scopedstrWindowClassName) override;
      void setClass(::innate_subsystem::enum_window_class ewindowclass) override;


      void setCursor(enum_cursor ecursor) override;
      enum_cursor getCursor() override;

      void setDoubleBuffering(bool bDoubleBuffering) override;
      bool isDoubleBuffering() override;

      // basic window manipulation procedures
      void show() override;
      void hide() override;
      void enableWindow(bool bEnable) override;
      void setEnabled(bool bEnable) override;
      void updateWindow() override;
      bool setSize(const ::i32_size & size) override;
      bool setPosition(const ::i32_point & point) override;
      bool setPlacement(const ::i32_rectangle & rectangle) override;
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
      void loadIcon(::u32 id) override;

      // setParent()
      // Making child window by changing parent of the window
      void setParent(::innate_subsystem::WindowInterface * pwindow) override;
      ::innate_subsystem::WindowInterface * getParent() override;


      ::operating_system::window dialog_item_operating_system_window(::i32 iDlgItem) override;


      void subclassControlById(::Particle * pWindowControl, ::u32 id) override;
      void subclassWindow(const ::operating_system::window & operatingsystemwindow) override;
      void unsubclassWindow() override;


      // for changing registered class parameters of created window
      void setClassStyle(::u32 style) override;
      void setClassCursor(::innate_subsystem::CursorInterface * pcursor) override;
      void setClassBackground(::innate_subsystem::BrushInterface * pbrush) override;
      void setClassMenu(::innate_subsystem::MenuInterface * pmenu) override;

      bool we_want_WM_KEYDOWN_when_enter_is_pressed() const override;

      // for changing or get style and exstyle of window
      ::i64 getStyle() override;
      void setStyle(::u32 style) override;
      void addStyle(::u32 styleFlag) override;
      void removeStyle(::u32 styleFlag) override;
      bool isStyleEnabled(::u32 styleFlags) override;


      ::i64 getExStyle() override;
      void setExStyle(::u32 exstyle) override;
      void addExStyle(::u32 styleFlag) override;
      void removeExStyle(::u32 styleFlag) override;
      bool isExStyleEnabled(::u32 styleFlag) override;

      // full redraw of window area
      void redraw(const ::i32_rectangle &rcArea ={}) override;

      // set or kill timer, with identifactor ident
      // and time in milliseconds
      void setTimer(::uptr ident, ::u32 time) override;
      void killTimer(::uptr ident) override;

      // set foreground window
      void setForegroundWindow() override;

      // post message to this window
      void postMessage(::u32 Msg, ::wparam wparam = 0, ::lparam lparam = 0) override;
      void post(const ::procedure & procedure) override;

      ::i32_rectangle getClientRect() override;
      ::i32_rectangle getFullScreenRect() override;
      ::i32_size getBorderSize() override;
      ::i32_rectangle getScreenWorkArea() override;


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
      virtual bool _applyScreenChanges(::i32 fullscreen);

      //static LRESULT CALLBACK s_window_procedure(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam);
      //virtual bool on_window_procedure(LRESULT &lresult, UINT message, WPARAM wparam, LPARAM lparam) override;

      // static const ::i32 MOUSE_LDOWN  = 1;
      // static const ::i32 MOUSE_MDOWN  = 2;
      // static const ::i32 MOUSE_RDOWN  = 4;
      // static const ::i32 MOUSE_WUP    = 8;
      // static const ::i32 MOUSE_WDOWN  = 16;

      // private:
      // This function may be implement in child class.
      // Here is stub function, always returned false.
      virtual bool _onWmCommand(::wparam wparam, ::lparam lparam);
      virtual bool onCommand(::u32 controlID, ::u32 notificationID) override;
      //virtual bool onSysCommand(::wparam wparam, ::lparam lparam) override;
      bool on_user_system_command(::user::enum_system_command esystemcommand) override;
      bool onMessage(::user::enum_message emessage, ::wparam wparam, ::lparam lparam) override;
      bool onKey(user::enum_message eusermessage, user::enum_key euserkey) override;
      bool onMouseEx(::u32 uMessage, ::i32 iButtonMask, ::u16 wheelSpeed,
                             const ::i32_point &point, bool &bDoDefaultProcessing) override;
      bool onMouse(::u8 mouseButtons, ::u16 wheelSpeed, const ::i32_point & position) override;

      bool onCreate(void * pCreateStruct) override;

      bool on_window_procedure(::lresult & lresult, ::u32 message, ::wparam wparam, ::lparam lparam) override;


      virtual void _defer_update_double_buffering();


      void onDraw(::innate_subsystem::GraphicsInterface * pgraphics, const ::i32_rectangle & rectangle) override;


      virtual void _doPaint(HDC hdc);
      void onBeforeFullScreen(bool bRestore) override;
      void onAfterFullScreen(bool bRestore) override;
      void onBeforeUnFullScreen(bool bMinimizing) override;
      void onAfterUnFullScreen(bool bMinimizing) override;
      bool onGetTooltip(::i32 iControl, string &strTooltip) override;
      bool onCalculateDefaultSize(i32_rectangle &rectangleDefaultSize) override;
      void onAdjustWindowSize() override;
      void onSize() override;

   };



} //  namespace innate_subsystem_windows


