#include "framework.h"


namespace aura
{


   namespace windows
   {


      node::node()
      {

         m_pauranode = this;

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


      ::color::color node::get_default_color(::u64 u)
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


      void node::set_console_colors(::u32 dwScreenColors, ::u32 dwPopupColors, ::u32 dwWindowAlpha)
      {

         ::windows::registry::key key(HKEY_CURRENT_USER, "Console", true);

         key._set("ScreenColors", dwScreenColors);
         key._set("PopupColors", dwPopupColors);
         key._set("WindowAlpha", dwWindowAlpha);

      }



      ::e_status node::set_system_dark_mode1(bool bSet)
      {

         ::windows::registry::key key(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Themes\\Personalize", true);

         ::u32 dwSystemUseLightTheme;
         if (bSet)
         {
            dwSystemUseLightTheme = 0;
         }
         else
         {
            dwSystemUseLightTheme = 1;
         }

         key._set("SystemUsesLightTheme", dwSystemUseLightTheme);
         return ::success;

      }


      ::e_status node::set_app_dark_mode1(bool bSet)
      {

         ::windows::registry::key key(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Themes\\Personalize", true);

         ::u32 dwAppsUseLightTheme;
         if (bSet)
         {
            dwAppsUseLightTheme = 0;
         }
         else
         {
            dwAppsUseLightTheme = 1;
         }

         key._set("AppsUseLightTheme", dwAppsUseLightTheme);

         return ::success;

      }


      double node::get_time_zone()
      {

         double dTimeZone = 0.;

#ifdef WINDOWS
         {
            //time_t t = time(nullptr);

            //struct tm *p = localtime(&t);

            DYNAMIC_TIME_ZONE_INFORMATION i = {};

            ::u32 dw = GetDynamicTimeZoneInformation(&i);

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

            time_t t = time(nullptr);

            struct tm lt = { 0 };

            localtime_r(&t, &lt);

            //printf("Offset to GMT is %lds.\n", lt.tm_gmtoff);

            //printf("The time zone is '%s'.\n", lt.tm_zone);

            dTimeZone = +((double)lt.tm_gmtoff / (60.0 * 60.0));

         }
#endif

         return dTimeZone;

      }


      ::e_status node::open_folder(::file::path& pathFolder)
      {

         wstring wstrFolder(pathFolder);

         int i = (int)(iptr) ::ShellExecuteW(nullptr, L"open", wstrFolder, nullptr, nullptr, SW_NORMAL);

         if (i < 32)
         {

            switch (i)
            {
            case 0:
               //The operating system is out of memory or resources.
               return error_no_memory;
            case ERROR_FILE_NOT_FOUND:
               return error_file_not_found;
               //The specified file was not found.
            case ERROR_PATH_NOT_FOUND:
               return error_path_not_found;
               //            The specified path was not found.
            case          ERROR_BAD_FORMAT:
               return error_bad_format;
               //The.exe file is invalid(non - Win32.exe or error in.exe image).
               //case SE_ERR_ACCESSDENIED:
               //         return error_access_denied;
               ////The operating system denied access to the specified file.
               //SE_ERR_ASSOCINCOMPLETE
               //The file name association is incomplete or invalid.
               //SE_ERR_DDEBUSY
               //The DDE transaction could not be completed because other DDE transactions were being processed.
               //SE_ERR_DDEFAIL
               //The DDE transaction failed.
               //SE_ERR_DDETIMEOUT
               //The DDE transaction could not be completed because the request timed out.
               //SE_ERR_DLLNOTFOUND
               //The specified DLL was not found.
               //SE_ERR_FNF
               //The specified file was not found.
               //SE_ERR_NOASSOC
               //There is no application associated with the given file name extension.This error will also be returned if you attempt to print a file that is not printable.
               //SE_ERR_OOM
               //There was not enough memory to complete the operation.
               //SE_ERR_PNF
               //The specified path was not found.
               //SE_ERR_SHARE
               //A sharing violation occurred.*/
            default:
               return error_failed;
            }

         }

         return ::success;

      }

      ::e_status node::register_dll(const ::file::path& pathDll)
      {


         string strPathDll;

         //#ifdef _DEBUG

         strPathDll = pathDll;

         //#else
         //
         //   strPathDll = ::dir::matter() / "time" / process_platform_dir_name() /"stage/_desk_tb.dll";
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

         property_set set;

         set["privileged"] = true;

         if (!call_sync(path, strParam, path.folder(), ::e_display_none, 3_min, set))
         {

            return false;

         }

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

         return true;

      }


      ::e_status node::system_main()
      {

         //__pointer(::node::system) psystem = m_psystem;

         auto psystem = m_psystem;

         auto estatus = psystem->main();

         if (!estatus)
         {

            return estatus;

         }

         estatus = m_psystem->inline_term();

         if (!estatus)
         {

            return estatus;

         }

         return estatus;


      }


      int _os_message_box(const ::string & pszMessage, const ::string & pszTitle, const ::e_message_box& emessagebox)
      {

         int iMessageBox = emessagebox.m_eenum & 0x7f;

         wstring wstrText(pszMessage);

         wstring wstrTitle(pszTitle);

         int iResult = ::MessageBox(nullptr, wstrText, wstrTitle, iMessageBox);

         return iResult;

      }


   } // namespace windows


} // namespace aura



