// From acme/filesystem/file/_.cpp by camilo on 2021-08-09 
// 03:09 BRT <3ThomasBorregaardSorensen
#include "framework.h"
#include "file_system.h"
#include "path_system.h"
#include "acme/exception/exception.h"

#include "acme/prototype/datetime/earth_time.h"
#include "acme/_operating_system.h"


namespace acme_windows
{


   file_system::file_system()
   {

   }


   file_system::~file_system()
   {


   }


   //::file::path file_system::module()
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


   class ::time file_system::modification_time(const ::file::path & pathParam)
   {

      auto path = path_system()->defer_process_relative_path(pathParam);

      ::windows::file_instance fileinstance;

      if (!fileinstance.safe_create_file(path, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL))
      {

         DWORD dwLastError = ::GetLastError();

         throw_last_error_exception(path, ::file::e_open_read, dwLastError, "acme_windows::file_system::modification_time safe_create_file failed");

      }

      FILETIME ftWrite;

      fileinstance.get_file_time(nullptr, nullptr, &ftWrite);

      return class ::time(as_file_time(ftWrite)) + ::time::local();

   }


   void file_system::set_modification_time(const ::file::path & pathParam, const class ::time & time)
   {

      auto path = path_system()->defer_process_relative_path(pathParam);

      ::windows::file_instance fileinstance;

      if (!fileinstance.safe_create_file(path, GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL))
      {

         DWORD dwLastError = ::GetLastError();

         throw_last_error_exception(path, ::file::e_open_write, dwLastError, "acme_windows::file_system::set_modification_time safe_create_file failed");

      }

      auto FILETIME = as_FILETIME(file_time(time - ::time::local()));

      fileinstance.set_file_time(nullptr, nullptr, &FILETIME);
           
   }


   ::file::path file_system::time_put_contents(const ::file::path& pathFolder, const ::string& strPrefix, const ::string& strExtension, const ::string& str)
   {

      ::file::path path;

      int i = 0;

      while (true)
      {

         string strHexadecimal;

         strHexadecimal.formatf("%08x", i);

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


   void file_system::_erase(const ::file::path & pathParam)
   {

      auto path = path_system()->defer_process_relative_path(pathParam);

      ::delete_file(path);

   }


   string file_system::get_temporary_file_name(const scoped_string & scopedstrName, const scoped_string & scopedstrExtension)
   {

#ifdef WINDOWS

      WCHAR pPathBuffer[MAX_PATH * 16];

      unsigned int dwRetVal = GetTempPathW(sizeof(pPathBuffer) / sizeof(WCHAR), pPathBuffer);

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


//   void file_system::write_memory_to_file(FILE * file, const void * pdata, memsize nCount, memsize * puiWritten)
//   {
//
//#if OSBIT > 32
//
//      memsize pos = 0;
//
//      unsigned int dw = 0;
//
//      unsigned int dwWrite;
//
//      memsize uiWrittenTotal = 0;
//
//      while (pos < nCount)
//      {
//
//         dwWrite = (unsigned int)minimum(nCount - uiWrittenTotal, 0xffffffffu);
//
//         dw = (unsigned int)(fwrite(&((u8 *)pdata)[pos], 1, dwWrite, file));
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
//      unsigned int dw = 0;
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



