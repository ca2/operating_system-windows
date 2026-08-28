#pragma once


#include "aura/graphics/draw2d/region.h"


namespace draw2d_gdiplus
{


   class region :
      virtual public ::draw2d::region
   {
   public:


      //__creatable_from_base(region, ::draw2d::region);


      auto_pointer < Gdiplus::Region >       m_pgdiplusregion;


      region();
      ~region() override;


      void update(::draw2d::graphics * pdraw2dgraphics) override;
      void clear_node_data() override;


      bool translate(const ::i32_point & point, ::draw2d::graphics * pdraw2dgraphics = nullptr) override;

      bool contains(const ::i32_point & point, ::draw2d::graphics * pdraw2dgraphics = nullptr) override;

      bool get_bounding_box(::i32_rectangle & rectangle, ::draw2d::graphics * pdraw2dgraphics = nullptr) override;

      void expand_bounding_box(::f64_rectangle & rectangle, ::draw2d::graphics * pdraw2dgraphics) override;

      Gdiplus::Region * get(::draw2d::graphics * pdraw2dgraphics);
      Gdiplus::Region * get_rectangle(::draw2d::graphics * pdraw2dgraphics);
      Gdiplus::Region * get_ellipse(::draw2d::graphics * pdraw2dgraphics);
      Gdiplus::Region * get_polygon(::draw2d::graphics * pdraw2dgraphics);
      Gdiplus::Region * get_poly_polygon(::draw2d::graphics * pdraw2dgraphics);
      Gdiplus::Region * get_combine(::draw2d::graphics * pdraw2dgraphics);


   };


} // namespace draw2d_gdiplus



