#include "framework.h"
#include "draw2d.h"
#include "graphics.h"
#include "aura/graphics/image/image.h"
#include "acme/prototype/prototype/memory.h"
#include "operating_system-windows/gdiplus_library/_.h"


namespace draw2d_gdiplus
{


   draw2d::draw2d()
   {
      
      initialize_gdiplus();

      m_bUseGraphicsPool = false;

   }


   draw2d::~draw2d()
   {

      terminate_gdiplus();

   }


   void draw2d::initialize(::particle * pparticle)
   {

      //auto estatus = 
      
      ::draw2d::draw2d::initialize(pparticle);

      //if (!estatus)
      //{

      //   return estatus;

      //}
   
   }


   ::draw2d::graphics_pointer draw2d::do_allocation_strategy(::draw2d::host * pdraw2dhost, ::image::image * pimage,
                                             const ::i32_size & size)
   {

      if (::is_set(pimage))
      {

         auto pgraphics = create_newø<::draw2d_gdiplus::graphics>();

         pgraphics->create_draw2d_graphics(pimage->get_bitmap());

         return pgraphics;

      }

      return ::draw2d::draw2d::do_allocation_strategy(pdraw2dhost, pimage, size);

}



   void draw2d::do_release_to_pool_strategy(::draw2d::graphics_pointer &pgraphics)
   {
         
      pgraphics.release();
      
   }




   string draw2d::write_text_get_default_implementation_name()
   {

      return "win32";

   }


   void draw2d::adjust_composited_window_styles(::u32& nExStyle, ::u32& nStyle)
   {

      nExStyle |= WS_EX_LAYERED;

   }


} // namespace draw2d_gdiplus



