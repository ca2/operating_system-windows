//
// Created by camilo on 05/12/2020. <3tbs!!
//
#include "framework.h"
//#include "acme/operating_system.h"


namespace acme
{


   //void system::inline_init()
   //{

   //   auto estatus = process_init();

   //   if (!estatus)
   //   {

   //      return estatus;

   //   }

   //   return ::success;

   //}


   void system::inline_term()
   {

      return ::success;

   }

   
   void system::on_end()
   {

      return ::success;

   }


   void system::os_construct()
   {


   }


   ::enum_operating_system system::get_operating_system() const
   {

      return ::e_operating_system_windows;

   }


   ::user::enum_desktop system::calc_edesktop()
   {

      return ::user::e_desktop_windows;

   }


} // namespace acme



