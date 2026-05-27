// Copyright (C) 2009,2010,2011,2012 GlavSoft LLC.
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
// Adapted by camilo on beginning of 2026-April <3ThomasBorregaardSorensen!!
//
#pragma once


#include "innate_subsystem/drawing/Pen.h"
#include "subsystem_windows/_common_header.h"
#include <Gdiplus.h>

namespace innate_subsystem_windows
{

   class Pen :
      virtual public Implementation<::innate_subsystem::PenInterface>
   {
   public:
      // const static ::i32 SOLID_TYPE = PS_SOLID;
      // const static ::i32 DASH_TYPE = PS_DASH;
      // const static ::i32 NULL_TYPE = PS_NULL;
      //
   //public:
      ///Pen(::i32 type, ::i32 width, COLORREF color);
      Pen();
      ~Pen() override;


      //void * _HGDIOBJ() override;


      void initialize_pen(innate_subsystem::enum_pen epen, ::i32 width, const color::color& color) override;


      void destroyGraphicsObject() override;

   // protected:
       //HPEN m_hpen;
      Gdiplus::Pen * m_ppen;
   //
   //    friend class Graphics;
   };

//#endi
} // namespace innate_subsystem_windows

