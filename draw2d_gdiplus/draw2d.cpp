#include "framework.h"
#include "draw2d.h"
#include "acme/prototype/prototype/memory.h"


CLASS_DECL_DRAW2D_GDIPLUS void initialize_gdiplus();
CLASS_DECL_DRAW2D_GDIPLUS void terminate_gdiplus();


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
   
      //estatus = 
      
      initialize_gdiplus();

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //return estatus;
   
   }


   string draw2d::write_text_get_default_implementation_name()
   {

      return "win32";

   }





} // namespace draw2d_gdiplus



