// Create on 2021-03-21 20:00 <3ThomasBS_
#include "framework.h"


namespace windows
{

   
   acme_dir::acme_dir()
   {

      m_pplatformdir = this;

   }


   acme_dir::~acme_dir()
   {


   }


   string acme_dir::dir_root()
   {

      ::string path;

      path = _get_known_folder(FOLDERID_RoamingAppData);

      if (path.length() > 0 && path[path.length() - 1] != '\\')
      {

         path += "\\";

      }

      path += "ca2";

      return path;

   }


   ::file::path acme_dir::get_memory_map_base_folder_path() 
   {

      auto path = _get_known_folder(FOLDERID_RoamingAppData);

      path /= "ca2/memory_map";

      return path;

   }


   ::file::path acme_dir::home()
   {

      return _get_known_folder(FOLDERID_Profile);

   }


   ::file::path acme_dir::program_data()
   {

      return _get_known_folder(FOLDERID_ProgramData);

   }


   ::file::path acme_dir::roaming()
   {

      return _get_known_folder(FOLDERID_RoamingAppData);

   }


   ::file::path acme_dir::appdata()
   {

      return ca2roaming() / "appdata" / app_relative();

   }


   ::file::path acme_dir::public_system()
   {

      return public_root() / "system";

   }


   ::file::path acme_dir::system()
   {

      return ca2roaming() / "system";

   }


   ::file::path acme_dir::config()
   {

      return ca2roaming() / "config";

   }


   ::file::path acme_dir::local()
   {

      return ca2roaming() / "local";

   }


   ::file::path acme_dir::sensitive()
   {

   #ifdef WINDOWS

      return "C:\\sensitive\\sensitive";

   #else

      return "/sensitive/sensitive";

   #endif

   }







   string acme_dir::system_short_name()
   {

   #ifdef _UWP

      return "metro";

   #else

      ::file::path pathSystemShortName = localconfig() / "system_short_name.txt";

      return m_psystem->m_pacmefile->as_string(pathSystemShortName).trimmed();

   #endif

   }


   ::file::path acme_dir::relative(::file::path path)
   {

      path.replace(":", "");

      ::str::ends_eat_ci(path, ".exe");

      return path;

   }

   #ifdef _UWP


   ::file::path acme_dir::app_relative()
   {

      return "";

   }


   #else


   ::file::path acme_dir::app_relative()
   {

      ::file::path path = m_psystem->m_pacmefile->executable();

      path = relative(path);

      return path;

   }


   #endif



   ::file::path acme_dir::inplace_install(string strAppId, string strPlatform, string strConfiguration)
   {

   #ifdef WINDOWS_DESKTOP

      ::file::path path;

      string strFolder;

      strsize iFind = strAppId.find('/');

      if (strPlatform.compare_ci("win32") == 0 || strPlatform.compare_ci("x86") == 0)
      {

         path = program_files_x86();

      }
      else
      {
         path = program_files_x86();


         path = program_files();

      }

      if (iFind < 0)
      {

         path /= strAppId;

      }
      else
      {

         path /= strAppId.Left(iFind);

         path /= strAppId.Mid(iFind + 1);

      }

      return path;

   #elif defined(ANDROID)

         auto psystem = m_psystem;

         auto pacmedir = psystem->m_pacmedir;


      return          auto psystem = m_psystem;

         auto pacmedir = psystem->m_pacmedir;

pacmedir->roaming();

   #else

      return m_psystem->m_pacmepath->app_module().folder(4);

   #endif


   }


   ::file::path acme_dir::inplace_matter_install(string strAppId, string strPlatform, string strConfiguration)
   {

   #ifdef WINDOWS_DESKTOP

      ::file::path path;

      string strFolder;

      strsize iFind = strAppId.find('/');

      path = ca2roaming();

      path /= "_matter";

      return path;

   #elif defined(ANDROID)

         auto psystem = m_psystem;

         auto pacmedir = psystem->m_pacmedir;


      return          auto psystem = m_psystem;

         auto pacmedir = psystem->m_pacmedir;

pacmedir->roaming();

   #else

      return m_psystem->m_pacmepath->app_module().folder(4);

   #endif


   }


   ::file::path acme_dir::install()
   {

      if (m_pathInstallFolder == nullptr || m_pathInstallFolder.is_empty())
      {

         return default_install();

      }

      return m_pathInstallFolder;

   }


   ::file::path acme_dir::default_install()
   {

   #ifdef ANDROID
            auto psystem = m_psystem;

         auto pacmedir = psystem->m_pacmedir;



      return          auto psystem = m_psystem;

         auto pacmedir = psystem->m_pacmedir;

pacmedir->roaming();

   #elif defined(__APPLE__)

      return m_psystem->m_pacmefile->executable()-3;

   #else

      return m_psystem->m_pacmefile->executable()-4;

   #endif

   }


   ::file::path acme_dir::beforeca2()
   {

      return ::file_path_folder(install());

   }






   #ifdef WINDOWS_DESKTOP


   #include <Shlobj.h>


   ::file::path acme_dir::program_files_x86()
   {

      wstring wstrModuleFolder(get_buffer, sizeof(unichar) * 8);

      wstring wstrModuleFilePath(get_buffer, sizeof(unichar) * 8);

      wcscpy(wstrModuleFilePath, _wgetenv(L"PROGRAMFILES(X86)"));

      if (wcslen(wstrModuleFilePath) == 0)
      {

         SHGetSpecialFolderPathW(nullptr, wstrModuleFilePath, CSIDL_PROGRAM_FILES, false);

      }

      wstrModuleFilePath.trim_right(L"\\/");

      wcscpy(wstrModuleFolder, wstrModuleFilePath);

      return string(wstrModuleFolder);

   }


   ::file::path acme_dir::program_files()
   {

      wstring wstrModuleFolder(get_buffer, sizeof(unichar) * 8);

      wstring wstrModuleFilePath(get_buffer, sizeof(unichar) * 8);

      wcscpy(wstrModuleFilePath, _wgetenv(L"PROGRAMW6432"));

      if (wcslen(wstrModuleFilePath) == 0)
      {

         SHGetSpecialFolderPathW(nullptr, wstrModuleFilePath, CSIDL_PROGRAM_FILES, false);

      }

      wstrModuleFilePath.trim_right(L"\\/");

      wstrModuleFolder = wstrModuleFilePath;

      return string(wstrModuleFolder);



   }


   #else


   ::file::path acme_dir::program_files_x86()
   {

      ::file::path path("/opt/ca2");

      return path;

   }


   ::file::path acme_dir::program_files()
   {

      ::file::path path("/opt/ca2");

      return path;

   }


   #endif


   ::file::path acme_dir::stage(string strAppId, string strPlatform, string strConfiguration)
   {

      return inplace_install(strAppId, strPlatform, strConfiguration) / "time" / time_binary_platform(strPlatform) / strConfiguration;

   }


   #ifdef LINUX


   ::file::path acme_dir::home()
   {

      return getenv("HOME");

   }


   #endif


#if defined(_UWP) || defined(__APPLE__) || defined(LINUX) || defined(ANDROID)

   ::file::path acme_dir::bookmark()
   {

      auto psystem = m_psystem;

      auto pacmedir = psystem->m_pacmedir;

      return pacmedir->localconfig() / "bookmark";

   }


   #endif


   #ifdef _UWP


   ::file::path acme_dir::home()
   {

      return "";

   }


   #endif


   void acme_dir::set_path_install_folder(const ::string & pszPath)
   {

      m_pathInstallFolder = pszPath;

   }


   ::file::path acme_dir::bookmark()
   {

      return localconfig() / "bookmark";

   }


   ::file::path acme_dir::sys_temp()
   {

      return appdata() / "time";

   }


   ::file::path acme_dir::ca2appdata()
   {

      return ca2roaming() / "appdata";

   }


   ::file::path acme_dir::public_root()
   {

      return program_data() / "ca2";

   }

   ::file::path acme_dir::ca2roaming()
   {

      return roaming() / "ca2";

   }


   ::file::path acme_dir::localconfig()
   {

      return ca2roaming() / "localconfig";

   }


   //

   //::file::path acme_dir::pathfind(const string& pszEnv, const string& pszTopic, const string& pszMode)
   //{

   //   ::file::patha stra;

   //   stra.add_tokens(pszEnv, ":", false);

   //   string strCandidate;

   //   for (i32 i = 0; i < stra.get_count(); i++)
   //   {

   //      strCandidate = stra[i] / pszTopic;

   //      //if (m_pcontext->m_papexcontext->file().exists(strCandidate))
   //      if (m_pacmefile->exists(strCandidate))
   //      {

   //         return strCandidate;

   //      }

   //   }

   //   return "";

   //}



   //::file::path acme_dir::get_memory_map_base_folder_path()
   //{

   //   return "";

   //}


   ::file::path acme_dir::user_appdata_local()
   {

      return _shell_get_special_folder_path(CSIDL_LOCAL_APPDATA);

   }


   bool acme_dir::_shell_get_special_folder_path(HWND hwnd, ::file::path& str, i32 csidl, bool fCreate)
   {

      return ::SHGetSpecialFolderPathW(hwnd, wtostring(str, MAX_PATH * 8), csidl, fCreate) != false;

   }


   ::file::path acme_dir::_shell_get_special_folder_path(i32 csidl, bool fCreate, ::windowing::window* pwindow)
   {

      ::file::path path;

      if (!_shell_get_special_folder_path(nullptr, path, csidl, fCreate))
      {

         return "";

      }

      return path;

   }


   ::file::path acme_dir::_get_known_folder(REFKNOWNFOLDERID kfid)
   {

      ::file::path str;

      ::cotaskptr < PWSTR > pwszPath;

      HANDLE hToken = nullptr;

      //::OpenProcessToken(::GetCurrentProcess(), TOKEN_QUERY | TOKEN_IMPERSONATE | TOKEN_DUPLICATE, &hToken);

      HRESULT hr = SHGetKnownFolderPath(kfid, 0, hToken, &pwszPath);

      return pwszPath;

   }

   
//   bool acme_dir::_is(const char * path1)
//   {
//
//#ifdef _UWP
//
//      //string str;
//
//      ////str = "\\\\?\\";
//      ////str += path1;
//
//      //str = path1;
//
//      //str.ends_eat_ci("\\");
//      //str.ends_eat_ci("/");
//      //str.ends_eat_ci("\\");
//      //str.ends_eat_ci("/");
//
//      u32 dwFileAttributes = ::windows_get_file_attributes(path1);
//
//      if (dwFileAttributes != INVALID_FILE_ATTRIBUTES)
//      {
//
//         return dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY;
//
//      }
//      else
//      {
//
//         ::u32 dwLastError = ::GetLastError();
//
//         string strPrefix;
//
//         {
//
//            string strRelative = path1;
//
//            auto folderBase = winrt_folder(strRelative, strPrefix);
//
//            if (folderBase != nullptr)
//            {
//
//               strRelative.replace("/", "\\");
//
//               strPrefix.replace("/", "\\");
//
//               ::str::begins_eat_ci(strRelative, strPrefix);
//
//               strRelative.trim("/\\");
//
//               //strPrefix.trim_right("/\\");
//
//               try
//               {
//
//                  auto folder = folderBase->GetFolderAsync(strRelative);
//
//                  if (folder != nullptr)
//                  {
//
//                     return true;
//
//                  }
//
//               }
//               catch (...)
//               {
//
//               }
//
//            }
//
//         }
//
//         return false;
//
//         //auto folder = wait(::winrt::Windows::Storage::StorageFolder::GetFolderFromPathAsync(path1));
//
//         //bool bOk = folder != nullptr;
//
//         //if (!bOk)
//         //{
//
//         //   set_last_error(dwLastError);
//
//         //}
//
//         //if (bOk)
//         //{
//
//         //   return true;
//
//         //}
//
//         //return bOk;
//
//      }
//
//
//#elif defined(WINDOWS_DESKTOP)
//
//      auto dwFileAttributes = ::windows_get_file_attributes(path1);
//
//      if (dwFileAttributes == INVALID_FILE_ATTRIBUTES || !(dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
//      {
//
//         return false;
//
//      }
//
//      return true;
//
//#else
//
//      // dedicaverse stat -> Sir And Arthur - Cesar Serenato
//
//      return is_dir(path1);
//
//#endif
//
//   }

#include "framework.h"
#include "acme/operating_system.h"


#if defined(WINDOWS_DESKTOP)
#include <Shlobj.h>
#include <shellapi.h>
#elif defined(__APPLE__)
#include <sys/stat.h>
#include <dirent.h>
#elif defined(LINUX)
#include <dlfcn.h>
#include <link.h>
#include <sys/stat.h>
#include <dirent.h>
#elif defined(ANDROID)
#include <sys/stat.h>
#include <dirent.h>
#elif defined(_UWP)
#include "acme/os/universal_windows/file_winrt.h"
#endif




   void TranslateLastError()
   {

      if (errno == EEXIST)
      {

         set_last_status(error_already_exists);

      }
      else
      {

         set_last_status(::success);

      }

   }


bool windows_file_find_is_dots(WIN32_FIND_DATAW & data)
{

   if (data.cFileName[0] == L'.')
   {

      if (data.cFileName[1] == L'\0' ||
         (data.cFileName[1] == L'.' &&
            data.cFileName[2] == L'\0'))
      {

         return true;

      }

   }

   return false;

}


#if defined(_UWP)

#pragma push_macro("get_system()")

#undef get_system()

   using namespace ::winrt::Windows::get_system();

#pragma pop_macro("get_system()")

#endif


//      ::file::path acme_dir::module()
//      {
//
//#if defined(_UWP)
//
//         return "";
//
//#elif defined(WINDOWS)
//
//         wstring wstrModuleFolder(get_buffer, MAX_PATH * 8);
//
//         wstring wstrModuleFilePath(get_buffer, MAX_PATH * 8);
//
//         HMODULE hmodule = ::GetModuleHandleA("acme.dll");
//
//         if (hmodule == nullptr)
//         {
//
//            hmodule = ::GetModuleHandleA("spalib.dll");
//
//         }
//
//         if (hmodule == nullptr)
//         {
//
//            wcscpy(wstrModuleFilePath, _wgetenv(L"PROGRAMFILES(X86)"));
//
//
//            if (wstrModuleFilePath.empty())
//            {
//
//               SHGetSpecialFolderPathW(nullptr, wstrModuleFilePath, CSIDL_PROGRAM_FILES, false);
//
//            }
//
//            wstrModuleFilePath.trim_right(L"\\/");
//
//            wcscat(wstrModuleFilePath, L"\\ca2\\");
//
//#ifdef X86
//
//            wcscat(wstrModuleFilePath, L"stage\\x86\\");
//
//#else
//            wide_concatenate(wstrModuleFilePath, L"stage\\x64\\");
//
//#endif
//
//            wcscpy(wstrModuleFolder, wstrModuleFilePath);
//
//            return string(wstrModuleFolder);
//
//         }
//
//         if (!GetModuleFileNameW(hmodule, wstrModuleFilePath, (::u32)wstrModuleFilePath.length()))
//         {
//
//            return "";
//
//         }
//
//         LPWSTR pszModuleFileName;
//
//         if (!GetFullPathNameW(wstrModuleFilePath, (::u32)wstrModuleFilePath.length(), wstrModuleFolder, &pszModuleFileName))
//         {
//
//            return "";
//
//         }
//
//         wstrModuleFolder.release_string_buffer();
//
//         wstrModuleFolder.trim_right(L"\\/");
//
//         return wstrModuleFolder;
//
//#else
//
//         string strModuleFolder;
//
//         auto wstrModuleFolder = strModuleFolder.get_string_buffer(MAX_PATH * 8);
//
//         __throw(todo);
//
//         return wstrModuleFolder;
//
//#endif
//
//      }
//

      // bool eat_end_level(string & str, i32 iLevelCount, const char * pSeparator)
      // {

      //    strsize iLast = str.length() - 1;

      //    if(iLast < 0)
      //       return iLevelCount <= 0;

      //    while(str[iLast] == '/' || str[iLast] == '\\')
      //       iLast--;

      //    for(i32 i = 0; i < iLevelCount; i++)
      //    {

      //       strsize iFind1 = str.reverse_find('/', iLast);

      //       strsize iFind2 = str.reverse_find('\\', iLast);

      //       strsize iFind = maximum(iFind1, iFind2);

      //       if(iFind >= iLast)
      //          return false;

      //       if(iFind < 0)
      //          return false;

      //       iLast = iFind;

      //       while(str[iLast] == '/' || str[iLast] == '\\')
      //          iLast--;

      //    }

      //    str = str.substr(0, iLast + 1);

      //    return true;

      // }
      //
      //
      //   string ca2_module_dup()
      //   {
      //
      //      static string * s_pstrCalc = nullptr;
      //
      //      if(s_pstrCalc != nullptr)
      //      {
      //
      //         return *s_pstrCalc;
      //
      //      }
      //
      //      string str;
      //
      //   #ifdef WINDOWS_DESKTOP
      //
      //      wstring wstrModuleFilePath(get_buffer, MAX_PATH * 8);
      //
      //      GetModuleFileNameW(::GetModuleHandleA("acme.dll"), wstrModuleFilePath, MAX_PATH + 1);
      //
      //      str = (const unichar *) wstrModuleFilePath;
      //
      //   #elif defined(LINUX)
      //
      //      void * handle = dlopen("libacme.so", RTLD_NOW);
      //
      //      if(handle == nullptr)
      //         return "";
      //
      //      link_map * plm;
      //
      //      dlinfo(handle, RTLD_DI_LINKMAP, &plm);
      //
      //      string strCa2ModuleFolder = plm->l_name;
      //
      //      dlclose(handle);
      //
      //      str = strCa2ModuleFolder;
      //
      //   #elif defined(_UWP)
      //
      //      str = "";
      //
      //   #elif defined(__APPLE__)
      //
      //      {
      //
      //         str = get_exe_path();
      //
      //         if(str.has_char())
      //         {
      //
      //            goto found;
      //
      //         }
      //
      //         str = ::dir::pathfind(::file::path(str).folder(), "libacme.dylib", "rfs"); // readable - normal file - non zero size_f64
      //
      //         if(str.has_char())
      //         {
      //
      //            goto found;
      //
      //         }
      //
      //         str = ::dir::pathfind(getenv("DYLD_LIBRARY_PATH"), "libacme.dylib", "rfs"); // readable - normal file - non zero size_f64
      //
      //         if(str.has_char())
      //         {
      //
      //            goto found;
      //
      //         }
      //
      //         str = get_exe_path();
      //
      //         if(str.has_char())
      //         {
      //
      //            goto found;
      //
      //         }
      //
      //         str = ::dir::pathfind(getenv("DYLD_FALLBACK_LIBRARY_PATH"), "libacme.dylib", "rfs"); // readable - normal file - non zero size_f64
      //
      //         if(str.has_char())
      //         {
      //
      //            goto found;
      //
      //         }
      //
      //      }
      //
      //   found:
      //      ;
      //
      //   #endif
      //
      //      s_pstrCalc = new string(str);
      //
      //      return *s_pstrCalc;
      //
      //
      //   }


      //bool acme_dir::create(const char * path)
      //{

      //   return _create(path);

      //}


#ifndef WINDOWS_DESKTOP


      bool acme_dir::_mk(const char * path)
      {

         if (is(path))
         {

            return true;

         }

         string strName;

         ::file::path pathDir;

         strsize iLastPos;

#ifdef _UWP

         {

            string strPath = path;

            string strPrefix;

            winrt_folder(strPath, strPrefix);

            pathDir = strPrefix;

            iLastPos = strPrefix.get_length();

         }

#else

         iLastPos = -1;

#endif

         ::file::patha stra;

         path.ascendants_path(stra);

         index i = stra.get_upper_bound();

         for (; i >= 0; i--)
         {

            string strDir = stra[i];

            if (is(strDir))
            {

               break;

            }

         }

         if (i < 0)
         {

            return true;

         }

         for (; i < stra.get_count(); i++)
         {

            string strDir = stra[i];

            if (::dir::mkdir(strDir))
            {

            }
            else
            {

               auto estatus = ::get_last_status();

               if (estatus == ::error_already_exists)
               {

                  try
                  {

                     file_delete(strDir);

                  }
                  catch (...)
                  {

                  }

                  string str = stra[i];

                  str.trim_right("\\/");

                  try
                  {

                     file_delete(str);

                  }
                  catch (...)
                  {

                  }

                  if (::dir::mkdir(stra[i]))
                  {

                     continue;

                  }
                  else
                  {

                     estatus = ::get_last_status();

                  }

               }

#ifdef WINDOWS_DESKTOP

               char * pszError;

               FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, nullptr, dwError, 0, (char *)&pszError, 8, nullptr);

               //TRACE("         auto psystem = m_psystem;

         auto pacmedir = psystem->m_pacmedir;

pacmedir->create CreateDirectoryW last error(%d)=%s", dwError, pszError);

               ::LocalFree(pszError);

               //m_isdirmap.set(stra[i], false);

#endif

               return false;

            }

         }

         return true;

      }


#endif


      ::e_status acme_dir::_create_directory(const char * path)
      {

#ifdef WINDOWS

         wstring wstr;

         if (file_path_is_absolute(path))
         {

            wstr = L"\\\\?\\" + wstring(path);

         }
         else
         {

            wstr = path;

         }

         if (!::CreateDirectoryW(wstr, nullptr))
         {

            return false;

         }

#else

         if (::mkdir(path, S_IRWXU | S_IRWXG | S_IRWXO) != 0)
         {

            TranslateLastError();

            return false;

         }

         set_last_status(success);

#endif

         return true;

      }



      ::file::path acme_dir::module()
      {

#ifdef WINDOWS

         wstring path(get_buffer, MAX_PATH * 8);

         if (!GetModuleFileNameW(nullptr, path, (::u32)path.size()))
         {

            return "";

         }

         string strPath(path);

         strPath = solve_relative(strPath);

         ::file::path pathFolder = file_path_folder(strPath);

         return pathFolder;

#else

         return "/acme/stage";

#endif

      }


      bool acme_dir::is(const char * path)
      {

         //if (::file::system_dir::g_pthis == nullptr)
         //{

         return _is(path);

         //}

         //return ::file::system_dir::g_pthis->is(path, ::get_context_system());

      }



      void acme_dir::rls(::file::patha & stra, const char * psz)
      {
         ::count start = stra.get_count();
         ls(stra, psz);
         ::count end = stra.get_count();
         for (::index i = start; i < end; i++)
         {
            if (is(stra[i]))
            {
               rls(stra, stra[i]);
            }
         }

      }


      void acme_dir::rls_dir(::file::patha & stra, const char * psz)
      {

         ::count start = stra.get_count();

         ls_dir(stra, psz);

         ::count end = stra.get_count();

         for (::index i = start; i < end; i++)
         {

            ::file::path path = stra[i];

            rls_dir(stra, path);

         }

      }


      void acme_dir::ls(::file::patha & stra, const char * psz)
      {

#if defined(LINUX) || defined(__APPLE__) || defined(ANDROID)

         DIR * dirp = opendir(psz);

         if (dirp == nullptr)
            return;

         dirent * dp;
         ::file::path path;
         while ((dp = readdir(dirp)) != nullptr)
         {

            if (strcmp(dp->d_name, "..") == 0)
               continue;
            else if (strcmp(dp->d_name, ".") == 0)
               continue;
            path = psz / dp->d_name;
            path.m_iDir = dp->d_type & DT_DIR ? 1 : 0;
            path.m_iSize = -1;
            stra.add(path);

            //output_debug_string("flood for you: dir::ls ----> " + path);

         }

         closedir(dirp);

#elif defined(_UWP)

         ::winrt::Windows::Storage::StorageFolder ^ folder = nullptr;

         string strPrefix;

         string str = psz;

         try
         {

            if (string(psz).compare_ci("image://") == 0)
            {

               strPrefix = "image://";

               try
               {

                  folder = ::winrt::Windows::Storage::KnownFolders::PicturesLibrary;

               }
               catch (...)
               {

                  folder = nullptr;

               }

            }
            else if (string(psz).compare_ci("music://") == 0)
            {

               strPrefix = "music://";

               try
               {

                  folder = ::winrt::Windows::Storage::KnownFolders::MusicLibrary;

               }
               catch (...)
               {

                  folder = nullptr;

               }

            }
            else if (string(psz).compare_ci("video://") == 0)
            {

               strPrefix = "video://";

               try
               {

                  folder = ::winrt::Windows::Storage::KnownFolders::VideosLibrary;

               }
               catch (...)
               {

                  folder = nullptr;

               }

            }
            else if (string(psz).compare_ci("document://") == 0)
            {

               strPrefix = "document://";

               try
               {

                  folder = ::winrt::Windows::Storage::KnownFolders::DocumentsLibrary;

               }
               catch (...)
               {

                  folder = nullptr;

               }

            }
            else
            {

               if (::str::begins_eat_ci(str, "image://"))
               {

                  strPrefix = "image://";

                  try
                  {

                     folder = ::winrt::Windows::Storage::KnownFolders::PicturesLibrary;

                  }
                  catch (...)
                  {

                     folder = nullptr;

                  }

               }

               if (::str::begins_eat_ci(str, "music://"))
               {

                  strPrefix = "music://";

                  try
                  {

                     folder = ::winrt::Windows::Storage::KnownFolders::MusicLibrary;

                  }
                  catch (...)
                  {

                     folder = nullptr;

                  }

               }

               if (::str::begins_eat_ci(str, "video://"))
               {

                  strPrefix = "video://";

                  try
                  {

                     folder = ::winrt::Windows::Storage::KnownFolders::VideosLibrary;

                  }
                  catch (...)
                  {

                     folder = nullptr;

                  }

               }

               if (::str::begins_eat_ci(str, "document://"))
               {

                  strPrefix = "document://";

                  try
                  {

                     folder = ::winrt::Windows::Storage::KnownFolders::DocumentsLibrary;

                  }
                  catch (...)
                  {

                     folder = nullptr;

                  }

               }

               if (strPrefix.has_char())
               {

                  string_array stra;

                  stra.explode("/", str);

                  string str;

                  while (stra.get_count() > 0)
                  {

                     str = stra[0];

                     if (str.has_char())
                     {

                        folder = wait(folder->GetFolderAsync(str));

                        strPrefix += str + "/";

                     }

                     stra.erase_at(0);

                  }

               }
               else
               {

                  folder = ::winrt::Windows::Storage::StorageFolder::GetFolderFromPathAsync(str).get();

                  strPrefix = str + "/";

               }

            }

         }
         catch (...)
         {

            return;

         }

         if (folder == nullptr)
         {

            return;

         }

         string strPath = string(begin(folder->Path));

         auto a = folder->GetItemsAsync().get();

         for (u32 u = 0; u < a->Size; u++)
         {

            string strPath = string(begin(a->GetAt(u)->Path));

            ::file::path path(strPath);

            string str = path;

            path.m_iDir = a->GetAt(u)->IsOfType(::winrt::Windows::Storage::StorageItemTypes::Folder) ? 1 : 0;

            stra.add(path);

         }


#else

         WIN32_FIND_DATAW FindFileData;

         HANDLE hFind;

         hFind = FindFirstFileW(wstring(psz) + "\\*", &FindFileData);

         if (hFind == INVALID_HANDLE_VALUE)
         {

            return;

         }

         while (true)
         {

            if (!windows_file_find_is_dots(FindFileData) && (FindFileData.dwFileAttributes != INVALID_FILE_ATTRIBUTES))
               stra.add(::file::path(FindFileData.cFileName));

            //if (stra.has_elements() && stra.last() == "teste")
            //{
            //   output_debug_string("teste");
            //}

            if (!FindNextFileW(hFind, &FindFileData))
               break;

         }

         FindClose(hFind);

#endif


      }


      void acme_dir::ls_dir(::file::patha & stra, const char * psz)
      {

#if defined(LINUX) || defined(__APPLE__) || defined(ANDROID)

         DIR * dirp = opendir(psz);

         if (dirp == nullptr)
            return;

         dirent * dp;

         while ((dp = readdir(dirp)) != nullptr)
         {
            if (dp->d_name[0] == '.')
            {
               if (dp->d_name[1] == '\0')
                  continue;
               if (dp->d_name[1] == '.')
               {
                  if (dp->d_name[2] == '\0')
                     continue;
               }
            }
            ::file::path strPath = psz / dp->d_name;
            if (is(strPath))
            {
               stra.add(strPath);
            }

         }

         closedir(dirp);

#elif defined(_UWP)

         ::winrt::Windows::Storage::StorageFolder ^ folder = wait(::winrt::Windows::Storage::StorageFolder::GetFolderFromPathAsync(string(psz)));

         ::winrt::Windows::Foundation::Collections::IVectorView < ::winrt::Windows::Storage::StorageFolder ^ > ^ a = wait(folder->GetFoldersAsync());

         for (u32 u = 0; u < a->Size; u++)
         {
            stra.add(begin(a->GetAt(u)->Path));
         }


#else

         WIN32_FIND_DATAW FindFileData;

         HANDLE hFind;

         hFind = FindFirstFileW(wstring(psz), &FindFileData);

         if (hFind == INVALID_HANDLE_VALUE)
            return;

         while (true)
         {

            if (!windows_file_find_is_dots(FindFileData) && (FindFileData.dwFileAttributes != INVALID_FILE_ATTRIBUTES) && (FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0)
            {

               stra.add(::file::path(FindFileData.cFileName));

            }

            stra.add(::file::path(FindFileData.cFileName));

            if (!FindNextFileW(hFind, &FindFileData))
               break;

         }

         FindClose(hFind);

#endif


      }


      void acme_dir::ls_file(::file::patha & stra, const char * psz)
      {

#if defined(LINUX) || defined(__APPLE__) || defined(ANDROID)

         DIR * dirp = opendir(psz);

         if (dirp == nullptr)
            return;

         dirent * dp;

         while ((dp = readdir(dirp)) != nullptr)
         {
            if (dp->d_name[0] == '.')
            {
               if (dp->d_name[1] == '\0')
                  continue;
               if (dp->d_name[1] == '.')
               {
                  if (dp->d_name[2] == '\0')
                     continue;
               }
            }
            ::file::path strPath = psz / dp->d_name;
            if (!is(strPath))
            {
               stra.add(strPath);
            }

         }

         closedir(dirp);

#elif defined(_UWP)

         ::winrt::Windows::Storage::StorageFolder ^ folder = wait(::winrt::Windows::Storage::StorageFolder::GetFolderFromPathAsync(string(psz)));

         ::winrt::Windows::Foundation::Collections::IVectorView < ::winrt::Windows::Storage::StorageFolder ^ > ^ a = wait(folder->GetFoldersAsync());

         for (u32 u = 0; u < a->Size; u++)
         {
            stra.add(begin(a->GetAt(u)->Path));
         }


#else

         WIN32_FIND_DATAW FindFileData;

         HANDLE hFind;

         hFind = FindFirstFileW(wstring(psz), &FindFileData);

         if (hFind == INVALID_HANDLE_VALUE)
            return;

         while (true)
         {

            if (!windows_file_find_is_dots(FindFileData) && (FindFileData.dwFileAttributes != INVALID_FILE_ATTRIBUTES) && (FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0)
            {
            }
            else
            {
               stra.add(::file::path(FindFileData.cFileName));
            }


            stra.add(::file::path(FindFileData.cFileName));

            if (!FindNextFileW(hFind, &FindFileData))
               break;

         }

         FindClose(hFind);

#endif

      }


      ::file::path acme_dir::pathfind(const string & pszEnv, const string & pszTopic, const string & pszMode)
      {

         string_array stra;

         stra.add_tokens(pszEnv, ":");

         string strCandidate;

         for (i32 i = 0; i < stra.get_count(); i++)
         {

            if (stra[i].is_empty())
               continue;

            strCandidate = ::file::path(stra[i]) / pszTopic;

            if (m_pacmefile->exists(strCandidate))
            {
               return strCandidate;
            }

         }

         return "";

      }


      ::file::path acme_dir::archive()
      {

#ifdef WINDOWS

         ::file::path pathArchive = getenv("__archive");

         return pathArchive;

#else

         return "/archive";

#endif

      }


      ::file::path acme_dir::tool()
      {

         return archive() / "tool-windows";

      }


      //int acme_dir::make_path(const char * psz)
      //{


      //   return create(psz) != false;

      //}


//      bool acme_dir::_create(const char * pathParam)
//      {
//
//         if (is(pathParam))
//         {
//
//            return true;
//
//         }
//
//         ::file::path path(pathParam);
//
//         string strName;
//
//         ::file::path pathDir;
//
//         strsize iLastPo = -1;
//
//         ::file::patha stra;
//
//
//         path.ascendants_path(stra);
//
//         index i = stra.get_upper_bound();
//
//         for (; i >= 0; i--)
//         {
//
//            string strDir = stra[i];
//
//            if (is(strDir))
//            {
//
//               break;
//
//            }
//
//         }
//
//         if (i < 0)
//         {
//
//            return true;
//
//         }
//
//         for (; i < stra.get_count(); i++)
//         {
//
//            string strDir = stra[i];
//
//            if (create_directory(strDir))
//            {
//
//            }
//            else
//            {
//
//               DWORD dwError = ::GetLastError();
//
//               if (dwError == ERROR_ALREADY_EXISTS)
//               {
//
//                  try
//                  {
//
//                     m_pacmefile->delete_file(strDir);
//
//                  }
//                  catch (...)
//                  {
//
//                  }
//
//                  string str = stra[i];
//
//                  str.trim_right("\\/");
//
//                  try
//                  {
//
//                     m_pacmefile->delete_file(str);
//
//                  }
//                  catch (...)
//                  {
//
//                  }
//
//                  if (create_directory(stra[i]))
//                  {
//
//                     continue;
//
//                  }
//                  else
//                  {
//
//                     dwError = ::GetLastError();
//
//                  }
//
//               }
//
//#ifdef WINDOWS_DESKTOP
//
//               WCHAR * pwszError;
//
//               FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, nullptr, dwError, 0, (WCHAR *)&pwszError, 8, nullptr);
//
//               //TRACE("         auto psystem = m_psystem;
//
////         auto pacmedir = psystem->m_pacmedir;
////
////pacmedir->create CreateDirectoryW last error(%d)=%s", dwError, pszError);
////
//               ::LocalFree(pwszError);
//
//               //m_isdirmap.set(stra[i], false);
//
//#endif
//
//               return false;
//
//            }
//
//         }
//
//         return true;
//
//      }



   string acme_dir::get_current_directory()
   {

      auto size = GetCurrentDirectoryW(0, nullptr);

      wstring wstr;

      auto buffer = wstr.get_string_buffer(size);

      GetCurrentDirectoryW(size + 1, buffer);

      wstr.release_string_buffer(size);

      return wstr;

   }



} // namespace windows



