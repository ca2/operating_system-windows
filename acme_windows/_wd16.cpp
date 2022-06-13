#include "framework.h"
#include "acme/operating_system.h"


BSTR AllocSysString(const wd16char * pchData, strsize nDataLength) noexcept
{

   BSTR bstr = nullptr;

   strsize nLen = ::str().utf_to_utf_length(bstr, pchData, nDataLength);

   bstr = ::SysAllocStringLen(nullptr, (::u32)nLen);

   if (bstr != nullptr)
   {

      ::str().utf_to_utf(bstr, pchData, nDataLength);

   }

   return bstr;

}


// pbstr is [in,out] BSTR string
bool ReAllocSysString(BSTR * pbstr, const wd16char * pchData, strsize nDataLength) noexcept
{

   strsize nLen = ::str().utf_to_utf_length((wchar_t* ) pbstr, pchData, nDataLength);

   bool bSuccess = ::SysReAllocStringLen(pbstr, nullptr, (::u32)nLen) != 0;

   if (bSuccess)
   {

      ::str().utf_to_utf(*pbstr, pchData, nDataLength);

   }

   return bSuccess;

}


u32 format_message(u32 dwFlags, const void * pSource, u32 dwMessageID, u32 dwLanguageID, wd16char * pszBuffer, u32 nSize, va_list * pArguments) noexcept
{

   return ::FormatMessageW(dwFlags, pSource, dwMessageID, dwLanguageID, pszBuffer, nSize, pArguments);

}



