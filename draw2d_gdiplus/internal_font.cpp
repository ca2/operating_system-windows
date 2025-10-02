// Create by camilo on 2024-12-30 20:00 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "font.h"
#include "internal_font.h"


namespace draw2d_gdiplus
{


   internal_font::internal_font()
   {


   }


   internal_font::~internal_font()
   {



   }


   void internal_font::load_from_memory(::memory_base * pmemory)
   {

      if (pmemory->is_empty())
      {

         throw ::exception(error_wrong_state);

      }

      m_pcollection = øraw_new Gdiplus::PrivateFontCollection();

      m_pcollection->AddMemoryFont(pmemory->data(), (INT)pmemory->size());

      auto & fontCollection = *m_pcollection;

      auto iFamilyCount = fontCollection.GetFamilyCount();

      m_familya.set_size(iFamilyCount);

      fontCollection.GetFamilies(iFamilyCount, m_familya.data(), &m_iFamilyCount);

      m_familya.set_size(iFamilyCount);

      for (int iFamily = 0; iFamily < iFamilyCount; iFamily++)
      {

         if (m_familya[iFamily].GetLastStatus() != Gdiplus::Ok)
         {

            warningf("font family nok");

         }

      }

   }


   void internal_font::on_create_font(::draw2d::graphics * pgraphics, ::write_text::font * pfont)
   {

      if (m_iFamilyCount <= 0)
      {

         throw exception(error_resource);

      }

      ::cast < ::draw2d_gdiplus::font> pdraw2dgdiplusfont = pfont;

      int iFoundFamily = -1;

      WCHAR wszGetFamilyName[LF_FACESIZE];

      auto & pgdiplusfontfamily = pdraw2dgdiplusfont->m_pgdiplusfontfamily;

      if (pdraw2dgdiplusfont->::write_text::font::m_pfontfamily->m_strFamilyName.has_character())
      {

         for (int iFamily = 0; iFamily < m_iFamilyCount; iFamily++)
         {

            auto & fontfamily = m_familya[iFamily];

            if (fontfamily.GetFamilyName(wszGetFamilyName) == Gdiplus::Ok)
            {

               string strFontFamily = wszGetFamilyName;

               if (strFontFamily.case_insensitive_order(pdraw2dgdiplusfont->::write_text::font::m_pfontfamily->m_strFamilyName) == 0)
               {

                  pgdiplusfontfamily = fontfamily.Clone();

                  break;

               }

            }

         }

      }

      if (::is_null(pgdiplusfontfamily))
      {

         pgdiplusfontfamily = m_familya.first().Clone();

      }

      if (::is_null(pgdiplusfontfamily))
      {

         throw exception(error_resource);

      }

         //pfontfamily = &pprivatefont->m_familya[iFoundFamily];

         ////if (pfontfamily->GetFamilyName(wszGetFamilyName) != Gdiplus::Ok)
         ////{

         ////   throw exception(error_resource);

         ////}

         ////auto pfont = ___new Gdiplus::Font(
         ////   wszGetFamilyName,
         ////   (Gdiplus::REAL)m_dFontSize,
         ////   iStyle,
         ////   unit,
         ////   pprivatefont->m_pcollection);

         //pfontfamily

         //set_gdiplus_font(pfont);

         //bFont = true;

         auto pgdiplusfont = øraw_new Gdiplus::Font(
            pgdiplusfontfamily,
            gdiplus_font_size(pdraw2dgdiplusfont->m_fontsize),
            pdraw2dgdiplusfont->m_iStyle,
            gdiplus_font_unit(pdraw2dgdiplusfont->m_fontsize));

         pdraw2dgdiplusfont->set_gdiplus_font(pgdiplusfont);

      //}
      //else
      //{

      //   auto pfont = ___new Gdiplus::Font(
      //      &pprivatefont->m_familya.first(),
      //      (Gdiplus::REAL)m_dFontSize,
      //      iStyle,
      //      unit);

      //   set_gdiplus_font(pfont);

      //   bFont = true;

      //}

   }



} // namespace draw2d_gdiplus



