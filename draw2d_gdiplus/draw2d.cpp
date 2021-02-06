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


   ::e_status draw2d::initialize(::layered * pobjectContext)
   {

      auto estatus = ::draw2d::draw2d::initialize(pobjectContext);

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


} // namespace draw2d_gdiplus



