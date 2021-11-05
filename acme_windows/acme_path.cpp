// Create on 2021-03-22 09:12 <3ThomasBS_
#include "framework.h"


namespace windows
{

   
   acme_path::acme_path()
   {

      m_pplatformpath = this;

   }


   acme_path::~acme_path()
   {


   }



   // ::file::path acme_path::ca2_module()
   //       {
      
   //       #if defined(ANDROID)
      
   //          return m_psystem->m_pacmepath->app_module().folder();
      
   //       #elif defined(_UWP)
      
   //          wstring wstrModuleFilePath;
      
   //          auto pwszModuleFilePath = wstrModuleFilePath.get_string_buffer(MAX_PATH * 8);
      
   //          if (!GetModuleFileNameW(nullptr, pwszModuleFilePath, MAX_PATH * 8))
   //          {
               
   //             return "";
               
   //          }
      
   //          wstrModuleFilePath.release_string_buffer();
      
   //          LPWSTR pszModuleFileName;
      
   //          wstring wstrModuleFolder;
      
   //          auto pwszModuleFolder = wstrModuleFolder.get_string_buffer(MAX_PATH * 8);
      
   //          if (!GetFullPathNameW(wstrModuleFilePath, MAX_PATH * 8, pwszModuleFolder, &pszModuleFileName))
   //          {
      
   //             return "";
               
   //          }
      
   //          wstrModuleFolder.release_string_buffer();
      
   //          wstrModuleFolder.ends_eat_ci("\\");
   //          wstrModuleFolder.ends_eat_ci("/");
   //          wstrModuleFolder.ends_eat_ci("\\");
   //          wstrModuleFolder.ends_eat_ci("/");
      
   //          return string(wstrModuleFolder);
      
      
   //       #elif defined(WINDOWS)
      
      
   //          wstring wstrModuleFolder(get_buffer, MAX_PATH * 8);
      
      
   //          wstring wstrModuleFilePath(get_buffer, MAX_PATH * 8);
      
      
   //          HMODULE hmodule = ::GetModuleHandleA("acme.dll");
      
   //          if(hmodule == nullptr)
   //             hmodule = ::GetModuleHandleA("spalib.dll");
      
   //          if(hmodule == nullptr)
   //          {
      
   //             cotaskp(PWSTR) pwstr;
      
   //             HRESULT hr = SHGetKnownFolderPath(
   //                          FOLDERID_ProgramFilesX86,
   //                          KF_FLAG_DEFAULT,
   //                          nullptr,
   //                          &pwstr);
      
   //             wcscpy(wstrModuleFilePath, pwstr);
      
      
   //             //if(wstrModuleFilePath[wcslen(wstrModuleFilePath) - 1] == '\\'
      
   //             //      || wstrModuleFilePath[wcslen(wstrModuleFilePath) - 1] == '/')
      
   //             //{
   //             //   wstrModuleFilePath[wcslen(wstrModuleFilePath) - 1] = '\0';
      
   //             //}
   //             wcscat(wstrModuleFilePath, L"\\ca2\\");
      
   //       #ifdef X86
   //             wcscat(wstrModuleFilePath,L"stage\\x86\\");
      
   //       #else
   //             wide_concatenate(wstrModuleFilePath, L"stage\\x64\\");
      
   //       #endif
      
   //             wcscpy(wstrModuleFolder, wstrModuleFilePath);
      
   //             wstrModuleFilePath.release_string_buffer();
      
   //             return string(wstrModuleFolder);
      
      
   //          }
      
   //          if (!GetModuleFileNameW(hmodule, wstrModuleFilePath, (::u32)wstrModuleFilePath.length()))
   //          {
      
   //             return "";
      
   //          }
      
   //          wstrModuleFilePath.release_string_buffer();
      
   //          LPWSTR pszModuleFileName;
      
   //          if (!GetFullPathNameW(wstrModuleFilePath, (::u32)wstrModuleFilePath.length(), wstrModuleFolder, &pszModuleFileName))
   //          {
      
   //             return "";
      
   //          }
      
   //          wstrModuleFolder.release_string_buffer();
      
   //          if(wstrModuleFolder.has_char())
   //          {
      
   //             wstrModuleFolder.trim_right(L"\\/");
      
   //          }
      
   //          return wstrModuleFolder;
      
   //       #elif defined(__APPLE__)
      
   //          string str;
      
   //          {
      
   //    //         str = ::dir::pathfind(getenv("DYLD_LIBRARY_PATH"), "libacme.dylib", "rfs"); // readable - normal file - non zero size_f64
   //    //
   //    //         if(str.has_char())
   //    //         {
   //    //            str = ::file::path(str).folder();
   //    //            goto found;
   //    //
   //    //         }
   //    //
   //    //
   //    //         str = ::dir::pathfind(getenv("DYLD_FALLBACK_LIBRARY_PATH"), "libacme.dylib", "rfs"); // readable - normal file - non zero size_f64
   //    //
   //    //         if(str.has_char())
   //    //         {
   //    //            str = ::file::path(str).folder();
   //    //            goto found;
   //    //
   //    //         }
      
   //             str = get_exe_path();
      
      
   //             if(str.has_char())
   //             {
   //                str = ::file::path(str).folder();
   //                goto found;
   //             }
      
      
   //          }
   //       found:
   //          ;
      
   //          return str;
      
   //       #else
      
   //          string strModuleFolder;
      
   //          auto wstrModuleFolder = strModuleFolder.get_string_buffer(MAX_PATH * 8);
      
   //          void * handle = dlopen("libacme.so", RTLD_NOW);
      
   //          if(handle == nullptr)
   //          {
      
   //             strcpy(wstrModuleFolder, "/ca2/");
      
   //          }
   //          else
   //          {
      
   //             link_map * plm;
      
   //             dlinfo(handle, RTLD_DI_LINKMAP, &plm);
      
   //             strcpy(wstrModuleFolder, plm->l_name);
      
   //             dlclose(handle);
      
   //             strcpy(wstrModuleFolder, ::file_path_folder(wstrModuleFolder));
      
   //          }
      
   //          return string(wstrModuleFolder);
      
      
      
   //       #endif
      
      
   //       }

         //bool acme_path::windows_find_is_dots(WIN32_FIND_DATAW & data)
         //{

         //   if (data.cFileName[0] == L'.')
         //   {

         //      if (data.cFileName[1] == L'\0' ||
         //         (data.cFileName[1] == L'.' &&
         //            data.cFileName[2] == L'\0'))
         //      {

         //         return true;

         //      }

         //   }

         //   return false;

         //}


         ::file::path acme_path::_final(const char * path)
         {

            wstring wstr(path);

            HANDLE hfile = INVALID_HANDLE_VALUE;

            try
            {

               if (m_psystem->m_pacmedir->is(path))
               {

                  hfile = hfile_create(path,
                     GENERIC_READ,          // open for reading
                     FILE_SHARE_READ,       // share for reading
                     nullptr,                  // default security
                     OPEN_EXISTING,         // existing file only
                     FILE_ATTRIBUTE_NORMAL, // normal file
                     nullptr);                 // no attr. template

               }
               else
               {

                  hfile = hfile_create(path,
                     FILE_LIST_DIRECTORY,          // open for reading
                     FILE_SHARE_READ,       // share for reading
                     nullptr,                  // default security
                     OPEN_EXISTING,         // existing file only
                     FILE_ATTRIBUTE_NORMAL, // normal file
                     nullptr);                 // no attr. template

               }

               if (hfile == INVALID_HANDLE_VALUE)
               {

                  return wstr;

               }

               DWORD dw = GetFinalPathNameByHandleW(hfile, nullptr, 0, VOLUME_NAME_DOS);

               if (dw > 0)
               {

                  wstring wstr2;

                  auto * pwsz = wstr2.get_string_buffer(dw + 1);

                  dw = GetFinalPathNameByHandleW(hfile, pwsz, dw + 1, VOLUME_NAME_DOS);

                  if (dw > 0)
                  {

                     wstr2.release_string_buffer();

                     wstr = wstr2;

                  }

               }

            }
            catch (...)
            {

            }

            ::CloseHandle(hfile);

            return wstr;

         }


} // namespace windows





bool windows_find_is_dots(WIN32_FIND_DATAW & data)
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

