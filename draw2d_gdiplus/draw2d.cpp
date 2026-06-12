#include "framework.h"
#include "draw2d.h"
#include "acme/prototype/prototype/memory.h"
#include "operating_system-windows/gdiplus_library/_.h"


namespace draw2d_gdiplus
{


   draw2d::draw2d()
   {
      
      initialize_gdiplus();


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


   string draw2d::write_text_get_default_implementation_name()
   {

      return "win32";

   }


   void draw2d::adjust_composited_window_styles(::u32& nExStyle, ::u32& nStyle)
   {

      nExStyle |= WS_EX_LAYERED;

   }


} // namespace draw2d_gdiplus



