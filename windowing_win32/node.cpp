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


   ::e_status node::register_extended_event_listener(::matter * pmatter, bool bMouse, bool bKeyboard)
   {

      ::e_status estatusMouse = ::success_none;

      ::e_status estatusKeyboard = ::success_none;

      if (bMouse)
      {

         estatusMouse = ::mouse_hook::install(pmatter);

         if (estatusMouse.succeeded())
         {

            fork(__routine([]()
               {

                  ::mouse_hook::run();

               }));

         }

      }

      if (bKeyboard)
      {

         estatusKeyboard = ::keyboard_hook::install(pmatter);

         if (estatusKeyboard.succeeded())
         {

            fork(__routine([]()
               {

                  ::keyboard_hook::run();

               }));

         }

      }

      auto estatus = estatusMouse & estatusKeyboard;

      return estatus;

   }


   ::e_status node::unregister_extended_event_listener(::matter * pmatter, bool bMouse, bool bKeyboard)
   {

      ::e_status estatusMouse = ::success_none;

      ::e_status estatusKeyboard = ::success_none;

      if (bMouse)
      {

         estatusMouse = ::mouse_hook::uninstall(pmatter);


      }

      if (bKeyboard)
      {

         estatusKeyboard = ::keyboard_hook::uninstall(pmatter);

      }

      auto estatus = estatusMouse & estatusKeyboard;

      return estatus;

   }


} // namespace linux



