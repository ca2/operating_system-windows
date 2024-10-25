#pragma once


#include "acme/platform/auto_pointer.h"
#include "aura/graphics/draw2d/draw2d.h"


namespace draw2d_gdiplus
{


   class CLASS_DECL_DRAW2D_GDIPLUS draw2d :
      virtual public ::draw2d::draw2d
   {
   public:


      class private_font :
         virtual public ::matter
      {
      public:

         auto_pointer < Gdiplus::PrivateFontCollection >    m_pcollection;
         ::raw_array < Gdiplus::FontFamily >                m_familya;
         int                                                m_iFamilyCount;

         private_font();
         ~private_font() override;

      };

      //__creatable_from_base(draw2d, ::draw2d::draw2d);
      string_map < ::pointer<private_font >>m_mapPrivateFont;

      draw2d();
      ~draw2d() override;


      void initialize(::particle * pparticle) override;

      virtual string write_text_get_default_implementation_name() override;


      virtual private_font * get_file_private_font(::platform::context * pcontext, const ::file::path & path);


   };


} // namespace draw2d_gdiplus



