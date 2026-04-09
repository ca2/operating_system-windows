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
#include "Graphics.h"
#include "DeviceContext.h"
#include "Bitmap.h"
#include "Brush.h"
#include "Pen.h"


namespace innate_subsystem_win32
{
   // Graphics::Graphics(DeviceContext *dc)
   // : m_dc(dc)
   // {
   // }

   Graphics::Graphics()
   {

   }


   Graphics::~Graphics()
   {
   }


   innate_subsystem::DeviceContextInterface * Graphics::device_context()
   {

return m_pdevicecontext;

   }


   void Graphics::initialize_graphics(innate_subsystem::DeviceContextInterface * pdevicecontext)
   {

      m_pdevicecontext = pdevicecontext;

   }

   void Graphics::setBkMode(bool transparent)
   {
      SetBkMode(m_pdevicecontext->m_hdc, transparent ? TRANSPARENT : OPAQUE);
   }

   void Graphics::setTextColor(const ::color::color & color)
   {
      SetTextColor(m_pdevicecontext->m_hdc, RGB(color.byte_red(), color.byte_green(), color.byte_blue()));
   }

   void Graphics::setBkColor(const ::color::color & color)
   {
      SetBkColor(m_pdevicecontext->m_hdc, RGB(color.byte_red(), color.byte_green(), color.byte_blue()));
   }

   void Graphics::setBrush(::innate_subsystem::BrushInterface *pbrush)
   {

      // auto pbrushWin32 = pbrush->impl<Brush>();
      //
      // HGDIOBJ object = pbrushWin32 ? pbrushWin32->m_hbrush : nullptr;
      //
      m_pdevicecontext->selectObject(pbrush);

   }

   void Graphics::setPen(::innate_subsystem::PenInterface *ppen)
   {

      // ::cast < ::innate_subsystem_win32::Pen > ppenWin32 = ::innate_subsystem::get_implementation(ppen);
      //
      // HGDIOBJ object = ppenWin32 ? ppenWin32->m_hpen : nullptr;
      //
      m_pdevicecontext->selectObject(ppen);

   }

   void Graphics::moveTo(int x, int y)
   {
      MoveToEx(m_pdevicecontext->m_hdc, x, y, NULL);
   }

   void Graphics::lineTo(int x, int y)
   {
      LineTo(m_pdevicecontext->m_hdc, x, y);
   }

   void Graphics::fillRect(int l, int t, int r, int b, ::innate_subsystem::BrushInterface *pbrush)
   {
      RECT rect;

      rect.top = t;
      rect.left = l;
      rect.bottom = b;
      rect.right = r;


      auto hbrush = (HBRUSH) pbrush->_HGDIOBJ();


      FillRect(m_pdevicecontext->m_hdc, &rect, hbrush);

   }


   void Graphics::ellipse(int l, int t, int r, int b)
   {
      Ellipse(m_pdevicecontext->m_hdc, l, t, r, b);
   }

   void Graphics::rectangle(int l, int t, int r, int b)
   {
      Rectangle(m_pdevicecontext->m_hdc, l, t, r, b);
   }

   void Graphics::drawBitmap(::innate_subsystem::BitmapInterface *pbitmap, int x, int y, int w, int h)
   {
      DeviceContext memDC;

      memDC.initialize_device_context(m_pdevicecontext);

      auto pobjOld = memDC.selectObject(pbitmap);

      BitBlt(m_pdevicecontext->m_hdc, x, y, w, h, memDC.m_hdc, 0, 0, SRCCOPY);

      memDC.selectObject(pobjOld);
   }

   void Graphics::drawText(const char *text, int cchText, ::int_rectangle &rect, unsigned int format)
   {

      ::string str;

      if (cchText >= 0)
      {

         str.assign(text, cchText);

      }
      else
      {

         str = text;

      }

      ::wstring wstr(str);

      RECT rc;
      ::copy(rc, rect);
      DrawText(m_pdevicecontext->m_hdc, wstr, wstr.length(), &rc, format);
   }

   
} // namespace innate_subsystem_win32


