#pragma once


#include "aura/_.h"


#ifdef _DRAW2D_GDIPLUS_STATIC
#define CLASS_DECL_DRAW2D_GDIPLUS
#elif defined(_DRAW2D_GDIPLUS_LIBRARY)
#define CLASS_DECL_DRAW2D_GDIPLUS  CLASS_DECL_EXPORT
#else
#define CLASS_DECL_DRAW2D_GDIPLUS  CLASS_DECL_IMPORT
#endif


::e_status gdiplus_draw_text(::draw2d::graphics * pgraphics, ::draw2d::path * ppath, const string & str, rectd & rectParam, const ::e_align & ealign, const ::e_draw_text & edrawtext, ::draw2d::font * pfont, double dFontWidth, ::draw2d::brush * pbrush = nullptr, bool bMeasure = false);


inline auto gdiplus_color(const ::color& color)
{
   return Gdiplus::Color(color.m_iA, color.m_iR, color.m_iG, color.m_iB);
}



#define __graphics(pgraphics) ((::draw2d_gdiplus::graphics *) pgraphics->m_pthis)
#define __pen(ppen) ((::draw2d_gdiplus::pen *) ppen->m_pthis)
#define __brush(pbrush) ((::draw2d_gdiplus::brush *) pbrush->m_pthis)
#define __font(pfont) ((::draw2d_gdiplus::font *) pfont->m_pthis)
#define __graphics_path(ppath) ((::draw2d_gdiplus::path *) ppath->m_pthis)




class g_keep
{

public:

   Gdiplus::Graphics* point;
   Gdiplus::GraphicsState s;

   g_keep(Gdiplus::Graphics* point1)
   {

      point = point1;

      s = point->Save();

   }

   ~g_keep()
   {

      point->Restore(s);

   }

};


#include "node.h"



