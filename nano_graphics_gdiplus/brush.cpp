//
// Created by camilo on 31/01/2022 16:06 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "brush.h"
// #include "_nano.h"


namespace nano_graphics_gdiplus
{

   brush::brush() { }


   brush::~brush() {}


   void brush::create_solid_brush(const ::color::color& color)
   {

      m_pbrush = new ::Gdiplus::SolidBrush(
         ::Gdiplus::Color(color.u8_opacity(), color.u8_red(), color.u8_green(), color.u8_blue()));

   }

   //void brush::update(::nano::graphics::context *pnanodevice)
   //{

   //   if (m_bModified)
   //   {

   //      destroy();

   //      m_hgdiobj = ::CreateSolidBrush(win32_COLORREF(m_color));

   //      m_bModified = false;
   //   }
   //}


} // namespace nano_graphics_gdiplus
