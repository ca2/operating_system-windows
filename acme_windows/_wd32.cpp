#include "framework.h"
#include "acme/prototype/string/string.h"
#include "acme/_operating_system.h"


BSTR AllocSysString(const ::wd32_character * pchData, strsize nDataLength) noexcept
{

   BSTR bstr = nullptr;

   strsize nLen = utf_to_utf_length(bstr, pchData, nDataLength);

   bstr = ::SysAllocStringLen(nullptr, (unsigned int)nLen);

   if (bstr != nullptr)
   {

      ::utf_to_utf(bstr, pchData, nDataLength);

   }

   return bstr;

}


// pbstr is [in,out] BSTR string
bool ReAllocSysString(BSTR * pbstr, const ::wd32_character * pchData, strsize nDataLength) noexcept
{

   strsize nLen = utf_to_utf_length((wchar_t *) pbstr, pchData, nDataLength);

   bool bSuccess = ::SysReAllocStringLen(pbstr, nullptr, (unsigned int)nLen) != 0;

   if (bSuccess)
   {

      ::utf_to_utf(*pbstr, pchData, nDataLength);

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



