// From acme/filesystem/file/_.cpp by camilo on 2021-08-09 
// 03:09 BRT <3ThomasBorregaardSorensen
#include "framework.h"
#include "acme_file.h"
#include "acme_path.h"
#include "acme/exception/exception.h"

#include "acme/primitive/datetime/earth_time.h"
#include "acme/_operating_system.h"


namespace acme_windows
{


   acme_file::acme_file()
   {

   }


   acme_file::~acme_file()
   {


   }


   //::file::path acme_file::module()
   //{

   //   ::file::path path;

   //   {

   //      wstring wstrPath;

   //      auto p = wstrPath.get_buffer(MAX_PATH * 16);

   //      if (!GetModuleFileNameW(nullptr, p, (DWORD)wstrPath.length()))
   //      {

   //         return "";

   //      }

   //      wstrPath.release_buffer();

   //      path = ::string(wstrPath);

   //   }

   //   return path;

   //}


   class ::time acme_file::modification_time(const ::file::path & pathParam)
   {

      auto path = acmepath()->defer_process_relative_path(pathParam);

      ::windows::file_instance fileinstance;

      if (!fileinstance.safe_create_file(path, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL))
      {

         DWORD dwLastError = ::GetLastError();

         throw_last_error_exception(path, ::file::e_open_read, dwLastError, "acme_windows::acme_file::modification_time safe_create_file failed");

      }

      FILETIME ftWrite;

      fileinstance.get_file_time(nullptr, nullptr, &ftWrite);

      return class ::time(as_file_time(ftWrite)) + ::time::local();

   }


   void acme_file::set_modification_time(const ::file::path & pathParam, const class ::time & time)
   {

      auto path = acmepath()->defer_process_relative_path(pathParam);

      ::windows::file_instance fileinstance;

      if (!fileinstance.safe_create_file(path, GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL))
      {

         DWORD dwLastError = ::GetLastError();

         throw_last_error_exception(path, ::file::e_open_write, dwLastError, "acme_windows::acme_file::set_modification_time safe_create_file failed");

      }

      auto FILETIME = as_FILETIME(file_time(time - ::time::local()));

      fileinstance.set_file_time(nullptr, nullptr, &FILETIME);
           
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


   void acme_file::_erase(const ::file::path & pathParam)
   {

      auto path = acmepath()->defer_process_relative_path(pathParam);

      ::delete_file(path);

   }


   string acme_file::get_temporary_file_name(const scoped_string & scopedstrName, const scoped_string & scopedstrExtension)
   {

#ifdef WINDOWS

      WCHAR pPathBuffer[MAX_PATH * 16];

      ::u32 dwRetVal = GetTempPathW(sizeof(pPathBuffer) / sizeof(WCHAR), pPathBuffer);

      if (dwRetVal > sizeof(pPathBuffer) || (dwRetVal == 0))
      {

         DWORD dwLastError = ::GetLastError();

         //debug_print("GetTempPath failed (%d)\n", ::GetLastError());

         auto estatus = ::windows::last_error_status(dwLastError);

         throw ::exception(estatus);

      }

#else
#define MAX_PATH_HERE 300
      char pPathBuffer[MAX_PATH_HERE * 16];

      strcpy(pPathBuffer, "/tmp/");

#endif

      ::file::path pathFolder(pPathBuffer);

      for (int i = 0; i < 1000; i++)
      {

         ::file::path path;

         path = pathFolder;

         path /= scopedstrName;

         path /= ::as_string(i);

         path /= (string(scopedstrName) + "." + string(scopedstrExtension));

         if (!this->exists(path))
         {

            return ::transfer(path);

         }

      }

      throw ::exception(error_not_found);

      return string();

   }


//   void acme_file::write_memory_to_file(FILE * file, const void * pdata, memsize nCount, memsize * puiWritten)
//   {
//
//#if OSBIT > 32
//
//      memsize pos = 0;
//
//      ::u32 dw = 0;
//
//      ::u32 dwWrite;
//
//      memsize uiWrittenTotal = 0;
//
//      while (pos < nCount)
//      {
//
//         dwWrite = (::u32)minimum(nCount - uiWrittenTotal, 0xffffffffu);
//
//         dw = (::u32)(fwrite(&((u8 *)pdata)[pos], 1, dwWrite, file));
//
//
//         if (dw != dwWrite)
//         {
//
//            uiWrittenTotal += dw;
//
//            if (puiWritten != nullptr)
//            {
//
//               *puiWritten = uiWrittenTotal;
//
//            }
//
//            throw ::exception(error_io);
//
//         }
//
//         uiWrittenTotal += dw;
//
//         if (dw != dwWrite)
//         {
//
//            break;
//
//         }
//
//         pos += dw;
//
//      }
//
//      if (puiWritten != nullptr)
//      {
//
//         *puiWritten = uiWrittenTotal;
//
//      }
//
//      if (uiWrittenTotal != nCount)
//      {
//
//         throw ::exception(error_failed);
//
//      }
//
//      // return ::success;
//
//#else
//
//      ::u32 dw = 0;
//
//      dw = ::fwrite(pdata, 1, (size_t)nCount, file);
//
//      int_bool bOk = dw == nCount;
//
//      if (puiWritten != nullptr)
//      {
//
//         *puiWritten = dw;
//
//      }
//
//      if (!bOk)
//      {
//
//         throw ::exception(error_failed);
//
//      }
//
//      // return success;
//
//#endif
//
//   }



} // namespace acme_windows



