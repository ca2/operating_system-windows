// Create on 2021-03-21 20:00 <3ThomasBS_
#include "framework.h"
#include "directory_system.h"
#include "file_system.h"
#include "acme/exception/exception.h"
#include "acme/filesystem/filesystem/listing.h"
#include "acme/operating_system/process.h"
#include "acme/platform/application.h"
#include "acme/platform/node.h"
#include "acme/prototype/string/adaptor.h"
#include "acme/prototype/string/str.h"
#include "acme/operating_system/windows_common/com/cotaskptr.h"
#include "acme/operating_system/windows_common/com/hresult_exception.h"

#include "acme/_operating_system.h"
#include <Shlobj.h>


#include "acme/operating_system/windows_common/find_file.h"


//#ifdef WINDOWS_DESKTOP
//
//
//#include <Shlobj.h>


namespace acme_windows
{

   
   directory_system::directory_system()
   {

   }


   directory_system::~directory_system()
   {


   }


   string directory_system::dir_root()
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


   ::file::path directory_system::get_memory_map_base_folder_path() 
   {

      auto path = _get_known_folder(FOLDERID_RoamingAppData);

      path /= "ca2/memory_map";

      return path;

   }


   ::file::path directory_system::home()
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


   ::file::path directory_system::program_data()
   {

      return _get_known_folder(FOLDERID_ProgramData);

   }


   ::file::path directory_system::application_data_base()
   {

      return roaming();

   }


   ::file::path directory_system::roaming()
   {

      return _get_known_folder(FOLDERID_RoamingAppData);

   }


   ::file::path directory_system::appdata()
   {

      return roaming() / appid();

   }


   // ::file::path directory_system::public_system()
   // {
   //
   //    return public_root() / "system";
   //
   // }
   //

   ::file::path directory_system::userconfig()
   {

      return roaming() / "user";

   }


   ::file::path directory_system::config()
   {

      return ca2roaming() / "config";

   }


   ::file::path directory_system::local()
   {

      return ca2roaming() / "local";

   }


   ::file::path directory_system::sensitive()
   {

      return acme_windows_common::directory_system::sensitive();

   }







   string directory_system::system_short_name()
   {

   #ifdef UNIVERSAL_WINDOWS

      return "metro";

   #else

      ::file::path pathSystemShortName = localconfig() / "system_short_name.txt";

      return file_system()->as_string(pathSystemShortName).trimmed();

   #endif

   }


   ::file::path directory_system::relative(::file::path path)
   {

      path.replace_with("", ":");

      path.case_insensitive_ends_eat(".exe");

      return path;

   }

   #ifdef UNIVERSAL_WINDOWS


   ::file::path directory_system::app_relative()
   {

      return "";

   }


   #else


   ::string directory_system::appid()
   {

      return ::acme_windows_common::directory_system::appid();

   }


   #endif



   ::file::path directory_system::inplace_install(const ::scoped_string & scopedstrAppId, const ::scoped_string & scopedstrPlatform, const ::scoped_string & scopedstrConfiguration)
   {

   #ifdef WINDOWS_DESKTOP

      ::file::path path;

      string strFolder;

      character_count iFind = scopedstrAppId.find_index('/');

      if (scopedstrPlatform.case_insensitive_order("win32") == 0 || scopedstrPlatform.case_insensitive_order("x86") == 0)
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

         path /= scopedstrAppId;

      }
      else
      {

         path /= scopedstrAppId.left(iFind);

         path /= scopedstrAppId.substr(iFind + 1);

      }

      return path;

   #elif defined(ANDROID)

         auto psystem = system();

         auto pacmedir = psystem->m_pdirectorysystem;


      return          auto psystem = system();

         auto pacmedir = psystem->m_pdirectorysystem;

pacmedir->roaming();

   #else

      return path_system()->app_module().folder(4);

   #endif


   }


   ::file::path directory_system::inplace_matter_install(const ::scoped_string & scopedstrAppId, const ::scoped_string & scopedstrPlatform, const ::scoped_string & scopedstrConfiguration)
   {

   #ifdef WINDOWS_DESKTOP

      ::file::path path;

      string strFolder;

      character_count iFind = scopedstrAppId.find_index('/');

      path = ca2roaming();

      path /= "_matter";

      return path;

   #elif defined(ANDROID)

         auto psystem = system();

         auto pacmedir = psystem->m_pdirectorysystem;


      return          auto psystem = system();

         auto pacmedir = psystem->m_pdirectorysystem;

pacmedir->roaming();

   #else

      return path_system()->app_module().folder(4);

   #endif


   }


   ::file::path directory_system::install()
   {

      if (m_pathInstallFolder.is_empty())
      {

         return default_install();

      }

      return m_pathInstallFolder;

   }


   ::file::path directory_system::default_install()
   {

   #ifdef ANDROID
            auto psystem = system();

         auto pacmedir = psystem->m_pdirectorysystem;



      return          auto psystem = system();

         auto pacmedir = psystem->m_pdirectorysystem;

pacmedir->roaming();

   #elif defined(__APPLE__)

      return file_system()->module()-3;

   #else

      return file_system()->module()-4;

   #endif

   }


   ::file::path directory_system::beforeca2()
   {

      return ::file_path_folder(install());

   }






   ::file::path directory_system::program_files_x86()
   {

      wstring wstrModuleFolder;

      wstring wstrModuleFilePath;

      wstrModuleFilePath = _wgetenv(L"PROGRAMFILES(X86)");

      if (wcslen(wstrModuleFilePath) == 0)
      {

         auto p = wstrModuleFilePath.get_buffer(MAX_PATH * 8);

         SHGetSpecialFolderPathW(nullptr, p, CSIDL_PROGRAM_FILES, false);

         wstrModuleFilePath.release_buffer();

      }

      wstrModuleFilePath.trim_right(L"\\/");

      wstrModuleFolder = wstrModuleFilePath;

      return string(wstrModuleFolder);

   }


   ::file::path directory_system::program_files()
   {

      wstring wstrModuleFolder;

      wstring wstrModuleFilePath;

      wstrModuleFilePath = _wgetenv(L"PROGRAMW6432");

      if (wcslen(wstrModuleFilePath) == 0)
      {

         auto p = wstrModuleFilePath.get_buffer(MAX_PATH * 8);

         SHGetSpecialFolderPathW(nullptr, p, CSIDL_PROGRAM_FILES, false);

         wstrModuleFilePath.release_buffer();

      }

      wstrModuleFilePath.trim_right(L"\\/");

      wstrModuleFolder = wstrModuleFilePath;

      return string(wstrModuleFolder);

   }


   ::file::path directory_system::stage(const ::scoped_string & scopedstrAppId, const ::scoped_string & scopedstrPlatform, const ::scoped_string & scopedstrConfiguration)
   {

      return inplace_install(scopedstrAppId, scopedstrPlatform, scopedstrConfiguration) / "time" / node()->time_binary_platform(scopedstrPlatform) / scopedstrConfiguration;

   }



   void directory_system::set_path_install_folder(const ::scoped_string & scopedstrPath)
   {

      m_pathInstallFolder = scopedstrPath;

   }


   ::file::path directory_system::bookmark()
   {

      return localconfig() / "bookmark";

   }


   ::file::path directory_system::sys_temp()
   {

      return appdata() / "time";

   }


   ::file::path directory_system::ca2appdata()
   {

      return ca2roaming() / "appdata";

   }


   ::file::path directory_system::public_root()
   {

      return program_data() / "ca2";

   }

   ::file::path directory_system::ca2roaming()
   {

      return roaming() / "ca2";

   }


   ::file::path directory_system::localconfig()
   {

      return ca2roaming() / "localconfig";

   }


   //

   //::file::path directory_system::pathfind(const ::scoped_string & scopedstrEnv, const ::scoped_string & scopedstrTopic, const ::scoped_string & scopedstrMode)
   //{

   //   ::file::path_array stra;

   //   stra.add_tokens(pszEnv, ":", false);

   //   string strCandidate;

   //   for (int i = 0; i < stra.get_count(); i++)
   //   {

   //      strCandidate = stra[i] / pszTopic;

   //      //if (m_papplication->file().exists(strCandidate))
   //      if (m_pfilesystem->exists(strCandidate))
   //      {

   //         return strCandidate;

   //      }

   //   }

   //   return "";

   //}



   //::file::path directory_system::get_memory_map_base_folder_path()
   //{

   //   return "";

   //}


   ::file::path directory_system::user_appdata_local()
   {

      return _shell_get_special_folder_path(CSIDL_LOCAL_APPDATA);

   }


   bool directory_system::_shell_get_special_folder_path(HWND hwnd, ::file::path& str, int csidl, bool fCreate)
   {

      return ::SHGetSpecialFolderPathW(hwnd, wstring_adaptor(str, MAX_PATH * 8), csidl, fCreate) != false;

   }


   ::file::path directory_system::_shell_get_special_folder_path(int csidl, bool fCreate, ::windowing::window* pwindow)
   {

      ::file::path path;

      if (!_shell_get_special_folder_path(nullptr, path, csidl, fCreate))
      {

         return "";

      }

      return path;

   }


   ::file::path directory_system::_get_known_folder(REFKNOWNFOLDERID kfid)
   {

      ::file::path str;

      ::cotaskptr < PWSTR > pwszPath;

      HANDLE hToken = nullptr;

      //::OpenProcessToken(::GetCurrentProcess(), TOKEN_QUERY | TOKEN_IMPERSONATE | TOKEN_DUPLICATE, &hToken);

      HRESULT hr = SHGetKnownFolderPath(kfid, 0, hToken, &pwszPath);

      defer_throw_hresult(hr);

      return pwszPath.m_p;

   }

   
//   bool directory_system::_is(const_char_pointer path1)
//   {
//
//#ifdef UNIVERSAL_WINDOWS
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
//      unsigned int dwFileAttributes = ::windows_get_file_attributes(path1);
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
//         unsigned int dwLastError = ::GetLastError();
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
#elif defined(UNIVERSAL_WINDOWS)
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


#if defined(UNIVERSAL_WINDOWS)

#pragma push_macro("system()")

#undef system()

   using namespace ::winrt::Windowsacmesystem();

#pragma pop_macro("system()")

#endif


//      ::file::path directory_system::module()
//      {
//
//#if defined(UNIVERSAL_WINDOWS)
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
//         if (!GetModuleFileNameW(hmodule, wstrModuleFilePath, (unsigned int)wstrModuleFilePath.length()))
//         {
//
//            return "";
//
//         }
//
//         LPWSTR pszModuleFileName;
//
//         if (!GetFullPathNameW(wstrModuleFilePath, (unsigned int)wstrModuleFilePath.length(), wstrModuleFolder, &pszModuleFileName))
//         {
//
//            return "";
//
//         }
//
//         wstrModuleFolder.release_buffer();
//
//         wstrModuleFolder.trim_right(L"\\/");
//
//         return wstrModuleFolder;
//
//#else
//
//         string strModuleFolder;
//
//         auto wstrModuleFolder = strModuleFolder.get_buffer(MAX_PATH * 8);
//
//         throw ::exception(todo);
//
//         return wstrModuleFolder;
//
//#endif
//
//      }
//

      // bool eat_end_level(string & str, int iLevelCount, const_char_pointer pSeparator)
      // {

      //    character_count iLast = str.length() - 1;

      //    if(iLast < 0)
      //       return iLevelCount <= 0;

      //    while(str[iLast] == '/' || str[iLast] == '\\')
      //       iLast--;

      //    for(int i = 0; i < iLevelCount; i++)
      //    {

      //       character_count iFind1 = str.rear_find('/', iLast);

      //       character_count iFind2 = str.rear_find('\\', iLast);

      //       character_count iFind = maximum(iFind1, iFind2);

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
      //   #elif defined(UNIVERSAL_WINDOWS)
      //
      //      str = "";
      //
      //   #elif defined(__APPLE__)
      //
      //      {
      //
      //         str = get_exe_path();
      //
      //         if(str.has_character())
      //         {
      //
      //            goto found;
      //
      //         }
      //
      //         str = ::dir::pathfind(::file::path(str).folder(), "libacme.dylib", "rfs"); // readable - normal file - non zero double_size
      //
      //         if(str.has_character())
      //         {
      //
      //            goto found;
      //
      //         }
      //
      //         str = ::dir::pathfind(getenv("DYLD_LIBRARY_PATH"), "libacme.dylib", "rfs"); // readable - normal file - non zero double_size
      //
      //         if(str.has_character())
      //         {
      //
      //            goto found;
      //
      //         }
      //
      //         str = get_exe_path();
      //
      //         if(str.has_character())
      //         {
      //
      //            goto found;
      //
      //         }
      //
      //         str = ::dir::pathfind(getenv("DYLD_FALLBACK_LIBRARY_PATH"), "libacme.dylib", "rfs"); // readable - normal file - non zero double_size
      //
      //         if(str.has_character())
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
      //      s_pstrCalc = ___new string(str);
      //
      //      return *s_pstrCalc;
      //
      //
      //   }


      //bool directory_system::create(const_char_pointer path)
      //{

      //   return _create(path);

      //}


#ifndef WINDOWS_DESKTOP


      bool directory_system::_mk(const_char_pointer path)
      {

         if (is(path))
         {

            return true;

         }

         string strName;

         ::file::path pathFolder;

         character_count iLastPos;

#ifdef UNIVERSAL_WINDOWS

         {

            string strPath = path;

            string strPrefix;

            winrt_folder(strPath, strPrefix);

            pathFolder = strPrefix;

            iLastPos = strPrefix.length();

         }

#else

         iLastPos = -1;

#endif

         ::file::path_array stra;

         path.ascendants_path(stra);

         ::collection::index i = stra.get_upper_bound();

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

               //informationf("         auto psystem = system();

         auto pacmedir = psystem->m_pdirectorysystem;

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




      ::file::path directory_system::module()
      {

#ifdef WINDOWS

         wstring path;

         auto p = path.get_buffer(MAX_PATH * 8);

         if (!GetModuleFileNameW(nullptr, p, (unsigned int)path.size()))
         {

            return "";

         }

         path.release_buffer();

         string strPath(path);

         strPath = solve_relative(strPath);

         ::file::path pathFolder = file_path_folder(strPath);

         return pathFolder;

#else

         return "/acme/stage";

#endif

      }


      //bool directory_system::is(const_char_pointer path)
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

         if (bDirectory)
         {

            path.set_existent_folder();

         }
         else
         {

            path.set_existent_file();


         }

         path.m_iSize = make64_from32(finddata.nFileSizeLow, finddata.nFileSizeHigh);

         listing.defer_add(path);

      }


      bool directory_system::enumerate(::file::listing & listing)
      {

         if (listing.m_pathFinal.is_empty())
         {

            listing.m_pathFinal = listing.m_pathUser;

         }

         if (!is(listing.m_pathFinal))
         {

            listing.m_pathFinal = m_papplication->defer_process_path(listing.m_pathFinal);

            if (!is(listing.m_pathFinal))
            {

               return false;

            }

         }

         if (!listing.on_start_enumerating(this))
         {

            return true;

         }

         ::windows::find_file findfile;

         auto windowsPath = listing.m_pathFinal.windows_path().path();

         if(!findfile.find_first_file(windowsPath + L"\\*"))
         {

            return true;

         }

         do
         {

            defer_add(listing, findfile.m_finddata);

         } while (findfile.find_next_file());

         return true;

      }


      //bool directory_system::enumerate(::file::listing & listing)
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

      //void directory_system::rls_dir(::file::path_array & stra, const scoped_string & str)
      //{

      //   ::collection::count start = stra.get_count();

      //   ls_dir(stra, psz);

      //   ::collection::count end = stra.get_count();

      //   for (::collection::index i = start; i < end; i++)
      //   {

      //      ::file::path path = stra[i];

      //      rls_dir(stra, path);

      //   }

      //}


//      void directory_system::ls(::file::path_array & stra, const scoped_string & str)
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
//#elif defined(UNIVERSAL_WINDOWS)
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
//               if (strPrefix.has_character())
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
//                     if (str.has_character())
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
//         for (unsigned int u = 0; u < a->Size; u++)
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

//      void directory_system::ls_dir(::file::path_array & stra, const scoped_string & str)
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
//#elif defined(UNIVERSAL_WINDOWS)
//
//         ::winrt::Windows::Storage::StorageFolder ^ folder = wait(::winrt::Windows::Storage::StorageFolder::GetFolderFromPathAsync(string(psz)));
//
//         ::winrt::Windows::Foundation::Collections::IVectorImpact < ::winrt::Windows::Storage::StorageFolder ^ > ^ a = wait(folder->GetFoldersAsync());
//
//         for (unsigned int u = 0; u < a->Size; u++)
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
//      void directory_system::ls_file(::file::path_array & stra, const scoped_string & str)
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
//#elif defined(UNIVERSAL_WINDOWS)
//
//         ::winrt::Windows::Storage::StorageFolder ^ folder = wait(::winrt::Windows::Storage::StorageFolder::GetFolderFromPathAsync(string(psz)));
//
//         ::winrt::Windows::Foundation::Collections::IVectorImpact < ::winrt::Windows::Storage::StorageFolder ^ > ^ a = wait(folder->GetFoldersAsync());
//
//         for (unsigned int u = 0; u < a->Size; u++)
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
      ::file::path directory_system::pathfind(const ::scoped_string & scopedstrEnv, const ::scoped_string & scopedstrTopic, const ::scoped_string & scopedstrMode)
      {

         string_array stra;

         stra.add_tokens(scopedstrEnv, ":");

         string strCandidate;

         for (int i = 0; i < stra.get_count(); i++)
         {

            if (stra[i].is_empty())
               continue;

            strCandidate = ::file::path(stra[i]) / scopedstrTopic;

            if (m_pfilesystem->exists(strCandidate))
            {
               return strCandidate;
            }

         }

         return "";

      }


      ::file::path directory_system::archive()
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


      ::file::path directory_system::tool()
      {

         return archive() / "tool-windows";

      }


      //int directory_system::make_path(const scoped_string & str)
      //{


      //   return create(psz) != false;

      //}


//      void directory_system::__øcreate(const_char_pointer pathParam)
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
//         ::file::path pathFolder;
//
//         character_count iLastPo = -1;
//
//         ::file::path_array stra;
//
//         path.ascendants_path(stra);
//
//         ::collection::index i = stra.get_upper_bound() - 1;
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
//                  if (m_pfilesystem->exists(strDir))
//                  {
//
//                     m_pfilesystem->delete_file(strDir);
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
////               //informationf("         auto psystem = system();
////
//////         auto pacmedir = psystem->m_pdirectorysystem;
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


   ::file::path directory_system::get_current()
   {

      auto size = GetCurrentDirectoryW(0, nullptr);

      wstring wstr;

      auto buffer = wstr.get_buffer(size);

      GetCurrentDirectoryW(size + 1, buffer);

      wstr.release_buffer(size);

      string str(wstr);

      return str;

   }


   void directory_system::change_current(const ::file::path & pathParam)
   {

      auto path = m_papplication->defer_process_path(pathParam);

      auto windowspath = path.windows_path();

      if (!::SetCurrentDirectoryW(windowspath.extended_path()))
      {

         throw_last_error_exception();

      }

      //return ::success;

   }




   //::file::path directory_system::program_files_x86()
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


   //::file::path directory_system::program_files()
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


   ::file::path directory_system::temp()
   {

      ::string strPath;

      if (!::GetTempPathW(MAX_PATH * 8, ::wstring_adaptor(strPath, MAX_PATH * 8)))
      {

         throw_last_error_exception();

      }

      return strPath;

   }

   /*::file::path node::current_directory()
   {

      ::string str;

      if (!::GetCurrentDirectoryW(MAX_PATH * 8, wstring_adaptor(str, MAX_PATH * 8)))
      {

         throw_last_error_exception();

      }

      return str;

   }*/


   //::file::path directory_system::msys2()
   //{

   //   ::file::path pathMsys2;

   //   pathMsys2 = "C:\\msys64";

   //   return pathMsys2;

   //}



   ::file::path directory_system::windows()
   {

      return _get_known_folder(FOLDERID_Windows);

   }





   ::file::path directory_system::system_drive()
   {

      auto windows = this->windows();

      auto system_drive = windows.folder();

      return system_drive;

   }


   ::file::path directory_system::___fonts()
   {

      return this->fonts();

   }


   ::file::path directory_system::fonts()
   {

      return this->windows() / "Fonts";

   }



   void directory_system::initialize(::particle * pparticle)
   {

      //auto estatus =

      ::directory_system::initialize(pparticle);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      m_pathInstall = this->install();

      this->m_pplatformdir->_shell_get_special_folder_path(
         nullptr,
         m_strCommonAppData,
         CSIDL_COMMON_APPDATA,
         false);
      //shell_get_special_folder_path(
      // nullptr,
      //m_pathProfile,
      //CSIDL_PROFILE,
      //false);

      m_pathHome = this->m_pplatformdir->_get_known_folder(FOLDERID_Profile);

      m_pathCa2Config = this->ca2roaming();

      m_strCommonAppData /= "ca2";

      m_strAppData = this->m_pplatformdir->_get_known_folder(FOLDERID_RoamingAppData);

      this->m_pplatformdir->_shell_get_special_folder_path(
         nullptr,
         m_strPrograms,
         CSIDL_PROGRAMS,
         false);
      this->m_pplatformdir->_shell_get_special_folder_path(
         nullptr,
         m_strCommonPrograms,
         CSIDL_COMMON_PROGRAMS,
         false);

      {

         //string strRelative;
         //strRelative = install();
         //index iFind = strRelative.find(':');
         //if (iFind >= 0)
         //{
         //   character_count iFind1 = strRelative.rear_find("\\", iFind);
         //   character_count iFind2 = strRelative.rear_find("/", iFind);
         //   character_count iStart = maximum(iFind1 + 1, iFind2 + 1);
         //   strRelative = strRelative.left()(iFind - 1) + "_" + strRelative.substr(iStart, iFind - iStart) + strRelative.substr(iFind + 1);
         //}



      }

      if (m_strTimeFolder.is_empty())
      {

         m_strTimeFolder = this->appdata() / "time";

      }

      if (m_strNetSeedFolder.is_empty())
      {

         m_strNetSeedFolder = this->install() / "net";

      }

      auto psystem = system();

      auto pacmedir = psystem->m_pdirectorysystem;

      pacmedir->create(m_strTimeFolder);
      //xxdebug_box("win_dir::initialize (m_strTimeFolder)", "win_dir::initialize", 0);

      if (!pacmedir->is(m_strTimeFolder))
      {
         //return false;

      }

          /*     auto psystem = system();

         auto pacmedir = psystem->m_pdirectorysystem;*/

      pacmedir->create(m_strTimeFolder / "time");

      //xxdebug_box("win_dir::initialize", "win_dir::initialize", 0);

      //return ::success;

   }


   void directory_system::init_system()
   {

      //auto estatus =

      ::directory_system::init_system();

      //if (!estatus)
      //{

      //   return estatus;

      //}


      //return ::success;

   }


} // namespace acme_windows



