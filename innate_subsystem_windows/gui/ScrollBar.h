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
#pragma once
//#ifndef _SCROLL_BAR_H_
//#define _SCROLL_BAR_H_

#include "innate_subsystem/gui/ScrollBar.h"
#include "innate_subsystem_windows/_common_header.h"
#include "innate_subsystem_windows/gui/Window.h"


namespace  innate_subsystem_windows
{
   // ScrollBar class
   // This class doesn't create any window, it only show/hide that is already
   // contained in existed window.

   class CLASS_DECL_INNATE_SUBSYSTEM_WINDOWS ScrollBar :
   virtual public window_implementation<innate_subsystem::ScrollBarInterface, Window>
   {
   public:
      ScrollBar();

      //void setWindow(HWND hwnd) override;
      bool showVertScroll(bool show) override;
      bool showHorzScroll(bool show) override;
      void setHorzRange(::i32 imin, ::i32 imax, ::i32 istep) override;
      void setVertRange(::i32 imin, ::i32 imax, ::i32 istep) override;
      void setVertPos(::i32 iPos) override;
      void setHorzPos(::i32 iPos) override;
      void moveUpVert(::i32 iPercent = 0) override;
      void moveDownVert(::i32 iPercent = 0) override;
      void moveLeftHorz(::i32 iPercent = 0) override;
      void moveRightHorz(::i32 inPercent = 0) override;
      ::i32 getVertPos() override;
      ::i32 getHorzPos() override;
      ::i32 getVerticalSize() override;
      ::i32 getHorizontalSize() override;

      static const ::i32 SCROLL_STEP = 5 ;
   //protected:
      void enableVirtualScroll() override;
      void disableVirtualScroll() override;
      bool _showVertScroll(bool show) override;
      bool _showHorzScroll(bool show) override;

      //HWND m_hwnd;
      ::i32 m_vPos, m_hPos;
      ::i32 m_vMin, m_vMax;
      ::i32 m_hMin, m_hMax;
      ::i32 m_vStep;
      ::i32 m_hStep;
      bool m_isVirtualScroll;
      bool m_isVert;
      bool m_isHorz;
      bool m_isVVert;
      bool m_isVHorz;
   };


} // namespace ininnate_subsystem_win32