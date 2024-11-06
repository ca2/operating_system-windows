#pragma once



// Format a message using format string_base < TYPE_CHAR > 'pszFormat'
template < typename TYPE_CHAR >
void __cdecl string_base < TYPE_CHAR >::FormatMessage(const CHAR_TYPE * pszFormat, ...)
{
   if (pszFormat == nullptr)
   {

      throw ::exception(error_bad_argument);

   }

   va_list argList;

   va_start(argList, pszFormat);

   FormatMessageV(pszFormat, argList);

   va_end(argList);

}


void FormatMessageV(const CHAR_TYPE * pszFormat, va_list args);

// Format a message using format string_base < TYPE_CHAR > 'pszFormat' and va_list
template < typename TYPE_CHAR >
void string_base < TYPE_CHAR >::FormatMessageV(const CHAR_TYPE * pszFormat, va_list argList)
{

#ifdef WINDOWS_DESKTOP

   // format message into temporary buffer pszTemp

   CHAR_TYPE * pszTemp;

   unsigned int dwResult = ::str().format_message(FORMAT_MESSAGE_FROM_STRING | FORMAT_MESSAGE_ALLOCATE_BUFFER, pszFormat, 0, 0, reinterpret_cast<CHAR_TYPE *>(&pszTemp), 0, &argList);

   if (dwResult == 0)
   {

      throw no_memory();

   }

   *this = pszTemp;

   LocalFree(pszTemp);

#else

   FormatV(pszFormat, argList);

#endif

}



#ifdef WINDOWS

// OLE BSTR support

// allocate a BSTR containing a copy of the string_base < TYPE_CHAR >
template < typename TYPE_CHAR >
BSTR string_base < TYPE_CHAR >::AllocSysString() const
{
   BSTR bstrResult = ::str().AllocSysString(data(), get_length());
   if (bstrResult == nullptr)
   {
      throw no_memory();
   }
   return(bstrResult);
}


template < typename TYPE_CHAR >
BSTR string_base < TYPE_CHAR >::SetSysString(BSTR * pbstr) const
{

   ASSERT(is_memory_segment_ok(pbstr, sizeof(BSTR)));

   if (!::str().ReAllocSysString(pbstr, data(), get_length()))
   {

      throw no_memory();

   }

   ASSERT(*pbstr != nullptr);

   return(*pbstr);

}

#endif

