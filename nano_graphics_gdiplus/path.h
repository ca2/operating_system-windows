//
// Created by camilo on 2026-05-27 05:15 <3ThomasBorregaardSørensen!! Mummi!! Bilbo!!
//
#pragma once


#include "acme/nano/graphics/path.h"
#include <gdiplus.h>


namespace nano_graphics_gdiplus
{


   class CLASS_DECL_NANO_GRAPHICS_GDIPLUS path 
      : virtual public ::nano::graphics::path
   {
   public:


      ::auto_pointer<::Gdiplus::GraphicsPath> m_pgraphicspath;


      path();
      ~path() override;


      void add_arc(::f64 x, ::f64 y, ::f64 w, ::f64 h, const ::f64_angle & angleStart, const ::f64_angle & angleSweep) override;

      void close_figure() override;
      
   };


} // namespace nano_graphics_gdiplus
