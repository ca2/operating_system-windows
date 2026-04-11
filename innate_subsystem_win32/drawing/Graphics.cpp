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
m_iBkMode = TRANSPARENT;
      m_pfont = nullptr;
      m_pbrushText = nullptr;
   }


   Graphics::~Graphics()
   {

      if (m_pfont)
      {

         delete m_pfont;
         m_pfont = nullptr;
      }
      if (m_pbrushText)
      {

         delete m_pbrushText;
         m_pbrushText = nullptr;
      }
   }


   innate_subsystem::DeviceContextInterface * Graphics::device_context()
   {

return m_pdevicecontext;

   }


   void Graphics::initialize_graphics(innate_subsystem::DeviceContextInterface * pdevicecontext)
   {

      m_pdevicecontext = pdevicecontext;

   }

   void Graphics::initialize_graphics(innate_subsystem::BitmapInterface * pbitmap)
   {

      constructø(m_pdevicecontext);

      m_pdevicecontext->initialize_device_context(pbitmap);

   }

   void Graphics::setBkMode(bool transparent)
   {
      m_iBkMode = transparent ? TRANSPARENT : OPAQUE;
//      SetBkMode(m_pdevicecontext->m_hdc, transparent ? TRANSPARENT : OPAQUE);

   }


   void Graphics::setBlendModeOn(bool bSet)
   {

      if (bSet)
      {
         m_pdevicecontext->m_pgraphics->SetCompositingMode(Gdiplus::CompositingModeSourceOver);

      }
      else
      {
         m_pdevicecontext->m_pgraphics->SetCompositingMode(Gdiplus::CompositingModeSourceCopy);

      }

   }

   void Graphics::setAntiAliasOn(bool bOn)
   {

      if (bOn)
      {
         m_pdevicecontext->m_pgraphics->SetSmoothingMode(Gdiplus::SmoothingModeAntiAlias);

      }
      else
      {
         m_pdevicecontext->m_pgraphics->SetSmoothingMode(Gdiplus::SmoothingModeNone);

      }

   }


   void Graphics::setTextColor(const ::color::color & color)
   {
      m_colorText= color;
      //SetTextColor(m_pdevicecontext->m_hdc, RGB(color.byte_red(), color.byte_green(), color.byte_blue()));
   }

   void Graphics::setBkColor(const ::color::color & color)
   {
      //SetBkColor(m_pdevicecontext->m_hdc, RGB(color.byte_red(), color.byte_green(), color.byte_blue()));
      m_colorBk = color;
   }

   void Graphics::setBrush(::innate_subsystem::BrushInterface *pbrush)
   {

      // auto pbrushWin32 = pbrush->impl<Brush>();
      //
      // HGDIOBJ object = pbrushWin32 ? pbrushWin32->m_hbrush : nullptr;
      //
      //m_pdevicecontext->selectObject(pbrush);
      m_pbrush = pbrush;

   }

   void Graphics::setPen(::innate_subsystem::PenInterface *ppen)
   {

      // ::cast < ::innate_subsystem_win32::Pen > ppenWin32 = ::innate_subsystem::get_implementation(ppen);
      //
      // HGDIOBJ object = ppenWin32 ? ppenWin32->m_hpen : nullptr;
      //
      //m_pdevicecontext->selectObject(ppen);
      m_ppen = ppen;

   }

   void Graphics::moveTo(int x, int y)
   {
      //MoveToEx(m_pdevicecontext->m_hdc, x, y, NULL);
      m_pointCurrent.x = x;
      m_pointCurrent.y = y;
   }

   void Graphics::lineTo(int x, int y)
   {
      //LineTo(m_pdevicecontext->m_hdc, x, y);
      m_pdevicecontext->m_pgraphics->DrawLine(m_ppen->m_ppen, m_pointCurrent.x, m_pointCurrent.y, x, y);
      m_pointCurrent.x = x;
      m_pointCurrent.y = y;

   }

   void Graphics::fillRect(int l, int t, int r, int b, ::innate_subsystem::BrushInterface *pbrush)
   {
      Gdiplus::Rect gdiplusrect;

      gdiplusrect.X = t;
      gdiplusrect.Y = l;
      gdiplusrect.Width = r-l;
      gdiplusrect.Height = b-t;

      auto pbrushWin32 = pbrush->impl<::innate_subsystem_win32::Brush>();

      //auto hbrush = (HBRUSH) pbrush->_HGDIOBJ();

m_pdevicecontext->m_pgraphics->FillRectangle(pbrushWin32->m_pbrush, gdiplusrect);
      //FillRect(m_pdevicecontext->m_hdc, &rect, hbrush);

   }


   void Graphics::fillRect(const ::int_rectangle & rectangle, const ::color::color & color)
   {
      Gdiplus::Rect gdiplusrect;

      ::copy(gdiplusrect, rectangle);

      //auto pbrushWin32 = pbrush->impl<::innate_subsystem_win32::Brush>();
      Gdiplus::Color gdipluscolor(color.byte_opacity(), color.byte_red(), color.byte_green(), color.byte_blue());
      Gdiplus::SolidBrush solidbrush(gdipluscolor);

      //auto hbrush = (HBRUSH) pbrush->_HGDIOBJ();

      m_pdevicecontext->m_pgraphics->FillRectangle(&solidbrush, gdiplusrect);
      //FillRect(m_pdevicecontext->m_hdc, &rect, hbrush);

   }

   void Graphics::ellipse(int l, int t, int r, int b)
   {
      //Ellipse(m_pdevicecontext->m_hdc, l, t, r, b);
      Gdiplus::Rect gdiplusrect;

      gdiplusrect.X = t;
      gdiplusrect.Y = l;
      gdiplusrect.Width = r-l;
      m_pdevicecontext->m_pgraphics->FillEllipse(m_pbrush->m_pbrush, gdiplusrect);
      m_pdevicecontext->m_pgraphics->DrawEllipse(m_ppen->m_ppen, gdiplusrect);
   }

   void Graphics::rectangle(int l, int t, int r, int b)
   {
      //Rectangle(m_pdevicecontext->m_hdc, l, t, r, b);
      Gdiplus::Rect gdiplusrect;

      gdiplusrect.X = t;
      gdiplusrect.Y = l;
      gdiplusrect.Width = r-l;
      m_pdevicecontext->m_pgraphics->FillRectangle(m_pbrush->m_pbrush, gdiplusrect);
      m_pdevicecontext->m_pgraphics->DrawRectangle(m_ppen->m_ppen, gdiplusrect);

   }

   void Graphics::drawBitmap(::innate_subsystem::BitmapInterface *pbitmap, int x, int y, int w, int h)
   {

      auto pbitmapWin32 = pbitmap->impl<::innate_subsystem_win32::Bitmap>();
      //DeviceContext memDC;

      //memDC.initialize_device_context(m_pdevicecontext);

      //auto pobjOld = memDC.selectObject(pbitmap);
      m_pdevicecontext->m_pgraphics->DrawImage(pbitmapWin32->m_pbitmap, x, y, w, h);

      //BitBlt(m_pdevicecontext->m_hdc, x, y, w, h, memDC.m_hdc, 0, 0, SRCCOPY);

      //memDC.selectObject(pobjOld);
   }


   void Graphics::drawBitmap(::innate_subsystem::BitmapInterface *pbitmap, int x, int y, int srcx, int srcy, int srcW, int srcH)
   {

      auto pbitmapWin32 = pbitmap->impl<::innate_subsystem_win32::Bitmap>();

      m_pdevicecontext->m_pgraphics->DrawImage(pbitmapWin32->m_pbitmap, x, y, srcx, srcy, srcW, srcH, Gdiplus::UnitPixel);

   }

   void Graphics::_defer_text_tools()
   {

      if (!m_pfont)
      {

         m_pfont = new Gdiplus::Font(L"Arial", 14.0f);

      }
      if (!m_pbrushText || m_colorBrushText != m_colorText)
      {
         if (m_pbrushText)
         {

            delete m_pbrushText;
            m_pbrushText = nullptr;
         }
         auto color = m_colorText;
         m_colorBrushText = color;
         Gdiplus::Color gdipluscolor(color.byte_opacity(), color.byte_red(), color.byte_green(), color.byte_blue());
         m_pbrushText = new Gdiplus::SolidBrush(gdipluscolor);

      }

   }

   void Graphics::drawText(const char *text, int cchText, ::int_rectangle &rectangle, unsigned int format)
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

      Gdiplus::RectF gdiplusrect;

      ::copy(gdiplusrect, rectangle);

      _defer_text_tools();

      auto pstringformat = Gdiplus::StringFormat::GenericTypographic();
      // RECT rc;
      // ::copy(rc, rect);
      // DrawText(m_pdevicecontext->m_hdc, wstr, wstr.length(), &rc, format);
      m_pdevicecontext->m_pgraphics->DrawString(wstr, wstr.length(), m_pfont, gdiplusrect, pstringformat, m_pbrushText);
   }

   
} // namespace innate_subsystem_win32


