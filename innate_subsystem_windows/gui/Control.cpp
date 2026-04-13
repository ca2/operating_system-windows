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
#include "../framework.h"
#include "Control.h"

//namespace windows
//{
namespace innate_subsystem_windows
{

  Control::Control()
//  : m_hwnd(NULL)
  {
  }

  // Control::Control(HWND hwnd)
  // : m_hwnd(hwnd)
  // {
  // }

  Control::~Control()
  {
  }

  // void Control::setWindow(HWND hwnd)
  // {
  //    // Save handle
  //    m_hwnd = hwnd;
  //    // Save pointer to default window proc
  //    m_defWindowProc = (WNDPROC)GetWindowLongPtr(m_hwnd, GWLP_WNDPROC);
  // }


  void Control::setText(const char *text)
  {
     //SetWindowText(m_hwnd, text);
     setWindowText(text);
  }

  void Control::setSignedInt(int value)
  {

     ::string strText;

     strText.formatf("%d", value);

     setText(strText);

  }


  void Control::setUnsignedInt(unsigned int value)
  {

     ::string strText;

     strText.formatf("%u", value);

     setText(strText);

  }

  //
  // FIXME: Stub
  //

  void Control::setTextVerticalAlignment(::innate_subsystem::VerticalAlignment align)
  {
  }



   void Control::setVisible(bool visible)
   {

      if (visible)
      {

         show();

      }
      else
      {

         hide();

      }
      //ShowWindow(m_hwnd, visible ? SW_SHOW : SW_HIDE);
   }


  //
  // FIXME: Stub
  //

  innate_subsystem::VerticalAlignment Control::getTextVerticalAlignment()
  {
     return innate_subsystem::Left;
  }

  // HWND Control::getWindow()
  // {
  //    return m_hwnd;
  // }
  //
  // void Control::setStyle(DWORD style)
  // {
  //    ::SetWindowLong(m_hwnd, GWL_STYLE, style);
  // }
  //
  // DWORD Control::getStyle()
  // {
  //    return ::GetWindowLong(m_hwnd, GWL_STYLE);
  // }
  //
  // void Control::addStyle(DWORD styleFlag)
  // {
  //    DWORD flags = getStyle();
  //    flags |= styleFlag;
  //    setStyle(flags);
  // }
  //
  // void Control::removeStyle(DWORD styleFlag)
  // {
  //    DWORD flags = getStyle();
  //    flags &= ~styleFlag;
  //    setStyle(flags);
  // }
  //
  // bool Control::isStyleEnabled(DWORD styleFlag)
  // {
  //    DWORD flags = getStyle();
  //    return (flags & styleFlag) == styleFlag;
  // }
  //
  // void Control::setExStyle(DWORD style)
  // {
  //    SetWindowLong(m_hwnd, GWL_EXSTYLE, style);
  // }
  //
  // DWORD Control::getExStyle()
  // {
  //    return (DWORD)GetWindowLong(m_hwnd, GWL_EXSTYLE);
  // }
  //
  // void Control::addExStyle(DWORD styleFlag)
  // {
  //    DWORD flags = getExStyle();
  //    flags |= styleFlag;
  //    setExStyle(flags);
  // }
  //
  // void Control::removeExStyle(DWORD styleFlag)
  // {
  //    DWORD flags = getExStyle();
  //    flags &= ~styleFlag;
  //    setExStyle(flags);
  // }
  //
  // bool Control::isExStyleEnabled(DWORD styleFlag)
  // {
  //    DWORD flags = getExStyle();
  //    return (flags & styleFlag) == styleFlag;
  // }

  // void Control::replaceWindowProc(WNDPROC wndProc)
  // {
  //    SetWindowLongPtr(m_hwnd, GWLP_USERDATA, (LONG_PTR)this);
  //    SetWindowLongPtr(m_hwnd, GWLP_WNDPROC, (LONG_PTR)wndProc);
  // }


  // void Control::postUserMessage(unsigned int uMessage, ::wparam wparam, ::lparam lparam)
  // {
  //
  //    m_pparticleThis->po
  //
  // }
  //


} // namespace innate_subsystem_windows


//} // namespace windows

