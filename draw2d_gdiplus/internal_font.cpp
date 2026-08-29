// Create by camilo on 2024-12-30 20:00 <3ThomasBorregaardSorensen!!
#include "platform.h"
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

      if (m_pgdiplusprivatefontcollection)
      {

         m_pgdiplusprivatefontcollection.destroy();

      }

      m_pgdiplusprivatefontcollection = ::as_pointer(new Gdiplus::PrivateFontCollection());

      m_pgdiplusprivatefontcollection->AddMemoryFont(pmemory->data(), (INT)pmemory->size());

      auto & fontCollection = *m_pgdiplusprivatefontcollection;

      auto iFamilyCount = fontCollection.GetFamilyCount();

      m_gdiplusfamilya.set_size(iFamilyCount);

      fontCollection.GetFamilies(iFamilyCount, m_gdiplusfamilya.data(), &m_iFamilyCount);

      m_gdiplusfamilya.set_size(iFamilyCount);

      for (::i32 iFamily = 0; iFamily < iFamilyCount; iFamily++)
      {

         if (m_gdiplusfamilya[iFamily].GetLastStatus() != Gdiplus::Ok)
         {

            warningf("font family nok");

         }

      }

   }


   void internal_font::on_create_font(::draw2d::graphics * pdraw2dgraphics, ::write_text::font * pwritetextfont)
   {

      if (m_iFamilyCount <= 0)
      {

         throw exception(error_resource);

      }

      ::cast < ::draw2d_gdiplus::font> pdraw2dgdiplusfont = pwritetextfont;

      ::i32 iFoundFamily = -1;

      WCHAR wszGetFamilyName[LF_FACESIZE];

      auto & pgdiplusfontfamily = pdraw2dgdiplusfont->m_pgdiplusfontfamily;

      if (pdraw2dgdiplusfont->::write_text::font::m_pfontfamily->m_strFamilyName.has_character())
      {

         for (::i32 iFamily = 0; iFamily < m_iFamilyCount; iFamily++)
         {

            auto & fontfamily = m_gdiplusfamilya[iFamily];

            if (fontfamily.GetFamilyName(wszGetFamilyName) == Gdiplus::Ok)
            {

               string strFontFamily = wszGetFamilyName;

               if (strFontFamily.case_insensitive_order(pdraw2dgdiplusfont->::write_text::font::m_pfontfamily->m_strFamilyName) == 0)
               {

                  pgdiplusfontfamily = ::as_pointer(fontfamily.Clone());

                  break;

               }

            }

         }

      }

      if (!pgdiplusfontfamily)
      {

         pgdiplusfontfamily = ::as_pointer(m_gdiplusfamilya.first().Clone());

      }

      if (!pgdiplusfontfamily)
      {

         throw exception(error_resource);

      }

         //pfontfamily = &pprivatefont->m_familya[iFoundFamily];

         ////if (pfontfamily->GetFamilyName(wszGetFamilyName) != Gdiplus::Ok)
         ////{

         ////   throw exception(error_resource);

         ////}

         ////auto pwritetextfont = ___new Gdiplus::Font(
         ////   wszGetFamilyName,
         ////   (Gdiplus::REAL)m_dFontSize,
         ////   iStyle,
         ////   unit,
         ////   pprivatefont->m_pcollection);

         //pfontfamily

         //set_gdiplus_font(pwritetextfont);

         //bFont = true;

         auto pgdiplusfont = new Gdiplus::Font(
            pgdiplusfontfamily,
            gdiplus_font_size(pdraw2dgdiplusfont->m_fontsize),
            pdraw2dgdiplusfont->m_iStyle,
            gdiplus_font_unit(pdraw2dgdiplusfont->m_fontsize));

         pdraw2dgdiplusfont->m_pgdiplusfont = ::as_pointer(pgdiplusfont);

      //}
      //else
      //{

      //   auto pwritetextfont = ___new Gdiplus::Font(
      //      &pprivatefont->m_familya.first(),
      //      (Gdiplus::REAL)m_dFontSize,
      //      iStyle,
      //      unit);

      //   set_gdiplus_font(pwritetextfont);

      //   bFont = true;

      //}

   }



} // namespace draw2d_gdiplus



