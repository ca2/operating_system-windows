// Copyright (C) 2008,2009,2010,2011,2012 GlavSoft LLC.
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
#include "MessageWindow.h"
#include "subsystem/platform/WindowMessageHandler.h"


#define DEFAULT_WINDOW_CLASS_NAME "WindowClass"


namespace subsystem_windows
{


   //MessageWindow::MessageWindow(const HINSTANCE hinst,
   //                             const char *windowClassName,
   //                             WindowMessageHandler *messageHandler)
   //: m_hwnd(0),
   //  m_hinst(hinst),
   //  m_pwindowmessagehandler(messageHandler)
   //{
   //   if (windowClassName != 0) {
   //      m_strWindowClassName = windowClassName;
   //   } else {
   //      m_strWindowClassName = DEFAULT_WINDOW_CLASS_NAME;
   //   }

   //}
   MessageWindow::MessageWindow() :
       //m_hwnd(nullptr), m_hinst(nullptr), m_pwindowmessagehandler(nullptr)
       m_pwindowmessagehandler(nullptr)
   {
      //if (windowClassName != 0)
      //{
        // m_strWindowClassName = windowClassName;
      //}
      //else
      //{
         m_strWindowClassName = DEFAULT_WINDOW_CLASS_NAME;
      //}
   }

   MessageWindow::~MessageWindow(void)
   {
      destroyWindow();

      if (m_strWindowClassName.has_character()) {
         ::wstring wstrWindowClassName;
         wstrWindowClassName = m_strWindowClassName;
         UnregisterClass(wstrWindowClassName,
                         (HINSTANCE)::windows::hinstance_from_function(::windows::window::s_window_procedure));
         m_strWindowClassName.clear();
      }
   }

   bool MessageWindow::createMessageWindow(const ::scoped_string & scopedstrWindowClassName, ::subsystem::WindowMessageHandler *messageHandler)
   {
      if (messageHandler != 0) {
         m_pwindowmessagehandler = messageHandler;
      }

      //::wstring wstrWindowClassName;

      //wstrWindowClassName = m_strWindowClassName;

      if (scopedstrWindowClassName.has_character())
      {

         m_strWindowClassName = scopedstrWindowClassName;

      }

      //auto hinstance = ::windows::hinstance_from_function(::windows::window::s_window_procedure);

      if (!register_window_class(m_strWindowClassName)) {
         return false;
      }

      //::wstring wstrWindowClassName;

      //wstrWindowClassName = m_strWindowClassName;

      auto hinstance = ::windows::hinstance_from_function(::windows::window::s_window_procedure);

      create_window(m_strWindowClassName, "MessageWindow",
                              WS_OVERLAPPEDWINDOW, {-32768, -32768, 0, 0});

      if (m_windowswindow.is_null()) {
         return false;
      }

      SetWindowLongPtr(m_windowswindow.as_HWND(), GWLP_USERDATA, (LONG_PTR) this);
      return true;
   }

   void MessageWindow::destroyWindow()
   {
      if (m_windowswindow.as_HWND()) {
         DestroyWindow(m_windowswindow.as_HWND());
         m_windowswindow = nullptr;
      }
   }


   bool MessageWindow::on_window_procedure(::lresult & lresult, unsigned int message, ::wparam wparam, ::lparam lparam)
   {

      if (m_pwindowmessagehandler)
      {

         lresult = m_pwindowmessagehandler->processMessage((::user::enum_message) message, wparam,  lparam);

         return false;

      }
      else
      {

         return this->wndProc(lresult, message, wparam, lparam);

      }

   }

   // LRESULT CALLBACK MessageWindow::staticWndProc(HWND hwnd, unsigned int message,
   //                                        WPARAM wparam, LPARAM lparam)
   // {
   //    MessageWindow *_this;
   //    if (message == WM_CREATE) {
   //       _this = (MessageWindow *)((CREATESTRUCT *)lparam)->lpCreateParams;
   //       wparam = (WPARAM)hwnd; // Pass hwnd throw ::wparam
   //    } else {
   //       _this = (MessageWindow *)GetWindowLongPtr(hwnd, GWLP_USERDATA);
   //    }
   //    if (_this != NULL) {
   //       bool result;
   //       if (_this->m_pwindowmessagehandler != 0) {
   //          result = _this->m_pwindowmessagehandler->processMessage(message,
   //                                                           wparam,
   //                                                           lparam);
   //       } else {
   //          result = _this->wndProc(message, wparam, lparam);
   //       }
   //       if (result) {
   //          return 0;
   //       }
   //    }
   //
   //    return DefWindowProc(hwnd, message, wparam, lparam);
   // }

   // ATOM MessageWindow::regClass(HINSTANCE hinst, const char *windowClassName)
   // {
   //
   //    ::wstring wstrWindowClassName;
   //
   //    wstrWindowClassName = windowClassName;
   //
   //    WNDCLASS wcWindowClass = {0};
   //    wcWindowClass.lpfnWndProc = staticWndProc;
   //    wcWindowClass.style = NULL;
   //    wcWindowClass.hInstance = m_hinst;
   //    wcWindowClass.lpszClassName = wstrWindowClassName;
   //    wcWindowClass.hCursor = NULL;
   //    wcWindowClass.hbrBackground = (HBRUSH)COLOR_WINDOW;
   //
   //    return RegisterClass(&wcWindowClass);
   // }


} // namespace subsystem_windows



