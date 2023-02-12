// Create on 2021-03-22 09:12 <3ThomasBS_
#include "framework.h"
#include "acme_path.h"
#include "acme/filesystem/filesystem/path.h"
#include "acme/_operating_system.h"


namespace acme_windows
{


   acme_path::acme_path()
   {

   }


   acme_path::~acme_path()
   {


   }


   ::file::path acme_path::_final(const ::file::path & pathParam)
   {

      wstring wstr(pathParam);

      HANDLE hfile = INVALID_HANDLE_VALUE;

      try
      {

         if (::is_directory(pathParam))
         {

            hfile = ::CreateFileW(wstr,
               GENERIC_READ,          // open for reading
               FILE_SHARE_READ,       // share for reading
               nullptr,
               OPEN_EXISTING,         // existing file only
               0,
               nullptr);              // no ext. properties

         }
         else
         {

            hfile = ::CreateFileW(wstr,
               FILE_LIST_DIRECTORY,   // open for reading
               FILE_SHARE_READ,       // share for reading
               nullptr,
               OPEN_EXISTING,         // existing file only
               0,
               nullptr);              // no ext. properties

         }

         if (hfile == INVALID_HANDLE_VALUE)
         {

            return ::string(wstr);

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

      return ::string(wstr);

   }


   ::file::path acme_path::get_absolute_path(const ::scoped_string& scopedstr)
   {


      ::string result = scopedstr; //realpath() fails if path is already absolute

      wstring wstrPath(scopedstr);

      auto newLength = GetFullPathNameW(wstrPath, 0, nullptr, NULL);
      
      wstring wstrFullPath;

      decltype(newLength) length;

      do
      {

         length = newLength;

         auto pszFullPath = wstrFullPath.get_string_buffer(length);

         newLength = GetFullPathNameW(wstrPath, MAX_PATH, pszFullPath, NULL);

         wstrFullPath.release_string_buffer(length);

      } while (newLength < length);

      
      return result;
   }



} // namespace acme_windows


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



