#include "framework.h"
#include "acme/prototype/string/string.h"
#include "acme/_operating_system.h"


namespace windows
{

   //struct langid_iso
   //{

   //   LANGID m_langid;
   //   string m_strIso;

   //   langid_iso(LANGID langid, const ::scoped_string & scopedstrIso);

   //};




   CLASS_DECL_ACME_WINDOWS string langid_to_iso(LANGID langid)
   {

      if (PRIMARYLANGID(langid) == LANG_DANISH)
      {

         return "da";

      }
      else if (PRIMARYLANGID(langid) == LANG_ENGLISH)
      {

         return "en";

      }
      else if (PRIMARYLANGID(langid) == LANG_GERMAN)
      {

         return "de";

      }
      else if (PRIMARYLANGID(langid) == LANG_JAPANESE)
      {

         return "jp";

      }
      else if (PRIMARYLANGID(langid) == LANG_POLISH)
      {

         return "pl";

      }
      else if (langid == MAKELANGID(LANG_PORTUGUESE, SUBLANG_PORTUGUESE_BRAZILIAN))
      {

         return "pt-br";

      }
      else if (langid == LANG_SWEDISH)
      {

         return "se";

      }
      else
      {

         return "_std";

      }

   }


} // namespace acme_windows




