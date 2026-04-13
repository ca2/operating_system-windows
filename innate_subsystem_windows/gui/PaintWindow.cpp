// Copyright (C) 2012 GlavSoft LLC.
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
#include "PaintWindow.h"
#include "drawing/DeviceContext.h"

namespace innate_subsystem_windows
   {
      PaintWindow::PaintWindow()
       : m_bIsDraw(false)
      {
      }

      PaintWindow::~PaintWindow()
      {
      }

      ::pointer < innate_subsystem::DeviceContextInterface > PaintWindow::getPaintDeviceContext()
      {
         if (!m_bIsDraw) {
            return 0;
         }
         return m_pdevicecontext;
      }

      void PaintWindow::onPaint(DeviceContext *dc, PAINTSTRUCT *paintStruct) {
      }

      // bool PaintWindow::wndProc(unsigned int message, ::wparam wparam, ::lparam lparam)
      // {
      //    if (message == WM_PAINT) {
      //       construct_newø(m_pdevicecontext);
      //       auto hwnd = ::as_HWND(operating_system_window());
      //       m_pdevicecontext->m_hdc = BeginPaint(hwnd, &m_paintStruct);
      //       m_bIsDraw = true;
      //       //DeviceContext dc(this);
      //       onPaint(m_pdevicecontext, &m_paintStruct);
      //       EndPaint(hwnd, &m_paintStruct);
      //       m_bIsDraw = false;
      //       return true;
      //    }
      //    return Window::wndProc(message, wparam, lparam);
      // }
   } // namespace innate_subsystem_windows
