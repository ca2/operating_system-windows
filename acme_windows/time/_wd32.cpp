#include "framework.h"
#include "acme/operating_system.h"


namespace str
{




BSTR AllocSysString(const ::wd32_character * pchData, character_count nDataLength) noexcept
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
bool ReAllocSysString(BSTR * pbstr, const ::wd32_character * pchData, character_count nDataLength) noexcept
{

   character_count nLen = utf_to_utf_length(pbstr, pchData, nDataLength);

   bool bSuccess = ::SysReAllocStringLen(pbstr, nullptr, (unsigned int)nLen) != 0;

   if (bSuccess)
   {

      utf_to_utf(*pbstr, pchData, nDataLength);

   }

   return bSuccess;

}



unsigned int format_message(unsigned int dwFlags, const void * pSource, unsigned int dwMessageID, unsigned int dwLanguageID, ::wd32_character * pszBuffer, unsigned int nSize, va_list * pArguments) noexcept
{

#ifdef WINDOWS

   throw_todo();

   return 0;

   //return ::FormatMessageW(dwFlags, pSource, dwMessageID, dwLanguageID, pszBuffer, nSize, pArguments);

#else

   return 0;

#endif

}


//character_count  char_traits::SafeStringLen(const ::wd32_character * psz) noexcept
//{
//   // returns length in bytes
//   return (psz != nullptr) ? character_count(strlen(psz)) : 0;
//}
//
//character_count  char_traits::SafeStringLen(const ::wd32_character * psz) noexcept
//{
//   // returns length in wchar_ts
//#ifdef WINDOWS
//   return (psz != nullptr) ? character_count(wd32_len(psz)) : 0;
//#else
//   return (psz != nullptr) ? character_count(wide_length(psz)) : 0;
//#endif
//}
//
//character_count  char_traits::GetCharLen(const ::wd32_character* pch) noexcept
//{
//   (void)pch;
//   // returns ::wd32_character length
//   return 1;
//}
//
//character_count  char_traits::GetCharLen(const ::wd32_character* pch) noexcept
//{
//   // returns ::wd32_character length
//   return  ::str().get_utf8_char(pch).get_length();
//}


// unsigned int xxxget_environment_variable(const ::wd32_character * pszVar, ::wd32_character * pszBuffer, unsigned int dwSize)
// {

// #ifdef UNIVERSAL_WINDOWS

//    throw ::exception(todo);

// #elif defined(WINDOWS_DESKTOP)

//    wstring wstr;

//    auto psz = wstr.get_buffer(dwSize);

//    wstring wstrVar(pszVar);

//    auto result = ::GetEnvironmentVariableW(wstrVar, psz, dwSize);

//    utf_to_utf(pszBuffer, psz);

//    return result;

// #else

//    string strVar(pszVar);

//    auto pszEnv = getenv(strVar);

//    wd32_string wstrEnv(pszEnv);

//    if (pszBuffer == nullptr)
//    {

//       if (pszEnv == nullptr)
//       {

//          return 0;

//       }
//       else
//       {

//          return (unsigned int)wstrEnv.get_length();

//       }

//    }

//    return (unsigned int)__wd32len(wd32_count_copy(pszBuffer, wstrEnv, dwSize));

// #endif

// }


} // namespace str





void output_debug_string(const ::wd32_character * psz)
{

   string str(psz);

   output_debug_string(str);

}

