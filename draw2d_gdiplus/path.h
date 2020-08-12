#pragma once


namespace draw2d_gdiplus
{


   class CLASS_DECL_DRAW2D_GDIPLUS path :
      virtual public ::draw2d::path
   {
   public:


      Gdiplus::GraphicsPath *    m_ppath;
      Gdiplus::PointF            m_pointInternal;
      bool                       m_bHasPointInternal;
      bool                       m_bHasPath;


      path();
      virtual ~path();


      virtual bool internal_add_arc(const ::rect & rect, double iStart, double iAngle);

      virtual pointd internal_last_point();

      virtual pointd internal_current_point();


      virtual bool internal_begin_figure(bool bFill, ::draw2d::e_fill_mode efillmode);
      virtual bool internal_end_figure(bool bClose);

      virtual bool internal_add_line(double x1, double y1, double x2, double y2);
      virtual bool internal_add_rect(double x, double y, double cx, double cy);
      virtual bool internal_add_line(double x, double y);
      virtual bool internal_add_move(double x, double y);

      virtual bool internal_add_string(::draw2d::graphics * pgraphics, i32 x,i32 y,const string & strText,::draw2d::font * pfont);
      virtual bool internal_add_draw_text(::draw2d::graphics * pgraphics, const ::rect & rect, const string & strText, ::draw2d::font * pfont, int nFormat);


      virtual bool create(::draw2d::graphics * pgraphics) override;
      virtual void destroy() override;

      virtual bool set(::draw2d::graphics * pgraphics, const ::draw2d::path::element & e);

      virtual bool set(::draw2d::graphics * pgraphics, const ::draw2d::path::arc & a);

      virtual bool set(::draw2d::graphics * pgraphics, const ::draw2d::path::rect & rect);

      virtual bool set(::draw2d::graphics * pgraphics, const ::draw2d::path::line & l);

      virtual bool set(::draw2d::graphics * pgraphics, const ::draw2d::path::move & point);

      virtual bool set(::draw2d::graphics * pgraphics, ::draw2d::path::element::e_type etype, const ::draw2d::path::string_path & point);

      virtual bool contains(::draw2d::graphics_pointer& pgraphics, const pointd& point) override;


   };


} // namespace draw2d_gdiplus




