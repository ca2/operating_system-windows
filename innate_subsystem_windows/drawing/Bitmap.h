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


#include "innate_subsystem/drawing/Bitmap.h"
#include "subsystem_windows/_common_header.h"
#include <Gdiplus.h>

namespace innate_subsystem_windows
{
   class CLASS_DECL_INNATE_SUBSYSTEM_WINDOWS Bitmap :
   virtual public Implementation<innate_subsystem::BitmapInterface>

   {
   public:
      // // Creates empty bitmap with specified size.
      // Bitmap(const ::int_size & size);
      // // Creates compatible with dc bitmap with specified size.
      // Bitmap(HDC dc, const ::int_size & size);
      // // Creates bitmap from HBITMAP object.
      // Bitmap(HBITMAP bitmap);
      // // Destroys bitmap object.
      HBITMAP m_hbitmap;

      Gdiplus::Bitmap * m_pbitmap;


      Bitmap();
      ~Bitmap() override;


      // Creates empty bitmap with specified size.
      void initialize_bitmap(const int_size& size) override;
      // Creates compatible with dc bitmap with specified size.
      void initialize_bitmap(innate_subsystem::DeviceContextInterface* pdevicecontext, const int_size& size) override;
      // Creates bitmap from HBITMAP object.
      void initialize_bitmap(BitmapInterface* pbitmap) override;
      virtual void _initialize_bitmap(HBITMAP hbitmap, HPALETTE hpalette);

      // Returns bitmap width.
      int_size getSize() const override;
      // Returns bitmap height.
      //int getHeight() const;

      void destroyGraphicsObject() override;

   //protected:
      //HBITMAP m_hbitmap;

      // friend class Icon;
      // friend class Graphics;
      // friend class BitmapGraphics;
   };


} // namespace innate_subsystem_windows


