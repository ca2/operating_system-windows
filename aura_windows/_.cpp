#include "framework.h"
#include "acme/_library.h"


//void CLASS_DECL_ACME_WINDOWS __cdecl _ca2_purecall()
//{
//
//   throw ::exception(::exception());
//
//}
//






namespace windows
{




   //HINSTANCE load_library(const ::scoped_string & scopedstr)

   //{

   //   return ::LoadLibraryW(utf8_to_unicode(psz));


   //}


   //bool CLASS_DECL_ACME_WINDOWS shell_get_special_folder_path(HWND hwnd, ::file::path& str, int csidl, bool fCreate)
   //{

   //   return ::SHGetSpecialFolderPathW(hwnd, wstring_adaptor(str, MAX_PATH * 8), csidl, fCreate) != false;

   //}


   //::file::path CLASS_DECL_ACME_WINDOWS shell_get_special_folder_path(int csidl, bool fCreate, ::windowing::window* pwindow)
   //{

   //   ::file::path path;

   //   if (!shell_get_special_folder_path(nullptr, path, csidl, fCreate))
   //   {

   //      return "";

   //   }

   //   return path;

   //}




   //unsigned int get_current_directory(string& str)
   //{

   //   return ::GetCurrentDirectoryW(MAX_PATH * 8, wstring_adaptor(str, MAX_PATH * 8));

   //}


   //unsigned int get_temp_path(string& str)
   //{

   //   return ::GetTempPathW(MAX_PATH * 8, wstring_adaptor(str, MAX_PATH * 8));

   //}


   //int reg_query_value(HKEY hkey, const ::scoped_string & scopedstrSubKey, string& str)
   //{

   //   DWORD dwType = 0;
   //   DWORD dwSize = 0;
   //   int lResult = RegQueryValueExW(hkey, wstring(pszSubKey), nullptr, &dwType, nullptr, &dwSize);

   //   if (lResult != ERROR_SUCCESS)
   //      return lResult;
   //   ASSERT(dwType == REG_SZ || dwType == REG_MULTI_SZ || dwType == REG_EXPAND_SZ);
   //   if (dwType == REG_SZ || dwType == REG_MULTI_SZ || dwType == REG_EXPAND_SZ)
   //   {

   //      natural_wstring pwsz(byte_count, dwSize);

   //      lResult = RegQueryValueExW(hkey, wstring(pszSubKey), nullptr, &dwType, (unsigned char*)(unichar*)pwsz, &dwSize);

   //      str = pwsz;

   //      //str.release_buffer(dwSize);

   //      return lResult;

   //   }
   //   else
   //   {

   //      return ERROR_NOT_SUPPORTED;

   //   }

   //}


   //HICON extract_icon(HINSTANCE hInst, const ::scoped_string & scopedstrExeFileName, unsigned int nIconIndex)

   //{

   //   return ::ExtractIconW(hInst, utf8_to_unicode(pszExeFileName), nIconIndex);


   //}


   //bool delete_file(const ::scoped_string & scopedstrFileName)

   //{

   //   return ::DeleteFileW(utf8_to_unicode(pFileName)) != false;


   //}





} // namespace windows



//LRESULT CALLBACK __window_procedure(HWND oswindow, ::user::enum_message eusermessage, ::wparam wparam, ::lparam lparam);
//
//WNDPROC get_window_procedure()
//{
//
//   return &::__window_procedure;
//
//}





