#pragma once


#include "aura/graphics/draw2d/region.h"


namespace draw2d_gdiplus
{


   class region :
      virtual public ::draw2d::region
   {
   public:


      //__creatable_from_base(region, ::draw2d::region);


      Gdiplus::Region *       m_pregion;


      region();
      ~region() override;


      void create(::draw2d::graphics * pgraphics, ::i8 iCreate) override;
      void destroy() override;


      bool translate(const ::point_i32 & point, ::draw2d::graphics * pgraphics = nullptr) override;

      bool contains(const ::point_i32 & point, ::draw2d::graphics * pgraphics = nullptr) override;

      bool get_bounding_box(::rectangle_i32 & rectangle, ::draw2d::graphics * pgraphics = nullptr) override;

      void max_bounding_box(::rectangle_f64 & rectangle, ::draw2d::graphics * pgraphics) override;

      Gdiplus::Region * get(::draw2d::graphics * pgraphics);
      Gdiplus::Region * get_rectangle(::draw2d::graphics * pgraphics);
      Gdiplus::Region * get_ellipse(::draw2d::graphics * pgraphics);
      Gdiplus::Region * get_polygon(::draw2d::graphics * pgraphics);
      Gdiplus::Region * get_poly_polygon(::draw2d::graphics * pgraphics);
      Gdiplus::Region * get_combine(::draw2d::graphics * pgraphics);


   };


} // namespace draw2d_gdiplus



