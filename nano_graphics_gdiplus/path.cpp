//
// Created by camilo on 2026-05-27 05:16 <3ThomasBorregaardSørensen!! Mummi!! Bilbo!!
//
#include "framework.h"
#include "path.h"

namespace nano_graphics_gdiplus 
{


   path::path() : m_pgraphicspath(new ::Gdiplus::GraphicsPath())
   {


   }


   path::~path()
   {


   }


   void path::add_arc(::f64 x, ::f64 y, ::f64 w, ::f64 h, const ::f64_angle & angleStart, const ::f64_angle & angleSweep)
   {

      m_pgraphicspath->AddArc((::Gdiplus::REAL)x, (::Gdiplus::REAL)y, (::Gdiplus::REAL) w, (::Gdiplus::REAL)h,
                              (::Gdiplus::REAL)angleStart.degrees(), (::Gdiplus::REAL)angleSweep.degrees());

   }

} // nano_graphics_gdiplus