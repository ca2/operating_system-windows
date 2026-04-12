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


#include "subsystem_apex/drawing/Graphics.h"
//#include "util/CommonHeader.h"
#include <Gdiplus.h>
// #include "subsystem_apex/drawing/DeviceContext.h"
// #include "subsystem_apex/drawing/Bitmap.h"
// #include "subsystem_apex/drawing/Brush.h"
// #include "subsystem_apex/drawing/Pen.h"

namespace innate_subsystem_win32
{
   class Graphics :
   virtual public ::subsystem::implementation<::subsystem_apex::GraphicsInterface>
   {
   public:


      ::pointer < ::innate_subsystem_win32::DeviceContext > m_pdevicecontext;
      ::pointer<::innate_subsystem_win32::Brush > m_pbrush;
      ::pointer<::innate_subsystem_win32::Pen>m_ppen;
      ::pointer<::innate_subsystem_win32::Font>m_pfont;
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

      subsystem_apex::DeviceContextInterface * device_context() override;

      void initialize_graphics(::subsystem_apex::DeviceContextInterface * pdevicecontext) override;
      void initialize_graphics(::subsystem_apex::BitmapInterface * pbitmap) override;

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
      void setBrush(::subsystem_apex::BrushInterface * pbrush) override;
      // Sets current pen.
      void setPen(::subsystem_apex::PenInterface * ppen) override;
      // Sets current font.
      void setFont(::subsystem_apex::FontInterface * pfont) override;

      // Moves cursor to specified position.
      void moveTo(const ::int_point & point) override;
      // Draws line from current position to specified line.
      void lineTo(const ::int_point & point) override;

      // Draws filled rect.
      void fillRect(const ::int_rectangle & rectangle, ::subsystem_apex::BrushInterface * pbrush) override;
      void fillRect(const ::int_rectangle & rectangle, const ::color::color & color) override;
      // Draws ellipse.
      void ellipse(const ::int_rectangle & rectangle) override;
      // Draws rectance.
      void rectangle(const ::int_rectangle & rectangle) override;

      // Draws bitmap.
      void drawBitmap(::subsystem_apex::BitmapInterface * pbitmap, const ::int_rectangle & rectangle) override;
      void drawBitmap(::subsystem_apex::BitmapInterface *bitmap, const ::int_point & point, const ::int_rectangle & rectangle) override;
      // Draws text.
      void drawText(const char *text, int cchText, ::int_rectangle &rect, unsigned int format, enum_align ealign) override;

   ///protected:


   };


} // namespace innate_subsystem_win32