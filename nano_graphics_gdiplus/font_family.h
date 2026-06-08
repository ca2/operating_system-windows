// Created by camilo on 2026-06-08 03:43 <3ThomasBorregaardSørensen!! Mummi!! Bilbo!!
#pragma once


#include "acme/nano/graphics/font_family.h"
#include <gdiplus.h>


namespace nano_graphics_gdiplus
{


   class CLASS_DECL_NANO_GRAPHICS_GDIPLUS font_family : virtual public ::nano::graphics::font_family
   {
   public:


      ::auto_pointer<::Gdiplus::FontFamily> m_pfontfamily;

      
      font_family();
      ~font_family();


      void create_font_family(enum_font efont) override;
      void create_font_family_with_name(const ::scoped_string &scopedstr) override;

      
      virtual void _create_font_family();

      
   };



} // namespace nano_graphics_gdiplus




