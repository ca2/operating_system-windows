// Copyright (C) 2011,2012 GlavSoft LLC.
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
// with this program; if not, w_rite to the Free Software Foundation, Inc.,
// 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
//-------------------------------------------------------------------------
//

#pragma once


#include "subsystem/node/Screen.h"
#include "subsystem/framebuffer/PixelFormat.h"
#include "acme/prototype/geometry2d/rectangle.h"
#include "subsystem_windows/_common_header.h"


namespace subsystem_windows
{
   // This class get info for a windows desktop.
   class CLASS_DECL_SUBSYSTEM_WINDOWS Screen :
   virtual public Implementation<::subsystem::ScreenInterface>
   {
   public:
      Screen();
      ~Screen() override;

      void update() override;

      // Returns a PixelFormat that was at latest call of the
      // update() function.
      ::innate_subsystem::PixelFormat getPixelFormat() override;

      // Returns a desktop dimension that was at latest call of the
      // update() function.
      // Desktop dimension is a dimension of windows virtual desktop including
      // all monitors.
      ::i32_size getDesktopDimension() override;

      // Returns a rectangle that was at latest call of the
      // update() function.
      // The rectangle is a rectangle of windows virtual desktop including
      // all monitors (coordinates can be negative).
      ::i32_rectangle getDesktopRect() override;

      // This structure can be used by user code.
      struct BMI
      {
         BITMAPINFOHEADER bmiHeader;
         ::u32 red;
         ::u32 green;
         ::u32 blue;
      };

      struct Palette8bitBMI
      {
         BITMAPINFOHEADER bmiHeader;
         RGBQUAD rgbQuad[256];
      };

      // Fills the BMI structure. If dc == 0 the getBMI() function will
      // use a current desktop dc.
      virtual void _getBMI(BMI *bmi, HDC dc);

      // Windows contain both visible and invisible pseudo-monitors
      // that are associated with mirroring drivers.
      // The function returns only visible monitor count.
      ::i32 getVisibleMonitorCount() override;

   //private:
      virtual void _fillPixelFormat(const BMI *bmi);
      // Find position of first true bit
      ::i32 findFirstBit(const ::u32 bits) override;

      void fillScreenRect();

      ::innate_subsystem::PixelFormat m_pixelformat;
      ::i32_rectangle m_virtDesktopRect;
   };

}// namespace subsystem_windows