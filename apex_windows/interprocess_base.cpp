// created by Camilo 2021-01-31 05:36 BRT <3CamiloSasukeThomasBorregaardSoerensen
// From interprocess_communcation by camilo on 2022-10-11 15:33 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "interprocess_base.h"
#include "apex/operating_system.h"
//#include "apex/platform/app_core.h"
//#include "interprocess_handler.h"
#include "apex/platform/launcher.h"
#include "launcher.h"


namespace apex_windows
{



   interprocess_base::interprocess_base()
   {

      set_hwnd(nullptr);

   }


   interprocess_base::~interprocess_base()
   {

      if (get_hwnd() != nullptr)
      {

         ::DestroyWindow((HWND)get_hwnd());

         set_hwnd(nullptr);

      }

   }




} // namespace apex_windows



