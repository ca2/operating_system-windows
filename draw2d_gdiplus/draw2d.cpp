#include "framework.h"


CLASS_DECL_ACME ::e_status init_gdiplus();
CLASS_DECL_ACME ::e_status term_gdiplus();


namespace draw2d_gdiplus
{


   draw2d::draw2d()
   {

      

   }


   draw2d::~draw2d()
   {

      term_gdiplus();

   }


   ::e_status draw2d::initialize(::layered * pobjectContext)
   {

      auto estatus = ::draw2d::draw2d::initialize(pobjectContext);

      if (!estatus)
      {

         return estatus;

      }
   
      estatus = init_gdiplus();

      if (!estatus)
      {

         return estatus;

      }

      return estatus;
   
   }


} // namespace draw2d_gdiplus



