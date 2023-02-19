// Created by camilo on 2021-06-05 21:17 BRT <3ThomasBS_!!
#include "framework.h"
#include "write_text_win32_gdi.h"


#undef USUAL_OPERATING_SYSTEM_SUPPRESSIONS
#include "acme/_operating_system.h"


namespace write_text_win32_gdi
{


   ::enum_character_set get_character_set(int iCharacterSet)
   {

      if (iCharacterSet == CHINESEBIG5_CHARSET)
      {

         return ::e_character_set_chinesebig5;

      }
      else if (iCharacterSet == GB2312_CHARSET)
      {

         return ::e_character_set_gb2312;

      }
      else if (iCharacterSet == SHIFTJIS_CHARSET)
      {

         return ::e_character_set_shiftjis;

      }
      else if (iCharacterSet == ANSI_CHARSET)
      {

         return ::e_character_set_ansi;

      }
      else if (iCharacterSet == SYMBOL_CHARSET)
      {

         return ::e_character_set_symbol;

      }
      else if (iCharacterSet == OEM_CHARSET)
      {

         return ::e_character_set_default;

      }
      else if (iCharacterSet == DEFAULT_CHARSET)
      {

         return ::e_character_set_default;

      }
      else if (iCharacterSet == HEBREW_CHARSET)
      {

         return ::e_character_set_hebrew;

      }
      else if (iCharacterSet == ARABIC_CHARSET)
      {

         return ::e_character_set_arabic;

      }
      else if (iCharacterSet == GREEK_CHARSET)
      {

         return ::e_character_set_greek;

      }
      else if (iCharacterSet == TURKISH_CHARSET)
      {

         return ::e_character_set_turkish;

      }
      else if (iCharacterSet == VIETNAMESE_CHARSET)
      {

         return ::e_character_set_vietnamese;

      }
      else if (iCharacterSet == THAI_CHARSET)
      {

         return ::e_character_set_thai;

      }
      else if (iCharacterSet == EASTEUROPE_CHARSET)
      {

         return ::e_character_set_easteurope;

      }
      else if (iCharacterSet == RUSSIAN_CHARSET)
      {

         return ::e_character_set_russian;

      }
      else if (iCharacterSet == JOHAB_CHARSET)
      {

         return ::e_character_set_johab;

      }
      else if (iCharacterSet == HANGUL_CHARSET)
      {

         return ::e_character_set_hangul;

      }
      else if (iCharacterSet == BALTIC_CHARSET)
      {

         return ::e_character_set_baltic;

      }
      else if (iCharacterSet == MAC_CHARSET)
      {

         return ::e_character_set_mac;

      }
      else
      {

         output_debug_string("OTHER char SET");

      }

      return ::e_character_set_default;

   }


} // namespace write_text_win32_gdi



