// Created by camilo on 2026-06-08 03:43 <3ThomasBorregaardSørensen!! Mummi!! Bilbo!!
#include "framework.h"
#include "font_family.h"


namespace nano_graphics_gdiplus
{


   font_family::font_family() { m_efont = e_font_none; }


   font_family::~font_family() {}


   void font_family::create_font_family(enum_font efont)
   {

      ::nano::graphics::font_family::create_font_family(efont);

      _create_font_family();

      
   }


   void font_family::create_font_family_with_name(const ::scoped_string &scopedstrFamilyName)
   {

      ::nano::graphics::font_family::create_font_family_with_name(scopedstrFamilyName);

      _create_font_family();

   }


   void font_family::_create_font_family()
   {

      ::string strFontFamilyName = get_font_family_name();

      ::wstring wstrFontFamilyName(strFontFamilyName);

      m_pfontfamily = new ::Gdiplus::FontFamily(wstrFontFamilyName);


   }


} // namespace nano_graphics_gdiplus










