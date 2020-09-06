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


      virtual bool internal_add_arc(const ::rectd & rect, const ::angle & angleBeg, const ::angle& angleEnd);

      virtual pointd internal_last_point();

      virtual pointd internal_current_point();


      //virtual bool internal_begin_figure(bool bFill, ::draw2d::e_fill_mode efillmode);
      //virtual bool internal_end_figure(bool bClose);

      virtual bool internal_begin_figure();
      virtual bool internal_close_figure();

      virtual bool internal_add_line(double x1, double y1, double x2, double y2);
      virtual bool internal_add_rect(double x, double y, double cx, double cy);
      //virtual bool internal_add_line(double x, double y);
      //virtual bool internal_add_move(double x, double y);

      virtual bool internal_add_text_out(::draw2d::graphics * pgraphics, i32 x,i32 y,const string & strText,::draw2d::font * pfont);
      virtual bool internal_add_draw_text(::draw2d::graphics * pgraphics, const ::rect & rect, const string & strText, ::draw2d::font * pfont, int nFormat);


      virtual bool create(::draw2d::graphics * pgraphics, ::i8 iCreate) override;
      virtual void destroy() override;

      virtual bool _set(::draw2d::graphics* pgraphics, ::draw2d::path::begin* pbegin);

      virtual bool _set(::draw2d::graphics* pgraphics, ::draw2d::path::arc* parc);

      virtual bool _set(::draw2d::graphics* pgraphics, ::draw2d::path::rect* prect);

      virtual bool _set(::draw2d::graphics* pgraphics, ::draw2d::path::line* pline);

      virtual bool _set(::draw2d::graphics* pgraphics, ::draw2d::path::lines* plines);

      virtual bool _set(::draw2d::graphics* pgraphics, ::draw2d::path::polygon* pline);

      virtual bool _set(::draw2d::graphics* pgraphics, ::draw2d::path::text_out* ptextout);

      virtual bool _set(::draw2d::graphics* pgraphics, ::draw2d::path::draw_text* pdrawtext);

      virtual bool _set(::draw2d::graphics* pgraphics, ::draw2d::path::close* pclose);

      virtual bool contains(::draw2d::graphics_pointer& pgraphics, const pointd& point) override;


   };


} // namespace draw2d_gdiplus




