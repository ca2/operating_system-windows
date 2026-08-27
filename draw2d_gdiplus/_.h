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


//void gdiplus_draw_text(::draw2d::graphics * pdraw2dgraphics, ::draw2d::path * pdraw2dpath, const ::scoped_string & scopedstr, ::f64_rectangle & rectangleParam, const ::e_align & ealign, const ::e_draw_text & edrawtext, ::write_text::font * pwritetextfont, ::f64 dFontWidth, ::draw2d::brush * pdraw2dbrush = nullptr, bool bMeasure = false);


inline auto gdiplus_color(const ::color::color & color)
{

   return Gdiplus::Color(
      color.m_u8Opacity,
      color.m_u8Red,
      color.m_u8Green,
      color.m_u8Blue);

}


//#define __graphics(pdraw2dgraphics) ((::draw2d_gdiplus::graphics *) pdraw2dgraphics->m_pthis)
//#define __pen(pdraw2dpen) ((::draw2d_gdiplus::pen *) pdraw2dpen->m_pthis)
//#define __brush(pdraw2dbrush) ((::draw2d_gdiplus::brush *) pdraw2dbrush->m_pthis)
//#define __font(pwritetextfont) ((::draw2d_gdiplus::font *) pwritetextfont->m_pthis)
//#define __graphics_path(pdraw2dpath) ((::draw2d_gdiplus::path *) pdraw2dpath->m_pthis)


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
