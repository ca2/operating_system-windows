#include "framework.h"
#include "acme/operating_system.h"


namespace str
{


   BSTR AllocSysString(const ::ansi_character * pchData, character_count nDataLength) noexcept
   {

      BSTR bstr = nullptr;

      character_count nLen = utf_to_utf_length(bstr, pchData, nDataLength);

      bstr = ::SysAllocStringLen(nullptr, (unsigned int)nLen);

      if (bstr != nullptr)
      {

         utf_to_utf(bstr, pchData, nDataLength);

      }

      return bstr;

   }


   // pbstr is [in,out] BSTR string
   bool ReAllocSysString(BSTR * pbstr, const ::ansi_character * pchData, character_count nDataLength) noexcept
   {

      character_count nLen = utf_to_utf_length(pbstr, pchData, nDataLength);

      bool bSuccess = ::SysReAllocStringLen(pbstr, nullptr, (unsigned int)nLen) != 0;

      if (bSuccess)
      {

         utf_to_utf(*pbstr, pchData, nDataLength);

      }

      return bSuccess;

   }


   inline wstring bstr_to_wstr(BSTR bstr)
   {

      int len = ::SysStringLen(bstr);

      wstring wstr((wchar_t *)bstr, len);

      return wstr;

   }


   inline string bstr_to_str(BSTR bstr)
   {

      wstring wstr = bstr_to_wstr(bstr);

      return wstr;

   }


   unsigned int format_message(unsigned int dwFlags, const void * pSource, unsigned int dwMessageID, unsigned int dwLanguageID, ::ansi_character * pszBuffer, unsigned int nSize, va_list * pArguments) noexcept
   {

       return ::FormatMessageA(dwFlags, pSource, dwMessageID, dwLanguageID, pszBuffer, nSize, pArguments);

   }

   
//    unsigned int xxxget_environment_variable(const ::ansi_character * pszVar, ::ansi_character * pszBuffer, unsigned int dwSize)
//    {

// #ifdef UNIVERSAL_WINDOWS

//          throw ::exception(todo);

// #elif defined(WINDOWS_DESKTOP)

//          return ::GetEnvironmentVariableA(pszVar, pszBuffer, dwSize);

// #else

//          const ::ansi_character * pszEnv = getenv(pszVar);

//          if (pszBuffer == nullptr)
//          {

//             if (pszEnv == nullptr)
//             {

//                return 0;

//             }
//             else
//             {

//                return (unsigned int)strlen(pszEnv);

//             }

//          }

//          return (unsigned int)strlen(ansi_count_copy(pszBuffer, pszEnv, dwSize));

// #endif

//    }


} // namespace str





CLASS_DECL_ACME BSTR AllocSysString(const ::scoped_string & scopedstr)
{

   return ::str().AllocSysString(str.c_str(), str.length());

}


CLASS_DECL_ACME BSTR SetSysString(BSTR * pbstr, const ::scoped_string & scopedstr)
{

   ::str().ReAllocSysString(pbstr, str.c_str(), str.length());
   
   return *pbstr;

}
