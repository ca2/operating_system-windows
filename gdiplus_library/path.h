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


      virtual bool internal_add_arc(const ::f64_rectangle & rectangle, const ::f64_angle & angleBeg, const ::f64_angle & angleEnd);

      virtual ::f64_point internal_last_point();

      virtual ::f64_point internal_current_point();


      //virtual bool internal_begin_figure(bool bFill, ::draw2d::e_fill_mode efillmode);
      //virtual bool internal_end_figure(bool bClose);

      virtual bool internal_begin_figure();
      virtual bool internal_close_figure();

      virtual bool internal_add_line(::f64 x1, ::f64 y1, ::f64 x2, ::f64 y2);
      virtual bool internal_add_rect(::f64 x, ::f64 y, ::f64 cx, ::f64 cy, ::draw2d::graphics * pgraphics);
      virtual bool internal_add_ellipse(::f64 x, ::f64 y, ::f64 cx, ::f64 cy);
      //virtual bool internal_add_line(::f64 x, ::f64 y);
      //virtual bool internal_add_move(::f64 x, ::f64 y);

      virtual bool internal_add_text_out(::draw2d::graphics * pgraphics, ::i32 x,::i32 y, const ::scoped_string & scopedstrText,::write_text::font * pfont);
      virtual bool internal_add_draw_text(::draw2d::graphics * pgraphics, const ::i32_rectangle & rectangle, const ::scoped_string & scopedstrText, ::write_text::font * pfont, const ::e_align & ealign, const ::e_draw_text & edrawtext);


      virtual void create(::draw2d::graphics * pgraphics, ::i8 iCreate) override;
      void destroy() override;

      virtual bool _set(::draw2d::graphics* pgraphics, const ::draw2d::enum_item & eshape);

      virtual bool _set(::draw2d::graphics* pgraphics, const ::f64_arc & parc);

      virtual bool _set(::draw2d::graphics* pgraphics, const ::f64_line & pline);

      virtual bool _set(::draw2d::graphics* pgraphics, const ::f64_lines & pline);

      virtual bool _set(::draw2d::graphics* pgraphics, const ::f64_rectangle & rectangle);

      virtual bool _set(::draw2d::graphics * pgraphics, const ::f64_ellipse & ellipse);

      virtual bool _set(::draw2d::graphics* pgraphics, const ::f64_polygon & polygon);

      virtual bool _set(::draw2d::graphics* pgraphics, const ::write_text::text_out& ptextout);

      virtual bool _set(::draw2d::graphics* pgraphics, const ::write_text::draw_text& pdrawtext);

      virtual bool contains(::draw2d::graphics_pointer& pgraphics, const ::f64_point& point) override;


   };


} // namespace draw2d_gdiplus




