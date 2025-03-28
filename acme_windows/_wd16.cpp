#include "framework.h"
#include "acme/prototype/string/string.h"
#include "acme/_operating_system.h"


BSTR AllocSysString(const ::wd16_character * pchData, character_count nDataLength) noexcept
{

   BSTR bstr = nullptr;

   character_count nLen = utf_to_utf_length(bstr, pchData, nDataLength);

   bstr = ::SysAllocStringLen(nullptr, (unsigned int)nLen);

   if (bstr != nullptr)
   {

      ::utf_to_utf(bstr, pchData, nDataLength);

   }

   return bstr;

}


// pbstr is [in,out] BSTR string
bool ReAllocSysString(BSTR * pbstr, const ::wd16_character * pchData, character_count nDataLength) noexcept
{

   character_count nLen = utf_to_utf_length((wchar_t* ) pbstr, pchData, nDataLength);

   bool bSuccess = ::SysReAllocStringLen(pbstr, nullptr, (unsigned int)nLen) != 0;

   if (bSuccess)
   {

      ::utf_to_utf(*pbstr, pchData, nDataLength);

   }

   return bSuccess;

}


unsigned int format_message(unsigned int dwFlags, const void * pSource, unsigned int dwMessageID, unsigned int dwLanguageID, ::wd16_character * pszBuffer, unsigned int nSize, va_list * pArguments) noexcept
{

   return ::FormatMessageW(dwFlags, pSource, dwMessageID, dwLanguageID, pszBuffer, nSize, pArguments);

}



