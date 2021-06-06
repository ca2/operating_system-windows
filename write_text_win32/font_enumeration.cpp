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

      ::EnumFontFamiliesW(m_hdc, (const widechar *)nullptr, (FONTENUMPROCW)&font_enumeration::callback, (lparam)this);

      for (auto & pitem : m_pitema->ptra())
      {

         enumerate_character_set(pitem);

      }

      ::DeleteDC(m_hdc);

      m_hdc = nullptr;

      return ::success;

   }


   BOOL CALLBACK font_enumeration::callback(LPLOGFONTW plf, LPNEWTEXTMETRICW lpntm, ::u32 dwFontType, LPVOID p)
   {

      font_enumeration * penumeration = (font_enumeration *)p;

      if (wcslen(plf->lfFaceName) > 1 && plf->lfFaceName[0] == '@')
      {

      }
      else if (dwFontType & RASTER_FONTTYPE)
      {

         if (penumeration->m_bRaster)
         {

            penumeration->m_pitema->add(__new(::write_text::font_enumeration_item(plf->lfFaceName)));

         }

      }
      else if (dwFontType & TRUETYPE_FONTTYPE)
      {

         if (penumeration->m_bTrueType)
         {

            penumeration->m_pitema->add(__new(::write_text::font_enumeration_item(plf->lfFaceName)));

         }

      }
      else
      {

         if (penumeration->m_bOther)
         {

            penumeration->m_pitema->add(__new(::write_text::font_enumeration_item(plf->lfFaceName)));

         }

      }

      return true;

   }


   void font_enumeration::enumerate_character_set(::write_text::font_enumeration_item* pitem)
   {

      ::EnumFontFamiliesW(m_hdc, pitem->m_wstrName, (FONTENUMPROCW)&font_enumeration::callback_character_set, (lparam)pitem);

   }


   BOOL CALLBACK font_enumeration::callback_character_set(LPLOGFONTW plf, LPNEWTEXTMETRICW lpntm, ::u32 dwFontType, LPVOID p)
   {

      ::write_text::font_enumeration_item * pitem = (::write_text::font_enumeration_item *)p;

      ::enum_character_set echarset = ::write_text_win32_gdi::get_character_set(plf->lfCharSet);

      if (echarset != ::e_character_set_ansi && echarset != ::e_character_set_default)
      {

         pitem->m_echaracterseta.add(echarset);

      }

      return true;


   }





} // namespace windowing_win32



