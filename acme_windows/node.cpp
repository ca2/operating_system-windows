#include "framework.h"
#include "acme/platform/node.h"
//#include "acme/node/windows/registry.h"
#include "node.h"
#include "acme/filesystem/filesystem/acme_dir.h"


namespace windows
{


   namespace acme
   {


      node::node()
      {


      }


      node::~node()
      {


      }


      ::e_status node::initialize_matter(::matter* pmatter)
      {

         auto estatus = ::matter::initialize_matter(pmatter);

         if (!estatus)
         {

            return estatus;

         }

         return estatus;

      }

      //   string node::get_user_name()
      //   {
      //
      //      WCHAR wsz[1024];
      //
      //      DWORD dwSize = sizeof(wsz) / sizeof(WCHAR);
      //
      //      ::GetUserNameW(wsz, &dwSize);
      //
      //      return string(wsz);
      //
      //   }
      //#include "aura/os/windows/_c.h"
      //
      //
      //   bool node::_os_calc_app_dark_mode()
      //   {
      //
      //      try
      //      {
      //
      //         ::windows::registry::key key;
      //
      //         key.open(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Themes\\Personalize");
      //
      //         ::u32 dw;
      //
      //         auto estatus = key._get("AppsUseLightTheme", dw);
      //
      //         if (::failed(estatus))
      //         {
      //
      //            estatus = key._get("SystemUseLightTheme", dw);
      //
      //            if (::failed(estatus))
      //            {
      //
      //               return false;
      //
      //            }
      //
      //         }
      //
      //         return dw == 0;
      //
      //      }
      //      catch (...)
      //      {
      //
      //         return false;
      //
      //      }
      //
      //   }
      //
      //
      //   bool node::_os_calc_system_dark_mode()
      //   {
      //
      //      try
      //      {
      //
      //         ::windows::registry::key key;
      //
      //         key.open(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Themes\\Personalize");
      //
      //         ::u32 dw;
      //
      //         auto estatus = key._get("SystemUseLightTheme", dw);
      //
      //         if (::failed(estatus))
      //         {
      //
      //            estatus = key._get("AppsUseLightTheme", dw);
      //
      //            if (::failed(estatus))
      //            {
      //
      //               return false;
      //
      //            }
      //
      //         }
      //
      //         return dw == 0;
      //
      //      }
      //      catch (...)
      //      {
      //
      //         return false;
      //
      //      }
      //
      //   }
      //
      //
      //   ::color::color node::get_default_color(::u64 u)
      //   {
      //
      //      switch (u)
      //      {
      //      case COLOR_3DFACE:
      //         return argb(127, 192, 192, 184);
      //      case COLOR_WINDOW:
      //         return argb(127, 255, 255, 255);
      //      case COLOR_3DLIGHT:
      //         return argb(127, 218, 218, 210);
      //      case COLOR_3DHIGHLIGHT:
      //         return argb(127, 238, 238, 230);
      //      case COLOR_3DSHADOW:
      //         return argb(127, 138, 138, 130);
      //      case COLOR_3DDKSHADOW:
      //         return argb(127, 90, 90, 80);
      //      default:
      //         break;
      //      }
      //
      //      return argb(127, 0, 0, 0);
      //
      //   }
      //
      //   
      //   void node::set_console_colors(::u32 dwScreenColors, ::u32 dwPopupColors, ::u32 dwWindowAlpha)
      //   {
      //
      //      ::windows::registry::key key(HKEY_CURRENT_USER, "Console", true);
      //
      //      key._set("ScreenColors", dwScreenColors);
      //      key._set("PopupColors", dwPopupColors);
      //      key._set("WindowAlpha", dwWindowAlpha);
      //
      //   }
      //
      //
      //
      //   ::e_status node::set_system_dark_mode1(bool bSet)
      //   {
      //
      //      ::windows::registry::key key(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Themes\\Personalize", true);
      //
      //      ::u32 dwSystemUseLightTheme;
      //      if (bSet)
      //      {
      //         dwSystemUseLightTheme = 0;
      //      }
      //      else
      //      {
      //         dwSystemUseLightTheme = 1;
      //      }
      //
      //      key._set("SystemUsesLightTheme", dwSystemUseLightTheme);
      //      return ::success;
      //
      //   }
      //
      //
      //   ::e_status node::set_app_dark_mode1(bool bSet)
      //   {
      //
      //      ::windows::registry::key key(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Themes\\Personalize", true);
      //
      //      ::u32 dwAppsUseLightTheme;
      //      if (bSet)
      //      {
      //         dwAppsUseLightTheme = 0;
      //      }
      //      else
      //      {
      //         dwAppsUseLightTheme = 1;
      //      }
      //
      //      key._set("AppsUseLightTheme", dwAppsUseLightTheme);
      //
      //      return ::success;
      //
      //   }
      //
      //   
      //   double node::get_time_zone()
      //   {
      //
      //      double dTimeZone = 0.;
      //
      //#ifdef WINDOWS
      //      {
      //         //time_t t = time(nullptr);
      //
      //         //struct tm *p = localtime(&t);
      //
      //         DYNAMIC_TIME_ZONE_INFORMATION i = {};
      //
      //         ::u32 dw = GetDynamicTimeZoneInformation(&i);
      //
      //         if (dw == TIME_ZONE_ID_STANDARD)
      //         {
      //
      //            dTimeZone = -((double)(i.Bias + i.StandardBias) / 60.0);
      //
      //         }
      //         else if (dw == TIME_ZONE_ID_DAYLIGHT)
      //         {
      //
      //            dTimeZone = -((double)(i.Bias + i.DaylightBias) / 60.0);
      //
      //         }
      //         else
      //         {
      //
      //            dTimeZone = -((double)i.Bias / 60.0);
      //
      //         }
      //
      //      }
      //#else
      //      {
      //
      //         time_t t = time(nullptr);
      //
      //         struct tm lt = { 0 };
      //
      //         localtime_r(&t, &lt);
      //
      //         //printf("Offset to GMT is %lds.\n", lt.tm_gmtoff);
      //
      //         //printf("The time zone is '%s'.\n", lt.tm_zone);
      //
      //         dTimeZone = +((double)lt.tm_gmtoff / (60.0 * 60.0));
      //
      //      }
      //#endif
      //
      //      return dTimeZone;
      //
      //   }
      //
      //
      //   ::e_status node::open_folder(::file::path & pathFolder)
      //   {
      //
      //      wstring wstrFolder(pathFolder);
      //
      //      int i = (int) (iptr) ::ShellExecuteW(nullptr, L"open", wstrFolder, nullptr, nullptr, SW_NORMAL);
      //
      //      if (i < 32)
      //      {
      //
      //         switch (i)
      //         {
      //         case 0:
      //            //The operating system is out of memory or resources.
      //            return error_no_memory;
      //         case ERROR_FILE_NOT_FOUND:
      //            return error_file_not_found;
      //            //The specified file was not found.
      //         case ERROR_PATH_NOT_FOUND:
      //            return error_path_not_found;
      //            //            The specified path was not found.
      //         case          ERROR_BAD_FORMAT:
      //            return error_bad_format;
      //            //The.exe file is invalid(non - Win32.exe or error in.exe image).
      //            //case SE_ERR_ACCESSDENIED:
      //            //         return error_access_denied;
      //            ////The operating system denied access to the specified file.
      //            //SE_ERR_ASSOCINCOMPLETE
      //            //The file name association is incomplete or invalid.
      //            //SE_ERR_DDEBUSY
      //            //The DDE transaction could not be completed because other DDE transactions were being processed.
      //            //SE_ERR_DDEFAIL
      //            //The DDE transaction failed.
      //            //SE_ERR_DDETIMEOUT
      //            //The DDE transaction could not be completed because the request timed out.
      //            //SE_ERR_DLLNOTFOUND
      //            //The specified DLL was not found.
      //            //SE_ERR_FNF
      //            //The specified file was not found.
      //            //SE_ERR_NOASSOC
      //            //There is no application associated with the given file name extension.This error will also be returned if you attempt to print a file that is not printable.
      //            //SE_ERR_OOM
      //            //There was not enough memory to complete the operation.
      //            //SE_ERR_PNF
      //            //The specified path was not found.
      //            //SE_ERR_SHARE
      //            //A sharing violation occurred.*/
      //         default:
      //            return error_failed;
      //         }
      //
      //      }
      //
      //      return ::success;
      //
      //   }
      //
      //
      //   ::e_status node::register_dll(const ::file::path & pathDll)
      //   {
      //
      //
      //      string strPathDll;
      //         
      //      //#ifdef _DEBUG
      //         
      //      strPathDll = pathDll;
      //         
      //      //#else
      //      //
      //      //   strPathDll = m_psystem->m_pacmedir->matter() / "time" / process_platform_dir_name() /"stage/_desk_tb.dll";
      //      //
      //      //#endif
      //         
      //      string strParam;
      //         
      //      strParam = "/s \"" + strPathDll + "\"";
      //         
      //      //wstring wstrParam(strParam);
      //         
      //      //STARTUPINFOW si = {};
      //         
      //      //si.cb = sizeof(si);
      //         
      //      //si.wShowWindow = SW_HIDE;
      //         
      //      //PROCESS_INFORMATION pi = {};
      //         
      //      WCHAR wszSystem[2048];
      //         
      //      GetSystemDirectoryW(wszSystem, sizeof(wszSystem) / sizeof(WCHAR));
      //         
      //      wstring wstrSystem(wszSystem);
      //         
      //      ::file::path path(wstrSystem);
      //         
      //      path /= "regsvr32.exe";
      //         
      //      property_set set;
      //         
      //      set["privileged"] = true;
      //         
      //      if (!call_sync(path, strParam, path.folder(), ::e_display_none, 3_min, set))
      //      {
      //         
      //         return false;
      //         
      //      }
      //         
      //      //if (CreateProcessW(wstrPath, wstrParam, nullptr, nullptr, false, 0, nullptr, wstrSystem, &si, &pi))
      //      //{
      //         
      //      //   output_debug_string("created");
      //         
      //      //}
      //      //else
      //      //{
      //         
      //      //   output_debug_string("not created");
      //         
      //      //}
      //         
      //      //CloseHandle(pi.hProcess);
      //         
      //      //CloseHandle(pi.hthread);
      //         
      //      return true;
      //         
      //   }
      //
      //
      //   ::e_status node::start()
      //   {
      //
      //      auto estatus = m_psystem->m_papexsystem->m_papex->thread_initialize(m_psystem->m_papexsystem);
      //
      //      if (!estatus)
      //      {
      //
      //         return estatus;
      //
      //      }
      //
      //      estatus = m_psystem->on_start();
      //
      //      if (!estatus)
      //      {
      //
      //         return estatus;
      //
      //      }
      //
      //      estatus = m_psystem->main();
      //
      //      if (!estatus)
      //      {
      //
      //         return estatus;
      //
      //      }
      //
      //      estatus = m_psystem->inline_term();
      //
      //      if (!estatus)
      //      {
      //
      //         return estatus;
      //
      //      }
      //
      //      return estatus;
      //
      //
      //   }
      //
      //
      //   ::e_status node::get_firefox_installation_info(string& strPathToExe, string& strInstallDirectory)
      //   {
      //
      //#ifdef WINDOWS_DESKTOP
      //
      //      try
      //      {
      //
      //         ::windows::registry::key key(HKEY_LOCAL_MACHINE, "SOFTWARE\\Mozilla\\Mozilla Firefox");
      //
      //         string strCurrentVersion;
      //
      //         key.get("CurrentVersion", strCurrentVersion);
      //
      //         key.open(HKEY_LOCAL_MACHINE, "SOFTWARE\\Mozilla\\Mozilla Firefox\\" + strCurrentVersion + "\\Main");
      //
      //         key.get("PathToExe", strPathToExe);
      //
      //         key.get("Install Directory", strInstallDirectory);
      //
      //      }
      //      catch (const ::e_status& estatus)
      //      {
      //
      //         return estatus;
      //
      //      }
      //
      //      return ::success;
      //
      //#else
      //
      //      return ::error_failed;
      //
      //#endif
      //
      //   }
      //
      //
      //   ::e_status node::_001InitializeShellOpen()
      //   {
      //
      //      //ASSERT(m_atomApp == nullptr && m_atomSystemTopic == nullptr); // do once
      //
      //      //m_atomApp            = ::GlobalAddAtomW(::str::international::utf8_to_unicode(m_strAppName));
      //
      //      //m_atomSystemTopic    = ::GlobalAddAtomW(L"system");
      //
      //      return ::success;
      //
      //   }
      //
      //
      //   ::e_status node::process_init()
      //   {
      //
      //      
      //
      //      defer_initialize_winsock();
      //      return success;
      //
      //   }
      //
      //
      //   string node::veriwell_multimedia_music_midi_get_default_library_name()
      //   {
      //
      //      return "music_midi_mmsystem";
      //
      //   }
      //
      //
      //   string node::multimedia_audio_mixer_get_default_library_name()
      //   {
      //
      //      return "audio_mixer_mmsystem";
      //
      //   }
      //
      //
      //   string node::multimedia_audio_get_default_library_name()
      //   {
      //
      //      string str;
      //
      //      if (file_exists(m_psystem->m_pacmedir->system() / "config\\system\\audio.txt"))
      //      {
      //
      //         str = file_as_string(m_psystem->m_pacmedir->system() / "config\\system\\audio.txt");
      //
      //      }
      //      else
      //      {
      //
      //         ::file::path strPath;
      //
      //         strPath = m_psystem->m_pacmedir->appdata() / "audio.txt";
      //
      //         str = file_as_string(strPath);
      //
      //      }
      //
      //      if (str.has_char())
      //         return "audio_" + str;
      //      else
      //         return "audio_mmsystem";
      //
      //   }
      //
      //
         // Twitter Automator and Denis Lakic and UpWork contribution
      // enzymes: Liveedu.tv, Twitch.tv and Mixer.com streamers and viewers
      // Mummi and bilbo!!
      // create call to :
      void node::install_crash_dump_reporting(const string& strModuleNameWithTheExeExtension)
      {

         ::windows::registry::key k;

         string strKey = "SOFTWARE\\Microsoft\\Windows\\Windows Error Reporting\\LocalDumps\\" + strModuleNameWithTheExeExtension;

         if (k._open(HKEY_LOCAL_MACHINE, strKey, true))
         {
            ::file::path str = m_psystem->m_pacmedir->system() / "CrashDumps" / strModuleNameWithTheExeExtension;
            wstring wstr = str;
            RegSetValueExW(k.m_hkey, L"DumpFolder", 0, REG_EXPAND_SZ, (byte*)wstr.c_str(), ::u32((wcslen(wstr) + 1) * sizeof(wchar_t)));
            ::u32 dw = 10;
            RegSetValueExW(k.m_hkey, L"DumpCount", 0, REG_DWORD, (byte*)&dw, sizeof(dw));
            dw = 2;
            RegSetValueExW(k.m_hkey, L"DumpType", 0, REG_DWORD, (byte*)&dw, sizeof(dw));

         }

         output_debug_string("test01");

      }
      //
      //
      //   int g_iMemoryCountersStartable = 0;
      //
      //   bool node::memcnts()
      //   {
      //
      //      if (g_iMemoryCountersStartable && g_iMemoryCounters < 0)
      //      {
      //
      //         g_iMemoryCounters = file_exists(m_psystem->m_pacmedir->config() / "system/memory_counters.txt") ? 1 : 0;
      //
      //         if (g_iMemoryCounters)
      //         {
      //
      //            g_pmutexMemoryCounters = new ::mutex(e_create_new, false, "Global\\ca2_memory_counters");
      //
      //         }
      //
      //      }
      //
      //      return g_iMemoryCountersStartable && g_iMemoryCounters;
      //
      //   }
      //
      //
      //   ::file::path* g_pMemoryCounters = nullptr;
      //
      //
      //   CLASS_DCL_ACME::file::path node::memcnts_base_path()
      //   {
      //
      //      if (g_iMemoryCountersStartable && g_pMemoryCounters == nullptr)
      //      {
      //
      //         g_pMemoryCounters = new ::file::path();
      //
      //#if defined(_UWP)
      //
      //         string strBasePath = m_psystem->m_pacmedir->system() / "memory_counters";
      //
      //#else
      //
      //         ::file::path strModule = module_path_from_pid(getpid());
      //
      //         string strBasePath = m_psystem->m_pacmedir->system() / "memory_counters" / strModule.title() / __str(getpid());
      //
      //#endif
      //
      //         * g_pMemoryCounters = strBasePath;
      //
      //      }
      //
      //      return *g_pMemoryCounters;
      //
      //   }
      //
      //


      ::e_status node::datetime_to_filetime(::filetime_t* pfiletime, const ::datetime::time& time)
      {

         SYSTEMTIME sysTime;

         sysTime.wYear = (::u16)time.GetYear();
         sysTime.wMonth = (::u16)time.GetMonth();
         sysTime.wDay = (::u16)time.GetDay();
         sysTime.wHour = (::u16)time.GetHour();
         sysTime.wMinute = (::u16)time.GetMinute();
         sysTime.wSecond = (::u16)time.GetSecond();
         sysTime.wMilliseconds = 0;

         // convert system time to local file time
         FILETIME localTime;

         DWORD dwLastError = ::GetLastError();

         if (!SystemTimeToFileTime((LPSYSTEMTIME)&sysTime, &localTime))
         {

            DWORD dwLastError = ::GetLastError();

            return last_error_to_status(dwLastError);

         }

         // convert local file time to UTC file time
         if (!LocalFileTimeToFileTime(&localTime, (FILETIME*)pfiletime))
         {

            DWORD dwLastError = ::GetLastError();

            return last_error_to_status(dwLastError);

         }

         return ::success;

      }


      ::e_status node::last_error_to_status(DWORD dwLastError)
      {

         if (dwLastError == 0)
         {

            return ::success;

         }
         else
         {

            return error_failed;

         }


      }


      string node::audio_get_default_library_name()
      {

         return "audio_mmsystem";

      }


      ::e_status node::on_start_system()
      {

         auto psystem = m_psystem;

         auto estatus = psystem->post_initial_request();

         if (!estatus)
         {

            return estatus;

         }

         return estatus;

      }


   } // namespace acme


} // namespace windows



