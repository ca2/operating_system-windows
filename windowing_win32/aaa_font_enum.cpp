#include "framework.h"


namespace windowing_win32
{



   class wingdi_font_enum
   {
   public:


      HDC                                 m_hdc;
      ::write_text::font_enumeration_item_array & m_itema;
      bool                                m_bRaster;
      bool                                m_bTrueType;
      bool                                m_bOther;
      wstring                             m_wstrTopicFaceName;
      int_array                           m_iaCharSet;


      wingdi_font_enum(::write_text::font_enumeration_item_array & itema, bool bRaster, bool bTrueType, bool bOther) :
         m_itema(itema),
         m_bRaster(bRaster),
         m_bTrueType(bTrueType),
         m_bOther(bOther)
      {

         m_iaCharSet.add(CHINESEBIG5_CHARSET);
         m_iaCharSet.add(GB2312_CHARSET);
         m_iaCharSet.add(SHIFTJIS_CHARSET);
         //m_iaCharSet.add(ANSI_CHARSET);
         m_iaCharSet.add(SYMBOL_CHARSET);
         //m_iaCharSet.add(OEM_CHARSET);
         //m_iaCharSet.add(DEFAULT_CHARSET);
         m_iaCharSet.add(HEBREW_CHARSET);
         m_iaCharSet.add(ARABIC_CHARSET);
         m_iaCharSet.add(GREEK_CHARSET);
         m_iaCharSet.add(TURKISH_CHARSET);
         m_iaCharSet.add(VIETNAMESE_CHARSET);
         m_iaCharSet.add(THAI_CHARSET);
         m_iaCharSet.add(EASTEUROPE_CHARSET);
         m_iaCharSet.add(RUSSIAN_CHARSET);
         m_iaCharSet.add(JOHAB_CHARSET);
         m_iaCharSet.add(HANGUL_CHARSET);
         m_iaCharSet.add(BALTIC_CHARSET);
         //m_iaCharSet.add(MAC_CHARSET);

         m_hdc = nullptr;

         enumerate();

      }


      ~wingdi_font_enum()
      {

         ::DeleteDC(m_hdc);

      }


      void enumerate()
      {

         if (m_hdc == nullptr)
         {

            m_hdc = ::CreateCompatibleDC(nullptr);

         }

         ::EnumFontFamiliesW(m_hdc, (const widechar *)nullptr, (FONTENUMPROCW)&wingdi_font_enum::callback, (lparam)this);

         for (auto & pitem : m_itema.ptra())
         {

            enum_cs(pitem);

         }

      }


      void enum_cs(::write_text::font_enumeration_item * pitem)
      {

         ::EnumFontFamiliesW(m_hdc, pitem->m_wstrName, (FONTENUMPROCW)&wingdi_font_enum::callback_cs, (lparam)pitem);

      }


      static BOOL CALLBACK callback(LPLOGFONTW plf, LPNEWTEXTMETRICW lpntm, ::u32 FontType, LPVOID point_i32);


      static BOOL CALLBACK callback_cs(LPLOGFONTW plf, LPNEWTEXTMETRICW lpntm, ::u32 FontType, LPVOID point_i32);


   };




   BOOL CALLBACK wingdi_font_enum::callback(LPLOGFONTW plf, LPNEWTEXTMETRICW lpntm, ::u32 dwFontType, LPVOID p)
   {

      wingdi_font_enum * penum = (wingdi_font_enum *)p;

      if (wcslen(plf->lfFaceName) > 1 && plf->lfFaceName[0] == '@')
      {

      }
      else if (dwFontType & RASTER_FONTTYPE)
      {

         if (penum->m_bRaster)
         {

            penum->m_itema.add(__new(::write_text::font_enumeration_item(plf->lfFaceName)));

         }

      }
      else if (dwFontType & TRUETYPE_FONTTYPE)
      {

         if (penum->m_bTrueType)
         {

            penum->m_itema.add(__new(::write_text::font_enumeration_item(plf->lfFaceName)));

         }

      }
      else
      {

         if (penum->m_bOther)
         {

            penum->m_itema.add(__new(::write_text::font_enumeration_item(plf->lfFaceName)));

         }

      }

      return true;

   }


   BOOL CALLBACK wingdi_font_enum::callback_cs(LPLOGFONTW plf, LPNEWTEXTMETRICW lpntm, ::u32 dwFontType, LPVOID p)
   {

      ::write_text::font_enumeration_item * pitem = (::write_text::font_enumeration_item *)p;

      ::enum_character_set echarset = wingdi_get_cs(plf->lfCharSet);

      if (echarset != ::e_character_set_ansi && echarset != ::e_character_set_default)
      {

         pitem->m_echaracterseta.add(echarset);

      }

      return true;

   }


   CLASS_DECL_WINDOWING_WIN32 void wingdi_enum_fonts(::write_text::font_enumeration_item_array & itema, bool bRaster, bool bTrueType, bool bOther)
   {

      wingdi_font_enum fonts(itema, bRaster, bTrueType, bOther);

   }


   ::enum_character_set wingdi_get_cs(int iCs)
   {

      if (iCs == CHINESEBIG5_CHARSET)
      {

         return ::e_character_set_chinesebig5;

      }
      else if (iCs == GB2312_CHARSET)
      {

         return ::e_character_set_gb2312;

      }
      else if (iCs == SHIFTJIS_CHARSET)
      {

         return ::e_character_set_shiftjis;

      }
      else if (iCs == ANSI_CHARSET)
      {

         return ::e_character_set_ansi;

      }
      else if (iCs == SYMBOL_CHARSET)
      {

         return ::e_character_set_symbol;

      }
      else if (iCs == OEM_CHARSET)
      {

         return ::e_character_set_default;

      }
      else if (iCs == DEFAULT_CHARSET)
      {

         return ::e_character_set_default;

      }
      else if (iCs == HEBREW_CHARSET)
      {

         return ::e_character_set_hebrew;

      }
      else if (iCs == ARABIC_CHARSET)
      {

         return ::e_character_set_arabic;

      }
      else if (iCs == GREEK_CHARSET)
      {

         return ::e_character_set_greek;

      }
      else if (iCs == TURKISH_CHARSET)
      {

         return ::e_character_set_turkish;

      }
      else if (iCs == VIETNAMESE_CHARSET)
      {

         return ::e_character_set_vietnamese;

      }
      else if (iCs == THAI_CHARSET)
      {

         return ::e_character_set_thai;

      }
      else if (iCs == EASTEUROPE_CHARSET)
      {

         return ::e_character_set_easteurope;

      }
      else if (iCs == RUSSIAN_CHARSET)
      {

         return ::e_character_set_russian;

      }
      else if (iCs == JOHAB_CHARSET)
      {

         return ::e_character_set_johab;

      }
      else if (iCs == HANGUL_CHARSET)
      {

         return ::e_character_set_hangul;

      }
      else if (iCs == BALTIC_CHARSET)
      {

         return ::e_character_set_baltic;

      }
      else if (iCs == MAC_CHARSET)
      {

         return ::e_character_set_mac;

      }
      else
      {

         output_debug_string("OTHER char SET");

      }

      return ::e_character_set_default;

   }


} // namespace windowing_win32



