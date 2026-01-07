// Created by camilo on 2026-01-06 22:33 <3ThomasBorregaardSørensen!!
#include "framework.h"
#include "allocator.h"



namespace typeface_gdiplus
{


   allocator::allocator() {}


   allocator ::~allocator() {}

   
   ::pointer<::typeface::typeface> allocator::create_typeface(const ::scoped_string &scopedstrName)
   {

      if (scopedstrName == "gdiplus" || scopedstrName.is_empty())
      {

         return ::øcreate_new<::typeface_gdiplus::typeface>();
      }
      else
      {

         throw ::exception(error_wrong_state, "not know typeface");
      }

      return {};
   }


   ::pointer<::typeface::face> allocator::create_face(const ::scoped_string &scopedstrName)
   {

      if (scopedstrName == "gdiplus" || scopedstrName.is_empty())
      {

         return ::øcreate_new<::typeface_gdiplus::face>();
      }
      else
      {

         throw ::exception(error_wrong_state, "not know face");
      }


      throw ::interface_only();

      return {};
   }


} // namespace typeface
