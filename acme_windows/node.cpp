#include "framework.h"
#undef USUAL_OPERATING_SYSTEM_SUPPRESSIONS
#include "node.h"
#include "directory_system.h"
#include "file_system.h"
#include "registry.h"
#include "process.h"
#include "exclusive.h"
#include "application.h"
#include "create_process.h"
#include "file_link.h"
#include "acme/exception/exception.h"
#include "acme/exception/status.h"
#include "acme/filesystem/filesystem/directory_system.h"
#include "acme/filesystem/filesystem/file_context.h"
#include "acme/filesystem/filesystem/directory_context.h"
//#include "acme/filesystem/filesystem/folder_dialog.h"
#include "acme/operating_system/process.h"
#include "acme/operating_system/summary.h"
#include "acme/parallelization/install_mutex.h"
#include "acme/parallelization/manual_reset_happening.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/platform/scoped_restore.h"
#include "acme/platform/application.h"
#include "acme/platform/system.h"
#include "acme/platform/uuid.h"
#include "acme/prototype/prototype/memory.h"
#include "acme/prototype/string/__wide.h"
#include "acme/prototype/string/str.h"
#include "acme/prototype/string/adaptor.h"
#include "acme/prototype/string/international.h"
#include "acme/prototype/string/str.h"

#include "acme/_operating_system.h"


#include "acme/operating_system/windows_common/com/hresult_exception.h"
#include "acme/operating_system/windows_common/com/comptr.h"
#include "acme/operating_system/windows_common/com/cotaskptr.h"
#include "acme_windows_common/security_attributes.h"
#include "acme/operating_system/windows_common/com/bstring.h"
#include "acme/operating_system/windows_common/com/variant.h"
#include <Shldisp.h>
#include <shellapi.h>
#include <Shlobj.h>


#pragma comment(lib, "Version.lib")

CLASS_DECL_ACME void acme_set_main_hwnd(HWND hwnd);
CLASS_DECL_ACME HWND acme_get_main_hwnd();

//CLASS_DECL_ACME void nano_graphics_win32_factory(::factory::factory * pfactory);
//CLASS_DECL_ACME extern "C" void nano_user_win32_factory(::factory::factory * pfactory);


//
//#if defined(_WIN32)
//#  ifndef NOMINMAX
//#  define NOMINMAX 1
//#  endif
////#  include <windows.h>
//#include <commdlg.h>
////#endif
//
////#include <shobjidl.h>
////#include <ShellApi.h>
////#include <Security.h>
////#include <wincred.h>
//#include <shobjidl_core.h>
//



CLASS_DECL_ACME_WINDOWS void call_async(const scoped_string& strPath, const scoped_string& strParam, const scoped_string& strDir, ::e_display edisplay, bool bPrivileged, unsigned int* puiPid);


namespace windows
{


   CLASS_DECL_ACME_WINDOWS string langid_to_iso(LANGID langid);


} // namespace windows


namespace acme_windows
{

   struct shell_execute :
      public SHELLEXECUTEINFOW
   {

      wstring        m_wstrFile;

      wstring        m_wstrParams;

      wstring        m_wstrWorkingDirectory;

      shell_execute(const scoped_string& strFile, const scoped_string& strParams, const ::file::path& pathWorkingDirectory = {})
      {

         ::zero(this, sizeof(SHELLEXECUTEINFOW));

         cbSize = sizeof(SHELLEXECUTEINFOW);

         m_wstrFile = strFile;

         lpFile = m_wstrFile;

         if (strParams.has_character())
         {

            m_wstrParams = strParams;

            lpParameters = m_wstrParams;

         }

         if (pathWorkingDirectory.has_character())
         {

            m_wstrWorkingDirectory = pathWorkingDirectory.windows_path().extended_path();

            lpDirectory = m_wstrWorkingDirectory;

         }

      }


      bool async()
      {

         if (!::ShellExecuteExW(this))
         {

            return false;

         }

         return true;

      }


      bool synchronization_object(const class time& timeWait, DWORD& dwExitCode)
      {

         fMask = SEE_MASK_NOASYNC | SEE_MASK_NOCLOSEPROCESS;

         if (!async())
         {

            return false;

         }

         auto start = ::time::now();

         DWORD dwError = ::GetLastError();

         dwExitCode = 0;

         while (true)
         {

            if (::GetExitCodeProcess(hProcess, &dwExitCode))
            {

               if (dwExitCode != STILL_ACTIVE)
               {

                  break;

               }

            }
            else
            {

               break;

            }

            auto waitNow = minimum(timeWait - start.elapsed(), 1000_ms);

            if (waitNow <= 0_s)
            {

               break;

            }

            preempt(waitNow);

         }

         ::CloseHandle(hProcess);

         return true;


      }


   };


   node::node()
   {

      //::windows::callstack::s_pcriticalsection = ___new critical_section();

   }


   node::~node()
   {

      //#ifdef WINDOWS
      //
      //         ::acme::del(::windows::callstack::s_pcriticalsection);
      //
      //#endif

   }


   void node::initialize(::particle* pparticle)
   {

      ::platform::node::initialize(pparticle);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //windows_registry_initialize();

      //return estatus;

   }


   //void node::call_async(const ::scoped_string & scopedstrPath, const ::scoped_string & scopedstrParam, const ::scoped_string & scopedstrDir, ::e_display edisplay, bool bPrivileged, unsigned int * puiPid)
   //{

   //   /*auto estatus =*/ ::call_async(strPath, strParam, strDir, edisplay, bPrivileged, puiPid);

   //   //if (!estatus)
   //   //{

   //   //   return estatus;

   //   //}

   //   //return estatus;

   //}



   void node::shell_open(const ::file::path& pathFile, const ::scoped_string & scopedstrParams, const ::file::path& pathFolder)
   {

      wstring wstrFile(pathFile.windows_path().extended_path());

      const wchar_t* pwszParams = nullptr;

      wstring wstrParams(scopedstrParams);

      if (wstrParams.has_character())
      {

         pwszParams = wstrParams;

      }

      const wchar_t* pwszFolder = nullptr;

      wstring wstrFolder(pathFolder.windows_path().extended_path());

      if (wstrFolder.has_character())
      {

         pwszFolder = wstrFolder;

      }

      HWND hwndMain = acme_get_main_hwnd();

      int iRet = (int)(iptr) ::ShellExecuteW(hwndMain,
         L"open",
         wstrFile,
         pwszParams,
         pwszFolder,
         SW_SHOWNORMAL);

   }




   ::file::path node::get_default_base_integration_folder()
   {

      return directory_system()->system_drive() / "integration" / "_____";

   }


   //::color::color node::reinterpreted_windows_darkness_background_color()
   //{

   //   if (_win32_registry_windows_darkness())
   //   {

   //      return ::color::black;

   //   }

   //   return ::color::white;

   //}





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
   //         unsigned int dw;
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
   //   bool node::_os_calc_dark_mode()
   //   {
   //
   //      try
   //      {
   //
   //         ::acme_windows::registry::key key;
   //
   //         key.open(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Themes\\Personalize");
   //
   //         unsigned int dw;
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
   //   ::color::color node::get_default_color(unsigned long long u)
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
   //   void node::set_console_colors(unsigned int dwScreenColors, unsigned int dwPopupColors, unsigned int dwWindowAlpha)
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
   //      unsigned int dwSystemUseLightTheme;
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
   //      unsigned int dwAppsUseLightTheme;
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
   //         //posix_time t = time(nullptr);
   //
   //         //struct tm *p = localtime(&t);
   //
   //         DYNAMIC_TIME_ZONE_INFORMATION i = {};
   //
   //         unsigned int dw = GetDynamicTimeZoneInformation(&i);
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
   //         posix_time t = time(nullptr);
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
   //      //   strPathDll = directory_system()->matter() / "time" / process_platform_name() /"stage/_desk_tb.dll";
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
   //      ::property_set set;
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
   //      auto estatus = system()->m_papex->thread_initialize(system());
   //
   //      if (!estatus)
   //      {
   //
   //         return estatus;
   //
   //      }
   //
   //      estatus = system()->on_start();
   //
   //      if (!estatus)
   //      {
   //
   //         return estatus;
   //
   //      }
   //
   //      estatus = system()->main();
   //
   //      if (!estatus)
   //      {
   //
   //         return estatus;
   //
   //      }
   //
   //      estatus = system()->inline_term();
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
   //   string node::veriwell_multimedia_music_midi_get_default_implementation_name()
   //   {
   //
   //      return system()->implementation_name("music_midi", "mmsystem");
   //
   //   }
   //
   //
   //   string node::multimedia_audio_mixer_get_default_implementation_name()
   //   {
   //
   //      return "audio_mixer_mmsystem";
   //
   //   }
   //
   //
   //   string node::multimedia_audio_get_default_implementation_name()
   //   {
   //
   //      string str;
   //
   //      if (file_system()->exists(directory_system()->system() / "config\\system\\audio.txt"))
   //      {
   //
   //         str = file_system()->as_string(directory_system()->system() / "config\\system\\audio.txt");
   //
   //      }
   //      else
   //      {
   //
   //         ::file::path strPath;
   //
   //         strPath = directory_system()->appdata() / "audio.txt";
   //
   //         str = file_system()->as_string(strPath);
   //
   //      }
   //
   //      if (str.has_character())
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
   void node::install_crash_dump_reporting(const ::scoped_string & scopedstrModuleNameWithTheExeExtension)
   {

      ::acme_windows::registry::key k;

      string strKey = "SOFTWARE\\Microsoft\\Windows\\Windows Error Reporting\\LocalDumps\\" + scopedstrModuleNameWithTheExeExtension;

      if (k._open(HKEY_LOCAL_MACHINE, strKey, true))
      {
         ::file::path str = directory_system()->userconfig() / "CrashDumps" / scopedstrModuleNameWithTheExeExtension;
         wstring wstr = str;
         RegSetValueExW(k.m_hkeySub, L"DumpFolder", 0, REG_EXPAND_SZ, (unsigned char*)wstr.c_str(), unsigned int((wcslen(wstr) + 1) * sizeof(wchar_t)));
         unsigned int dw = 10;
         RegSetValueExW(k.m_hkeySub, L"DumpCount", 0, REG_DWORD, (unsigned char*)&dw, sizeof(dw));
         dw = 2;
         RegSetValueExW(k.m_hkeySub, L"DumpType", 0, REG_DWORD, (unsigned char*)&dw, sizeof(dw));

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
   //         g_iMemoryCounters = xxxxfile_exists(directory_system()->config() / "system/memory_counters.txt") ? 1 : 0;
   //
   //         if (g_iMemoryCounters)
   //         {
   //
   //            g_pmutexMemoryCounters = ___new ::mutex(e_create_new, false, "Global\\ca2_memory_counters");
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
   //         g_pMemoryCounters = ___new ::file::path();
   //
   //#if defined(UNIVERSAL_WINDOWS)
   //
   //         string strBasePath = directory_system()->system() / "memory_counters";
   //
   //#else
   //
   //         ::file::path strModule = module_path_from_pid(getpid());
   //
   //         string strBasePath = directory_system()->system() / "memory_counters" / strModule.title() / ::as_string(getpid());
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

   //   sysTime.wYear = (unsigned short)time.year();
   //   sysTime.wMonth = (unsigned short)time.month();
   //   sysTime.wDay = (unsigned short)time.day();
   //   sysTime.wHour = (unsigned short)time.hour();
   //   sysTime.wMinute = (unsigned short)time.minute();
   //   sysTime.wSecond = (unsigned short)time.second();
   //   sysTime.wMilliseconds = 0;

   //   // convert system time to local file time
   //   FILETIME localTime;

   //   DWORD dwLastError = ::GetLastError();

   //   if (!SystemTimeToFileTime((LPSYSTEMTIME)&sysTime, &localTime))
   //   {

   //      DWORD dwLastError = ::GetLastError();

   //      auto estatus = ::windows::last_error_status(dwLastError);

   //      throw ::exception(estatus, "::windows::node::datetime_to_filetime (1)");

   //   }

   //   // convert local file time to UTC file time
   //   if (!LocalFileTimeToFileTime(&localTime, (FILETIME*)pfiletime))
   //   {

   //      DWORD dwLastError = ::GetLastError();

   //      auto estatus = ::windows::last_error_status(dwLastError);

   //      throw ::exception(estatus, "::windows::node::datetime_to_filetime (2)");

   //   }

   //   //return ::success;

   //}


   //::e_status node::windows::last_error_status(DWORD dwLastError)
   //{

   //   if (dwLastError == 0)
   //   {

   //      return ::success;

   //      //return;

   //   }
   //   else
   //   {

   //      return error_failed;

   //   }

   //}


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


   string node::audio_get_default_implementation_name()
   {

      return system()->implementation_name("audio", "mmsystem");

   }


   //void node::on_start_system()
   //{

   //   auto psystem = system();

   //   auto estatus = psystem->post_initial_request();

   //   if (!estatus)
   //   {

   //      return estatus;

   //   }

   //   return estatus;

   //}


   ::file::path_array_base node::process_identifier_modules_paths(::process_identifier processidentifier)
   {

      HANDLE hProcess;

      //unsigned int i;

      DWORD dwProcess = (DWORD)processidentifier;

      hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, false, dwProcess);

      if (nullptr == hProcess)
      {

         return {};

      }

      const int iMaxModuleCount = 1024 * 8;

      ::array < HMODULE > hmodulea;

      hmodulea.set_size(iMaxModuleCount);

      ::file::path_array_base patha;

      DWORD cbNeeded;

      while (!EnumProcessModules(hProcess, hmodulea.data(), (DWORD)hmodulea.get_size_in_bytes(), &cbNeeded)
         || hmodulea.get_size_in_bytes() < cbNeeded)
      {

         if (hmodulea.get_count() > 1024 * 1024)
         {

            return {};

         }

         hmodulea.set_size(hmodulea.get_size() * 2);

      }

      hmodulea.set_size(cbNeeded / sizeof(HMODULE));

      ::array < WCHAR > wchara;

      wchara.set_size(MAX_PATH * 8);

      for (auto& hmodule : hmodulea)
      {

         if (GetModuleFileNameExW(hProcess, hmodule, wchara.data(), (DWORD)wchara.size()))
         {

            patha.add(wchara.data());

         }

      }

      CloseHandle(hProcess);

      return ::transfer(patha);

   }


   //::file::path_array_base node::modules_paths()
   //{

   //   auto processidentifiera = processes_identifiers();

   //   ::file::path_array_base patha;

   //   for (auto processidentifier : processidentifiera)
   //   {

   //      auto pathaProcessModules = process_identifier_modules_paths(processidentifier);

   //      patha.append_unique_ci(pathaProcessModules);

   //   }

   //   return ::transfer(patha);

   //}


   bool node::load_modules_diff(string_array_base& straOld, string_array_base& straNew, const ::scoped_string & scopedstrExceptDir)
   {

      bool bFound;

      HMODULE hmodule;

      ::collection::count iLenExcept;

      if (scopedstrExceptDir.has_character())
      {

         iLenExcept = scopedstrExceptDir.length();

      }
      else
      {

         iLenExcept = 0;

      }

      for (int i = 0; i < straOld.get_count(); i++)
      {

         bFound = false;

         if (iLenExcept > 0)
         {

            if (ansi_length(straOld[i]) > iLenExcept)
            {

               if (_strnicmp(straOld[i], scopedstrExceptDir.begin(), (size_t)iLenExcept) == 0)
               {

                  continue;

               }

            }

         }

         for (int j = 0; j < straNew.get_count(); j++)
         {

            if (case_insensitive_ansi_compare(straOld[i], straNew[j]) == 0)
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


   ::process_identifier_array node::module_path_processes_identifiers(const ::scoped_string & scopedstrModulePath, bool bModuleNameIsPropertyFormatted)
   {

      ::file::path pathModule(scopedstrModulePath);

      process_identifier_array processesidentifiers;

      if (pathModule.is_empty())
      {

         return processesidentifiers;

      }

      auto pmutex = create_global_named_mutex(this, NULL, "the_veri_global_ca2");

      synchronous_lock lock_the_veri_global_ca2(pmutex);

      auto dwaProcesses = ::windows::enum_processes();

      //WCHAR currName[MAX_PATH];
      //GetModuleFileNameEx(GetCurrentProcess(), NULL, currName, MAX_PATH);
      //DWORD currProcessId = GetCurrentProcessId();

      for (auto& dwProcess : dwaProcesses)
      {

         auto pathProcessModule = process_identifier_module_path(dwProcess);

         //HANDLE handleProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, dwProcess);

         //if (handleProcess)
         //{

         //   WCHAR name[MAX_PATH];

         //   GetModuleFileNameEx(handleProcess, NULL, name, MAX_PATH);

         //   ::CloseHandle(handleProcess);

         //   wstring wstr(name);

         if (pathModule == pathProcessModule)
         {

            processesidentifiers.add(dwProcess);

         }

      }

      return ::transfer(processesidentifiers);

   }


   //HANDLE process_snap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

   //PROCESSENTRY32 entry;

   //DWORD dwError = ::GetLastError();

   //if (Process32First(process_snap, &entry) && dwError != ERROR_NO_MORE_FILES)
   //{

   //repeat_process:

   //   string strPath;

   //   strPath = process_identifier_module_path(entry.th32ProcessID);

   //   if (bModuleNameIsPropertyFormatted)
   //   {

   //      if (entry.th32ProcessID != 0 && strPath.case_insensitive_order(pathModule) == 0)
   //      {

   //         iaPid.add((long long)entry.th32ProcessID);

   //      }

   //   }
   //   else
   //   {

   //      if (entry.th32ProcessID != 0 && ::file::path(strPath) == pathModule)
   //      {

   //         iaPid.add((long long)entry.th32ProcessID);

   //      }

   //   }

   //   DWORD dwError = ::GetLastError();

   //   if (Process32Next(process_snap, &entry) && dwError != ERROR_NO_MORE_FILES)
   //   {

   //      goto repeat_process;

   //   }

   //}

   //::CloseHandle(process_snap);

//   return iaPid;
//
//}


   ::file::path node::process_identifier_module_path(::process_identifier processidentifier)
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

      DWORD dwProcess = (DWORD)processidentifier;

      HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, false, dwProcess);

      if (hProcess == nullptr)
      {

         return "";

      }

      WCHAR path[MAX_PATH * 4];

      string strPath;

      if (GetModuleFileNameExW(hProcess, 0, path, sizeof(path) / sizeof(path[0])))
      {
         strPath = solve_relative(string(path));

      }

      ::CloseHandle(hProcess);

      return strPath;

   }


   ::process_identifier_array node::processes_identifiers()
   {

      process_identifier_array processidentifiera;

      dword_array dwaProcesses;

      ::windows::enum_processes(dwaProcesses);

      for (auto& dwProcess : dwaProcesses)
      {

         processidentifiera.add(dwProcess);

      }

      return processidentifiera;

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


   bool node::process_contains_module(string& strImage, ::process_identifier processidentifier, const ::scoped_string & scopedstrLibrary)
   {

      HANDLE hProcess;

      DWORD cbNeeded;

      ::collection::index i;

      hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, false, (DWORD)processidentifier);

      if (nullptr == hProcess)
         return false;

      const int iMaxModuleCount = 1024;

      array < HMODULE > hmods;

      hmods.set_size(iMaxModuleCount);

      const int iImageSize = MAX_PATH * 8;

      ::memory memory;

      memory.set_size(iImageSize);

      GetModuleFileNameExW(hProcess, nullptr, (WCHAR*)memory.data(), (DWORD)(memory.size() / sizeof(WCHAR)));

      strImage = (const wchar_t*)memory.data();

      wstring wstrLibrary(scopedstrLibrary);

      bool bFound = false;

      if (EnumProcessModules(hProcess, hmods.data(), (DWORD)(hmods.get_size_in_bytes()), &cbNeeded))
      {

         for (i = 0; i < ::collection::index(cbNeeded / sizeof(HMODULE)); i++)
         {

            // Get the full path to the module's file.

            if (GetModuleFileNameExW(hProcess, hmods[i], (WCHAR*)memory.data(), (DWORD)(memory.size() / sizeof(WCHAR))))
            {

               if (case_insensitive_string_order((const wchar_t*)memory.data(), wstrLibrary) == 0)
               {

                  bFound = true;

                  break;

               }

            }

         }

      }

      ::CloseHandle(hProcess);

      return bFound;

   }


   ::process_identifier_array node::shared_library_process(string_array_base& straProcesses, const ::scoped_string & scopedstrLibrary)
   {

      process_identifier_array processidentifiera;

      auto dwaProcesses = ::windows::enum_processes();

      ::string strImage;

      for (auto& dwProcess : dwaProcesses)
      {

         if (process_contains_module(strImage, dwProcess, scopedstrLibrary))
         {

            straProcesses.add(strImage);

            processidentifiera.add(dwProcess);

         }

      }

      return ::transfer(processidentifiera);

   }









   //CLASS_DECL_ACME unsigned int get_current_process_id()
   //{
   //
   //   return ::GetCurrentProcessId();
   //
   //}






   //CLASS_DECL_ACME BOOL LaunchAppIntoDifferentSession(const ::scoped_string & scopedstrProcess, const ::scoped_string & scopedstrCommand, const ::scoped_string & scopedstrDir, STARTUPINFOW* psi, PROCESS_INFORMATION* ppi, int iSession)
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
   //            //            information(this)("%d", dwLastError);
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
   //      debug_print("find Privilege value Error: %u\n", get_last_error());
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
   //      debug_print("find Privilege value Error: %u\n", iError);
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
   //CLASS_DECL_ACME BOOL LaunchAppIntoSystemAcc(const ::scoped_string & scopedstrProcess, const ::scoped_string & scopedstrCommand, const ::scoped_string & scopedstrDir, STARTUPINFOW* psi, PROCESS_INFORMATION* ppi)
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
   //      str.formatf("find Privilege value Error: %u\n", dwError);
   //      message_box(str, "Help Me", ::user::e_message_box_ok);
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


   bool node::is_process_running(::process_identifier processidentifier)
   {

      DWORD dwProcess = (DWORD)processidentifier;

      HANDLE process = ::OpenProcess(SYNCHRONIZE, false, dwProcess);

      DWORD ret = ::WaitForSingleObject(process, 0);

      ::CloseHandle(process);

      return ret == WAIT_TIMEOUT;

   }


   string node::get_environment_variable(const ::scoped_string& scopedstrEnvironmentVariable)
   {

      string str;

      wstring wstrEnvironmentVariable(scopedstrEnvironmentVariable);

      DWORD dwSize = GetEnvironmentVariableW(wstrEnvironmentVariable, nullptr, 0);

      wstring wstr;

      auto pwsz = wstr.get_buffer(dwSize);

      dwSize = GetEnvironmentVariableW(wstrEnvironmentVariable, pwsz, dwSize);

      wstr.release_buffer(dwSize);

      str = wstr;

      return str;

   }


   ::string node::expand_environment_variables(const ::scoped_string& scopedstr)
   {

      wstring wstrSource(scopedstr);

      auto len = ExpandEnvironmentStringsW(wstrSource, nullptr, 0);

      wstring wstrTarget;

      auto pwszTarget = wstrTarget.get_buffer(len);

      ExpandEnvironmentStringsW(wstrSource, pwszTarget, len + 1);

      wstrTarget.release_buffer(len);

      return wstrTarget;

   }


   void node::set_environment_variable(const ::scoped_string& scopedstrEnvironmentVariable, const ::scoped_string& scopedstrValue)
   {

      ::wstring wstrEnvironmentVariable(scopedstrEnvironmentVariable);

      ::wstring wstrValue(scopedstrValue);

      ::SetEnvironmentVariableW(wstrEnvironmentVariable, wstrValue);

   }


   ::process_identifier node::create_process(const ::scoped_string & scopedstrCommandLine)
   {

      STARTUPINFO StartupInfo;

      PROCESS_INFORMATION ProcessInfo;

      ULONG rc;

      memory_set(&StartupInfo, 0, sizeof(StartupInfo));

      StartupInfo.cb = sizeof(STARTUPINFO);

      StartupInfo.dwFlags = STARTF_USESHOWWINDOW;

      StartupInfo.wShowWindow = SW_HIDE;

      wstring wstrCommandLine(scopedstrCommandLine);

      if (!CreateProcessW(nullptr, (WCHAR*)wstrCommandLine.c_str(), nullptr, nullptr, false,
         CREATE_NEW_CONSOLE,
         nullptr,
         nullptr,
         &StartupInfo,
         &ProcessInfo))
      {

         auto lasterror = ::GetLastError();

         auto estatus = ::windows::last_error_status(lasterror);

         throw ::exception(estatus, "::windows::node::create_process (1)");

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

         throw ::exception(estatus, "::windows::node::create_process (2)");

      }

      return ProcessInfo.dwProcessId;

   }


   void node::run_silent(const ::scoped_string & scopedstrFunct, const ::scoped_string & scopedstrstrParams)
   {

#if defined(UNIVERSAL_WINDOWS)

      throw ::interface_only();

#elif defined(WINDOWS_DESKTOP)

      STARTUPINFO StartupInfo;

      PROCESS_INFORMATION ProcessInfo;

      char Args[4096];

      char* pEnvCMD = nullptr;

      const_char_pointer pDefaultCMD = "CMD.EXE";

      ULONG rc;

      memory_set(&StartupInfo, 0, sizeof(StartupInfo));

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
      ansi_concatenate(Args, scopedstrFunct);
      ansi_concatenate(Args, " ");
      //the parameters passed to the application being run from the command window.
      ansi_concatenate(Args, scopedstrstrParams);

      wstring wstrArguments(Args);

      if (!CreateProcessW(nullptr, (WCHAR*)wstrArguments.c_str(), nullptr, nullptr, false,
         CREATE_NEW_CONSOLE,
         nullptr,
         nullptr,
         &StartupInfo,
         &ProcessInfo))
      {

         auto lasterror = ::GetLastError();

         auto estatus = ::windows::last_error_status(lasterror);

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

      int processId;

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

         sleep(::time(23));

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

         auto estatus = ::windows::last_error_status(dwLastError);

         throw ::exception(estatus, "::windows::node::reboot (1)");

      }

      TOKEN_PRIVILEGES tokenprivileges;

      if (!LookupPrivilegeValue(nullptr, SE_SHUTDOWN_NAME, &tokenprivileges.Privileges[0].Luid))
      {

         DWORD dwLastError = ::GetLastError();

         TRACELASTERROR();

         auto estatus = ::windows::last_error_status(dwLastError);

         throw ::exception(estatus, "::windows::node::reboot (2)");

      }

      tokenprivileges.PrivilegeCount = 1;

      tokenprivileges.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

      if (!AdjustTokenPrivileges(htoken, false, &tokenprivileges, 0, (PTOKEN_PRIVILEGES) nullptr, 0))
      {

         DWORD dwLastError = ::GetLastError();

         TRACELASTERROR();

         auto estatus = ::windows::last_error_status(dwLastError);

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

         auto estatus = ::windows::last_error_status(dwLastError);

         throw ::exception(estatus, "::windows::node::reboot (4)");

      }

      //reset the previlages

      tokenprivileges.Privileges[0].Attributes = 0;

      AdjustTokenPrivileges(htoken, false, &tokenprivileges, 0, (PTOKEN_PRIVILEGES) nullptr, 0);

      //return ::success;

   }


   string node::get_user_language()
   {

      //#ifdef UNIVERSAL_WINDOWS
      //
      //      string_array_base stra;
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

      string strIso = ::windows::langid_to_iso(langid);

      //#endif
      string strUserlanguage = strIso;

      return strUserlanguage;

   }


   ::pointer < security_attributes > node::get_application_exclusivity_security_attributes()
   {

      bool bSetOk = false;

      auto psecurityattributes = øcreate_new<::acme_windows_common::security_attributes>();

      psecurityattributes->m_memory.set_size(sizeof(SECURITY_ATTRIBUTES) + sizeof(SECURITY_DESCRIPTOR));

      auto pSecurityAttributes = (LPSECURITY_ATTRIBUTES)psecurityattributes->get_os_security_attributes();

      ZeroMemory(pSecurityAttributes, sizeof(*pSecurityAttributes));

      pSecurityAttributes->nLength = sizeof(*pSecurityAttributes);

      pSecurityAttributes->bInheritHandle = false; // object uninheritable

      // declare and initialize a security descriptor
      auto pSecurityDescriptor = (SECURITY_DESCRIPTOR*)(pSecurityAttributes + 1);

      bool bInitializeOk = InitializeSecurityDescriptor(pSecurityDescriptor, SECURITY_DESCRIPTOR_REVISION) != false;

      if (bInitializeOk)
      {
         // give the security descriptor a Null Dacl
         // done using the  "true, (PACL)nullptr" here
         bSetOk = SetSecurityDescriptorDacl(pSecurityDescriptor,
            true,
            (PACL)nullptr,
            false) != false;

      }

      if (bSetOk)
      {

         pSecurityAttributes->lpSecurityDescriptor = pSecurityDescriptor;

      }
      else
      {

         psecurityattributes->m_memory.set_size(0);

      }

      return psecurityattributes;

   }


   void node::register_spa_file_type(const ::scoped_string & scopedstrAppIdHandler)
   {

#ifdef WINDOWS_DESKTOP

      HKEY hkey;

      wstring extension = L".spa";                     // file extension
      wstring desc = L"spafile";          // file type description
      wstring content_type = L"application/x-spa";

      wstring app(directory_system()->stage(scopedstrAppIdHandler, process_platform_name(), process_configuration_name()));

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
      RegSetValueExW(hkey, L"", 0, REG_SZ, (unsigned char*)desc.c_str(), unsigned int(desc.length() * sizeof(wchar_t))); // default vlaue is description of file extension
      RegSetValueExW(hkey, L"ContentType", 0, REG_SZ, (unsigned char*)content_type.c_str(), unsigned int(content_type.length() * sizeof(wchar_t))); // default vlaue is description of file extension
      RegCloseKey(hkey);



      // 2: Create Subkeys for action ( "Open with my program" )
      // HKEY_CLASSES_ROOT\.002\Shell\\open with my program\\command
      if (RegCreateKeyExW(HKEY_CLASSES_ROOT, path.c_str(), 0, 0, 0, KEY_ALL_ACCESS, 0, &hkey, 0) != ERROR_SUCCESS)
      {
         output_debug_string("Could not create or open a registrty key\n");
         throw ::exception(error_resource);
      }
      RegSetValueExW(hkey, L"", 0, REG_SZ, (unsigned char*)app.c_str(), unsigned int(app.length() * sizeof(wchar_t)));
      RegCloseKey(hkey);


      path = L"spafile\\DefaultIcon";

      if (RegCreateKeyExW(HKEY_CLASSES_ROOT, path.c_str(), 0, 0, 0, KEY_ALL_ACCESS, 0, &hkey, 0) != ERROR_SUCCESS)
      {
         output_debug_string("Could not create or open a registrty key\n");
         throw ::exception(error_resource);
      }
      RegSetValueExW(hkey, L"", 0, REG_SZ, (unsigned char*)icon.c_str(), unsigned int(icon.length() * sizeof(wchar_t)));
      RegCloseKey(hkey);

      ::file::path pathFile(directory_system()->stage(scopedstrAppIdHandler, process_platform_name(), process_configuration_name()) / "spa_register.txt");

      int iRetry = 9;

      while (!file_system()->exists(pathFile) && iRetry > 0)
      {

         directory_system()->create(pathFile.folder());

         file_system()->put_contents(pathFile, "");

         iRetry--;

         sleep(100_ms);

      }

#endif

      //return true;

   }


   void node::start_program_files_app_app_admin(const ::scoped_string & scopedstrPlatform, const ::scoped_string & scopedstrConfiguration)
   {

#ifdef WINDOWS_DESKTOP

      SHELLEXECUTEINFOW sei = {};

      string str = directory_system()->app_app_admin(scopedstrPlatform, scopedstrConfiguration);

      if (!file_system()->exists(str))
      {

         throw ::exception(error_failed);

      }

      throw ::exception(error_failed);

      //::install::admin_mutex mutexStartup(this, "-startup");

      //wstring wstr(str);

      //sei.cbSize = sizeof(SHELLEXECUTEINFOW);
      //sei.fMask = SEE_MASK_NOASYNC | SEE_MASK_NOCLOSEPROCESS;
      //sei.lpVerb = L"RunAs";

      //sei.lpFile = wstr.c_str();

      //::ShellExecuteExW(&sei);

      //DWORD dwGetLastError = GetLastError();

#endif

      //return ::success;

   }


   void node::get_folder_path_from_user(::file::path& pathFolder)
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

         throw ::exception(estatus);


      }

      //return ::success;

   }



   HICON node::extract_icon(HINSTANCE hInst, const ::scoped_string & scopedstrExeFileName, unsigned int nIconIndex)

   {

      return ::ExtractIconW(hInst, utf8_to_unicode(scopedstrExeFileName), nIconIndex);


   }


   int node::reg_query_value(HKEY hkey, const ::scoped_string & scopedstrSubKey, string& str)
   {

      DWORD dwType = 0;
      DWORD dwSize = 0;
      int lResult = RegQueryValueExW(hkey, wstring(scopedstrSubKey), nullptr, &dwType, nullptr, &dwSize);

      if (lResult != ERROR_SUCCESS)
         return lResult;
      ASSERT(dwType == REG_SZ || dwType == REG_MULTI_SZ || dwType == REG_EXPAND_SZ);
      if (dwType == REG_SZ || dwType == REG_MULTI_SZ || dwType == REG_EXPAND_SZ)
      {

         wstring wstr;

         auto pwsz = wstr.get_buffer(dwSize);

         lResult = RegQueryValueExW(hkey, wstring(scopedstrSubKey), nullptr, &dwType, (unsigned char*)(unichar*)pwsz, &dwSize);

         wstr.release_buffer(dwSize);

         str = wstr;

         //str.release_buffer(dwSize);

         return lResult;

      }
      else
      {

         return ERROR_NOT_SUPPORTED;

      }

   }


   //HICON node::extract_icon(HINSTANCE hInst, const ::scoped_string & scopedstrExeFileName, unsigned int nIconIndex)

   //{

   //   return ::ExtractIconW(hInst, utf8_to_unicode(pszExeFileName), nIconIndex);


   //}


   void node::delete_file(const ::file::path& pathParam)
   {

      auto path = m_papplication->defer_process_path(pathParam);

      ::delete_file(path);

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

      //if (!call_sync(path, strParam, path.folder(), ::e_display_none, 3_minute, set))
      int iExitCode = -1;
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

      //return true;

   }


   //::string node::expand_environment_variables(const ::scoped_string & scopedstr)
   //{

   //   wstring wstrSource(str);

   //   wstring wstrTarget = expand_environment_variables(wstrSource);

   //   return wstrTarget;

   //}


   ::wstring node::expand_environment_variables(const ::wstring& wstr)
   {

      DWORD dwCharLen = ::ExpandEnvironmentStringsW(wstr, nullptr, 0);

      wstring wstrTarget;

      if (dwCharLen)
      {

         auto pwsz = wstrTarget.get_buffer(dwCharLen);

         ::ExpandEnvironmentStringsW(wstr, pwsz, dwCharLen + 1);

         wstrTarget.release_buffer();

      }

      return wstrTarget;

   }


   //void node::implement(::pointer<::platform::node> & pnode, ::pointer<::platform::system> & psystem)
   void node::node_main()
   {

      return ::platform::node::node_main();

   }


   void node::on_start_system()
   {

      ::platform::node::on_start_system();


      //auto estatus = system()->post_initial_request();

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //return estatus;

   }


   void node::create_app_shortcut(::platform::application* papp)
   {

   }


   void node::open_internet_link(const ::scoped_string& scopedstrUrl, const ::scoped_string& scopedstrProfile, const ::scoped_string& scopedstrTarget)
   {

      //#ifdef DEBUG
      //
      //      ::string_array_base straOutput;
      //
      //      int iExitCode = 0;
      //
      //      command_system(straOutput, iExitCode, "\"C:\\Program Files\\Google\\Chrome\\Application\\chrome.exe\" \"" + strUrl + "\" --auto-open-devtools-for-tabs");
      //
      //#else

      wstring wstrUrl(scopedstrUrl);

      ::ShellExecuteW(nullptr, L"open", wstrUrl, nullptr, nullptr, SW_SHOWNORMAL);

      //#endif

   }


   void node::shell_launch(const ::scoped_string & scopedstrUrl)
   {

      wstring wstrUrl(scopedstrUrl);

      ::ShellExecuteW(nullptr, L"open", wstrUrl, nullptr, nullptr, SW_SHOWNORMAL);

   }


   long long node::current_process_identifier()
   {

      return ::GetCurrentProcessId();

   }



   bool node::stdin_has_input_events()
   {

      HANDLE handleStdin = ::GetStdHandle(STD_INPUT_HANDLE);

      DWORD dwNumberOfEvents = 0;

      if (!GetNumberOfConsoleInputEvents(handleStdin, &dwNumberOfEvents))
      {

         return false;

      }

      return dwNumberOfEvents > 0;

   }


   void node::flush_stdin_input_events()
   {

      HANDLE handleStdin = ::GetStdHandle(STD_INPUT_HANDLE);

      ::FlushConsoleInputBuffer(handleStdin);

   }


   void node::flush_stdin()
   {

      while (stdin_has_input_events())
      {

         flush_stdin_input_events();

      }

   }


   //void node::defer_initialize_callstack()
   //{

   //   critical_section_lock synchronouslock(sym_dbg_help_critical_section());

   //   auto process = GetCurrentProcess();

   //   if (!m_bInitializeCallstack)
   //   {

   //      m_bInitializeCallstack = true;

   //      SymSetOptions(SymGetOptions() | SYMOPT_LOAD_LINES);

   //      SymInitialize(process, NULL, TRUE);

   //   }
   //   else
   //   {

   //      SymRefreshModuleList(process);

   //   }

   //}


   ::string node::get_command_line()
   {

      return ::GetCommandLineW();

   }


   ::pointer < ::acme::exclusive > node::_get_exclusive(::particle* pparticleContext, const ::scoped_string & scopedstrName, ::security_attributes* psecurityattributes)
   {

      return øallocate exclusive(pparticleContext, scopedstrName, psecurityattributes);

   }


   //void node::command_system(string_array_base & straOutput, int & iExitCode, const scoped_string & scopedstr, enum_command_system ecommandsystem, const class time & timeTimeout, ::particle * pparticleSynchronization, ::file::file * pfileLines)
   //{

   //   //straOutput.clear();

   //   string str(scopedstr);

   //   wstring wstr;

   //   wstr = str;

   //   STARTUPINFO si = { sizeof(si) };
   //   PROCESS_INFORMATION pi = {};
   //   SECURITY_ATTRIBUTES saAttr;

   //   ZeroMemory(&saAttr, sizeof(saAttr));

   //   saAttr.nLength = sizeof(SECURITY_ATTRIBUTES);
   //   saAttr.bInheritHandle = TRUE;
   //   saAttr.lpSecurityDescriptor = NULL;

   //   HANDLE hOutRd;
   //   HANDLE hOutWr;

   //   // Create a pipe for the child process's STDOUT. 

   //   if (!CreatePipe(&hOutRd, &hOutWr, &saAttr, 0))
   //   {

   //      // log error
   //      DWORD dwLastError = GetLastError();

   //      auto estatus = ::windows::last_error_status(dwLastError);

   //      throw ::exception(estatus);

   //   }

   //   // Ensure the read handle to the pipe for STDOUT is not inherited.
   //   if (!SetHandleInformation(hOutRd, HANDLE_FLAG_INHERIT, 0))
   //   {

   //      ::CloseHandle(hOutRd);
   //      ::CloseHandle(hOutWr);

   //      // log error
   //      DWORD dwLastError = GetLastError();

   //      auto estatus = ::windows::last_error_status(dwLastError);

   //      throw ::exception(estatus);

   //   }

   //   HANDLE hErrRd;
   //   HANDLE hErrWr;

   //   // Create a pipe for the child process's STDOUT. 

   //   if (!CreatePipe(&hErrRd, &hErrWr, &saAttr, 0))
   //   {

   //      ::CloseHandle(hOutRd);
   //      ::CloseHandle(hOutWr);

   //      // log error
   //      DWORD dwLastError = GetLastError();

   //      auto estatus = ::windows::last_error_status(dwLastError);

   //      throw ::exception(estatus);

   //   }


   //   // Ensure the read handle to the pipe for STDOUT is not inherited.
   //   if (!SetHandleInformation(hErrRd, HANDLE_FLAG_INHERIT, 0))
   //   {

   //      ::CloseHandle(hOutRd);
   //      ::CloseHandle(hOutWr);
   //      ::CloseHandle(hErrRd);
   //      ::CloseHandle(hErrWr);

   //      // log error
   //      DWORD dwLastError = GetLastError();

   //      auto estatus = ::windows::last_error_status(dwLastError);

   //      throw ::exception(estatus);

   //   }

   //   {

   //      DWORD dwState = PIPE_NOWAIT;

   //      SetNamedPipeHandleState(hOutRd, &dwState, nullptr, nullptr);

   //   }

   //   {

   //      DWORD dwState = PIPE_NOWAIT;

   //      SetNamedPipeHandleState(hErrRd, &dwState, nullptr, nullptr);

   //   }

   //   ZeroMemory(&si, sizeof(si));
   //   si.cb = sizeof(si);
   //   si.hStdError = hErrWr;
   //   si.hStdOutput = hOutWr;
   //   si.dwFlags |= STARTF_USESTDHANDLES;

   //   ZeroMemory(&pi, sizeof(pi));

   //   if (!CreateProcessW(nullptr, wstr, NULL, NULL, TRUE, CREATE_NO_WINDOW, NULL, NULL, &si, &pi))
   //   {

   //      ::CloseHandle(hOutRd);
   //      ::CloseHandle(hOutWr);
   //      ::CloseHandle(hErrRd);
   //      ::CloseHandle(hErrWr);

   //      DWORD dwLastError = ::GetLastError();

   //      auto estatus = ::windows::last_error_status(dwLastError);

   //      throw ::exception(estatus);

   //   }

   //   class ::time timeStart;

   //   timeStart.Now();

   //   string strError;

   //   string strOutput;

   //   single_lock sl(pparticleSynchronization);

   //   while (true)
   //   {

   //      auto result = WaitForSingleObject(pi.hProcess, 100);

   //      char sz[256];

   //      while (true)
   //      {

   //         DWORD dwRead = 0;

   //         if (!ReadFile(hOutRd, sz, 256, &dwRead, nullptr))
   //         {

   //            break;

   //         }

   //         if (dwRead == 0)
   //         {

   //            break;

   //         }

   //         string str(sz, dwRead);

   //         if (ecommandsystem & e_command_system_inline_log)
   //         {

   //            fprintf(stdout, "%s", str.c_str());

   //            fflush(stdout);

   //         }

   //         strOutput += str;

   //         ::str().get_lines(straOutput, strOutput, "I: ", false, &sl, pfileLines);

   //      };

   //      while (true)
   //      {

   //         DWORD dwRead = 0;

   //         if (!ReadFile(hErrRd, sz, 256, &dwRead, nullptr))
   //         {

   //            break;

   //         }

   //         if (dwRead == 0)
   //         {

   //            break;

   //         }

   //         string str(sz, dwRead);

   //         if (ecommandsystem & e_command_system_inline_log)
   //         {

   //            fprintf(stderr, "%s", str.c_str());

   //            fflush(stderr);

   //         }

   //         strError += str;

   //         ::str().get_lines(straOutput, strError, "E: ", false, &sl, pfileLines);

   //      };

   //      if (result == WAIT_OBJECT_0)
   //      {

   //         break;

   //      }

   //      if (!timeTimeout.is_infinite() && timeStart.elapsed() > timeTimeout)
   //      {

   //         break;

   //      }

   //   }

   //   DWORD dwExitCode = 0;

   //   if (GetExitCodeProcess(pi.hProcess, &dwExitCode))
   //   {

   //      iExitCode = dwExitCode;

   //   }

   //   ::CloseHandle(hOutRd);
   //   ::CloseHandle(hOutWr);
   //   ::CloseHandle(hErrRd);
   //   ::CloseHandle(hErrWr);

   //   ::CloseHandle(pi.hProcess);
   //   ::CloseHandle(pi.hThread);

   //   ::str().get_lines(straOutput, strOutput, "I: ", true, &sl, pfileLines);
   //   ::str().get_lines(straOutput, strError, "E: ", true, &sl, pfileLines);

   //}


   int node::command_system(const ::scoped_string& scopedstr, const ::trace_function& tracefunction, const ::file::path& pathWorkingDirectory, ::e_display edisplay)
   {

      auto pcreateprocess = øcreate_new < ::acme_windows::create_process>();

      pcreateprocess->m_pathWorkingDirectory = pathWorkingDirectory;

      pcreateprocess->m_edisplay = edisplay;

      pcreateprocess->initialize_stdout();
      pcreateprocess->initialize_stderr();
      pcreateprocess->initialize_stdin();

      pcreateprocess->prepare();

      if (edisplay == e_display_up)
      {

         pcreateprocess->set_create_new_console();

      }

      //pcreateprocess->set_create_new_console();
      pcreateprocess->call_create_process(scopedstr);
      //string str(scopedstr);


      //::string str1;
      //auto range = str();
      //range.m_erange = e_range_none;
      //try
      //{
      //   str1 = range.consume_quoted_value();

      //}
      //catch (...)
      //{


      //}
      //::string str2;
      //if (str1.is_empty())
      //{
      //   ::string strCmd = this->get_environment_variable("ComSpec");
      //   str1 = strCmd;
      //   str2 = "\"" + strCmd + "\" /c \"" + scopedstr + "\"";
      //}
      //else
      //{

      //   str2 = scopedstr;
      //   str2.trim();
      //}

      //wstring wstr1;
      //wstring wstr2;

      //wstr1 = str1;
      //wstr2 = str2;



      //if (!CreateProcessW(
      //   (WCHAR *)wstr1.c_str(), (WCHAR*)wstr2.c_str(), 
      //   NULL, NULL, TRUE, EXTENDED_STARTUPINFO_PRESENT | CREATE_NEW_CONSOLE, NULL, NULL,
      //   &pcreateprocess->m_si.StartupInfo, &pcreateprocess->m_pi))
      //{

      //   //::CloseHandle(hOutRd);
      //   //::CloseHandle(hOutWr);
      //   //::CloseHandle(hErrRd);
      //   //::CloseHandle(hErrWr);
      //   //::CloseHandle(hInRd);
      //   //::CloseHandle(hInWr);

      //   DWORD dwLastError = ::GetLastError();

      //   printf("Create Process failed with lasterror = %d\n", dwLastError);
      //   printf("Parameters: %s %s\n", str1.c_str(), str2.c_str());

      //   auto estatus = ::windows::last_error_status(dwLastError);

      //   throw ::exception(estatus);

      //}


//      class ::time timeStart;

  //    timeStart.Now();

      pcreateprocess->wait_process(tracefunction);

      //      return iExitCode;

      return pcreateprocess->m_iExitCode;

   }


   void node::launch_command_system(const ::scoped_string& scopedstr, const ::file::path& pathWorkingDirectory, ::e_display edisplay)
   {

      auto pcreateprocess = øcreate_new < ::acme_windows::create_process>();


      pcreateprocess->m_pathWorkingDirectory = pathWorkingDirectory;

      pcreateprocess->m_edisplay = edisplay;

      pcreateprocess->prepare();

      pcreateprocess->set_create_new_console();

      pcreateprocess->call_create_process(scopedstr);

   }


   int node::synchronous_posix_terminal(const ::scoped_string& scopedstrCommand, enum_posix_shell eposixshell , const trace_function& tracefunction)
   {

      ::file::path pathGitBash = "C:/Program Files/Git/git-bash.exe";

      ::string strGitBash(pathGitBash);

      strGitBash.double_quote();

      ::string strCommand(pathGitBash);

      strCommand.double_quote(true);

      ::string strParameters;

      strParameters = " -i -c " + scopedstrCommand.double_quoted(true);

      int iExitCode = command_system(strGitBash + strParameters, tracefunction);

      return iExitCode;

   }


   bool node::has_command(const ::scoped_string& scopedstrCommand)
   {

      ::string strOutput;

      int iExitCode = get_command_output(strOutput, "WHERE " + scopedstrCommand);

      strOutput.trim();

      if (!file_system()->exists(strOutput))
      {

         return false;

      }

      return true;

   }


   int node::command(const ::scoped_string& scopedstrCommand, const trace_function& tracefunction)
   {

      try
      {

         //string strEscaped = scopedstrCommand;

         //::string strCommand;

         //informationf("Current Directory: %s\n", directory_system()->get_current().c_str());
         //informationf("%s\n", strEscaped.c_str());

         ////if (m_bMsys)
         ////{

         ////   strCommand = "\"C:\\msys64\\usr\\bin\\bash.exe\" -c \'" + strEscaped + "\'";

         ////}
         ////else
         //{

         //   strCommand = "\"cmd.exe\" /c " + strEscaped;

         //}

         ////

         auto iExitCode = this->command_system(scopedstrCommand, tracefunction);

         ///command_system("cmd.exe -c \"C:\\msys64\\msys2_shell.cmd\" \"" + strEscaped + "\"");

         return iExitCode;

      }
      catch (...)
      {

      }

      return -1;

   }



   //int node::command_system(const ::scoped_string& scopedstr, const class ::time& timeOut)
   //{


   //   //class ::time timeStart;

   //   //timeStart.Now();


   //   while (::task_get_run())
   //   {

   //      auto result = WaitForSingleObject(m_pi.hProcess, 100);

   //      if (result == WAIT_OBJECT_0)
   //      {

   //         break;

   //      }

   //      if (
   //         !timeOut.is_infinite()
   //         && timeStart.elapsed() > timeOut)
   //      {

   //         break;

   //      }

   //   }



   //   ////single_lock sl(pparticleSynchronization);

   //   //while (true)
   //   //{


   //   //   while (true)
   //   //   {

   //   //      DWORD dwRead = 0;

   //   //      if (!ReadFile(hErrRd, sz, 256, &dwRead, nullptr))
   //   //      {

   //   //         break;

   //   //      }

   //   //      if (dwRead == 0)
   //   //      {

   //   //         break;

   //   //      }

   //   //      string str(sz, dwRead);

   //   //      strError += str;

   //   //      if (tracefunction)
   //   //      {

   //   //         ::str::get_lines(strError, false, [&](auto & str)
   //   //            {

   //   //                  tracefunction(e_trace_level_error, str);

   //   //            });

   //   //      }


   //   //      //if (ecommandsystem & e_command_system_inline_log)
   //   //      //{

   //   //      //   fprintf(stderr, "%s", str.c_str());

   //   //      //   fflush(stderr);

   //   //      //}

   //   //      //strError += str;

   //   //      //::str().get_lines(straOutput, strError, "E: ", false, &sl, pfileLines);

   //   //   };



   //   //}

   //   DWORD dwExitCode = 0;

   //   int iExitCode = 0;

   //   if (GetExitCodeProcess(pi.hProcess, &dwExitCode))
   //   {

   //      iExitCode = dwExitCode;

   //   }



   //   ::CloseHandle(pi.hProcess);
   //   ::CloseHandle(pi.hThread);

   //   return iExitCode;

   //}


   //void node::open_terminal_and_run(const ::scoped_string& scopedstr)
   //{

   //   ::file::path pathCurrentDirectory;

   //   pathCurrentDirectory = directory_system()->get_current();

   //   auto windowspathCurrentDirectory = pathCurrentDirectory.windows_path();

   //   ::wstring wstrCurrentDirectory;

   //   wstrCurrentDirectory = windowspathCurrentDirectory;

   //   ::wstring wstrParameters;

   //   wstrParameters = L"/c ";

   //   wstrParameters += ::wstring(scopedstr);

   //   auto iResult = (INT_PTR) ::ShellExecuteW(nullptr, L"open", L"cmd.exe", wstrParameters, wstrCurrentDirectory, SW_SHOW);

   //   DWORD dw = ::GetLastError();

   //   if (iResult >= 32)
   //   {

   //      information() << "ShellExecuteW \"" + scopedstr + "\" succeeded : " << iResult;

   //   }
   //   else
   //   {

   //      information() << "ShellExecuteW \"" + scopedstr + "\" failed : " << iResult;

   //   }

   //}


   unsigned long long node::translate_processor_affinity(int iOrder)
   {

      DWORD_PTR dwProcessAffinityMask;
      DWORD_PTR dwSystemAffinityMask;
      if (!GetProcessAffinityMask(::GetCurrentProcess(), &dwProcessAffinityMask, &dwSystemAffinityMask))
      {
         return 0;
      }
      int j = 0;
      uptr dwMask = 1;
      for (int i = 0; i < sizeof(dwProcessAffinityMask) * 8; i++)
      {
         if ((dwMask & dwProcessAffinityMask) != 0)
         {
            if (iOrder == j)
            {
               return dwMask;
            }
            j++;
         }
         dwMask = dwMask << 1;
      }

      return 0;

   }


   int node::get_current_process_affinity_order()
   {


      DWORD_PTR dwProcessAffinityMask;
      DWORD_PTR dwSystemAffinityMask;

      if (!GetProcessAffinityMask(::GetCurrentProcess(), &dwProcessAffinityMask, &dwSystemAffinityMask))
      {

         return 0;

      }

      int iCount = 0;
      uptr dwMask = 1;
      for (int i = 0; i < sizeof(dwProcessAffinityMask) * 8; i++)
      {
         if ((dwMask & dwProcessAffinityMask) != 0)
         {
            iCount++;
         }
         dwMask = dwMask << 1;
      }

      return iCount;

   }


   int node::get_current_process_maximum_affinity()
   {

      DWORD_PTR dwProcessAffinityMask;
      DWORD_PTR dwSystemAffinityMask;
      if (!GetProcessAffinityMask(::GetCurrentProcess(), &dwProcessAffinityMask, &dwSystemAffinityMask))
      {
         return 0;
      }
      int iMax = -1;
      uptr dwMask = 1;
      for (int i = 0; i < sizeof(dwProcessAffinityMask) * 8; i++)
      {
         if ((dwMask & dwProcessAffinityMask) != 0)
         {
            iMax = i;
         }
         dwMask = dwMask << 1;
      }

      return iMax;

   }


   int node::get_current_processor_index()
   {


      return ::GetCurrentProcessorNumber();


   }


   bool node::set_process_priority(::enum_priority epriority)
   {

      return (::SetPriorityClass(::GetCurrentProcess(), get_os_priority_class(epriority)) != 0);


   }


   void node::shell_execute_async(const scoped_string& scopedstrFile, const scoped_string& scopedstrParams, const ::file::path& pathWorkingDirectory)
   {

      shell_execute execute(scopedstrFile, scopedstrParams, pathWorkingDirectory);

      execute.async();

   }


   int node::shell_execute_sync(const scoped_string& scopedstrFile, const scoped_string& scopedstrParams, const class time& timeTimeout, const ::file::path& pathWorkingDirectory)
   {

      shell_execute execute(scopedstrFile, scopedstrParams, pathWorkingDirectory);

      DWORD dwExitCode = 0;

      if (!execute.synchronization_object(timeTimeout, dwExitCode))
      {

         throw ::exception(error_failed);

      }

      return dwExitCode;

   }


   void node::root_execute_async(const scoped_string& scopedstrFile, const scoped_string& scopedstrParams, const ::file::path& pathWorkingDirectory)
   {

      shell_execute execute(scopedstrFile, scopedstrParams, pathWorkingDirectory);

      execute.lpVerb = L"RunAs";

      execute.async();

   }


   int node::root_execute_sync(const scoped_string& scopedstrFile, const scoped_string& scopedstrParams, const class time& timeTimeout, const ::file::path& pathWorkingDirectory)
   {

      shell_execute execute(scopedstrFile, scopedstrParams, pathWorkingDirectory);

      execute.lpVerb = L"RunAs";

      DWORD dwExitCode = 0;

      if (!execute.synchronization_object(timeTimeout, dwExitCode))
      {

         throw ::exception(error_failed);

      }

      return dwExitCode;

   }


   void node::call_async(const ::scoped_string & scopedstrPath, const ::scoped_string & scopedstrParam, const ::scoped_string & scopedstrDir, ::e_display edisplay, bool bPrivileged, unsigned int* puiPid)
   {

      SHELLEXECUTEINFOW info = {};

      wstring wstrFile = scopedstrPath;
      wstring wstrParam = scopedstrParam;
      wstring wstrDir =scopedstrDir;

      info.cbSize = sizeof(SHELLEXECUTEINFOW);

      if (edisplay == e_display_default)
      {
         info.nShow = SW_SHOWDEFAULT;
      }
      else
      {
         info.nShow = is_visible(edisplay) ? SW_NORMAL : SW_HIDE;

      }
      info.lpFile = wstrFile;
      info.lpParameters = wstrParam;
      info.lpDirectory = wstrDir;


      if (bPrivileged)
      {

         info.lpVerb = L"RunAs";


      }

      if (puiPid != nullptr)
      {

         info.fMask |= SEE_MASK_NOCLOSEPROCESS;

      }

      info.fMask |= SEE_MASK_FLAG_NO_UI;

      int iOk = ::ShellExecuteExW(&info);

      if (puiPid != nullptr)
      {

         *puiPid = ::GetProcessId(info.hProcess);

         ::CloseHandle(info.hProcess);

      }

      int iSeResult = (int)(iptr)info.hInstApp;

      if (iSeResult < 32)
      {

         DWORD dwError = ::GetLastError();

         auto estatus = ::windows::last_error_status(dwError);

         throw ::exception(estatus);

      }

      //return ::success;

   }


   void node::call_sync(const ::scoped_string & scopedstrPath, const ::scoped_string & scopedstrParam, const ::scoped_string & scopedstrDir, ::e_display edisplay, const class time& timeTimeout, ::property_set & set, int* piExitCode)
   {

      SHELLEXECUTEINFOW infoa;

      memory_set(&infoa, 0, sizeof(infoa));

      wstring wstrFile(scopedstrPath);
      wstring wstrParam(scopedstrParam);
      wstring wstrDir(scopedstrDir);

      infoa.cbSize = sizeof(infoa);
      infoa.lpFile = wstrFile;

      infoa.lpParameters = wstrParam;

      infoa.lpDirectory = wstrDir;

      infoa.nShow = is_visible(edisplay) ? SW_NORMAL : SW_HIDE;

      infoa.fMask |= SEE_MASK_NOCLOSEPROCESS | SEE_MASK_NOASYNC | SEE_MASK_FLAG_NO_UI;

      if (set.is_true("privileged"))
      {

         infoa.lpVerb = L"RunAs";

      }

      if (!::ShellExecuteExW(&infoa))
      {

         auto lasterror = ::GetLastError();

         auto estatus = ::windows::last_error_status(lasterror);

         throw ::exception(estatus);

      }

      set["pid"] = (unsigned int) ::GetProcessId(infoa.hProcess);

      DWORD dwExitCode = (DWORD)-1;

      class ::time timeStart;

      timeStart.Now();

      while (::task_get_run())
      {
         // Thanks from Blehman@Twitch from Slovakia through Googling...
         // 2020-02-19
         if (WaitForSingleObject(infoa.hProcess, 200) == WAIT_OBJECT_0)
         {

            break;

         }

         if (timeStart.elapsed() > timeTimeout)
         {

            set["timed_out"] = true;

            break;

         }

      }

      GetExitCodeProcess(infoa.hProcess, &dwExitCode);

      if (set.is_true("timed_out"))
      {

         if (set.is_true("terminate_on_timeout"))
         {

            auto TerminateProcess_return = ::TerminateProcess(infoa.hProcess, -1);
            auto TerminateProcess_GetLastError = ::GetLastError();

            set["TerminateProcess_return"] = TerminateProcess_return;
            set["TerminateProcess_GetLastError"] = (unsigned int)TerminateProcess_GetLastError;

         }

      }

      ::CloseHandle(infoa.hProcess);

      int iExitCode = dwExitCode;

      if (::is_set(piExitCode))
      {

         *piExitCode = iExitCode;

      }

      //if (iExitCode == 0)
      //{

      //   //return ::success;

      //   return;

      //}
      //else if(iExitCode > 0)
      //{
      // 
      //   return e_status_process_result_positive_base + iExitCode;

      //}
      //else
      //{

      //   return e_status_process_result_negative_base + iExitCode;

      //}

   }


   void node::launch_application(::particle* pparticle, const ::scoped_string & scopedstrAppId, const ::scoped_string & scopedstrParams, int iBitCount)
   {


   }




   ::string node::registry_environment_variable_to_system(const ::scoped_string& scopedstr)
   {

      if (scopedstr.case_insensitive_equals("path"))
      {

         return "PATH";

      }

      return scopedstr;

   }


   ::string node::system_environment_variable_to_registry(const ::scoped_string& scopedstr)
   {

      if (scopedstr.case_insensitive_equals("path"))
      {

         return "Path";

      }

      return scopedstr;

   }


   int node::environment_variable_registry_payload_type(const ::scoped_string& scopedstr)
   {

      if (scopedstr.case_insensitive_equals("path"))
      {

         return REG_EXPAND_SZ;

      }

      return REG_SZ;

   }


   ::string node::get_user_permanent_environment_variable(const ::scoped_string& scopedstr)
   {

      ::acme_windows::registry::key key(HKEY_CURRENT_USER, "Environment");

      string strName = system_environment_variable_to_registry(scopedstr);

      ::string str;

      if (!key.get(strName, str))
      {

         return {};

      }

      return str;

   }


   ::string node::get_system_permanent_environment_variable(const ::scoped_string& scopedstr)
   {

      ::acme_windows::registry::key key(HKEY_LOCAL_MACHINE, "SYSTEM\\CurrentControlSet\\Control\\Session Manager\\Environment");

      string strName = system_environment_variable_to_registry(scopedstr);

      ::string str;

      if (!key.get(strName, str))
      {

         return {};

      }

      return str;

   }


   void node::set_user_permanent_environment_variable(const ::scoped_string& scopedstr, const ::scoped_string& scopedstrPayload, bool bNoSystemNotify)
   {

      ::acme_windows::registry::key key(HKEY_CURRENT_USER, "Environment");

      string strName = system_environment_variable_to_registry(scopedstr);

      if (strName.is_empty())
      {

         throw ::exception(error_failed);

      }

      int iPayloadType = environment_variable_registry_payload_type(strName);

      key.set(strName, scopedstrPayload, iPayloadType);

      if (!bNoSystemNotify)
      {

         system_notify_environment_variable_change();

      }

   }


   void node::system_notify_environment_variable_change()
   {

      DWORD_PTR dwptrResult = 0;

      ::SendMessageTimeoutW(HWND_BROADCAST, WM_SETTINGCHANGE,
         0, (LPARAM)L"Environment",
         SMTO_ABORTIFHUNG | SMTO_NOTIMEOUTIFNOTHUNG, 10000, &dwptrResult);

      ::preempt(10_s);

   }


   void node::_update_process_environment_variable(const ::scoped_string& scopedstr)
   {

      auto strUser = get_user_permanent_environment_variable(scopedstr);

      auto strSystem = get_system_permanent_environment_variable(scopedstr);

      ::string str;

      if (scopedstr == "PATH")
      {

         if (strUser.has_character())
         {

            if (strSystem.has_character())
            {

               str = strUser + ";" + strSystem;

            }
            else
            {

               str = strUser;

            }

         }
         else
         {

            str = strSystem;

         }

      }
      else
      {

         if (strUser.has_character())
         {

            str = strUser;

         }
         else
         {

            str = strSystem;

         }

      }

      ::string strCurrent = get_environment_variable(scopedstr);

      if (strCurrent != str)
      {

         ::wstring wstrKey(scopedstr);

         ::wstring wstr(str);

         wstr = expand_environment_variables(wstr);

         SetEnvironmentVariableW(wstrKey, wstr);

      }

   }


   void node::update_process_environment_variables()
   {

      _update_process_environment_variable("PATH");

   }


   bool node::_has_beta_use_unicode_utf8()
   {

      ::acme_windows::registry::key key;

      if (!key._open(HKEY_LOCAL_MACHINE, "SYSTEM\\CurrentControlSet\\Control\\Nls\\CodePage"))
      {

         return false;

      }

      {

         ::string str;

         if (!key._get("ACP", str) || str != "65001")
         {

            return false;

         }

      }

      {

         ::string str;

         if (!key._get("OEMCP", str) || str != "65001")
         {

            return false;

         }

      }

      {

         ::string str;

         if (!key._get("MACCP", str) || str != "65001")
         {

            return false;

         }

      }

      return true;

   }

   // https://stackoverflow.com/questions/56419639/what-does-beta-use-unicode-utf-8-for-worldwide-language-support-actually-do
   ::e_status node::_defer_beta_use_unicode_utf8()
   {

      if (_has_beta_use_unicode_utf8())
      {

         return ::success;

      }

      return _beta_use_unicode_utf8();

   }


   ::e_status node::_beta_use_unicode_utf8()
   {

      ::acme_windows::registry::key key;

      if (!key._open(HKEY_LOCAL_MACHINE, "SYSTEM\\CurrentControlSet\\Control\\Nls\\CodePage", true))
      {

         return error_failed;

      }

      try
      {

         key.set("ACP", "65001");
         key.set("OEMCP", "65001");
         key.set("MACCP", "65001");

      }
      catch (...)
      {

         return error_failed;

      }

      return error_need_restart_application_to_activate_feature;

   }


   bool node::_is_visual_studio_installed()
   {

      ::acme_windows::registry::key key;

      if (key._open(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\VisualStudio\\17.0"))
      {

         return true;

      }

      if (key._open(HKEY_LOCAL_MACHINE, "SOFTWARE\\WOW6432Node\\Microsoft\\VisualStudio\\17.0"))
      {

         return true;

      }

      return false;

   }


   bool node::_is_tortoise_git_installed()
   {

      ::acme_windows::registry::key key;

      if (!key._open(HKEY_LOCAL_MACHINE, "SOFTWARE\\TortoiseGit"))
      {

         return false;

      }

      ::string str;

      if (!key._get("Directory", str) || str.is_empty())
      {

         return false;

      }

      return true;

   }


   bool node::_is_smart_git_installed()
   {

      ::acme_windows::registry::key key;

      if (!key._open(HKEY_LOCAL_MACHINE, "SOFTWARE\\SmartGit"))
      {

         return false;

      }

      ::string str;

      if (!key._get("ApplicationName", str) || str.is_empty())
      {

         return false;

      }

      return true;

   }


   bool node::_is_msys2_installed()
   {

      if (!directory_system()->is("C:/msys64"))
      {

         return false;

      }

      return true;

   }


   bool node::has_posix_shell_command(const ::scoped_string& scopedstr, enum_posix_shell eposixshell)
   {

      try
      {

         ::string strCheckCommand;

         strCheckCommand.formatf("command -v %s", scopedstr.as_string().c_str());

         ::string strOutput;

         auto iExitCode = get_posix_shell_command_output(strOutput, strCheckCommand, eposixshell, 1_min);

         return iExitCode == 0 || strOutput.has_character();

      }
      catch (...)
      {

      }

      return false;

   }


   void node::install_posix_shell_command(const ::scoped_string& scopedstr, enum_posix_shell eposixshell, const ::trace_function& tracefunction)
   {

      ::string strOutput;

      if (eposixshell == e_posix_shell_msys2)
      {

         ::string strInstallPackage;

         strInstallPackage = posix_shell_command_install_package(scopedstr, eposixshell);

         ::string strInstallCommand;

         strInstallCommand = "pacman -S --noconfirm " + strInstallPackage;

         posix_shell_command(strInstallCommand, eposixshell, tracefunction);

      }
      else
      {

         ::string strOutput;

         strOutput.formatf("install_posix_shell_command failed for command %s: installation method not standard, inexistent or not implemented for shell %d",
            scopedstr.as_string().c_str(),
            eposixshell);

         tracefunction(e_trace_level_error, strOutput, false);

         throw ::exception(error_failed, strOutput);

      }

      //return strOutput;

   }


   ::string node::posix_shell_command_install_package(const ::scoped_string& scopedstr, enum_posix_shell eposixshell)
   {

      ::string str(scopedstr);

      str.trim();

      str.ends_eat(".exe");

      str.trim();

      str.make_lower();

      if (str == "cmp")
      {

         return "diffutils";

      }

      return ::acme_windows_common::node::posix_shell_command_install_package(scopedstr, eposixshell);

   }


   bool node::_is_strawberry_perl_installed()
   {

      if (!file_system()->exists("C:/Strawberry/perl/bin/perl.exe"))
      {

         return false;

      }

      return true;

   }


   bool node::_is_code_exe_user_path_environment_variable_ok(::string* pstrCorrectPath, const_char_pointer pszPath)
   {

      ::string str;
      
      if (::is_null(pszPath))
      {

         str = get_user_permanent_environment_variable("PATH");

      }
      else
      {

         str = pszPath;

      }

      bool bChanged = false;

      if (!str.case_insensitive_contains("C:\\operating_system\\bin"))
      {

         str += ";C:\\operating_system\\bin";

         bChanged = true;

      }

      if (!str.case_insensitive_contains("C:\\operating_system\\tool-windows\\bin"))
      {

         str += ";C:\\operating_system\\tool-windows\\bin";

         bChanged = true;

      }

      if (!bChanged)
      {

         return true;

      }

      if (::is_set(pstrCorrectPath))
      {

         *pstrCorrectPath = str;

      }

      return false;

   }


   bool node::_is_coder_mode_enabled()
   {

      ::acme_windows::registry::key key;

      if (!key._open(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\AppModelUnlock"))
      {

         return false;

      }

      DWORD dwAllowDevelopmentWithoutDevLicense{};

      if (!key._get("AllowDevelopmentWithoutDevLicense", dwAllowDevelopmentWithoutDevLicense))
      {

         return false;

      }

      return dwAllowDevelopmentWithoutDevLicense != 0;

   }


   void node::_enable_coder_mode(bool bEnable)
   {

      ::acme_windows::registry::key key;

      if (!key._open(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\AppModelUnlock", true))
      {

         throw ::exception(error_failed);

      }

      DWORD dwAllowDevelopmentWithoutDevLicense = bEnable ? 1 : 0;

      key._set("AllowDevelopmentWithoutDevLicense", dwAllowDevelopmentWithoutDevLicense);

      ////if (!key._set("AllowDevelopmentWithoutDevLicense", dwAllowDevelopmentWithoutDevLicense))
      //{

      //   throw ::exception(error_failed);

      //}

      DWORD_PTR dwptrResult = 0;

      ::SendMessageTimeoutW(HWND_BROADCAST, WM_SETTINGCHANGE,
         0, (LPARAM)L"AppModelUnlock",
         SMTO_ABORTIFHUNG | SMTO_NOTIMEOUTIFNOTHUNG, 10000, &dwptrResult);

      ::SendMessageTimeoutW(HWND_BROADCAST, WM_SETTINGCHANGE,
         0, (LPARAM)L"AllowDevelopmentWithoutDevLicense",
         SMTO_ABORTIFHUNG | SMTO_NOTIMEOUTIFNOTHUNG, 10000, &dwptrResult);

      ::preempt(5_s);

      int iExitCode = this->::particle::node()->command_system("gpupdate /force", 5_min);

   }


   void node::set_user_run_once(const ::scoped_string& scopedstrLabel, const ::scoped_string& scopedstrCommand)
   {

      ::acme_windows::registry::key key(HKEY_CURRENT_USER, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\RunOnce");

      key.set(scopedstrLabel, scopedstrCommand);

   }


   //void node::unzip_to_folder(const ::file::path& pathFolder, const ::file::path& pathZip)
   //{

   //   auto strFolderWindowsPath = pathFolder.windows_path();

   //   auto strZipWindowsPath = pathZip.windows_path();

   //   _unzip_to_folder(strZipWindowsPath, strFolderWindowsPath);

   //}


   ////https ://social.msdn.microsoft.com/Forums/vstudio/en-US/45668d18-2840-4887-87e1-4085201f4103/visual-c-to-unzip-a-zip-file-to-a-specific-directory
   //// removed return type and changed error returns to exceptions
   //// replace __try __finally with at_end_of_scope
   //// changed arguments to ansi_character * and used bstring class for string conversion
   //// use of comptr to guard COM objets and variant to guard VARIANTs
   //void node::_unzip_to_folder(const_char_pointer pszZip, const_char_pointer pszFolder)
   //{

   //   comptr < IShellDispatch> pISD;

   //   comptr < Folder> pZippedFile;
   //   comptr < Folder > pDestination;

   //   long FilesCount = 0;
   //   comptr< IDispatch > pItem;
   //   comptr < FolderItems > pFilesInside;

   //   variant Options, OutFolder, InZipFile, Item;

   //   CoInitialize(NULL);

   //   directory_system()->create(pszFolder);


   //   {
   //      // speccylad@twitch contribution recalled
   //      at_end_of_scope
   //      {

   //         CoUninitialize();

   //      };

   //      HRESULT hr = pISD.CoCreateInstance(CLSID_Shell, NULL, CLSCTX_INPROC_SERVER);

   //      defer_throw_hresult(hr);

   //      bstring bstrZip(pszZip);

   //      InZipFile.vt = VT_BSTR;
   //      InZipFile.bstrVal = bstrZip;
   //      pISD->NameSpace(InZipFile, &pZippedFile);
   //      if (!pZippedFile)
   //      {
   //         //pISD->Release();
   //         throw ::exception(error_failed, "pISD->NameSpace(InZipFile, &pZippedFile)");
   //      }

   //      bstring bstrFolder(pszFolder);

   //      OutFolder.vt = VT_BSTR;
   //      OutFolder.bstrVal = bstrFolder;
   //      pISD->NameSpace(OutFolder, &pDestination);
   //      if (!pDestination)
   //      {
   //         //pZippedFile->Release();
   //         //pISD->Release();
   //         throw ::exception(error_failed, "::acme_windows::common::node::_unzip_to_folder (1)");
   //      }

   //      pZippedFile->Items(&pFilesInside);
   //      if (!pFilesInside)
   //      {
   //         //pDestination->Release();
   //         //pZippedFile->Release();
   //         //pISD->Release();
   //         throw ::exception(error_failed, "::acme_windows::common::node::_unzip_to_folder (2)");
   //      }

   //      pFilesInside->get_Count(&FilesCount);
   //      if (FilesCount < 1)
   //      {
   //         //pFilesInside->Release();
   //         //pDestination->Release();
   //         //pZippedFile->Release();
   //         //pISD->Release();
   //         throw ::exception(error_failed, "::acme_windows::common::node::_unzip_to_folder (3)");
   //      }

   //      pFilesInside->QueryInterface(IID_IDispatch, (void**)&pItem);

   //      Item.vt = VT_DISPATCH;
   //      Item.pdispVal = pItem;

   //      Options.vt = VT_I4;
   //      Options.lVal = 1024 | 512 | 16 | 4;//http://msdn.microsoft.com/en-us/library/bb787866(VS.85).aspx

   //      bool retval = pDestination->CopyHere(Item, Options) == S_OK;

   //      //pItem->Release(); pItem = 0L;
   //      //pFilesInside->Release(); pFilesInside = 0L;
   //      //pDestination->Release(); pDestination = 0L;
   //      //pZippedFile->Release(); pZippedFile = 0L;
   //      //pISD->Release(); pISD = 0L;


   //   }

   //}

   ::pointer <::operating_system::summary > node::operating_system_summary()
   {

      _synchronous_lock synchronouslock(this->synchronization());

      if (!m_poperatingsystemsummary)
      {

         auto psummary = øcreate_new < ::operating_system::summary >();

         m_poperatingsystemsummary = psummary;

         psummary->m_strSystem = "windows";
         psummary->m_strSystemBranch = "windows";
         psummary->m_strSystemFamily = "windows";
         psummary->m_strSystemRelease = "10";
         psummary->m_strSystemAmbientRelease = "windows";
         //psummary->m_strSlashedStore = "windows";

      }

      return m_poperatingsystemsummary;


   }

   void node::launch_app(const ::scoped_string & scopedstr, const_char_pointer *argv, int iFlags)
   {

      shell_open(scopedstr);

   }


   ::pointer < ::operating_system::application > node::module_path_application(const ::scoped_string& scopedstr)
   {

      auto papplication = øcreate < ::operating_system::application >();

      papplication->open_by_module_path(scopedstr);

      return papplication;

   }


   ::string node::default_component_implementation(const ::scoped_string& scopedstrComponentName)
   {

      if (scopedstrComponentName == "nano_speech"
         || scopedstrComponentName == "text_to_speech")
      {

         return "sapi";

      }
      else if (scopedstrComponentName == "nano_graphics")
      {

         return "gdi";

      }

      return ::acme_windows_common::node::default_component_implementation(scopedstrComponentName);

   }


   ::string node::operating_system_application_version()
   {

      auto pathModule = file()->module();

      ::wstring wstrModulePath(pathModule);

      DWORD dw;

      unsigned int dwResSize = GetFileVersionInfoSizeW(
         wstrModulePath,
         &dw);


      if (dwResSize > 0)
      {
         memory memory;
         memory.set_size(dwResSize);
         if (GetFileVersionInfoW(
            wstrModulePath,
            0,
            dwResSize,
            memory.data()))
         {
            unsigned int cbTranslate;
            struct LANGANDCODEPAGE
            {
               unsigned short wLanguage;
               unsigned short wCodePage;
            } *lpTranslate;

            // read the list_base of languages and code pages.

            VerQueryValueW(memory.data(),
               TEXT("\\VarFileInfo\\Translation"),
               (LPVOID*)&lpTranslate,
               &cbTranslate);

            wstring wstrKey;
            //for( i=0; i < (cbTranslate/sizeof(struct LANGANDCODEPAGE)); i++ )
            for (int i = 0; i < 1; i++)
            {
               wchar_t* lpwsz;
               unsigned int uSize;

               wstrKey.formatf(
                  TEXT("\\StringFileInfo\\%04x%04x\\FileDescription"),
                  lpTranslate[i].wLanguage,
                  lpTranslate[i].wCodePage);




               wstrKey.formatf(
                  TEXT("\\StringFileInfo\\%04x%04x\\FileVersion"),
                  lpTranslate[i].wLanguage,
                  lpTranslate[i].wCodePage);

               // Retrieve file description for language and code page "i".
               VerQueryValueW(memory.data(),
                  (wchar_t*)(const wchar_t*)wstrKey,
                  (LPVOID*)&lpwsz,
                  &uSize);


               wstring wstrVersion(lpwsz, uSize);

               return wstrVersion;

            }

         }

      }

      return "";

   }


   ::file::path node::_get_power_shell_path()
   {

      registry::key key(HKEY_CLASSES_ROOT, "Microsoft.PowerShellConsole.1");

      ::string str;

      key.get("FriendlyTypeName", str);

      str.begins_eat("@");

      auto r = str();

      ::string str2 = r.consume_quoted_value();

      auto psystem = system();

      auto pnode = psystem->node();

      ::string strPowerShell = pnode->expand_environment_variables(str2);

      return strPowerShell;

   }


   ::file::path node::_get_cmd_path()
   {

      ::string strCmd = get_environment_variable("ComSpec");

      return strCmd;

   }
   
   
   bool node::_is_google_chrome_installed()
   {

      try
      {

         ::acme_windows::registry::key key;

         key.open(HKEY_LOCAL_MACHINE, "Software\\Microsoft\\Windows\\CurrentVersion\\App Paths\\chrome.exe");

         ::string strPath;

         key._get({}, strPath);

         strPath.trim();

         strPath.pair_trim_quotes();

         if (strPath.is_empty() || !file_system()->exists(strPath))
         {

            return false;

         }

         return true;

      }
      catch (...)
      {

      }

      return false;

   }


   bool node::_is_opera_browser_installed()
   {

      try
      {

         ::acme_windows::registry::key key;

         key.open(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\App Paths\\opera.exe");

         ::string strPath;

         key._get({}, strPath);

         strPath.trim();

         strPath.pair_trim_quotes();

         if (strPath.is_empty() || !file_system()->exists(strPath))
         {

            return false;

         }

         return true;

      }
      catch (...)
      {

      }

      return false;

   }


   bool node::_is_visual_studio_code_installed()
   {

      try
      {

         auto pathHome = directory_system()->home();

         auto pathVsLnk = pathHome / "AppData/Roaming/Microsoft/Windows/Start Menu/Programs/Visual Studio Code/Visual Studio Code.lnk";

         if (!file_system()->exists(pathVsLnk))
         {

            return false;

         }

         auto plink = øcreate_new<::acme_windows::file_link>();

         plink->open(pathVsLnk, ::file::e_link_target);

         auto pathTarget = plink->m_pathTarget;

         if (!file_system()->exists(pathTarget))
         {

            return false;

         }

         return true;

      }
      catch (...)
      {


      }

      return false;

   }


   //::file::path node::___fonts_folder()
   //{

   //   WCHAR windir[MAX_PATH];

   //   GetWindowsDirectoryW(windir, MAX_PATH);

   //   ::file::path pathWindows = windir;

   //   auto pathFonts = pathWindows / "Fonts";

   //   return pathFolder;

   //}


   //void node::do_windowing_system_factory()
   //{

   //   auto pfactory = system()->factory("windowing_system", "win32");

   //   pfactory->merge_to_global_factory();

   //}


   bool node::defer_component_factory(const ::scoped_string & scopedstrComponent)
   {

      //if (scopedstrComponent == "nano_graphics")
      //{


      //   auto pfactory = this->factory();

      //   nano_graphics_win32_factory(pfactory);

      //   return true;

      //}


      if (acme_windows_common::node::defer_component_factory(scopedstrComponent))
      {


         return true;

      }

      return false;


   }


   void node::realize(::particle_pointer pparticle)
   {


   }


   void node::calculate_onedrive_installed()
   {

      m_bOneDrive = false;

      m_pathOneDrive.empty();

      m_bOneDriveCalculated = true;

      __check_refdbg

      ::cast < acme_windows::directory_system > pdirectorysystem = directory_system();

      ::file::path pathSkyDrive;

      bool bException = false;

      try
      {

         pathSkyDrive = pdirectorysystem->_get_known_folder(FOLDERID_OneDrive);

      }
      catch (...)
      {

         bException = true;

      }

      __check_refdbg

      if (bException || !directory_system()->is(pathSkyDrive))
      {

         if (::system()->is_desktop_system())
         {

            auto pathHome = directory()->home();

            auto pathTxt = pathHome / "onedrive.txt";

            if (file()->exists(pathTxt))
            {

               string strPath = file()->safe_get_string(pathTxt);

               strPath.trim();

               if (strPath.has_character() && directory()->is(strPath))
               {

                  m_pathOneDrive = strPath;

                  m_bOneDrive = true;

               }

            }

         }
         else
         {

            m_pathOneDrive.empty();

         }

      }
      else
      {

         m_pathOneDrive = pathSkyDrive;

      }

      if (directory()->is(m_pathOneDrive))
      {

         m_bOneDrive = true;

      }

      m_bOneDriveCalculated = true;


   }


   void node::defer_register_server_library(const ::platform::uuid & uuid, const ::file::path & path)
   {

      auto windowspath = path.windows_path();

      ::acme_windows::registry::key key;

      ::string strKey;

      //WCHAR szCLSID[MAX_PATH];

      //StringFromGUID2(CLSID_DeskBand, szCLSID, ARRAYSIZE(szCLSID));

      strKey.formatf("CLSID\\{%s}\\InprocServer32", uuid.as_string().uppered().c_str());

      //::string strKey(wstrKey);

      ::string strPath;

      bool bUnregister = false;

      if (!key._open(HKEY_CLASSES_ROOT, strKey, false)
         || !key._get("", strPath)
         || (bUnregister = !strPath.case_insensitive_equals(windowspath.path())))
      {

         if (bUnregister)
         {

            auto hinst = ShellExecuteW(NULL, _T("RunAs"), L"regsvr32.exe", "/s /u " + windowspath.path(), NULL, SW_SHOWNORMAL);

         }

         auto hinst = ShellExecuteW(NULL, _T("RunAs"), L"regsvr32.exe", "/s " + windowspath.path(), NULL, SW_SHOWNORMAL);

      }

   }


   void node::defer_unregister_server_library(const ::platform::uuid & uuid, const ::file::path & path)
   {

      auto windowspath = path.windows_path();

      ::acme_windows::registry::key key;

      ::string strKey;

      //WCHAR szCLSID[MAX_PATH];

      //StringFromGUID2(CLSID_DeskBand, szCLSID, ARRAYSIZE(szCLSID));

      strKey.formatf("CLSID\\{%s}\\InprocServer32", uuid.as_string().uppered().c_str());

      //::string strKey(wstrKey);

      ::string strPath;

      bool bUnregister = false;

      if (key._open(HKEY_CLASSES_ROOT, strKey, false))
      {

         auto hinst = ShellExecuteW(NULL, _T("RunAs"), L"regsvr32.exe", "/s /u " + windowspath.path(), NULL, SW_SHOWNORMAL);

      }

   }


   bool node::is_server_library_registered(::file::path & path,const ::platform::uuid & uuid)
   {

      auto windowspath = path.windows_path();

      ::acme_windows::registry::key key;

      ::string strKey;

      //WCHAR szCLSID[MAX_PATH];

      //StringFromGUID2(CLSID_DeskBand, szCLSID, ARRAYSIZE(szCLSID));

      strKey.formatf("CLSID\\{%s}\\InprocServer32", uuid.as_string().uppered().c_str());

      //::string strKey(wstrKey);

      ::string strPath;

      bool bUnregister = false;

      bool bRegistered = key._open(HKEY_CLASSES_ROOT, strKey, false);

      if (!bRegistered)
      {

         return false;

      }

      key._get("", strPath);

      path = strPath;

      return true;

   }


   ::string node::get_host_name()
   {


      TCHAR computerName[MAX_COMPUTERNAME_LENGTH + 256];
      DWORD size = sizeof(computerName) / sizeof(TCHAR);

      if (GetComputerNameEx(ComputerNamePhysicalDnsFullyQualified, computerName, &size)) {
         //printf("Computer Name: %s\n", computerName);
      }
      else {
         //printf("GetComputerNameEx failed with error: %lu\n", GetLastError());
      }

      return computerName;

   }


   ::file::path node::_get_font_path_from_name(const ::scoped_string & scopedstrName) 
   {
      
      auto path = __get_font_path_from_name(scopedstrName, true);

      if (path.is_empty())
      {

         path = __get_font_path_from_name(scopedstrName, false);

         if (path.is_empty())
         {

            path = __get_font_path_from_name(scopedstrName + " Regular", true);

         }

      }

      return path;

   }


   ::file::path node::__get_font_path_from_name(const ::scoped_string& scopedstrName, bool bTrueType)
   {
      HKEY hKey;
      const_char_pointer fonts_reg_path = "SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Fonts";

      // Open the Fonts registry key
      if (RegOpenKeyExA(HKEY_LOCAL_MACHINE, fonts_reg_path, 0, KEY_READ, &hKey) != ERROR_SUCCESS)
         return {};

      DWORD index = 0;
      CHAR value_name[256];
      BYTE data[260];
      DWORD value_name_len, data_len, type;
      BOOL found = FALSE;

      ::string str;



      ::string strName(scopedstrName);

      if (bTrueType)
      {

         strName += " (TrueType)";

      }

      while (!found) {
         value_name_len = sizeof(value_name);
         data_len = sizeof(data);
         if (RegEnumValueA(hKey, index++, value_name, &value_name_len, NULL, &type, data, &data_len) != ERROR_SUCCESS)
            break;

         if (type == REG_SZ && strName.case_insensitive_equals(value_name)) {
            // Found the matching font
            char windows_dir[MAX_PATH];
            GetWindowsDirectoryA(windows_dir, MAX_PATH);


            str.formatf("%s\\Fonts\\%s", windows_dir, (char*)data);

            // Combine with Fonts path

            found = TRUE;
         }
      }

      RegCloseKey(hKey);
      return str;
   }


} // namespace acme_windows





#ifdef WINDOWS_DESKTOP

int windows_desktop1_main(HINSTANCE hInstance, int nCmdShow);



//#include "apex/operating_system/windows/_.h"

#endif


