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

         __pointer(::draw2d_gdiplus::draw2d) pdraw2d = m_psystem->m_paurasystem->draw2d();

         auto pprivatefont = pdraw2d->get_file_private_font(pgraphics->m_pcontext, m_path);

         if (pprivatefont)
         {

            if (pprivatefont->m_iFamilyCount <= 0)
            {

               throw exception(error_resource);

            }

            int iFound = 0;

            WCHAR wszGetFamilyName[LF_FACESIZE];

            if (m_strFontFamilyName.has_char())
            {

               for (int i = 0; i < pprivatefont->m_iFamilyCount; i++)
               {

                  auto & fontfamily = pprivatefont->m_pfamily.m_p[i];

                  if (fontfamily.GetFamilyName(wszGetFamilyName) == Gdiplus::Ok)
                  {

                     string strFontFamily = wszGetFamilyName;

                     if (strFontFamily.compare_ci(m_strFontFamilyName) == 0)
                     {

                        iFound = i;

                        break;


                     }

                  }

               }

            }

            auto & fontfamily = pprivatefont->m_pfamily.m_p[iFound];

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

      }
      
      if(!bFont)
      {

         auto pfont = new Gdiplus::Font(
            utf8_to_unicode(m_strFontFamilyName),
            (Gdiplus::REAL)m_dFontSize,
            iStyle,
            unit);

         set_gdiplus_font(pfont);

      }

      m_mapText.erase_all();

      //return true;

   }


   ::enum_character_set font::calculate_character_set(::draw2d::graphics * pgraphics)
   {

      return ::write_text::font::calculate_character_set(pgraphics);

   }


} // namespace draw2d_gdiplus



