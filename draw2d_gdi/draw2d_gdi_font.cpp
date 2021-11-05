#include "framework.h"


namespace draw2d_gdi
{


   font::font(::object * pobject) :
      ::write_text::font(pobject)
   {

   }


   font::~font()
   {

   }


   font::operator HFONT() const
   {

      return (HFONT)(this == nullptr ? nullptr : get_handle());

   }


   bool font::CreateFontIndirect(const LOGFONTW * lpLogFont)
   {

      return Attach(::CreateFontIndirectW(lpLogFont));

   }


   bool font::CreateFont(int nHeight, int nWidth, int nEscapement, int nOrientation, int nWeight, BYTE bItalic, BYTE bUnderline, BYTE cStrikeOut, BYTE nCharSet, BYTE nOutPrecision, BYTE nClipPrecision, BYTE nQuality, BYTE nPitchAndFamily, const ::string & lpszFacename)
   {

      return Attach(::CreateFontW(nHeight, nWidth, nEscapement, nOrientation, nWeight, bItalic, bUnderline, cStrikeOut, nCharSet, nOutPrecision, nClipPrecision, nQuality,  nPitchAndFamily, wstring(lpszFacename)));

   }


   bool font::GetLogFont(LOGFONTW * pLogFont)
   {

      return ::GetObjectW(get_handle(), sizeof(LOGFONTW), pLogFont);

   }


   void font::construct(const ::write_text::font & pfontParam)
   {

      class font & font = const_cast < ::draw2d_gdi::font & > (dynamic_cast < const ::draw2d_gdi::font & > (pfontParam));

      if(get_handle() != nullptr)
         destroy();

      if(font.get_handle() != nullptr)
      {
         LOGFONTW lf;
         __memset(&lf, 0, sizeof(lf));
         font.GetLogFont(&lf);
         CreateFontIndirect(&lf);
      }

   }


   void font::dump(dump_context & dumpcontext) const
   {
      ::draw2d::object::dump(dumpcontext);

      if (get_handle() == nullptr)
         return;

      /*         if (!afxData.bWin95 && ::GetObjectType(get_handle()) != OBJ_FONT)
      {
      // not a valid GDI object
      dumpcontext << "has ILLEGAL HFONT!";
      return;
      }*/

      LOGFONTW lf;
      VERIFY(get_object(sizeof(lf), &lf));
      dumpcontext << "lf.lfHeight = " << lf.lfHeight;
      dumpcontext << "\nlf.lfWidth = " << lf.lfWidth;
      dumpcontext << "\nlf.lfEscapement = " << lf.lfEscapement;
      dumpcontext << "\nlf.lfOrientation = " << lf.lfOrientation;
      dumpcontext << "\nlf.lfWeight = " << lf.lfWeight;
      dumpcontext << "\nlf.lfItalic = " << (int)lf.lfItalic;
      dumpcontext << "\nlf.lfUnderline = " << (int)lf.lfUnderline;
      dumpcontext << "\nlf.lfStrikeOut = " << (int)lf.lfStrikeOut;
      dumpcontext << "\nlf.lfCharSet = " << (int)lf.lfCharSet;
      dumpcontext << "\nlf.lfOutPrecision = " << (int)lf.lfOutPrecision;
      dumpcontext << "\nlf.lfClipPrecision = " << (int)lf.lfClipPrecision;
      dumpcontext << "\nlf.lfQuality = " << (int)lf.lfQuality;
      dumpcontext << "\nlf.lfPitchAndFamily = " << (int)lf.lfPitchAndFamily;
      dumpcontext << "\nlf.lfFaceName = " << (const ::string &)lf.lfFaceName;

      dumpcontext << "\n";
   }

   /////////////////////////////////////////////////////////////////////////////
   // out-of-line ::draw2d::brush, font, etc. helpers

   // nPointSize is actually scaled 10x
   bool font::CreatePointFont(int nPointSize, const ::string & lpszFaceName, ::draw2d::graphics_pointer & pgraphics)
   {

      LOGFONTW logFont;

      __zero(logFont);

      logFont.lfCharSet = DEFAULT_CHARSET;

      logFont.lfHeight = nPointSize;

      wstring wstr(lpszFaceName);

      wstr = wstr.substr(0, sizeof(logFont.lfFaceName));

      wcsncpy(logFont.lfFaceName, wstr, sizeof(logFont.lfFaceName) / sizeof(wchar_t));

      return CreatePointFontIndirect(&logFont, pgraphics);

   }

   // pLogFont->nHeight is interpreted as PointSize * 10
   bool font::CreatePointFontIndirect(const LOGFONTW* lpLogFont, ::draw2d::graphics_pointer & pgraphics)
   {
      HDC hDC;
      if (pgraphics != nullptr)
      {
         ASSERT_VALID(pgraphics);
         ASSERT((dynamic_cast<::draw2d_gdi::graphics * >(pgraphics))->get_handle2() != nullptr);
         hDC = (dynamic_cast<::draw2d_gdi::graphics * >(pgraphics))->get_handle2();
      }
      else
         hDC = ::GetDC(nullptr);

      // convert nPointSize to logical units based on pgraphics
      LOGFONTW logFont = *lpLogFont;
      ::point_i32 point;
      // 72 points/inch, 10 decipoints/point_i32
      point.y = ::MulDiv(::GetDeviceCaps(hDC, LOGPIXELSY), logFont.lfHeight, 720);
      point.x = 0;
      ::DPtoLP(hDC, &point, 1);
      ::point_i32 pointOrg;
      ::DPtoLP(hDC, pointOrg, 1);
      logFont.lfHeight = -abs(point.y - pointOrg.y);

      if (pgraphics == nullptr)
         ReleaseDC(nullptr, hDC);


      logFont.lfQuality = ANTIALIASED_QUALITY;

      return CreateFontIndirect(&logFont);

   }


   bool font::create()
   {

      ::draw2d_gdi::object::create();

      if(m_eunitFontSize == ::draw2d::unit_pixel)
      {

         CreatePointFont((i32) (m_dFontSize * 720.0 / 96.0), m_strFontFamilyName, nullptr);

      }
      else
      {
         CreatePointFont((i32) (m_dFontSize * 10.0), m_strFontFamilyName, nullptr);
      }

      return true;

   }

} // namespace draw2d_gdi







