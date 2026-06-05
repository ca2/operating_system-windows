// Created by camilo on 2026-06-04 19:22 <3ThomasBorregaardSørensen!! Mummi!! Bilbo!!
// From innate_subsystem by camilo on 2026-06-04 19:33 <3ThomasBorregaardSørensen!! Mummi!! Bilbo!!
#pragma once


#include "innate_subsystem/drawing/Path.h"
#include <Gdiplus.h>

namespace innate_subsystem_windows
{


   class Path : 
      virtual public Implementation<::innate_subsystem::PathInterface>
   {
   public:


      ::auto_pointer<::Gdiplus::GraphicsPath> m_pgraphicspath;



      Path();
      ~Path() override;


      virtual void addArc(::f64 x, ::f64 y, ::f64 w, ::f64 h, const ::f64_angle &angleStart,
                           const ::f64_angle &angleSweep) override;

      virtual void closeFigure() override;

   };




} // namespace innate_subsystem_windows
