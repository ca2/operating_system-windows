#include "framework.h"


extern "C"
void draw2d_gdiplus_factory_exchange(::factory_map * pfactorymap)
{

   create_factory < ::draw2d_gdiplus::image, ::image >();
   create_factory < ::draw2d_gdiplus::graphics, ::draw2d::graphics >();
   create_factory < ::draw2d_gdiplus::bitmap, ::draw2d::bitmap >();
   create_factory < ::draw2d_gdiplus::pen, ::draw2d::pen >();
   create_factory < ::draw2d_gdiplus::brush, ::draw2d::brush >();
   create_factory < ::draw2d_gdiplus::region, ::draw2d::region >();
   create_factory < ::draw2d_gdiplus::font, ::write_text::font >();
   create_factory < ::draw2d_gdiplus::path, ::draw2d::path >();
   create_factory < ::draw2d_gdiplus::draw2d, ::draw2d::draw2d >();

}



