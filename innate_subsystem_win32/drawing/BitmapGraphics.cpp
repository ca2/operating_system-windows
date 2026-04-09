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
#include "BitmapGraphics.h"
#include "Bitmap.h"
#include "DeviceContext.h"


namespace innate_subsystem_win32
{
   // BitmapGraphics::BitmapGraphics(DeviceContext *complatibleDC, const ::int_size & size)
   // : Graphics(complatibleDC), m_isPainting(false)
   // {
   //    m_bitmap = new Bitmap(complatibleDC->m_dc, width, height);
   //    m_dc = new DeviceContext(complatibleDC);
   // }

   // BitmapGraphics::BitmapGraphics(DeviceContext* pdevicecontextCompatible, const int_size& size)
   // {
   //
   //
   // }

   // BitmapGraphics::BitmapGraphics(DeviceContext* pdevicecontextCompatible, const int_size& size)
   // {
   //
   //
   // }
   //

   BitmapGraphics::BitmapGraphics():
   m_isPainting(false)
   {


   }


   BitmapGraphics::~BitmapGraphics()
   {
      //delete m_bitmap;
      //delete m_dc;
   }

   void BitmapGraphics::initialize_bitmap_graphics(::innate_subsystem::DeviceContextInterface *pdevicecontextCompatible, const ::int_size & size)
//   : Graphics(complatibleDC), m_isPainting(false)
   {
      constructø(m_pbitmap);
      m_pbitmap->initialize_bitmap(pdevicecontextCompatible, size);
      initialize_graphics(pdevicecontextCompatible);
      //constructø(m_pdevice);
      //m_pdevice->initialize_device(pdevicecontextCompatible);
   }


   ::innate_subsystem::BitmapInterface *BitmapGraphics::getBitmap()
   {
      return m_pbitmap;
   }

   void BitmapGraphics::beginPaint()
   {
      _ASSERT(!m_isPainting);

      m_isPainting = true;
      //auto pdevicecontextWin32 = this->impl< ::innate_subsystem_win32::DeviceContext>();
      //auto pbitmapWin32 = m_pbitmap->impl< ::innate_subsystem_win32::Bitmap >();
      m_pgraphicsobjectOldBitmap = device_context()->selectObject(m_pbitmap);
   }

   void BitmapGraphics::endPaint()
   {
      _ASSERT(m_isPainting);

      m_isPainting = false;
      //auto pdevicecontextWin32 = this->impl< ::innate_subsystem_win32::DeviceContext>();
      device_context()->selectObject(m_pgraphicsobjectOldBitmap);
   }
} // namespace innate_subsystem_win32