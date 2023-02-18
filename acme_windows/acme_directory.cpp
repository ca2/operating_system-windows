// Create on 2021-03-21 20:00 <3ThomasBS_
#include "framework.h"
#include "acme_directory.h"
#include "acme_file.h"
#include "acme/exception/exception.h"
#include "acme/filesystem/filesystem/listing.h"
#include "acme/operating_system/process.h"
#include "acme/platform/node.h"
#include "acme/primitive/string/adaptor.h"
#include "acme/primitive/string/str.h"
#include "acme_windows_common/cotaskptr.h"
#include "acme_windows_common/hresult_exception.h"

#include "acme/_operating_system.h"
#include <Shlobj.h>


//#ifdef WINDOWS_DESKTOP
//
//
//#include <Shlobj.h>


namespace acme_windows
{

   
   acme_directory::acme_directory()
   {

   }


   acme_directory::~acme_directory()
   {


   }


   string acme_directory::dir_root()
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


   ::file::path acme_directory::get_memory_map_base_folder_path() 
   {

      auto path = _get_known_folder(FOLDERID_RoamingAppData);

      path /= "ca2/memory_map";

      return path;

   }


   ::file::path acme_directory::home()
   {

      try
      {

         return _get_known_folder(FOLDERID_Profile);

      }
      //catch(const ::exception & e)
      catch (const ::exception &)
      { 
      
      }
      catch (...)
      {

      }

      return getenv("USERPROFILE");

   }


   ::file::path acme_directory::program_data()
   {

      return _get_known_folder(FOLDERID_ProgramData);

   }


   ::file::path acme_directory::roaming()
   {

      return _get_known_folder(FOLDERID_RoamingAppData);

   }


   ::file::path acme_directory::appdata()
   {

      return ca2roaming() / "appdata" / app_relative();

   }


   ::file::path acme_directory::public_system()
   {

      return public_root() / "system";

   }


   ::file::path acme_directory::system()
   {

      return ca2roaming() / "system";

   }


   ::file::path acme_directory::config()
   {

      return ca2roaming() / "config";

   }


   ::file::path acme_directory::local()
   {

      return ca2roaming() / "local";

   }


   ::file::path acme_directory::sensitive()
   {

   #ifdef WINDOWS

      return "C:\\sensitive\\sensitive";

   #else

      return "/sensitive/sensitive";

   #endif

   }







   string acme_directory::system_short_name()
   {

   #ifdef _UWP

      return "metro";

   #else

      ::file::path pathSystemShortName = localconfig() / "system_short_name.txt";

      return acmefile()->as_string(pathSystemShortName).trimmed();

   #endif

   }


   ::file::path acme_directory::relative(::file::path path)
   {

      path.replace_with("", ":");

      path.case_insensitive_ends_eat(".exe");

      return path;

   }

   #ifdef _UWP


   ::file::path acme_directory::app_relative()
   {

      return "";

   }


   #else


   ::file::path acme_directory::app_relative()
   {

      ::file::path path = acmefile()->module();

      path = relative(path);

      return path;

   }


   #endif



   ::file::path acme_directory::inplace_install(string strAppId, string strPlatform, string strConfiguration)
   {

   #ifdef WINDOWS_DESKTOP

      ::file::path path;

      string strFolder;

      strsize iFind = strAppId.find_index('/');

      if (strPlatform.case_insensitive_order("win32") == 0 || strPlatform.case_insensitive_order("x86") == 0)
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

         path /= strAppId.left(iFind);

         path /= strAppId.substr(iFind + 1);

      }

      return path;

   #elif defined(ANDROID)

         auto psystem = acmesystem();

         auto pacmedir = psystem->m_pacmedirectory;


      return          auto psystem = acmesystem();

         auto pacmedir = psystem->m_pacmedirectory;

pacmedir->roaming();

   #else

      return acmepath()->app_module().folder(4);

   #endif


   }


   ::file::path acme_directory::inplace_matter_install(string strAppId, string strPlatform, string strConfiguration)
   {

   #ifdef WINDOWS_DESKTOP

      ::file::path path;

      string strFolder;

      strsize iFind = strAppId.find_index('/');

      path = ca2roaming();

      path /= "_matter";

      return path;

   #elif defined(ANDROID)

         auto psystem = acmesystem();

         auto pacmedir = psystem->m_pacmedirectory;


      return          auto psystem = acmesystem();

         auto pacmedir = psystem->m_pacmedirectory;

pacmedir->roaming();

   #else

      return acmepath()->app_module().folder(4);

   #endif


   }


   ::file::path acme_directory::install()
   {

      if (m_pathInstallFolder.is_empty())
      {

         return default_install();

      }

      return m_pathInstallFolder;

   }


   ::file::path acme_directory::default_install()
   {

   #ifdef ANDROID
            auto psystem = acmesystem();

         auto pacmedir = psystem->m_pacmedirectory;



      return          auto psystem = acmesystem();

         auto pacmedir = psystem->m_pacmedirectory;

pacmedir->roaming();

   #elif defined(__APPLE__)

      return acmefile()->module()-3;

   #else

      return acmefile()->module()-4;

   #endif

   }


   ::file::path acme_directory::beforeca2()
   {

      return ::file_path_folder(install());

   }






   ::file::path acme_directory::program_files_x86()
   {

      wstring wstrModuleFolder(e_get_buffer, sizeof(unichar) * 8);

      wstring wstrModuleFilePath(e_get_buffer, sizeof(unichar) * 8);

      wcscpy(wstrModuleFilePath, _wgetenv(L"PROGRAMFILES(X86)"));

      if (wcslen(wstrModuleFilePath) == 0)
      {

         SHGetSpecialFolderPathW(nullptr, wstrModuleFilePath, CSIDL_PROGRAM_FILES, false);

      }

      wstrModuleFilePath.trim_right(L"\\/");

      wcscpy(wstrModuleFolder, wstrModuleFilePath);

      return string(wstrModuleFolder);

   }


   ::file::path acme_directory::program_files()
   {

      wstring wstrModuleFolder(e_get_buffer, sizeof(unichar) * 8);

      wstring wstrModuleFilePath(e_get_buffer, sizeof(unichar) * 8);

      wcscpy(wstrModuleFilePath, _wgetenv(L"PROGRAMW6432"));

      if (wcslen(wstrModuleFilePath) == 0)
      {

         SHGetSpecialFolderPathW(nullptr, wstrModuleFilePath, CSIDL_PROGRAM_FILES, false);

      }

      wstrModuleFilePath.trim_right(L"\\/");

      wstrModuleFolder = wstrModuleFilePath;

      return string(wstrModuleFolder);



   }


   ::file::path acme_directory::stage(string strAppId, string strPlatform, string strConfiguration)
   {

      return inplace_install(strAppId, strPlatform, strConfiguration) / "time" / acmenode()->time_binary_platform(strPlatform) / strConfiguration;

   }



   void acme_directory::set_path_install_folder(const ::string & pszPath)
   {

      m_pathInstallFolder = pszPath;

   }


   ::file::path acme_directory::bookmark()
   {

      return localconfig() / "bookmark";

   }


   ::file::path acme_directory::sys_temp()
   {

      return appdata() / "time";

   }


   ::file::path acme_directory::ca2appdata()
   {

      return ca2roaming() / "appdata";

   }


   ::file::path acme_directory::public_root()
   {

      return program_data() / "ca2";

   }

   ::file::path acme_directory::ca2roaming()
   {

      return roaming() / "ca2";

   }


   ::file::path acme_directory::localconfig()
   {

      return ca2roaming() / "localconfig";

   }


   //

   //::file::path acme_directory::pathfind(const string& pszEnv, const string& pszTopic, const string& pszMode)
   //{

   //   ::file::path_array stra;

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



   //::file::path acme_directory::get_memory_map_base_folder_path()
   //{

   //   return "";

   //}


   ::file::path acme_directory::user_appdata_local()
   {

      return _shell_get_special_folder_path(CSIDL_LOCAL_APPDATA);

   }


   bool acme_directory::_shell_get_special_folder_path(HWND hwnd, ::file::path& str, i32 csidl, bool fCreate)
   {

      return ::SHGetSpecialFolderPathW(hwnd, wstring_adaptor(str, MAX_PATH * 8), csidl, fCreate) != false;

   }


   ::file::path acme_directory::_shell_get_special_folder_path(i32 csidl, bool fCreate, ::windowing::window* pwindow)
   {

      ::file::path path;

      if (!_shell_get_special_folder_path(nullptr, path, csidl, fCreate))
      {

         return "";

      }

      return path;

   }


   ::file::path acme_directory::_get_known_folder(REFKNOWNFOLDERID kfid)
   {

      ::file::path str;

      ::cotaskptr < PWSTR > pwszPath;

      HANDLE hToken = nullptr;

      //::OpenProcessToken(::GetCurrentProcess(), TOKEN_QUERY | TOKEN_IMPERSONATE | TOKEN_DUPLICATE, &hToken);

      HRESULT hr = SHGetKnownFolderPath(kfid, 0, hToken, &pwszPath);

      defer_throw_hresult(hr);

      return pwszPath.m_p;

   }

   
//   bool acme_directory::_is(const char * path1)
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
//      //str.case_insensitive_ends_eat("\\");
//      //str.case_insensitive_ends_eat("/");
//      //str.case_insensitive_ends_eat("\\");
//      //str.case_insensitive_ends_eat("/");
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
//               strRelative.case_insensitive_begins_eat(strPrefix);
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
//#include "acme/operating_system.h"


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


bool windows_file_find_is_dots(const WIN32_FIND_DATAW & data)
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

#pragma push_macro("acmesystem()")

#undef acmesystem()

   using namespace ::winrt::Windowsacmesystem();

#pragma pop_macro("acmesystem()")

#endif


//      ::file::path acme_directory::module()
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
//         throw ::exception(todo);
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

      //       strsize iFind1 = str.rear_find('/', iLast);

      //       strsize iFind2 = str.rear_find('\\', iLast);

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


      //bool acme_directory::create(const char * path)
      //{

      //   return _create(path);

      //}


#ifndef WINDOWS_DESKTOP


      bool acme_directory::_mk(const char * path)
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

            iLastPos = strPrefix.length();

         }

#else

         iLastPos = -1;

#endif

         ::file::path_array stra;

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

               //TRACE("         auto psystem = acmesystem();

         auto pacmedir = psystem->m_pacmedirectory;

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




      ::file::path acme_directory::module()
      {

#ifdef WINDOWS

         wstring path(e_get_buffer, MAX_PATH * 8);

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


      //bool acme_directory::is(const char * path)
      //{

      //   //if (::file::system_dir::g_pthis == nullptr)
      //   //{

      //   return _is(path);

      //   //}

      //   //return ::file::system_dir::g_pthis->is(path, ::get_context_system());

      //}


      void defer_add(::file::listing & listing, const WIN32_FIND_DATAW & finddata)
      {


         if (windows_file_find_is_dots(finddata))
         {

            return;

         }
            
         if (finddata.dwFileAttributes == INVALID_FILE_ATTRIBUTES)
         {

            return;

         }

         ::file::path path;

         string strFilename(finddata.cFileName);

         path = listing.m_pathFinal / strFilename;

         path.m_iBasePathLength = path.length() - strFilename.length();

         bool bDirectory = (finddata.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY);

         path.m_iDir = bDirectory ? 1 : 0;

         path.m_iSize = make64_from32(finddata.nFileSizeLow, finddata.nFileSizeHigh);

         listing.defer_add(path);

      }


      bool acme_directory::enumerate(::file::listing & listing)
      {

         if (listing.m_pathFinal.is_empty())
         {

            listing.m_pathFinal = listing.m_pathUser;

         }

         if (!is(listing.m_pathFinal))
         {

            return false;

         }

         if (!listing.on_start_enumerating(this))
         {

            return true;

         }

         WIN32_FIND_DATAW FindFileData;

         HANDLE hFind;

         hFind = FindFirstFileW(wstring(listing.m_pathFinal) + L"\\*", &FindFileData);

         if (hFind == INVALID_HANDLE_VALUE)
         {

            return true;

         }

         while (true)
         {

            defer_add(listing, FindFileData);

            if (!FindNextFileW(hFind, &FindFileData))
            {

               break;

            }

         }

         FindClose(hFind);

         return true;

      }


      //bool acme_directory::enumerate(::file::listing & listing)
      //{

      //   listing.m_pathFinal = listing.m_pathUser;

      //   if (!is(listing.m_pathFinal))
      //   {

      //      return false;

      //   }

      //   if (!listing.on_start_enumerating(this))
      //   {

      //      return true;

      //   }

      //   WIN32_FIND_DATAW FindFileData;

      //   HANDLE hFind;

      //   hFind = FindFirstFileW(wstring(listing.m_pathFinal) + "\\*", &FindFileData);

      //   if (hFind == INVALID_HANDLE_VALUE)
      //   {

      //      return true;

      //   }

      //   while (true)
      //   {

      //      if (windows_file_find_is_dots(FindFileData)
      //         || FindFileData.dwFileAttributes != INVALID_FILE_ATTRIBUTES)
      //      {

      //         continue;

      //      }

      //      ::file::path path(FindFileData.cFileName);

      //      bool bDirectory = (FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY);

      //      path.m_iDir = bDirectory ? 1 : 0;

      //      path.m_iSize = make64_from32(FindFileData.nFileSizeLow, FindFileData.nFileSizeHigh);

      //      listing.defer_add(path);

      //      if (!FindNextFileW(hFind, &FindFileData))
      //      {

      //         break;

      //      }

      //   }

      //   FindClose(hFind);

      //}

      //void acme_directory::rls_dir(::file::path_array & stra, const scoped_string & str)
      //{

      //   ::count start = stra.get_count();

      //   ls_dir(stra, psz);

      //   ::count end = stra.get_count();

      //   for (::index i = start; i < end; i++)
      //   {

      //      ::file::path path = stra[i];

      //      rls_dir(stra, path);

      //   }

      //}


//      void acme_directory::ls(::file::path_array & stra, const scoped_string & str)
//      {
//
//#if defined(LINUX) || defined(__APPLE__) || defined(ANDROID)
//
//         DIR * dirp = opendir(psz);
//
//         if (dirp == nullptr)
//            return;
//
//         dirent * dp;
//         ::file::path path;
//         while ((dp = readdir(dirp)) != nullptr)
//         {
//
//            if (strcmp(dp->d_name, "..") == 0)
//               continue;
//            else if (strcmp(dp->d_name, ".") == 0)
//               continue;
//            path = psz / dp->d_name;
//            path.m_iDir = dp->d_type & DT_DIR ? 1 : 0;
//            path.m_iSize = -1;
//            stra.add(path);
//
//            //output_debug_string("flood for you: dir::ls ----> " + path);
//
//         }
//
//         closedir(dirp);
//
//#elif defined(_UWP)
//
//         ::winrt::Windows::Storage::StorageFolder ^ folder = nullptr;
//
//         string strPrefix;
//
//         string str = psz;
//
//         try
//         {
//
//            if (string(psz).case_insensitive_order("image://") == 0)
//            {
//
//               strPrefix = "image://";
//
//               try
//               {
//
//                  folder = ::winrt::Windows::Storage::KnownFolders::PicturesLibrary;
//
//               }
//               catch (...)
//               {
//
//                  folder = nullptr;
//
//               }
//
//            }
//            else if (string(psz).case_insensitive_order("music://") == 0)
//            {
//
//               strPrefix = "music://";
//
//               try
//               {
//
//                  folder = ::winrt::Windows::Storage::KnownFolders::MusicLibrary;
//
//               }
//               catch (...)
//               {
//
//                  folder = nullptr;
//
//               }
//
//            }
//            else if (string(psz).case_insensitive_order("video://") == 0)
//            {
//
//               strPrefix = "video://";
//
//               try
//               {
//
//                  folder = ::winrt::Windows::Storage::KnownFolders::VideosLibrary;
//
//               }
//               catch (...)
//               {
//
//                  folder = nullptr;
//
//               }
//
//            }
//            else if (string(psz).case_insensitive_order("document://") == 0)
//            {
//
//               strPrefix = "document://";
//
//               try
//               {
//
//                  folder = ::winrt::Windows::Storage::KnownFolders::DocumentsLibrary;
//
//               }
//               catch (...)
//               {
//
//                  folder = nullptr;
//
//               }
//
//            }
//            else
//            {
//
//               if (str.case_insensitive_begins_eat("image://"))
//               {
//
//                  strPrefix = "image://";
//
//                  try
//                  {
//
//                     folder = ::winrt::Windows::Storage::KnownFolders::PicturesLibrary;
//
//                  }
//                  catch (...)
//                  {
//
//                     folder = nullptr;
//
//                  }
//
//               }
//
//               if (str.case_insensitive_begins_eat("music://"))
//               {
//
//                  strPrefix = "music://";
//
//                  try
//                  {
//
//                     folder = ::winrt::Windows::Storage::KnownFolders::MusicLibrary;
//
//                  }
//                  catch (...)
//                  {
//
//                     folder = nullptr;
//
//                  }
//
//               }
//
//               if (str.case_insensitive_begins_eat("video://"))
//               {
//
//                  strPrefix = "video://";
//
//                  try
//                  {
//
//                     folder = ::winrt::Windows::Storage::KnownFolders::VideosLibrary;
//
//                  }
//                  catch (...)
//                  {
//
//                     folder = nullptr;
//
//                  }
//
//               }
//
//               if (str.case_insensitive_begins_eat("document://"))
//               {
//
//                  strPrefix = "document://";
//
//                  try
//                  {
//
//                     folder = ::winrt::Windows::Storage::KnownFolders::DocumentsLibrary;
//
//                  }
//                  catch (...)
//                  {
//
//                     folder = nullptr;
//
//                  }
//
//               }
//
//               if (strPrefix.has_char())
//               {
//
//                  string_array stra;
//
//                  stra.explode("/", str);
//
//                  string str;
//
//                  while (stra.get_count() > 0)
//                  {
//
//                     str = stra[0];
//
//                     if (str.has_char())
//                     {
//
//                        folder = wait(folder->GetFolderAsync(str));
//
//                        strPrefix += str + "/";
//
//                     }
//
//                     stra.erase_at(0);
//
//                  }
//
//               }
//               else
//               {
//
//                  folder = ::winrt::Windows::Storage::StorageFolder::GetFolderFromPathAsync(str).get();
//
//                  strPrefix = str + "/";
//
//               }
//
//            }
//
//         }
//         catch (...)
//         {
//
//            return;
//
//         }
//
//         if (folder == nullptr)
//         {
//
//            return;
//
//         }
//
//         string strPath = string(begin(folder->Path));
//
//         auto a = folder->GetItemsAsync().get();
//
//         for (u32 u = 0; u < a->Size; u++)
//         {
//
//            string strPath = string(begin(a->GetAt(u)->Path));
//
//            ::file::path path(strPath);
//
//            string str = path;
//
//            path.m_iDir = a->GetAt(u)->IsOfType(::winrt::Windows::Storage::StorageItemTypes::Folder) ? 1 : 0;
//
//            stra.add(path);
//
//         }
//
//
//#else
//
//         WIN32_FIND_DATAW FindFileData;
//
//         HANDLE hFind;
//
//         hFind = FindFirstFileW(wstring(psz) + "\\*", &FindFileData);
//
//         if (hFind == INVALID_HANDLE_VALUE)
//         {
//
//            return;
//
//         }
//
//         while (true)
//         {
//
//            if (!windows_file_find_is_dots(FindFileData) && (FindFileData.dwFileAttributes != INVALID_FILE_ATTRIBUTES))
//               stra.add(::file::path(FindFileData.cFileName));
//
//            //if (stra.has_elements() && stra.last() == "teste")
//            //{
//            //   output_debug_string("teste");
//            //}
//
//            if (!FindNextFileW(hFind, &FindFileData))
//               break;
//
//         }
//
//         FindClose(hFind);
//
//#endif
//
//
//      }
//

//      void acme_directory::ls_dir(::file::path_array & stra, const scoped_string & str)
//      {
//
//#if defined(LINUX) || defined(__APPLE__) || defined(ANDROID)
//
//         DIR * dirp = opendir(psz);
//
//         if (dirp == nullptr)
//            return;
//
//         dirent * dp;
//
//         while ((dp = readdir(dirp)) != nullptr)
//         {
//            if (dp->d_name[0] == '.')
//            {
//               if (dp->d_name[1] == '\0')
//                  continue;
//               if (dp->d_name[1] == '.')
//               {
//                  if (dp->d_name[2] == '\0')
//                     continue;
//               }
//            }
//            ::file::path strPath = psz / dp->d_name;
//            if (is(strPath))
//            {
//               stra.add(strPath);
//            }
//
//         }
//
//         closedir(dirp);
//
//#elif defined(_UWP)
//
//         ::winrt::Windows::Storage::StorageFolder ^ folder = wait(::winrt::Windows::Storage::StorageFolder::GetFolderFromPathAsync(string(psz)));
//
//         ::winrt::Windows::Foundation::Collections::IVectorImpact < ::winrt::Windows::Storage::StorageFolder ^ > ^ a = wait(folder->GetFoldersAsync());
//
//         for (u32 u = 0; u < a->Size; u++)
//         {
//            stra.add(begin(a->GetAt(u)->Path));
//         }
//
//
//#else
//
//         WIN32_FIND_DATAW FindFileData;
//
//         HANDLE hFind;
//
//         hFind = FindFirstFileW(wstring(psz), &FindFileData);
//
//         if (hFind == INVALID_HANDLE_VALUE)
//            return;
//
//         while (true)
//         {
//
//            if (!windows_file_find_is_dots(FindFileData) && (FindFileData.dwFileAttributes != INVALID_FILE_ATTRIBUTES) && (FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0)
//            {
//
//               stra.add(::file::path(FindFileData.cFileName));
//
//            }
//
//            stra.add(::file::path(FindFileData.cFileName));
//
//            if (!FindNextFileW(hFind, &FindFileData))
//               break;
//
//         }
//
//         FindClose(hFind);
//
//#endif
//
//
//      }
//
//
//      void acme_directory::ls_file(::file::path_array & stra, const scoped_string & str)
//      {
//
//#if defined(LINUX) || defined(__APPLE__) || defined(ANDROID)
//
//         DIR * dirp = opendir(psz);
//
//         if (dirp == nullptr)
//            return;
//
//         dirent * dp;
//
//         while ((dp = readdir(dirp)) != nullptr)
//         {
//            if (dp->d_name[0] == '.')
//            {
//               if (dp->d_name[1] == '\0')
//                  continue;
//               if (dp->d_name[1] == '.')
//               {
//                  if (dp->d_name[2] == '\0')
//                     continue;
//               }
//            }
//            ::file::path strPath = psz / dp->d_name;
//            if (!is(strPath))
//            {
//               stra.add(strPath);
//            }
//
//         }
//
//         closedir(dirp);
//
//#elif defined(_UWP)
//
//         ::winrt::Windows::Storage::StorageFolder ^ folder = wait(::winrt::Windows::Storage::StorageFolder::GetFolderFromPathAsync(string(psz)));
//
//         ::winrt::Windows::Foundation::Collections::IVectorImpact < ::winrt::Windows::Storage::StorageFolder ^ > ^ a = wait(folder->GetFoldersAsync());
//
//         for (u32 u = 0; u < a->Size; u++)
//         {
//            stra.add(begin(a->GetAt(u)->Path));
//         }
//
//
//#else
//
//         WIN32_FIND_DATAW FindFileData;
//
//         HANDLE hFind;
//
//         hFind = FindFirstFileW(wstring(psz), &FindFileData);
//
//         if (hFind == INVALID_HANDLE_VALUE)
//            return;
//
//         while (true)
//         {
//
//            if (!windows_file_find_is_dots(FindFileData) && (FindFileData.dwFileAttributes != INVALID_FILE_ATTRIBUTES) && (FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0)
//            {
//            }
//            else
//            {
//               stra.add(::file::path(FindFileData.cFileName));
//            }
//
//
//            stra.add(::file::path(FindFileData.cFileName));
//
//            if (!FindNextFileW(hFind, &FindFileData))
//               break;
//
//         }
//
//         FindClose(hFind);
//
//#endif
//
//      }
//
//
      ::file::path acme_directory::pathfind(const string & pszEnv, const string & pszTopic, const string & pszMode)
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


      ::file::path acme_directory::archive()
      {

#ifdef WINDOWS

         ::file::path pathArchive = getenv("__archive");

         if (pathArchive.is_empty())
         {

            return "C:\\archive";

         }

         return pathArchive;

#else

         return "/archive";

#endif

      }


      ::file::path acme_directory::tool()
      {

         return archive() / "tool-windows";

      }


      //int acme_directory::make_path(const scoped_string & str)
      //{


      //   return create(psz) != false;

      //}


//      void acme_directory::__create(const char * pathParam)
//      {
//
//         if (is(pathParam))
//         {
//
//            return;
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
//         ::file::path_array stra;
//
//         path.ascendants_path(stra);
//
//         index i = stra.get_upper_bound() - 1;
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
//            return;
//
//         }
//
//         for (; i < stra.get_count(); i++)
//         {
//
//            string strDir = stra[i];
//
//            try
//            {
//
//               create_directory(strDir);
//
//            }
//            catch(const ::exception & exception)
//            {
//
//               if(exception.m_estatus == error_already_exists)
//               {
//
//                  if (m_pacmefile->exists(strDir))
//                  {
//
//                     m_pacmefile->delete_file(strDir);
//
//                     create_directory(strDir);
//
//                  }
//
//               }
//               else
//               {
//
//                  throw ::exception;
//
//               }
//
////#ifdef WINDOWS_DESKTOP
////
////               WCHAR * pwszError;
////
////               FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, nullptr, dwError, 0, (WCHAR *)&pwszError, 8, nullptr);
////
////               //TRACE("         auto psystem = acmesystem();
////
//////         auto pacmedir = psystem->m_pacmedirectory;
//////
//////pacmedir->create CreateDirectoryW last error(%d)=%s", dwError, pszError);
//////
////               ::LocalFree(pwszError);
////
////               //m_isdirmap.set(stra[i], false);
////
////#endif
////
////               //return false;
//
//            }
//
//         }
//
//         //return true;
//
//      //}
//
//   }


   string acme_directory::get_current()
   {

      auto size = GetCurrentDirectoryW(0, nullptr);

      wstring wstr;

      auto buffer = wstr.get_string_buffer(size);

      GetCurrentDirectoryW(size + 1, buffer);

      wstr.release_string_buffer(size);

      string str(wstr);

      return str;

   }


   void acme_directory::change_current(const scoped_string & str)
   {

      wstring wstr(str);

      if (!SetCurrentDirectoryW(wstr))
      {

         DWORD dwLastError = ::GetLastError();

         auto estatus = ::windows::last_error_status(dwLastError);

         throw ::exception(estatus, "windows::acme_directory::change_current");

      }

      //return ::success;

   }




   //::file::path acme_directory::program_files_x86()
   //{

   //   wstring wstrModuleFolder(e_get_buffer, sizeof(unichar) * 8);

   //   wstring wstrModuleFilePath(e_get_buffer, sizeof(unichar) * 8);

   //   wcscpy(wstrModuleFilePath, _wgetenv(L"PROGRAMFILES(X86)"));

   //   if (wcslen(wstrModuleFilePath) == 0)
   //   {

   //      SHGetSpecialFolderPathW(nullptr, wstrModuleFilePath, CSIDL_PROGRAM_FILES, false);

   //   }

   //   wstrModuleFilePath.trim_right(L"\\/");

   //   wcscpy(wstrModuleFolder, wstrModuleFilePath);

   //   return string(wstrModuleFolder);

   //}


   //::file::path acme_directory::program_files()
   //{

   //   wstring wstrModuleFolder(e_get_buffer, sizeof(unichar) * 8);

   //   wstring wstrModuleFilePath(e_get_buffer, sizeof(unichar) * 8);

   //   wcscpy(wstrModuleFilePath, _wgetenv(L"PROGRAMW6432"));

   //   if (wcslen(wstrModuleFilePath) == 0)
   //   {

   //      SHGetSpecialFolderPathW(nullptr, wstrModuleFilePath, CSIDL_PROGRAM_FILES, false);

   //   }

   //   wstrModuleFilePath.trim_right(L"\\/");

   //   wstrModuleFolder = wstrModuleFilePath;

   //   return string(wstrModuleFolder);



   //}




} // namespace acme_windows



