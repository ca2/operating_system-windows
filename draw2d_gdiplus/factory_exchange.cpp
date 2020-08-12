#include "framework.h"


namespace draw2d_gdiplus
{


#define new AURA_NEW


   factory_exchange::factory_exchange()
   {

      create_factory < image, ::image >();
      create_factory < graphics, ::draw2d::graphics >();
      create_factory < bitmap, ::draw2d::bitmap >();
      create_factory < pen, ::draw2d::pen >();
      create_factory < brush, ::draw2d::brush >();
      //create_factory < palette, ::draw2d::palette >();
      create_factory < region, ::draw2d::region >();
      create_factory < font, ::draw2d::font >();
      create_factory < path, ::draw2d::path >();
      //create_factory < printer, ::draw2d::printer >();

//#undef new
//
//      Gdiplus::Region * pregion = new Gdiplus::Region();
//
//      output_debug_string("teshtchee!!");

   }


   factory_exchange::~factory_exchange()
   {
   }


} // namespace draw2d_gdiplus



extern "C"
void draw2d_factory_exchange()
{

   draw2d_gdiplus::factory_exchange factoryexchange;

}

#ifdef CUBE

void initialize_draw2d_factory_exchange()
{

   g_pfnfactoryexchangeDraw2d = &draw2d_factory_exchange;

}

#endif




draw2d_gdiplus::factory_exchange factoryexchange;