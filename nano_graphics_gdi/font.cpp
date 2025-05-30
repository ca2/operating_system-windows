//
// Created by camilo on 31/01/2022 16:06 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "font.h"
#include "device.h"
//#include "_nano.h"


namespace windows
{



   namespace nano
   {


      namespace graphics
      {

         font::font()
         {

            m_pthis = this;

         }


         font::~font()
         {

         }


         void font::update(::nano::graphics::device* pnanodevice)
         {

            if (m_bModified)
            {

               destroy();

               LOGFONTW logfontw = {};

               auto pwindowsnanodevice = dynamic_cast <::windows::nano::graphics::device*>(pnanodevice);

               m_hgdiobj = _create_point_font(m_iFontSize * 10, m_strFontName, m_bBold, pwindowsnanodevice->m_hdc, &logfontw);

               m_bModified = false;

            }


         }


         HFONT font::_create_point_font(int nPointSize, const ::scoped_string& scopedstrFaceName, bool bBold, HDC hdc, LOGFONTW* plf)
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

            wstring wstr(scopedstrFaceName);

            wstr = wstr.substr(0, sizeof(plf->lfFaceName));

            wcsncpy(plf->lfFaceName, wstr, sizeof(plf->lfFaceName) / sizeof(wchar_t));

            return _create_point_font_indirect(plf, hdc);

         }


         // pLogFont->nHeight is interpreted as PointSize * 10
         HFONT font::_create_point_font_indirect(LOGFONTW* pLogFont, HDC hdc)
         {

            LOGFONTW& logFont = *pLogFont;


            ::int_point point;
            // 72 points/inch, 10 decipoints/int_point
            point.y() = ::MulDiv(::GetDeviceCaps(hdc, LOGPIXELSY), logFont.lfHeight, 720);
            point.x() = 0;
            ::DPtoLP(hdc, (POINT*)&point, 1);
            ::int_point pointOrg = { 0, 0 };
            ::DPtoLP(hdc, (POINT*)&pointOrg, 1);
            logFont.lfHeight = -abs(point.y() - pointOrg.y());

            logFont.lfQuality = CLEARTYPE_NATURAL_QUALITY;

            HFONT hfont = ::CreateFontIndirectW(&logFont);

            if (::GetObjectW(hfont, sizeof(logFont), pLogFont))
            {

               ::informationf("got log font");

            }

            return hfont;

         }



      } // namespace graphics


   } // namespace nano


} // namespace windows



