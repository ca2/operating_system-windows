#include "framework.h"
#include "file_context.h"
#include "dir_system.h"
#include "file_system.h"
#include "node.h"
#include "acme/exception/exception.h"
#include "acme/filesystem/file/exception.h"
#include "acme/filesystem/file/memory_file.h"
#include "acme/filesystem/file/status.h"
#include "acme/filesystem/filesystem/acme_directory.h"
#include "acme/filesystem/filesystem/dir_context.h"

#include "acme/platform/debug.h"
#include "acme/prototype/prototype/payload.h"
#include "acme/prototype/string/international.h"
#include "acme/platform/system.h"

#include "acme/_operating_system.h"
#include "acme_windows/registry.h"



CLASS_DECL_ACME_WINDOWS const void * get_resource_pointer(HINSTANCE hinst, DWORD nID, const char * pcszType, memsize & memsize);
CLASS_DECL_ACME_WINDOWS bool read_resource_as_memory(memory & m, HINSTANCE hinst, DWORD nID, const char * pcszType, strsize iReadAtMostByteCount = -1);
CLASS_DECL_ACME::file::path get_module_path(HMODULE hmodule);
CLASS_DECL_ACME FILETIME & copy(FILETIME & filetime, const ::earth::time & time);


namespace acme_windows
{


   file_context::file_context()
   {

      m_bFolderResourceCalculated = false;

   }


   file_context::~file_context()
   {

   }


   void file_context::initialize(::particle * pparticle)
   {

      //auto estatus = 
      
      ::acme_windows_common::file_context::initialize(pparticle);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      ::pointer<::acme::system>psystem = system();

      m_pfilesystem = psystem->m_pfilesystem;

      m_pdirsystem = psystem->m_pdirsystem;

      //return ::success;

   }


   void file_context::init_system()
   {

      ::acme_windows_common::file_context::init_system();

      //auto estatus = m_pfilesystem->update_module_path();

      //if (!estatus)
      //{

      //   return estatus;

      //}

//      return ::success;

   }


   void file_context::term_system()
   {

      ::acme_windows_common::file_context::init_system();

      //auto estatus = m_pfilesystem->update_module_path();

      //if (!estatus)
      //{

      //   return estatus;

      //}

//      return ::success;

   }


   void file_context::finalize()
   {

      m_pfilesystem.release();

      m_pdirsystem.release();

      ::acme_windows_common::file_context::finalize();

   }

   //bool file_context::FullPath(string & str, const ::string & pszFileIn)
   //{


   //   if (pszFileIn.case_insensitive_begins("http://"))
   //   {

   //      str = pszFileIn;

   //      return true;

   //   }
   //   else if (pszFileIn.case_insensitive_begins("https://"))
   //   {

   //      str = pszFileIn;

   //      return true;

   //   }

   //   wstring wstrFileIn;

   //   wstrFileIn = utf8_to_unicode(pszFileIn);

   //   wstring wstrFileOut;
   //   bool b = windows_full_path(wstrFileOut.get_buffer(MAX_PATH * 8), wstrFileIn) != false;
   //   if (b)
   //   {
   //      unicode_to_utf8(str, wstrFileOut);
   //   }
   //   return b;
   //}

   //bool file_context::FullPath(wstring & wstrFullPath, const wstring & wstrPath)
   //{

   //   /*      if(::apex::file_context::FullPath(wstrFullPath, wstrPath))
   //   return true;*/

   //   if (wstrPath.case_insensitive_begins(L"http://"))
   //   {
   //      wstrFullPath = wstrPath;
   //      return true;
   //   }
   //   else if (wstrPath.case_insensitive_begins(L"https://"))
   //   {
   //      wstrFullPath = wstrPath;
   //      return true;
   //   }

   //   return windows_full_path(wstrFullPath, wstrPath) != false;

   //}


   //::u32 file_context::GetFileName(const ::string & pszPathName, string & str)

   //{
   //   i32 nMax = MAX_PATH * 8;
   //   wstring wstrPathName;
   //   wstrPathName = utf8_to_unicode(pszPathName);

   //   wstring wstrTitle;
   //   ::u32 user = vfxGetFileName(wstrPathName, wstrTitle.get_buffer(nMax), nMax);
   //   str = unicode_to_utf8(wstrTitle);
   //   return user;
   //}


   string file_context::get_short_file_name(const ::string & str)
   {

      return windows_get_short_file_name(str);

   }


   string file_context::get_module_short_file_name(HINSTANCE hinstance)
   {

      auto path = get_module_path(hinstance);

      auto strShortFileName = get_short_file_name(path);
      
      return strShortFileName;

   }


   ::payload file_context::length(const ::file::path & path)
   {

      ::payload varRet;

      //varRet = ::file_context::length(path);

      //if (!varRet.is_null())
      //   return varRet;


#ifdef WINDOWS

      WIN32_FILE_ATTRIBUTE_DATA data;

      if (!GetFileAttributesExW(utf8_to_unicode(path), GetFileExInfoStandard, &data))
      {
         varRet.set_type(::e_type_null);
      }
      else
      {
         varRet = (u32)data.nFileSizeLow;
      }

#else

      struct stat stat;

      if (::stat(strPath, &stat) == -1)
      {
         varRet.set_type(::e_type_null);
      }
      else
      {
         varRet = stat.st_size;
      }

#endif

      return varRet;

   }


   ::payload file_context::length(const ::file::path & path, ::payload * pvarQuery)
   {

      // TODO: I don't remember what pvarQuery is used for, in the time of reimplementation
      // of this function. Maybe you should consider it in some case(s).

      return length(path);

   }


   void file_context::transfer(const ::file::path & pszNew, const ::file::path & psz)
   {

#ifdef WINDOWS_DESKTOP

      if (!::MoveFileW(
         utf8_to_unicode(psz),
         utf8_to_unicode(pszNew)))
      {

         DWORD dwError = ::GetLastError();

         if (dwError == ERROR_ALREADY_EXISTS)
         {

            if (::CopyFileW(
               utf8_to_unicode(psz),
               utf8_to_unicode(pszNew),
               false))
            {

               if (!::DeleteFileW(utf8_to_unicode(psz)))
               {

                  dwError = ::GetLastError();

                  string strError;

                  strError.formatf("Failed to delete the file to move \"%s\" error=%d", psz, dwError);

                  information() << "%s", strError;

               }

               return;

            }

            dwError = ::GetLastError();

         }

         string strError;

         strError.formatf("Failed to move file \"%s\" to \"%s\" error=%d", psz, pszNew, dwError);

         throw ::exception(::error_io, strError);

      }

#elif defined(UNIVERSAL_WINDOWS)

      ::winrt::Windows::Storage::StorageFile ^ file = get_os_file(psz, 0, 0, nullptr, OPEN_EXISTING, 0, nullptr);

      if (file == nullptr)
      {

         //output_debug_string("test");

         throw ::exception(::exception("file::file_context::move Could not move file, could not open source file"));

      }

      string strDirOld = psz.folder();
      string strDirNew = pszNew.folder();
      string strNameOld = psz.name();
      string strNameNew = pszNew.name();

      if (strDirOld == strDirNew)
      {
         if (strNameOld == strNameNew)
         {
            return ::success;
         }
         else
         {
            ::wait(file->RenameAsync(strNameNew));
         }
      }
      else
      {
         ::winrt::Windows::Storage::StorageFolder ^ folder = get_os_folder(strDirNew);
         if (strNameOld == strNameNew)
         {
            ::wait(file->MoveAsync(folder));
         }
         else
         {
            ::wait(file->MoveAsync(folder, strNameNew));
         }
      }


#else
      if (::rename(psz, pszNew) != 0)
      {
         i32 err = errno;
         string strError;
         strError.Format("Failed to delete file error=%d", err);
         throw ::exception(::exception(strError));
      }
#endif

   }


   void file_context::erase(const ::file::path & path)
   {

//#ifdef WINDOWS_DESKTOP
//
      ::windows::file_instance fileinstance;

      //filehandle.create_file(L"\\\\?\\" + path.get_os_path(),
      if(!fileinstance.safe_create_file(path,
         GENERIC_READ | GENERIC_WRITE, 0, nullptr, OPEN_EXISTING,
         FILE_FLAG_OPEN_REPARSE_POINT | FILE_FLAG_DELETE_ON_CLOSE, nullptr))
      {

         DWORD dwLastError = ::GetLastError();

         throw_last_error_exception(path, ::file::e_open_read | ::file::e_open_write, dwLastError, "apex_windows::file_context::erase safe_create_file failed");

      }

      //if (h == INVALID_HANDLE_VALUE)
      //{

      //   DWORD dwLastError = ::GetLastError();

      //   if (dwLastError == 2) // the file does not exist, so delete "failed"
      //   {

      //      return;

      //   }

      //   auto estatus = ::windows::last_error_status(dwLastError);

      //   auto errorcode = ::windows::last_error_error_code(dwLastError);

      //   //string strError;

      //   //strError.formatf("Failed to delete file \"%s\" error=%d", psz, dwError);

      //   throw ::file::exception(estatus, errorcode, path, "Failed to open file to be deleted.");

      //}
      //else
      //{

      fileinstance.flush_file_buffers();
         //::FlushFileBuffers(h);
         //::CloseHandle(h);
      //}

      /*      if(!::DeleteFileW(utf8_to_unicode(string("\\\\?\\") + psz)))
      {
      u32 dwError = ::get_last_error();
      if(dwError == 2) // the file does not exist, so delete "failed"
      return;
      string strError;
      strError.Format("Failed to delete file \"%s\" error=%d", psz, dwError);
      throw ::exception(io_exception(strError));
      }*/


//#else
//
//      if (unlink(psz) != 0)
//      {
//         i32 err = errno;
//         if (err != ENOENT) // already does not exist - consider removal successful - does not issue an exception
//         {
//            string strError;
//            strError.Format("Failed to delete file error=%d", err);
//            throw ::exception(::exception(strError));
//         }
//      }
//#endif

   }


   bool file_context::is_read_only(const ::file::path & psz)
   {

#ifdef WINDOWS_DESKTOP

      u32 dwAttrib = ::windows::get_file_attributes(psz);

      if (dwAttrib & FILE_ATTRIBUTE_READONLY)
      {

         return true;

      }

      return false;

#elif defined(UNIVERSAL_WINDOWS)

      throw ::exception(todo);

#else

      struct stat st;

      if (stat(psz, &st) != 0)
         return true;

      return !(st.st_mode & S_IWUSR);

#endif

   }


   ::block file_context::get_main_resource_block()
   {

      memsize s = 0;

      const void* pdata = get_resource_pointer((HINSTANCE)system()->m_pplatform->m_hinstanceThis, 1024, "ZIP", s);

      //m_memoryMainResource.assign(pdata, s);

      //return m_memoryMainResource;

      return { pdata, s };

   }


   file_pointer file_context::resource_get_file(const ::file::path & path)
   {

      auto pfile = create_memory_file();

      int iId = atoi(path);

      string strExtension = path.final_extension();

      strExtension.make_upper();
      const ::ansi_character * psz = strExtension;
      if (strExtension == "HTML")
      {

         psz = (const char *)RT_HTML;

      }

      ::pointer<::acme::system>psystem = system();

      if (read_resource_as_memory(*pfile->get_primitive_memory(), (HINSTANCE) psystem->m_pplatform->m_hinstanceThis, iId, psz))
      {

         return pfile;

      }


      return nullptr;

   }


   bool file_context::get_last_write_time(FILETIME * pfiletime, const ::string & strFilename)
   {

      WIN32_FILE_ATTRIBUTE_DATA data{};

      if (!GetFileAttributesExW(wstring(strFilename), GetFileExInfoStandard, &data))
      {

         return false;

      }

      *pfiletime = data.ftLastWriteTime;

      return true;

   }

   //void file_context::set_status(const ::file::path & path,const ::file::file_status& status)
   //{

   //   wstring pszFileName(path);

   //   ::u32 wAttr;
   //   FILETIME creationTime;
   //   FILETIME lastAccessTime;
   //   FILETIME lastWriteTime;
   //   LPFILETIME pCreationTime = nullptr;

   //   LPFILETIME pLastAccessTime = nullptr;

   //   LPFILETIME pLastWriteTime = nullptr;


   //   if((wAttr = windows_get_file_attributes((LPWSTR)(const ::wide_character *)pszFileName)) == (::u32)-1L)

   //      file_exception::throw_os_error((::i32)GetLastError());

   //   if((::u32)status.m_attribute != wAttr && (wAttr & readOnly))
   //   {
   //      // set file attribute, only if currently readonly.
   //      // This way we will be able to modify the time assuming the
   //      // caller changed the file from readonly.

   //      if(!SetFileAttributesW((LPWSTR)(const ::wide_character *)pszFileName,(::u32)status.m_attribute))

   //         file_exception::throw_os_error((::i32)GetLastError());
   //   }

   //   // last modification time
   //   if(status.m_mtime.get_time() != 0)
   //   {
   //      ::apex::TimeToFileTime(status.m_mtime,&lastWriteTime);
   //      pLastWriteTime = &lastWriteTime;


   //      // last access time
   //      if(status.m_atime.get_time() != 0)
   //      {
   //         ::apex::TimeToFileTime(status.m_atime,&lastAccessTime);
   //         pLastAccessTime = &lastAccessTime;

   //      }

   //      // create time
   //      if(status.m_ctime.get_time() != 0)
   //      {
   //         ::apex::TimeToFileTime(status.m_ctime,&creationTime);
   //         pCreationTime = &creationTime;

   //      }

   //      HANDLE hFile = ::CreateFileW((LPWSTR)(const ::wide_character *)pszFileName,GENERIC_READ | GENERIC_WRITE,

   //         FILE_SHARE_READ,nullptr,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,
   //         nullptr);

   //      if(hFile == INVALID_HANDLE_VALUE)
   //         file_exception::throw_os_error((::i32)::GetLastError());

   //      if(!SetFileTime((HANDLE)hFile,pCreationTime,lpLastAccessTime,lpLastWriteTime))

   //         file_exception::throw_os_error((::i32)::GetLastError());

   //      if(!::CloseHandle(hFile))
   //         file_exception::throw_os_error((::i32)::GetLastError());
   //   }

   //   if((::u32)status.m_attribute != wAttr && !(wAttr & readOnly))
   //   {
   //      if(!SetFileAttributes((char *)pszFileName,(::u32)status.m_attribute))

   //         file_exception::throw_os_error((::i32)GetLastError());
   //   }
   //}


   //void file::SetStatus(const ::string & pszFileName,const ::file::file_status& status)

   //{
   //   ::u32 wAttr;
   //   FILETIME creationTime;
   //   FILETIME lastAccessTime;
   //   FILETIME lastWriteTime;
   //   LPFILETIME pCreationTime = nullptr;

   //   LPFILETIME pLastAccessTime = nullptr;

   //   LPFILETIME pLastWriteTime = nullptr;


   //   if((wAttr = GetFileAttributes((char *)pszFileName)) == (::u32)-1L)

   //      file_exception::throw_os_error((::i32)GetLastError());

   //   if((::u32)status.m_attribute != wAttr && (wAttr & readOnly))
   //   {
   //      // set file attribute, only if currently readonly.
   //      // This way we will be able to modify the time assuming the
   //      // caller changed the file from readonly.

   //      if(!SetFileAttributes((char *)pszFileName,(::u32)status.m_attribute))

   //         file_exception::throw_os_error((::i32)GetLastError());
   //   }

   //   // last modification time
   //   if(status.m_mtime.get_time() != 0)
   //   {
   //      ::apex::TimeToFileTime(status.m_mtime,&lastWriteTime);
   //      pLastWriteTime = &lastWriteTime;


   //      // last access time
   //      if(status.m_atime.get_time() != 0)
   //      {
   //         ::apex::TimeToFileTime(status.m_atime,&lastAccessTime);
   //         pLastAccessTime = &lastAccessTime;

   //      }

   //      // create time
   //      if(status.m_ctime.get_time() != 0)
   //      {
   //         ::apex::TimeToFileTime(status.m_ctime,&creationTime);
   //         pCreationTime = &creationTime;

   //      }

   //      HANDLE hFile = ::CreateFile(pszFileName,GENERIC_READ | GENERIC_WRITE,

   //         FILE_SHARE_READ,nullptr,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,
   //         nullptr);

   //      if(hFile == INVALID_HANDLE_VALUE)
   //         file_exception::throw_os_error((::i32)::GetLastError());

   //      if(!SetFileTime((HANDLE)hFile,pCreationTime,lpLastAccessTime,lpLastWriteTime))

   //         file_exception::throw_os_error((::i32)::GetLastError());

   //      if(!::CloseHandle(hFile))
   //         file_exception::throw_os_error((::i32)::GetLastError());
   //   }

   //   if((::u32)status.m_attribute != wAttr && !(wAttr & readOnly))
   //   {
   //      if(!SetFileAttributes((char *)pszFileName,(::u32)status.m_attribute))

   //         file_exception::throw_os_error((::i32)GetLastError());
   //   }
   //}



   //void file_context::update_module_path()
   //{

   //   auto estatus = ::file_context::update_module_path();

   //   if(!estatus)
   //{
   //   
   //   return estatus;
   //   
   //}

   //   return estatus;

   //}


   file_pointer file_context::get_file(const ::payload & payloadFile, ::file::e_open eopen, ::pointer < ::file::exception > * ppfileexception)
   {

      return ::file_context::get_file(payloadFile, eopen);

   }


   ::file::path file_context::dropbox_info_network_payload()
   {

      ::file::path pathNetworkPayload;

      pathNetworkPayload = acmedirectory()->user_appdata_local() / "Dropbox/info" NETWORK_PAYLOAD_DEFAULT_EXTENSION;

      return pathNetworkPayload;

   }


   ::file::path file_context::dropbox_client()
   {

      auto pathClientFolder = dir()->dropbox_client();

      if (pathClientFolder.is_empty() || !dir()->is(pathClientFolder))
      {

         return {};

      }

      return pathClientFolder / "Dropbox.exe";

   }


} // namespace apex_windows



