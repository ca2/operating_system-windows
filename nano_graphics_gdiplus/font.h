//
// Created by camilo on 31/01/2022 14:43 <3ThomasBorregaardSorensen!!
//
#pragma once


#include "acme/nano/graphics/font.h"
#include "object.h"
#include <gdiplus.h>


namespace nano_graphics_gdiplus
{


   class CLASS_DECL_NANO_GRAPHICS_GDIPLUS font : virtual public ::nano::graphics::font, virtual public object
   {
   public:


      ::auto_pointer < ::Gdiplus::FontFamily > m_pfontfamily;
      ::auto_pointer<::Gdiplus::Font> m_pfont;


      // CreatableFromBase(::nano::graphics::font, ::nano::graphics::font);


      font();
      ~font() override;


      //void update(::nano::graphics::context *pnanodevice) override;

      void create_point_font(enum_font efont, ::f64 fPointSize, bool bBold = false, bool bItalic, bool bUnderline = false) override;
      void create_pixel_font(enum_font efont, ::f64 fPixelSize, bool bBold = false, bool bItalic, bool bUnderline = false) override;
      //static HFONT _create_point_font(::i32 nPointSize, const ::scoped_string &scopedstrFaceName, bool bBold,
        //                              bool bUnderline, HDC hdc, LOGFONTW *plf);
      //static HFONT _create_point_font_indirect(LOGFONTW *pLogFont, HDC hdc);

      virtual void _create_font(enum_font efont, ::f64 fPixelSize, bool bPointSize, bool bBold = false, bool bUnderline = false);


   };


} // namespace nano_graphics_gdiplus
