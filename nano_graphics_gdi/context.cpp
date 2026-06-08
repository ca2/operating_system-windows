//
// Created by camilo on 31/01/2022.
//
#include "framework.h"
#include "context.h"
#include "brush.h"
#include "font.h"
#include "icon.h"
#include "pen.h"
#include "acme/prototype/geometry2d/size.h"
#include "acme/prototype/geometry2d/rectangle.h"
////#include "acme/exception/exception.h"
#pragma comment(lib, "Msimg32.lib")
#include <gdiplus.h>


::i32 align_to_windows_draw_text_align(const ::e_align & ealign);

::i32 draw_text_to_windows_draw_text(const ::e_draw_text & edrawtext);


      namespace nano_graphics_gdi
      {


         context::context()
         {

            m_hdc = ::CreateCompatibleDC(nullptr);
            m_bDelete = true;

         }




         context::~context()
         {

            if (m_bDelete)
            {

               ::DeleteDC(m_hdc);

            }

         }


         void context::attach(void * posdata, const ::i32_size & size, int iType)
         {

             if (iType == 0) {
                 auto hdc = (HDC)posdata;

                 m_hdc = hdc;
                 m_bDelete = false;

                 m_size = size;
             }
             else {

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


         void context::_draw_text(const ::scoped_string &scopedstr, const ::f64_rectangle &rectangleText,
                                  const ::e_draw_text &edrawtext, const ::e_align &ealign)
         {

            //COLORREF colorrefBackgroundColor = win32_COLORREF(pnanobrushBack->m_color);

            //SetBkColor(m_hdc, colorrefBackgroundColor);

            ::SetBkMode(m_hdc, TRANSPARENT);

            COLORREF colorrefTextColor = win32_COLORREF(m_pbrush->m_color);

            SetTextColor(m_hdc, colorrefTextColor);
            //SetTextColor(m_hdc, RGB(100, 100, 255));

            SetBkMode(m_hdc, OPAQUE);

            wstring wstrMessage(scopedstr);

            //pnanofont->update(this);

            auto hfont = (HFONT)m_pfont->m_hgdiobj;

            //auto hfont2 = CreateSimpleFont16();

            //auto h3 = ::SelectObject(m_hdc, hfont2);

            auto h3 = ::SelectObject(m_hdc, hfont);


            LOGFONTW lf{};

            ::GetObject(hfont, sizeof(lf), &lf);

            TEXTMETRICW textmetricw = {};

            ::GetTextMetrics(m_hdc, &textmetricw);

            ::i32 iAlign = align_to_windows_draw_text_align(ealign);

            ::i32 iFlag = draw_text_to_windows_draw_text(edrawtext);

            //iAlign = 0;

            //iFlag = 0;

            RECT r;

            ::copy(r, rectangleText);

            //InflateRect(&r, 16, 16);

            
            auto pszMessage = wstrMessage.c_str();

            //            if (scopedstr.contains("Operating"))
            //{

            //   information("Operating");

            //   //r.left = 0;
            //   //r.top = 0;
            //   //r.right = 400;
            //   //r.bottom = 30;

            //   wstrMessage = "test";
            //   // return;
            //}
            
            ::i32 iLength = wstrMessage.length();

            //auto pbrush = createø<::nano::graphics::brush>();

            //pbrush->m_color = ::color::yellow;

            //auto ppen = createø<::nano::graphics::pen>();

            //ppen->m_color = ::color::magenta;

            //rectangle(r, nullptr, ppen);

            ::DrawTextW(m_hdc, wstrMessage, (::i32)iLength, (LPRECT)&r, iAlign | iFlag);

            //::SelectObject(m_hdc, h3);

            //::DeleteObject(hfont2);

         }


         ::f64_size context::get_text_extents(const ::scoped_string & scopedstr)
         {

            //pnanofont->update(this);
            auto hfont = (HFONT) m_pfont->m_hgdiobj;

            ::SelectObject(m_hdc, hfont);

            wstring wstr(scopedstr);

            ::SIZE size;

            if (!::GetTextExtentPoint32W(m_hdc, wstr, (::i32)wstr.length(), &size))
            {

               throw ::exception(error_failed);

            }

            return { size.cx, size.cy };

         }


         void context::rectangle(const ::f64_rectangle& rectangle)
         {

            if (!m_pbrush && !m_ppen)
            {

               return;

            }

            if (m_pbrush)
            {

               //pnanobrush->update(this);

               ::SelectObject(m_hdc, (HGDIOBJ)m_pbrush->m_hgdiobj);
            }
            else
            {

               ::SelectObject(m_hdc, (HGDIOBJ)::GetStockObject(NULL_BRUSH));

            }

            if (m_ppen)
            {

               //pnanopen->update(this);

               ::SelectObject(m_hdc, (HGDIOBJ)m_ppen->m_hgdiobj);
            }
            else
            {

               ::SelectObject(m_hdc, (HGDIOBJ)::GetStockObject(NULL_PEN));

            }


            auto r = rectangle;

            if (m_ppen)
            {

               r.left += m_ppen->m_fWidth - 1;
               r.top += m_ppen->m_fWidth - 1;
            }

            ::Rectangle(m_hdc,
               r.left,
               r.top,
               r.right,
               r.bottom);


         }


         void context::draw_icon(::f64 x, ::f64 y, ::f64 cx, ::f64 cy, ::nano::graphics::icon *picon)
         {



            ::pointer < ::nano_graphics_gdi::icon > pwindowsicon = picon;

            Gdiplus::Graphics g(m_hdc);

            Gdiplus::Rect r;

            r.X = x;
            r.Y = y;
            r.Width = cx;
            r.Height = cy;

            g.DrawImage(pwindowsicon->m_pimage, r);
            //)

            //HDC hdcMem = ::CreateCompatibleDC(m_hdc);

            //HBITMAP hOldBitmap = (HBITMAP)SelectObject(hdcMem, pwindowsicon->m_hgdiobj);

            //// Step 3: Use BitBlt to copy the bitmap from the memory DC to the destination DC
            //    // Set up the BLENDFUNCTION structure for alpha blending
            //BLENDFUNCTION blendFunction;
            //blendFunction.BlendOp = AC_SRC_OVER;
            //blendFunction.BlendFlags = 0;
            //blendFunction.SourceConstantAlpha = 255;  // Use full opacity
            //blendFunction.AlphaFormat = AC_SRC_ALPHA; // The source bitmap has an alpha channel

            //// Step 3: Use AlphaBlend to copy the bitmap from the memory DC to the destination DC
            //AlphaBlend(m_hdc, x, y, cx, cy, hdcMem, 0, 0, cx, cy, blendFunction);


            //// Step 4: Restore the old bitmap in the memory DC
            //SelectObject(hdcMem, hOldBitmap);

            //::DeleteDC(hdcMem);

         }


         void context::translate(::f64 x, ::f64 y)
         {

            OffsetViewportOrgEx(m_hdc, x, y, nullptr);

         }


      } // namespace nano_graphics_gdi





::i32 align_to_windows_draw_text_align(const ::e_align & ealign)
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



::i32 draw_text_to_windows_draw_text(const ::e_draw_text & edrawtext)
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


