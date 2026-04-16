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


#include "innate_subsystem/drawing/Graphics.h"
//#include "util/CommonHeader.h"
#include <Gdiplus.h>
// #include "innate_subsystem/drawing/DeviceContext.h"
// #include "innate_subsystem/drawing/Bitmap.h"
// #include "innate_subsystem/drawing/Brush.h"
// #include "innate_subsystem/drawing/Pen.h"

namespace innate_subsystem_windows
{
   class Graphics :
   virtual public implementation<::innate_subsystem::GraphicsInterface>
   {
   public:


      ::pointer < ::innate_subsystem_windows::DeviceContext > m_pdevicecontext;
      ::pointer<::innate_subsystem_windows::Brush > m_pbrush;
      ::pointer<::innate_subsystem_windows::Pen>m_ppen;
      ::pointer<::innate_subsystem_windows::Font>m_pfont;
      int m_iBkMode;
      ::color::color m_colorText;
      ::color::color m_colorBk;
      ::int_point m_pointCurrent;
      //Gdiplus::Font * m_pfont;
      Gdiplus::Brush * m_pbrushText;
      ::color::color m_colorBrushText;



      // Creates graphics object with specified device context.
      //Graphics(DeviceContext *dc);
      Graphics();
      // Graphics class destructor.
      ~Graphics() override;


      virtual void _defer_text_tools();

      innate_subsystem::DeviceContextInterface * device_context() override;

      void initialize_graphics(::innate_subsystem::DeviceContextInterface * pdevicecontext) override;
      void initialize_graphics(::innate_subsystem::BitmapInterface * pbitmap) override;

      // Sets background colors mix mode.
      void setBkMode(bool transparent) override;

      void setBlendModeOn(bool bSet) override;

      void setAntiAliasOn(bool bOn) override;

      // Sets background color.
      void setBkColor(const ::color::color & color) override;

      // Sets text color.
      void setTextColor(const ::color::color & color) override;

      void setTextRenderingHintClearType() override;


      // Sets current brush.
      void setBrush(::innate_subsystem::BrushInterface * pbrush) override;
      // Sets current pen.
      void setPen(::innate_subsystem::PenInterface * ppen) override;
      // Sets current font.
      void setFont(::innate_subsystem::FontInterface * pfont) override;

      // Moves cursor to specified position.
      void moveTo(const ::int_point & point) override;
      // Draws line from current position to specified line.
      void lineTo(const ::int_point & point) override;

      // Draws filled rect.
      void fillRect(const ::int_rectangle & rectangle, ::innate_subsystem::BrushInterface * pbrush) override;
      void fillRect(const ::int_rectangle & rectangle, const ::color::color & color) override;
      // Draws ellipse.
      void ellipse(const ::int_rectangle & rectangle) override;
      // Draws rectance.
      void rectangle(const ::int_rectangle & rectangle) override;

      // Draws bitmap.
      void drawBitmap(::innate_subsystem::BitmapInterface * pbitmap, const ::int_rectangle & rectangle) override;
      void drawBitmap(::innate_subsystem::BitmapInterface *bitmap, const ::int_point & point, const ::int_rectangle & rectangle) override;
      // Draws text.
      void drawText(const char *text, int cchText, ::int_rectangle &rect, unsigned int format, enum_align ealign) override;

   ///protected:


   };


} // namespace innate_subsystem_windows