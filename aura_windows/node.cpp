#include "framework.h"
#include "node.h"
#include "acme/platform/system.h"
#include "acme_windows/registry.h"
#include "apex/input/input.h"
#include "acme/_operating_system.h"
#include <shellapi.h>


namespace aura_windows
{


   node::node()
   {

      //m_pauranode = this;
      //m_pAuraPlatform = this;

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


   bool node::_os_calc_app_dark_mode()
   {

      try
      {

         ::acme_windows::registry::key key;

         key.open(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Themes\\Personalize");

         DWORD dwAppsUseLightTheme = 0;

         auto bOk = key._get("AppsUseLightTheme", dwAppsUseLightTheme);

         if (!bOk)
         {

            return false;

         }

         return dwAppsUseLightTheme == 0;

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

         ::acme_windows::registry::key key;

         key.open(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Themes\\Personalize");

         DWORD dwSystemUseLightTheme;

         auto bOk = key._get("SystemUseLightTheme", dwSystemUseLightTheme);

         if (!bOk)
         {

            return false;

         }

         return dwSystemUseLightTheme == 0;

      }
      catch (...)
      {

         return false;

      }

   }


   ::color::color node::get_default_color(unsigned long long u)
   {

      switch (u)
      {
      case COLOR_3DFACE:
         return argb(127, 192, 192, 200);
      case COLOR_WINDOW:
         return argb(127, 255, 255, 255);
      case COLOR_3DLIGHT:
         return argb(127, 218, 218, 210);
      case COLOR_3DHIGHLIGHT:
         return argb(127, 238, 238, 230);
      case COLOR_3DSHADOW:
         return argb(127, 138, 138, 130);
      case COLOR_3DDKSHADOW:
         return argb(127, 90, 90, 80);
      default:
         break;
      }

      return argb(127, 0, 0, 0);

   }


   void node::set_console_colors(unsigned int dwScreenColors, unsigned int dwPopupColors, unsigned int dwWindowAlpha)
   {

      ::acme_windows::registry::key key(HKEY_CURRENT_USER, "Console", true);

      key._set("ScreenColors", dwScreenColors);
      key._set("PopupColors", dwPopupColors);
      key._set("WindowAlpha", dwWindowAlpha);

   }



   double node::get_time_zone()
   {

      double dTimeZone = 0.;

#ifdef WINDOWS
      {
         //posix_time t = time(nullptr);

         //struct tm *p = localtime(&t);

         DYNAMIC_TIME_ZONE_INFORMATION i = {};

         unsigned int dw = GetDynamicTimeZoneInformation(&i);

         if (dw == TIME_ZONE_ID_STANDARD)
         {

            dTimeZone = -((double)(i.Bias + i.StandardBias) / 60.0);

         }
         else if (dw == TIME_ZONE_ID_DAYLIGHT)
         {

            dTimeZone = -((double)(i.Bias + i.DaylightBias) / 60.0);

         }
         else
         {

            dTimeZone = -((double)i.Bias / 60.0);

         }

      }
#else
      {

         posix_time t = time(nullptr);

         struct tm lt = { 0 };

         localtime_r(&t, &lt);

         //printf("Offset to GMT is %lds.\n", lt.tm_gmtoff);

         //printf("The time zone is '%s'.\n", lt.tm_zone);

         dTimeZone = +((double)lt.tm_gmtoff / (60.0 * 60.0));

      }
#endif

      return dTimeZone;

      }


   void node::open_folder(::file::path& pathFolder)
   {

      wstring wstrFolder(pathFolder);

      int i = (int)(iptr) ::ShellExecuteW(nullptr, L"open", wstrFolder, nullptr, nullptr, SW_NORMAL);

      if (i < 32)
      {

         auto estatus = ::windows::last_error_status(i);

         //switch (i)
         //{
         //case 0:
         //   //The operating system is out of memory or resources.
         //   return error_no_memory;
         //case ERROR_FILE_NOT_FOUND:
         //   return error_file_not_found;
         //   //The specified file was not found.
         //case ERROR_PATH_NOT_FOUND:
         //   return error_path_not_found;
         //   //            The specified path was not found.
         //case          ERROR_BAD_FORMAT:
         //   return error_bad_format;
         //   //The.exe file is invalid(non - Win32.exe or error in.exe image).
         //   //case SE_ERR_ACCESSDENIED:
         //   //         return error_access_denied;
         //   ////The operating system denied access to the specified file.
         //   //SE_ERR_ASSOCINCOMPLETE
         //   //The file name association is incomplete or invalid.
         //   //SE_ERR_DDEBUSY
         //   //The DDE transaction could not be completed because other DDE transactions were being processed.
         //   //SE_ERR_DDEFAIL
         //   //The DDE transaction failed.
         //   //SE_ERR_DDETIMEOUT
         //   //The DDE transaction could not be completed because the request timed out.
         //   //SE_ERR_DLLNOTFOUND
         //   //The specified DLL was not found.
         //   //SE_ERR_FNF
         //   //The specified file was not found.
         //   //SE_ERR_NOASSOC
         //   //There is no application associated with the given file name extension.This error will also be returned if you attempt to print a file that is not printable.
         //   //SE_ERR_OOM
         //   //There was not enough memory to complete the operation.
         //   //SE_ERR_PNF
         //   //The specified path was not found.
         //   //SE_ERR_SHARE
         //   //A sharing violation occurred.*/
         //default:
         //   return error_failed;
         //}

      }

      //return ::success;

   }

   void node::register_dll(const ::file::path& pathDll)
   {


      string strPathDll;

      //#ifdef _DEBUG

      strPathDll = pathDll;

      //#else
      //
      //   strPathDll = ::dir::matter() / "time" / process_platform_name() /"stage/_desk_tb.dll";
      //
      //#endif

      string strParam;

      strParam = "/s \"" + strPathDll + "\"";

      //wstring wstrParam(strParam);

      //STARTUPINFOW si = {};

      //si.cb = sizeof(si);

      //si.wShowWindow = SW_HIDE;

      //PROCESS_INFORMATION pi = {};

      WCHAR wszSystem[2048];

      GetSystemDirectoryW(wszSystem, sizeof(wszSystem) / sizeof(WCHAR));

      wstring wstrSystem(wszSystem);

      ::file::path path(wstrSystem);

      path /= "regsvr32.exe";

      ::property_set set;

      set["privileged"] = true;


      int iExitCode = 0;

      call_sync(path, strParam, path.folder(), ::e_display_none, 3_min, set, &iExitCode);

      //if (!call_sync(path, strParam, path.folder(), ::e_display_none, 3_min, set))
      //{

      //   return false;

      //}

      //if (CreateProcessW(wstrPath, wstrParam, nullptr, nullptr, false, 0, nullptr, wstrSystem, &si, &pi))
      //{

      //   output_debug_string("created");

      //}
      //else
      //{

      //   output_debug_string("not created");

      //}

      //CloseHandle(pi.hProcess);

      //CloseHandle(pi.hthread);

      //return true;

   }


   void node::node_main()
   {

      //auto pacmesystem = system();

      //pacmesystem->main();

      ::apex_windows::node::node_main();

   }


   void node::system_main()
   {

      apex_windows::node::system_main();

      //::pointer<::node::system>psystem = system();

      //auto psystem = system();

      //auto estatus = 

//      psystem->main();

      //if (!estatus)
      //{

      //   return estatus;

      //}

      /*estatus = system()->inline_term();

      if (!estatus)
      {

         return estatus;

      }*/

      //return estatus;


   }


   int _os_message_box(const ::scoped_string & scopedstrMessage, const ::scoped_string & scopedstrTitle, const ::e_message_box& emessagebox)
   {

      int iMessageBox = emessagebox.m_eenum & 0x7f;

      wstring wstrText(pszMessage);

      wstring wstrTitle(pszTitle);

      int iResult = ::MessageBox(nullptr, wstrText, wstrTitle, iMessageBox);

      return iResult;

   }


   ::pointer < ::input::input > node::create_input()
   {

      auto pfactory = system()->factory("input", "win32");

      auto pinput = __øcreate<::input::input >(pfactory);

      pinput->initialize(this);

      return pinput;

   }


} // namespace aura_windows



