#include "framework.h"
#include "acme/prototype/string/string.h"
#include "acme/_operating_system.h"


BSTR AllocSysString(const ::wd16_character * pchData, strsize nDataLength) noexcept
{

   BSTR bstr = nullptr;

   strsize nLen = utf_to_utf_length(bstr, pchData, nDataLength);

   bstr = ::SysAllocStringLen(nullptr, (::u32)nLen);

   if (bstr != nullptr)
   {

      ::utf_to_utf(bstr, pchData, nDataLength);

   }

   return bstr;

}


// pbstr is [in,out] BSTR string
bool ReAllocSysString(BSTR * pbstr, const ::wd16_character * pchData, strsize nDataLength) noexcept
{

   strsize nLen = utf_to_utf_length((wchar_t* ) pbstr, pchData, nDataLength);

   bool bSuccess = ::SysReAllocStringLen(pbstr, nullptr, (::u32)nLen) != 0;

   if (bSuccess)
   {

      ::utf_to_utf(*pbstr, pchData, nDataLength);

   }

   return bSuccess;

}


u32 format_message(u32 dwFlags, const void * pSource, u32 dwMessageID, u32 dwLanguageID, ::wd16_character * pszBuffer, u32 nSize, va_list * pArguments) noexcept
{

   return ::FormatMessageW(dwFlags, pSource, dwMessageID, dwLanguageID, pszBuffer, nSize, pArguments);

}



