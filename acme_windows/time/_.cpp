#include "framework.h"
#include "acme/operating_system.h"


#include "acme/constant/id.h"
#include <VersionHelpers.h>

// #ifndef USE_OS_IMAGE_LOADER

// #include "FreeImage/FreeImage.h"

// #endif

#undef ___new
#include "gdiplus.h"
#include <ddeml.h>
#define ___new ACME_NEW


void __term_threading();
void __term_windowing();

CLASS_DECL_ACME bool is_verbose();



CLASS_DECL_ACME int __cdecl _memory_type(const void * p);


string key_to_char(wparam wparam, lparam lparam)
{



   unichar wsz[32];

   unsigned char baState[256];

   for(int i = 0; i < 256; i++)
   {
      baState[i] = (unsigned char) GetAsyncKeyState(i);
   }

   if((GetAsyncKeyState(VK_SHIFT) & I32_MINIMUM) != 0)
   {
      baState[VK_SHIFT] |= 0x80;
   }


   int iRet = ToUnicodeEx((unsigned int) wparam, (unsigned int) lparam, baState, wsz, 32, 0, GetKeyboardLayout(GetCurrentThreadId()));


   if(iRet > 0)
   {

      wsz[iRet] = L'\0';

      string str;

      str = unicode_to_utf8(wsz);

      if((GetAsyncKeyState(VK_CAPITAL) & 0x0001) != 0)
      {
         if((GetAsyncKeyState(VK_SHIFT) & I32_MINIMUM) != 0)
         {
            str.make_lower();
         }
         else
         {
            str.make_upper();
         }
      }
      else
      {
         if((GetAsyncKeyState(VK_SHIFT) & I32_MINIMUM) != 0)
         {
            str.make_upper();
         }
         else
         {
            str.make_lower();
         }
      }



      return str;

   }

   return "";

}


//string get_last_error_message(unsigned int dwError)
//{
//
//   LPWSTR pBuffer;
//
//   HMODULE Hand = nullptr;
//
//   if(!FormatMessageW(
//         FORMAT_MESSAGE_ALLOCATE_BUFFER |
//         FORMAT_MESSAGE_FROM_SYSTEM,
//         nullptr,
//         dwError,
//         0,
//         (LPWSTR) &pBuffer,
//
//         1,
//         nullptr))
//   {
//
//      HMODULE Hand = ::LoadLibraryW(L"NTDLL.DLL");
//
//      if(!FormatMessageW(
//            FORMAT_MESSAGE_ALLOCATE_BUFFER |
//            FORMAT_MESSAGE_FROM_SYSTEM |
//            FORMAT_MESSAGE_FROM_HMODULE,
//            Hand,
//            dwError,
//            0,
//            (LPWSTR) &pBuffer,
//
//            1,
//            nullptr))
//      {
//         FreeLibrary(Hand);
//         return "";
//      }
//
//   }
//
//   string str(pBuffer);
//
//
//   LocalFree(pBuffer);
//
//
//   if(Hand != nullptr)
//   {
//      FreeLibrary(Hand);
//   }
//
//   return str;
//
//}
//
//


/*

// This example checks if the operating system is of "NT-type"
// (which means Windows NT, 2000, XP).
int GetVersion_ex1()
{
   unsigned int    dwVersion = GetVersion();
   // Get major and minor version numbers of Windows
   unsigned short loword = LOWORD(dwVersion);
   int lowbyte = lower_byte(loword);
   int hibyte = higher_byte(loword);

   debug_print("Window major version = %d and minor version = %d\n", lowbyte, hibyte);

   if (!(dwVersion & I32_MINIMUM))                // Windows NT, 2000, XP
      return 1;
   else         // Windows 95, 98, ME
      return 0;
}


*/





int_bool is_windows_98_or_lesser()
{

//#if defined(_WIN32_WINNT) && (_WIN32_WINNT >= _WIN32_WINNT_WIN7) // Windows 7 or greater
#if defined(_WIN32_WINNT) && (_WIN32_WINNT >= _WIN32_WINNT_LONGHORN) // Windows 7 or greater

   return false;

#else

   OSVERSIONINFO osversioninfo;

   osversioninfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);

   if (!GetVersionEx(&osversioninfo))
      return 0;

   return
   osversioninfo.dwPlatformId == VER_PLATFORM_WIN32s
   || (osversioninfo.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS && ((osversioninfo.dwMajorVersion == 4 && osversioninfo.dwMinorVersion <= 10) || osversioninfo.dwMajorVersion < 4));

#endif

}

int_bool is_windows_nt()
{

#if defined(_WIN32_WINNT) && (_WIN32_WINNT >= _WIN32_WINNT_WINXP) // winxp or greater

   return IsWindowsXPOrGreater();

#else

   return !(GetVersion() & I32_MINIMUM);

#endif

}


int_bool is_windows_7_or_lower()
{

   return !IsWindows8OrGreater();

}


int_bool is_windows_8_or_greater()
{

#if defined(_WIN32_WINNT) && (_WIN32_WINNT >= _WIN32_WINNT_WINXP) // winxp or greater

   return IsWindows8OrGreater();

#else

   OSVERSIONINFO osversioninfo;

   osversioninfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);

   if(!GetVersionEx(&osversioninfo))
      return 0;

   throw ::exception(todo);

   return osversioninfo.dwPlatformId == VER_PLATFORM_WIN32_NT && osversioninfo.dwMajorVersion >= 6 && osversioninfo.dwMinorVersion >= 2;

#endif

}


//int_bool is_windows_vista_or_greater()
//{
//
//#if defined(_WIN32_WINNT) && (_WIN32_WINNT >= _WIN32_WINNT_WINXP) // winxp or greater
//
//   return IsWindowsVistaOrGreater();
//
//#else
//
//   OSVERSIONINFO osversioninfo;
//
//   osversioninfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
//
//   if (!GetVersionEx(&osversioninfo))
//      return 0;
//
//   return osversioninfo.dwPlatformId == VER_PLATFORM_WIN32_NT && osversioninfo.dwMajorVersion >= 6;
//
//#endif
//
//}


//int_bool is_windows_xp_or_greater()
//{
//
//#if defined(_WIN32_WINNT) && (_WIN32_WINNT >= _WIN32_WINNT_WINXP) // winxp or greater
//
//   return IsWindowsXPOrGreater();
//
//#else
//
//   OSVERSIONINFO osversioninfo;
//
//   osversioninfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
//
//   if (!GetVersionEx(&osversioninfo))
//      return 0;
//
//   return osversioninfo.dwPlatformId == VER_PLATFORM_WIN32_NT && (osversioninfo.dwMajorVersion > 5 || (osversioninfo.dwMajorVersion == 5 && osversioninfo.dwMinorVersion >= 1);
//
//#endif
//
//}
//
//
//int_bool is_windows_2000_or_greater()
//{
//
//#if defined(_WIN32_WINNT) && (_WIN32_WINNT >= _WIN32_WINNT_WINXP) // winxp or greater
//
//   return IsWindowsXPOrGreater();
//
//#else
//
//   OSVERSIONINFO osversioninfo;
//
//   osversioninfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
//
//   if (!GetVersionEx(&osversioninfo))
//      return 0;
//
//   return osversioninfo.dwPlatformId == VER_PLATFORM_WIN32_NT && osversioninfo.dwMajorVersion >= 5;
//
//#endif
//
//}


int_bool is_windows_nt_lesser_than_2000()
{

#if defined(_WIN32_WINNT) && (_WIN32_WINNT >= _WIN32_WINNT_WINXP) // winxp or greater

   return false;

#else

   OSVERSIONINFO osversioninfo;

   osversioninfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);

   if (!GetVersionEx(&osversioninfo))
   {

      return 0;

   }

   return osversioninfo.dwPlatformId == VER_PLATFORM_WIN32_NT && osversioninfo.dwMajorVersion < 5;

#endif

}


int_bool is_windows_native_unicode()
{

#if defined(_WIN32_WINNT) && (_WIN32_WINNT >= _WIN32_WINNT_WINXP) // winxp or greater

   return true;

#else

   static int_bool s_bNativeUnicode = -1;

   if (bNativeUnicode == -1)
   {

      unsigned int dwVersion = GetVersion();

      // get the Windows version.

      unsigned int dwWindowsMajorVersion = (unsigned int)(lower_byte(LOWORD(dwVersion)));
      unsigned int dwWindowsMinorVersion = (unsigned int)(higher_byte(LOWORD(dwVersion)));

      // get the build number.

      unsigned int dwBuild;

      if (dwVersion < I32_MINIMUM)              // Windows NT
         dwBuild = (unsigned int)(HIWORD(dwVersion));
      else if (dwWindowsMajorVersion < 4)      // Win32s
         dwBuild = (unsigned int)(HIWORD(dwVersion) & ~0x8000);
      else                                     // Windows Me/98/95
         dwBuild = 0;

      if (dwVersion < I32_MINIMUM)              // Windows NT
         s_bNativeUnicode = true;
      else if (dwWindowsMajorVersion < 4)      // Win32s
         s_bNativeUnicode = false;
      else                                     // Windows Me/98/95
         s_bNativeUnicode = false;

   }

   return bNativeUnicode;

#endif

}


// __is_valid_atom() returns true if the passed parameter is
// a valid local or global atom.
bool __is_valid_atom(ATOM nAtom)
{
   
   wchar_t sBuffer[256];

   if(GetAtomNameW(nAtom,sBuffer,_countof(sBuffer)))
   {
      
      return true;

   }
   
   DWORD dwError = ::GetLastError();

   if(dwError == ERROR_INSUFFICIENT_BUFFER || dwError == ERROR_MORE_DATA)
   {

      return true;

   }

   if(GlobalGetAtomNameW(nAtom,sBuffer,_countof(sBuffer)))
   {

      return true;

   }

   dwError = ::GetLastError();

   if(dwError == ERROR_INSUFFICIENT_BUFFER || dwError == ERROR_MORE_DATA)
   {

      return true;

   }

   return false;

}


// is_memory_segment_ok() returns true if the passed parameter is
// a valid representation of a local or a global atom within a const_char_pointer  .

bool __is_valid_atom(const scoped_string & str)
{

   return HIWORD(psz) == 0L && __is_valid_atom(ATOM(LOWORD(psz)));

}


bool __is_valid_atom(const wchar_t * psz)
{
   
   return HIWORD(psz) == 0L && __is_valid_atom(ATOM(LOWORD(psz)));

}


int_bool IsWow64()
{

   int_bool bIsWow64 = false;

   if (!IsWow64Process(GetCurrentProcess(), &bIsWow64))
   {
      return false;
   }

   return bIsWow64 != false;

}


int_bool EnableTokenPrivilege(LPCTSTR pszPrivilege)
{
   
   // do it only once
   static int_bool bEnabled = false;

   if (bEnabled)
   {
      
      return true;

   }

   bEnabled = true;

   HANDLE hToken = 0;

   TOKEN_PRIVILEGES tokenprivileges = { 0 };

   // Get a token for this process.
   if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken))
   {

      return false;

   }

   // Get the LUID for the privilege.
   if (LookupPrivilegeValue(nullptr, pszPrivilege, &tokenprivileges.Privileges[0].Luid))
   {
      
      tokenprivileges.PrivilegeCount = 1;  // one privilege to set
      
      tokenprivileges.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

      // set the privilege for this process.
      AdjustTokenPrivileges(hToken, false, &tokenprivileges, 0, (PTOKEN_PRIVILEGES)nullptr, 0);

      DWORD dwError = ::GetLastError();

      if (dwError != ERROR_SUCCESS)
      {

         return false;

      }

      return true;

   }

   return false;

}


CLASS_DECL_ACME string get_last_error_string()
{

   DWORD dwError = ::GetLastError();

   return get_error_string(dwError);

}


CLASS_DECL_ACME string get_error_string(DWORD dwError)
{

   WCHAR * pszError;

   FormatMessageW(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, nullptr, dwError, 0, (WCHAR *)&pszError, 0, nullptr);

   string strError(pszError);

   ::LocalFree(pszError);

   return strError;

}




bool __node_pos_init()
{

   return true;

}


bool __node_pre_term()
{

   return true;

}


bool __node_pos_term()
{

   return true;

}





CLASS_DECL_ACME hinstance get_module_handle(const platform_char * psz)
{

   return (hinstance) GetModuleHandle(psz);

}



namespace windows
{

   class CLASS_DECL_ACME message_box :
      virtual public ::conversation
   {
   public:

      HWND                 m_hwnd;
      string               m_strMessage;
      string               m_strTitle;
      ::e_message_box      m_emessagebox;

      
      message_box() { m_hwnd = nullptr; m_emessagebox = e_message_box_ok; }

      ::enum_dialog_result show(HWND hwnd, const scoped_string & strMessage, const scoped_string & strTitle, const ::e_message_box& emessagebox)
      {

         m_hwnd = hwnd;
         m_strMessage = pszMessage;
         m_strTitle = pszTitle;
         m_emessagebox = emessagebox;

         return __show();

      }

      
         ::enum_dialog_result __show()
         {

            return
               (::enum_dialog_result)
               ::MessageBox(
                  m_hwnd,
                  wstring(m_strMessage),
                  wstring(m_strTitle),
                  (int)m_emessagebox.m_eenum);

         }

   };


} // namespace windows



// pointer< ::extended::future < ::conversation > > xxxshow_error_message(const ::scoped_string & scopedstrMessage, const ::scoped_string & scopedstrTitle, const ::e_message_box & emessagebox)
// {

//    wstring wstrMessage(strMessage);

//    wstring wstrTitle(strTitle);

//    auto pmessagebox = __allocate windows::message_box();

//    auto pfuture = pmessagebox->::extended::asynchronous <::conversation>::future();

//    pmessagebox->m_edialogresult = pmessagebox->show(nullptr, strMessage, strTitle, emessagebox);

//    pfuture->set_status(::success);

//    return pfuture;

// }



