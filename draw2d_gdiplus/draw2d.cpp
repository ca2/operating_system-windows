#include "platform.h"
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


   ::draw2d::graphics_pointer draw2d::do_allocation_strategy(::acme::user::interaction * pacmeuserinteractionAffinity, ::image::image * pimage,
                                             const ::i32_size & size)
   {

      if (::is_set(pimage))
      {

         auto pdraw2dgraphics = create_newø<::draw2d_gdiplus::graphics>();

         //pdraw2dgraphics->create_bitmap_graphics(pimage->get_bitmap());

         pdraw2dgraphics->update_as_image_render_target(pimage);

         return pdraw2dgraphics;

      }

      return ::draw2d::draw2d::do_allocation_strategy(pacmeuserinteractionAffinity, pimage, size);

}



   void draw2d::do_release_to_pool_strategy(::draw2d::graphics_pointer &pdraw2dgraphics, ::image::image * pimage)
   {
         
      pdraw2dgraphics.release();
      
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



