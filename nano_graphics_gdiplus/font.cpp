//
// Created by camilo on 31/01/2022 16:06 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "font.h"
#include "context.h"
#include "acme/platform/node.h"
// #include "_nano.h"


namespace nano_graphics_gdiplus
{

   font::font() {  }


   font::~font() {}


   void font::create_point_font(enum_font efont, ::f64 fPointSize, bool bBold, bool bUnderline)
   {

      //auto strFontFamily = node()->font_name(efont);

      //::wstring wstrFontFamily(strFontFamily);

      //m_pfontfamily = new ::Gdiplus::FontFamily(wstrFontFamily);

      //m_pfont = font(&ff, 12.f, FontStyleRegular, UnitPixel);

      _create_font(efont, fPointSize, true, bBold, bUnderline);
   }


   void font::create_pixel_font(enum_font efont, ::f64 fPixelSize, bool bBold, bool bUnderline)
   {

      /*auto strFontFamily = node()->font_name(efont);

      ::wstring wstrFontFamily(strFontFamily);

      m_pfontfamily = new ::Gdiplus::FontFamily(wstrFontFamily);

      m_pfont = font(&ff, 12.f, FontStyleRegular, UnitPixel);*/

      _create_font(efont, fPixelSize, false, bBold, bUnderline);
   }


   void font::_create_font(enum_font efont, ::f64 fSize, bool bPointSize, bool bBold, bool bUnderline)
   {

      auto strFontFamily = node()->font_name(efont);

      ::wstring wstrFontFamily(strFontFamily);

      m_pfontfamily = new ::Gdiplus::FontFamily(wstrFontFamily);

      m_pfont = new ::Gdiplus::Font(m_pfontfamily, fSize, 
         (bBold ? Gdiplus::FontStyleBold : Gdiplus::FontStyleRegular) | 
         (bUnderline  ? Gdiplus::FontStyleUnderline | Gdiplus::FontStyleRegular),
                     bPointSize ? Gdiplus::UnitPoint : Gdiplus::UnitPixel);
   }


   //void font::update(::nano::graphics::context *pnanodevice)
   //{

   //   if (m_bModified)
   //   {

   //      destroy();

   //      LOGFONTW logfontw = {};

   //      auto pgraphicscontextGdiplus = dynamic_cast<::nano_graphics_gdiplus::context *>(pnanodevice);

   //      m_hgdiobj = _create_point_font(m_iFontSize * 10, m_strFontName, m_bBold, m_bUnderline,
   //                                     pgraphicscontextGdiplus->m_hdc, &logfontw);

   //      m_bModified = false;

   //   }

   //}


   //HFONT font::_create_point_font(::i32 nPointSize, const ::scoped_string &scopedstrFaceName, bool bBold, bool bUnderline,
   //                               HDC hdc, LOGFONTW *plf)
   //{

   //   LOGFONTW lF;

   //   if (plf == nullptr)
   //   {

   //      plf = &lF;

   //      ::memory_set(plf, 0, sizeof(*plf));

   //      plf->lfCharSet = DEFAULT_CHARSET;
   //   }

   //   plf->lfHeight = nPointSize;

   //   plf->lfWeight = bBold ? FW_BOLD : FW_NORMAL;

   //   plf->lfUnderline = bUnderline ? TRUE : FALSE;

   //   wstring wstr(scopedstrFaceName);

   //   wstr = wstr.substr(0, sizeof(plf->lfFaceName));

   //   wcsncpy(plf->lfFaceName, wstr, sizeof(plf->lfFaceName) / sizeof(wchar_t));

   //   return _create_point_font_indirect(plf, hdc);
   //}


   //// pLogFont->nHeight is interpreted as PointSize * 10
   //HFONT font::_create_point_font_indirect(LOGFONTW *pLogFont, HDC hdc)
   //{

   //   LOGFONTW &logFont = *pLogFont;


   //   ::i32_point point;
   //   // 72 points/inch, 10 decipoints/i32_point
   //   point.y = ::MulDiv(::GetDeviceCaps(hdc, LOGPIXELSY), logFont.lfHeight, 720);
   //   point.x = 0;
   //   ::DPtoLP(hdc, (POINT *)&point, 1);
   //   ::i32_point pointOrg = {0, 0};
   //   ::DPtoLP(hdc, (POINT *)&pointOrg, 1);
   //   logFont.lfHeight = -abs(point.y - pointOrg.y);

   //   logFont.lfQuality = CLEARTYPE_NATURAL_QUALITY;

   //   HFONT hfont = ::CreateFontIndirectW(&logFont);

   //   if (::GetObjectW(hfont, sizeof(logFont), pLogFont))
   //   {

   //      ::informationf("got log font");
   //   }

   //   return hfont;
   //}


} // namespace nano_graphics_gdiplus
