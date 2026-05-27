#include "framework.h"


namespace draw2d_gdi
{


   font::font(::particle * pparticle) :
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


   bool font::CreateFont(::i32 nHeight, ::i32 nWidth, ::i32 nEscapement, ::i32 nOrientation, ::i32 nWeight, BYTE bItalic, BYTE bUnderline, BYTE cStrikeOut, BYTE nCharSet, BYTE nOutPrecision, BYTE nClipPrecision, BYTE nQuality, BYTE nPitchAndFamily, const ::scoped_string & scopedstrFacename)
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
         memory_set(&lf, 0, sizeof(lf));
         font.GetLogFont(&lf);
         CreateFontIndirect(&lf);
      }

   }


   void font::dump(dump_context & dumpcontext) const
   {
      ::draw2d::object::dump(dumpcontext);

      if (get_handle() == nullptr)
         return;

      /*         if (!::windows_definition::Data.bWin95 && ::GetObjectType(get_handle()) != OBJ_FONT)
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
      dumpcontext << "\nlf.lfItalic = " << (::i32)lf.lfItalic;
      dumpcontext << "\nlf.lfUnderline = " << (::i32)lf.lfUnderline;
      dumpcontext << "\nlf.lfStrikeOut = " << (::i32)lf.lfStrikeOut;
      dumpcontext << "\nlf.lfCharSet = " << (::i32)lf.lfCharSet;
      dumpcontext << "\nlf.lfOutPrecision = " << (::i32)lf.lfOutPrecision;
      dumpcontext << "\nlf.lfClipPrecision = " << (::i32)lf.lfClipPrecision;
      dumpcontext << "\nlf.lfQuality = " << (::i32)lf.lfQuality;
      dumpcontext << "\nlf.lfPitchAndFamily = " << (::i32)lf.lfPitchAndFamily;
      dumpcontext << "\nlf.lfFaceName = " << (const ::string &)lf.lfFaceName;

      dumpcontext << "\n";
   }

   /////////////////////////////////////////////////////////////////////////////
   // out-of-line ::draw2d::brush, font, etc. helpers

   // nPointSize is actually scaled 10x
   bool font::CreatePointFont(::i32 nPointSize, const ::scoped_string & scopedstrFaceName, ::draw2d::graphics_pointer & pgraphics)
   {

      LOGFONTW logFont;

      zero(logFont);

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
         ASSERT_OK(pgraphics);
         ASSERT((dynamic_cast<::draw2d_gdi::graphics * >(pgraphics))->get_handle2() != nullptr);
         hDC = (dynamic_cast<::draw2d_gdi::graphics * >(pgraphics))->get_handle2();
      }
      else
         hDC = ::GetDC(nullptr);

      // convert nPointSize to logical units based on pgraphics
      LOGFONTW logFont = *lpLogFont;
      ::i32_point point;
      // 72 points/inch, 10 decipoints/i32_point
      point.y = ::MulDiv(::GetDeviceCaps(hDC, LOGPIXELSY), logFont.lfHeight, 720);
      point.x = 0;
      ::DPtoLP(hDC, &point, 1);
      ::i32_point pointOrg;
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

      if(m_eunitFontSize == ::draw2d::e_unit_pixel)
      {

         CreatePointFont((::i32) (m_dFontSize * 720.0 / 96.0), m_strFontFamilyName, nullptr);

      }
      else
      {
         CreatePointFont((::i32) (m_dFontSize * 10.0), m_strFontFamilyName, nullptr);
      }

      return true;

   }

} // namespace draw2d_gdi







