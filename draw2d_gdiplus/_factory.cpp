#include "framework.h"
#include "image.h"
#include "graphics.h"
#include "bitmap.h"
#include "pen.h"
#include "brush.h"
#include "region.h"
#include "font.h"
#include "internal_font.h"
#include "path.h"
#include "draw2d.h" 

//BEGIN_FACTORY(draw2d_gdiplus)
//FACTORY_ITEM(::draw2d_gdiplus::image)
//FACTORY_ITEM(::draw2d_gdiplus::graphics)
//FACTORY_ITEM(::draw2d_gdiplus::bitmap)
//FACTORY_ITEM(::draw2d_gdiplus::pen)
//FACTORY_ITEM(::draw2d_gdiplus::brush)
//FACTORY_ITEM(::draw2d_gdiplus::region)
//FACTORY_ITEM(::draw2d_gdiplus::font)
//FACTORY_ITEM(::draw2d_gdiplus::path)
//FACTORY_ITEM(::draw2d_gdiplus::draw2d)
//END_FACTORY()
//
//

__FACTORY_EXPORT void draw2d_gdiplus_factory(::factory::factory * pfactory)
{


   pfactory->add_factory_item < ::draw2d_gdiplus::image, ::image::image >();
   pfactory->add_factory_item < ::draw2d_gdiplus::graphics, ::draw2d::graphics >();
   pfactory->add_factory_item < ::draw2d_gdiplus::bitmap, ::draw2d::bitmap >();
   pfactory->add_factory_item < ::draw2d_gdiplus::pen, ::draw2d::pen >();
   pfactory->add_factory_item < ::draw2d_gdiplus::brush, ::draw2d::brush >();
   pfactory->add_factory_item < ::draw2d_gdiplus::region, ::draw2d::region >();
   pfactory->add_factory_item < ::draw2d_gdiplus::font, ::write_text::font >();
   pfactory->add_factory_item < ::draw2d_gdiplus::internal_font, ::write_text::internal_font >();
   pfactory->add_factory_item < ::draw2d_gdiplus::path, ::draw2d::path >();
   pfactory->add_factory_item < ::draw2d_gdiplus::draw2d, ::draw2d::draw2d >();


}



