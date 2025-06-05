#pragma once


#include "aura/graphics/draw2d/draw2d.h"


namespace draw2d_gdiplus
{


   class CLASS_DECL_DRAW2D_GDIPLUS draw2d :
      virtual public ::draw2d::draw2d
   {
   public:



      //__creatable_from_base(draw2d, ::draw2d::draw2d);
      

      draw2d();
      ~draw2d() override;


      void initialize(::particle * pparticle) override;

      virtual string write_text_get_default_implementation_name() override;


      //virtual ::write_text::internal_font * internal_font_from_file(::platform::context * pcontext, const ::file::path & path);
      void adjust_composited_window_styles(unsigned int& nExStyle, unsigned int& nStyle) override;


   };


} // namespace draw2d_gdiplus



