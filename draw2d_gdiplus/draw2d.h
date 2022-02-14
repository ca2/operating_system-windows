#pragma once


#include "aura/graphics/draw2d/draw2d.h"


namespace draw2d_gdiplus
{


   class CLASS_DECL_DRAW2D_GDIPLUS draw2d :
      virtual public ::draw2d::draw2d
   {
   public:


      __creatable_from_library(aaaaa_aaaaaa, ::aaaaa_aaaaaa, "draw2d_gdiplus");


      draw2d();
      ~draw2d() override;


      void initialize(::object * pobject) override;

      virtual string write_text_get_default_library_name() override;

   };


} // namespace draw2d_gdiplus



