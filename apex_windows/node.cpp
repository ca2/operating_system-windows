#include "framework.h"
#undef USUAL_OPERATING_SYSTEM_SUPPRESSIONS
#include "node.h"
//#include "node.h"
#include "acme/constant/user_key.h"
#include "acme/exception/exception.h"
#include "acme/filesystem/filesystem/acme_path.h"
#include "acme/filesystem/filesystem/link.h"
#include "acme/platform/application.h"
#include "acme/primitive/primitive/memory.h"
#include "acme/primitive/string/adaptor.h"
#include "acme/primitive/string/international.h"
#include "acme_windows/acme_directory.h"
#include "acme_windows/acme_file.h"
#include "acme_windows/acme_path.h"
#include "acme_windows/registry.h"
#include "acme/filesystem/filesystem/file_context.h"
#include "apex/platform/application.h"
//#include "apex/platform/node.h"
#include "apex/platform/system.h"



#include "acme/filesystem/file/exception.h"
#include "acme/operating_system/process.h"
#include "acme/platform/scoped_restore.h"
#include "acme/filesystem/file/status.h"
#include "acme/filesystem/filesystem/acme_directory.h"
#include "acme/filesystem/filesystem/acme_path.h"

#include "acme/parallelization/manual_reset_event.h"
#include "acme/parallelization/task_flag.h"
#include "acme/platform/node.h"
#include "acme/primitive/collection/_container.h"
#include "acme/primitive/string/international.h"
#include "acme/primitive/string/string.h"
#include "acme/primitive/string/str.h"
#include "apex/filesystem/file/set.h"
#include "acme/filesystem/filesystem/dir_context.h"
#include "acme/filesystem/filesystem/file_context.h"
#include "apex/platform/application.h"
#include "apex/platform/context.h"

#include "operating_system/operating_system-windows/deployment/resource1.h"

#include "acme/_operating_system.h"


#include "acme_windows_common/cotaskptr.h"

#include "acme_windows/registry.h"
#include "acme_windows/itemidlist.h"
#include "acme_windows/acme_directory.h"
#include "acme_windows/acme_file.h"


#include <wincred.h>
#include <wtsapi32.h>
#include <shobjidl.h>
#include <ShellApi.h>
#include <Security.h>
#include <wincred.h>
#include <shobjidl_core.h>


CLASS_DECL_ACME::file::path get_module_path(HANDLE hProcess, HMODULE hmodule);


//::e_status hresult_to_estatus(HRESULT hresult)
//{
//
//   if (SUCCEEDED(hresult))
//   {
//
//      return ::success;
//
//   }
//   else
//   {
//
//      return ::error_failed;
//
//   }
//
//}



CREDUIAPI
BOOL
WINAPI
CredPackAuthenticationBufferWfoo(
   _In_ u32                                      dwFlags,
   _In_ LPWSTR                                     pszUserName,
   _In_ LPWSTR                                     pszPassword,
   _Out_writes_bytes_opt_(*pcbPackedCredentials) PBYTE   pPackedCredentials,
   _Inout_ u32* pcbPackedCredentials
);


//#include <Wtsapi32.h>
//#include <Psapi.h>
//#include <WinCred.h>

CLASS_DECL_APEX_WINDOWS HBITMAP get_icon_hbitmap(HICON hICON);

#include <shellapi.h>
#include <shobjidl_core.h>
#include <iphlpapi.h>


//CLASS_DECL_APEX_WINDOWS HRESULT win_create_link(const ::wide_character * pszPathObj, const ::wide_character * pszPathLink, const ::wide_character * pszDesc, const ::wide_character * pszIconPath, ::i32 iIcon);
CLASS_DECL_ACME_WINDOWS void shell_notify_folder_change(const wchar_t* pwsz);
CLASS_DECL_ACME_WINDOWS void shell_notify_item_change(const wchar_t* pwsz);
CLASS_DECL_ACME_WINDOWS void shell_notify_assoc_change();

namespace windows
{
   int user_key_to_key_code(::user::enum_key ekey);
}

::pointer_array < ::networking::address > get_adapters_addresses();

namespace windows
{


   int user_key_to_key_code(::user::enum_key ekey)
   {

      if (ekey >= ::user::e_key_0 && ekey <= ::user::e_key_9)
      {

         return (int)('0' + (ekey - ::user::e_key_0));

      }

      if (ekey >= ::user::e_key_a && ekey <= ::user::e_key_z)
      {

         return (int)('A' + (ekey - ::user::e_key_a));

      }

      if (ekey == ::user::e_key_space)
      {

         return (int)ekey;

      }

      switch (ekey)
      {
      case ::user::e_key_left:
         return VK_LEFT;
      case ::user::e_key_right:
         return VK_RIGHT;
      case ::user::e_key_up:
         return VK_UP;
      case ::user::e_key_down:
         return VK_DOWN;
      case ::user::e_key_tab:
         return VK_TAB;
      case ::user::e_key_return:
         return VK_RETURN;
      case ::user::e_key_left_shift:
         return VK_LSHIFT;
      case ::user::e_key_right_shift:
         return VK_RSHIFT;
      case ::user::e_key_left_control:
         return VK_LCONTROL;
      case ::user::e_key_right_control:
         return VK_RCONTROL;
      case ::user::e_key_left_alt:
         return VK_LMENU;
      case ::user::e_key_right_alt:
         return VK_RMENU;
      case ::user::e_key_left_command:
         return VK_LWIN;
      case ::user::e_key_right_command:
         return VK_RWIN;
      case ::user::e_key_back:
         return VK_BACK;
      case ::user::e_key_delete:
         return VK_DELETE;
      case ::user::e_key_home:
         return VK_HOME;
      case ::user::e_key_end:
         return VK_END;
      case ::user::e_key_page_up:
         return VK_PRIOR;
      case ::user::e_key_page_down:
         return VK_NEXT;
      case ::user::e_key_escape:
         return VK_ESCAPE;
      }

      return ::user::e_key_none;

   }


} // namespace windows


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
         //posix_time t = time(nullptr);

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

      acme_windows::node::system_main();

      ////auto estatus = 
      //system()->m_pacmenode->m_papexnode->thread_initialize(system()->m_papexsystem);

      ////if (!estatus)
      ////{

      ////   return estatus;

      ////}

      ////estatus = 

      //system()->on_start_system();

      ////if (!estatus)
      ////{

      ////   return estatus;

      ////}

      ////estatus = 
      //system()->main();

      ////if (!estatus)
      ////{

      ////   return estatus;

      ////}

      ////estatus = system()->inline_term();

      ////if (!estatus)
      ////{

      ////   return estatus;

      ////}

      ////return estatus;


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

      if (estatus.failed())
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

      ::pointer < ::acme_windows::acme_path > pacmepath = acmepath();

      auto pshelllink = pacmepath->_get_IShellLinkW(pathLnk);

      if (!pshelllink)
      {

         return false;

      }

      wstring wstrTarget;

      auto pwsz = wstrTarget.get_buffer(MAX_PATH * 8);

      HRESULT hresult = pshelllink->GetPath(pwsz, MAX_PATH * 8, nullptr, 0);

      wstrTarget.release_buffer();

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

      ::pointer < ::acme_windows::acme_path > pacmepath = acmepath();

      auto pshelllink = pacmepath->_get_IShellLinkW(pathLnk);

      if (!pshelllink)
      {

         return false;

      }

      wstring wstrIcon;

      auto pwsz = wstrIcon.get_buffer(MAX_PATH * 8);

      HRESULT hresult = pshelllink->GetIconLocation(pwsz, MAX_PATH * 8, &iIcon);

      wstrIcon.release_buffer();

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


   string node::veriwell_multimedia_music_midi_get_default_implementation_name()
   {

      return system()->implementation_name("music_midi", "mmsystem");

   }


   string node::multimedia_audio_mixer_get_default_implementation_name()
   {

      return system()->implementation_name("audio_mixer", "mmsystem");

   }


   string node::multimedia_audio_get_default_implementation_name()
   {

      string str;

      if (acmefile()->exists(acmedirectory()->roaming() / "system/audio.txt"))
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

               strKey.formatf(
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
         
         auto pwsz = wstr.get_buffer(dwSize);

         lResult = RegQueryValueExW(hkey, wstring(pszSubKey), nullptr, &dwType, (::u8*)(unichar*)pwsz, &dwSize);

         wstr.release_buffer(dwSize);

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

         auto lasterror = ::GetLastError();

         auto estatus = ::windows::last_error_status(lasterror);

         throw ::exception(estatus);

      }

   }


   void node::user_post(const ::procedure& procedure)
   {

      system()->m_papexsystem->post_procedure(procedure);

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

               auto pnode = system()->node()->m_papexnode;

               string strAppName = papp->app_name();

               //string strAppIdUnderscore = papp->m_strAppId;

               //strAppIdUnderscore.find_replace("/", "_");

               //strAppIdUnderscore.find_replace("-", "_");

               //if (papp->m_strAppName.has_char())
               //{

               //   strAppName = papp->m_strAppName;

               //}
               //else
               //{

               //   strAppName = strAppIdUnderscore;

               //}

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

      //   system()->m_pacmenode->m_papexnode->shell_create_link(pathObj, pathLnk, "app=" + papplication->m_strAppName);

      //}

   }

   
   void node::on_create_app_shortcut(::acme::application * papplication)
   {

      defer_create_app_shortcut(papplication);

   }


   ::file::path node::app_shortcut_path(::acme::application* papplication)
   {

      string strAppName = papplication->app_name();

      string strRoot = papplication->app_root();

      ::file::path pathShortcut;

      //#ifdef WINDOWS_DESKTOP

      pathShortcut = acmedirectory()->roaming() / "Microsoft/Windows/Start Menu/Programs" / strRoot / (strAppName + ".lnk");

      //#else
      //
      //      ::string strDesktopFileName;
      //
      //      strDesktopFileName = m_strAppId;
      //
      //      strDesktopFileName.find_replace("/", ".");
      //
      //      pathShortcut = acmedirectory()->home() / ".local/share/applications" / (strDesktopFileName + ".desktop");
      //
      //#endif

      return pathShortcut;

   }


#define PRESSED(key) ((::GetAsyncKeyState(key) & 0x8000) != 0)


   bool node::is_key_pressed(bool * pbPressed, ::user::enum_key ekey)
   {

      if (ekey == ::user::e_key_left_button
         || ekey == ::user::e_key_middle_button
         || ekey == ::user::e_key_right_button)
      {

         return apex_windows_common::node::is_key_pressed(pbPressed, ekey);

      }

      if (ekey == ::user::e_key_alt)
      {

         *pbPressed = PRESSED(VK_MENU) || PRESSED(VK_RMENU) || PRESSED(VK_LMENU);

      }
      else if (ekey == ::user::e_key_control)
      {

         *pbPressed = PRESSED(VK_CONTROL) || PRESSED(VK_RCONTROL) || PRESSED(VK_LCONTROL);

      }
      else if (ekey == ::user::e_key_shift)
      {

         *pbPressed = PRESSED(VK_SHIFT) || PRESSED(VK_RSHIFT) || PRESSED(VK_LSHIFT);

      }
      else if (ekey == ::user::e_key_command)
      {

         *pbPressed = PRESSED(VK_RWIN) || PRESSED(VK_LWIN);

      }
      else
      {

         int iKeyCode = ::windows::user_key_to_key_code(ekey);

         *pbPressed = (::GetAsyncKeyState(iKeyCode) & 0x8000) != 0;

      }

      return true;

   }



   string node::get_command_line()
   {

      return GetCommandLineW();

   }


   void node::shutdown(bool bIfPowerOff)
   {
      bool retval = true;
      HANDLE hToken;
      TOKEN_PRIVILEGES tokenprivileges;
      if (!OpenProcessToken(GetCurrentProcess(),
         TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken))
         throw ::exception(error_failed);
      LookupPrivilegeValue(nullptr, SE_SHUTDOWN_NAME, &tokenprivileges.Privileges[0].Luid);
      tokenprivileges.PrivilegeCount = 1;
      tokenprivileges.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
      AdjustTokenPrivileges(hToken, false, &tokenprivileges, 0, (PTOKEN_PRIVILEGES) nullptr, 0);
      if (bIfPowerOff)
         retval = ExitWindowsEx(EWX_POWEROFF, 0) != false;
      else
         retval = ExitWindowsEx(EWX_SHUTDOWN, 0) != false;

      //reset the previlages
      tokenprivileges.Privileges[0].Attributes = 0;
      AdjustTokenPrivileges(hToken, false, &tokenprivileges, 0, (PTOKEN_PRIVILEGES) nullptr, 0);
      //return retval;
   }


   void node::reboot()
   {
      HANDLE hToken;
      TOKEN_PRIVILEGES tokenprivileges;
      if (!OpenProcessToken(GetCurrentProcess(),
         TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken))
         throw ::exception(error_failed);
      if (!LookupPrivilegeValue(nullptr, SE_SHUTDOWN_NAME, &tokenprivileges.Privileges[0].Luid))
      {
         TRACELASTERROR();
         throw ::exception(error_failed);
      }
      tokenprivileges.PrivilegeCount = 1;
      tokenprivileges.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
      if (!AdjustTokenPrivileges(hToken, false, &tokenprivileges, 0, (PTOKEN_PRIVILEGES) nullptr, 0))
      {
         TRACELASTERROR();
         throw ::exception(error_failed);
      }
      if (GetLastError() == ERROR_NOT_ALL_ASSIGNED)
      {
         throw ::exception(error_failed);
      }
      ////if(!LookupPrivilegeValue(nullptr, SE_REMOTE_SHUTDOWN_NAME, &tokenprivileges.Privileges[0].Luid))
      ////{
      ////   TRACELASTERROR();
      ////   return false;
      ////}
      ////tokenprivileges.PrivilegeCount = 1;
      ////tokenprivileges.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
      ////if(!AdjustTokenPrivileges(hToken, false, &tokenprivileges, 0, (PTOKEN_PRIVILEGES) nullptr, 0))
      ////{
      ////   TRACELASTERROR();
      ////   return false;
      ////}
      ////if (GetLastError() == ERROR_NOT_ALL_ASSIGNED)
      ////{
      ////   return false;
      ////}

      //if(!WTSShutdownSystem(WTS_CURRENT_SERVER_HANDLE,WTS_WSD_REBOOT))
      //{
      //   TRACELASTERROR();
      //   return false;
      //}
      //if (!ExitWindowsEx(EWX_REBOOT | EWX_FORCE,
      if (!ExitWindowsEx(EWX_REBOOT,
         SHTDN_REASON_MAJOR_SOFTWARE | SHTDN_REASON_MINOR_INSTALLATION))
      {
         TRACELASTERROR();
         throw ::exception(error_failed);
      }
      //reset the previlages
//      tokenprivileges.Privileges[0].Attributes = 0;
 //     AdjustTokenPrivileges(hToken, false, &tokenprivileges, 0, (PTOKEN_PRIVILEGES) nullptr, 0);
      //return true;
   }


   void node::terminate_processes_by_title(const ::string& lpszName)
   {

      while (true)
      {

         auto processidentifiera = title_processes_identifiers(lpszName);

         if (processidentifiera.is_empty())
         {

            break;

         }

         for (auto& processidentifier : processidentifiera)
         {

            DWORD dwProcess = (DWORD)processidentifier;

            HANDLE hProcess = ::OpenProcess(PROCESS_QUERY_INFORMATION |
               PROCESS_VM_READ,
               false, dwProcess);
            TerminateProcess(hProcess, (::u32)-1);
            CloseHandle(hProcess);
            /*::EnumWindows((WNDENUMPROC)
            CKillProcessHelper::TerminateAppEnum,
            (LPARAM) dwId);
            // Wait on the handle. If it signals, great.

            //If it times out, then you kill it.

            if(WaitForSingleObject(hProcess, 5000)
            !=WAIT_OBJECT_0)
            bResult = TerminateProcess(hProcess,0);
            else
            bResult = true;
            CloseHandle(hProcess);
            return bResult == true;*/

         }

         preempt(200_ms);

      }

   }


   ::process_identifier_array node::module_path_processes_identifiers(const ::scoped_string& scopedstrName)
   {

      ::process_identifier_array processidentifieraModulePath;

      auto processidentifiera = processes_identifiers();

      for (auto& processidentifier : processidentifiera)
      {

         if (process_identifier_module_path(processidentifier).case_insensitive_equals(scopedstrName))
         {

            processidentifieraModulePath.add(processidentifier);

         }

      }

      return processidentifieraModulePath;

   }


   ::process_identifier_array node::title_processes_identifiers(const ::scoped_string& scopedstrName)
   {

      ::process_identifier_array processidentifieraTitle;

      auto processidentifiera = processes_identifiers();

      for (auto& processidentifier : processidentifiera)
      {

         if (process_identifier_module_path(processidentifier).title().case_insensitive_equals(scopedstrName))
         {

            processidentifieraTitle.add(processidentifier);

         }

      }

      return processidentifieraTitle;

   }


   ::process_identifier node::current_process_identifier()
   {

      return (int)::GetCurrentProcessId();

   }


   ::file::path node::process_identifier_module_path(::process_identifier processidentifier)
   {

      string strName;

      DWORD dwProcess = (DWORD)processidentifier;

      // get a handle to the process.
      HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION |
         PROCESS_VM_READ,
         false, dwProcess);

      // get the process name.

      if (nullptr != hProcess)
      {

         HMODULE hMod;

         DWORD cbNeeded;

         if (EnumProcessModules(hProcess, &hMod, sizeof(hMod), &cbNeeded))
         {

            strName = ::get_module_path(hProcess, hMod);

         }

      }

      CloseHandle(hProcess);

      return strName;

   }


   ::process_identifier_array node::processes_identifiers()
   {

      //::acme_windows_common::node::processes_identifiers();

      process_identifier_array processidentifiera;

      //return node()->processes_identifiers();

      ::raw_array < DWORD > ua;

      ASSERT(sizeof(::u32) == sizeof(u32));

      ua.set_size(0);

      DWORD cbNeeded = 0;

      while(cbNeeded == natural(ua.get_count()))
      {

         ua.set_size(ua.get_count() + 1024);

         if(!EnumProcesses((DWORD *) ua.m_begin, (DWORD) (ua.get_count() * sizeof(::u32)), &cbNeeded))
         {

            return{};

         }

         ua.set_size(cbNeeded / sizeof(u32));

      }

      for (auto& u : ua)
      {

         processidentifiera.add(u);

      }

      return ::transfer(processidentifiera);

   }


   //::file::path node::get_module_path(HMODULE hmodule)
   //{
   //   
   //   wstring wstrPath;
   //   
   //   u32 dwSize = 1;

   //   while(natural(wstrPath.length() + 1) == dwSize)
   //   {

   //      dwSize = ::GetModuleFileNameW(
   //               hmodule,
   //               wstrPath.get_buffer(dwSize + 1024),
   //               (dwSize + 1024));

   //      wstrPath.release_buffer();

   //   }

   //   return unicode_to_utf8(wstrPath);

   //}


   ::payload node::connection_settings_get_auto_detect()
   {

      try
      {

         ::acme_windows::registry::key key1(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Internet Settings\\Connections", false);

         memory mem;

         key1.get("DefaultConnectionSettings", mem);

         bool bAutoDetect = (((::u8*)mem.data())[8] & 0x08) != 0;

         if (!bAutoDetect)
         {

            return ::error_false;

         }

      }
      catch (const ::e_status& estatus)
      {

         return estatus.m_eenum;

      }

      return ::success;

   }


   ::payload node::connection_settings_get_auto_config_url()
   {

      string strUrl;

      try
      {

         ::acme_windows::registry::key key(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Internet Settings", false);

         key.get("AutoConfigURL", strUrl);

      }
      catch (const ::e_status& estatus)
      {

         return estatus.m_eenum;

      }

      return ::success;

   }


   void node::local_machine_set_run(const ::string& strKey, const ::file::path& pathExecutable, const ::string& strArguments, bool bSet)
   {

      try
      {

         ::acme_windows::registry::key keyKar(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", true);


         if (bSet)
         {

            auto windowspath = pathExecutable.windows_path();

            keyKar.set(strKey, windowspath);

         }
         else
         {

            keyKar.delete_value(strKey);

         }

      }
      catch (...)
      {

         //return false;

      }

      //return true;

   }


   void node::local_machine_set_run_once(const ::string& pszKey, const ::file::path& pathExecutable, const ::string& pszArguments, bool bSet)
   {

      try
      {

         ::acme_windows::registry::key keyKar(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\RunOnce", true);

         if (bSet)
         {

            auto windowspath = pathExecutable.windows_path();

            keyKar.set(pszKey, windowspath);

         }
         else
         {

            keyKar.delete_value(pszKey);

         }

      }
      catch (...)
      {

         //return false;

      }

      //return true;

   }


   void node::current_user_set_run(const ::string& pszKey, const ::file::path& pathExecutable, const ::string& strArguments, bool bSet)
   {

      try
      {

         ::acme_windows::registry::key keyKar(HKEY_CURRENT_USER, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", true);


         if (bSet)
         {

            string str;

            auto windowspath = pathExecutable.windows_path();

            str = "\"" + string(windowspath) + "\"" + ::str::has_char(strArguments, " ");

            keyKar.set(pszKey, str);

         }
         else
         {

            keyKar.delete_value(pszKey);

         }


      }
      catch (...)
      {

         //         return false;

      }

      ///return true;

   }


   void node::current_user_set_run_once(const ::string& pszKey, const ::file::path& pathExecutable, const ::string& pszArguments, bool bSet)
   {

      try
      {

         ::acme_windows::registry::key keyKar(HKEY_CURRENT_USER, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\RunOnce", true);

         if (bSet)
         {

            auto windowspath = pathExecutable.windows_path();

            keyKar.set(pszKey, windowspath);

         }
         else
         {

            keyKar.delete_value(pszKey);

         }

      }
      catch (...)
      {

         //return false;

      }

      //return true;
   }


   void node::defer_register_ca2_plugin_for_mozilla()
   {

      //try
      //{

      ::acme_windows::registry::key key;

      key.open(HKEY_LOCAL_MACHINE, "SOFTWARE\\MozillaPlugins", true);

      key.open(key, "@ca2.cc/npca2", true);

      key.set("Description", "ca2 plugin for NPAPI");
      key.set("Path", dir()->module() / "npca2.dll");
      key.set("ProductName", "ca2 plugin for NPAPI");
      key.set("Vendor", "ca2 Desenvolvimento de Software Ltda.");
      key.set("Version", file()->as_string(dir()->install() / "appdata/x86/ca2_build.txt"));

      key.open(key, "application/apex", true);

      key.set("Description", "apex Document");

      //}
      //catch (...)
      //{

      //   return false;

      //}

      //return true;

   }


   void node::file_extension_get_open_with_list_keys(string_array& straKey, const ::string& pszExtension)
   {

      //try
      //{

      string strExt;

      strExt = ".";
      strExt += pszExtension;

      string strOpenWithKey;
      strOpenWithKey = strExt + "\\OpenWithList";

      ::acme_windows::registry::key key(HKEY_CLASSES_ROOT, strOpenWithKey, false);

      key.ls_key(straKey);

      //}
      //catch (...)
      //{

      //   return false;

      //}

      //return true;

   }


   void node::file_extension_get_open_with_list_commands(string_array& straCommand, const ::string& pszExtension)
   {

      string_array straKey;

      file_extension_get_open_with_list_keys(straKey, pszExtension);
      /*{

         __throw_failed(error_failed);

      }*/

      //return true;

   }


   void node::file_association_set_default_icon(const ::string& pszExtension, const ::string& pszExtensionNamingClass, const ::string& pszIconPath)
   {

      //try
      //{

      string strExtensionNamingClass(pszExtensionNamingClass);

      ::acme_windows::registry::key keyLink3(HKEY_CLASSES_ROOT, strExtensionNamingClass, true);

      keyLink3.set("DefaultIcon", pszIconPath);

      //}
      //catch (...)
      //{

      //   return false;

      //}

      //return true;


   }


   void node::file_association_set_shell_open_command(const ::string& pszExtension, const ::string& pszExtensionNamingClass, const ::string& pszCommand, const ::string& pszParam)
   {

      //::e_status estatus = ::success;

      //try
      //{

      bool bForUser = true;

      if (bForUser)
      {

         string strExt;

         strExt += pszExtension;

         string strExtensionNamingClass(pszExtensionNamingClass);

         ::acme_windows::registry::key key(HKEY_CURRENT_USER, "Software\\Classes\\" + strExt, true);

         key._set(nullptr, strExtensionNamingClass);

         ::acme_windows::registry::key keyLink3(HKEY_CURRENT_USER, "Software\\Classes\\" + strExtensionNamingClass + "\\shell", true);

         keyLink3._set("", "open");


         ::acme_windows::registry::key keyLink2(keyLink3, "open", true);

         keyLink2._set("", "");

         ::acme_windows::registry::key keyLink1(keyLink2, "command", true);

         string strCommand(pszCommand);

         strCommand = solve_relative(strCommand);

         string strFormat;

         strFormat = "\"" + strCommand + "\"";

         strFormat += pszParam;

         keyLink1._set("", strFormat);

         //}
         //catch (...)
         //{

         //   return false;

         //}

         //if (!estatus)
         //{

         //   return false;

         //}

         //return true;

      }
      else
      {

         string strExt;

         strExt += pszExtension;

         string strExtensionNamingClass(pszExtensionNamingClass);

         ::acme_windows::registry::key key(HKEY_CLASSES_ROOT, strExt, true);

         key._set(nullptr, strExtensionNamingClass);

         ::acme_windows::registry::key keyLink3(HKEY_CLASSES_ROOT, strExtensionNamingClass + "\\shell", true);

         keyLink3._set("", "open");


         ::acme_windows::registry::key keyLink2(keyLink3, "open", true);

         keyLink2._set("", "");

         ::acme_windows::registry::key keyLink1(keyLink2, "command", true);

         string strCommand(pszCommand);

         strCommand = solve_relative(strCommand);

         string strFormat;

         strFormat.formatf("\"%s\" %s", strCommand.c_str(), pszParam);

         keyLink1._set("", strFormat);
      }


   }


   void node::file_association_get_shell_open_command(const ::string& pszExtension, string& strExtensionNamingClass, string& strCommand, string& strParam)
   {

      //try
      //{
      string strExt;

      strExt = ".";
      strExt += pszExtension;

      ::acme_windows::registry::key key(HKEY_CLASSES_ROOT, strExt, false);
      key.get(nullptr, strExtensionNamingClass);

      ::acme_windows::registry::key keyLink(HKEY_CLASSES_ROOT, strExtensionNamingClass + "\\shell\\open\\command", false);

      string strFormat;

      keyLink.get(nullptr, strFormat);

      {

         auto range = strFormat();

         try
         {

            strCommand = range.consume_quoted_value();

            range.consume_spaces();

            range.consume("\"%L\"");

            strParam = range;

         }
         catch (...)
         {
         }


      }


      //}
      //catch (...)
      //{

      //   return false;

      //}

      //return true;

   }


   void node::open_url_link_at_system_browser(const string& strUrl, const string& strProfile)
   {

      string strBrowser = "chrome";

      if (strProfile.contains("\\Chrome\\"))
      {

         strBrowser = "chrome";

      }

      //string strMappedProfile;

      //if (strProfile.has_char())
      //{

      //   auto path = system()->m_papexsystem->dir().config() / "config/browser" / strBrowser / (strProfile + ".txt");

      //   strMappedProfile = system()->m_papexsystem->file().as_string(path);

      //}


      if (strProfile.has_char() && strBrowser == "chrome")
      {

         ::acme_windows::registry::key key;

         if (key._open(HKEY_CLASSES_ROOT, "ChromeHTML\\shell\\open\\command"))
         {

            string str = key.get("");

            auto range = str();

            ::file::path path = range.consume_quoted_value();

            string strCommand = "\"" + path + "\" \"" + strUrl + "\" --profile-directory=\"" + strProfile + "\"";

            //string strOutput;

            //string strError;

            //string_array straOutput;

            //int iExitCode = 0;

            //auto estatus = 
            //node()->command_system(straOutput, iExitCode, strCommand);

            command_system(strCommand, [](auto etraceleve, auto& str) {});

            //return estatus;

         }

      }

      return ::acme_windows::node::open_url_link_at_system_browser(strUrl, strProfile);

   }


   bool node::open_in_ie(const ::string& pcsz)
   {

      try
      {

         ::acme_windows::registry reg;

         string str;

         string str2;

         string strCommand;

         ::acme_windows::registry::key key(HKEY_CLASSES_ROOT, ".html", false);

         if (key._open(HKEY_CLASSES_ROOT, ".html\\shell\\opennew\\command", false))
         {

            if (key._get("", str2))
            {

               string strCommand(str2);

               strCommand.replace_with(pcsz, "%1");

               WinExec(strCommand, e_display_normal);

            }

         }
         else if (key._open(HKEY_CLASSES_ROOT, str, false))
         {

            str += "\\shell\\opennew\\command";

            if (key._get("", str2))
            {

               string strCommand(str2);

               strCommand.replace_with(pcsz, "%1");

               WinExec(strCommand, e_display_normal);

            }

         }

      }
      catch (...)
      {

         return false;

      }

      return true;

   }


   //------------------------------------------------------------------------
   // The following function retrieves the identity of the current user.
   // This is a helper function and is not part of the Windows Biometric
   // Framework API.
   //
   struct TOKEN_INFO
   {
      TOKEN_USER tokenUser;
      ::u8 buffer[SECURITY_MAX_SID_SIZE];
   };


   HRESULT GetCurrentUserIdentity(TOKEN_INFO& tokenInfo)
   {

      // Declare variables.
      bool bOk = true;

      HANDLE tokenHandle = nullptr;

      DWORD bytesReturned = 0;

      // Open the access token associated with the
      // current process
      if (!OpenProcessToken(
         GetCurrentProcess(),            // Process handle
         TOKEN_READ,                     // Read access only
         &tokenHandle))                  // Access token handle
      {

         u32 win32Status = GetLastError();

         //debug_print("Cannot open token handle: %d\n",win32Status);

         bOk = false;

      }

      // Zero the tokenInfoBuffer structure.
      ZeroMemory(&tokenInfo, sizeof(tokenInfo));

      // Retrieve information about the access token. In this case,
      // retrieve a SID.
      if (!GetTokenInformation(
         tokenHandle,                    // Access token handle
         TokenUser,                      // User for the token
         &tokenInfo.tokenUser,     // Buffer to fill
         sizeof(tokenInfo),        // Size of the buffer
         &bytesReturned))                // Size needed
      {

         u32 win32Status = GetLastError();

         //debug_print("Cannot query token information: %d\n",win32Status);

         bOk = false;

      }

      if (tokenHandle != nullptr)
      {

         CloseHandle(tokenHandle);

      }

      return bOk;

   }


   BOOL
      GetAccountSid(
         TCHAR* SystemName,
         TCHAR* AccountName,
         PSID* Sid
      )
   {

      LPTSTR ReferencedDomain = nullptr;
      DWORD cbSid = 128;    // initial allocation attempt
      DWORD cchReferencedDomain = 16; // initial allocation size_i32
      SID_NAME_USE peUse;
      BOOL bSuccess = false; // assume this function will fail

      __try
      {

         //
         // initial memory allocations
         //
         if ((*Sid = HeapAlloc(
            GetProcessHeap(),
            0,
            cbSid
         )) == nullptr) __leave;

         if ((ReferencedDomain = (TCHAR*)HeapAlloc(
            GetProcessHeap(),
            0,
            cchReferencedDomain * sizeof(TCHAR)
         )) == nullptr) __leave;

         //
         // Obtain the SID of the specified account on the specified system.
         //
         while (!LookupAccountName(
            SystemName,         // machine to lookup account on
            AccountName,        // account to lookup
            *Sid,               // SID of interest
            &cbSid,             // size_i32 of SID
            ReferencedDomain,   // domain account was found on
            &cchReferencedDomain,
            &peUse
         ))
         {
            if (GetLastError() == ERROR_INSUFFICIENT_BUFFER)
            {
               //
               // reallocate memory
               //
               if ((*Sid = HeapReAlloc(
                  GetProcessHeap(),
                  0,
                  *Sid,
                  cbSid
               )) == nullptr) __leave;

               if ((ReferencedDomain = (TCHAR*)HeapReAlloc(
                  GetProcessHeap(),
                  0,
                  ReferencedDomain,
                  cchReferencedDomain * sizeof(TCHAR)
               )) == nullptr) __leave;
            }
            else __leave;
         }

         //
         // Indicate success.
         //
         bSuccess = true;

      } // finally
      __finally
      {

         //
         // Cleanup and indicate failure, if appropriate.
         //

         HeapFree(GetProcessHeap(), 0, ReferencedDomain);

         if (!bSuccess)
         {
            if (*Sid != nullptr)
            {
               HeapFree(GetProcessHeap(), 0, *Sid);
               *Sid = nullptr;
            }
         }

      } // finally

      return bSuccess;
   }


   void node::_getCredentialsForService(const ::string& strService, ::string& strUsername, ::string& strPassword)
   {

      HRESULT hr = S_OK;
      u32   dwResult;
      sec_cotaskptr < PVOID > pvInAuthBlob;
      sec_cotaskptr < PVOID > pvAuthBlob;
      CREDUI_INFOW u{};
      ULONG   ulAuthPackage = 0;
      BOOL    fSave = false;
      WCHAR szDomainAndUser[CREDUI_MAX_USERNAME_LENGTH + CREDUI_MAX_DOMAIN_TARGET_LENGTH + 1];
      WCHAR szDomain[CREDUI_MAX_DOMAIN_TARGET_LENGTH + 1];
      //      TOKEN_INFO ti;

      u32 maxLenName = CREDUI_MAX_USERNAME_LENGTH + 1;
      u32 maxLenPass = CREDUI_MAX_PASSWORD_LENGTH + 1;
      u32 maxLenDomain = CREDUI_MAX_DOMAIN_TARGET_LENGTH + 1;

      HICON hicon = nullptr;

      // Display a dialog box to request credentials.
      //zero(u);
      u.cbSize = sizeof(u);
      u.hwndParent = nullptr;

      // Retrieve the user name and domain name.
      // SID_NAME_USE    SidUse;
      u32           cchTmpUsername = CREDUI_MAX_USERNAME_LENGTH + 1;
      u32           cchTmpDomain = CREDUI_MAX_DOMAIN_TARGET_LENGTH + 1;
      u32           cchDomainAndUser = CREDUI_MAX_USERNAME_LENGTH + CREDUI_MAX_DOMAIN_TARGET_LENGTH + 1;

      wstring wstrCaption("\"ca2 : " + strService + "\" Authentication");
      wstring wstrMessage("The Service \"ca2 : " + strService + "\" requires current user password for installing Windows Service.");

      u32 lenUserName = CREDUI_MAX_USERNAME_LENGTH + 1;

      //::GetUserNameW(szUsername,&lenUserName);

      u32 dwLastError = 0;

      bool bOk;

      //if(!GetCurrentUserIdentity(ti))
      //   return false;
      ////szDomain[0] ='.';
      ////         szDomain[1] ='\0';
      //if(!LookupAccountSidW(
      //   nullptr,             // Local computer
      //   ti.tokenUser.puser->Sid,             // Security identifier for user
      //   szUsername,       // User name
      //   &cchTmpUsername,  // Size of user name
      //   szDomain,         // Domain name
      //   &cchTmpDomain,    // Size of domain name
      //   &SidUse))         // Account type
      //{
      //   dwResult = GetLastError();
      //   debug_print("\n getCredentialsForService LookupAccountSidLocalW failed: win32 error = 0x%x\n",dwResult);
      //   return false;
      //}

      ULONG l = sizeof(szDomainAndUser) / sizeof(WCHAR);

      ::GetUserNameExW(NameSamCompatible, szDomainAndUser, &l);

      // Combine the domain and user names.
      /*swprintf_s(
         szDomainAndUser,
         cchDomainAndUser,
         L"%s\\%s",
         szDomain,
         szUsername);*/

      WCHAR szPassword[CREDUI_MAX_PASSWORD_LENGTH + 1];
      ::zero(szPassword, CREDUI_MAX_PASSWORD_LENGTH);

      // Call CredPackAuthenticationBufferW once to determine the size,
      // in bytes, of the authentication buffer.

      if (!CredPackAuthenticationBufferW(
         0,                // Reserved
         szDomainAndUser,  // Domain\User name
         szPassword,       // User Password
         nullptr,             // Packed credentials
         &pvInAuthBlob.m_size)    // Size, in bytes, of credentials
         && GetLastError() != ERROR_INSUFFICIENT_BUFFER)
      {

         dwResult = GetLastError();

         //debug_print("\n getCredentialsForService CredPackAuthenticationBufferW (1) failed: win32 error = 0x%x\n",dwResult);

         throw ::exception(error_failed);

      }

      // Allocate memory for the input buffer.
      pvInAuthBlob.alloc();

      if (pvInAuthBlob.is_null())
      {

         //debug_print("\n getCredentialsForService CoTaskMemAlloc() Out of memory.\n");

         throw ::exception(error_failed);

      }

      // Call CredPackAuthenticationBufferW again to retrieve the
      // authentication buffer.
      if (!CredPackAuthenticationBufferW(
         0,
         szDomainAndUser,
         szPassword,
         (PBYTE)pvInAuthBlob.m_p,
         &pvInAuthBlob.m_size))
      {
         dwResult = GetLastError();
         //debug_print("\n CredPackAuthenticationBufferW (2) failed: win32 error = 0x%x\n",dwResult);
      }


      u.pszCaptionText = wstrCaption;
      u.pszMessageText = wstrMessage;
      hicon = (HICON) ::LoadImageW(::GetModuleHandle(nullptr), MAKEINTRESOURCEW(1), IMAGE_ICON, 48, 48, LR_DEFAULTCOLOR);


      if (hicon != nullptr)
      {

         u.hbmBanner = get_icon_hbitmap(hicon);

         ::DeleteObject(hicon);

      }

   retry:

      dwResult = CredUIPromptForWindowsCredentialsW(
         &u,             // Customizing information
         dwLastError,               // Error code to display
         &ulAuthPackage,  // Authorization package
         pvInAuthBlob,    // Credential ::u8 array
         pvInAuthBlob.m_size,    // Size of credential input buffer
         &pvAuthBlob,     // Output credential ::u8 array
         &pvAuthBlob.m_size,     // Size of credential ::u8 array
         &fSave,          // Select the save check box.
         //CREDUIWIN_SECURE_PROMPT |
         CREDUIWIN_IN_CRED_ONLY |
         CREDUIWIN_ENUMERATE_CURRENT_USER
      );


      WCHAR szUsername[CREDUI_MAX_USERNAME_LENGTH + 1];


      if (dwResult == NO_ERROR)
      {

         DWORD lenName = maxLenName;
         DWORD lenDomain = maxLenDomain;
         DWORD lenPass = maxLenPass;

         bOk = CredUnPackAuthenticationBufferW(CRED_PACK_PROTECTED_CREDENTIALS,
            pvAuthBlob,
            pvAuthBlob.m_size,
            szUsername,
            &lenName,
            szDomain,
            &lenDomain,
            szPassword,
            &lenPass) != false;


         if (!bOk)
         {
            dwLastError = ::GetLastError();
            goto retry;
         }

         //wcscpy(szDomainAndUser,szUsername);

         ::GetUserNameExW(NameSamCompatible, szDomainAndUser, &l);

         bOk = CredUIParseUserNameW(
            szDomainAndUser,
            szUsername,
            CREDUI_MAX_USERNAME_LENGTH,
            szDomain,
            CREDUI_MAX_DOMAIN_TARGET_LENGTH
         ) == NO_ERROR;

         if (!bOk)
         {
            dwLastError = ::GetLastError();
            goto retry;
         }

         HANDLE h;

         if (::LogonUserW(
            szUsername,
            szDomain,
            szPassword,
            LOGON32_LOGON_SERVICE,
            LOGON32_PROVIDER_DEFAULT,
            &h))
         {

            ::CloseHandle(h);

         }
         else
         {

            dwLastError = ::GetLastError();

            goto retry;

         }

         wcscpy(szUsername, szDomainAndUser);

      }
      else
      {

         if (dwResult != ERROR_CANCELLED)
         {

            goto retry;

         }

         hr = HRESULT_FROM_WIN32(dwResult);

         bOk = false;

      }

      if (u.hbmBanner != nullptr)
      {

         ::DeleteObject(u.hbmBanner);

      }

      if (!bOk)
      {

         throw ::exception(error_failed);

      }

      strUsername = szUsername;

      strPassword = szPassword;

   }


   string node::calc_service_name()
   {

      ::acme::application* papp = get_app();

      if (get_app()->m_papexapplication->m_strAppName.is_empty()
         || get_app()->m_papexapplication->m_strAppName.case_insensitive_order("bergedge") == 0
         || !get_app()->is_service())
         return "";

      string strServiceName = get_app()->m_strAppId;

      strServiceName.replace_with("-", "/");

      strServiceName.replace_with("-", "\\");

      return strServiceName;

   }


   void node::enable_service()
   {

      string strServiceName = calc_service_name();

      if (strServiceName.is_empty())
      {

         throw ::exception(error_failed);

      }

      SC_HANDLE hdlSCM = OpenSCManagerW(0, 0, SC_MANAGER_CREATE_SERVICE);

      if (hdlSCM == 0)
      {

         u32 lasterror = ::GetLastError();

         ::windows::throw_last_error(lasterror);

      }

      string strDisplayName(strServiceName);

      strDisplayName.replace_with(" ", "-");

      string strExe(strServiceName);

      strExe.replace_with("_", "-");

      strExe += ".exe";

      string strCalling = m_pcontext->m_papexcontext->dir()->module() / strExe + " : service";

      if (is_true("no_remote_simpledb"))
      {

         strCalling += " no_remote_simpledb";

      }

      ::string strUserName;
      ::string strPassword;

      auto papp = get_app()->m_papexapplication;

      if (get_app()->is_user_service())
      {

         _getCredentialsForService(get_app()->m_strAppId, strUserName, strPassword);
         //         {

         //pname = lpszName;
         //ppass = pszPass;

         //}
         //else
         //{

         //   throw ::exception(error_failed);

         //}

      }

      enable_service(strServiceName, strDisplayName, strCalling, strUserName, strPassword);

   }


   void node::disable_service()
   {

      string strServiceName = calc_service_name();

      if (strServiceName.is_empty())
      {

         throw ::exception(error_failed);

      }

      disable_service(strServiceName);

   }


   void node::start_service()
   {

      string strServiceName = calc_service_name();

      if (strServiceName.is_empty())
      {

         throw ::exception(error_failed);

      }

      start_service(strServiceName);

   }


   void node::enable_service(const ::string& strServiceName, const ::string& strDisplayName, const ::string& strCommand, const ::string& strUser, const ::string& strPass)
   {

      if (strServiceName.is_empty())
      {

         throw ::exception(error_bad_argument);

      }

      SC_HANDLE hdlSCM = OpenSCManagerW(0, 0, SC_MANAGER_CREATE_SERVICE);

      if (hdlSCM == 0)
      {
         //::GetLastError()
         throw ::exception(error_failed);

      }

      WCHAR lpszName[CREDUI_MAX_USERNAME_LENGTH + CREDUI_MAX_DOMAIN_TARGET_LENGTH + 1];
      WCHAR pszPass[CREDUI_MAX_PASSWORD_LENGTH + 1];

      wcscpy(lpszName, wstring(strUser));
      wcscpy(pszPass, wstring(strPass));

      SC_HANDLE hdlServ = ::CreateServiceW(
         hdlSCM,                    // SCManager database
         wstring(strServiceName),
         wstring(strDisplayName),        // service name to display
         STANDARD_RIGHTS_REQUIRED,  // desired access
         SERVICE_WIN32_OWN_PROCESS, // service type
         SERVICE_AUTO_START,      // start type
         SERVICE_ERROR_NORMAL,      // error control type
         wstring(strCommand),                   // service's binary Path name
         0,                      // no load ordering group
         0,                      // no tag identifier
         0,                      // no dependencies
         strUser.has_char() ? lpszName : nullptr,                      // LocalSystem account
         strPass.has_char() ? pszPass : nullptr);                     // no password


      if (!hdlServ)
      {

         u32 lasterror = ::GetLastError();

         CloseServiceHandle(hdlSCM);

         ::windows::throw_last_error(lasterror);

      }

      SecureZeroMemory(lpszName, sizeof(lpszName));
      SecureZeroMemory(pszPass, sizeof(pszPass));


      CloseServiceHandle(hdlServ);
      CloseServiceHandle(hdlSCM);

      //return true;

   }


   void node::disable_service(const ::string& strServiceName)
   {

      if (strServiceName.is_empty())
      {

         throw ::exception(error_bad_argument);

      }

      SC_HANDLE hdlSCM = OpenSCManagerW(0, 0, SC_MANAGER_ALL_ACCESS);

      if (hdlSCM == 0)
      {
         //::GetLastError();
         throw ::exception(error_failed);
      }

      SC_HANDLE hdlServ = ::OpenServiceW(
         hdlSCM,                    // SCManager database
         wstring(strServiceName),
         DELETE);

      if (!hdlServ)
      {
         u32 lasterror = ::GetLastError();
         CloseServiceHandle(hdlSCM);
         if (lasterror == 1060) // Service already doesn't exist.
            return; // do self-healing
         ::windows::throw_last_error(lasterror);
      }

      if (!::DeleteService(hdlServ))
      {
         u32 lasterror = ::GetLastError();
         CloseServiceHandle(hdlServ);
         CloseServiceHandle(hdlSCM);
         ::windows::throw_last_error(lasterror);
      }

      CloseServiceHandle(hdlServ);

      CloseServiceHandle(hdlSCM);

      //return true;

   }

   void  node::stop_service()
   {

      string strServiceName = calc_service_name();

      if (strServiceName.is_empty())
      {

         throw ::exception(error_failed);

      }

      return stop_service(strServiceName);

   }


   void node::start_service(const ::string& strServiceName)
   {

      if (strServiceName.is_empty())
      {

         throw ::exception(error_failed);

      }

      SC_HANDLE hdlSCM = OpenSCManagerW(0, 0, SC_MANAGER_ALL_ACCESS);

      if (hdlSCM == 0)
      {
         //::GetLastError();
         throw ::exception(error_failed);

      }

      SC_HANDLE hdlServ = ::OpenServiceW(
         hdlSCM,                    // SCManager database
         wstring(strServiceName),
         SERVICE_START);                     // no password


      if (!hdlServ)
      {
         CloseServiceHandle(hdlSCM);
         //Ret = ::GetLastError();
         throw ::exception(error_failed);
      }

      bool bOk = StartService(hdlServ, 0, nullptr) != false;

      CloseServiceHandle(hdlServ);
      CloseServiceHandle(hdlSCM);

      //return bOk != false;
   }


   void node::stop_service(const ::string& strServiceName)
   {

      if (strServiceName.is_empty())
      {
         throw ::exception(error_failed);

      }

      SC_HANDLE hdlSCM = OpenSCManagerW(0, 0, SC_MANAGER_ALL_ACCESS);

      if (hdlSCM == 0)
      {
         //::GetLastError();
         throw ::exception(error_failed);
      }

      SC_HANDLE hdlServ = ::OpenServiceW(
         hdlSCM,                    // SCManager database
         wstring(strServiceName),
         SERVICE_STOP);                     // no password

      if (!hdlServ)
      {
         // Ret = ::GetLastError();
         CloseServiceHandle(hdlSCM);
         throw ::exception(error_failed);
      }

      SERVICE_STATUS ss;

      memory_set(&ss, 0, sizeof(ss));

      bool bOk = ::ControlService(hdlServ, SERVICE_CONTROL_STOP, &ss) != false;

      ::DeleteService(hdlServ);

      CloseServiceHandle(hdlServ);

      CloseServiceHandle(hdlSCM);

      //return bOk != false;
   }


   void node::raise_exception(u32 dwExceptionCode, u32 dwExceptionFlags)
   {

      RaiseException(dwExceptionCode, dwExceptionFlags, 0, nullptr);

   }


   bool node::is_remote_session()
   {

      return GetSystemMetrics(SM_REMOTESESSION) != false;

   }


   void node::set_file_status(const ::file::path& path, const ::file::file_status& status)
   {

      u32 wAttr;

      FILETIME creationTime;
      FILETIME lastAccessTime;
      FILETIME lastWriteTime;
      LPFILETIME pCreationTime = nullptr;

      LPFILETIME pLastAccessTime = nullptr;

      LPFILETIME pLastWriteTime = nullptr;

      wAttr = ::windows::get_file_attributes(path);
      //{

      //   DWORD dwLastError = ::GetLastError();

      //   auto estatus = ::windows::last_error_status(dwLastError);

      //   auto errorcode = ::windows::last_error_error_code(dwLastError);

      //   throw ::file::exception(estatus, errorcode, path, ::file::e_open_none, "!windows_get_file_attributes");

      //}


      if (status.m_attribute != wAttr && (wAttr & FILE_ATTRIBUTE_READONLY))
      {

         // set file attribute, only if currently readonly.
         // This way we will be able to modify the time assuming the
         // caller changed the file from readonly.

         ::windows::set_file_attributes(path, status.m_attribute & ~FILE_ATTRIBUTE_READONLY);

      }


      //{

      //   DWORD dwLastError = ::GetLastError();

      //   auto estatus = ::windows::last_error_status(dwLastError);

      //   auto errorcode = ::windows::last_error_error_code(dwLastError);

      //   throw ::file::exception(estatus, errorcode, ::string(wstr), ::file::e_open_none, "!SetFileAttributesW");

      //}

      //}

      // last modification time
      if (status.m_timeModification != 0_s)
      {

         //system()->m_pnode->datetime_to_filetime((file_time_t *) &lastWriteTime, status.m_mtime);

         lastWriteTime = as_FILETIME(file_time(status.m_timeModification));

         pLastWriteTime = &lastWriteTime;


      }

      // last access time
      if (status.m_timeAccess != 0_s)
      {

         //auto pnode = system()->m_papexsystem->node();

         lastAccessTime = as_FILETIME(file_time(status.m_timeAccess));

         pLastAccessTime = &lastAccessTime;


      }

      // create time
      if (status.m_timeCreation != 0_s)
      {

         creationTime = as_FILETIME(file_time(status.m_timeCreation));

         pCreationTime = &creationTime;

      }

      ::windows::file_instance fileinstance;

      if (!fileinstance.safe_create_file(path, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr))
      {

         DWORD dwLastError = ::GetLastError();

         throw_last_error_exception(path, ::file::e_open_read | ::file::e_open_write, dwLastError, "apex_windows::node::set_file_status safe_create_file failed");

      }


      //if(hFile == INVALID_HANDLE_VALUE)
      //{

      //   DWORD dwLastError = ::GetLastError();

      //   auto estatus = ::windows::last_error_status(dwLastError);

      //   auto errorcode = ::windows::last_error_error_code(dwLastError);

      //   throw ::file::exception(estatus, errorcode, wstr, "!CreateFileW");

      //}

      fileinstance.set_file_time(pCreationTime, pLastAccessTime, pLastWriteTime);
      //{

      //   DWORD dwLastError = ::GetLastError();

      //   auto estatus = ::windows::last_error_status(dwLastError);

      //   auto errorcode = ::windows::last_error_error_code(dwLastError);

      //   throw ::file::exception(estatus, errorcode, wstr, "!SetFileTime");

      //}

      //if(!::CloseHandle(hFile))
      //{

      //   DWORD dwLastError = ::GetLastError();

      //   auto estatus = ::windows::last_error_status(dwLastError);

      //   auto errorcode = ::windows::last_error_error_code(dwLastError);

      //   throw ::file::exception(estatus, errorcode, wstr, "!CloseHandle");

      //}

      if ((u32)status.m_attribute != wAttr && (status.m_attribute & FILE_ATTRIBUTE_READONLY))
      {

         ::windows::set_file_attributes(path, status.m_attribute);
         //{

         //   DWORD dwLastError = ::GetLastError();

         //   auto estatus = ::windows::last_error_status(dwLastError);

         //   auto errorcode = ::windows::last_error_error_code(dwLastError);

         //   throw ::file::exception(estatus, errorcode, wstr, "!SetFileAttributesW");

         //}

      }

   }






   bool node::has_alias_in_path(const scoped_string& str, bool bNoUI, bool bNoMount)
   {

      return false;

   }


   bool node::is_alias(const ::file::path& path)
   {

      return path.case_insensitive_ends(".lnk");

   }


   void node::get_default_browser(string& strId, ::file::path& path, string& strParam)
   {

      //try
      //{

      ::acme_windows::registry::key key;

      key.open(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\FileExts\\.html\\UserChoice", false);

      string strProgId;

      string strHash;

      key._get("Hash", strHash);

      key._get("ProgId", strProgId);

      if (strProgId.begins("App") && strHash.has_char())
      {

         strId = "edge";

      }
      if (strProgId.case_insensitive_begins("IE."))
      {

         strId = "ie";

      }
      else if (strProgId.case_insensitive_begins("ChromeHTML"))
      {

         strId = "chrome";

      }
      else if (strProgId.case_insensitive_begins("FirefoxHTML"))
      {

         strId = "firefox";

      }
      else if (strProgId.case_insensitive_begins("Opera"))
      {

         strId = "opera";

      }
      else if (strProgId.case_insensitive_begins("VivaldiHTM."))
      {

         strId = "vivaldi";

      }
      else if (strProgId.case_insensitive_ends("app_core_commander"))
      {

         strId = "commander";

      }
      else
      {

         strId = "commander";

      }

      string strDefault;

      key._open(HKEY_CLASSES_ROOT, strProgId + "\\shell\\open\\command", false);

      key._get("", strDefault);

      if (strDefault.is_empty())
      {

         throw ::exception(error_failed);

      }

      bool bQuote = strDefault.case_insensitive_begins_eat("\"");

      strsize iFind = strDefault.case_insensitive_find_index(".exe");

      if (iFind <= 0)
      {

         throw ::exception(error_failed);

      }

      path = strDefault.left(iFind);

      path += ".exe";

      //MessageBox(nullptr, path, "pathProgram", e_message_box_ok);

      strParam = strDefault.substr(iFind + 5);

      if (bQuote)
      {

         strParam.case_insensitive_begins_eat("\"");

      }

      //   return true;

      //}
      //catch (...)
      //{

      //   return false;

      //}

   }


   void node::initialize_wallpaper_fileset(::file::set* pfileset, bool bAddSearch)
   {

      if (bAddSearch)
      {

         ::file::path pathFolder;

         acmedirectory()->m_pplatformdir->_shell_get_special_folder_path(nullptr, pathFolder, CSIDL_WINDOWS, false);

         pathFolder /= "Web/Wallpaper";

         pfileset->add_search(pathFolder, true);

      }

      //return true;

   }


   void node::set_dark_mode(bool bDarkMode)
   {

      set_system_dark_mode1(bDarkMode);

      set_app_dark_mode1(bDarkMode);

      DWORD_PTR res;
      SendMessageTimeout(HWND_BROADCAST, WM_SETTINGCHANGE, 0, (LPARAM)TEXT("ImmersiveColorSet"), 0, 1000, &res);

      //return ::success;

   }


   //void node::set_system_dark_mode1(bool bSet)
   //{

   //   ::acme_windows::registry::key key(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Themes\\Personalize", true);

   //   ::u32 dwSystemUseLightTheme;
   //   if (bSet)
   //   {
   //      dwSystemUseLightTheme = 0;
   //   }
   //   else
   //   {
   //      dwSystemUseLightTheme = 1;
   //   }

   //   key._set("SystemUsesLightTheme", dwSystemUseLightTheme);


   //   //return ::success;

   //}


   //void node::set_app_dark_mode1(bool bSet)
   //{

   //   ::acme_windows::registry::key key(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Themes\\Personalize", true);

   //   ::u32 dwAppsUseLightTheme;
   //   if (bSet)
   //   {
   //      dwAppsUseLightTheme = 0;
   //   }
   //   else
   //   {
   //      dwAppsUseLightTheme = 1;
   //   }

   //   key._set("AppsUseLightTheme", dwAppsUseLightTheme);

   //   //return ::success;

   //}



   //#elif defined(LINUX)
   //   //string strDir;
   //   //strDir = m_pcontext->m_papexcontext->dir().path(getenv("HOME"), "Pictures");
   //   //imagefileset.add_search(strDir);
   //   string strDir;
   //   strDir = "/usr/share/backgrounds";
   //   imagefileset.add_search(strDir, true);
   //            }
   //
   //#elif defined(MACOS)
   //   //string strDir;
   //   //strDir = m_pcontext->m_papexcontext->dir().path(getenv("HOME"), "Pictures");
   //   //imagefileset.add_search(strDir);
   //   string strDir;
   //   strDir = "/Library/Desktop Pictures";
   //   imagefileset.add_search(strDir, true);
   //            }
   //
   //#else


   void node::file_open(const ::file::path& pathParam, const string& strParams, const ::file::path& pathFolder)
   {

      auto path = m_pcontext->m_papexcontext->defer_process_path(pathParam);

      manual_reset_event manualresetevent;

      ::e_status estatusFileOpen = ::success;
      ::i32 iShellExecuteExitCode = 33;
      DWORD dwLastError = 0;
      const char* pszShellExecuteError = nullptr;

      fork([=, &manualresetevent, &estatusFileOpen,
         &dwLastError, &iShellExecuteExitCode, &pszShellExecuteError]()
         {

            ::CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);

            //::CoInitializeEx(nullptr, COINIT_DISABLE_OLE1DDE);

            at_end_of_scope
            {

               manualresetevent.SetEvent();

               ::CoUninitialize();

            };

            SHELLEXECUTEINFOW si{};

            //PeekMessage(nullptr, nullptr, 0, 0, 0);

            ::windows_path windowspathTarget(path.windows_path());

            ::windows_path windowspathFolder(pathFolder.windows_path());

            wstring wstrParams(strParams);

            const wchar_t* pwszParams = wstrParams.c_str();

            const wchar_t* pwszFolder = windowspathFolder.c_str();

            si.cbSize = sizeof(si);

            //si.fMask = SEE_MASK_ASYNCOK;
            si.fMask = SEE_MASK_NOASYNC;

            si.fMask |= SEE_MASK_FLAG_NO_UI;

            si.fMask |= SEE_MASK_WAITFORINPUTIDLE;

            si.hwnd = nullptr;

            si.lpVerb = L"open";

            ::pointer < ::itemidlist > pitemidlist = path.m_pparticleOsPath;

            if (windowspathTarget.is_empty() && pitemidlist)
            {

               si.fMask |= SEE_MASK_IDLIST;

               si.lpIDList = pitemidlist->m_pidl;


            }
            else
            {

               si.lpFile = windowspathTarget;

            }

            si.lpParameters = pwszParams;

            si.lpDirectory = pwszFolder;

            si.nShow = SW_SHOWDEFAULT;

            si.hInstApp = nullptr;

            ShellExecuteExW(&si);

            iShellExecuteExitCode = (int)(iptr)si.hInstApp;

            if (iShellExecuteExitCode > 32)
            {

               estatusFileOpen = ::success;

            }
            else
            {
               dwLastError = ::GetLastError();
               switch (iShellExecuteExitCode)
               {
               case 0:
                  pszShellExecuteError = "The operating system is out of memory or resources.";
                  break;
                  //ERROR_FILE_NOT_FOUND
                  //pszShellExecuteError = "The specified file was not found.
               case   SE_ERR_FNF:
                  pszShellExecuteError = "The specified file was not found.";
                  break;

                  //ERROR_PATH_NOT_FOUND
                  //pszShellExecuteError = "The specified path was not found.
               case  SE_ERR_PNF:
                  pszShellExecuteError = "The specified path was not found.";
                  break;

               case   ERROR_BAD_FORMAT:
                  pszShellExecuteError = "The.exe file is invalid(non - Win32.exe or error in.exe image).";
                  break;
               case   SE_ERR_ACCESSDENIED:
                  pszShellExecuteError = "The operating system denied access to the specified file.";
                  break;
               case   SE_ERR_ASSOCINCOMPLETE:
                  pszShellExecuteError = "The file name association is incomplete or invalid.";
                  break;
               case   SE_ERR_DDEBUSY:
                  pszShellExecuteError = "The DDE transaction could not be completed because other DDE transactions were being processed.";
                  break;
               case  SE_ERR_DDEFAIL:
                  pszShellExecuteError = "The DDE transaction failed.";
                  break;
               case  SE_ERR_DDETIMEOUT:
                  pszShellExecuteError = "The DDE transaction could not be completed because the request timed out.";
                  break;
               case   SE_ERR_DLLNOTFOUND:
                  pszShellExecuteError = "The specified DLL was not found.";
                  break;
               case  SE_ERR_NOASSOC:
                  pszShellExecuteError = "There is no application associated with the given file name extension.This error will also be returned if you attempt to print a file that is not printable.";
                  break;
               case  SE_ERR_OOM:
                  pszShellExecuteError = "There was not enough memory to complete the operation.";
                  break;
               case  SE_ERR_SHARE:
                  pszShellExecuteError = "A sharing violation occurred.";
                  break;
                  break;
               default:
                  pszShellExecuteError = "Some Error occurred";
               }

               estatusFileOpen = error_failed;

            }

         });

      auto estatus = manualresetevent.wait(5_min);

      if (estatusFileOpen.failed())
      {

         ::string strMessage;

         strMessage.formatf("apex_windows::node::file_open ShellExecuteExW failed with error (%d, %d) \"%s\"", iShellExecuteExitCode, dwLastError, pszShellExecuteError);

         auto errorcode = ::windows::last_error_error_code(dwLastError);

         throw exception(estatusFileOpen, { errorcode }, strMessage);

      }
      else if (estatus.failed())
      {

         throw exception(estatus, "apex_windows::node::file_open failed");

      }

   }


   //https://stackoverflow.com/questions/1591342/c-how-to-determine-if-a-windows-process-is-running
   //#include <windows.h>
   //#include <tlhelp32.h>
   //#include <tchar.h>
   //
   //   bool IsProcessRunning(const TCHAR* const executableName) {
   //      PROCESSENTRY32 entry;
   //      entry.dwSize = sizeof(PROCESSENTRY32);
   //
   //      const auto snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
   //
   //      if (!Process32First(snapshot, &entry)) {
   //         CloseHandle(snapshot);
   //         return false;
   //      }
   //
   //      do {
   //         if (!_tcsicmp(entry.szExeFile, executableName)) {
   //            CloseHandle(snapshot);
   //            return true;
   //         }
   //      } while (Process32Next(snapshot, &entry));
   //
   //      CloseHandle(snapshot);
   //      return false;
   //   }
   //

   void node::hidden_start(const ::file::path& pathParam, const string& strParams, const ::file::path& pathFolder)
   {

      auto path = m_pcontext->m_papexcontext->defer_process_path(pathParam);

      fork([=]()
         {

            ::CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);

            SHELLEXECUTEINFOW si{};

            PeekMessage(nullptr, nullptr, 0, 0, 0);

            wstring wstrTarget(path);

            wstring wstrFolder(pathFolder);

            wstring wstrParams(strParams);

            const wchar_t* pwszParams = wstrParams.c_str();

            const wchar_t* pwszFolder = wstrFolder.c_str();

            si.cbSize = sizeof(si);

            si.fMask = SEE_MASK_ASYNCOK;

            si.hwnd = nullptr;

            si.lpVerb = L"open";

            auto pitemidlist = path.m_pparticleOsPath.cast < ::itemidlist >();

            if (wstrTarget.is_empty() && pitemidlist)
            {

               si.fMask |= SEE_MASK_IDLIST;

               si.lpIDList = pitemidlist->m_pidl;


            }
            else
            {

               si.lpFile = wstrTarget;


            }

            si.lpParameters = pwszParams;


            si.lpDirectory = pwszFolder;


            si.nShow = SW_HIDE;

            si.hInstApp = nullptr;

            ShellExecuteExW(&si);

            ::CoUninitialize();

         });

      //return true;

   }


   void node::hidden_run(const class time& timeWait, const ::file::path& pathParam, const string& strParams, const ::file::path& pathFolder)
   {

      auto pevent = __allocate< manual_reset_event >();

      auto path = m_pcontext->m_papexcontext->defer_process_path(pathParam);

      class ::time timeStart;

      timeStart.Now();

      bool bSuccess = true;

      fork([pevent, &bSuccess, timeStart, timeWait, path, pathFolder, strParams]()
         {

            ::CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);

            SHELLEXECUTEINFOW si{};

            PeekMessage(nullptr, nullptr, 0, 0, 0);

            wstring wstrTarget(path);

            wstring wstrFolder(pathFolder);

            wstring wstrParams(strParams);

            const wchar_t* pwszParams = wstrParams.c_str();

            const wchar_t* pwszFolder = wstrFolder.c_str();

            si.cbSize = sizeof(si);

            //si.fMask = SEE_MASK_ASYNCOK;
            si.fMask = SEE_MASK_NOCLOSEPROCESS;

            si.hwnd = nullptr;

            si.lpVerb = L"open";

            auto pitemidlist = path.m_pparticleOsPath.cast < ::itemidlist >();

            if (wstrTarget.is_empty() && pitemidlist)
            {

               si.fMask |= SEE_MASK_IDLIST;

               si.lpIDList = pitemidlist->m_pidl;

            }
            else
            {

               si.lpFile = wstrTarget;

            }

            si.lpParameters = pwszParams;

            si.lpDirectory = pwszFolder;

            si.nShow = SW_HIDE;

            si.hInstApp = nullptr;

            ShellExecuteExW(&si);

            auto dwWait = ::windows::wait(timeWait);

            auto timeElapsed(timeStart.elapsed());

            auto dwElapsed = ::windows::wait(timeElapsed);

            auto i = dwWait - dwElapsed;

            if (i < 0)
            {

               bSuccess = false;

            }
            else
            {

               DWORD dwWait = (DWORD)minimum(INFINITE, i);

               bSuccess = WaitForSingleObject(si.hProcess, dwWait);

            }

            pevent->SetEvent();

            ::CloseHandle(si.hProcess);

            ::CoUninitialize();

         });

      pevent->wait(timeWait);

      if (bSuccess)
      {

         throw exception(error_wait_timeout);

      }

   }


   void node::register_user_auto_start(const string& strId, const ::file::path& pathExecutable, const string& strArguments, bool bRegister)
   {

      current_user_set_run(strId, pathExecutable, strArguments, bRegister);

      //return true;

   }


   bool node::is_user_auto_start(const string& strAppId)
   {

      ::acme_windows::registry::key keyKar;

      if (keyKar._open(HKEY_CURRENT_USER, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", false))
      {

         string strValue;

         if (keyKar._get(strAppId, strValue))
         {

            if (strValue.has_char())
            {

               return true;

            }

         }

      }

      return false;

   }


   ::file::path node::get_app_path(const ::string& strApp)
   {

      string str(strApp);

      ::acme_windows::registry::key key;

      string strDefault;

   repeat:

      if (key._open(HKEY_LOCAL_MACHINE, "Software\\Microsoft\\Windows\\CurrentVersion\\App Paths\\" + str, false))
      {

         if (key._get("", strDefault))
         {

            if (strDefault.has_char())
            {

               return strDefault;

            }

         }

      }

      if (!str.case_insensitive_ends(".exe"))
      {

         str += ".exe";

         goto repeat;

      }

      return ::acme_windows_common::node::get_app_path(str);

   }


   void node::set_default_browser()
   {

      auto papp = get_app()->m_papexapplication;

      string strTargetProgId;
      string strModule = solve_relative(acmefile()->module());

      strTargetProgId = get_app()->m_papexapplication->m_strAppName;

      strTargetProgId.replace_with("_", "-");
      strTargetProgId.replace_with("_", "\\");
      strTargetProgId.replace_with("_", "/");

      __prevent_bad_status_exception;

      {

         ::acme_windows::registry::key regkey(HKEY_LOCAL_MACHINE, "SOFTWARE\\RegisteredApplications", true);

         string strValue;

         regkey.set(strTargetProgId, "Software\\Clients\\StartMen::u32ernet\\" + strTargetProgId + "\\Capabilities");

      }

      {

         ::acme_windows::registry::key regkey(HKEY_LOCAL_MACHINE, "Software\\Clients\\StartMen::u32ernet\\" + strTargetProgId, true);

         string strValue;

         regkey.set("", get_app()->find_string("ApplicationName"));

      }

      {

         ::acme_windows::registry::key regkey(HKEY_LOCAL_MACHINE, "Software\\Clients\\StartMen::u32ernet\\" + strTargetProgId + "\\Capabilities", true);

         string strValue;

         regkey.set("ApplicationDescription", get_app()->find_string("ApplicationDescription"));
         regkey.set("ApplicationIcon", get_app()->find_string("ApplicationIcon"));
         regkey.set("ApplicationName", get_app()->find_string("ApplicationName"));

      }

      {

         ::acme_windows::registry::key regkey(HKEY_LOCAL_MACHINE, "Software\\Clients\\StartMen::u32ernet\\" + strTargetProgId + "\\Capabilities\\FileAssociations", true);

         string strValue;

         regkey.set(".htm", strTargetProgId);
         regkey.set(".html", strTargetProgId);
         regkey.set(".pdf", strTargetProgId);
         regkey.set(".shtml", strTargetProgId);
         regkey.set(".svg", strTargetProgId);
         regkey.set(".webp", strTargetProgId);
         regkey.set(".xht", strTargetProgId);
         regkey.set(".xhtml", strTargetProgId);

      }

      {

         ::acme_windows::registry::key regkey(HKEY_LOCAL_MACHINE, "Software\\Clients\\StartMen::u32ernet\\" + strTargetProgId + "\\Capabilities\\Startmenu", true);

         string strValue;

         regkey.set("StartMen::u32ernet", strTargetProgId);

      }

      {

         ::acme_windows::registry::key regkey(HKEY_LOCAL_MACHINE, "Software\\Clients\\StartMen::u32ernet\\" + strTargetProgId + "\\Capabilities\\URLAssociations", true);

         string strValue;

         regkey.set("ftp", strTargetProgId);
         regkey.set("http", strTargetProgId);
         regkey.set("https", strTargetProgId);
         regkey.set("irc", strTargetProgId);
         regkey.set("mailto", strTargetProgId);
         regkey.set("mms", strTargetProgId);
         regkey.set("news", strTargetProgId);
         regkey.set("nntp", strTargetProgId);
         regkey.set("sms", strTargetProgId);
         regkey.set("smsto", strTargetProgId);
         regkey.set("tel", strTargetProgId);
         regkey.set("urn", strTargetProgId);
         regkey.set("webcal", strTargetProgId);

      }

      {

         ::acme_windows::registry::key regkey(HKEY_LOCAL_MACHINE, "Software\\Clients\\StartMen::u32ernet\\" + strTargetProgId + "\\DefaultIcon", true);

         string strValue;

         regkey.set("", strModule + ",0");

      }


      {

         ::acme_windows::registry::key regkey(HKEY_LOCAL_MACHINE, "Software\\Clients\\StartMen::u32ernet\\" + strTargetProgId + "\\InstallInfo", true);

         string strValue;

         regkey.set("HideIconsCommand", "\"" + strModule + "\" : hide_icons");
         regkey.set("IconsVisible", 1);
         regkey.set("ReinstallCommand", "\"" + strModule + "\" : install");
         regkey.set("ShowIconsCommand", "\"" + strModule + "\" : show_icons");

      }


      {

         ::acme_windows::registry::key regkey(HKEY_LOCAL_MACHINE, "Software\\Clients\\StartMen::u32ernet\\" + strTargetProgId + "\\shell\\open\\command", true);

         string strValue;

         regkey.set("", "\"" + strModule + "\" : browser_weather=default");

      }


      {

         ::acme_windows::registry::key regkey(HKEY_CLASSES_ROOT, strTargetProgId, true);

         regkey.set("", strTargetProgId + " HTML Document");
         regkey.set("AppUserModelId", get_app()->find_string("AppUserModelId"));

      }
      {

         ::acme_windows::registry::key regkey(HKEY_CLASSES_ROOT, strTargetProgId + "\\papplication", true);

         regkey.set("ApplicationCompany", get_app()->find_string("ApplicationCompany"));
         regkey.set("ApplicationDescription", get_app()->find_string("ApplicationDescription"));
         regkey.set("ApplicationIcon", get_app()->find_string("ApplicationIcon"));
         regkey.set("ApplicationName", get_app()->find_string("ApplicationName"));
         regkey.set("AppUserModelId", get_app()->find_string("AppUserModelId"));

      }
      {

         ::acme_windows::registry::key regkey(HKEY_CLASSES_ROOT, strTargetProgId + "\\DefaultIcon", true);

         regkey.set("", get_app()->find_string("DefaultIcon"));

      }

      file_association_set_shell_open_command(strTargetProgId, strTargetProgId, strModule, "\"%1\"");
      {

         ::acme_windows::registry::key regkey(HKEY_CURRENT_USER, "SOFTWARE\\Microsoft\\Windows\\shell\\Associations\\UrlAssociations\\http\\UserChoice", true);

         string strProgId;

         regkey.get("ProgId", strProgId);

         if (strProgId != strTargetProgId)
         {

            regkey.delete_value("Hash");

            regkey.set("ProgId", strTargetProgId);

         }

      }

      {

         ::acme_windows::registry::key key(HKEY_CURRENT_USER, "SOFTWARE\\Microsoft\\Windows\\shell\\Associations\\UrlAssociations\\https\\UserChoice", true);

         string strProgId;

         key.get("ProgId", strProgId);

         if (strProgId != strTargetProgId)
         {

            string strHash;

            key.delete_value("Hash");

            key.set("ProgId", strTargetProgId);

         }

      }

      {

         ::acme_windows::registry::key key(HKEY_CURRENT_USER, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Explorer\\FileExts\\.html\\UserChoice", true);

         string strProgId;

         key.get("ProgId", strProgId);

         if (strProgId != strTargetProgId)
         {

            key.delete_value("Hash");

            key.set("ProgId", strTargetProgId);

         }

      }

      {

         ::acme_windows::registry::key key(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\FileExts\\.htm\\UserChoice", true);

         string strProgId;

         key._get("ProgId", strProgId);

         if (strProgId != strTargetProgId)
         {

            key.delete_value("Hash");

            key.set("ProgId", strTargetProgId);

         }

      }

      {

         ::acme_windows::registry::key key(HKEY_CLASSES_ROOT, ".html\\OpenWithProgids", true);

         key._set(strTargetProgId, "");

      }

      {

         ::acme_windows::registry::key key(HKEY_CLASSES_ROOT, ".htm\\OpenWithProgids", true);

         key._set(strTargetProgId, "");

      }

      SHChangeNotify(SHCNE_ASSOCCHANGED, SHCNF_DWORD | SHCNF_FLUSH, nullptr, nullptr);

      sleep(1_s);

      //return true;

   }


   void node::set_file_extension_mime_type(string_array& straExtension, string_array& straMimeType)
   {

      string strTargetProgId;

      string strModule = solve_relative(acmefile()->module());

      string strApplicationRegistryPath = find_string("ApplicationRegistryPath");

      ::file::path pathApplication;

      pathApplication = "Software";

      pathApplication /= strApplicationRegistryPath;

      pathApplication /= strTargetProgId;

      strTargetProgId = get_app()->m_papexapplication->m_strAppName;

      strTargetProgId.replace_with("_", "-");
      strTargetProgId.replace_with("_", "\\");
      strTargetProgId.replace_with("_", "/");

      ::e_status estatus = ::success;

      {

         ::acme_windows::registry::key regkey(HKEY_LOCAL_MACHINE, pathApplication, true);

         string strValue;

         //auto estatusRegistry =
         regkey._set("", get_app()->find_string("ApplicationName"));

         //if(!estatusRegistry)
         //{

         //   estatus = estatusRegistry;

         //}

      }


      {

         ::acme_windows::registry::key regkey(HKEY_LOCAL_MACHINE, pathApplication / "DefaultIcon", true);

         string strValue;

         //auto estatusRegistry = 
         regkey._set("", strModule + ",0");

         //if (!estatusRegistry)
         //{

         //   estatus = estatusRegistry;

         //}


      }


      {

         ::acme_windows::registry::key regkey(HKEY_LOCAL_MACHINE, pathApplication / "InstallInfo", true);

         string strValue;

         ///auto estatusRegistry = 

         regkey._set("HideIconsCommand", "\"" + strModule + "\" : hide_icons");

         //if(estatusRegistry.succeeded())
         //{

         regkey._set("IconsVisible", 1);

         //}

         //if(estatusRegistry.succeeded())
         //{

         regkey._set("ReinstallCommand", "\"" + strModule + "\" : install");

         //}

         //if(estatusRegistry.succeeded())
         //{
         regkey._set("ShowIconsCommand", "\"" + strModule + "\" : show_icons");

         //}

         //if (!estatusRegistry)
         //{

         //   estatus = estatusRegistry;

         //}

      }

      {

         ::acme_windows::registry::key regkey(HKEY_LOCAL_MACHINE, pathApplication / "shell/open/command", true);

         string strValue;

         regkey._set("", "\"" + strModule + "\" \"%1\"");

         /*      if (!estatusRegistry)
               {

                  estatus = estatusRegistry;

               }*/

      }


      ::file::path pathApplicationCapabilities;

      pathApplicationCapabilities = pathApplication / "Capabilities";

      {

         ::acme_windows::registry::key regkey(HKEY_LOCAL_MACHINE, "SOFTWARE\\RegisteredApplications", true);

         string strValue;

         /*auto estatusRegistry =*/ regkey._set(strTargetProgId, pathApplicationCapabilities);

         /*        if (!estatusRegistry)
                 {

                    estatus = estatusRegistry;

                 }*/

      }

      {

         ::acme_windows::registry::key regkey(HKEY_LOCAL_MACHINE, pathApplicationCapabilities, true);

         string strValue;

         //auto estatusRegistry = 
         regkey._set("ApplicationDescription", get_app()->find_string("ApplicationDescription"));

         //if(estatusRegistry.succeeded())
         //{

            //estatusRegistry =
         regkey._set("ApplicationIcon", get_app()->find_string("ApplicationIcon"));

         //}

         //if(estatusRegistry.succeeded())
         //{

            //estatusRegistry = 
         regkey._set("ApplicationName", get_app()->find_string("ApplicationName"));

         //}

         //if (!estatusRegistry)
         //{

         //   estatus = estatusRegistry;

         //}


      }

      {

         ::acme_windows::registry::key regkey(HKEY_LOCAL_MACHINE, pathApplicationCapabilities / "FileAssociations", true);

         string strValue;

         //auto estatusRegistry = 
         regkey._set(".mp4", strTargetProgId);

         //if (!estatusRegistry)
         //{

         //   estatus = estatusRegistry;

         //}

      }

      //{

      //   ::acme_windows::registry::key regkey(HKEY_LOCAL_MACHINE, "Software\\Clients\\StartMen::u32ernet\\" + strTargetProgId + "\\Capabilities\\Startmenu", true);

      //   string strValue;

      //   regkey.set("StartMen::u32ernet", strTargetProgId);

      //}

      {

         ::acme_windows::registry::key regkey(HKEY_LOCAL_MACHINE, pathApplicationCapabilities / "FileAssociations", true);

         for (index i = 0; i < straMimeType.get_count(); i++)
         {

            string strExtension = straExtension[i];

            regkey._set("." + strExtension, strTargetProgId + "." + strExtension);

         }

      }

      {

         ::acme_windows::registry::key regkey(HKEY_LOCAL_MACHINE, pathApplicationCapabilities / "MimeAssociations", true);

         for (index i = 0; i < straMimeType.get_count(); i++)
         {

            string strMimeType = straMimeType[i];

            string strExtension = straExtension[i];

            regkey._set(strMimeType, strTargetProgId + "." + strExtension);

         }

      }

      //{

      //   ::acme_windows::registry::key regkey(HKEY_CLASSES_ROOT, strTargetProgId, true);

      //   regkey.set("", strTargetProgId + " HTML Document");
      //   regkey.set("AppUserModelId", get_app()->prop("AppUserModelId"));

      //}
      {

         ::acme_windows::registry::key regkey(HKEY_CLASSES_ROOT, strTargetProgId + "\\papplication", true);

         regkey._set("ApplicationCompany", get_app()->find_string("ApplicationCompany"));

         regkey._set("ApplicationDescription", get_app()->find_string("ApplicationDescription"));


         regkey._set("ApplicationIcon", get_app()->find_string("ApplicationIcon"));

         regkey._set("ApplicationName", get_app()->find_string("ApplicationName"));

         regkey._set("AppUserModelId", get_app()->find_string("AppUserModelId"));

         //}

         //if (!estatusRegistry)
         //{

         //   estatus = estatusRegistry;

         //}

      }
      {

         ::acme_windows::registry::key regkey(HKEY_CLASSES_ROOT, strTargetProgId + "\\DefaultIcon", true);

         regkey._set("", get_app()->find_string("DefaultIcon"));

         //if (!estatusRegistry)
         //{

         //   estatus = estatusRegistry;

         //}

      }

      for (index i = 0; i < straExtension.get_count(); i++)
      {

         string strExtension = straExtension[i];

         file_association_set_shell_open_command(strExtension, strTargetProgId + "." + strExtension, strModule, "\"%1\"");
         //{

         //   estatus = ::error_failed;

         //}

         //{

         ::acme_windows::registry::key regkey(HKEY_CLASSES_ROOT, "." + strExtension + "\\OpenWithProgids", true);

         regkey._set(strTargetProgId, "");;

         //}

      }

      //{

      //   ::acme_windows::registry::key regkey(HKEY_CURRENT_USER, "SOFTWARE\\Microsoft\\Windows\\shell\\Associations\\UrlAssociations\\http\\UserChoice", true);

      //   string strProgId;

      //   regkey.QueryValue("ProgId", strProgId);

      //   if (strProgId != strTargetProgId)
      //   {

      //      regkey.DeleteValue("Hash");
      //      regkey.set("ProgId", strTargetProgId);

      //   }

      //}

      //{

      //   ::acme_windows::registry::key regkey(HKEY_CURRENT_USER, "SOFTWARE\\Microsoft\\Windows\\shell\\Associations\\UrlAssociations\\https\\UserChoice", true);

      //   string strProgId;

      //   regkey.QueryValue("ProgId", strProgId);

      //   if (strProgId != strTargetProgId)
      //   {

      //      regkey.DeleteValue("Hash");
      //      regkey.set("ProgId", strTargetProgId);

      //   }

      //}

      //{

      //   ::acme_windows::registry::key regkey(HKEY_CURRENT_USER, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Explorer\\FileExts\\.html\\UserChoice", true);
      //   string strProgId;

      //   regkey.QueryValue("ProgId", strProgId);

      //   if (strProgId != strTargetProgId)
      //   {

      //      regkey.DeleteValue("Hash");
      //      regkey.set("ProgId", strTargetProgId);

      //   }

      //}
      //{

      //   ::acme_windows::registry::key regkey(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\FileExts\\.htm\\UserChoice", true);
      //   string strProgId;

      //   regkey.QueryValue("ProgId", strProgId);

      //   if (strProgId != strTargetProgId)
      //   {

      //      regkey.DeleteValue("Hash");
      //      regkey.set("ProgId", strTargetProgId);

      //   }

      //}
      //{

      //   ::acme_windows::registry::key regkey(HKEY_CLASSES_ROOT, ".htm\\OpenWithProgids", true);

      //   if(!regkey.set(strTargetProgId, ""))
      //   {

      //      informationf("Failure to set .htm/OpenWithProgids");

      //   }

      //}
      //file_association_set_shell_open_command(".htm", strTargetProgId, strModule, "\"%1\"");
      //file_association_set_shell_open_command(".html", strTargetProgId, strModule, "\"%1\"");
      //file_association_set_shell_open_command("http", strTargetProgId, strModule, "\"%1\"");
      //file_association_set_shell_open_command("https", strTargetProgId, strModule, "\"%1\"");

      fork([this]()
         {

            defer_co_initialize_ex(false);


            SHChangeNotify(SHCNE_ASSOCCHANGED, SHCNF_DWORD | SHCNF_FLUSH, nullptr, nullptr);

            preempt(3_s);

            //}

         });


      //if (!estatus)
      //{

      //   return false;

      //}

      //return true;

   }


   //void node::browse_file_open(property_set & set)
   //{

   //   //::user::interaction* pinteraction = nullptr;
   //   //
   //   //if (::is_set(puiOwner))
   //   //{

   //   //   pinteraction = puiOwner->get_wnd();

   //   //}

   //   bool bOk = false;

   //   //try
   //   //{

   //   //   if (::is_set(pinteraction))
   //   //   {

   //   //      pinteraction->enable_window(false);

   //   //   }

   //   //}
   //   //catch (...)
   //   //{


   //   //}

   //   //try
   //   //{

   //      bool bDisableOleDDE = true;

   //      node()->defer_co_initialize_ex(false, bDisableOleDDE);

   //      comptr < IFileOpenDialog > pfileopen;

   //      HRESULT hr = pfileopen.CoCreateInstance(CLSID_FileOpenDialog, nullptr, CLSCTX_ALL);

   //      if (SUCCEEDED(hr))
   //      {

   //         FILEOPENDIALOGOPTIONS options = 0;

   //         hr = pfileopen->GetOptions(&options);

   //         array < COMDLG_FILTERSPEC > rgSpec;

   //         array < wstring > wstraSpecs;

   //         ::generic::container::copy(wstraSpecs, set["file_filter_specs"].stra());

   //         array < wstring > wstraNames;

   //         ::generic::container::copy(wstraNames, set["file_filter_names"].stra());

   //         rgSpec.set_size(minimum(wstraSpecs.get_size(), wstraNames.get_size()));

   //         for (index i = 0; i < rgSpec.get_size(); i++)
   //         {

   //            rgSpec[i].pszName = wstraNames[i];

   //            rgSpec[i].pszSpec = wstraSpecs[i];

   //            //{ L"CSV files", L"*.csv" },
   //            //{ L"Text files", L"*.txt" },
   //            //{ L"All files", L"*.*" },

   //         }

   //         if (rgSpec.get_size() > 0)
   //         {

   //            pfileopen->SetFileTypes(::u32(rgSpec.get_size()), rgSpec.m_begin);

   //         }

   //         if (set["allow_multi_select"].is_true())
   //         {

   //            options |= FOS_ALLOWMULTISELECT;

   //         }

   //         hr = pfileopen->SetOptions(options);

   //         if (set["default_file_extension"].length() > 0)
   //         {

   //            pfileopen->SetDefaultExtension(wstring(set["default_file_extension"]));

   //         }

   //         if (set["file_name"].length() > 0)
   //         {

   //            pfileopen->SetFileName(wstring(set["file_name"]));

   //         }

   //         if (set["folder"].length() > 0)
   //         {

   //            wstring wstr(set["folder"]);

   //            comptr < IShellItem > psi;

   //            hr = SHCreateItemFromParsingName(wstr, nullptr, IID_IShellItem, (void **)&psi);

   //            if (SUCCEEDED(hr))
   //            {

   //               pfileopen->SetFolder(psi);

   //            }

   //         }

   //         //HWND hwndOwner = nullptr;

   //         //if (::is_set(pinteraction))
   //         //{

   //         //   hwndOwner = pinteraction->get_handle();

   //         //}

   //         // Show the Save dialog box.
   //         //hr = pfileopen->Show(hwndOwner);
   //         hr = pfileopen->Show(nullptr);

   //         if (SUCCEEDED(hr))
   //         {

   //            if (options & FOS_ALLOWMULTISELECT)
   //            {

   //               comptr < IShellItemArray > pitema;

   //               hr = pfileopen->GetResults(&pitema);

   //               if (SUCCEEDED(hr))
   //               {

   //                  DWORD dwNumItems = 0; // number of items in multiple selection

   //                  hr = pitema->GetCount(&dwNumItems);  // get number of selected items

   //                  auto & straDest = set["file_name"].string_array_reference();

   //                  // Loop through IShellItemArray and construct string for display
   //                  for (u32 i = 0; i < dwNumItems; i++)
   //                  {
   //                     comptr < IShellItem > pitem;

   //                     hr = pitema->GetItemAt(i, &pitem); // get a selected item from the IShellItemArray

   //                     if (SUCCEEDED(hr))
   //                     {

   //                        ::cotaskptr < PWSTR > pwszFilePath;

   //                        hr = pitem->GetDisplayName(SIGDN_FILESYSPATH, &pwszFilePath);

   //                        // Display the file name to the user.
   //                        if (SUCCEEDED(hr))
   //                        {

   //                           string strPath((PWSTR)pwszFilePath);

   //                           straDest.add(strPath);

   //                           bOk = true;

   //                        }

   //                     }

   //                  }

   //               }

   //            }
   //            else
   //            {

   //               // Get the file name from the dialog box.
   //               comptr < IShellItem > pitem;

   //               hr = pfileopen->GetResult(&pitem);

   //               if (SUCCEEDED(hr))
   //               {

   //                  ::cotaskptr < PWSTR > pwszFilePath;

   //                  hr = pitem->GetDisplayName(SIGDN_FILESYSPATH, &pwszFilePath);

   //                  // Display the file name to the user.
   //                  if (SUCCEEDED(hr))
   //                  {

   //                     set["file_name"] = string((PWSTR)pwszFilePath);

   //                     bOk = true;

   //                  }

   //               }

   //            }

   //         }

   //      }

   //   //}
   //   //catch (...)
   //   //{

   //   //}

   //   //try
   //   //{

   //   //   if (::is_set(pinteraction))
   //   //   {

   //   //      pinteraction->enable_window();

   //   //      pinteraction->order_top();

   //   //      pinteraction->display(e_display_normal, XXXXe_activation_set_foreground);

   //   //      pinteraction->set_need_redraw();

   //   //      pinteraction->post_redraw();

   //   //   }

   //   //}
   //   //catch (...)
   //   //{

   //   //}

   //   //return bOk;

   //}


   //void node::browse_file_save(property_set & set)
   //{

   //   //::user::interaction* pinteraction = puiOwner->get_wnd();

   //   bool bOk = false;

   //   //try
   //   //{

   //   //   pinteraction->enable_window(false);

   //   //}
   //   //catch (...)
   //   //{

   //   //}

   //   //try
   //   //{

   //   node()->defer_co_initialize_ex(false);

   //      comptr < IFileSaveDialog > pfilesave;

   //      // Create the FileSaveDialog object.
   //      HRESULT hr = pfilesave.CoCreateInstance(CLSID_FileSaveDialog, nullptr, CLSCTX_ALL);

   //      if (SUCCEEDED(hr))
   //      {

   //         //COMDLG_FILTERSPEC rgSpec[] =
   //         //{
   //         // { L"CSV files", L"*.csv" },
   //         // { L"Text files", L"*.txt" },
   //         // { L"All files", L"*.*" },
   //         //};

   //         //pFileSave->SetFileTypes(3, rgSpec);



   //         //pFileSave->SetFileName(L"Twitter Automator Export");

   //         array < COMDLG_FILTERSPEC > rgSpec;

   //         array < wstring > wstraSpecs;

   //         ::generic::container::copy(wstraSpecs, set["file_filter_specs"].stra());

   //         array < wstring > wstraNames;

   //         ::generic::container::copy(wstraNames, set["file_filter_names"].stra());

   //         rgSpec.set_size(minimum(wstraSpecs.get_size(), wstraNames.get_size()));

   //         for (index i = 0; i < rgSpec.get_size(); i++)
   //         {

   //            rgSpec[i].pszName = wstraNames[i];

   //            rgSpec[i].pszSpec = wstraSpecs[i];

   //            //{ L"CSV files", L"*.csv" },
   //            //{ L"Text files", L"*.txt" },
   //            //{ L"All files", L"*.*" },

   //         }

   //         if (rgSpec.get_size() > 0)
   //         {

   //            pfilesave->SetFileTypes(::u32 (rgSpec.get_size()), rgSpec.m_begin);

   //         }

   //         if (set["default_file_extension"].length() > 0)
   //         {

   //            pfilesave->SetDefaultExtension(wstring(set["default_file_extension"]));

   //         }

   //         if (set["file_name"].length() > 0)
   //         {

   //            pfilesave->SetFileName(wstring(set["file_name"]));

   //         }

   //         if (set["folder"].length() > 0)
   //         {

   //            wstring wstr(set["folder"]);

   //            comptr < IShellItem > psi;

   //            hr = SHCreateItemFromParsingName(wstr, nullptr, IID_IShellItem, (void **)&psi);

   //            if (SUCCEEDED(hr))
   //            {

   //               pfilesave->SetFolder(psi);

   //            }

   //         }

   //         // Show the Save dialog box.
   //         hr = pfilesave->Show(nullptr);

   //         if (SUCCEEDED(hr))
   //         {

   //            // Get the file name from the dialog box.
   //            comptr < IShellItem > pitem;

   //            hr = pfilesave->GetResult(&pitem);

   //            if (SUCCEEDED(hr))
   //            {

   //               ::cotaskptr < PWSTR > pwszFilePath;

   //               hr = pitem->GetDisplayName(SIGDN_FILESYSPATH, &pwszFilePath);

   //               // Display the file name to the user.
   //               if (SUCCEEDED(hr))
   //               {

   //                  set["file_name"] = string(pwszFilePath.m_p);

   //                   bOk = true;

   //               }

   //            }

   //         }

   //      }

   //   //}
   //   //catch (...)
   //   //{

   //   //}

   //   //try
   //   //{

   //   //   pinteraction->enable_window();

   //   //   pinteraction->order_top();

   //   //   pinteraction->display(e_display_normal, XXXXe_activation_set_foreground);

   //   //   pinteraction->set_need_redraw();

   //   //   pinteraction->post_redraw();

   //   //}
   //   //catch (...)
   //   //{

   //   //}

   //   //return bOk;

   //}



//   void node::browse_folder( property_set & set)
//   {
//
//      //::user::interaction* pinteraction = puiOwner->get_wnd();
//
//      bool bOk = false;
//
//      //try
//      //{
//
//      //   pinteraction->enable_window(false);
//
//      //}
//      //catch (...)
//      //{
//
//
//      //}
//
//      //try
//      //{
//
//      node()->defer_co_initialize_ex(false);
//
//         comptr < IFileOpenDialog > pfileopen;
//
//         // Create the FileOpenDialog object.
//         HRESULT hr = pfileopen.CoCreateInstance(CLSID_FileOpenDialog, nullptr, CLSCTX_ALL);
//
//         if (SUCCEEDED(hr))
//         {
//
//            if (set["folder"].length() > 0)
//            {
//
//               wstring wstr(set["folder"]);
//
//               comptr < IShellItem > psi;
//
//               hr = SHCreateItemFromParsingName(wstr, nullptr, IID_IShellItem, (void **)&psi);
//
//               if (SUCCEEDED(hr))
//               {
//
//                  pfileopen->SetFolder(psi);
//
//               }
//
//            }
//
//            pfileopen->SetOptions(FOS_PICKFOLDERS);
//
//            // Show the Open dialog box.
//            hr = pfileopen->Show(nullptr);
//
//            if (SUCCEEDED(hr))
//            {
//
//               // Get the file name from the dialog box.
//               comptr < IShellItem > pitem;
//
//               hr = pfileopen->GetResult(&pitem);
//
//               if (SUCCEEDED(hr))
//               {
//
//                  ::cotaskptr < PWSTR > pwszFilePath;
//
//                  hr = pitem->GetDisplayName(SIGDN_FILESYSPATH, &pwszFilePath);
//
//                  // Display the file name to the user.
//                  if (SUCCEEDED(hr))
//                  {
//
//                     set["folder"] = string((PWSTR) pwszFilePath);
//
//                     bOk = true;
//
//                  }
//
//               }
//
//            }
//
//         }
//
//      //}
//      //catch (...)
//      //{
//
//      //}
//
//      //try
//      //{
//
//      //   pinteraction->enable_window();
//
//      //   pinteraction->order_top();
//
//      //   pinteraction->display(e_display_normal, XXXXe_activation_set_foreground);
//
//      //   pinteraction->set_need_redraw();
//
//      //   pinteraction->post_redraw();
//
//
//      //}
//      //catch (...)
//      //{
//
//
//      //}
//
////      return bOk;
//
//   }


   //void node::browse_file_or_folder(property_set & set)
   //{

   //   //::user::interaction* pinteraction = puiOwner->get_wnd();

   //   bool bOk = false;

   //   //try
   //   //{

   //   //   pinteraction->enable_window(false);

   //   //}
   //   //catch (...)
   //   //{


   //   //}

   //   //try
   //   //{

   //   node()->defer_co_initialize_ex(false);

   //      comptr < IFileOpenDialog > pfileopen;

   //      // Create the FileOpenDialog object.
   //      HRESULT hr = pfileopen.CoCreateInstance(CLSID_FileOpenDialog, nullptr, CLSCTX_ALL);

   //      if (SUCCEEDED(hr))
   //      {

   //         if (set["folder"].length() > 0)
   //         {

   //            wstring wstr(set["folder"]);

   //            comptr < IShellItem > psi;

   //            hr = SHCreateItemFromParsingName(wstr, nullptr, IID_IShellItem, (void **)&psi);

   //            if (SUCCEEDED(hr))
   //            {

   //               pfileopen->SetFolder(psi);

   //            }

   //         }

   //         pfileopen->SetOptions(FOS_PATHMUSTEXIST | FOS_PICKFOLDERS);

   //         // Show the Open dialog box.
   //         hr = pfileopen->Show(nullptr);

   //         if (SUCCEEDED(hr))
   //         {

   //            // Get the file name from the dialog box.
   //            comptr < IShellItem > pitem;

   //            hr = pfileopen->GetResult(&pitem);

   //            if (SUCCEEDED(hr))
   //            {

   //               ::cotaskptr < PWSTR > pwszFilePath;

   //               hr = pitem->GetDisplayName(SIGDN_FILESYSPATH, &pwszFilePath);

   //               // Display the file name to the user.
   //               if (SUCCEEDED(hr))
   //               {

   //                  set["path"] = string((PWSTR)pwszFilePath);

   //                  bOk = true;

   //               }

   //            }

   //         }

   //      }

   //   //}
   //   //catch (...)
   //   //{

   //   //}

   //   //try
   //   //{

   //   //   pinteraction->enable_window();

   //   //   pinteraction->order_top();

   //   //   pinteraction->display(e_display_normal, XXX_activation_set_foreground);

   //   //   pinteraction->set_need_redraw();

   //   //   pinteraction->post_redraw();

   //   //}
   //   //catch (...)
   //   //{


   //   //}

   //   //return bOk;


   //}


   /*void node::list_process(::file::path_array & patha, ::process_identifier_array & uaPid)
   {

      ASSERT(sizeof(::u32) == sizeof(u32));

      uaPid = this->processes_identifiers();

      patha.set_size(uaPid.get_count());

      for(index i = 0; i < uaPid.get_count(); i++)
      {

         patha[i] = process_identifier_module_path(uaPid[i]);

      }

   }
   */


   void node::broadcast_environment_variable_change()
   {

      ::SendNotifyMessageA(HWND_BROADCAST, WM_SETTINGCHANGE, 0, (LPARAM)"Environment");

      //return ::success;

   }



} // namespace windows



