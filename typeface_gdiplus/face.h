// Created by camilo with Mom and Bilbo support on
// 2025-06-01 23:20 <3ThomasBorregaardSorensen!!
#pragma once


#include "bred/typeface/face.h"
#include <gdiplus.h>


namespace typeface_gdiplus
{


   class CLASS_DECL_TYPEFACE_GDIPLUS face:
      virtual public ::typeface::face
   {
   public:

      
      ///unsigned int m_FaceVAO, m_FaceVBO;


      Gdiplus::Font* m_pfont;
      Gdiplus::FontFamily* m_pfamily;

      face();
      ~face() override;


      virtual void _defer_gdiplus_font_and_family();

      //virtual character& get_character(const ::scoped_string& scopedstr);


      virtual void create_character(::typeface::character& ch, const ::scoped_string& scopedstr);

      //void create_draw_buffers();

      //void create_texture(::typeface::character& ch, const unsigned char* p);

      void get_text_metric(::write_text::text_metric* ptextmetric);



   };


} // namespace typeface_gdiplus

