#pragma once


#include "aura/graphics/draw2d/path.h"


namespace draw2d_gdiplus
{


   class CLASS_DECL_DRAW2D_GDIPLUS path :
      virtual public ::draw2d::path
   {
   public:


      //__creatable_from_base(path, ::draw2d::path);


      Gdiplus::GraphicsPath *    m_ppath;
      Gdiplus::PointF            m_pointInternal;
      bool                       m_bHasPointInternal;
      bool                       m_bHasPath;


      path();
      virtual ~path();


      virtual bool internal_add_arc(const ::rectangle_f64 & rectangle, const ::angle_f64 & angleBeg, const ::angle_f64 & angleEnd);

      virtual point_f64 internal_last_point();

      virtual point_f64 internal_current_point();


      //virtual bool internal_begin_figure(bool bFill, ::draw2d::e_fill_mode efillmode);
      //virtual bool internal_end_figure(bool bClose);

      virtual bool internal_begin_figure();
      virtual bool internal_close_figure();

      virtual bool internal_add_line(double x1, double y1, double x2, double y2);
      virtual bool internal_add_rect(double x, double y, double cx, double cy, ::draw2d::graphics * pgraphics);
      virtual bool internal_add_ellipse(double x, double y, double cx, double cy);
      //virtual bool internal_add_line(double x, double y);
      //virtual bool internal_add_move(double x, double y);

      virtual bool internal_add_text_out(::draw2d::graphics * pgraphics, i32 x,i32 y, const ::string & strText,::write_text::font * pfont);
      virtual bool internal_add_draw_text(::draw2d::graphics * pgraphics, const ::rectangle_i32 & rectangle, const ::string & strText, ::write_text::font * pfont, const ::e_align & ealign, const ::e_draw_text & edrawtext);


      virtual void create(::draw2d::graphics * pgraphics, ::i8 iCreate) override;
      void destroy() override;

      virtual bool _set(::draw2d::graphics* pgraphics, const ::draw2d::enum_item & eshape);

      virtual bool _set(::draw2d::graphics* pgraphics, const ::arc_f64 & parc);

      virtual bool _set(::draw2d::graphics* pgraphics, const ::line_f64 & pline);

      virtual bool _set(::draw2d::graphics* pgraphics, const ::lines_f64 & pline);

      virtual bool _set(::draw2d::graphics* pgraphics, const ::rectangle_f64 & rectangle);

      virtual bool _set(::draw2d::graphics * pgraphics, const ::ellipse_f64 & ellipse);

      virtual bool _set(::draw2d::graphics* pgraphics, const ::polygon_f64 & polygon);

      virtual bool _set(::draw2d::graphics* pgraphics, const ::write_text::text_out& ptextout);

      virtual bool _set(::draw2d::graphics* pgraphics, const ::write_text::draw_text& pdrawtext);

      virtual bool contains(::draw2d::graphics_pointer& pgraphics, const point_f64& point) override;


   };


} // namespace draw2d_gdiplus




