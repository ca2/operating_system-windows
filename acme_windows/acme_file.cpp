// From acme/filesystem/file/_.cpp by camilo on 2021-08-09 
// 03:09 BRT <3ThomasBorregaardSørensen
#include "framework.h"
#include "acme_file.h"
#include "acme_path.h"
#include "acme/operating_system.h"
#include "acme/operating_system/time.h"
#include <stdio.h>


namespace acme_windows
{


   acme_file::acme_file()
   {

   }


   acme_file::~acme_file()
   {


   }


   ::file::path acme_file::module()
   {

      ::file::path path;

      {

         wstring wstrPath(e_get_buffer, MAX_PATH * 16);

         if (!GetModuleFileNameW(nullptr, wstrPath, (DWORD)wstrPath.get_length()))
         {

            return "";

         }

         path = wstrPath.release_string_buffer();

      }

      return path;

   }


   ::earth::time acme_file::modification_time(const char* pathParam)
   {

      auto path = m_psystem->m_pacmepath->defer_process_relative_path(pathParam);

      auto hFile = CreateFileW(wstring(path), GENERIC_READ, FILE_SHARE_READ, NULL,
         OPEN_EXISTING, 0, NULL);

      if (hFile == INVALID_HANDLE_VALUE)
      {
         
         return {};
      }
      
      FILETIME ftWrite;

      // Retrieve the file times for the file.
      if (!GetFileTime(hFile, nullptr, nullptr, &ftWrite))
      {

         ::CloseHandle(hFile);
         return {};

      }
      ::CloseHandle(hFile);
      // Convert the last-write time to local time.
      //FileTimeToSystemTime(&ftWrite, &stUTC);

      ::earth::time time;

      file_time_to_time(&time.m_i, (file_time_t *) & ftWrite);

      return (INTEGRAL_SECOND) time.m_i;

      //SystemTimeToTzSpecificLocalTime(NULL, &stUTC, &stLocal);

      // Build a string showing the date and time.
      //dwRet = StringCchPrintf(lpszString, dwSize,
         //TEXT("%02d/%02d/%d  %02d:%02d"),
         //stLocal.wMonth, stLocal.wDay, stLocal.wYear,
         //stLocal.wHour, stLocal.wMinute);

      //if (S_OK == dwRet)
        // return TRUE;
      //else return FALSE;
      

   }


   void acme_file::set_modification_time(const char* pathParam, const ::earth::time & time)
   {

      auto path = m_psystem->m_pacmepath->defer_process_relative_path(pathParam);

      auto hFile = CreateFileW(wstring(path), GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);

      if (hFile == INVALID_HANDLE_VALUE)
      {
         
         auto lastError = GetLastError();
         
         auto estatus = last_error_to_status(lastError);

         throw ::exception(estatus, "windows::acme_file::set_modification_time (1)");

      }

      ::file_time_t filetime;

      time_to_file_time(&filetime, &time.m_i);

      // Retrieve the file times for the file.
      if (!SetFileTime(hFile, nullptr, nullptr, (FILETIME *) & filetime))
      {

         auto lastError = GetLastError();
         
         ::CloseHandle(hFile);
         
         auto estatus = last_error_to_status(lastError);

         throw ::exception(estatus, "windows::acme_file::set_modification_time (2)");

      }

      ::CloseHandle(hFile);
      
   }


   ::file::path acme_file::time_put_contents(const ::file::path& pathFolder, const ::string& strPrefix, const ::string& strExtension, const ::string& str)
   {

      ::file::path path;

      int i = 0;

      while (true)
      {

         string strHexadecimal;

         strHexadecimal.format("%08x", i);

         path = pathFolder / (strPrefix + "-" + strHexadecimal + "." + strExtension);

         if (exists(path))
         {

            i++;

            continue;

         }

         put_contents(path, str);

         break;

      }

      return path;

   }


   void acme_file::_erase(const char* path)
   {

      ::wstring wstrPath(path);

      if (!::DeleteFileW(wstrPath))
      {

         auto lastError = ::GetLastError();

         auto estatus = last_error_to_status(lastError);

         throw ::exception(estatus, "Failed to delete file \"" + ::string(path) + "\"");

      }

   }


} // namespace acme_windows



