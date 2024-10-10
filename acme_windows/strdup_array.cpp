#include "framework.h"
#include "node.h"
#include "acme/prototype/collection/strdup_array.h"


namespace acme_windows 
{


   platform_char** node::get_envp(wcsdup_array& wcsdupa)
   {

      auto lpvEnv = ::GetEnvironmentStringsW();

      if (lpvEnv == NULL)
      {

         return nullptr;

      }

      // Variable strings are separated by NULL ::u8, and the block is terminated by a NULL ::u8.

      for (auto lpszVariable = (LPWSTR)lpvEnv; *lpszVariable; lpszVariable++)
      {

         wstring wstrVariable(lpszVariable);

         auto pszVariable = wcsdup(wstrVariable);

         wcsdupa.m_wszptra.add(pszVariable);

         while (*lpszVariable)
         {

            lpszVariable++;

         }

      }

      if (!FreeEnvironmentStrings(lpvEnv))
      {

         ::output_debug_string("GetEnvironmentStrings() failed.");

      }

      return wcsdupa.m_wszptra.data();

   }


} // namespace acme_windows



