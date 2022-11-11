#include "framework.h"
#include "font.h"
#include "draw2d.h"
#include "acme/exception/exception.h"
#include "acme/primitive/string/international.h"


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


   void font::destroy()
   {

      auto pfont = get_gdiplus_font();

      if (pfont)
      {

         delete pfont;

         set_gdiplus_font(nullptr);

      }

      ::write_text::font::destroy();

      //return ::success;

   }


   void font::create(::draw2d::graphics * pgraphics, ::i8 iCreate)
   {

      i32 iStyle = 0;

      if (m_iFontWeight >= 600)
      {

         iStyle |= (i32)Gdiplus::FontStyleBold;

      }

      if (m_bItalic)
      {

         iStyle |= (i32)Gdiplus::FontStyleItalic;

      }

      if (m_bUnderline)
      {

         iStyle |= (i32)Gdiplus::FontStyleUnderline;

      }

      if (m_bStrikeout)
      {

         iStyle |= (i32)Gdiplus::FontStyleStrikeout;

      }

      Gdiplus::Unit unit;

      switch (m_eunitFontSize)
      {
      case ::draw2d::e_unit_pixel:

         unit = Gdiplus::UnitPixel;

         break;

      case ::draw2d::e_unit_point:

         unit = Gdiplus::UnitPoint;

         break;

      default:

         unit = Gdiplus::UnitPoint;

         break;

      };

      bool bFont = false;

      if (m_path.has_char())
      {

         ::pointer<::draw2d_gdiplus::draw2d>pdraw2d = acmesystem()->m_paurasystem->draw2d();

         auto pprivatefont = pdraw2d->get_file_private_font(pgraphics->m_pcontext, m_path);

         if (pprivatefont)
         {

            if (pprivatefont->m_iFamilyCount <= 0)
            {

               throw exception(error_resource);

            }
            else if (pprivatefont->m_iFamilyCount == 1)
            {

               auto pfont = new Gdiplus::Font(
                  &pprivatefont->m_familya.first(),
                  (Gdiplus::REAL)m_dFontSize,
                  iStyle,
                  unit);

               set_gdiplus_font(pfont);

               bFont = true;

            }
            else
            {

               int iFoundFamily = -1;

               WCHAR wszGetFamilyName[LF_FACESIZE];

               if (m_strFontFamilyName.has_char())
               {

                  for (int iFamily = 0; iFamily < pprivatefont->m_iFamilyCount; iFamily++)
                  {

                     auto & fontfamily = pprivatefont->m_familya[iFamily];

                     if (fontfamily.GetFamilyName(wszGetFamilyName) == Gdiplus::Ok)
                     {

                        string strFontFamily = wszGetFamilyName;

                        if (strFontFamily.compare_ci(m_strFontFamilyName) == 0)
                        {

                           iFoundFamily = iFamily;

                           break;

                        }

                     }

                  }

               }

               if (iFoundFamily >= 0)
               {

                  auto & fontfamily = pprivatefont->m_familya[iFoundFamily];

                  if (fontfamily.GetFamilyName(wszGetFamilyName) != Gdiplus::Ok)
                  {

                     throw exception(error_resource);

                  }

                  auto pfont = new Gdiplus::Font(
                     wszGetFamilyName,
                     (Gdiplus::REAL)m_dFontSize,
                     iStyle,
                     unit,
                     pprivatefont->m_pcollection);

                  set_gdiplus_font(pfont);

                  bFont = true;

               }
               else
               {

                  auto pfont = new Gdiplus::Font(
                     &pprivatefont->m_familya.first(),
                     (Gdiplus::REAL)m_dFontSize,
                     iStyle,
                     unit);

                  set_gdiplus_font(pfont);

                  bFont = true;

               }

            }

         }

      }

      if (!bFont)
      {

         auto pfont = new Gdiplus::Font(
            utf8_to_unicode(m_strFontFamilyName),
            (Gdiplus::REAL)m_dFontSize,
            iStyle,
            unit);

         set_gdiplus_font(pfont);

      }

      auto pfont = get_gdiplus_font();

      if (pfont)
      {

         Gdiplus::FontFamily fontfamily;

         if (pfont->GetFamily(&fontfamily) == Gdiplus::Ok)
         {

            INT iStyle = pfont->GetStyle();

            double dHeight = fontfamily.GetEmHeight(iStyle);

            double dSize = pfont->GetSize();

            double dFontHeight = pfont->GetHeight((Gdiplus::REAL)pgraphics->get_dpiy());

            auto & textmetric = m_textmetric2;

            textmetric.m_dAscent = dSize * fontfamily.GetCellAscent(iStyle) / dHeight;
            textmetric.m_dDescent = dSize * fontfamily.GetCellDescent(iStyle) / dHeight;
            textmetric.m_dInternalLeading = 0.;
            textmetric.m_dExternalLeading = dSize * fontfamily.GetLineSpacing(iStyle) / dHeight -
               (textmetric.m_dAscent + textmetric.m_dDescent);

         }

      }




      m_mapText.erase_all();

      //return true;

   }


   ::enum_character_set font::calculate_character_set(::draw2d::graphics * pgraphics)
   {

      return ::write_text::font::calculate_character_set(pgraphics);

   }


} // namespace draw2d_gdiplus



