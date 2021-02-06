#include "framework.h"
#include "acme/node/windows/registry.h"


namespace node_windows
{


   node::node()
   {


   }


   node::~node()
   {


   }


   string node::get_user_name()
   {

      WCHAR wsz[1024];

      DWORD dwSize = sizeof(wsz) / sizeof(WCHAR);

      ::GetUserNameW(wsz, &dwSize);

      return string(wsz);

   }
#include "aura/os/windows/_c.h"


   bool node::_os_calc_app_dark_mode()
   {

      try
      {

         ::windows::registry::key key;

         key.open(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Themes\\Personalize");

         ::u32 dw;

         auto estatus = key._get("AppsUseLightTheme", dw);

         if (::failed(estatus))
         {

            estatus = key._get("SystemUseLightTheme", dw);

            if (::failed(estatus))
            {

               return false;

            }

         }

         return dw == 0;

      }
      catch (...)
      {

         return false;

      }

   }


   bool node::_os_calc_system_dark_mode()
   {

      try
      {

         ::windows::registry::key key;

         key.open(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Themes\\Personalize");

         ::u32 dw;

         auto estatus = key._get("SystemUseLightTheme", dw);

         if (::failed(estatus))
         {

            estatus = key._get("AppsUseLightTheme", dw);

            if (::failed(estatus))
            {

               return false;

            }

         }

         return dw == 0;

      }
      catch (...)
      {

         return false;

      }

   }


} // namespace node_windows






int _os_message_box(const char * pszMessage, const char * pszTitle, const ::e_message_box & emessagebox)
{

   int iMessageBox = emessagebox.m_eenum & 0x7f;

   wstring wstrText(pszMessage);

   wstring wstrTitle(pszTitle);

   int iResult = ::MessageBox(nullptr, wstrText, wstrTitle, iMessageBox);

   return iResult;

}

