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
#include "framework.h"
#include "Bitmap.h"
#include "DeviceContext.h"

#include "innate_subsystem/drawing/DeviceContext.h"


namespace innate_subsystem_windows
{
   // Bitmap::Bitmap(const ::int_size & size)
   // : m_bitmap(NULL)
   // {
   //    // Prepare buffer
   //    int bpp = 32;
   //    size_t size = width * height * (bpp / 8);
   //    std::vector<unsigned char> bits(size);
   //    if (width != 0 && height != 0) {
   //       memset(&bits.front(), 0, size);
   //       // Create bitmap handle
   //       m_bitmap = CreateBitmap(width, height, 1, bpp, &bits.front());
   //    }
   // }
   //
   // Bitmap::Bitmap(HDC dc, const ::int_size & size)
   // {
   //    m_bitmap = CreateCompatibleBitmap(dc, width, height);
   // }
   //
   // Bitmap::Bitmap(HBITMAP bitmap)
   // : m_bitmap(bitmap)
   // {
   // }

   Bitmap::Bitmap() :
   m_pbitmap(nullptr), m_hbitmap(nullptr)
   {


   }


   Bitmap::~Bitmap()
   {
      destroyGraphicsObject();
      // if (m_hbitmap != NULL) {
      //    ::DeleteObject(m_hbitmap);
      // }
   }

   void Bitmap::initialize_bitmap(const ::int_size & size)
   {
      destroyGraphicsObject();
      // //;mm_bitmap(NULL)
      // // Prepare buffer
       int bpp = 32;
       size_t s = size.area() * (bpp / 8);
       ::memory bits;
       bits.set_size(s);
       if (size > 0)
       {
          memset(bits.data(), 0, bits.size());
          // Create bitmap handle
          m_hbitmap = CreateBitmap(size.cx, size.cy, 1, bpp, bits.data());
       }
      
      //m_pbitmap= new  Gdiplus::Bitmap(size.cx, size.cy, PixelFormat32bppARGB);
       m_pbitmap = new Gdiplus::Bitmap(m_hbitmap, nullptr);
   }

   void Bitmap::initialize_bitmap(::innate_subsystem::DeviceContextInterface * pdevicecontext, const ::int_size & size)
   {
      destroyGraphicsObject();
      auto pdevicecontextWin32 = pdevicecontext->impl<::innate_subsystem_windows::DeviceContext>();
      m_hbitmap = CreateCompatibleBitmap(pdevicecontextWin32->m_hdc2, size.cx, size.cy);
      //m_pbitmap = new Gdiplus::Bitmap(size.cx, size.cy, pdevicecontextWin32->m_pgraphics);
      m_pbitmap = new Gdiplus::Bitmap(m_hbitmap, nullptr);
   }

   void Bitmap::initialize_bitmap(::innate_subsystem::BitmapInterface * pbitmap)
   //: m_bitmap(bitmap)
   {

      destroyGraphicsObject();
      auto ppbitmapWin32 = pbitmap->impl<::innate_subsystem_windows::DeviceContext>();
      auto pbitmapWin32 = pbitmap->impl < ::innate_subsystem_windows::Bitmap>();
      m_hbitmap = pbitmapWin32->m_hbitmap;
      m_pbitmap = new Gdiplus::Bitmap(m_hbitmap, nullptr);
      // pbitmapWin32->m_pbitmap->GetWidth(), pbitmapWin32->m_pbitmap->GetHeight(),
      // PixelFormat32bppARGB);
      //m_pbitmap = pbitmapWin32->m_pbitmap->Clone(0, 0,
        // pbitmapWin32->m_pbitmap->GetWidth(), pbitmapWin32->m_pbitmap->GetHeight(),
         //PixelFormat32bppARGB);

   }


   void Bitmap::_initialize_bitmap(HBITMAP hbitmap, HPALETTE hpalette)
   {

      destroyGraphicsObject();
      m_pbitmap = new Gdiplus::Bitmap(hbitmap, hpalette);

   }

   ::int_size Bitmap::getSize() const
   {

      auto w = m_pbitmap->GetWidth();
      auto h = m_pbitmap->GetHeight();

      return {w, h};
      // BITMAP bitmap;
      // if (GetObject(m_hbitmap, sizeof(BITMAP), &bitmap) == 0) {
      //    return 0;
      // }
      // return {bitmap.bmWidth, bitmap.bmHeight};
   }

   // int Bitmap::getHeight() const
   // {
   //    BITMAP bitmap;
   //    if (GetObject(m_bitmap, sizeof(BITMAP), &bitmap) == 0) {
   //       return 0;
   //    }
   //    return bitmap.bmHeight;
   // }
   void Bitmap::destroyGraphicsObject()
   {

      if (m_pbitmap)
      {

         delete m_pbitmap;

         m_pbitmap = nullptr;

      }

   }
} // namespace innate_subsystem_windows


