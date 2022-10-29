#include "framework.h"
#include "node.h"
#include "acme/parallelization/install_mutex.h"
#include "acme_directory.h"
#include "acme_file.h"
#include "registry.h"
#include "process.h"
#include <shellapi.h>
#include <TlHelp32.h>


CLASS_DECL_ACME_WINDOWS void call_async(const char * pszPath, const char * pszParam, const char * pszDir, ::e_display edisplay, bool bPrivileged, unsigned int * puiPid);


namespace acme_windows
{


   node::node()
   {

      //::windows::callstack::s_pcriticalsection = new critical_section();

   }


   node::~node()
   {

      //#ifdef WINDOWS
      //
      //         ::acme::del(::windows::callstack::s_pcriticalsection);
      //
      //#endif

   }


   void node::initialize(::particle * pparticle)
   {

      ::acme::node::initialize(pobject);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      windows_registry_initialize();

      //return estatus;

   }


   void node::call_async(const ::string & strPath, const ::string & strParam, const ::string & strDir, ::e_display edisplay, bool bPrivileged, unsigned int * puiPid)
   {

      /*auto estatus =*/ ::call_async(strPath, strParam, strDir, edisplay, bPrivileged, puiPid);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //return estatus;

   }



   void node::shell_open(const ::file::path & pathFile, const ::string & strParams, const ::file::path & pathFolder)
   {

      wstring wstrFile(pathFile);

      wstring wstrParams(strParams);

      wstring wstrFolder(pathFolder);

      int iRet = (int)(iptr) ::ShellExecuteW(nullptr, L"open", wstrFile, wstrParams, wstrFolder, SW_RESTORE);

   }


   bool node::win32_registry_windows_dark_mode_for_app()
   {

      try
      {

         ::acme_windows::registry::key key;

         key.open(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Themes\\Personalize");

         ::u32 dw;

         /*auto estatus =*/ key._get("AppsUseLightTheme", dw);

         //if (::failed(estatus))
         //{

         /*estatus =*/ key._get("SystemUseLightTheme", dw);

         //   if (::failed(estatus))
         //   {

         //      return false;

         //   }

         //}

         return dw == 0;

      }
      catch (...)
      {

         return false;

      }

   }


   bool node::win32_registry_windows_dark_mode_for_system()
   {

      try
      {

         ::acme_windows::registry::key key;

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


   bool node::win32_registry_windows_darkness()
   {

      return win32_registry_windows_dark_mode_for_app() || win32_registry_windows_dark_mode_for_system();

   }


   ::color::color node::reinterpreted_windows_darkness_background_color()
   {

      if (win32_registry_windows_darkness())
      {

         return ::color::black;

      }

      return ::color::white;

   }


   void node::fetch_user_color()
   {

      //DWORD dwBackgroundWindowColor = ::GetSysColor(COLOR_WINDOW);

      //auto colorWindowBackground = argb(255, GetRValue(dwBackgroundWindowColor), GetGValue(dwBackgroundWindowColor), GetBValue(dwBackgroundWindowColor));

      auto colorWindowBackground = reinterpreted_windows_darkness_background_color();

      string str;

      str.format("\n\n\nWindow Background Color rgb(%d,%d,%d)\n\n", colorWindowBackground.red, colorWindowBackground.green, colorWindowBackground.blue);

      ::output_debug_string(str);

      background_color(colorWindowBackground);

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
   //         ::acme_windows::registry::key key;
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
   //         ::acme_windows::registry::key key;
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
   //         return argb(127, 192, 192, 200);
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
   //      ::acme_windows::registry::key key(HKEY_CURRENT_USER, "Console", true);
   //
   //      key._set("ScreenColors", dwScreenColors);
   //      key._set("PopupColors", dwPopupColors);
   //      key._set("WindowAlpha", dwWindowAlpha);
   //
   //   }
   //
   //
   //
   //   void node::set_system_dark_mode1(bool bSet)
   //   {
   //
   //      ::acme_windows::registry::key key(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Themes\\Personalize", true);
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
   //   void node::set_app_dark_mode1(bool bSet)
   //   {
   //
   //      ::acme_windows::registry::key key(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Themes\\Personalize", true);
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
   //   void node::open_folder(::file::path & pathFolder)
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
   //   void node::register_dll(const ::file::path & pathDll)
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
   //      //   strPathDll = acmedirectory()->matter() / "time" / process_platform_name() /"stage/_desk_tb.dll";
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
   //   void node::start()
   //   {
   //
   //      auto estatus = acmesystem()->m_papexsystem->m_papex->thread_initialize(acmesystem()->m_papexsystem);
   //
   //      if (!estatus)
   //      {
   //
   //         return estatus;
   //
   //      }
   //
   //      estatus = acmesystem()->on_start();
   //
   //      if (!estatus)
   //      {
   //
   //         return estatus;
   //
   //      }
   //
   //      estatus = acmesystem()->main();
   //
   //      if (!estatus)
   //      {
   //
   //         return estatus;
   //
   //      }
   //
   //      estatus = acmesystem()->inline_term();
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
   //   void node::get_firefox_installation_info(string& strPathToExe, string& strInstallDirectory)
   //   {
   //
   //#ifdef WINDOWS_DESKTOP
   //
   //      try
   //      {
   //
   //         ::acme_windows::registry::key key(HKEY_LOCAL_MACHINE, "SOFTWARE\\Mozilla\\Mozilla Firefox");
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
   //      catch (const ::e_status & estatus)
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
   //   void node::_001InitializeShellOpen()
   //   {
   //
   //      //ASSERT(m_atomApp == nullptr && m_atomSystemTopic == nullptr); // do once
   //
   //      //m_atomApp            = ::GlobalAddAtomW(utf8_to_unicode(m_strAppName));
   //
   //      //m_atomSystemTopic    = ::GlobalAddAtomW(L"system");
   //
   //      return ::success;
   //
   //   }
   //
   //
   //   void node::process_init()
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
   //      if (acmefile()->exists(acmedirectory()->system() / "config\\system\\audio.txt"))
   //      {
   //
   //         str = acmefile()->as_string(acmedirectory()->system() / "config\\system\\audio.txt");
   //
   //      }
   //      else
   //      {
   //
   //         ::file::path strPath;
   //
   //         strPath = acmedirectory()->appdata() / "audio.txt";
   //
   //         str = acmefile()->as_string(strPath);
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
   void node::install_crash_dump_reporting(const string & strModuleNameWithTheExeExtension)
   {

      ::acme_windows::registry::key k;

      string strKey = "SOFTWARE\\Microsoft\\Windows\\Windows Error Reporting\\LocalDumps\\" + strModuleNameWithTheExeExtension;

      if (k._open(HKEY_LOCAL_MACHINE, strKey, true))
      {
         ::file::path str = acmedirectory()->system() / "CrashDumps" / strModuleNameWithTheExeExtension;
         wstring wstr = str;
         RegSetValueExW(k.m_hkey, L"DumpFolder", 0, REG_EXPAND_SZ, (byte *)wstr.c_str(), ::u32((wcslen(wstr) + 1) * sizeof(wchar_t)));
         ::u32 dw = 10;
         RegSetValueExW(k.m_hkey, L"DumpCount", 0, REG_DWORD, (byte *)&dw, sizeof(dw));
         dw = 2;
         RegSetValueExW(k.m_hkey, L"DumpType", 0, REG_DWORD, (byte *)&dw, sizeof(dw));

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
   //         g_iMemoryCounters = xxxxfile_exists(acmedirectory()->config() / "system/memory_counters.txt") ? 1 : 0;
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
   //         string strBasePath = acmedirectory()->system() / "memory_counters";
   //
   //#else
   //
   //         ::file::path strModule = module_path_from_pid(getpid());
   //
   //         string strBasePath = acmedirectory()->system() / "memory_counters" / strModule.title() / __string(getpid());
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


   //void node::datetime_to_filetime(::file_time_t* pfiletime, const ::earth::time& time)
   //{

   //   SYSTEMTIME sysTime;

   //   sysTime.wYear = (::u16)time.year();
   //   sysTime.wMonth = (::u16)time.month();
   //   sysTime.wDay = (::u16)time.day();
   //   sysTime.wHour = (::u16)time.hour();
   //   sysTime.wMinute = (::u16)time.minute();
   //   sysTime.wSecond = (::u16)time.second();
   //   sysTime.wMilliseconds = 0;

   //   // convert system time to local file time
   //   FILETIME localTime;

   //   DWORD dwLastError = ::GetLastError();

   //   if (!SystemTimeToFileTime((LPSYSTEMTIME)&sysTime, &localTime))
   //   {

   //      DWORD dwLastError = ::GetLastError();

   //      auto estatus = last_error_to_status(dwLastError);

   //      throw ::exception(estatus, "::windows::node::datetime_to_filetime (1)");

   //   }

   //   // convert local file time to UTC file time
   //   if (!LocalFileTimeToFileTime(&localTime, (FILETIME*)pfiletime))
   //   {

   //      DWORD dwLastError = ::GetLastError();

   //      auto estatus = last_error_to_status(dwLastError);

   //      throw ::exception(estatus, "::windows::node::datetime_to_filetime (2)");

   //   }

   //   //return ::success;

   //}


   ::e_status node::last_error_to_status(DWORD dwLastError)
   {

      if (dwLastError == 0)
      {

         return ::success;

         //return;

      }
      else
      {

         return error_failed;

      }

   }


   ::e_status node::ExitCode_to_status(DWORD dwExitCode)
   {

      if (dwExitCode == 0)
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


   //void node::on_start_system()
   //{

   //   auto psystem = acmesystem();

   //   auto estatus = psystem->post_initial_request();

   //   if (!estatus)
   //   {

   //      return estatus;

   //   }

   //   return estatus;

   //}


   bool node::process_modules(string_array & stra, u32 processID)
   {

      HANDLE hProcess;

      DWORD cbNeeded;

      u32 i;

      hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, false, processID);

      if (nullptr == hProcess)
         return false;

      const i32 iMaxModuleCount = 1024 * 8;

      HMODULE * hMods = new HMODULE[iMaxModuleCount];

      const i32 iImageSize = MAX_PATH * 8;

      wchar_t * szImage = (wchar_t *)::memory_allocate(iImageSize * 2);

      if (EnumProcessModules(hProcess, hMods, sizeof(HMODULE) * iMaxModuleCount, &cbNeeded))
      {

         for (i = 0; i < (cbNeeded / sizeof(HMODULE)); i++)
         {

            if (GetModuleFileNameExW(hProcess, hMods[i], szImage, iImageSize / sizeof(char)))
            {

               stra.add(string(szImage));

            }

         }

      }

      memory_free_debug(szImage, 0);

      delete hMods;

      CloseHandle(hProcess);

      return true;

   }


   bool node::load_modules_diff(string_array & straOld, string_array & straNew, const ::string & pszExceptDir)
   {

      bool bFound;

      HMODULE hmodule;

      ::count iLenExcept;

      if (pszExceptDir != nullptr)
      {

         iLenExcept = ansi_length(pszExceptDir);

      }
      else
      {

         iLenExcept = 0;

      }

      for (i32 i = 0; i < straOld.get_count(); i++)
      {

         bFound = false;

         if (iLenExcept > 0)
         {

            if (ansi_length(straOld[i]) > iLenExcept)
            {

               if (_strnicmp(straOld[i], pszExceptDir, (size_t)iLenExcept) == 0)
               {

                  continue;

               }

            }

         }

         for (i32 j = 0; j < straNew.get_count(); j++)
         {

            if (ansi_compare_ci(straOld[i], straNew[j]) == 0)
            {

               bFound = true;

               break;

            }

         }

         if (!bFound)
         {

            hmodule = nullptr;

            // double check, ensure, that the module has not been already loaded
            // it may happen by loading a missing module that loads dependencies that satisfies straOld modules state.

            if (::GetModuleHandleExA(GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT, straOld[i], &hmodule) == false || hmodule == nullptr)
            {

               try
               {

                  ::LoadLibraryW(wstring(straOld[i]));

               }
               catch (...)
               {

               }

            }

         }

      }

      return true;

   }


   id_array node::module_path_get_pid(const ::string & pszModulePath, bool bModuleNameIsPropertyFormatted)
   {

      ::file::path pathModule(pszModulePath);

      id_array iaPid;

      if (pathModule.is_empty())
      {

         return iaPid;

      }

      ::mutex veri_global_ca2(this, NULL, "Global\\the_veri_global_ca2");

      synchronous_lock lock_the_veri_global_ca2(&veri_global_ca2);

      HANDLE process_snap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

      PROCESSENTRY32 entry;

      DWORD dwError = ::GetLastError();

      if (Process32First(process_snap, &entry) && dwError != ERROR_NO_MORE_FILES)
      {

      repeat_process:

         string strPath;

         strPath = module_path_from_pid(entry.th32ProcessID);

         //::output_debug_string(strPath + "\n");


         if (bModuleNameIsPropertyFormatted)
         {
            if (entry.th32ProcessID != 0 && strPath.compare_ci(pathModule) == 0)
            {

               iaPid.add((::i64)entry.th32ProcessID);

            }
         }
         else
         {
            if (entry.th32ProcessID != 0 && ::file::path(strPath) == pathModule)
            {

               iaPid.add((::i64)entry.th32ProcessID);

            }

         }

         DWORD dwError = ::GetLastError();

         if (Process32Next(process_snap, &entry) && dwError != ERROR_NO_MORE_FILES)
         {

            goto repeat_process;

         }

      }

      ::CloseHandle(process_snap);

      return iaPid;

   }


   string node::module_path_from_pid(u32 pid)
   {

      //HANDLE hModuleSnap = INVALID_HANDLE_VALUE;

      //MODULEENTRY32 me32;

      //hModuleSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, pid);

      //if(hModuleSnap == INVALID_HANDLE_VALUE)
      //{

      //   return "";

      //}

      //me32.dwSize = sizeof(MODULEENTRY32);

      //if(!Module32First(hModuleSnap,&me32))
      //{

      //   CloseHandle(hModuleSnap);           // clean the snapshot matter

      //   return "";

      //}

      //string strName  = solve_relative(me32.szExePath);
      //
      //CloseHandle(hModuleSnap);

      //return strName;



      HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, false, pid);

      if (hProcess == nullptr)
         return "";

      WCHAR path[MAX_PATH * 4];

      string strPath;

      if (GetModuleFileNameExW(hProcess, 0, path, sizeof(path) / sizeof(path[0])))
      {
         strPath = solve_relative(string(path));

      }

      ::CloseHandle(hProcess);

      return strPath;

   }


   // http://stackoverflow.com/questions/4178443/get-the-full-path-from-a-pid-using-delphi
   //function GetPathFromPID(const PID: cardinal): string;
   //::payload
   //hProcess: THandle;
   //path: array[0..MAX_PATH - 1] of char;
   //begin
   //hProcess := OpenProcess(PROCESS_QUERY_INFORMATION or PROCESS_VM_READ,false,PID);
   //if hProcess <> 0 then
   //try
   //if GetModuleFileNameEx(hProcess,0,path,MAX_PATH) = 0 then
   //RaiseLastOSError;
   //result:= path;
   //finally
   //CloseHandle(hProcess)
   //end
   //else
   //RaiseLastOSError;
   //end;


   bool node::is_shared_library_busy(u32 processid, const string_array & stra)
   {

      string_array straSuffix(stra);

      straSuffix.surround("\\");

      return ::acme_windows::predicate_process_module(processid, [&](auto & me32)
         {

            return !straSuffix.suffixes_ci(string(me32.szModule)) && !stra.contains_ci(string(me32.szModule));

         });

   }


   bool node::is_shared_library_busy(const string_array & stra)
   {

      return ::acme_windows::predicate_process([&](auto pid)
         {

            return !is_shared_library_busy(pid, stra);

         });

   }


   bool node::process_contains_module(string & strImage, ::u32 processID, const ::string & pszLibrary)
   {

      HANDLE hProcess;

      DWORD cbNeeded;

      index i;

      hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, false, processID);

      if (nullptr == hProcess)
         return false;

      const i32 iMaxModuleCount = 1024;

      array < HMODULE > hmods;

      hmods.set_size(iMaxModuleCount);

      const i32 iImageSize = MAX_PATH * 8;

      memory mem;

      mem.set_size(iImageSize);

      GetModuleFileNameExW(hProcess, nullptr, (WCHAR *)mem.get_data(), (DWORD)(mem.get_size() / sizeof(WCHAR)));

      strImage = (const wchar_t *)mem.get_data();

      wstring wstrLibrary(pszLibrary);

      bool bFound = false;

      if (EnumProcessModules(hProcess, hmods.get_data(), (DWORD)(hmods.get_size_in_bytes()), &cbNeeded))
      {

         for (i = 0; i < ::index(cbNeeded / sizeof(HMODULE)); i++)
         {

            // Get the full path to the module's file.

            if (GetModuleFileNameExW(hProcess, hmods[i], (WCHAR *)mem.get_data(), (DWORD)(mem.get_size() / sizeof(WCHAR))))
            {

               if (!wide_compare_case_insensitive((const wchar_t *)mem.get_data(), wstrLibrary))
               {

                  bFound = true;

                  break;

               }

            }

         }

      }

      CloseHandle(hProcess);

      return bFound;

   }


   void node::shared_library_process(dword_array & dwa, string_array & straProcesses, const ::string & pszLibrary)
   {

      // Get the list of process identifiers.

      dword_array aProcesses;

      aProcesses.set_size(8192);

      DWORD cbNeeded, cProcesses;

      index i;

      if (!EnumProcesses((DWORD *)aProcesses.get_data(), (DWORD)(aProcesses.get_size_in_bytes()), &cbNeeded))
      {

         return;

      }

      // Calculate how many process identifiers were returned.

      cProcesses = cbNeeded / sizeof(DWORD);

      // Print the name of the modules for each process.

      string strImage;

      for (i = 0; i < ::index(cProcesses); i++)
      {

         if (process_contains_module(strImage, aProcesses[i], pszLibrary))
         {

            straProcesses.add(strImage); // there may processes with different pids but same image

            dwa.add(aProcesses[i]);

         }

      }

   }








   //CLASS_DECL_ACME ::file::path core_app_path(string strAppId)
   //{
   //
   //   ::file::path path = get_last_run_application_path(strAppId);
   //
   //   if (path.has_char())
   //   {
   //
   //      return path;
   //
   //   }
   //
   //   strAppId.replace("-", "_");
   //
   //   strAppId.replace("/", "_");
   //
   //   path = "C:\\acme\\time\\x64\\basis\\" + strAppId + ".exe";
   //
   //   return path;
   //
   //}
   //
   //
   //
   //CLASS_DECL_ACME ::u32 get_current_process_id()
   //{
   //
   //   return ::GetCurrentProcessId();
   //
   //}






   //CLASS_DECL_ACME BOOL LaunchAppIntoDifferentSession(const ::string & pszProcess, const ::string & pszCommand, const ::string & pszDir, STARTUPINFOW* psi, PROCESS_INFORMATION* ppi, int iSession)
   //{
   //   //PROCESS_INFORMATION pi;
   //   //STARTUPINFO si;
   //   BOOL bResult = false;
   //   DWORD dwSessionId, winlogonPid;
   //   HANDLE hUserToken, hUserTokenDup, hPToken, hProcess;
   //   DWORD dwCreationFlags;
   //
   //   // Log the client on to the local computer.
   //
   //   if (iSession < 0)
   //   {
   //      dwSessionId = WTSGetActiveConsoleSessionId();
   //   }
   //   else
   //   {
   //      dwSessionId = iSession;
   //   }
   //
   //   //////////////////////////////////////////
   //   // Find the winlogon process
   //   ////////////////////////////////////////
   //
   //   PROCESSENTRY32W procEntry;
   //
   //   HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
   //   if (hSnap == INVALID_HANDLE_VALUE)
   //   {
   //      return 1;
   //   }
   //
   //   procEntry.dwSize = sizeof(PROCESSENTRY32W);
   //
   //   if (!Process32FirstW(hSnap, &procEntry))
   //   {
   //      return 1;
   //   }
   //
   //   do
   //   {
   //      if (wcsicmp(procEntry.szExeFile,L"winlogon.exe") == 0)
   //      {
   //         // We found a winlogon process...
   //         // make sure it's running in the console session
   //         DWORD winlogonSessId = 0;
   //         HANDLE h = ::OpenProcess(PROCESS_QUERY_INFORMATION, false, procEntry.th32ProcessID);
   //         if (ProcessIdToSessionId(procEntry.th32ProcessID, &winlogonSessId))
   //         {
   //            if (winlogonSessId == dwSessionId)
   //            {
   //               winlogonPid = procEntry.th32ProcessID;
   //               break;
   //
   //            }
   //         }
   //         else
   //         {
   //            DWORD dwLastError = GetLastError();
   //
   //            //            TRACE(this)("%d", dwLastError);
   //         }
   //      }
   //
   //   } while (Process32NextW(hSnap, &procEntry));
   //
   //   ////////////////////////////////////////////////////////////////////////
   //
   //   LIBCALL(wtsapi32, WTSQueryUserToken)(dwSessionId, &hUserToken);
   //   dwCreationFlags = NORMAL_PRIORITY_CLASS | CREATE_NEW_CONSOLE;
   //   //ZeroMemory(&si,sizeof(STARTUPINFO));
   //   psi->cb = sizeof(STARTUPINFO);
   //   psi->lpDesktop = L"winsta0\\default";
   //
   //   //ZeroMemory(&pi,sizeof(pi));
   //   TOKEN_PRIVILEGES tp;
   //   LUID luid;
   //   hProcess = OpenProcess(MAXIMUM_ALLOWED, false, winlogonPid);
   //
   //   if (!::OpenProcessToken(hProcess, TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY
   //      | TOKEN_DUPLICATE | TOKEN_ASSIGN_PRIMARY | TOKEN_ADJUST_SESSIONID
   //      | TOKEN_READ | TOKEN_WRITE, &hPToken))
   //   {
   //      int abcd = GetLastError();
   //      debug_print("Process token open Error: %u\n", get_last_error());
   //   }
   //
   //   if (!LookupPrivilegeValue(nullptr, SE_DEBUG_NAME, &luid))
   //   {
   //      debug_print("lookup Privilege value Error: %u\n", get_last_error());
   //   }
   //   tp.PrivilegeCount = 1;
   //   tp.Privileges[0].Luid = luid;
   //   tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
   //
   //   DuplicateTokenEx(hPToken, MAXIMUM_ALLOWED, nullptr,
   //      SecurityIdentification, TokenPrimary, &hUserTokenDup);
   //   int dup = GetLastError();
   //
   //   //Adjust Token privilege
   //   SetTokenInformation(hUserTokenDup,
   //      TokenSessionId, (void*)(DWORD_PTR)dwSessionId, sizeof(DWORD));
   //
   //   if (!AdjustTokenPrivileges(hUserTokenDup, false, &tp, sizeof(TOKEN_PRIVILEGES),
   //      (PTOKEN_PRIVILEGES)nullptr, nullptr))
   //   {
   //      int abc = GetLastError();
   //      debug_print("Adjust Privilege value Error: %u\n", get_last_error());
   //   }
   //
   //   if (GetLastError() == ERROR_NOT_ALL_ASSIGNED)
   //   {
   //      debug_print("Token does not have the provilege\n");
   //   }
   //
   //   LPVOID pEnv = nullptr;
   //
   //   if (LIBCALL(userenv, CreateEnvironmentBlock)(&pEnv, hUserTokenDup, true))
   //   {
   //      dwCreationFlags |= CREATE_UNICODE_ENVIRONMENT;
   //   }
   //   else
   //      pEnv = nullptr;
   //
   //   // Launch the process in the client's logon session.
   //
   //   bResult = CreateProcessAsUserW(
   //      hUserTokenDup,                     // client's access token
   //      wstring(pszProcess),    // file to execute
   //      (wchar_t*)(const wchar_t *) wstring(pszCommand),                 // command line
   //      nullptr,            // pointer to process SECURITY_ATTRIBUTES
   //      nullptr,               // pointer to thread SECURITY_ATTRIBUTES
   //      false,              // handles are not inheritable
   //      dwCreationFlags,     // creation flags
   //      pEnv,               // pointer to _new environment block
   //      wstring(pszDir),               // name of current directory
   //      psi,               // pointer to STARTUPINFO structure
   //      ppi                // receives information about _new process
   //   );
   //   // End impersonation of client.
   //
   //   //get_last_error Shud be 0
   //
   //   int iResultOfCreateProcessAsUser = GetLastError();
   //
   //   //Perform All the Close Handles tasks
   //
   //   CloseHandle(hProcess);
   //   CloseHandle(hUserToken);
   //   CloseHandle(hUserTokenDup);
   //   CloseHandle(hPToken);
   //
   //   return 0;
   //}

   //CLASS_DECL_ACME bool enable_windows_token_privilege(HANDLE h, char * pcszName)
   //{
   //
   //   TOKEN_PRIVILEGES tp;
   //
   //   if (!LookupPrivilegeValue(nullptr, SE_DEBUG_NAME, &tp.Privileges[0].Luid))
   //   {
   //
   //      int iError = GetLastError();
   //
   //      debug_print("lookup Privilege value Error: %u\n", iError);
   //
   //      return false;
   //
   //   }
   //
   //   tp.PrivilegeCount = 1;
   //
   //   tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
   //
   //   if (!AdjustTokenPrivileges(h, false, &tp, sizeof(TOKEN_PRIVILEGES), (PTOKEN_PRIVILEGES)nullptr, nullptr))
   //   {
   //
   //      int iError = GetLastError();
   //
   //      debug_print("Adjust Privilege value Error: %u\n", iError);
   //
   //      return false;
   //
   //   }
   //
   //   return true;
   //
   //}
   //
   //CLASS_DECL_ACME BOOL LaunchAppIntoSystemAcc(const ::string & pszProcess, const ::string & pszCommand, const ::string & pszDir, STARTUPINFOW* psi, PROCESS_INFORMATION* ppi)
   //{
   //   //PROCESS_INFORMATION pi;
   //   //STARTUPINFO si;
   //   BOOL bResult = false;
   //   //   DWORD dwSessionId,winlogonPid;
   //   HANDLE hUserTokenDup, hProcess, hPToken;
   //   DWORD dwCreationFlags;
   //   HANDLE hUserToken = nullptr;
   //
   //
   //   // Log the client on to the local computer.
   //
   //   dwCreationFlags = NORMAL_PRIORITY_CLASS | CREATE_NEW_CONSOLE;
   //   //ZeroMemory(&si,sizeof(STARTUPINFO));
   //   psi->cb = sizeof(STARTUPINFOW);
   //   psi->lpDesktop = L"winsta0\\default";
   //
   //   //ZeroMemory(&pi,sizeof(pi));
   //
   ////   LUID luid;
   //   //hProcess = OpenProcess(MAXIMUM_ALLOWED,false,winlogonPid);
   //   hProcess = ::GetCurrentProcess();
   //
   //   //hPToken = hUserToken;
   //
   //   if (!::OpenProcessToken(hProcess, TOKEN_ALL_ACCESS, &hPToken))
   //   {
   //      int abcd = GetLastError();
   //      debug_print("Process token open Error: %u\n", get_last_error());
   //   }
   //
   //   if (!enable_windows_token_privilege(hPToken, SE_DEBUG_NAME))
   //   {
   //
   //      return false;
   //
   //   }
   //
   //   if (!enable_windows_token_privilege(hPToken, SE_CREATE_TOKEN_NAME))
   //   {
   //      return false;
   //   }
   //
   //   if (!enable_windows_token_privilege(hPToken, SE_TCB_NAME))
   //   {
   //
   //      return false;
   //
   //   }
   //
   //   if (!enable_windows_token_privilege(hPToken, SE_ASSIGNPRIMARYTOKEN_NAME))
   //   {
   //
   //      return false;
   //
   //   }
   //
   //   if (!enable_windows_token_privilege(hPToken, SE_INCREASE_QUOTA_NAME))
   //   {
   //
   //      return false;
   //
   //   }
   //
   //   //if(GetLastError() == ERROR_NOT_ALL_ASSIGNED)
   //   //{
   //   //   debug_print("Token does not have the provilege\n");
   //   //}
   //   // "LOCAL SERVICE" or "LocalService" ?
   //   // "NETWORK SERVICE" or "NetworkService" ?
   //   if (!LogonUserW(L"LocalService", L"NT AUTHORITY", nullptr, LOGON32_LOGON_SERVICE, LOGON32_PROVIDER_DEFAULT, &hUserToken))
   //   {
   //      DWORD dwError = ::GetLastError();
   //      string str;
   //      str.format("lookup Privilege value Error: %u\n", dwError);
   //      message_box(str, "Help Me", e_message_box_ok);
   //      return false;
   //   }
   //   if (!DuplicateTokenEx(hUserToken, TOKEN_ALL_ACCESS, nullptr, SecurityDelegation, TokenPrimary, &hUserTokenDup))
   //   {
   //      int dup = GetLastError();
   //      debug_print("DuplicateTokenEx Error: %u\n", get_last_error());
   //   }
   //
   //   //Adjust Token privilege
   //   //SetTokenInformation(hUserTokenDup,
   //   //   TokenSessionId,(void*)dwSessionId,sizeof(DWORD));
   //
   //
   //
   //   LPVOID pEnv = nullptr;
   //
   //   if (LIBCALL(userenv, CreateEnvironmentBlock)(&pEnv, hUserTokenDup, true))
   //   {
   //      dwCreationFlags |= CREATE_UNICODE_ENVIRONMENT;
   //   }
   //   else
   //      pEnv = nullptr;
   //
   //   // Launch the process in the client's logon session.
   //
   //   bResult = CreateProcessAsUserW(
   //      hUserTokenDup,                     // client's access token
   //      wstring(pszProcess),    // file to execute
   //      (wchar_t*)(const wchar_t*) wstring(pszCommand),                 // command line
   //      nullptr,            // pointer to process SECURITY_ATTRIBUTES
   //      nullptr,               // pointer to thread SECURITY_ATTRIBUTES
   //      false,              // handles are not inheritable
   //      dwCreationFlags,     // creation flags
   //      pEnv,               // pointer to _new environment block
   //      wstring(pszDir),               // name of current directory
   //      psi,               // pointer to STARTUPINFO structure
   //      ppi                // receives information about _new process
   //   );
   //   // End impersonation of client.
   //
   //   //get_last_error Shud be 0
   //
   //   //int iResultOfCreateProcessAsUser = GetLastError();
   //
   //   //Perform All the Close Handles tasks
   //
   //   //CloseHandle(hProcess);
   //   //CloseHandle(hUserToken);
   //   //CloseHandle(hUserTokenDup);
   //   //CloseHandle(hPToken);
   //
   //   return true;
   //}
   //


   bool node::is_process_running(::u32 pid)
   {

      HANDLE process = OpenProcess(SYNCHRONIZE, false, pid);

      DWORD ret = WaitForSingleObject(process, 0);

      CloseHandle(process);

      return ret == WAIT_TIMEOUT;

   }


   string node::get_environment_variable(const ::string & pszEnvironmentVariable)
   {

      string str;

      wstring wstrEnvironmentVariable(pszEnvironmentVariable);

      DWORD dwSize = GetEnvironmentVariableW(wstrEnvironmentVariable, nullptr, 0);

      acme::memory_allocate < LPWSTR > lpwsz(dwSize + 1);

      dwSize = (DWORD)lpwsz.get_size();

      dwSize = GetEnvironmentVariableW(wstrEnvironmentVariable, lpwsz, dwSize);

      str = (const WCHAR *)lpwsz;

      return str;

   }


   string node::expand_environment_variables(const string & str)
   {

      wstring wstrSource(str);

      auto len = ExpandEnvironmentStringsW(wstrSource, nullptr, 0);

      wstring wstrTarget;

      auto pwszTarget = wstrTarget.get_string_buffer(len);

      ExpandEnvironmentStringsW(wstrSource, pwszTarget, len + 1);

      wstrTarget.release_string_buffer(len);

      return wstrTarget;

   }


   void node::set_environment_variable(const ::string & pszEnvironmentVariable, const ::string & pszValue)
   {


      ::SetEnvironmentVariableW(wstring(pszEnvironmentVariable), wstring(pszValue));

      //return ::success;

   }


   void node::create_process(const ::string & pszCommandLine, u32 * pprocessId)
   {

      STARTUPINFO StartupInfo;

      PROCESS_INFORMATION ProcessInfo;

      ULONG rc;

      __memset(&StartupInfo, 0, sizeof(StartupInfo));

      StartupInfo.cb = sizeof(STARTUPINFO);

      StartupInfo.dwFlags = STARTF_USESHOWWINDOW;

      StartupInfo.wShowWindow = SW_HIDE;

      if (!CreateProcessW(nullptr, wstring(pszCommandLine), nullptr, nullptr, false,
         CREATE_NEW_CONSOLE,
         nullptr,
         nullptr,
         &StartupInfo,
         &ProcessInfo))
      {

         auto lastError = ::GetLastError();

         auto estatus = last_error_to_status(lastError);

         throw ::exception(estatus, "::windows::node::create_process (1)");

      }

      WaitForSingleObject(ProcessInfo.hProcess, INFINITE);

      if (!GetExitCodeProcess(ProcessInfo.hProcess, &rc))
      {

         rc = 0;

      }

      CloseHandle(ProcessInfo.hThread);

      CloseHandle(ProcessInfo.hProcess);

      if (pprocessId)
      {

         *pprocessId = ProcessInfo.dwProcessId;

      }

      auto estatus = ExitCode_to_status(rc);

      if (!estatus)
      {

         throw ::exception(estatus, "::windows::node::create_process (2)");

      }

   }


   void node::run_silent(const ::string & strFunct, const ::string & strstrParams)
   {

#if defined(_UWP)

      throw ::interface_only();

#elif defined(WINDOWS_DESKTOP)

      STARTUPINFO StartupInfo;

      PROCESS_INFORMATION ProcessInfo;

      char Args[4096];

      char * pEnvCMD = nullptr;

      const char * pDefaultCMD = "CMD.EXE";

      ULONG rc;

      __memset(&StartupInfo, 0, sizeof(StartupInfo));

      StartupInfo.cb = sizeof(STARTUPINFO);

      StartupInfo.dwFlags = STARTF_USESHOWWINDOW;

      StartupInfo.wShowWindow = SW_HIDE;

      Args[0] = 0;

      pEnvCMD = getenv("COMSPEC");

      if (pEnvCMD)
      {

         strcpy(Args, pEnvCMD);

      }
      else
      {

         strcpy(Args, pDefaultCMD);

      }

      // "/c" option - Do the command then terminate the command window
      ansi_concatenate(Args, " /c ");
      //the application you would like to run from the command window
      ansi_concatenate(Args, strFunct);
      ansi_concatenate(Args, " ");
      //the parameters passed to the application being run from the command window.
      ansi_concatenate(Args, strstrParams);

      if (!CreateProcessW(nullptr, wstring(Args), nullptr, nullptr, false,
         CREATE_NEW_CONSOLE,
         nullptr,
         nullptr,
         &StartupInfo,
         &ProcessInfo))
      {

         auto lastError = ::GetLastError();

         auto estatus = last_error_to_status(lastError);

         throw ::exception(estatus, "::windows::node::run_silent (1)");

      }

      WaitForSingleObject(ProcessInfo.hProcess, INFINITE);

      if (!GetExitCodeProcess(ProcessInfo.hProcess, &rc))
      {

         rc = 0;

      }

      CloseHandle(ProcessInfo.hThread);

      CloseHandle(ProcessInfo.hProcess);

      auto estatus = ExitCode_to_status(rc);

      if (!estatus)
      {

         throw ::exception(estatus, "::windows::node::run_silent (2)");

      }

#else

      string strCmdLine;

      strCmdLine = strFunct;

      if (ansi_length(strstrParams) > 0)
      {

         strCmdLine += " ";

         strCmdLine += strstrParams;

      }

      i32 processId;

      if (!create_process(strCmdLine, &processId))
      {

         throw ::exception(estatus, "::windows::node::run_silent (1)");

      }

      while (true)
      {

         if (kill(processId, 0) == -1 && errno == ESRCH) // No process can be found corresponding to processId
         {

            break;

         }

         sleep(::duration(23));

      }

      //return 0;

#endif

   }


   void node::reboot()
   {

      HANDLE htoken = nullptr;

      if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &htoken))
      {

         DWORD dwLastError = ::GetLastError();

         TRACELASTERROR();

         auto estatus = last_error_to_status(dwLastError);

         throw ::exception(estatus, "::windows::node::reboot (1)");

      }

      TOKEN_PRIVILEGES tokenprivileges;

      if (!LookupPrivilegeValue(nullptr, SE_SHUTDOWN_NAME, &tokenprivileges.Privileges[0].Luid))
      {

         DWORD dwLastError = ::GetLastError();

         TRACELASTERROR();

         auto estatus = last_error_to_status(dwLastError);

         throw ::exception(estatus, "::windows::node::reboot (2)");

      }

      tokenprivileges.PrivilegeCount = 1;

      tokenprivileges.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

      if (!AdjustTokenPrivileges(htoken, false, &tokenprivileges, 0, (PTOKEN_PRIVILEGES) nullptr, 0))
      {

         DWORD dwLastError = ::GetLastError();

         TRACELASTERROR();

         auto estatus = last_error_to_status(dwLastError);

         throw ::exception(estatus, "::windows::node::reboot (3)");

      }

      if (GetLastError() == ERROR_NOT_ALL_ASSIGNED)
      {

         throw ::exception(error_failed, "::windows::node::reboot (3.1)");

      }


      ////if(!LookupPrivilegeValue(nullptr, SE_REMOTE_SHUTDOWN_NAME, &tokenprivileges.Privileges[0].Luid))
      ////{
      ////   TRACELASTERROR();
      ////   return false;
      ////}
      ////tokenprivileges.PrivilegeCount = 1;
      ////tokenprivileges.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
      ////if(!AdjustTokenPrivileges(htoken, false, &tokenprivileges, 0, (PTOKEN_PRIVILEGES) nullptr, 0))
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
      if (!ExitWindowsEx(EWX_REBOOT, SHTDN_REASON_MAJOR_SOFTWARE | SHTDN_REASON_MINOR_INSTALLATION))
      {

         DWORD dwLastError = ::GetLastError();

         TRACELASTERROR();

         auto estatus = last_error_to_status(dwLastError);

         throw ::exception(estatus, "::windows::node::reboot (4)");

      }

      //reset the previlages

      tokenprivileges.Privileges[0].Attributes = 0;

      AdjustTokenPrivileges(htoken, false, &tokenprivileges, 0, (PTOKEN_PRIVILEGES) nullptr, 0);

      //return ::success;

   }


   string node::get_user_language()
   {

      //#ifdef _UWP
      //
      //      string_array stra;
      //
      //      try
      //      {
      //
      //         stra.explode("-", ::winrt::Windows::Globalization::ApplicationLanguages::PrimaryLanguageOverride);
      //
      //      }
      //      catch (long)
      //      {
      //
      //      }
      //
      //      strLocale = stra[0];
      //
      //      strSchema = stra[0];
      //
      //#elif defined(WINDOWS)

      LANGID langid = ::GetUserDefaultLangID();

      string strIso = ::acme_windows::langid_to_iso(langid);

      //#endif
      string strUserlanguage = strIso;

      return strUserlanguage;

   }


   bool node::get_application_exclusivity_security_attributes(memory & memory)
   {

      bool bSetOk = false;

      memory.set_size(sizeof(SECURITY_ATTRIBUTES) + sizeof(SECURITY_DESCRIPTOR));

      auto pMutexAttributes = (SECURITY_ATTRIBUTES *)memory.get_data();

      ZeroMemory(pMutexAttributes, sizeof(*pMutexAttributes));

      pMutexAttributes->nLength = sizeof(*pMutexAttributes);

      pMutexAttributes->bInheritHandle = false; // object uninheritable

      // declare and initialize a security descriptor
      auto pSD = (SECURITY_DESCRIPTOR *)(pMutexAttributes + 1);

      bool bInitOk = InitializeSecurityDescriptor(pSD, SECURITY_DESCRIPTOR_REVISION) != false;

      if (bInitOk)
      {
         // give the security descriptor a Null Dacl
         // done using the  "true, (PACL)nullptr" here
         bSetOk = SetSecurityDescriptorDacl(pSD,
            true,
            (PACL)nullptr,
            false) != false;

      }

      if (bSetOk)
      {

         pMutexAttributes->lpSecurityDescriptor = pSD;

      }
      else
      {

         memory.set_size(0);

      }

      return bSetOk;

   }


   void node::register_spa_file_type(const ::string & strAppIdHandler)
   {

#ifdef WINDOWS_DESKTOP

      HKEY hkey;

      wstring extension = L".spa";                     // file extension
      wstring desc = L"spafile";          // file type description
      wstring content_type = L"application/x-spa";

      wstring app(acmedirectory()->stage(strAppIdHandler, process_platform_name(), process_configuration_name()));

      wstring icon(app);

      app = L"\"" + app + L"\"" + L" \"%1\"";
      icon = L"\"" + icon + L"\",107";

      wstring action = L"Open";

      wstring sub = L"\\shell\\";

      wstring path = L"spafile\\shell\\open\\command";


      // 1: Create subkey for extension -> HKEY_CLASSES_ROOT\.002
      if (RegCreateKeyExW(HKEY_CLASSES_ROOT, extension.c_str(), 0, 0, 0, KEY_ALL_ACCESS, 0, &hkey, 0) != ERROR_SUCCESS)
      {
         output_debug_string("Could not create or open a registrty key\n");
         throw ::exception(error_resource);
      }
      RegSetValueExW(hkey, L"", 0, REG_SZ, (byte *)desc.c_str(), ::u32(desc.length() * sizeof(wchar_t))); // default vlaue is description of file extension
      RegSetValueExW(hkey, L"ContentType", 0, REG_SZ, (byte *)content_type.c_str(), ::u32(content_type.length() * sizeof(wchar_t))); // default vlaue is description of file extension
      RegCloseKey(hkey);



      // 2: Create Subkeys for action ( "Open with my program" )
      // HKEY_CLASSES_ROOT\.002\Shell\\open with my program\\command
      if (RegCreateKeyExW(HKEY_CLASSES_ROOT, path.c_str(), 0, 0, 0, KEY_ALL_ACCESS, 0, &hkey, 0) != ERROR_SUCCESS)
      {
         output_debug_string("Could not create or open a registrty key\n");
         throw ::exception(error_resource);
      }
      RegSetValueExW(hkey, L"", 0, REG_SZ, (byte *)app.c_str(), ::u32(app.length() * sizeof(wchar_t)));
      RegCloseKey(hkey);


      path = L"spafile\\DefaultIcon";

      if (RegCreateKeyExW(HKEY_CLASSES_ROOT, path.c_str(), 0, 0, 0, KEY_ALL_ACCESS, 0, &hkey, 0) != ERROR_SUCCESS)
      {
         output_debug_string("Could not create or open a registrty key\n");
         throw ::exception(error_resource);
      }
      RegSetValueExW(hkey, L"", 0, REG_SZ, (byte *)icon.c_str(), ::u32(icon.length() * sizeof(wchar_t)));
      RegCloseKey(hkey);

      wstring wstr(acmedirectory()->stage(strAppIdHandler, process_platform_name(), process_configuration_name()) / "spa_register.txt");

      int iRetry = 9;

      while (!acmefile()->exists(utf8(wstr.c_str())) && iRetry > 0)
      {

acmedirectory()create(::file_path_folder(utf8(wstr.c_str())).c_str());

         acmefile()->put_contents(utf8(wstr.c_str()).c_str(), "");

         iRetry--;

         sleep(100_ms);

      }

#endif

      //return true;

   }


   void node::start_program_files_app_app_admin(string strPlatform, string strConfiguration)
   {

#ifdef WINDOWS_DESKTOP

      SHELLEXECUTEINFOW sei = {};

      string str = acmedirectory()->app_app_admin(strPlatform, strConfiguration);

      if (!acmefile()->exists(str))
      {

         throw ::exception(error_failed);

      }

      ::install::admin_mutex mutexStartup(this, "-startup");

      wstring wstr(str);

      sei.cbSize = sizeof(SHELLEXECUTEINFOW);
      sei.fMask = SEE_MASK_NOASYNC | SEE_MASK_NOCLOSEPROCESS;
      sei.lpVerb = L"RunAs";

      sei.lpFile = wstr.c_str();

      ::ShellExecuteExW(&sei);

      DWORD dwGetLastError = GetLastError();

#endif

      //return ::success;

   }


   void node::get_folder_path_from_user(::file::path & pathFolder)
   {

      wstring wstrFolder(pathFolder);

      int i = (int)(iptr) ::ShellExecuteW(nullptr, L"open", wstrFolder, nullptr, nullptr, SW_NORMAL);

      if (i < 32)
      {
         auto estatus = last_error_to_status(i);
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

         throw ::exception(estatus);


      }

      //return ::success;

   }



   HICON node::extract_icon(HINSTANCE hInst, const ::string & pszExeFileName, ::u32 nIconIndex)

   {

      return ::ExtractIconW(hInst, utf8_to_unicode(pszExeFileName), nIconIndex);


   }


   ::u32 node::get_temp_path(string & str)
   {

      return ::GetTempPathW(MAX_PATH * 8, wtostring(str, MAX_PATH * 8));

   }


   ::i32 node::reg_query_value(HKEY hkey, const ::string & pszSubKey, string & str)
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

         lResult = RegQueryValueExW(hkey, wstring(pszSubKey), nullptr, &dwType, (byte *)(unichar *)pwsz, &dwSize);

         str = pwsz;

         //str.release_string_buffer(dwSize);

         return lResult;

      }
      else
      {

         return ERROR_NOT_SUPPORTED;

      }

   }


   //HICON node::extract_icon(HINSTANCE hInst, const ::string & pszExeFileName, ::u32 nIconIndex)

   //{

   //   return ::ExtractIconW(hInst, utf8_to_unicode(pszExeFileName), nIconIndex);


   //}


   void node::delete_file(const ::string & pFileName)
   {

      if (!::DeleteFileW(utf8_to_unicode(pFileName)))
      {

         throw ::exception(error_failed);

      }

      //return ::success;

   }




   ::u32 node::get_current_directory(string & str)
   {

      return ::GetCurrentDirectoryW(MAX_PATH * 8, wtostring(str, MAX_PATH * 8));

   }



   void node::register_dll(const ::file::path & pathDll)
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

      property_set set;

      set["privileged"] = true;

      //if (!call_sync(path, strParam, path.folder(), ::e_display_none, 3_minute, set))
      call_sync(path, strParam, path.folder(), ::e_display_none, 3_minute, set);
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


   //::string node::expand_environment_variables(const ::string & str)
   //{

   //   wstring wstrSource(str);

   //   wstring wstrTarget = expand_environment_variables(wstrSource);

   //   return wstrTarget;

   //}


   ::wstring node::expand_environment_variables(const ::wstring & wstr)
   {

      DWORD dwCharLen = ::ExpandEnvironmentStringsW(wstr, nullptr, 0);

      wstring wstrTarget;

      if (dwCharLen)
      {

         auto pwsz = wstrTarget.get_string_buffer(dwCharLen);

         ::ExpandEnvironmentStringsW(wstr, pwsz, dwCharLen + 1);

         wstrTarget.release_string_buffer();

      }

      return wstrTarget;

   }


   void node::implement(::pointer<::acme::node>& pnode, ::pointer<::acme::system> & psystem)
   {

      return ::acme::node::implement(pnode, psystem);

   }


   void node::on_start_system()
   {

      //auto estatus = acmesystem()->post_initial_request();
      acmesystem()->post_initial_request();

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //return estatus;

   }


   void node::create_app_shortcut(::acme::application * papp)
   {

   }


   void node::open_url(const ::string & strUrl)
   {

      wstring wstrUrl(strUrl);

      ::ShellExecuteW(nullptr, L"open", wstrUrl, nullptr, nullptr, SW_SHOWNORMAL);

   }


} // namespace acme_windows





#ifdef WINDOWS_DESKTOP

int windows_desktop1_main(HINSTANCE hInstance, int nCmdShow);



#include "apex/operating_system/windows/_.h"

#endif

