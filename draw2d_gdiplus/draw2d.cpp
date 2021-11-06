#include "framework.h"


CLASS_DECL_DRAW2D_GDIPLUS ::e_status initialize_gdiplus();
CLASS_DECL_DRAW2D_GDIPLUS ::e_status terminate_gdiplus();


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


   ::e_status draw2d::initialize(::object * pobject)
   {

      auto estatus = ::draw2d::draw2d::initialize(pobject);

      if (!estatus)
      {

         return estatus;

      }
   
      estatus = initialize_gdiplus();

      if (!estatus)
      {

         return estatus;

      }

      return estatus;
   
   }


   string draw2d::write_text_get_default_library_name()
   {

      return "win32";

   }

} // namespace draw2d_gdiplus



