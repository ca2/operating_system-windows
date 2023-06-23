#include "framework.h"
#include "file_memory_map.h"
#include "acme_directory.h"
#include "acme/parallelization/synchronous_lock.h"


//CLASS_DECL_ACME bool ensure_file_size_handle(HANDLE h, u64 iSize);


namespace acme_windows
{


   file_memory_map::file_memory_map()
   {

      m_hfilemap = nullptr;

   }


   file_memory_map::~file_memory_map()
   {


   }


   bool file_memory_map::open()
   {

      close();

      string strPath = get_path();

      ::file::path path(strPath);

      auto strWindowsPath = path.windows_path();

      ::windows_path windowspath = strWindowsPath;

      if (strPath.case_insensitive_begins("Local\\") || strPath.case_insensitive_begins("Global\\"))
      {

         m_fileinstance.m_handle = INVALID_HANDLE_VALUE;

         m_hfilemap = CreateFileMappingW(INVALID_HANDLE_VALUE, nullptr, PAGE_READWRITE, 0, (::u32)m_size, windowspath);

      }
      else
      {

         auto pathFolder = path.folder();

         auto strWindowsPathFolder = pathFolder.windows_path();

         ::windows_path windowspathFolder = strWindowsPathFolder;

         acmedirectory()->create(windowspathFolder);

         int iOpen;

         if (m_bCreate)
         {

            iOpen = OPEN_ALWAYS;

         }
         else
         {

            iOpen = OPEN_EXISTING;

         }

         if (!m_fileinstance.safe_create_file(path, (m_bRead || m_bWrite ? FILE_READ_DATA : 0) | (m_bWrite ? FILE_WRITE_DATA : 0), FILE_SHARE_WRITE | FILE_SHARE_READ, nullptr, iOpen, FILE_ATTRIBUTE_NORMAL, nullptr))
         {

            DWORD dwLastError = ::GetLastError();

            throw_last_error_exception(
               path,
               (m_bRead ? ::file::e_open_write : ::file::e_open_none) |
               (m_bWrite ? ::file::e_open_write : ::file::e_open_none),
               dwLastError,
               "acme_windows::file_memory_map::open safe_create_file failed");

         }

         if (m_fileinstance.nok())
         {

            return false;

         }

         m_fileinstance.ensure_file_size(m_size);

         m_hfilemap = CreateFileMappingW(m_fileinstance, nullptr, PAGE_READWRITE, 0, 0, nullptr);

      }

      if (m_hfilemap == nullptr)
      {
         
         close();

         return false;

      }

      m_pdata = ::MapViewOfFile(m_hfilemap, (m_bRead ? FILE_MAP_READ : 0) | (m_bWrite ? FILE_MAP_WRITE : 0), 0, 0, 0);

      if (m_pdata == nullptr)
      {

         close();

         return false;

      }

      //string strMutex;

      //strMutex = strPath + "-::mutex";

      //set_mutex(new class ::mutex(e_create_new, strMutex, nullptr, false));

      return true;

   }


   bool file_memory_map::is_mapped()
   {

      return m_pdata != nullptr;

   }


   //string file_memory_map::calculate_path_from_name(const ::string & strName)
   //{

   //   auto pathFolder = acmesystem()->get_memory_map_base_folder_path();

   //   auto path = pathFolder / (strName + ".filememorymap");

   //   return path;

   //}


   bool file_memory_map::close()
   {

      synchronous_lock synchronouslock(synchronization());

      if (m_pdata != nullptr)
      {

         ::UnmapViewOfFile(m_pdata);

         m_pdata = nullptr;

      }

      if (m_hfilemap != nullptr)
      {

         ::CloseHandle(m_hfilemap);

         m_hfilemap = nullptr;

      }

      if (m_fileinstance.is_ok())
      {

         m_fileinstance.close_handle();

      }

      return true;

   }


} // namespace acme_windows



