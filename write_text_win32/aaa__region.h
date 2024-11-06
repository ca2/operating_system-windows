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


      virtual bool create(::draw2d::graphics * pgraphics, char iCreate) override;
      virtual void destroy() override;


      virtual bool translate(const POINT& point, ::draw2d::graphics * pgraphics = nullptr) override;

      virtual bool contains(const POINT & point, ::draw2d::graphics * pgraphics = nullptr) override;

      virtual bool get_bounding_box(RECT* prectangle, ::draw2d::graphics * pgraphics = nullptr) override;

      virtual void expand_bounding_box(::double_rectangle * prectangle, ::draw2d::graphics * pgraphics) override;

      Gdiplus::Region * get(::draw2d::graphics * pgraphics);
      Gdiplus::Region * get_rect(::draw2d::graphics * pgraphics);
      Gdiplus::Region * get_oval(::draw2d::graphics * pgraphics);
      Gdiplus::Region * get_polygon(::draw2d::graphics * pgraphics);
      Gdiplus::Region * get_poly_polygon(::draw2d::graphics * pgraphics);
      Gdiplus::Region * get_combine(::draw2d::graphics * pgraphics);


   };


} // namespace draw2d_gdiplus



