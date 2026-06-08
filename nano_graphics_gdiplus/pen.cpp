//
// Created by camilo on 31/01/2022 16:06 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "pen.h"
// #include "_nano.h"


namespace nano_graphics_gdiplus
{

   pen::pen() {  }


   pen::~pen() {}


      void pen::create_pen(::nano::graphics::enum_pen epen, ::f64 fWidth, const ::color::color &color)
   {

      m_ppen = new ::Gdiplus::Pen(
         ::Gdiplus::Color(color.u8_opacity(), color.u8_red(), color.u8_green(), color.u8_blue()),
         (::Gdiplus::REAL) fWidth);
   }


      void pen::set_start_cap(::nano::graphics::enum_line_cap elinecap)
      { 
         
         ::Gdiplus::LineCap egdipluslinecap = ::Gdiplus::LineCapFlat;

         if (elinecap == ::nano::graphics::e_line_cap_round)
         {

            egdipluslinecap = ::Gdiplus::LineCapRound;

         }
         
         m_ppen->SetStartCap(egdipluslinecap);

      }


      void pen::set_end_cap(::nano::graphics::enum_line_cap elinecap)
      {

         ::Gdiplus::LineCap egdipluslinecap = ::Gdiplus::LineCapFlat;

         if (elinecap == ::nano::graphics::e_line_cap_round)
         {

            egdipluslinecap = ::Gdiplus::LineCapRound;
         }

         m_ppen->SetStartCap(egdipluslinecap);

   }

   //void pen::update(::nano::graphics::context *pnanodevice)
   //{

   //   if (m_bModified)
   //   {

   //      destroy();

   //      m_hgdiobj = ::CreatePen(PS_SOLID, m_iWidth, win32_COLORREF(m_color));

   //      m_bModified = false;
   //   }
   //}


} // namespace nano_graphics_gdiplus
