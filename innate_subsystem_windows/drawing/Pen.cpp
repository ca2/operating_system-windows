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
// Adapted by camilo on beginning of 2026-April <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "Pen.h"

//#include <crtdbg.h>


namespace innate_subsystem_windows
{


   // Pen::Pen(::innate_subsystem::enum_pennt type, int width, COLORREF color)
   // : m_pen(NULL)
   // {
   //    m_pen = CreatePen(type, width, color);
   //
   //    _ASSERT(m_pen != NULL);
   // }

   Pen::Pen():
//   m_hpen(nullptr)
   m_ppen(nullptr)
   {

   }


   Pen::~Pen()
   {

      destroyGraphicsObject();

   }


   // void * Pen::_HGDIOBJ()
   // {
   //
   //    return m_hpen;
   //
   // }

   void Pen::initialize_pen(innate_subsystem::enum_pen epen, int width, const color::color& color)
   {

      destroyGraphicsObject();

      //m_hpen = CreatePen((int) epen, width, RGB(color.byte_red(), color.byte_green(), color.byte_blue()));

      Gdiplus::Color gdipluscolor(color.byte_opacity(), color.byte_red(), color.byte_green(), color.byte_blue());

      m_ppen = new Gdiplus::Pen(gdipluscolor, width);

      if (!m_ppen || m_ppen->GetLastStatus() != Gdiplus::Ok)
      {

         throw ::exception(error_failed);

      }

   }


   void Pen::destroyGraphicsObject()
   {

      if (m_ppen)
      {

         delete m_ppen;

         m_ppen = nullptr;

      }

      // if (m_hpen)
      // {
      //    ::DeleteObject(m_hpen);
      //    m_hpen= nullptr;
      // }

   }


} // namespace innate_subsystem_windows


