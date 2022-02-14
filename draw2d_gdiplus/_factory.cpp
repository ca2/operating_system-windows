#include "framework.h"


__FACTORY_EXPORT void draw2d_gdiplus_factory(::factory::factory * pfactory)
{


   //pfactory->add_factory_item < ::draw2d_gdiplus::image, ::image >();
   pfactory->add_factory_item < ::draw2d_gdiplus::graphics, ::draw2d::graphics >();
   pfactory->add_factory_item < ::draw2d_gdiplus::bitmap, ::draw2d::bitmap >();
   pfactory->add_factory_item < ::draw2d_gdiplus::pen, ::draw2d::pen >();
   pfactory->add_factory_item < ::draw2d_gdiplus::brush, ::draw2d::brush >();
   pfactory->add_factory_item < ::draw2d_gdiplus::region, ::draw2d::region >();
   pfactory->add_factory_item < ::draw2d_gdiplus::font, ::write_text::font >();
   pfactory->add_factory_item < ::draw2d_gdiplus::path, ::draw2d::path >();
   pfactory->add_factory_item < ::draw2d_gdiplus::draw2d, ::draw2d::draw2d >();


}



