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


#include "apex/innate_subsystem/drawing/Graphics.h"
//#include "util/CommonHeader.h"

// #include "apex/innate_subsystem/drawing/DeviceContext.h"
// #include "apex/innate_subsystem/drawing/Bitmap.h"
// #include "apex/innate_subsystem/drawing/Brush.h"
// #include "apex/innate_subsystem/drawing/Pen.h"

namespace innate_subsystem_win32
{
   class Graphics :
   virtual public ::subsystem::implementation<::innate_subsystem::GraphicsInterface>
   {
   public:
      // Creates graphics object with specified device context.
      //Graphics(DeviceContext *dc);
      Graphics();
      // Graphics class destructor.
      ~Graphics() override;


      innate_subsystem::DeviceContextInterface * device_context() override;

      void initialize_graphics(::innate_subsystem::DeviceContextInterface * pdevicecontext) override;

      // Sets background colors mix mode.
      void setBkMode(bool transparent) override;
      // Sets background color.
      void setBkColor(const ::color::color & color) override;

      // Sets text color.
      void setTextColor(const ::color::color & color) override;
      // Sets current brush.
      void setBrush(::innate_subsystem::BrushInterface * pbrush) override;
      // Sets current pen.
      void setPen(::innate_subsystem::PenInterface * ppen) override;

      // Moves cursor to specified position.
      void moveTo(int x, int y) override;
      // Draws line from current position to specified line.
      void lineTo(int x, int y) override;

      // Draws filled rect.
      void fillRect(int l, int t, int r, int b, ::innate_subsystem::BrushInterface * pbrush) override;
      // Draws ellipse.
      void ellipse(int l, int t, int r, int b) override;
      // Draws rectance.
      void rectangle(int l, int t, int r, int b) override;

      // Draws bitmap.
      void drawBitmap(::innate_subsystem::BitmapInterface * pbitmap, int x, int y, int w, int h) override;
      // Draws text.
      void drawText(const char *text, int cchText, ::int_rectangle &rect, unsigned int format) override;

   ///protected:
      ::pointer < ::innate_subsystem_win32::DeviceContext > m_pdevicecontext;


   };


} // namespace innate_subsystem_win32