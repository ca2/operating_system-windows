#pragma once


#include "aura/.h"



#ifdef _DRAW2D_GDI_LIBRARY
#define CLASS_DECL_DRAW2D_GDI  CLASS_DECL_EXPORT
#else
#define CLASS_DECL_DRAW2D_GDI  CLASS_DECL_IMPORT
#endif


#include "draw2d_gdi_factory_exchange.h"



#include "draw2d_gdi_object.h"
#include "draw2d_gdi_pen.h"
#include "draw2d_gdi_bitmap.h"
#include "draw2d_gdi_brush.h"
#include "draw2d_gdi_font.h"
#include "draw2d_gdi_palette.h"
#include "draw2d_gdi_region.h"
#include "draw2d_gdi_image_impl.h"
#include "draw2d_gdi_path.h"


#include "draw2d_gdi_graphics.h"





#define GDI_GRAPHICS(pgraphics) (dynamic_cast < ::draw2d_gdi::graphics * > (dynamic_cast < ::draw2d::graphics * > (pgraphics)))
#define GDI_HDC(pgraphics) ((dynamic_cast < ::draw2d_gdi::graphics * > (dynamic_cast < ::draw2d::graphics * > (pgraphics)))->get_handle())
#define GDI_DIB(imageimpl) (dynamic_cast < ::draw2d_gdi::image_impl * > (imageimpl))
#define GDI_BRUSH(pbrush) (dynamic_cast < ::draw2d_gdi::brush * > (dynamic_cast < ::draw2d::brush * > (pbrush)))
#define GDI_PEN(ppen) (dynamic_cast < ::draw2d_gdi::pen * > (dynamic_cast < ::draw2d::pen * > (ppen)))
#define GDI_FONT(pfont) (dynamic_cast < ::draw2d_gdi::font * > (dynamic_cast < ::write_text::font * > (pfont)))
#define GDI_BITMAP(pbitmap) (dynamic_cast < ::draw2d_gdi::bitmap * > (dynamic_cast < ::draw2d::bitmap * > (pbitmap)))
#define GDI_REGION(pregion) (dynamic_cast < ::draw2d_gdi::region * > (dynamic_cast < ::draw2d::region * > (pregion)))


#define argb_invert(color32) argb(colorref_get_a_value(color32),colorref_get_b_value(color32),colorref_get_g_value(color32),colorref_get_r_value(color32))


namespace draw2d_gdi
{


   template < class T >
   void attach(const ::draw2d::graphics * pgraphicsConst, const __pointer(T) & objectConst, int iType)
   {

      ::draw2d::graphics_pointer & pgraphics = (::draw2d::graphics *) pgraphicsConst;
      __pointer(T) & o = (__pointer(T) &) objectConst;

      if (o.is_null())
         o.alloc((::draw2d::graphics *) pgraphicsConst);

      ::draw2d_gdi::object * pgdiobject = dynamic_cast <::draw2d_gdi::object *> (o.m_p);

      if (pgdiobject == nullptr)
         throw invalid_argument_exception();

      pgdiobject->Attach(::GetCurrentObject(GDI_GRAPHICS(pgraphics)->get_handle2(), iType));

   }


} // namespace draw2d_gdi



