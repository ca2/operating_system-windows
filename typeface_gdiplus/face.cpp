// Created by camilo with Mom and Bilbo support on
// 2025-06-01 23:29 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "face.h"
#include "aura/graphics/write_text/text_metric.h"
#include "operating_system-windows/gdiplus_library/_.h"

#pragma comment(lib, "gdiplus.lib")


using namespace Gdiplus;


namespace typeface_gdiplus
{



   // Converts a 32bpp bitmap into an 8bpp grayscale buffer
   memory ExtractGrayscaleFromBitmap(Bitmap& bmp) {
      ::i32 width = bmp.GetWidth();
      ::i32 height = bmp.GetHeight();

      memory grayBuffer(width * height);

      BitmapData data;
      Rect rect(0, 0, width, height);
      bmp.LockBits(&rect, ImageLockModeRead, PixelFormat32bppARGB, &data);

      BYTE* src = static_cast<BYTE*>(data.Scan0);

      for (::i32 y = 0; y < height; ++y) {
         BYTE* row = src + y * data.Stride;
         for (::i32 x = 0; x < width; ++x) {
            BYTE b = row[x * 4 + 0];
            BYTE g = row[x * 4 + 1];
            BYTE r = row[x * 4 + 2];
            BYTE a = row[x * 4 + 3];

            // Premultiplied alpha correction (optional)
            if (a > 0) {
               r = r * 255 / a;
               g = g * 255 / a;
               b = b * 255 / a;
            }

            BYTE gray = static_cast<BYTE>(0.299 * r + 0.587 * g + 0.114 * b);
            grayBuffer[y * width + x] = gray;
         }
      }

      bmp.UnlockBits(&data);
      return grayBuffer;
   }

   //memory RenderGlyphTo8BitGray(wchar_t ch, ::i32 width = 64, ::i32 height = 64) 
   //{

   //   //// Display as ASCII art (debugging purpose)
   //   //for (::i32 y = 0; y < height; ++y) {
   //   //   for (::i32 x = 0; x < width; ++x) {
   //   //      BYTE value = grayscale[y * width + x];
   //   //      putchar(value > 128 ? '#' : (value > 32 ? '+' : '.'));
   //   //   }
   //   //   putchar('\n');
   //   //}

   //   return grayscale;
   //}

   face::face()
   {

      //m_bFace = false;

      m_pfont = nullptr;
      m_pfamily = nullptr;

      initialize_gdiplus();


   }


   face::~face()
   {

      ::acme::del(m_pfont);
      ::acme::del(m_pfamily);

      terminate_gdiplus();

   }


   void face::_defer_gdiplus_font_and_family()
   {

      if (!m_pfamily || !m_pfont)
      {

         ::acme::del(m_pfont);
         ::acme::del(m_pfamily);

         //m_bFace = true;
         //return ch;
         m_pfamily = new FontFamily(::wstring(m_strFontName));
         //FontFamily* m_pfamily(L"Segoe UI");
         m_pfont = new Font(m_pfamily, (Gdiplus::REAL) m_iPixelSize, FontStyleRegular, UnitPixel);

         if (m_pfamily->GetLastStatus() != Ok || m_pfont->GetLastStatus() != Ok)
         {

            ::acme::del(m_pfont);
            ::acme::del(m_pfamily);

            throw ::exception(error_failed, "Could not create GDI+ font family or font");

         }

         //create_draw_buffers();

      }

   }

   void face::create_character(::typeface::character& ch, const ::scoped_string& scopedstr)
      //Character& face_freetype::get_character(const ::scoped_string& scopedstr)
   {

      _defer_gdiplus_font_and_family();

      wd32_character ia[2];
      ia[0] = unicode_index(scopedstr);
      ia[1] = 0;
      WCHAR wch[5];
      auto len = wd32_to_wd16(wch, ia);
      wch[len] = L'\0';
      auto iLength = static_cast<INT>(len);

      StringFormat format(StringFormat::GenericTypographic());
      format.SetFormatFlags(
         format.GetFormatFlags()
         | StringFormatFlagsMeasureTrailingSpaces
         | StringFormatFlagsNoWrap);

      Bitmap measureBitmap(1, 1, PixelFormat32bppPARGB);
      Graphics measureGraphics(&measureBitmap);
      measureGraphics.SetTextRenderingHint(TextRenderingHintAntiAliasGridFit);

      RectF layoutRect;
      PointF origin(0, 0);
      
      auto status = measureGraphics.MeasureString(wch, iLength, m_pfont, origin, &format, &layoutRect);

      if (status != Ok)
      {

         throw ::exception(error_failed, "GDI+ could not measure glyph");

      }

      ::i32 bmpWidth = maximum(1, static_cast<::i32>(ceil(layoutRect.Width)) + 4);
      ::i32 bmpHeight = maximum(1, static_cast<::i32>(ceil(layoutRect.Height)) + 4);

      Bitmap bmp(bmpWidth, bmpHeight, PixelFormat32bppPARGB);
      Graphics g(&bmp);
      g.SetSmoothingMode(SmoothingModeAntiAlias);
      g.SetTextRenderingHint(TextRenderingHintAntiAliasGridFit);
      g.Clear(Color(0, 0, 0, 0)); // Transparent background

      SolidBrush brush(Color(255, 255, 255, 255));

      // Draw glyph at (2, 2) for margin
      PointF drawPoint(2.0f, 2.0f);
      status = g.DrawString(wch, iLength, m_pfont, drawPoint, &format, &brush);

      if (status != Ok)
      {

         throw ::exception(error_failed, "GDI+ could not render glyph");

      }

      // Lock pixels
      BitmapData data;
      Rect rect(0, 0, bmpWidth, bmpHeight);
      status = bmp.LockBits(&rect, ImageLockModeRead, PixelFormat32bppPARGB, &data);

      if (status != Ok)
      {

         throw ::exception(error_failed, "GDI+ could not lock glyph bitmap");

      }

      //memory pre;
      //pre.set_size(bmpWidth * bmpHeight*4);
      //BYTE* src = static_cast<BYTE*>(data.Scan0);

      //for (::i32 y = 0; y < bmpHeight; ++y) {
      //   BYTE* row = src + y * data.Stride;
      //   for (::i32 x = 0; x < bmpWidth; ++x) {
      //      BYTE b = row[x * 4 + 0];
      //      BYTE g = row[x * 4 + 1];
      //      BYTE r = row[x * 4 + 2];
      //      BYTE a = row[x * 4 + 3];

      //      //if (a > 0) {
      //        // r = r * 255 / a;
      //         //g = g * 255 / a;
      //         //b = b * 255 / a;
      //      //}

      //      BYTE luminance = static_cast<BYTE>(0.299 * r + 0.587 * g + 0.114 * b);
      //      gray.data()[y * bmpWidth + x] = luminance;
      //   }
      //}

      

      auto iStyle = m_pfont->GetStyle();
      auto dEmHeight = (double)m_pfamily->GetEmHeight(iStyle);
      auto dCellAscent = (double)m_pfamily->GetCellAscent(iStyle);
      auto dFontSize = (double)m_pfont->GetSize();

      ::i32 bearingX = static_cast<::i32>(floor(layoutRect.X));
      ::i32 bearingY = dEmHeight > 0.0
         ? static_cast<::i32>(ceil(dFontSize * dCellAscent / dEmHeight))
         : 0;
      ::i32 advance = maximum(0, static_cast<::i32>(ceil(layoutRect.Width)));

      // now store character for later use
      //aracter = {
        //  texture,
      ch.Size = {bmpWidth, bmpHeight};
      ch.Bearing = {bearingX, bearingY};
      ch.Advance = advance;


      ::memory memoryGlyph;

      memoryGlyph.set_size(bmpWidth * bmpHeight * 4);

      auto ptarget = memoryGlyph.data();
      auto psource = static_cast<const ::u8*>(data.Scan0);
      auto iStride = data.Stride;

      if (iStride < 0)
      {

         psource += (bmpHeight - 1) * -iStride;

      }

      for (::i32 y = 0; y < bmpHeight; y++)
      {

         memory_copy(ptarget + y * bmpWidth * 4, psource + y * iStride, bmpWidth * 4);

      }

      create_texture(ch, memoryGlyph.data());
      bmp.UnlockBits(&data);
      //};
      //Characters.insert(std::pair<::i8, Character>(c, character));
   //}

      
      //Bitmap bmp(bmpWidth, bmpHeight, PixelFormat32bppARGB);
      //Graphics g(&bmp);
      //g.SetSmoothingMode(SmoothingModeAntiAlias);
      //g.Clear(Color(255, 255, 255, 255)); // white background

      //SolidBrush brush(Color(255, 0, 0, 0)); // black text

      //PointF origin(0, 0);
      //g.DrawString(wch, 1, m_pfont, origin, &brush);

      //auto grayscale = ExtractGrayscaleFromBitmap(bmp);


   }


   void face::get_text_metric(::write_text::text_metric* pmetric)
   {

      if (!pmetric)
      {

         throw ::exception(error_null_pointer);

      }

      _defer_gdiplus_font_and_family();

      Gdiplus::Font* pgdiplusfont = m_pfont;

      if (pgdiplusfont == nullptr)
      {

         //return false;

         throw ::exception(error_null_pointer);

      }

      Gdiplus::FontFamily* pgdiplusfontfamily = m_pfamily;

      if (pgdiplusfontfamily == nullptr)
      {

         //return false;

         throw ::exception(error_null_pointer);

      }

      INT iStyle = pgdiplusfont->GetStyle();

      //Gdiplus::FontFamily family;

      //pfont->GetFamily(&family);

      ::f64 dEmHeight = pgdiplusfontfamily->GetEmHeight(iStyle);

      ::f64 dCellAscent = pgdiplusfontfamily->GetCellAscent(iStyle);

      ::f64 dCellDescent = pgdiplusfontfamily->GetCellDescent(iStyle);

      ::f64 dLineSpacing = pgdiplusfontfamily->GetLineSpacing(iStyle);

      ::f64 dFontSize = pgdiplusfont->GetSize();

      if (dEmHeight <= 0.0)
      {

         throw ::exception(error_failed, "Invalid GDI+ font em height");

      }

      Bitmap measureBitmap(1, 1, PixelFormat32bppPARGB);
      Graphics measureGraphics(&measureBitmap);
      measureGraphics.SetTextRenderingHint(TextRenderingHintAntiAliasGridFit);


      auto pg = (Gdiplus::Graphics*)&measureGraphics;

      ::f64 dFontHeight = pgdiplusfont->GetHeight(pg);

      //m_pgraphics->DrawLine(m_ppen->get_os_data < Gdiplus::Pen* >(this), Gdiplus::PointF((Gdiplus::REAL)m_point.x, (Gdiplus::REAL)m_point.y), Gdiplus::PointF((Gdiplus::REAL)x, (Gdiplus::REAL)y));
      pmetric->m_dAscent = dFontSize * dCellAscent / dEmHeight;

      pmetric->m_dDescent = dFontSize * dCellDescent / dEmHeight;

      pmetric->m_dHeight = dFontHeight;

      ::f64 dLineSpacing2 = maximum(dFontHeight, dFontSize * dLineSpacing / dEmHeight);

      pmetric->m_dInternalLeading = 0;

      pmetric->m_dExternalLeading = dLineSpacing2 - (pmetric->m_dAscent + pmetric->m_dDescent);

   }


}// namespace typeface_gdiplus


