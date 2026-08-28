#pragma once


#include "aura/graphics/write_text/font.h"



namespace draw2d_gdiplus
{


   


   class CLASS_DECL_DRAW2D_GDIPLUS font :
      virtual public ::write_text::font
   {
   public:


      auto_pointer < Gdiplus::PrivateFontCollection >    m_pprivateFontCollection;
      auto_pointer < Gdiplus::FontFamily >               m_pgdiplusfontfamily;
      auto_pointer < Gdiplus::Font >                     m_pgdiplusfont;
      ::i32 m_iStyle;
      //__creatable_from_base(font, ::write_text::font);


      font();
      ~font() override;


//#ifdef DEBUG
//
//      
//      void dump(dump_context & dumpcontext) const override;
//
//
//#endif


      void update(::draw2d::graphics * pdraw2dgraphics) override;
      void clear_node_data() override;


      //Gdiplus::Font * get_gdiplus_font() { return (Gdiplus::Font *) m_osdata[0]; }
      //void set_gdiplus_font(Gdiplus::Font * pwritetextfont) { m_osdata[0] = pwritetextfont; }


      virtual enum_character_set calculate_character_set(::draw2d::graphics * pdraw2dgraphics);


      void on_create_internal_font(::draw2d::graphics * pdraw2dgraphics, ::write_text::internal_font * pinternalfont) override;


   };


} // namespace draw2d_gdiplus



