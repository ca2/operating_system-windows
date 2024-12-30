// Created by camilo on 2024-12-30 19:48 <3ThomasBorregaardSorensen!!
#pragma once


#include "acme/platform/auto_pointer.h"
#include "aura/graphics/write_text/internal_font.h"


namespace draw2d_gdiplus
{



   class internal_font :
      virtual public ::write_text::internal_font
   {
   public:


      auto_pointer < Gdiplus::PrivateFontCollection >    m_pcollection;
      ::raw_array < Gdiplus::FontFamily >                m_familya;
      int                                                m_iFamilyCount;

      
      internal_font();
      ~internal_font() override;

      
      void load_from_memory(::memory_base * pmemory) override;
      void on_create_font(::draw2d::graphics * pgraphics, ::write_text::font * pfont) override;


   };


} // namespace draw2d_gdiplus



