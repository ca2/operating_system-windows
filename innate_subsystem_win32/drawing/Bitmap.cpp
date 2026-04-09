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

#include "apex/innate_subsystem/drawing/DeviceContext.h"


namespace innate_subsystem_win32
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
   m_hbitmap(nullptr)
   {


   }


   Bitmap::~Bitmap()
   {
      if (m_hbitmap != NULL) {
         ::DeleteObject(m_hbitmap);
      }
   }

   void Bitmap::initialize_bitmap(const ::int_size & size)
   {
      //;mm_bitmap(NULL)
      // Prepare buffer
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
   }

   void Bitmap::initialize_bitmap(::innate_subsystem::DeviceContextInterface * pdevicecontext, const ::int_size & size)
   {
      ::cast < ::innate_subsystem_win32::DeviceContext > pdevicecontextWin32 = ::subsystem::get_implementation(pdevicecontext);
      m_hbitmap = CreateCompatibleBitmap(pdevicecontextWin32->m_hdc, size.cx, size.cy);
   }

   void Bitmap::initialize_bitmap(::innate_subsystem::BitmapInterface * pbitmap)
   //: m_bitmap(bitmap)
   {
      ::cast < ::innate_subsystem_win32::Bitmap > pbitmapWin32 = ::subsystem::get_implementation(pbitmap);
      m_hbitmap = pbitmapWin32->m_hbitmap;

   }


   ::int_size Bitmap::getSize() const
   {
      BITMAP bitmap;
      if (GetObject(m_hbitmap, sizeof(BITMAP), &bitmap) == 0) {
         return 0;
      }
      return {bitmap.bmWidth, bitmap.bmHeight};
   }

   // int Bitmap::getHeight() const
   // {
   //    BITMAP bitmap;
   //    if (GetObject(m_bitmap, sizeof(BITMAP), &bitmap) == 0) {
   //       return 0;
   //    }
   //    return bitmap.bmHeight;
   // }
} // namespace innate_subsystem_win32


