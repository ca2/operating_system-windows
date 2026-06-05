// Created by camilo on 2026-06-04 19:27 <3ThomasBorregaardSørensen!! Mummi!! Bilbo!!
// From innate_subsystem by camilo on 2026-06-04 19:34 <3ThomasBorregaardSørensen!! Mummi!! Bilbo!!
#include "framework.h"
#include "Path.h"



namespace innate_subsystem_windows
{

   Path::Path() : m_pgraphicspath(new ::Gdiplus::GraphicsPath()) 
   {
   }

   Path::~Path() 
      {
      }



   void Path::addArc(::f64 x, ::f64 y, ::f64 w, ::f64 h, const ::f64_angle &angleStart,
                         const ::f64_angle &angleSweep)
      {

         m_pgraphicspath->AddArc((::Gdiplus::REAL)x, (::Gdiplus::REAL)y, (::Gdiplus::REAL)w, (::Gdiplus::REAL)h,
                                 (::Gdiplus::REAL)angleStart.degrees(), (::Gdiplus::REAL)angleSweep.degrees());
      }


      void Path::closeFigure() { m_pgraphicspath->CloseFigure(); }


}
