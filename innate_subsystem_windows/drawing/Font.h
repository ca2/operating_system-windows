// Copyright (C) 2009,2010,2011,2012 GlavSoft LLC.
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
// From Pen.h by camilo on 2026-04-11 04:18 <3ThomasBorregaardSørensen!!
#pragma once

#include "innate_subsystem/drawing/Font.h"
#include "subsystem_windows/_common_header.h"
#include <Gdiplus.h>

//#include "util/CommonHeader.h"

namespace innate_subsystem_windows
{





   class CLASS_DECL_INNATE_SUBSYSTEM_WINDOWS Font :
virtual public ::subsystem::implementation<::innate_subsystem::FontInterface>
   {
   public:

      //public:
      //Pen(int type, int width, const ::color::color & color);
      Font();
      ~Font() override;


      //void * _HGDIOBJ() override;

      virtual void initialize_font(const char * pszFamily, int iPixelHeight, int iFontWeight = 400, bool bItalic = false) override;

      void destroyGraphicsObject() override;

      // protected:
      //    HPEN m_pen;
      //
      //    friend class Graphics;
      Gdiplus::Font * m_pfont;
   };


//#endi
//   } // namespace innate_subsystem
} // namespace innate_subsystem

