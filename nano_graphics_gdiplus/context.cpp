//
// Created by camilo on 31/01/2022.
//
#include "platform.h"
#include "context.h"
#include "acme/prototype/geometry2d/rectangle.h"
#include "acme/prototype/geometry2d/size.h"
#include "brush.h"
#include "font.h"
#include "icon.h"
#include "image.h"
#include "path.h"
#include "pen.h"
////#include "acme/exception/exception.h"
#pragma comment(lib, "Msimg32.lib")
#include "acme/nano/graphics/context.h"


#include <gdiplus.h>
::i32 align_to_windows_draw_text_align(enum_align ealign);

::i32 draw_text_to_windows_draw_text(enum_draw_text edrawtext);


namespace nano_graphics_gdiplus
{


   context::context()
   {

      m_hdc = nullptr;
      //m_hdc = ::CreateCompatibleDC(nullptr);
      //m_bDelete = true;
   }


   context::~context()
   {

      //if (m_bDelete)
      //{

      //   ::DeleteDC(m_hdc);
      //}
   }


   void context::create(const ::i32_size & size)
   {


          // Create an off-screen bitmap
      int width = size.cx;
      int height = size.cy;

      m_pgdiplusbitmapMemory = ::as_pointer(new ::Gdiplus::Bitmap(width, height, PixelFormat32bppARGB));

      // Create a graphics context from the bitmap
      m_pgdiplusgraphics = ::as_pointer(new ::Gdiplus::Graphics(m_pgdiplusbitmapMemory));


   }


   void context::set_smoothing_mode(::nano::graphics::enum_smoothing_mode esmoothingmode)
   {

      switch (esmoothingmode)
      {
         case ::nano::graphics::e_smoothing_mode_high_quality:
            m_pgdiplusgraphics->SetSmoothingMode(Gdiplus::SmoothingModeAntiAlias);
            break;
         default:
            m_pgdiplusgraphics->SetSmoothingMode(Gdiplus::SmoothingModeDefault);
            break;
      }

   }


   void context::set_text_rendering_hint(::nano::graphics::enum_text_rendering_hint etextrenderinghint)
   {

      switch (etextrenderinghint)
      {
      case ::nano::graphics::e_text_rendering_hint_clear_type_grid_fit:
         m_pgdiplusgraphics->SetTextRenderingHint(::Gdiplus::TextRenderingHintClearTypeGridFit);
         break;
      default:
         m_pgdiplusgraphics->SetTextRenderingHint(::Gdiplus::TextRenderingHintSystemDefault);
         break;
      }
   }


   void context::clear(const ::color::color & color)
   {

      Gdiplus::Color gdipluscolor(color.u8_opacity(), color.u8_red(), color.u8_green(), color.u8_blue());
      m_pgdiplusgraphics->Clear(gdipluscolor);

   }


   void context::set_brush(::nano::graphics::brush * pnanographicsbrush)
   {

      m_pnanographicsgdiplusbrush = pnanographicsbrush;

   }


   void context::set_pen(::nano::graphics::pen * pnanographicspen)
   {

      m_pnanographicsgdipluspen = pnanographicspen;

   }


   void context::set_font(::nano::graphics::font * pnanographicsfont)
   {

      m_pnanographicsgdiplusfont = pnanographicsfont;

   }


   void context::attach(void *posdata, const ::i32_size &size, ::i32 iType)
   {

      if (iType == 0)
      {

         auto hdc = (HDC)posdata;

         m_hdc = hdc;

         m_pgdiplusgraphics = ::as_pointer(new ::Gdiplus::Graphics(hdc));

         //m_bDelete = false;

         m_size = size;

      }
      else
      {

         throw ::exception(error_wrong_type);

      }
   }


   HFONT CreateSimpleFont16(void)
   {
      // Negative height means character height in pixels
      return CreateFontA(-16, // height ≈ 16 px
                         0, // width (auto)
                         0, // escapement
                         0, // orientation
                         FW_NORMAL, // weight
                         FALSE, // italic
                         FALSE, // underline
                         FALSE, // strikeout
                         DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY,
                         DEFAULT_PITCH | FF_DONTCARE, "Segoe UI");
   }



      //void context::_draw_text(const ::scoped_string &scopedstr, const ::f64_rectangle &rectangleText,
      //                      const ::e_align &ealign, const ::e_draw_text &edrawtext,
      //                      ::nano::graphics::brush *pbrushBack, ::nano::graphics::brush *pbrushText,
      //                      ::nano::graphics::font *pnanographicsfont)

   void context::_draw_text(const ::scoped_string &scopedstr, const ::f64_rectangle &rectangleText,
                           const ::e_draw_text &edrawtext, const ::e_align &ealign)
   {

      //COLORREF colorrefBackgroundColor = win32_COLORREF(pnanobrushBack->m_color);

      //SetBkColor(m_hdc, colorrefBackgroundColor);

      //COLORREF colorrefTextColor = win32_COLORREF(pnanobrushText->m_color);

      //SetTextColor(m_hdc, colorrefTextColor);
      // SetTextColor(m_hdc, RGB(100, 100, 255));

      //SetBkMode(m_hdc, OPAQUE);

      //wstring wstrMessage(scopedstr);

      //pnanofont->update(this);


      //auto hfont = (HFONT)pnanofont->operating_system_data();

      // auto hfont2 = CreateSimpleFont16();

      // auto h3 = ::SelectObject(m_hdc, hfont2);

      //auto h3 = ::SelectObject(m_hdc, hfont);


                   //SolidBrush textBrush(
       //Color(255,255,255,255));

       
      
       Gdiplus::StringFormat sf;

       if (ealign & e_align_right)
       {
          sf.SetAlignment(Gdiplus::StringAlignmentFar);
       }
       else if (ealign & e_align_horizontal_center)
       {
          sf.SetAlignment(Gdiplus::StringAlignmentCenter);
       }
       else
       {
          sf.SetAlignment(Gdiplus::StringAlignmentNear);
       }
      
       if (ealign & e_align_bottom)
       {
          sf.SetLineAlignment(Gdiplus::StringAlignmentFar);
       }
       else if (ealign & e_align_vertical_center)
       {
          sf.SetLineAlignment(Gdiplus::StringAlignmentCenter);
       }
       else
       {
          sf.SetLineAlignment(Gdiplus::StringAlignmentNear);
       }


       ::cast<::nano_graphics_gdiplus::font> pnanographicsgdiplusfont = m_pnanographicsgdiplusfont;

       ::cast<::nano_graphics_gdiplus::brush> pnanographicsgdiplusbrush = m_pnanographicsgdiplusbrush;


       ::wstring wstr(scopedstr);

       ::Gdiplus::RectF rectfText;

       ::copy(rectfText, rectangleText);

       m_pgdiplusgraphics->DrawString(
       wstr, (INT) wstr.length(),
       pnanographicsgdiplusfont->m_pgdiplusfont,
       rectfText,
       &sf,
       pnanographicsgdiplusbrush->m_pgdiplusbrush);

      //LOGFONTW lf{};

      //::GetObject(hfont, sizeof(lf), &lf);

      //TEXTMETRICW textmetricw = {};

      //::GetTextMetrics(m_hdc, &textmetricw);

      //::i32 iAlign = align_to_windows_draw_text_align(ealign);

      //::i32 iFlag = draw_text_to_windows_draw_text(edrawtext);

      //// iAlign = 0;

      //// iFlag = 0;

      //RECT r;

      //::copy(r, rectangleText);

      //// InflateRect(&r, 16, 16);


      //auto pszMessage = wstrMessage.c_str();

      ////            if (scopedstr.contains("Operating"))
      ////{

      ////   information("Operating");

      ////   //r.left = 0;
      ////   //r.top = 0;
      ////   //r.right = 400;
      ////   //r.bottom = 30;

      ////   wstrMessage = "test";
      ////   // return;
      ////}

      //::i32 iLength = wstrMessage.length();

      //// auto pnanographicsbrush = createø<::nano::graphics::brush>();

      //// pnanographicsbrush->m_color = ::color::yellow;

      //// auto pnanographicspen = createø<::nano::graphics::pen>();

      //// pnanographicspen->m_color = ::color::magenta;

      //// rectangle(r, nullptr, pnanographicspen);

      //::DrawTextW(m_hdc, wstrMessage, (::i32)iLength, (LPRECT)&r, iAlign | iFlag);

      //::SelectObject(m_hdc, h3);

      //::DeleteObject(hfont2);
   }


   //::i32_size context::get_text_extents(const ::scoped_string &scopedstr, ::nano::graphics::font *pnanographicsfont)
   ::f64_size context::get_text_extents(const ::scoped_string &scopedstr)
   {

      //pnanofont->update(this);

      ::cast<::nano_graphics_gdiplus::font> pnanographicsgdiplusfont = m_pnanographicsgdiplusfont;

          ::Gdiplus::RectF bounds;

          ::wstring wstrText(scopedstr);

          auto pgdiplusfont = pnanographicsgdiplusfont->m_pgdiplusfont;

      m_pgdiplusgraphics->MeasureString(wstrText.c_str(), (INT) wstrText.length(), pgdiplusfont,
         ::Gdiplus::PointF(0.f, 0.f), &bounds);

      return {bounds.Width, bounds.Height};

      /*::SelectObject(m_hdc, (HFONT)pnanofont->operating_system_data());

      wstring wstr(scopedstr);

      ::SIZE size;

      if (!::GetTextExtentPoint32W(m_hdc, wstr, (::i32)wstr.length(), &size))
      {

         throw ::exception(error_failed);
      }

      return {size.cx, size.cy};*/
   }


   //void context::rectangle(const ::f64_rectangle &rectangle, ::nano::graphics::brush *pnanographicsbrush,
     //                     ::nano::graphics::pen *pnanographicspen)

   void context::rectangle(const ::f64_rectangle &rectangle)
   {

      if (!m_pnanographicsgdiplusbrush && !m_pnanographicsgdipluspen)
      {

         return;
      }

      Gdiplus::RectF rectf;

      ::copy(rectf, rectangle);

      if (m_pnanographicsgdiplusbrush)
      {

         auto pgdiplusbrush = m_pnanographicsgdiplusbrush->m_pgdiplusbrush;

         m_pgdiplusgraphics->FillRectangle(pgdiplusbrush, rectf);
      }
      //else
      //{

      //   //::SelectObject(m_hdc, (HGDIOBJ)::GetStockObject(NULL_BRUSH));
      //}

      if (m_pnanographicsgdipluspen)
      {

         //pnanographicspen->update(this);

           //    ;
         //::SelectObject(m_hdc, (HGDIOBJ)pnanographicspen->operating_system_data());

         auto pgdiplusbrush = m_pnanographicsgdipluspen->m_pgdipluspen;

         m_pgdiplusgraphics->DrawRectangle(pgdiplusbrush, rectf);

      }
      else
      {
//
  //     ::SelectObject(m_hdc, (HGDIOBJ)::GetStockObject(NULL_PEN));
      }


      //auto r = rectangle;

      //if (pnanographicspen)
      //{

      //   r.left += pnanographicspen->m_iWidth - 1;
      //   r.top += pnanographicspen->m_iWidth - 1;
      //}

      //::Rectangle(m_hdc, r.left, r.top, r.right, r.bottom);
   }

      void context::ellipse(const ::f64_rectangle &rectangle)
   {

      if (!m_pnanographicsgdiplusbrush && !m_pnanographicsgdipluspen)
      {

         return;
      }

      Gdiplus::RectF rectf;

      ::copy(rectf, rectangle);

      if (m_pnanographicsgdiplusbrush)
      {

//         ::cast<::nano_graphics_gdiplus::brush> pnanographicsgdiplusbrush = m_pnanographicsgdiplusbrush;
         // pnanographicsbrush->update(this);

         auto pgdiplusbrush = m_pnanographicsgdiplusbrush->m_pgdiplusbrush;

         m_pgdiplusgraphics->FillEllipse(pgdiplusbrush, rectf);
      }
      // else
      //{

      //   //::SelectObject(m_hdc, (HGDIOBJ)::GetStockObject(NULL_BRUSH));
      //}

      if (m_pnanographicsgdipluspen)
      {

         // pnanographicspen->update(this);

         //    ;
         //::SelectObject(m_hdc, (HGDIOBJ)pnanographicspen->operating_system_data());

                  //::cast<::nano_graphics_gdiplus::pen> pgdipluspen = m_pnanographicsgdipluspen;

         auto pgdipluspen = m_pnanographicsgdipluspen->m_pgdipluspen;

         m_pgdiplusgraphics->DrawEllipse(pgdipluspen, rectf);
      }
      else
      {
         //
         //     ::SelectObject(m_hdc, (HGDIOBJ)::GetStockObject(NULL_PEN));
      }


      // auto r = rectangle;

      // if (pnanographicspen)
      //{

      //   r.left += pnanographicspen->m_iWidth - 1;
      //   r.top += pnanographicspen->m_iWidth - 1;
      //}

      //::Rectangle(m_hdc, r.left, r.top, r.right, r.bottom);
   }


      void context::line(const ::f64_point& point1, const ::f64_point& point2)
      {
         //::cast<::nano_graphics_gdiplus::pen> pgdipluspen = m_pnanographicsgdipluspen;

         ::Gdiplus::PointF pointf1((::Gdiplus::REAL)point1.x, (::Gdiplus::REAL)point1.y);
         ::Gdiplus::PointF pointf2((::Gdiplus::REAL)point2.x, (::Gdiplus::REAL)point2.y);

         auto pgdipluspen = m_pnanographicsgdipluspen->m_pgdipluspen;

         m_pgdiplusgraphics->DrawLine(pgdipluspen, pointf1, pointf2);

      }


   void context::draw_icon(::f64 x, ::f64 y, ::f64 cx, ::f64 cy, ::nano::graphics::icon *picon)
   {


      ::cast<::nano_graphics_gdiplus::icon> pgdiplusicon = picon;

      Gdiplus::RectF rectangle(
         (::Gdiplus::REAL) x,
         (::Gdiplus::REAL) y,
         (::Gdiplus::REAL) cx,
         (::Gdiplus::REAL) cy);

      m_pgdiplusgraphics->DrawImage(pgdiplusicon->m_pgdiplusimage, rectangle);
      //)

      // HDC hdcMem = ::CreateCompatibleDC(m_hdc);

      // HBITMAP hOldBitmap = (HBITMAP)SelectObject(hdcMem, pwindowsicon->m_hgdiobj);

      //// Step 3: Use BitBlt to copy the bitmap from the memory DC to the destination DC
      //    // Set up the BLENDFUNCTION structure for alpha blending
      // BLENDFUNCTION blendFunction;
      // blendFunction.BlendOp = AC_SRC_OVER;
      // blendFunction.BlendFlags = 0;
      // blendFunction.SourceConstantAlpha = 255;  // Use full opacity
      // blendFunction.AlphaFormat = AC_SRC_ALPHA; // The source bitmap has an alpha channel

      //// Step 3: Use AlphaBlend to copy the bitmap from the memory DC to the destination DC
      // AlphaBlend(m_hdc, x, y, cx, cy, hdcMem, 0, 0, cx, cy, blendFunction);


      //// Step 4: Restore the old bitmap in the memory DC
      // SelectObject(hdcMem, hOldBitmap);

      //::DeleteDC(hdcMem);
   }


   void context::draw_image(const ::f64_rectangle & rectangle, ::nano::graphics::image * pimage)
   {

      ::cast < ::nano_graphics_gdiplus::image > pnanographicsgdiplusimage = pimage;

      ::Gdiplus::RectF rectangleTarget;

      ::copy(rectangleTarget, rectangle);

      auto pgdiplusbitmap = pnanographicsgdiplusimage->m_pgdiplusbitmap;

      m_pgdiplusgraphics->DrawImage(pgdiplusbitmap, rectangleTarget);

   }


   void context::draw_image(const ::f64_point & point, const ::f64_rectangle & rectangle,
                            ::nano::graphics::image * pimage)
   {

      ::cast < ::nano_graphics_gdiplus::image > pnanographicsgdiplusimage = pimage;

      auto pgdiplusbitmap = pnanographicsgdiplusimage->m_pgdiplusbitmap;

      m_pgdiplusgraphics->DrawImage(
         pgdiplusbitmap,
         (::Gdiplus::REAL) point.x,
         (::Gdiplus::REAL) point.y,
         (::Gdiplus::REAL) rectangle.left,
         (::Gdiplus::REAL) rectangle.top,
         (::Gdiplus::REAL) rectangle.width(),
         (::Gdiplus::REAL) rectangle.height(),
         ::Gdiplus::UnitPixel);

   }


   void context::translate(::f64 x, ::f64 y) {
      //OffsetViewportOrgEx(m_hdc, x, y, nullptr);

      m_pgdiplusgraphics->TranslateTransform((Gdiplus::REAL)x, (::Gdiplus::REAL)y);
   
   }


   void context::do_path(::nano::graphics::path *pnanographicspath)
   {

      if (!m_pnanographicsgdiplusbrush && !m_pnanographicsgdipluspen)
      {

         return;

      }

      ::cast<::nano_graphics_gdiplus::path> pnanographicsgdipluspath = pnanographicspath;

      if (m_pnanographicsgdiplusbrush)
      {
         //::cast<::nano_graphics_gdiplus::brush> pnanographicsgdiplusbrush = m_pnanographicsgdiplusbrush;

         auto pgdiplusbrush = m_pnanographicsgdiplusbrush->m_pgdiplusbrush;

         auto pgdiplusgraphicspath = pnanographicsgdipluspath->m_pgdiplusgraphicspath;

         m_pgdiplusgraphics->FillPath(pgdiplusbrush, pgdiplusgraphicspath);

      }

      

      if (m_pnanographicsgdipluspen)
      {
         //::cast<::nano_graphics_gdiplus::pen> pgdipluspen = m_pnanographicsgdipluspen;

         auto pgdipluspen = m_pnanographicsgdipluspen->m_pgdipluspen;

         auto pgdiplusgraphicspath = pnanographicsgdipluspath->m_pgdiplusgraphicspath;

         m_pgdiplusgraphics->DrawPath(pgdipluspen, pgdiplusgraphicspath);

      }

   }


} // namespace nano_graphics_gdiplus


::i32 align_to_windows_draw_text_align(enum_align ealign)
{

   ::i32 iAlign = 0;

   if (ealign & e_align_right)
   {

      iAlign |= DT_RIGHT;
   }
   else if (ealign & e_align_horizontal_center)
   {

      iAlign |= DT_CENTER;
   }
   else
   {

      iAlign |= DT_LEFT;
   }


   if (ealign & e_align_bottom)
   {

      iAlign |= DT_BOTTOM;
   }
   else if (ealign & e_align_vertical_center)
   {

      iAlign |= DT_VCENTER;
   }
   else
   {

      iAlign |= DT_TOP;
   }

   return iAlign;
}


::i32 draw_text_to_windows_draw_text(enum_draw_text edrawtext)
{

   ::i32 iFlag = 0;

   if (edrawtext & e_draw_text_end_ellipsis)
   {

      iFlag |= DT_END_ELLIPSIS;
   }

   if (edrawtext & e_draw_text_expand_tabs)
   {

      iFlag |= DT_EXPANDTABS;
   }

   if (edrawtext & e_draw_text_single_line)
   {

      iFlag |= DT_SINGLELINE;
   }

   if (edrawtext & e_draw_text_word_break)
   {

      iFlag |= DT_WORDBREAK;
   }

   return iFlag;
}
