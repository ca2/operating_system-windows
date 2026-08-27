#include "platform.h"
#include "font.h"
#include "graphics.h"
#include "path.h"
#include "brush.h"
#include "acme/exception/exception.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/platform/acme.h"
#include "acme/platform/platform_platform.h"
#include "aura/graphics/draw2d/draw2d.h"
#include "aura/platform/system.h"


namespace draw2d_gdiplus
{


   void graphics::_gdiplus_draw_text(::draw2d::path * ppathParam, const ::scoped_string & scopedstr, ::f64_rectangle & rectangleParam, const ::e_align & ealign, const ::e_draw_text & edrawtext, ::write_text::font * pfontParam, ::f64 dFontWidth, ::draw2d::brush * pbrushParam, bool bMeasure)
   {

      if (scopedstr.is_empty())
      {

         //return ::success;

         return;

      }

      if (::is_null(pfontParam))
      {

         throw ::exception(error_failed);

      }

      ::cast < ::draw2d_gdiplus::font > pdraw2dgdiplusfont = pfontParam;

      auto pwritetextfont = pdraw2dgdiplusfont->m_pgdiplusfont;

      if (::is_null(pwritetextfont))
      {

         //return ::error_failed;

         throw ::exception(error_failed);

      }

      Gdiplus::Graphics * pdraw2dgraphics = m_pgdiplusgraphics;

      _synchronous_lock synchronouslock(::write_text::font::s_pmutexFontTextMap);

      Gdiplus::GraphicsPath * pdraw2dpath = nullptr;

      if (::is_set(ppathParam))
      {

         ::cast < ::draw2d_gdiplus::path > pdraw2dgdipluspath = ppathParam;

         pdraw2dpath = pdraw2dgdipluspath->m_pgdiplusgraphicspath;

      }

      Gdiplus::Brush * pdraw2dbrush = nullptr;

      if (::is_set(pbrushParam))
      {

         ::cast < ::draw2d_gdiplus::brush > pdraw2dgdiplusbrush = pbrushParam;

         pdraw2dbrush = pdraw2dgdiplusbrush->m_pgdiplusbrush;

         if (::is_null(pdraw2dbrush))
         {

            //return ::error_failed;

            throw ::exception(error_failed);

         }

      }

      ASSERT(pdraw2dgraphics != nullptr || pdraw2dpath != nullptr);
      ASSERT(pwritetextfont != nullptr);
      ASSERT(pdraw2dpath != nullptr || pdraw2dbrush != nullptr);

      Gdiplus::Status status = Gdiplus::Status::GenericError;

      Gdiplus::StringFormat format(Gdiplus::StringFormat::GenericTypographic());

      format.SetFormatFlags((format.GetFormatFlags()
         //| Gdiplus::StringFormatFlagsNoClip | Gdiplus::StringFormatFlagsMeasureTrailingSpaces
         | Gdiplus::StringFormatFlagsMeasureTrailingSpaces
         | (edrawtext & e_draw_text_single_line ? Gdiplus::StringFormatFlagsNoWrap : 0))
         & ~(Gdiplus::StringFormatFlagsLineLimit));

      if (edrawtext & e_draw_text_path_ellipsis)
      {

         format.SetTrimming(Gdiplus::StringTrimmingEllipsisPath);

      }
      else if (edrawtext & e_draw_text_end_ellipsis)
      {

         format.SetTrimming(Gdiplus::StringTrimmingEllipsisCharacter);

      }

      if (ealign & e_align_left)
      {

         format.SetAlignment(Gdiplus::StringAlignmentNear);

      }
      else if (ealign & e_align_right)
      {

         format.SetAlignment(Gdiplus::StringAlignmentFar);

      }
      else if (ealign & e_align_horizontal_center)
      {

         format.SetAlignment(Gdiplus::StringAlignmentCenter);

      }
      else
      {

         format.SetAlignment(Gdiplus::StringAlignmentNear);

      }

      if (ealign & e_align_bottom)
      {

         format.SetLineAlignment(Gdiplus::StringAlignmentFar);

      }
      else if (ealign & e_align_top)
      {

         format.SetLineAlignment(Gdiplus::StringAlignmentNear);

      }
      else if (ealign & e_align_vertical_center)
      {

         format.SetLineAlignment(Gdiplus::StringAlignmentCenter);

      }
      else
      {

         format.SetLineAlignment(Gdiplus::StringAlignmentNear);

      }

      //try
      //{

      Gdiplus::FontFamily f;
      ::i32 nStyle;
      Gdiplus::REAL size;
      Gdiplus::Unit unit;

      if (pdraw2dpath)
      {

         pwritetextfont->GetFamily(&f);
         nStyle = pwritetextfont->GetStyle();
         size = pwritetextfont->GetSize();
         unit = pwritetextfont->GetUnit();

         if (unit == Gdiplus::UnitPoint)
         {

            size = pdraw2dgraphics->GetDpiY() * size / 73.0f;

         }

      }

      ::write_text::font::text* ptext = nullptr;

      ::write_text::font::text text2;

      if (pfontParam->m_bCacheLayout)
      {

         ptext = &pfontParam->m_mapFontText[scopedstr];

      }
      else
      {

         ptext = &text2;

      }

      if (ptext->get_item(::write_text::font::text::e_size_backend_draw_text)->get_text().is_empty())
      {

         ptext->get_item(::write_text::font::text::e_size_backend_draw_text)->set_text(scopedstr);

      }

      if (dFontWidth == 1.0)
      {

         Gdiplus::RectF rectf((Gdiplus::REAL)rectangleParam.left, (Gdiplus::REAL)rectangleParam.top, (Gdiplus::REAL)(width(rectangleParam) * dFontWidth), (Gdiplus::REAL)(height(rectangleParam)));

         character_count iSize = ptext->get_item(::write_text::font::text::e_size_backend_draw_text)->get_text().length();

         if (pdraw2dpath)
         {

            status = pdraw2dpath->AddString(ptext->get_item(::write_text::font::text::e_size_backend_draw_text)->get_text(), (INT)iSize, &f, nStyle, size, rectf, &format);

            if (bMeasure)
            {

               Gdiplus::RectF box;

               status = pdraw2dgraphics->MeasureString(ptext->get_item(::write_text::font::text::e_size_backend_draw_text)->get_text(), (INT)iSize, pwritetextfont, rectf, &format, &box);

               copy(rectangleParam, box);

            }

         }
         else if (pdraw2dgraphics)
         {

            auto eTextRenderingMode = pdraw2dgraphics->GetTextRenderingHint();

            auto eCompositingMode = pdraw2dgraphics->GetCompositingMode();

            if (eCompositingMode == ::Gdiplus::CompositingModeSourceCopy)
            {

               if (eTextRenderingMode != ::Gdiplus::TextRenderingHintAntiAlias)
               {

                  pdraw2dgraphics->SetTextRenderingHint(::Gdiplus::TextRenderingHintAntiAlias);

               }

            }

            status = pdraw2dgraphics->DrawString(ptext->get_item(::write_text::font::text::e_size_backend_draw_text)->get_text(), (INT)ptext->get_item(::write_text::font::text::e_size_backend_draw_text)->get_text().length(), pwritetextfont, rectf, &format, pdraw2dbrush);

            if (bMeasure)
            {

               Gdiplus::RectF box;

               status = pdraw2dgraphics->MeasureString(ptext->get_item(::write_text::font::text::e_size_backend_draw_text)->get_text(), (INT)iSize, pwritetextfont, rectf, &format, &box);

               copy(rectangleParam, box);

            }


            if (eCompositingMode == Gdiplus::CompositingModeSourceCopy)
            {

               if (eTextRenderingMode != ::Gdiplus::TextRenderingHintAntiAlias)
               {

                  pdraw2dgraphics->SetTextRenderingHint(eTextRenderingMode);

               }

            }

         }

         //auto e = pdraw2dgraphics->GetTextRenderingHint();

         //status = pdraw2dgraphics->DrawString(ptext->m_wstr, (INT)iSize, pwritetextfont, rectf, &format, pdraw2dbrush);

      //}

      }
      else if (pdraw2dgraphics)
      {

         g_keep k(pdraw2dgraphics);

         Gdiplus::Matrix m;

         status = pdraw2dgraphics->GetTransform(&m);

         auto pmNew = as_auto_pointer(m.Clone());

         status = pmNew->Translate((Gdiplus::REAL)rectangleParam.left, (Gdiplus::REAL)rectangleParam.top);

         status = pmNew->Scale((Gdiplus::REAL)dFontWidth, (Gdiplus::REAL)1.0, Gdiplus::MatrixOrderAppend);

         Gdiplus::RectF rectf(0, 0, (Gdiplus::REAL)(width(rectangleParam) * dFontWidth), (Gdiplus::REAL)(height(rectangleParam)));

         status = pdraw2dgraphics->SetTransform(pmNew);

         character_count iSize = ptext->get_item(::write_text::font::text::e_size_backend_draw_text)->get_text().length();

         status = pdraw2dgraphics->DrawString(ptext->get_item(::write_text::font::text::e_size_backend_draw_text)->get_text(), (INT)iSize, pwritetextfont, rectf, &format, pdraw2dbrush);

         if (bMeasure)
         {

            Gdiplus::RectF box;

            status = pdraw2dgraphics->MeasureString(ptext->get_item(::write_text::font::text::e_size_backend_draw_text)->get_text(), (INT)iSize, pwritetextfont, rectf, &format, &box);

            copy(rectangleParam, box);

         }

      }
      else if (pdraw2dpath)
      {

         throw ::exception(error_not_supported);
         //Gdiplus::Matrix m;

         //status = pdraw2dpath->GetTransform(&m);

         //ap(Gdiplus::Matrix) pmNew = m.Clone();

         //status = pmNew->Translate((Gdiplus::REAL) rectangleParam.left, (Gdiplus::REAL) rectangleParam.top);

         //status = pmNew->Scale((Gdiplus::REAL) m_pwritetextfont->m_dFontWidth, (Gdiplus::REAL) 1.0, Gdiplus::MatrixOrderAppend);

         //Gdiplus::RectF rectf(0, 0, (Gdiplus::REAL) (width(rectangleParam) * m_pwritetextfont->m_dFontWidth), (Gdiplus::REAL) (height(rectangleParam)));

         //status = pdraw2dpath->SetTransform(pmNew);

         //wstring ptext->m_wstr = utf8_to_unicode(str);

         //Gdiplus::Font * pwritetextfont = gdiplus_font();

         //Gdiplus::Brush * pdraw2dbrush = gdiplus_brush();

         //character_count iSize = ptext->m_wstr.get_length();

         //status = pdraw2dpath->AddString(ptext->m_wstr, (INT)iSize, f, nStyle, emSize, rectf, &format);

         //status = pdraw2dpath->SetTransform(m);

      }


      //}
      //catch (...)
      //{

      //}

      //return Gdiplus::Status::Ok;

   }


} // namespace draw2d_gdiplus






