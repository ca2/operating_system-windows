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

#pragma once

//#include "util/CommonHeader.h"
//#include "../../source/app/apex/operating_system/windows/innate_subsystem_windows/WindowMessageHandler.h"
#include "acme/operating_system/windows/window.h"


namespace subsystem_windows
{


   class CLASS_DECL_SUBSYSTEM_WINDOWS MessageWindow :
      virtual public ::windows::window
   {
   public:
      // messageHandler is an external message handler that replace the
      // wndProc() function on message processing. If
      // messageHandler == 0 the wndProc() function will be used.
      //MessageWindow(const HINSTANCE hinst, const char *windowClassName,
        //            WindowMessageHandler *messageHandler = 0);
      //MessageWindow(const char *windowClassName,
        //            WindowMessageHandler *messageHandler = 0);
      MessageWindow();
      ~MessageWindow() override;

      virtual bool createMessageWindow(const ::scoped_string & scopedstrWindowClassName = {}, ::subsystem::WindowMessageHandler *messageHandler = nullptr);
      virtual void destroyWindow();

      //HWND getHWND() const { return m_hwnd; }

   //protected:
      // Function must return true value if the message has been processed.
      virtual bool wndProc(::lresult & lresult, unsigned int message, ::wparam wparam, ::lparam lparam) { return false; }

      virtual bool on_window_procedure(::lresult & lresult, unsigned int message, ::wparam wparam, ::lparam lparam);

      //HWND m_hwnd;
      ::pointer < ::subsystem::WindowMessageHandler > m_pwindowmessagehandler;

      //HINSTANCE m_hinst;
      ::string m_strWindowClassName;

   //private:
     // ATOM regClass(HINSTANCE hinst, const char * pszWindowClassName);

      //static LRESULT CALLBACK staticWndProc(HWND hwnd,
        //                                    unsigned int message,
          //                                  WPARAM wparam,
            //                                LPARAM lparam);
   };


} // namespace subsystem_windows




