// Implemented on 2022-08-19 18:24 <3ThomasBorregaardSorensen!!
#pragma once


#include "aura/operating_system.h"
#undef new
#include <gdiplus.h>




#include "aura/graphics/draw2d/color_matrix.h"


#ifdef WINDOWS_DESKTOP


inline void copy(Gdiplus::ColorMatrix& a, const color_matrix& b)
{

   copy_color_matrix(a.m, b.a);

}


#endif


void gdiplus_draw_text(::draw2d::graphics* pgraphics, ::draw2d::path* ppath, const ::string& str, rectangle_f64& rectangleParam, const ::e_align& ealign, const ::e_draw_text& edrawtext, ::write_text::font* pfont, double dFontWidth, ::draw2d::brush* pbrush = nullptr, bool bMeasure = false);


inline auto gdiplus_color(const ::color::color& color)
{

   return Gdiplus::Color(color.alpha, color.red, color.green, color.blue);

}


#include "object.h"
#include "pen.h"
#include "bitmap.h"
#include "brush.h"
#include "font.h"
#include "region.h"
#include "image.h"
#include "path.h"


#include "graphics.h"


#include "draw2d.h"



//#define GDIPLUS_GRAPHICS(pgraphics) (dynamic_cast < ::draw2d_gdiplus::graphics * > (dynamic_cast < ::draw2d::graphics * > (pgraphics)))
//#define GDIPLUS_HDC(pgraphics) ((dynamic_cast < ::draw2d_gdiplus::graphics * > (dynamic_cast < ::draw2d::graphics * > (pgraphics)))->get_handle())



#define __graphics(pgraphics) ((::draw2d_gdiplus::graphics *) pgraphics->m_pthis)
#define __pen(ppen) ((::draw2d_gdiplus::pen *) ppen->m_pthis)
#define __brush(pbrush) ((::draw2d_gdiplus::brush *) pbrush->m_pthis)
#define __font(pfont) ((::draw2d_gdiplus::font *) pfont->m_pthis)
#define __graphics_path(ppath) ((::draw2d_gdiplus::path *) ppath->m_pthis)




class g_keep
{

public:


   Gdiplus::Graphics* m_p;
   Gdiplus::GraphicsState     m_state;


   g_keep(Gdiplus::Graphics* p)
   {

      m_p = p;

      m_state = m_p->Save();

   }

   ~g_keep()
   {

      m_p->Restore(m_state);

   }

};
