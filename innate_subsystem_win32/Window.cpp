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
#include "framework.h"
//#include "util/CommonHeader.h"
#include "Window.h"
#include "drawing/Cursor.h"
#include "drawing/Icon.h"
#include "Menu.h"

#include "apex/innate_subsystem/drawing/Brush.h"

// namespace windows
// {
namespace innate_subsystem_win32
{
   Window::Window()
      : // m_windowswindow.as_HWND()(0),
   //   m_hicon(0),
      m_bWndCreated(false)
   {
   }

   Window::~Window()
   {
      // if (m_bWndCreated && m_windowswindow.as_HWND()) {
      //    DestroyWindow(m_windowswindow.as_HWND());
      // }
      // if (m_hicon) {
      //    DeleteObject(m_hicon);
      // }
   }


   void * Window::_HWND() const
   {

      return m_windowswindow.as_HWND();

   }
   void Window::_setHWND(void * p)
   {

      m_windowswindow = (HWND) p;

   }


   void *Window::_WNDPROC_default() const
   {

      return m_wndprocDefault;

   }


   operating_system::window Window::operating_system_window() const
   {

      return m_windowswindow.as_operating_system_window();

   }


   void Window::set_operating_system_window(const operating_system::window &operatingsystemwindow)
   {

      m_windowswindow = operatingsystemwindow;

   }


   innate_subsystem::WindowInterface *Window::get_window_implementation()
   {

      return this;

   }


   void Window::setClass(const ::scoped_string  & scopedstrWindowClassName)
   {
      m_strClassName = scopedstrWindowClassName;
   }

   bool Window::createWindow(const ::scoped_string & scopedstrWindowName, unsigned int style, const ::operating_system::window & operatingsystemwindowParent,
                                 int xPos, int yPos, int width, int height)
   {
      if (m_windowswindow.is_set()) {
         return false;
      }
      m_strWindowName = scopedstrWindowName;
      auto hwndParent = ::as_HWND(operatingsystemwindowParent);
      HWND hwnd = CreateWindow(::wstring(m_strClassName),
                            ::wstring(m_strWindowName),
                            style,
                            xPos, yPos,
                            width, height,
                            hwndParent,
                            0,
                            GetModuleHandle(0),
                            reinterpret_cast<LPVOID>((::windows::window *)this));
      m_bWndCreated = (hwnd == 0 ? false : true);
      if (m_bWndCreated) {

         m_wndprocDefault = (WNDPROC)GetWindowLongPtr(hwnd, GWLP_WNDPROC);
         SetWindowLongPtr(hwnd,
                          GWLP_USERDATA,
                          reinterpret_cast<LONG_PTR>(this));
      }
      return true;
   }

   void Window::loadIcon(unsigned int id)
   {
      if (m_hicon) {
         DeleteObject(m_hicon);
         m_hicon = 0;
      }
      if (IS_INTRESOURCE(id)) {
         m_hicon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(id));
         SetClassLongPtr(m_windowswindow.as_HWND(), GCLP_HICON, reinterpret_cast<LONG_PTR>(m_hicon));
      } else {
         SetClassLongPtr(m_windowswindow.as_HWND(), GCLP_HICON, static_cast<LONG_PTR>(id));
      }
   }

   void Window::enableWindow(bool bEnable)
   {
      _ASSERT(m_windowswindow.as_HWND() != 0);
      EnableWindow(m_windowswindow.as_HWND(), bEnable);
   }

   void Window::setEnabled(bool enabled)
   {
      if (enabled) {
         SendMessage(m_windowswindow.as_HWND(), WM_ENABLE, TRUE, NULL);
         removeStyle(WS_DISABLED);
      } else {
         if (isStyleEnabled(WS_DISABLED)) {
            return ;
         } // if already disabled
         SendMessage(m_windowswindow.as_HWND(), WM_ENABLE, FALSE, NULL);
         addStyle(WS_DISABLED);
      }
      invalidate();
   }


   bool Window::destroyWindow()
   {
      if (m_windowswindow.as_HWND()) {
         DestroyWindow(m_windowswindow.as_HWND());
         return true;
      }
      return false;
   }

   void Window::show()
   {
      _ASSERT(m_windowswindow.as_HWND() != 0);
      ShowWindow(m_windowswindow.as_HWND(), SW_SHOW);
   }

   void Window::hide()
   {
      _ASSERT(m_windowswindow.as_HWND() != 0);
      ShowWindow(m_windowswindow.as_HWND(), SW_HIDE);
   }

   bool Window::setSize(const ::int_size & size)
   {
      _ASSERT(m_windowswindow.as_HWND() != 0);
      return !!SetWindowPos(m_windowswindow.as_HWND(), 0, 0, 0, size.cx, size.cy,
                            SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE);
   }

   bool Window::setPosition(int xPos, int yPos)
   {
      _ASSERT(m_windowswindow.as_HWND() != 0);
      return !!SetWindowPos(m_windowswindow.as_HWND(), 0, xPos, yPos, 0, 0,
                            SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE);
   }

   void Window::setParent(const ::operating_system::window & operatingsystemwindow)
   {
      _ASSERT(m_windowswindow.as_HWND() != 0);
      SetParent(m_windowswindow.as_HWND(), as_HWND(operatingsystemwindow));
   }


   ::operating_system::window Window::dialog_item_operating_system_window(int iDlgItem)
   {

      _ASSERT(m_windowswindow.as_HWND() != 0);
      auto hwndChild = ::GetDlgItem(m_windowswindow.as_HWND(), iDlgItem);
      return ::as_operating_system_window(hwndChild);
   }

   void Window::setClassStyle(unsigned int style)
   {
      _ASSERT(m_windowswindow.as_HWND() != 0);
      SetClassLong(m_windowswindow.as_HWND(), GCL_STYLE, style);
   }

   void Window::setClassCursor(::innate_subsystem::CursorInterface * pcursor)
   {
      auto hcursor = pcursor->_HCURSOR();
      _ASSERT(m_windowswindow.as_HWND() != 0);
      SetClassLongPtr(m_windowswindow.as_HWND(), GCLP_HCURSOR, reinterpret_cast<LONG_PTR>(hcursor));
   }

   void Window::setClassBackground(::innate_subsystem::BrushInterface * pbrush)
   {
      auto hbrush = (HBRUSH) (HGDIOBJ) pbrush->_HGDIOBJ();
      _ASSERT(m_windowswindow.as_HWND() != 0);
      SetClassLongPtr(m_windowswindow.as_HWND(), GCLP_HBRBACKGROUND, reinterpret_cast<LONG_PTR>(hbrush));
   }

   void Window::setClassMenu(::innate_subsystem::MenuInterface * pmenu)
   {
      auto hbrush = (HBRUSH) (HGDIOBJ) pmenu->_HGDIOBJ();
      _ASSERT(m_windowswindow.as_HWND() != 0);
      SetClassLongPtr(m_windowswindow.as_HWND(), GCLP_MENUNAME, menu);
   }

   LONG Window::getStyle()
   {
      _ASSERT(m_windowswindow.as_HWND() != 0);
      return GetWindowLong(m_windowswindow.as_HWND(), GWL_STYLE);
   }

   void Window::setStyle(DWORD style)
   {
      _ASSERT(m_windowswindow.as_HWND() != 0);
      SetWindowLong(m_windowswindow.as_HWND(), GWL_STYLE, style);
   }


   void Window::addStyle(unsigned int styleFlag)
   {
      DWORD flags = getStyle();
      flags |= styleFlag;
      setStyle(flags);
   }


   LONG Window::getExStyle()
   {
      _ASSERT(m_windowswindow.as_HWND() != 0);
      return GetWindowLong(m_windowswindow.as_HWND(), GWL_EXSTYLE);
   }

   void Window::setExStyle(DWORD exstyle)
   {
      _ASSERT(m_windowswindow.as_HWND() != 0);
      SetWindowLong(m_windowswindow.as_HWND(), GWL_EXSTYLE, exstyle);
   }

   void Window::updateWindow()
   {
      _ASSERT(m_windowswindow.as_HWND() != 0);
      UpdateWindow(m_windowswindow.as_HWND());
   }

   void Window::setTimer(unsigned int_PTR ident, unsigned int time)
   {
      _ASSERT(m_windowswindow.as_HWND() != 0);
      SetTimer(m_windowswindow.as_HWND(), ident, time, 0);
   }

   void Window::killTimer(unsigned int_PTR ident)
   {
      _ASSERT(m_windowswindow.as_HWND() != 0);
      KillTimer(m_windowswindow.as_HWND(), ident);
   }

   bool Window::onCommand(::wparam wparam, ::lparam lparam)
   {
      return false;
   }

   bool Window::onNotify(int idCtrl, LPNMHDR pnmh)
   {
      return false;
   }

   bool Window::onSysCommand(::wparam wparam, ::lparam lparam)
   {
      return false;
   }

   bool Window::onMessage(unsigned int message, ::wparam wparam, ::lparam lparam)
   {
      return false;
   }

   void Window::setHWnd(HWND hwnd)
   {
      m_windowswindow.as_HWND() = hwnd;
   }

   HWND Window::getHWnd() const
   {
      return m_windowswindow.as_HWND();
   }

   void Window::setWindowText(const StringStorage *text)
   {
      _ASSERT(m_windowswindow.as_HWND() != 0);
      SetWindowText(m_windowswindow.as_HWND(), text->getString());
   }

   void Window::redraw(const ::int_rectangle &rcArea)
   {
      _ASSERT(m_windowswindow.as_HWND() != 0);

      if (rcArea == 0) {
         InvalidateRect(m_windowswindow.as_HWND(), NULL, TRUE);
      } else {
         InvalidateRect(m_windowswindow.as_HWND(), rcArea, FALSE);
      }
   }

   bool Window::onMouse(unsigned char msg, unsigned short wspeed, POINT pt)
   {
      return false;
   }

   void Window::setForegroundWindow()
   {
      _ASSERT(m_windowswindow.as_HWND() != 0);

      SetForegroundWindow(m_windowswindow.as_HWND());
   }


   void Control::setFocus()
   {
      ::SetFocus(m_windowswindow.as_HWND());
   }

   bool Control::hasFocus()
   {
      return (::GetFocus() == m_windowswindow.as_HWND()) || (GetForegroundWindow() == m_windowswindow.as_HWND());
   }

   bool Control::setForeground()
   {
      return SetForegroundWindow(getWindow()) != 0;
   }
   bool Control::isEnabled()
   {
      return (!isStyleEnabled(WS_DISABLED));
   }

   void Control::invalidate()
   {
      InvalidateRect(m_windowswindow.as_HWND(), NULL, TRUE);
   }

   void Control::getText(StringStorage *storage)
   {
      int length = (int)SendMessage(m_windowswindow.as_HWND(), WM_GETTEXTLENGTH, 0, 0);
      std::vector<TCHAR> buf(length + 1);
      GetWindowText(m_windowswindow.as_HWND(), &buf.front(), length + 1);
      storage->setString(&buf.front());
   }

   void Window::postMessage(unsigned int Msg, ::wparam wparam, ::lparam lparam)
   {
      _ASSERT(m_windowswindow.as_HWND() != 0);

      PostMessage(m_windowswindow.as_HWND(), Msg, ::wparam, ::lparam);
   }

   void Window::getClientRect(::int_rectangle &rc)
   {
      _ASSERT(m_windowswindow.as_HWND() != 0 && rc);

      GetClientRect(m_windowswindow.as_HWND(), rc);
   }

   void Window::getBorderSize(int *width, int *height)
   {
      _ASSERT(m_windowswindow.as_HWND() != 0);

      *width = 2 * GetSystemMetrics(SM_CXSIZEFRAME);
      *height = GetSystemMetrics(SM_CYSIZE) +
                2 * GetSystemMetrics(SM_CYSIZEFRAME);
   }


   LRESULT Window::s_window_procedure(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
   {

      if (messag)

      if (m_pcomposite)
      {

         if (m_pcomposite->window_procedure)

      }


   }


   bool Window::on_window_procedure(LRESULT &lresult, UINT message, WPARAM wparam, LPARAM lparam)
   {


      switch (message) {
      case WM_GETDLGCODE:
      {

         bool bWeWantWMKEYDOWNWhenEnterIsPressed = this->we_want_WM_KEYDOWN_when_enter_is_pressed();

         if (bWeWantWMKEYDOWNWhenEnterIsPressed)
         {

            lresult = CallWindowProc(m_defWindowProc, m_windowswindow.as_HWND(), uMsg, wparam.m_number, lparam.m_lparam);
            // We want WM_KEYDOWN scopedstrMessage when enter is pressed
            if (lparam.m_lparam &&
               ((MSG*)lparam.m_lparam)->message == WM_KEYDOWN &&
               ((MSG*)lparam.m_lparam)->wParam == VK_RETURN) {
               lresult = DLGC_WANTMESSAGE;
            }
         return true;

         }
         return false;

      }
      case WM_COMMAND:
         return onCommand(wparam, lparam);
      case WM_NOTIFY:
      {
         auto lpnmhdr = (LPNMHDR)lparam;
         if (onNotify((int)wparam, lpnmhdr))
         {

            lresult = 0;
            return true;

         }
         auto hwndFrom = lpnmhdr->hwndFrom;

         if (hwndFrom)
         {
            lresult = ::SendMessage(hwndFrom, WM_REFLECT_NOTIFY, wparam, lparam);
            return true;
         }

      }
      case WM_SYSCOMMAND:
         return onSysCommand(wparam, lparam);
         case WM_REFLECT_NOTIFY:
         {

            if (_onNotifyReflect(wparam, lparam))
            {

               lresult = 0;
               return true;

            }

         }

         case WM_LBUTTONDOWN:
      case WM_LBUTTONUP:
      case WM_MBUTTONDOWN:
      case WM_MBUTTONUP:
      case WM_RBUTTONDOWN:
      case WM_RBUTTONUP:
      case WM_MOUSEWHEEL:
      case WM_MOUSEMOVE:
      {
         unsigned char mouseButtons = 0;

         mouseButtons |= LOWORD(wparam) & MK_RBUTTON ? MOUSE_RDOWN : 0;
         mouseButtons |= LOWORD(wparam) & MK_MBUTTON ? MOUSE_MDOWN : 0;
         mouseButtons |= LOWORD(wparam) & MK_LBUTTON ? MOUSE_LDOWN : 0;

         // Translate position from ::lparam to POINT.
         POINTS points = MAKEPOINTS(lparam);
         POINT point;
         point.x = points.x;
         point.y = points.y;

         unsigned short wheelSpeed = 0;
         if (message == WM_MOUSEWHEEL) {
            // Get speed wheel and set mouse button.
            signed short wheelSignedSpeed = static_cast<signed short>(HIWORD(wparam));
            if (wheelSignedSpeed < 0) {
               mouseButtons |= MOUSE_WDOWN;
               wheelSpeed = -wheelSignedSpeed / WHEEL_DELTA;
            }
            else {
               mouseButtons |= MOUSE_WUP;
               wheelSpeed = wheelSignedSpeed / WHEEL_DELTA;
            }

            // In some cases wheelSignedSpeed can be smaller than the WHEEL_DELTA,
            // then wheelSpeed set to 1, but not 0.
            if (wheelSpeed == 0) {
               wheelSpeed = 1;
            }

            // If windows-message is WHEEL, then need to translate screen coordinate to client.
            if (!ScreenToClient(::as_HWND(m_operatingsystemwindow), &point)) {
               point.x = -1;
               point.y = -1;
            }
         }

         // Notify window about mouse-event.
         return onMouse(mouseButtons, static_cast<unsigned short>(wheelSpeed), point);
      }
      }
      return onMessage(message, wparam, lparam);
   }


   bool notification_handler::_000OnNotify(LRESULT &lresult, wparam wparam, lparam lparam)
   {

      auto iControl = LOWORD(wparam);

      auto lpnmhdr = (LPNMHDR) lparam.m_lparam;

      ::cast < ::innate_subsystem_win32::Window > pwindowWin32 = _this->get_window_implementation();

      auto &notification = pwindowWin32->m_mapControlNotification[iControl];

      if (notification.m_econtrol != ::innate_subsystem::e_control_none)
      {

         int iOperatingSystemNotificationCode = lpnmhdr->code;

         if (notification.m_iaNotification.contains(iOperatingSystemNotificationCode))
         {

            bool bHandled = _000OnNotify(notification.m_econtrol, iControl, lpnmhdr);

         // }
         //
         //    bool bHandled = _this->_onNotify(iControl, lpnmhdr);
            if (!bHandled)
            {
               windows_reflect_notify_t notify;
               notify.m_bHandled = false;
               notify.set_wparam(wparam);
               notify.m_lresult = 0;
               notify.m_lpnmhdr = lpnmhdr;
               bHandled = SendMessage(lpnmhdr->hwndFrom, WM_REFLECT_NOTIFY_EX, 0,(LPARAM) &notify);
               if (bHandled && notify.m_bHandled)
               {
                  bResult = notify.m_lresult;
               }
               //bResult = true;
            }

         }

      }



   }


   bool notification_handler::_000OnNotify(int idCtrl, LPNMHDR lpnmhdr)
   {
      return false;
   }

} // namespace innate_subsystem_win32
// } // namespace windows
//
