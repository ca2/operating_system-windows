#include "framework.h"
#include "acme/filesystem/filesystem/path.h"
#include "acme/primitive/string/adaptor.h"
#include "acme/primitive/string/international.h"
#include "acme/primitive/string/string.h"
#include "acme/_library.h"
#include <shellapi.h>
#include <shlobj.h>


namespace acme_windows
{


   HINSTANCE load_library(const ::string & psz)
   {

      return ::LoadLibraryW(utf8_to_unicode(psz));

   }


   bool CLASS_DECL_ACME_WINDOWS shell_get_special_folder_path(HWND hwnd, ::file::path& str, i32 csidl, bool fCreate)
   {

      return ::SHGetSpecialFolderPathW(hwnd, wstring_adaptor(str, MAX_PATH * 8), csidl, fCreate) != false;

   }


   ::file::path CLASS_DECL_ACME_WINDOWS shell_get_special_folder_path(i32 csidl, bool fCreate, ::windowing::window* pwindow)
   {

      ::file::path path;

      if (!shell_get_special_folder_path(nullptr, path, csidl, fCreate))
      {

         return {};

      }

      return path;

   }




   ::u32 get_current_directory(string& str)
   {

      return ::GetCurrentDirectoryW(MAX_PATH * 8, wstring_adaptor(str, MAX_PATH * 8));

   }


   ::u32 get_temp_path(string& str)
   {

      return ::GetTempPathW(MAX_PATH * 8, wstring_adaptor(str, MAX_PATH * 8));

   }


   //::i32 reg_query_value(HKEY hkey, const ::string & pszSubKey, string& str)
   //{

   //   DWORD dwType = 0;
   //   DWORD dwSize = 0;
   //   ::i32 lResult = RegQueryValueExW(hkey, wstring(pszSubKey), nullptr, &dwType, nullptr, &dwSize);

   //   if (lResult != ERROR_SUCCESS)
   //      return lResult;
   //   ASSERT(dwType == REG_SZ || dwType == REG_MULTI_SZ || dwType == REG_EXPAND_SZ);
   //   if (dwType == REG_SZ || dwType == REG_MULTI_SZ || dwType == REG_EXPAND_SZ)
   //   {

   //      natural_wstring pwsz(byte_count, dwSize);

   //      lResult = RegQueryValueExW(hkey, wstring(pszSubKey), nullptr, &dwType, (::u8*)(unichar*)pwsz, &dwSize);

   //      str = pwsz;

   //      //str.release_buffer(dwSize);

   //      return lResult;

   //   }
   //   else
   //   {

   //      return ERROR_NOT_SUPPORTED;

   //   }

   //}


   HICON extract_icon(HINSTANCE hInst, const ::string & pszExeFileName, ::u32 nIconIndex)

   {

      return ::ExtractIconW(hInst, utf8_to_unicode(pszExeFileName), nIconIndex);


   }


} // namespace windows



