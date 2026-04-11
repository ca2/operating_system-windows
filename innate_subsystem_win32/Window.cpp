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
#include "drawing/Bitmap.h"
#include "drawing/Brush.h"
#include "drawing/DeviceContext.h"
#include "drawing/Graphics.h"

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

   void Window::setClipboardViewerInterest()
   {

      m_bHasClipboardViewerInterest = true;

   }


   bool Window::onDrawClipboard()
   {


      return m_pcomposite->onDrawClipboard();

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


   void Window::setShowCursor(bool bShowCursor)
   {

      m_bShowCursor = bShowCursor;

   }


   bool Window::shouldShowCursor()
   {

      return m_bShowCursor;

   }


   void Window::setDoubleBuffering(bool bDoubleBuffering)
   {

      m_bDoubleBuffering = bDoubleBuffering;

   }


   bool Window::isDoubleBuffering()
   {

      return m_bDoubleBuffering;

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
      SetClassLongPtr(m_windowswindow.as_HWND(), GCLP_HCURSOR, (LONG_PTR)hcursor);
   }

   void Window::setClassBackground(::innate_subsystem::BrushInterface *)
   {
      //auto pbrushWin32 = pbrush->impl<::innate_subsystem_win32::Brush>();
      //auto hbrush = (HBRUSH) (HGDIOBJ) pbrush->_HGDIOBJ();
      //auto hbrush = pbrushWin32->m_pbrush->Get
      auto hbrush = (HBRUSH) ::CreateSolidBrush(::GetSysColor(COLOR_WINDOW));
      _ASSERT(m_windowswindow.as_HWND() != 0);
      SetClassLongPtr(m_windowswindow.as_HWND(), GCLP_HBRBACKGROUND, (LONG_PTR) hbrush);
   }

   void Window::setClassMenu(::innate_subsystem::MenuInterface * pmenu)
   {
      auto hmenu = (HMENU) pmenu->_HMENU();
      _ASSERT(m_windowswindow.as_HWND() != 0);
      SetClassLongPtr(m_windowswindow.as_HWND(), GCLP_MENUNAME,(LONG_PTR) hmenu);
   }


   long long Window::getStyle()
   {
      _ASSERT(m_windowswindow.as_HWND() != 0);
      return GetWindowLong(m_windowswindow.as_HWND(), GWL_STYLE);
   }


   void Window::setStyle(unsigned int style)
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


   long long Window::getExStyle()
   {
      _ASSERT(m_windowswindow.as_HWND() != 0);
      return GetWindowLong(m_windowswindow.as_HWND(), GWL_EXSTYLE);
   }

   void Window::setExStyle(unsigned int exstyle)
   {
      _ASSERT(m_windowswindow.as_HWND() != 0);
      SetWindowLong(m_windowswindow.as_HWND(), GWL_EXSTYLE, exstyle);
   }

   void Window::updateWindow()
   {
      _ASSERT(m_windowswindow.as_HWND() != 0);
      UpdateWindow(m_windowswindow.as_HWND());
   }

   void Window::setTimer(::uptr ident, unsigned int time)
   {
      _ASSERT(m_windowswindow.as_HWND() != 0);
      SetTimer(m_windowswindow.as_HWND(), ident, time, 0);
   }

   void Window::killTimer(::uptr ident)
   {
      _ASSERT(m_windowswindow.as_HWND() != 0);
      KillTimer(m_windowswindow.as_HWND(), ident);
   }

   bool Window::onCommand(::wparam wparam, ::lparam lparam)
   {
      return false;
   }

   // bool Window::onNotify(int idCtrl, LPNMHDR pnmh)
   // {
   //    return false;
   // }
   //
   bool Window::onSysCommand(::wparam wparam, ::lparam lparam)
   {
      return false;
   }

   bool Window::onMessage(unsigned int message, ::wparam wparam, ::lparam lparam)
   {
      return false;
   }

   // void * Window::_HWND() const
   // {
   //
   //    return m_windowswindow.as_HWND();
   //
   // }
   //
   //
   // void Window::_setHWND(void * p)
   // {
   //
   //    m_windowswindow = (HWND) p;
   //
   // }
   //
   //
   // void Window::_setHen(HWND hwnd)
   // {
   //    m_windowswindow.as_HWND() = hwnd;
   // }
   //
   // HWND Window::getHWnd() const
   // {
   //    return m_windowswindow.as_HWND();
   // }

   void Window::setWindowText(const ::scoped_string & scopedstr)
   {
      ::wstring wstr(scopedstr);
      _ASSERT(m_windowswindow.as_HWND() != 0);
      SetWindowText(m_windowswindow.as_HWND(), wstr);
   }

   void Window::redraw(const ::int_rectangle &rcArea)
   {
      _ASSERT(m_windowswindow.as_HWND() != 0);

      if (rcArea == 0) {
         InvalidateRect(m_windowswindow.as_HWND(), NULL, TRUE);
      } else {

         RECT rc;
         ::copy(rc, rcArea);
         InvalidateRect(m_windowswindow.as_HWND(), &rc, FALSE);
      }
   }

   bool Window::onMouse(unsigned char msg, unsigned short wspeed, const ::int_point & point)
   {
      return false;
   }

   void Window::setForegroundWindow()
   {
      _ASSERT(m_windowswindow.as_HWND() != 0);

      SetForegroundWindow(m_windowswindow.as_HWND());
   }


   void Window::setFocus()
   {
      ::SetFocus(m_windowswindow.as_HWND());
   }

   bool Window::hasFocus()
   {
      return (::GetFocus() == m_windowswindow.as_HWND()) || (GetForegroundWindow() == m_windowswindow.as_HWND());
   }

   bool Window::setForeground()
   {
      return SetForegroundWindow(m_windowswindow.as_HWND()) != 0;
   }

   bool Window::isEnabled()
   {
      return (!isStyleEnabled(WS_DISABLED));
   }

   bool Window::isIconic()
   {
      return ::IsIconic(m_windowswindow.as_HWND()) != FALSE;
   }

   void Window::invalidate()
   {
      InvalidateRect(m_windowswindow.as_HWND(), NULL, TRUE);
   }

   ::string Window::getText()
   {

      int length = (int)SendMessage(m_windowswindow.as_HWND(), WM_GETTEXTLENGTH, 0, 0);

      ::wstring wstr;

      GetWindowText(m_windowswindow.as_HWND(), wstr.auto_release_buffer(length), length + 1);

      return wstr;

   }


   void Window::postMessage(unsigned int Msg, ::wparam wparam, ::lparam lparam)
   {

      _ASSERT(m_windowswindow.as_HWND() != 0);

      PostMessage(m_windowswindow.as_HWND(), Msg, wparam, lparam);

   }


   void Window::getClientRect(::int_rectangle & rectangle)
   {

      _ASSERT(m_windowswindow.as_HWND() != 0);

      RECT rect{};

      GetClientRect(m_windowswindow.as_HWND(), &rect);

      ::copy(rectangle, rect);

   }


   ::int_size Window::getBorderSize()
   {

      _ASSERT(m_windowswindow.as_HWND() != 0);

      auto width = 2 * GetSystemMetrics(SM_CXSIZEFRAME);

      auto height = GetSystemMetrics(SM_CYSIZE) +
                2 * GetSystemMetrics(SM_CYSIZEFRAME);

      return {width, height};

   }


   bool Window::onCreate(void * pCreateStruct)
   {

      return m_pcomposite->onCreate(pCreateStruct);;

   }



   void Window::_defer_update_double_buffering()
   {

      if (!m_bDoubleBuffering)
      {

         return;

      }

      if (m_pdevicecontextBuffer && m_sizeBuffer == m_clientArea.size())
      {

          return;
      }

      if (m_pdevicecontextBuffer && m_pdevicecontextBuffer->m_pgraphics)
      {
         m_pdevicecontextBuffer->destroyDeviceContext();
          if (m_hbitmapOld)
          {
              SelectObject(m_hdcBuffer, m_hbitmapOld);
          }
          ::DeleteDC(m_hdcBuffer);
      }

      m_sizeBuffer = m_clientArea.size();

      m_hdcBuffer = CreateCompatibleDC(m_paintStruct.hdc);
      void *pBits = nullptr;

      // 2️⃣ Create 32-bit DIB section (alpha preserved)
      BITMAPINFO bi = {};
      bi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
      bi.bmiHeader.biWidth = m_sizeBuffer.cx;
      bi.bmiHeader.biHeight = -m_sizeBuffer.cy; // top-down
      bi.bmiHeader.biPlanes = 1;
      bi.bmiHeader.biBitCount = 32;
      bi.bmiHeader.biCompression = BI_RGB;
      m_hbitmapBuffer = CreateDIBSection(m_paintStruct.hdc, &bi, DIB_RGB_COLORS, &pBits, nullptr, 0);
      m_hbitmapOld = (HBITMAP)SelectObject(m_hdcBuffer, m_hbitmapBuffer);

      // 1️⃣ Create memory DC
      defer_constructø(m_pbitmapBuffer);
      m_pbitmapBuffer->_initialize_bitmap(m_hbitmapBuffer, nullptr);

      defer_constructø(m_pdevicecontextBuffer);
      m_pdevicecontextBuffer->initialize_device_context(m_pbitmapBuffer);

      // 3️⃣ Clear buffer (transparent black)
    //  ZeroMemory(pBits, m_sizeBuffer.area() * 4);
   }


   void Window::onDraw(::innate_subsystem::GraphicsInterface * pgraphics, const ::int_rectangle & rectangle)
   {

      m_pcomposite->onDraw(pgraphics, rectangle);


   }

   // void DesktopWindow::onPaint(DeviceContext *dc, PAINTSTRUCT *paintStruct)
   void Window::doPaint()
   {

      ::int_rectangle paintRect(m_paintStruct.rcPaint);


      // 5️⃣ Blit to screen (alpha ignored in normal window)


      // Cleanup
      // SelectObject(hdcMem, hOld);
      // DeleteObject(hBmp);
      // DeleteDC(hdcMem);

      // EndPaint(hwnd, &ps);
      if (paintRect.is_empty())
      {

         return;
      }

      if (m_clientArea.is_empty())
      {
         return;
      }


      _defer_update_double_buffering();


      //onDraw(m_hdcBuffer, m_paintStruct.rcPaint);

      ::int_rectangle r;

      copy(r, m_paintStruct.rcPaint);

      ::innate_subsystem_win32::Graphics g;

      g.m_pdevicecontext = m_pdevicecontextBuffer;

      onDraw(&g, r);

      ::BitBlt(
         m_paintStruct.hdc,
         m_paintStruct.rcPaint.left,
         m_paintStruct.rcPaint.top,
         ::width(m_paintStruct.rcPaint),
         ::height(m_paintStruct.rcPaint),
         m_hdcBuffer,
         m_paintStruct.rcPaint.left,
         m_paintStruct.rcPaint.top,
         SRCCOPY);

   }



   //bool Window::on_window_procedure(LRESULT & lresult, HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
   bool Window::on_window_procedure(::lresult & lresult, unsigned int message, ::wparam wparam, ::lparam lparam)
   {

      if (m_pcomposite)
      {

         if (m_pcomposite->on_window_procedure(lresult, message, wparam, lparam))
         {

            return true;

         }

      }

      switch (message)
      {
         case WM_CREATE:
         {

            if (m_bHasClipboardViewerInterest)
            {

               m_hwndNextViewer = SetClipboardViewer((HWND)_HWND());

            }

         }
            break;
         case WM_CHANGECBCHAIN:
            {
            if (m_bHasClipboardViewerInterest)
            {
               if ((HWND)wparam.m_number == m_hwndNextViewer)
               {
                  m_hwndNextViewer = (HWND)lparam.m_lparam;
               }
               else if (m_hwndNextViewer != NULL)
               {
                  SendMessage(m_hwndNextViewer, message, wparam, lparam);
               }
            }
            return true;
      }
         case WM_DRAWCLIPBOARD:
         {
            if (m_bHasClipboardViewerInterest)
            {
               bool ok = onDrawClipboard();
               SendMessage(m_hwndNextViewer, message, wparam, lparam);
               return ok;
            }
         }
break;
      case WM_GETDLGCODE:
         {

            bool bWeWantWMKEYDOWNWhenEnterIsPressed = this->we_want_WM_KEYDOWN_when_enter_is_pressed();

            if (bWeWantWMKEYDOWNWhenEnterIsPressed)
            {

               lresult = CallWindowProc(m_wndprocDefault, m_windowswindow.as_HWND(), message, wparam, lparam);

               auto pmsg = lparam.raw_cast<MSG*>();
               // We want WM_KEYDOWN scopedstrMessage when enter is pressed
               if (pmsg &&
                  pmsg->message == WM_KEYDOWN &&
                  pmsg->wParam == VK_RETURN)
               {
                  lresult = DLGC_WANTMESSAGE;
               }
               return true;

            }
            return false;

         }
            case WM_SETCURSOR:
                //if (m_bShowCursor || m_timeStartDesktopWindow.elapsed() < 8_s)
               if (m_bShowCursor)
                {
                    ::SetCursor(LoadCursor(nullptr, IDC_ARROW));
                }
                else
                {
                    ::SetCursor(nullptr);
                }
                return true;

      case WM_COMMAND:
         return onCommand(wparam, lparam);
      case WM_NOTIFY:
      {
         if (_000OnNotify(lresult, wparam, lparam))
         {

            return true;

         }
         // auto hwndFrom = lpnmhdr->hwndFrom;
         //
         // if (hwndFrom)
         // {
         //    lresult = ::SendMessage(hwndFrom, WM_REFLECT_NOTIFY, wparam, lparam);
         //    return true;
         // }

      }
      case WM_SYSCOMMAND:
         return onSysCommand(wparam, lparam);
      case WM_REFLECT_NOTIFY_EX:
         {

            auto pnotify = lparam.raw_cast<windows_reflect_notify_t *>();

            _000OnNotifyReflect(*pnotify);

            lresult = 0;

            return true;

         }
         break;
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

         mouseButtons |= LOWORD(wparam) & MK_RBUTTON ? innate_subsystem::e_mouse_right : 0;
         mouseButtons |= LOWORD(wparam) & MK_MBUTTON ? innate_subsystem::e_mouse_middle : 0;
         mouseButtons |= LOWORD(wparam) & MK_LBUTTON ? innate_subsystem::e_mouse_left : 0;

         // Translate position from ::lparam to POINT.
         POINTS points = MAKEPOINTS(lparam);
         ::int_point point;
         point.x = points.x;
         point.y = points.y;

         unsigned short wheelSpeed = 0;
         if (message == WM_MOUSEWHEEL) {
            // Get speed wheel and set mouse button.
            signed short wheelSignedSpeed = static_cast<signed short>(HIWORD(wparam));
            if (wheelSignedSpeed < 0) {
               mouseButtons |= ::innate_subsystem::e_mouse_wheel_down;
               wheelSpeed = -wheelSignedSpeed / WHEEL_DELTA;
            }
            else {
               mouseButtons |= ::innate_subsystem::e_mouse_wheel_up;
               wheelSpeed = wheelSignedSpeed / WHEEL_DELTA;
            }

            // In some cases wheelSignedSpeed can be smaller than the WHEEL_DELTA,
            // then wheelSpeed set to 1, but not 0.
            if (wheelSpeed == 0) {
               wheelSpeed = 1;
            }

            // If windows-message is WHEEL, then need to translate screen coordinate to client.
            POINT p;
            ::copy(p, point);
            if (!ScreenToClient(m_windowswindow.as_HWND(), &p)) {
               p.x = -1;
               p.y = -1;
            }
            ::copy(point, p);
         }

         // Notify window about mouse-event.
         return onMouse(mouseButtons, static_cast<unsigned short>(wheelSpeed), point);
      }
      }
      return onMessage(message, wparam, lparam);
   }


   bool notification_handler::_000OnNotify(::lresult &lresult, wparam wparam, lparam lparam)
   {

      auto iControl = LOWORD(wparam);

      auto lpnmhdr = (LPNMHDR) lparam.m_lparam;

      ::cast < ::innate_subsystem_win32::Window > pwindowWin32 = this->get_window_implementation();

      auto &notification = pwindowWin32->m_mapControlNotification[iControl];

      if (notification.m_econtrol != ::innate_subsystem::e_control_none)
      {

         int iOperatingSystemNotificationCode = lpnmhdr->code;

         if (notification.m_iaNotification.contains(iOperatingSystemNotificationCode))
         {

            windows_reflect_notify_t notify(lresult, wparam, lparam);

            _000OnNotify(notify);

         // }
         //
         //    bool bHandled = _this->_onNotify(iControl, lpnmhdr);
            if (!notify.m_bHandled)
            {
               // windows_reflect_notify_t notify;
               // notify.m_bHandled = false;
               // notify.set_wparam(wparam);
               // notify.m_lresult = 0;
               // notify.m_lpnmhdr = lpnmhdr;
               SendMessage(lpnmhdr->hwndFrom, WM_REFLECT_NOTIFY_EX, 0,(LPARAM) &notify);
               //if (bHandled && notify.m_bHandled)
               //{
                  //bResult = notify.m_lresult;
               //}
               //bResult = true;
            }

            if (notify.m_bHandled)
            {

               return true;

            }

         }

      }

      return false;

   }


   void notification_handler::_000OnNotify(windows_reflect_notify_t & notify)
   {
      //return false;
   }

} // namespace innate_subsystem_win32
// } // namespace windows
//
