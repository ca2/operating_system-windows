//
// Created by camilo on 31/01/2022 16:06 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "font.h"
#include "acme/nano/graphics/font_family.h"
#include "context.h"
//#include "_nano.h"


      namespace nano_graphics_gdi
      {

         font::font()
         {

            //m_pthis = this;

         }


         font::~font()
         {

         }

         
         void font::create_point_font(::nano::graphics::font_family * pfontfamily, ::f64 fPointSize, bool bBold,
                                        bool bItalic, bool bUnderline)
         {

            m_pfontfamily = pfontfamily;

            LOGFONTW logfontw = {};

            m_fFontSize = fPointSize;

            m_bPixelSize = false;

            m_bBold = bBold;

            m_bUnderline = bUnderline;

            m_bItalic = bItalic;

            ::string strFontName = m_pfontfamily->get_font_family_name();

            HDC hdc = ::GetDC(nullptr);

            m_hgdiobj = _create_point_font(m_fFontSize * 10, strFontName, m_bBold, m_bUnderline, hdc, &logfontw);

            ::ReleaseDC(nullptr, hdc);

         }

         
         void font::create_pixel_font(::nano::graphics::font_family *pfontfamily, ::f64 fPixelSize,
                                              bool bBold,
                                        bool bItalic, bool bUnderline)
         {

            m_pfontfamily = pfontfamily;

            LOGFONTW logfontw = {};

            m_fFontSize = fPixelSize;

            m_bPixelSize = true;

            m_bBold = bBold;

            m_bUnderline = bUnderline;

            m_bItalic = bItalic;

            ::string strFontName = m_pfontfamily->get_font_family_name();

            //auto pgdicontext = dynamic_cast<::nano_graphics_gdi::context *>(pgraphicscontext);

            HDC hdc = ::GetDC(nullptr);

            m_hgdiobj = _create_point_font(m_fFontSize * 10, strFontName, m_bBold, m_bUnderline, hdc,
                                           &logfontw);

            ::ReleaseDC(nullptr, hdc);

            //m_bModified = false;


         }



         //void font::update(::nano::graphics::context* pgraphicscontext)
         //{

         //   if (m_bModified)
         //   {

         //      destroy();

         //      LOGFONTW logfontw = {};

         //      auto pgdicontext = dynamic_cast <::nano_graphics_gdi::context*>(pgraphicscontext);

         //      m_hgdiobj = _create_point_font(m_iFontSize * 10, m_strFontName, m_bBold, m_bUnderline, pgdicontext->m_hdc, &logfontw);

         //      m_bModified = false;

         //   }


         //}


         HFONT font::_create_point_font(::i32 nPointSize, const ::scoped_string& scopedstrFaceName, bool bBold, bool bUnderline, HDC hdc, LOGFONTW* plf)
         {

            LOGFONTW lF;

            if (plf == nullptr)
            {

               plf = &lF;

               ::memory_set(plf, 0, sizeof(*plf));

               plf->lfCharSet = DEFAULT_CHARSET;

            }

            plf->lfHeight = nPointSize;

            plf->lfWeight = bBold ? FW_BOLD : FW_NORMAL;

            plf->lfUnderline = bUnderline ? TRUE : FALSE;

            wstring wstr(scopedstrFaceName);

            wstr = wstr.substr(0, sizeof(plf->lfFaceName));

            wcsncpy(plf->lfFaceName, wstr, sizeof(plf->lfFaceName) / sizeof(wchar_t));

            return _create_point_font_indirect(plf, hdc);

         }


         // pLogFont->nHeight is interpreted as PointSize * 10
         HFONT font::_create_point_font_indirect(LOGFONTW* pLogFont, HDC hdc)
         {

            LOGFONTW& logFont = *pLogFont;


            ::i32_point point;
            // 72 points/inch, 10 decipoints/i32_point
            point.y = ::MulDiv(::GetDeviceCaps(hdc, LOGPIXELSY), logFont.lfHeight, 720);
            point.x = 0;
            ::DPtoLP(hdc, (POINT*)&point, 1);
            ::i32_point pointOrg = { 0, 0 };
            ::DPtoLP(hdc, (POINT*)&pointOrg, 1);
            logFont.lfHeight = -abs(point.y - pointOrg.y);

            logFont.lfQuality = CLEARTYPE_NATURAL_QUALITY;

            HFONT hfont = ::CreateFontIndirectW(&logFont);

            if (::GetObjectW(hfont, sizeof(logFont), pLogFont))
            {

               ::informationf("got log font");

            }

            return hfont;

         }



      } // namespace nano_graphics_gdi

