#include "framework.h"
#include "acme/operating_system.h"


//namespace str
//{


   u32 format_message(u32 dwFlags, const void * pSource, u32 dwMessageID, u32 dwLanguageID, ansichar * pszBuffer, u32 nSize, va_list * pArguments) noexcept
   {

       return ::FormatMessageA(dwFlags, pSource, dwMessageID, dwLanguageID, pszBuffer, nSize, pArguments);

   }

//   
//
//} // namespace str




//
//CLASS_DECL_ACME BSTR AllocSysString(const ::string & str)
//{
//
//   return ::str().AllocSysString(str.c_str(), str.get_length());
//
//}
//
//
//CLASS_DECL_ACME BSTR SetSysString(BSTR * pbstr, const ::string & str)
//{
//
//   ::str().ReAllocSysString(pbstr, str.c_str(), str.get_length());
//   
//   return *pbstr;
//
//}
