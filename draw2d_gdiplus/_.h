#pragma once


#include "aura/_.h"
#include "acme/operating_system/windows/_gdiplus.h"



#if defined(_draw2d_gdiplus_project)
#define CLASS_DECL_DRAW2D_GDIPLUS  CLASS_DECL_EXPORT
#else
#define CLASS_DECL_DRAW2D_GDIPLUS  CLASS_DECL_IMPORT
#endif


#include "aura/graphics/draw2d/color_matrix.h"

#include "acme/prototype/geometry2d/_collection.h"


inline void copy(Gdiplus::ColorMatrix & a, const color_matrix & b)
{

   copy_color_matrix(a.m, b.a);

}


//void gdiplus_draw_text(::draw2d::graphics * pgraphics, ::draw2d::path * ppath, const ::string & str, rectangle_f64 & rectangleParam, const ::e_align & ealign, const ::e_draw_text & edrawtext, ::write_text::font * pfont, double dFontWidth, ::draw2d::brush * pbrush = nullptr, bool bMeasure = false);


inline auto gdiplus_color(const ::color::color & color)
{

   return Gdiplus::Color(
      color.m_u8Opacity,
      color.m_u8Red,
      color.m_u8Green,
      color.m_u8Blue);

}


#define __graphics(pgraphics) ((::draw2d_gdiplus::graphics *) pgraphics->m_pthis)
#define __pen(ppen) ((::draw2d_gdiplus::pen *) ppen->m_pthis)
#define __brush(pbrush) ((::draw2d_gdiplus::brush *) pbrush->m_pthis)
#define __font(pfont) ((::draw2d_gdiplus::font *) pfont->m_pthis)
#define __graphics_path(ppath) ((::draw2d_gdiplus::path *) ppath->m_pthis)




class g_keep
{

public:


   Gdiplus::Graphics * m_p;
   Gdiplus::GraphicsState     m_state;


   g_keep(Gdiplus::Graphics * p)
   {

      m_p = p;

      m_state = m_p->Save();

   }

   ~g_keep()
   {

      m_p->Restore(m_state);

   }

};
