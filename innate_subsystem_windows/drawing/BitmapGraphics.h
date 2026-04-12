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
#pragma once


#include "innate_subsystem/drawing/BitmapGraphics.h"



namespace innate_subsystem_windows
{
   //
   // Object that creates bitmap with specified size and allow to
   // draw into in through Graphics class methods.
   class BitmapGraphics :
      virtual public ::subsystem::implementation<::innate_subsystem::BitmapGraphicsInterface>
   {
   public:


      // Creates BitmapGraphics object with bitmap complatible with specified dc and
      // with specified size.
      //BitmapGraphics(DeviceContext *pdevicecontextCompatible, const ::int_size & size);
      BitmapGraphics();
      // Destroys bitmap and graphics object.
      ~BitmapGraphics() override;


      void initialize_bitmap_graphics(innate_subsystem::DeviceContextInterface* pdevicecontextCompatible, const int_size& size) override;

      // Returns target bitmap that we paint.
      ::innate_subsystem::BitmapInterface *getBitmap() override;

      void beginPaint() override;
      void endPaint() override;

   //protected:
      bool m_isPainting;
      ::pointer < ::innate_subsystem_windows::Bitmap > m_pbitmap;
      ::pointer < ::innate_subsystem::GraphicsObject > m_pgraphicsobjectOldBitmap;
   };





} // namespace innate_subsystem_windows