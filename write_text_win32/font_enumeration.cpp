// Created by camilo 2021-01
// Recreated by camilo 2021-02-10 <3TBS_!!
#include "framework.h"
#include "write_text_win32_gdi.h"


namespace write_text_win32
{

   
   font_enumeration::font_enumeration()
   {

      //m_iaCharSet.add(CHINESEBIG5_CHARSET);
      //m_iaCharSet.add(GB2312_CHARSET);
      //m_iaCharSet.add(SHIFTJIS_CHARSET);
      //m_iaCharSet.add(SYMBOL_CHARSET);
      ////m_iaCharSet.add(OEM_CHARSET);
      ////m_iaCharSet.add(DEFAULT_CHARSET);
      //m_iaCharSet.add(HEBREW_CHARSET);
      //m_iaCharSet.add(ARABIC_CHARSET);
      //m_iaCharSet.add(GREEK_CHARSET);
      //m_iaCharSet.add(TURKISH_CHARSET);
      //m_iaCharSet.add(VIETNAMESE_CHARSET);
      //m_iaCharSet.add(THAI_CHARSET);
      //m_iaCharSet.add(EASTEUROPE_CHARSET);
      //m_iaCharSet.add(RUSSIAN_CHARSET);
      //m_iaCharSet.add(JOHAB_CHARSET);
      //m_iaCharSet.add(HANGUL_CHARSET);
      //m_iaCharSet.add(BALTIC_CHARSET);
      ////m_iaCharSet.add(MAC_CHARSET);

      m_hdc = nullptr;

   }


   font_enumeration::~font_enumeration()
   {

   }


   ::e_status font_enumeration::on_enumerate_fonts()
   {

      if (m_hdc == nullptr)
      {

         m_hdc = ::CreateCompatibleDC(nullptr);

      }

      if (!m_hdc)
      {

         return error_failed;

      }

      auto estatus = __defer_construct_new(m_pitema);

      if (!estatus)
      {

         return estatus;

      }

      class font_enumeration* pfontenumeration = this;

      ::EnumFontFamiliesW(m_hdc, (const widechar *)nullptr, &font_enumeration::OLDFONTENUMPROCW, (LPARAM)pfontenumeration);

      for (auto & pitem : m_pitema->ptra())
      {

         enumerate_character_set(pitem);

      }

      ::DeleteDC(m_hdc);

      m_hdc = nullptr;

      return estatus;

   }


   int CALLBACK font_enumeration::OLDFONTENUMPROCW(CONST LOGFONTW* plogfont, CONST TEXTMETRICW* ptextmetric, DWORD dwFontType, LPARAM lparam)
   {

      auto pfontenumeration = (font_enumeration *)lparam;

      if (wcslen(plogfont->lfFaceName) > 1 && plogfont->lfFaceName[0] == '@')
      {

      }
      else if (dwFontType & RASTER_FONTTYPE)
      {

         if (pfontenumeration->m_bRaster)
         {

            auto pszFaceName = plogfont->lfFaceName;

            auto pfontenumerationitem = __new(::write_text::font_enumeration_item(pszFaceName));

            pfontenumeration->m_pitema->add(pfontenumerationitem);

         }

      }
      else if (dwFontType & TRUETYPE_FONTTYPE)
      {

         if (pfontenumeration->m_bTrueType)
         {

            auto pszFaceName = plogfont->lfFaceName;

            auto pfontenumerationitem = __new(::write_text::font_enumeration_item(pszFaceName));

            pfontenumeration->m_pitema->add(pfontenumerationitem);

         }

      }
      else
      {

         if (pfontenumeration->m_bOther)
         {

            auto pszFaceName = plogfont->lfFaceName;

            auto pfontenumerationitem = __new(::write_text::font_enumeration_item(pszFaceName));

            pfontenumeration->m_pitema->add(pfontenumerationitem);

         }

      }

      return TRUE;

   }


   void font_enumeration::enumerate_character_set(::write_text::font_enumeration_item* pitem)
   {

      ::EnumFontFamiliesW(m_hdc, pitem->m_wstrName, &font_enumeration::OLDFONTENUMPROCW_character_set, (LPARAM)pitem);

   }


   int CALLBACK font_enumeration::OLDFONTENUMPROCW_character_set(CONST LOGFONTW* plogfont, CONST TEXTMETRICW* ptextmetric, DWORD dwFontType, LPARAM lparam)
   {

      auto pfontenumerationitem = (::write_text::font_enumeration_item *)lparam;

      int iCharacterSet = plogfont->lfCharSet;

      ::enum_character_set echaracterset = ::write_text_win32_gdi::get_character_set(iCharacterSet);

      if (echaracterset != ::e_character_set_ansi && echaracterset != ::e_character_set_default)
      {

         pfontenumerationitem->m_echaracterseta.add(echaracterset);

      }

      return TRUE;

   }





} // namespace windowing_win32



