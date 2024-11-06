#include "framework.h"
#include "acme/operating_system.h"


namespace str
{


#ifdef WINDOWS


   BSTR AllocSysString(const ::wd16_character * pchData, character_count nDataLength) noexcept
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
   bool ReAllocSysString(BSTR * pbstr, const ::wd16_character * pchData, character_count nDataLength) noexcept
   {

      character_count nLen = utf_to_utf_length(pbstr, pchData, nDataLength);

      bool bSuccess = ::SysReAllocStringLen(pbstr, nullptr, (unsigned int)nLen) != 0;

      if (bSuccess)
      {

         utf_to_utf(*pbstr, pchData, nDataLength);

      }

      return bSuccess;

   }


#endif


   unsigned int format_message(unsigned int dwFlags, const void * pSource, unsigned int dwMessageID, unsigned int dwLanguageID, ::wd16_character * pszBuffer, unsigned int nSize, va_list * pArguments) noexcept
   {

#ifdef WINDOWS

      return ::FormatMessageW(dwFlags, pSource, dwMessageID, dwLanguageID, pszBuffer, nSize, pArguments);

#else

      return 0;

#endif

   }


   //character_count  char_traits::SafeStringLen(const ::wd16_character * psz) noexcept
   //{
   //   // returns length in bytes
   //   return (psz != nullptr) ? character_count(strlen(psz)) : 0;
   //}
   //
   //character_count  char_traits::SafeStringLen(const ::wd16_character * psz) noexcept
   //{
   //   // returns length in wchar_ts
   //#ifdef WINDOWS
   //   return (psz != nullptr) ? character_count(wd16_len(psz)) : 0;
   //#else
   //   return (psz != nullptr) ? character_count(wd16__length(psz)) : 0;
   //#endif
   //}
   //
   //character_count  char_traits::GetCharLen(const ::wd16_character* pch) noexcept
   //{
   //   (void)pch;
   //   // returns ::wd16_character length
   //   return 1;
   //}
   //
   //character_count  char_traits::GetCharLen(const ::wd16_character* pch) noexcept
   //{
   //   // returns ::wd16_character length
   //   return  ::str().get_utf8_char(pch).get_length();
   //}


//    unsigned int xxxget_environment_variable(const ::wd16_character * pszVar, ::wd16_character * pszBuffer, unsigned int dwSize)
//    {

// #ifdef UNIVERSAL_WINDOWS

//       throw ::exception(todo);

// #elif defined(WINDOWS_DESKTOP)

//       return ::GetEnvironmentVariableW(pszVar, pszBuffer, dwSize);

// #else

//       string strVar(pszVar);

//       auto pszEnv = getenv(strVar);

//       wd16_string wstrEnv(pszEnv);

//       if (pszBuffer == nullptr)
//       {

//          if (pszEnv == nullptr)
//          {

//             return 0;

//          }
//          else
//          {

//             return (unsigned int)wstrEnv.get_length();

//          }

//       }

//       return (unsigned int)__wd16len(wd16_count_copy(pszBuffer, wstrEnv, dwSize));

// #endif

//    }



} // namespace str



