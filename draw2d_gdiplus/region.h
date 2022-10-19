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


      virtual void create(::draw2d::graphics * pgraphics, ::i8 iCreate) override;
      void destroy() override;


      virtual bool translate(const POINT_I32 & point, ::draw2d::graphics * pgraphics = nullptr) override;

      virtual bool contains(const POINT_I32 & point, ::draw2d::graphics * pgraphics = nullptr) override;

      virtual bool get_bounding_box(RECTANGLE_I32 & rectangle, ::draw2d::graphics * pgraphics = nullptr) override;

      virtual void max_bounding_box(RECTANGLE_F64 & rectangle, ::draw2d::graphics * pgraphics) override;

      Gdiplus::Region * get(::draw2d::graphics * pgraphics);
      Gdiplus::Region * get_rectangle(::draw2d::graphics * pgraphics);
      Gdiplus::Region * get_ellipse(::draw2d::graphics * pgraphics);
      Gdiplus::Region * get_polygon(::draw2d::graphics * pgraphics);
      Gdiplus::Region * get_poly_polygon(::draw2d::graphics * pgraphics);
      Gdiplus::Region * get_combine(::draw2d::graphics * pgraphics);


   };


} // namespace draw2d_gdiplus



