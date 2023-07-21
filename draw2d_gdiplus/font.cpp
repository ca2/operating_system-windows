#include "framework.h"
#include "font.h"
#include "draw2d.h"
#include "acme/exception/exception.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/primitive/string/international.h"
#include "aura/graphics/write_text/fonts.h"


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


//#ifdef DEBUG
//
//
//   void font::dump(dump_context & dumpcontext) const
//   {
//
//      ::draw2d::object::dump(dumpcontext);
//
//   }
//
//
//#endif


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

      if (m_fontweight > e_font_weight_semibold)
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

      auto unit = gdiplus_font_unit(m_fontsize);

      bool bFont = false;

      Gdiplus::FontFamily * pfontfamily = nullptr;

      //::string strFamilyName = m_pfontfamily->family_name(this);

      //if (m_path.is_empty())
      //{

      //   ::string strFontBranch;

      //   if (strFamilyName.begins_eat("font_foundry:"))
      //   {

      //      auto pFind = strFamilyName.find_first("://");

      //      if (pFind)
      //      {

      //         strFontBranch = strFamilyName(0, pFind);

      //         strFamilyName = pFind + 3;

      //         auto penumeration = acmesystem()->m_paurasystem->draw2d()->write_text()->fonts()->enumeration(strFontBranch);

      //         if (penumeration)
      //         {

      //            //m_path = penumeration->m_pfontenumerationitema->predicate_find_first([](auto pitem)

      //         }

      //      }

      //   }

      //}

      if (m_path.has_char())
      {

         ::pointer<::draw2d_gdiplus::draw2d>pdraw2d = acmesystem()->m_paurasystem->draw2d();

         if (m_pfontfamily && m_pfontfamily->m_strBranch.has_char())
         {

            pdraw2d->write_text()->fonts()->enumeration(m_pfontfamily->m_strBranch)->defer_download_font(m_path);

         }

         auto pprivatefont = pdraw2d->get_file_private_font(pgraphics->m_pcontext, m_path);

         if (pprivatefont)
         {

            if (pprivatefont->m_iFamilyCount <= 0)
            {

               throw exception(error_resource);

            }
            else
            {

               int iFoundFamily = -1;

               WCHAR wszGetFamilyName[LF_FACESIZE];

               if (::write_text::font::m_pfontfamily->m_strFamilyName.has_char())
               {

                  for (int iFamily = 0; iFamily < pprivatefont->m_iFamilyCount; iFamily++)
                  {

                     auto & fontfamily = pprivatefont->m_familya[iFamily];

                     if (fontfamily.GetFamilyName(wszGetFamilyName) == Gdiplus::Ok)
                     {

                        string strFontFamily = wszGetFamilyName;

                        if (strFontFamily.case_insensitive_order(::write_text::font::m_pfontfamily->m_strFamilyName) == 0)
                        {

                           pfontfamily = &fontfamily;

                           break;

                        }

                     }

                  }

               }

               if (::is_null(pfontfamily))
               {

                  pfontfamily = &pprivatefont->m_familya.first();

               }

               if (::is_set(pfontfamily))
               {

                  //pfontfamily = &pprivatefont->m_familya[iFoundFamily];

                  ////if (pfontfamily->GetFamilyName(wszGetFamilyName) != Gdiplus::Ok)
                  ////{

                  ////   throw exception(error_resource);

                  ////}

                  ////auto pfont = new Gdiplus::Font(
                  ////   wszGetFamilyName,
                  ////   (Gdiplus::REAL)m_dFontSize,
                  ////   iStyle,
                  ////   unit,
                  ////   pprivatefont->m_pcollection);

                  //pfontfamily

                  //set_gdiplus_font(pfont);

                  //bFont = true;

                  auto pfont = new Gdiplus::Font(
                     pfontfamily,
                     gdiplus_font_size(m_fontsize),
                     iStyle,
                     gdiplus_font_unit(m_fontsize));

                  set_gdiplus_font(pfont);

                  bFont = true;

               }
               //else
               //{

               //   auto pfont = new Gdiplus::Font(
               //      &pprivatefont->m_familya.first(),
               //      (Gdiplus::REAL)m_dFontSize,
               //      iStyle,
               //      unit);

               //   set_gdiplus_font(pfont);

               //   bFont = true;

               //}

            }

         }

      }

      if (!bFont)
      {

         ::string strFamilyName = m_pfontfamily->family_name(this);

         if (strFamilyName.case_insensitive_equals("Segoe UI"))
         {

            auto efontweight = m_fontweight.sink(m_fontweight.i32());

            if (efontweight == e_font_weight_thin)
            {

               strFamilyName += " Light";

            }
            else if (efontweight == e_font_weight_extra_light)
            {

               strFamilyName += " Light";

            }
            else if (efontweight == e_font_weight_light)
            {

               strFamilyName += " Semilight";

            }
            else if (efontweight == e_font_weight_semi_light)
            {

               strFamilyName += " Semilight";

            }
            else if (efontweight > e_font_weight_normal)
            {

               strFamilyName += " Black";

            }

         }

         auto pfont = new Gdiplus::Font(
            utf8_to_unicode(strFamilyName),
            gdiplus_font_size(m_fontsize),
            iStyle,
            gdiplus_font_unit(m_fontsize));

         set_gdiplus_font(pfont);

      }

      auto pfont = get_gdiplus_font();

      if (pfont)
      {

         Gdiplus::FontFamily fontfamily;

         if (::is_null(pfontfamily))
         {

            if (pfont->GetFamily(&fontfamily) == Gdiplus::Ok)
            {

               pfontfamily = &fontfamily;

            }

         }

         if(::is_set(pfontfamily))
         {

            INT iStyle = pfont->GetStyle();

            double dHeight = pfontfamily->GetEmHeight(iStyle);

            double dSize = pfont->GetSize();

            double dFontHeight = pfont->GetHeight((Gdiplus::REAL)pgraphics->get_dpiy());

            auto & textmetric = m_textmetric2;

            textmetric.m_dAscent = dSize * pfontfamily->GetCellAscent(iStyle) / dHeight;
            textmetric.m_dDescent = dSize * pfontfamily->GetCellDescent(iStyle) / dHeight;
            textmetric.m_dInternalLeading = 0.;
            textmetric.m_dExternalLeading = dSize * pfontfamily->GetLineSpacing(iStyle) / dHeight -
               (textmetric.m_dAscent + textmetric.m_dDescent);

         }

      }

      synchronous_lock synchronouslock(acmesystem()->m_paurasystem->draw2d()->write_text()->m_pparticleFontTextMapSynchronization);

      m_mapFontText.erase_all();

   }


   ::enum_character_set font::calculate_character_set(::draw2d::graphics * pgraphics)
   {

      return ::write_text::font::calculate_character_set(pgraphics);

   }


} // namespace draw2d_gdiplus



