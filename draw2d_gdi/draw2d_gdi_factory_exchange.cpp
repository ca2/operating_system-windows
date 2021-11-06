#include "framework.h"


namespace draw2d_gdi
{


   factory_exchange::factory_exchange(::object * pobject) :
      object(pobject)
   {

      init_draw2d_gdi_mutex(pobject);

      create_factory < image_impl, ::image_impl >();
      create_factory < pgraphics, ::draw2d::graphics >();
      create_factory < bitmap, ::draw2d::bitmap >();
      create_factory < pen, ::draw2d::pen >();
      create_factory < brush, ::draw2d::brush >();
      create_factory < palette, ::draw2d::palette >();
      create_factory < region, ::draw2d::region >();
      create_factory < font, ::write_text::font >();
      create_factory < path, ::draw2d::path >();

   }


   factory_exchange::~factory_exchange()
   {

   }


} // namespace draw2d_gdi


void factory_exchange(::object * pobject)
{

   draw2d_gdi::factory_exchange factoryexchange(pobject);

}




