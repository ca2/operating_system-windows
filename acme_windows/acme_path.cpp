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


   ::file::path acme_path::_real_path(const ::file::path & path)
   {

      ::windows::file_instance fileinstance;

      auto etype = get_file_system_item_type(path);

      if (etype == ::file::e_type_folder)
      {

         if (!fileinstance.safe_create_file(path,
            GENERIC_READ,          // open for reading
            FILE_SHARE_READ,       // share for reading
            nullptr,
            OPEN_EXISTING,         // existing file only
            0,
            nullptr))              // no ext. properties
         {

            DWORD dwLastError = ::GetLastError();

            throw_last_error_exception(path, ::file::e_open_read, dwLastError, "acme_windows::acme_path::_real_path safe_create_file failed (e_type_directory)");

            return {}; 

         }

      }
      else if (etype == ::file::e_type_file)
      {

         if (!fileinstance.safe_create_file(path,
            FILE_LIST_DIRECTORY,   // open for reading
            FILE_SHARE_READ,       // share for reading
            nullptr,
            OPEN_EXISTING,         // existing file only
            0,
            nullptr))             // no ext. properties
         {

            DWORD dwLastError = ::GetLastError();

            throw_last_error_exception(path, ::file::e_open_read, dwLastError, "acme_windows::acme_path::_real_path safe_create_file failed (e_type_file)");

            return {};

         }

      }

      if (fileinstance.nok())
      {

         return {};

      }

      auto pathFinal = fileinstance.get_final_path_by_handle();

      return pathFinal;

   }


   ::file::path acme_path::_safe_real_path(const ::file::path & path)
   {

      ::windows::file_instance fileinstance;

      try
      {

         auto etype = safe_get_file_system_item_type(path);

         if (etype == ::file::e_type_folder)
         {

            if (!fileinstance.safe_create_file(path,
               GENERIC_READ,          // open for reading
               FILE_SHARE_READ,       // share for reading
               nullptr,
               OPEN_EXISTING,         // existing file only
               0,
               nullptr))              // no ext. properties
            {

               return {};

            }

         }
         else if (etype == ::file::e_type_file)
         {

            if (!fileinstance.safe_create_file(path,
               FILE_LIST_DIRECTORY,   // open for reading
               FILE_SHARE_READ,       // share for reading
               nullptr,
               OPEN_EXISTING,         // existing file only
               0,
               nullptr))             // no ext. properties
            {

               return {};

            }

         }

         if (fileinstance.nok())
         {

            return path;

         }

         auto pathFinal = fileinstance.get_final_path_by_handle();

         return pathFinal;

      }
      catch (...)
      {

      }

      return {};

}

::file::path acme_path::get_absolute_path(const ::scoped_string & scopedstr)
{

   ::string result = scopedstr; //realpath() fails if path is already absolute

   wstring wstrPath(scopedstr);

   auto newLength = GetFullPathNameW(wstrPath, 0, nullptr, NULL);

   wstring wstrFullPath;

   decltype(newLength) length;

   do
   {

      length = newLength;

      auto pszFullPath = wstrFullPath.get_buffer(length);

      newLength = GetFullPathNameW(wstrPath, MAX_PATH, pszFullPath, NULL);

      wstrFullPath.release_buffer(length);

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



