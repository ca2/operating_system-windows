#include "framework.h"


#undef new


namespace draw2d_gdiplus
{


   font::font()
   {

      m_pthis = this;

   }


   font::~font()
   {
      
      destroy();

   }


#ifdef DEBUG


   void font::dump(dump_context & dumpcontext) const
   {

      ::draw2d::object::dump(dumpcontext);

   }


#endif

   
   ::e_status font::destroy()
   {

      auto pfont = get_gdiplus_font();

      if (pfont)
      {

         delete pfont;

         set_gdiplus_font(nullptr);

      }

      ::write_text::font::destroy();
      
      return ::success;

   }


   bool font::create(::draw2d::graphics * pgraphics, ::i8 iCreate)
   {

      i32 iStyle = 0;

      if(m_iFontWeight >= 600)
      {

         iStyle |= (i32) Gdiplus::FontStyleBold;

      }

      if(m_bItalic)
      {

         iStyle |= (i32) Gdiplus::FontStyleItalic;

      }

      if(m_bUnderline)
      {

         iStyle |= (i32) Gdiplus::FontStyleUnderline;

      }

      if(m_bStrikeout)
      {

         iStyle |= (i32) Gdiplus::FontStyleStrikeout;

      }

      Gdiplus::Unit unit;

      switch(m_eunitFontSize)
      {
      case ::draw2d::unit_pixel:

         unit = Gdiplus::UnitPixel;

         break;

      case ::draw2d::unit_point:

         unit = Gdiplus::UnitPoint;

         break;

      default:

         unit = Gdiplus::UnitPoint;

         break;

      };

      auto pfont = new Gdiplus::Font(
      ::str::international::utf8_to_unicode(m_strFontFamilyName),
      (Gdiplus::REAL) m_dFontSize,
      iStyle,
      unit);

      set_gdiplus_font(pfont);

      m_mapText.erase_all();

      return true;

   }


   ::enum_character_set font::calculate_character_set(::draw2d::graphics * pgraphics)
   {

      return ::write_text::font::calculate_character_set(pgraphics);

   }


} // namespace draw2d_gdiplus



