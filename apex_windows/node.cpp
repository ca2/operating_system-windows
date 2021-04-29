#include "framework.h"
#include "apex/platform/node.h"
#include "acme/node/windows/registry.h"
#include "acme/filesystem/filesystem/acme_dir.h"
#include "acme/filesystem/filesystem/acme_path.h"
#include "acme_windows/node.h"
#include "node.h"
#include "aura/os/windows/_c.h"


namespace windows
{


   namespace apex
   {


      node::node()
      {

         m_papexnode = this;

         defer_initialize_winsock();

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


      ::e_status node::initialize(::object* pobject)
      {

         auto estatus = ::windows::acme::node::initialize(pobject);

         if (!estatus)
         {

            return estatus;

         }

         //if (!__node_apex_pre_init())
         //{

         //   return error_failed;

         //}

         //if (!__node_apex_pos_init())
         //{

         //   return error_failed;

         //}

         return estatus;

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
            return argb(127, 192, 192, 184);
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
         //   strPathDll = m_psystem->m_pacmedir->matter() / "time" / process_platform_dir_name() /"stage/_desk_tb.dll";
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

         auto estatus = m_psystem->m_papexsystem->m_papexnode->thread_initialize(m_psystem->m_papexsystem);

         if (!estatus)
         {

            return estatus;

         }

         estatus = m_psystem->on_start_system();

         if (!estatus)
         {

            return estatus;

         }

         estatus = m_psystem->main();

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


      ::e_status node::get_firefox_installation_info(string& strPathToExe, string& strInstallDirectory)
      {

#ifdef WINDOWS_DESKTOP

         try
         {

            ::windows::registry::key key(HKEY_LOCAL_MACHINE, "SOFTWARE\\Mozilla\\Mozilla Firefox");

            string strCurrentVersion;

            key.get("CurrentVersion", strCurrentVersion);

            key.open(HKEY_LOCAL_MACHINE, "SOFTWARE\\Mozilla\\Mozilla Firefox\\" + strCurrentVersion + "\\Main");

            key.get("PathToExe", strPathToExe);

            key.get("Install Directory", strInstallDirectory);

         }
         catch (const ::e_status& estatus)
         {

            return estatus;

         }

         return ::success;

#else

         return ::error_failed;

#endif

      }


      ::e_status node::_001InitializeShellOpen()
      {

         //ASSERT(m_atomApp == nullptr && m_atomSystemTopic == nullptr); // do once

         //m_atomApp            = ::GlobalAddAtomW(::str::international::utf8_to_unicode(m_strAppName));

         //m_atomSystemTopic    = ::GlobalAddAtomW(L"system");

         return ::success;

      }


      ::e_status node::process_init()
      {



         defer_initialize_winsock();
         return success;

      }


      string node::veriwell_multimedia_music_midi_get_default_library_name()
      {

         return "music_midi_mmsystem";

      }


      string node::multimedia_audio_mixer_get_default_library_name()
      {

         return "audio_mixer_mmsystem";

      }


      string node::multimedia_audio_get_default_library_name()
      {

         string str;

         if (file_exists(m_psystem->m_pacmedir->system() / "config\\system\\audio.txt"))
         {

            str = file_as_string(m_psystem->m_pacmedir->system() / "config\\system\\audio.txt");

         }
         else
         {

            ::file::path strPath;

            strPath = m_psystem->m_pacmedir->appdata() / "audio.txt";

            str = file_as_string(strPath);

         }

         if (str.has_char())
            return "audio_" + str;
         else
            return "audio_mmsystem";

      }

      bool node::is_application_installed(const ::file::path& pathExe, string strAppId, string& strBuild, const char* pszPlatform, const char* pszConfiguration, const char* pszLocale, const char* pszSchema)
      {

         ::file::path path;

         path = m_psystem->m_papexsystem->m_pdirsystem->application_installer_folder(pathExe, strAppId, pszPlatform, pszConfiguration, pszLocale, pszSchema) / "installed.txt";

         strBuild = file_as_string(path);

         return strBuild.has_char();

      }


      bool node::set_application_installed(const ::file::path& pathExe, string strAppId, const char* pszBuild, const char* pszPlatform, const char* pszConfiguration, const char* pszLocale, const char* pszSchema)
      {

         ::file::path path;

         path = m_psystem->m_papexsystem->m_pdirsystem->application_installer_folder(pathExe, strAppId, pszPlatform, pszConfiguration, pszLocale, pszSchema) / "installed.txt";

         return file_put_contents(path, pszBuild);

      }


      bool node::set_last_run_application_path(string strAppId)
      {

         ::file::path path = m_psystem->m_pacmepath->app_module();

         ::file::path pathFile = m_psystem->m_papexsystem->m_pdirsystem->get_last_run_application_path_file(strAppId);

         return file_put_contents(pathFile, path);

      }


      string node::get_version()
      {

         unichar pszModuleFilePath[MAX_PATH + 1];

         GetModuleFileNameW(nullptr, pszModuleFilePath, MAX_PATH + 1);

         DWORD dw;

         ::u32 dwResSize = GetFileVersionInfoSizeW(
            pszModuleFilePath,
            &dw);

         if (dwResSize > 0)
         {

            memory memory;

            memory.set_size(dwResSize);

            if (GetFileVersionInfoW(
               pszModuleFilePath,

               0,
               dwResSize,
               memory.get_data()))

            {
               ::u32 cbTranslate;
               struct LANGANDCODEPAGE
               {
                  ::u16 wLanguage;
                  ::u16 wCodePage;
               } *pTranslate;


               // read the list of languages and code pages.

               VerQueryValue(memory.get_data(),
                  TEXT("\\VarFileInfo\\Translation"),
                  (LPVOID*)&pTranslate,
                  &cbTranslate);

               string strKey;

               for (::u32 u = 0; u < (cbTranslate / sizeof(struct LANGANDCODEPAGE)); u++)
               {

                  WCHAR* psz;

                  UINT uSize;

                  //strKey.Format(
                  //"\\StringFileInfo\\%04x%04x\\FileDescription",
                  //pTranslate[u].wLanguage,
                  //pTranslate[u].wCodePage);

                  strKey.Format(
                     "\\StringFileInfo\\%04x%04x\\FileVersion",
                     pTranslate[u].wLanguage,
                     pTranslate[u].wCodePage);

                  wstring wstrKey(strKey);

                  // Retrieve file description for language and code page "i".
                  if (VerQueryValueW(memory.get_data(),
                     (WCHAR*)(const WCHAR*)wstrKey,
                     (LPVOID*)&psz,
                     &uSize))
                  {

                     string strVersion(psz, uSize);

                     return strVersion;

                  }

               }

            }

         }

         return "";

      }


      void node::show_wait_cursor(bool bShow)
      {

         if (bShow)
         {

            HCURSOR hcursorWait = ::LoadCursor(nullptr, IDC_WAIT);

            HCURSOR hcursorPrevious = ::SetCursor(hcursorWait);

            //     if(hcursorPrevious != hcursorWait)
            //         m_hcurWaitCursorRestore = hcursorPrevious;

         }
         else
         {

            //         ::SetCursor(m_hcurWaitCursorRestore);
         }

      }







      ::u32 node::get_current_directory(string& str)
      {

         return ::GetCurrentDirectoryW(MAX_PATH * 8, wtostring(str, MAX_PATH * 8));

      }


      ::u32 node::get_temp_path(string& str)
      {

         return ::GetTempPathW(MAX_PATH * 8, wtostring(str, MAX_PATH * 8));

      }


      ::i32 node::reg_query_value(HKEY hkey, const char* pszSubKey, string& str)
      {

         DWORD dwType = 0;
         DWORD dwSize = 0;
         ::i32 lResult = RegQueryValueExW(hkey, wstring(pszSubKey), nullptr, &dwType, nullptr, &dwSize);

         if (lResult != ERROR_SUCCESS)
            return lResult;
         ASSERT(dwType == REG_SZ || dwType == REG_MULTI_SZ || dwType == REG_EXPAND_SZ);
         if (dwType == REG_SZ || dwType == REG_MULTI_SZ || dwType == REG_EXPAND_SZ)
         {

            natural_wstring pwsz(byte_count, dwSize);

            lResult = RegQueryValueExW(hkey, wstring(pszSubKey), nullptr, &dwType, (byte*)(unichar*)pwsz, &dwSize);

            str = pwsz;

            //str.release_string_buffer(dwSize);

            return lResult;

         }
         else
         {

            return ERROR_NOT_SUPPORTED;

         }

      }


      HICON node::extract_icon(HINSTANCE hInst, const char* pszExeFileName, ::u32 nIconIndex)

      {

         return ::ExtractIconW(hInst, ::str::international::utf8_to_unicode(pszExeFileName), nIconIndex);


      }


      bool node::delete_file(const char* pFileName)

      {

         return ::DeleteFileW(::str::international::utf8_to_unicode(pFileName)) != false;


      }

      //CLASS_DECL_ACME::file::path user_appdata_local();

      //void node::time_to_filetime(::matter* pobject, const ::datetime::time& time, LPFILETIME pFileTime)
      //{

      //   SYSTEMTIME sysTime;

      //   sysTime.wYear = (::u16)time.GetYear();
      //   sysTime.wMonth = (::u16)time.GetMonth();
      //   sysTime.wDay = (::u16)time.GetDay();
      //   sysTime.wHour = (::u16)time.GetHour();
      //   sysTime.wMinute = (::u16)time.GetMinute();
      //   sysTime.wSecond = (::u16)time.GetSecond();
      //   sysTime.wMilliseconds = 0;

      //   // convert system time to local file time
      //   FILETIME localTime;

      //   DWORD dwLastError = ::GetLastError();

      //   if (!SystemTimeToFileTime((LPSYSTEMTIME)&sysTime, &localTime))
      //      ::file::throw_os_error(dwLastError);

      //   // convert local file time to UTC file time
      //   if (!LocalFileTimeToFileTime(&localTime, pFileTime))
      //      ::file::throw_os_error(dwLastError);

      //}



      //::file::path node::user_appdata_local()
      //{

      //   return shell_get_special_folder_path(CSIDL_LOCAL_APPDATA);

      //}



      //::file::path get_known_folder(REFKNOWNFOLDERID kfid)
      //{

      //   ::file::path str;

      //   ::cotaskptr < PWSTR > pwszPath;

      //   HANDLE hToken = nullptr;

      //   ::OpenProcessToken(::GetCurrentProcess(), TOKEN_QUERY | TOKEN_IMPERSONATE | TOKEN_DUPLICATE, &hToken);

      //   HRESULT hr = SHGetKnownFolderPath(kfid, 0, hToken, &pwszPath);

      //   return pwszPath;

      //}


   } // namespace node


} // namespace windows







