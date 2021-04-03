#pragma once


#include "aura/_.h"
#include "aura/operating_system.h"
#include "apex/operating_system.h"
#include "apex_windows/_.h"


#if defined(_AURA_WINDOWS_LIBRARY)
#define CLASS_DECL_AURA_WINDOWS  CLASS_DECL_EXPORT
#else
#define CLASS_DECL_AURA_WINDOWS  CLASS_DECL_IMPORT
#endif


::e_status gdiplus_draw_text(::draw2d::graphics * pgraphics, ::draw2d::path * ppath, const string & str, rectangle_f64 & rectParam, const ::e_align & ealign, const ::e_draw_text & edrawtext, ::write_text::font * pfont, double dFontWidth, ::draw2d::brush * pbrush = nullptr, bool bMeasure = false);


//inline auto gdiplus_color(const ::color::color& color)
//{
//   return Gdiplus::Color(color.m_iA, color.m_iR, color.m_iG, color.m_iB);
//}
//
//
//
//#define __graphics(pgraphics) ((::draw2d_gdiplus::graphics *) pgraphics->m_pthis)
//#define __pen(ppen) ((::draw2d_gdiplus::pen *) ppen->m_pthis)
//#define __brush(pbrush) ((::draw2d_gdiplus::brush *) pbrush->m_pthis)
//#define __font(pfont) ((::draw2d_gdiplus::font *) pfont->m_pthis)
//#define __graphics_path(ppath) ((::draw2d_gdiplus::path *) ppath->m_pthis)
//
//
//
//
//class g_keep
//{
//
//public:
//
//   Gdiplus::Graphics* point_i32;
//   Gdiplus::GraphicsState s;
//
//   g_keep(Gdiplus::Graphics* point1)
//   {
//
//      point = point1;
//
//      s = point_i32->Save();
//
//   }
//
//   ~g_keep()
//   {
//
//      point_i32->Restore(s);
//
//   }
//
//};


//#include "tts_speaker.h"



//#include "node.h"



