// Create on 2021-03-22 09:12 <3ThomasBS_
#include "framework.h"
#include "path_system.h"
#include "file_link.h"
#include "node.h"
#include "acme/filesystem/filesystem/directory_system.h"
#include "acme/filesystem/filesystem/path.h"
#include "acme/_operating_system.h"


namespace acme_windows
{


   path_system::path_system()
   {

   }


   path_system::~path_system()
   {


   }


   ::string path_system::discrete_shell_path(const ::file::path& path)
   {

      ::string strDiscreteShellPath = path.windows_path().path();

      return strDiscreteShellPath;

   }


   ::string path_system::shell_path(const ::file::path& path)
   {

      ::string strShellPath = discrete_shell_path(path);

      if (strShellPath.contains(' '))
      {

         strShellPath = "\"" + strShellPath + "\"";

      }

      return strShellPath;

   }


   ::file::path path_system::_real_path(const ::file::path & path)
   {

      ::windows::file_instance fileinstance;

      auto etype = safe_get_file_system_item_type(path);

      if (etype & ::file::e_type_folder2)
      {

         if (!fileinstance.safe_create_file(path,
            GENERIC_READ,          // open for reading
            FILE_SHARE_READ |
            FILE_SHARE_WRITE |
            FILE_SHARE_DELETE,       // share for reading
            nullptr,
            OPEN_EXISTING,         // existing file only
            FILE_FLAG_BACKUP_SEMANTICS,
            nullptr))              // no ext. properties
         {

            DWORD dwLastError = ::GetLastError();

            throw_last_error_exception(path, ::file::e_open_read, dwLastError, "acme_windows::path_system::_real_path safe_create_file failed (e_type_directory)");

            return {};

         }

      }
      else if (etype & ::file::e_type_file2)
      {

         if (!fileinstance.safe_create_file(path,
            GENERIC_READ,   // open for reading
            FILE_SHARE_READ |
            FILE_SHARE_WRITE |
            FILE_SHARE_DELETE,       // share for reading
            nullptr,
            OPEN_EXISTING,         // existing file only
            0,
            nullptr))             // no ext. properties
         {

            DWORD dwLastError = ::GetLastError();

            throw_last_error_exception(path, ::file::e_open_read, dwLastError, "acme_windows::path_system::_real_path safe_create_file failed (e_type_file)");

            return {};

         }

      }

      if (fileinstance.nok())
      {

         return {};

      }

      auto pathFinal = fileinstance.get_final_path_by_handle();

      pathFinal.set_type(etype);

      return pathFinal;

   }


   ::file::path path_system::_safe_real_path(const ::file::path & path)
   {

      ::windows::file_instance fileinstance;

      try
      {

         auto etype = safe_get_file_system_item_type(path);

         if (etype & ::file::e_type_file2)
         {

            if (!fileinstance.safe_create_file(path,
               GENERIC_READ,          // open for reading
               FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE, // share for reading
               nullptr,
               OPEN_EXISTING,         // existing file only
               FILE_ATTRIBUTE_NORMAL,
               nullptr))              // no ext. properties
            {

               return {};

            }

         }
         else if (etype & ::file::e_type_folder2)
         {

            if (!fileinstance.safe_create_file(path,
               GENERIC_READ,   // open for reading
               FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE, // share for reading
               nullptr,
               OPEN_EXISTING,         // existing file only
               FILE_ATTRIBUTE_DIRECTORY | FILE_FLAG_BACKUP_SEMANTICS,
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

   ::file::path path_system::get_absolute_path(const ::scoped_string & scopedstr)
   {

      ::string result = scopedstr; //pfilesystemcacheitem() fails if path is already absolute

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


   comptr < IShellLinkW > path_system::_get_IShellLinkW(const ::file::path & pathLink)
   {

      node()->defer_co_initialize_ex(false);

      HRESULT hr;

      comptr < IShellLinkW > pshelllink;

      if (FAILED(hr = pshelllink.CoCreateInstance(CLSID_ShellLink, nullptr, CLSCTX_INPROC_SERVER)))
      {

         return nullptr;

      }

      bool bOk = false;

      auto ppersistfile = pshelllink.as < IPersistFile >();

      if (!ppersistfile)
      {

         return nullptr;

      }

      auto strWindowsPath = pathLink.windows_path();

      ::windows_path windowspath = strWindowsPath;

      if (FAILED(hr = ppersistfile->Load(windowspath.extended_path(), STGM_WRITE)))
      {

         return nullptr;

      }

      return pshelllink;

   }


   ::pointer < ::file::link > path_system::resolve_link(const ::file::path & path, ::file::e_link elink)
   {

      auto plink = ::path_system::resolve_link(path, elink);

      if (plink)
      {

         return plink;

      }

      if (path.case_insensitive_ends(".lnk"))
      {

         plink = resolve_lnk_link(path, elink);

         if (plink)
         {

            return plink;

         }

      }

      return nullptr;

   }


   ::pointer < ::file::link > path_system::resolve_lnk_link(const ::file::path & path, ::file::e_link elink)
   {

      auto plink = øcreate_new < ::acme_windows::file_link >();

      plink->open(path, elink);

      return plink;

   }


   void path_system::rename(const ::file::path & pathNewName, const ::file::path & pathOldName)
   {

      auto windowspathOld = pathOldName.windows_path();

      auto windowspathNew = pathNewName.windows_path();

      ::wstring wstrOld = windowspathOld.extended_path();

      ::wstring wstrNew = windowspathNew.extended_path();

      if (!::MoveFileW(wstrOld, wstrNew))
      {

         DWORD dwLastError = ::GetLastError();

         throw ::exception(error_failed);

      }

   }


   void path_system::symbolic_link(const ::file::path & pathTarget, const ::file::path & pathSource)
   {

      auto windowspathTarget = pathTarget.windows_path();

      auto windowspathSource = pathSource.windows_path();

      windowspathTarget = windowspathTarget.extended_path();

      windowspathSource = windowspathSource.extended_path();

      ::wstring wstrTarget = windowspathTarget.extended_path();
      
      ::wstring wstrSource = windowspathSource.extended_path();

      DWORD dwFlag = 0;

      if (directory_system()->is(pathSource))
      {

         dwFlag |= SYMBOLIC_LINK_FLAG_DIRECTORY;

      }

      dwFlag |= SYMBOLIC_LINK_FLAG_ALLOW_UNPRIVILEGED_CREATE;

      bool bOk = ::CreateSymbolicLinkW(wstrTarget, wstrSource, dwFlag);

      if (!bOk)
      {

         throw ::exception(error_failed);

      }

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



