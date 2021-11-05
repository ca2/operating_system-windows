// Created by camilo on 2021/09/12 16:06 BRT <3TBS!!
#include "framework.h"
#include "mouse_hook.h"
#include "keyboard_hook.h"


namespace windowing_win32
{



   node::node()
   {

   }

   
   node::~node()
   {

   }


   ::e_status node::install_keyboard_hook(::matter * pmatterListener)
   {

      auto estatus = ::keyboard_hook::install(pmatterListener);

      if (estatus.succeeded())
      {

         fork(__routine([]()
            {

               ::keyboard_hook::run();

            }));

      }

      if (!estatus)
      {

         return estatus;

      }

      return estatus;

   }


   ::e_status node::uninstall_keyboard_hook(::matter * pmatterListener)
   {

      auto estatus = ::keyboard_hook::uninstall(pmatterListener);

      if (!estatus)
      {

         return estatus;

      }

      return estatus;

   }


   ::e_status node::install_mouse_hook(::matter * pmatterListener)
   {

      auto estatus = ::mouse_hook::install(pmatterListener);

      if (estatus.succeeded())
      {

         fork(__routine([]()
            {

               ::mouse_hook::run();

            }));

      }

      if (!estatus)
      {

         return estatus;

      }

      return estatus;

   }


   ::e_status node::uninstall_mouse_hook(::matter * pmatterListener)
   {

      auto estatus = ::mouse_hook::uninstall(pmatterListener);

      if (!estatus)
      {

         return estatus;

      }

      return estatus;

   }



} // namespace linux



