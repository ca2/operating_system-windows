#pragma once


namespace draw2d_gdiplus
{


   class region :
      virtual public ::draw2d::region
   {
   public:


      Gdiplus::Region *       m_pregion;


      region();
      virtual ~region();


      virtual bool create(::draw2d::graphics * pdraw2dgraphics, ::i8 iCreate) override;
      virtual void destroy() override;


      virtual bool translate(const POINT& point, ::draw2d::graphics * pdraw2dgraphics = nullptr) override;

      virtual bool contains(const POINT & point, ::draw2d::graphics * pdraw2dgraphics = nullptr) override;

      virtual bool get_bounding_box(RECT* prectangle, ::draw2d::graphics * pdraw2dgraphics = nullptr) override;

      virtual void expand_bounding_box(::f64_rectangle * prectangle, ::draw2d::graphics * pdraw2dgraphics) override;

      Gdiplus::Region * get(::draw2d::graphics * pdraw2dgraphics);
      Gdiplus::Region * get_rect(::draw2d::graphics * pdraw2dgraphics);
      Gdiplus::Region * get_oval(::draw2d::graphics * pdraw2dgraphics);
      Gdiplus::Region * get_polygon(::draw2d::graphics * pdraw2dgraphics);
      Gdiplus::Region * get_poly_polygon(::draw2d::graphics * pdraw2dgraphics);
      Gdiplus::Region * get_combine(::draw2d::graphics * pdraw2dgraphics);


   };


} // namespace draw2d_gdiplus



