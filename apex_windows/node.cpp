#include "framework.h"
#include "node.h"
#include "os_context.h"
#include "acme/exception/exception.h"
#include "acme/platform/application.h"
#include "acme/primitive/primitive/memory.h"
#include "acme/primitive/string/adaptor.h"
#include "acme/primitive/string/international.h"
#include "acme_windows/acme_directory.h"
#include "acme_windows/acme_file.h"
#include "acme_windows/registry.h"
#include "apex/filesystem/filesystem/file_context.h"
#include "apex/platform/application.h"
#include "apex/platform/os_context.h"
#include "apex/platform/system.h"
#include "operating-system/operating-system-windows/deployment/resource1.h"


#include "acme/_operating_system.h"


#include <shellapi.h>
#include <shobjidl_core.h>
#include <iphlpapi.h>


//CLASS_DECL_APEX_WINDOWS HRESULT win_create_link(const ::wide_character * pszPathObj, const ::wide_character * pszPathLink, const ::wide_character * pszDesc, const ::wide_character * pszIconPath, ::i32 iIcon);
CLASS_DECL_ACME_WINDOWS void shell_notify_folder_change(const wchar_t* pwsz);
CLASS_DECL_ACME_WINDOWS void shell_notify_item_change(const wchar_t* pwsz);
CLASS_DECL_ACME_WINDOWS void shell_notify_assoc_change();


::pointer_array < ::networking::address > get_adapters_addresses();

namespace apex_windows
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


   void node::initialize(::particle * pparticle)
   {

      //auto estatus = 
      ::acme_windows::node::initialize(pparticle);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //estatus = 

      ::apex_windows_common::node::initialize(pparticle);

      //if (!estatus)
      //{

      //   return estatus;

      //}


      //if (!__node_apex_pre_init())
      //{

      //   return error_failed;

      //}

      //if (!__node_apex_pos_init())
      //{

      //   return error_failed;

      //}

//         return estatus;

   }


   //bool node::_os_calc_app_dark_mode()
   //{

   //   try
   //   {

   //      ::acme_windows::registry::key key;

   //      key.open(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Themes\\Personalize");

   //      ::u32 dw;

   //      auto estatus = key._get("AppsUseLightTheme", dw);

   //      if (::failed(estatus))
   //      {

   //         estatus = key._get("SystemUseLightTheme", dw);

   //         if (::failed(estatus))
   //         {

   //            return false;

   //         }

   //      }

   //      return dw == 0;

   //   }
   //   catch (...)
   //   {

   //      return false;

   //   }

   //}


   //bool node::_os_calc_system_dark_mode()
   //{

   //   try
   //   {

   //      ::acme_windows::registry::key key;

   //      key.open(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Themes\\Personalize");

   //      ::u32 dw;

   //      auto estatus = key._get("SystemUseLightTheme", dw);

   //      if (::failed(estatus))
   //      {

   //         estatus = key._get("AppsUseLightTheme", dw);

   //         if (::failed(estatus))
   //         {

   //            return false;

   //         }

   //      }

   //      return dw == 0;

   //   }
   //   catch (...)
   //   {

   //      return false;

   //   }

   //}


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

      ::acme_windows::registry::key key(HKEY_CURRENT_USER, "Console", true);

      key._set("ScreenColors", dwScreenColors);
      key._set("PopupColors", dwPopupColors);
      key._set("WindowAlpha", dwWindowAlpha);

   }



   void node::set_system_dark_mode1(bool bSet)
   {

      ::acme_windows::registry::key key(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Themes\\Personalize", true);

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
      //         return ::success;

   }


   void node::set_app_dark_mode1(bool bSet)
   {

      ::acme_windows::registry::key key(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Themes\\Personalize", true);

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

      //return ::success;

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


   void node::open_folder(::file::path& pathFolder)
   {

      wstring wstrFolder(pathFolder);

      int i = (int)(iptr) ::ShellExecuteW(nullptr, L"open", wstrFolder, nullptr, nullptr, SW_NORMAL);

      //if (i < 32)
      //{

      auto estatus = ::windows::last_error_status(i);

      //   switch (i)
      //   {
      //   case 0:
      //      //The operating system is out of memory or resources.
      //      return error_no_memory;
      //   case ERROR_FILE_NOT_FOUND:
      //      return error_file_not_found;
      //      //The specified file was not found.
      //   case ERROR_PATH_NOT_FOUND:
      //      return error_path_not_found;
      //      //            The specified path was not found.
      //   case          ERROR_BAD_FORMAT:
      //      return error_bad_format;
      //      //The.exe file is invalid(non - Win32.exe or error in.exe image).
      //      //case SE_ERR_ACCESSDENIED:
      //      //         return error_access_denied;
      //      ////The operating system denied access to the specified file.
      //      //SE_ERR_ASSOCINCOMPLETE
      //      //The file name association is incomplete or invalid.
      //      //SE_ERR_DDEBUSY
      //      //The DDE transaction could not be completed because other DDE transactions were being processed.
      //      //SE_ERR_DDEFAIL
      //      //The DDE transaction failed.
      //      //SE_ERR_DDETIMEOUT
      //      //The DDE transaction could not be completed because the request timed out.
      //      //SE_ERR_DLLNOTFOUND
      //      //The specified DLL was not found.
      //      //SE_ERR_FNF
      //      //The specified file was not found.
      //      //SE_ERR_NOASSOC
      //      //There is no application associated with the given file name extension.This error will also be returned if you attempt to print a file that is not printable.
      //      //SE_ERR_OOM
      //      //There was not enough memory to complete the operation.
      //      //SE_ERR_PNF
      //      //The specified path was not found.
      //      //SE_ERR_SHARE
      //      //A sharing violation occurred.*/
      //   default:
      //      return error_failed;
      //   }

      //}

      throw ::exception(estatus);

      //return ::success;

   }


   void node::register_dll(const ::file::path& pathDll)
   {


      string strPathDll;

      //#ifdef _DEBUG

      strPathDll = pathDll;

      //#else
      //
      //   strPathDll = acmedirectory()->matter() / "time" / process_platform_name() /"stage/_desk_tb.dll";
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


      ::i32 iExitCode = -1;

      //if (!call_sync(path, strParam, path.folder(), ::e_display_none, 3_minute, set))
      call_sync(path, strParam, path.folder(), ::e_display_none, 3_minute, set, &iExitCode);
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

//         return true;

   }


   void node::system_main()
   {

      //auto estatus = 
      acmesystem()->m_pacmenode->m_papexnode->thread_initialize(acmesystem()->m_papexsystem);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //estatus = 

      acmesystem()->on_start_system();

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //estatus = 
      acmesystem()->main();

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //estatus = acmesystem()->inline_term();

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //return estatus;


   }


   void node::get_firefox_installation_info(string& strPathToExe, string& strInstallDirectory)
   {

#ifdef WINDOWS_DESKTOP

      ::acme_windows::registry::key key(HKEY_LOCAL_MACHINE, "SOFTWARE\\Mozilla\\Mozilla Firefox");

      string strCurrentVersion;

      key.get("CurrentVersion", strCurrentVersion);

      key.open(HKEY_LOCAL_MACHINE, "SOFTWARE\\Mozilla\\Mozilla Firefox\\" + strCurrentVersion + "\\Main");

      key.get("PathToExe", strPathToExe);

      key.get("Install Directory", strInstallDirectory);


      //return ::success;

#else

      return ::error_failed;

#endif

   }


   void node::_001InitializeShellOpen()
   {

      //ASSERT(m_atomApp == nullptr && m_atomSystemTopic == nullptr); // do once

      //m_atomApp            = ::GlobalAddAtomW(utf8_to_unicode(m_strAppName));

      //m_atomSystemTopic    = ::GlobalAddAtomW(L"system");

//         return ::success;

   }


   void node::shell_create_link(::file::path pathObj, ::file::path pathLnkParam, string strDesc, ::file::path pathIco, int iIcon)
   {

      auto pathLnk = pathLnkParam;

      if (!pathLnk.case_insensitive_ends(".lnk"))
      {

         pathLnk += ".lnk";

      }

      acmedirectory()->create(pathLnk.folder());

      wstring wstrObj(pathObj);
      wstring wstrLnk(pathLnk);
      wstring wstrDsc(strDesc);
      wstring wstrIco(pathIco);

      auto errorcode = _windows_create_link(wstrObj, wstrLnk, wstrDsc, wstrIco, iIcon);

      HRESULT hresult = E_FAIL;

      if (errorcode.m_etype == e_error_code_type_hresult)
      {

         hresult = (HRESULT) errorcode.m_iOsError;

      }

      auto estatus = ::windows::hresult_status(hresult);

      if (::failed(estatus))
      {

         throw ::exception(estatus);

      }

   }


   bool node::shell_link_target(::file::path& pathTarget, const ::file::path& pathLnkParam)
   {

      auto pathLnk = pathLnkParam;

      if (!pathLnk.case_insensitive_ends(".lnk"))
      {

         pathLnk += ".lnk";

      }

      wstring wstrLnk(pathLnk);

      ::pointer < ::apex_windows::os_context > poscontext = acmesystem()->m_papexsystem->os_context();

      comptr < IShellLinkW > pshelllink = poscontext->_get_IShellLinkW(pathLnk);

      if (!pshelllink)
      {

         return false;

      }

      wstring wstrTarget;

      auto pwsz = wstrTarget.get_string_buffer(MAX_PATH * 8);

      HRESULT hresult = pshelllink->GetPath(pwsz, MAX_PATH * 8, nullptr, 0);

      wstrTarget.release_string_buffer();

      if (FAILED(hresult))
      {

         auto estatus = ::windows::hresult_status(hresult);

         return false;

      }

      pathTarget = ::string(wstrTarget);

      return true;

   }


   bool node::shell_link_icon(::file::path& pathIcon, int & iIcon, const ::file::path& pathLnkParam)
   {

      auto pathLnk = pathLnkParam;

      if (!pathLnk.case_insensitive_ends(".lnk"))
      {

         pathLnk += ".lnk";

      }

      wstring wstrLnk(pathLnk);

      ::pointer < ::apex_windows::os_context > poscontext = acmesystem()->m_papexsystem->os_context();

      comptr < IShellLinkW > pshelllink = poscontext->_get_IShellLinkW(pathLnk);

      if (!pshelllink)
      {

         return false;

      }

      wstring wstrIcon;

      auto pwsz = wstrIcon.get_string_buffer(MAX_PATH * 8);

      HRESULT hresult = pshelllink->GetIconLocation(pwsz, MAX_PATH * 8, &iIcon);

      wstrIcon.release_string_buffer();

      if (FAILED(hresult))
      {

         auto estatus = ::windows::hresult_status(hresult);

         return false;

      }

      pathIcon = wstrIcon;

      return true;

   }


   //void node::integration_factory()
   //{



   //}


   void node::process_init()
   {



      //defer_initialize_winsock();
//         return success;

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

      if (acmefile()->exists(acmedirectory()->system() / "config\\system\\audio.txt"))
      {

         str = acmefile()->as_string(acmedirectory()->system() / "config\\system\\audio.txt");

      }
      else
      {

         ::file::path strPath;

         strPath = acmedirectory()->appdata() / "audio.txt";

         str = acmefile()->as_string(strPath);

      }

      if (str.has_char())
         return "audio_" + str;
      else
         return "audio_mmsystem";

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
            memory.data()))

         {
            ::u32 cbTranslate;
            struct LANGANDCODEPAGE
            {
               ::u16 wLanguage;
               ::u16 wCodePage;
            } *pTranslate;


            // read the list of languages and code pages.

            VerQueryValue(memory.data(),
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

               strKey.format(
                  "\\StringFileInfo\\%04x%04x\\FileVersion",
                  pTranslate[u].wLanguage,
                  pTranslate[u].wCodePage);

               wstring wstrKey(strKey);

               // Retrieve file description for language and code page "i".
               if (VerQueryValueW(memory.data(),
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

      return ::GetCurrentDirectoryW(MAX_PATH * 8, wstring_adaptor(str, MAX_PATH * 8));

   }


   ::u32 node::get_temp_path(string& str)
   {

      return ::GetTempPathW(MAX_PATH * 8, wstring_adaptor(str, MAX_PATH * 8));

   }


   ::i32 node::reg_query_value(HKEY hkey, const ::string& pszSubKey, string& str)
   {

      DWORD dwType = 0;
      DWORD dwSize = 0;
      ::i32 lResult = RegQueryValueExW(hkey, wstring(pszSubKey), nullptr, &dwType, nullptr, &dwSize);

      if (lResult != ERROR_SUCCESS)
      {

         return lResult;

      }

      ASSERT(dwType == REG_SZ || dwType == REG_MULTI_SZ || dwType == REG_EXPAND_SZ);
      if (dwType == REG_SZ || dwType == REG_MULTI_SZ || dwType == REG_EXPAND_SZ)
      {

         wstring wstr;
         
         auto pwsz = wstr.get_string_buffer(dwSize);

         lResult = RegQueryValueExW(hkey, wstring(pszSubKey), nullptr, &dwType, (byte*)(unichar*)pwsz, &dwSize);

         wstr.release_string_buffer(dwSize);

         str = wstr;

         return lResult;

      }
      else
      {

         return ERROR_NOT_SUPPORTED;

      }

   }


   HICON node::extract_icon(HINSTANCE hInst, const ::string& pszExeFileName, ::u32 nIconIndex)
   {

      return ::ExtractIconW(hInst, utf8_to_unicode(pszExeFileName), nIconIndex);

   }


   void node::delete_file(const ::string& pFileName)
   {

      if (!::DeleteFileW(utf8_to_unicode(pFileName)))
      {

         auto lastError = ::GetLastError();

         auto estatus = ::windows::last_error_status(lastError);

         throw ::exception(estatus);

      }

   }


   void node::node_post(const ::procedure& procedure)
   {

      acmesystem()->m_papexsystem->post_procedure(procedure);

   }


   void node::create_app_shortcut(::acme::application* papp)
   {

      if (papp->is_service())
      {

         return;

      }

      fork([this, papp]()
         {

            string strAppId = papp->m_strAppId;

            if (strAppId.has_char())
            {

               auto pnode = acmesystem()->node()->m_papexnode;

               string strAppName;

               string strAppIdUnderscore = papp->m_strAppId;

               strAppIdUnderscore.find_replace("/", "_");

               strAppIdUnderscore.find_replace("-", "_");

               if (papp->m_strAppName.has_char())
               {

                  strAppName = papp->m_strAppName;

               }
               else
               {

                  strAppName = strAppIdUnderscore;

               }

               string strRoot;

               auto findRootEnd = papp->m_strAppId.find_index('/');

               if (findRootEnd > 0)
               {

                  strRoot = papp->m_strAppId.left(findRootEnd);

               }

               auto path = acmefile()->module();

               auto pathShortcut = acmedirectory()->roaming() / "Microsoft/Windows/Start Menu/Programs" / strRoot / (strAppName + ".lnk");

#ifdef WINDOWS

               //auto pathIcon = path.folder() / "icon.ico";

               //if (!acmefile()->exists(pathIcon))
               //{

               //   papp->m_papexapplication->file().copy(pathIcon, "matter://main/icon.ico", false);

               //}

#else

               auto pathIcon = path.folder() / (strAppIdUnderscore + "-256.png");

               if (!acmefile()->exists(pathIcon))
               {

                  papp->m_papexapplication->file().copy(pathIcon, "matter://main/icon-256.png", false);

               }

#endif

#ifdef WINDOWS

               pnode->shell_create_link(path, pathShortcut, "Link for " + strAppName, path, -IDR_MAIN);

               if (payload("pin_app_to_taskbar").is_true())
               {

                  ::file::path pathUserPinned = acmedirectory()->roaming() / "Microsoft/Internet Explorer/Quick Launch/User Pinned/TaskBar" / pathShortcut.name();

                  wstring wstrShortcut;

                  wstrShortcut = pathShortcut;

                  acmefile()->copy(pathUserPinned, pathShortcut, true);

                  wstring wstr;

                  wstr = pathUserPinned.folder();

                  shell_notify_folder_change(wstr);

                  shell_notify_item_change(wstr);

                  shell_notify_assoc_change();

               }

#else

               //pnode->shell_create_link(path, pathShortcut, "Link for " + strAppName, pathIcon);

#endif

               auto pathCreatedShortcut = acmedirectory()->roaming() / papp->m_strAppId / "created_shortcut.txt";

               acmefile()->touch(pathCreatedShortcut);

            }

         });

   }


   void node::on_start_application(::apex::application * papplication)
   {

      ////if (!::is_debugger_attached())
      //{

      //   ::file::path pathObj;

      //   ::file::path pathLnk;

      //   pathObj = file()->module();

      //   string strLinkTitle;

      //   strLinkTitle = papplication->m_strAppName;

      //   strLinkTitle.replace_with("_", "/");
      //   strLinkTitle.replace_with("_", "\\");
      //   strLinkTitle.replace_with("_", "-");

      //   pathLnk = acmedirectory()->localconfig() / "desk/monitor-0/2desk" / strLinkTitle + ".lnk";

      //   acmedirectory()->create(pathLnk.folder());

      //   acmesystem()->m_pacmenode->m_papexnode->shell_create_link(pathObj, pathLnk, "app=" + papplication->m_strAppName);

      //}

   }




} // namespace apex_windows



