#include "framework.h"
#include "acme/operating_system.h"


namespace windows
{


   FARPROC api_base::get_address(const scoped_string & strModule, const_char_pointer pszName)
   {

      auto hmodule = ::GetModuleHandleW(wstring(pszModule));

      if (hmodule)
      {

         return GetProcAddress(hmodule, pszName);

      }

      return nullptr;

   }


} // namespace windows



