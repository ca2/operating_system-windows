#include "framework.h"
#include "font.h"
#include "graphics.h"
#include "path.h"
#include "brush.h"
#include "acme/exception/exception.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/platform/acme.h"
#include "acme/platform/platform.h"
#include "aura/graphics/draw2d/draw2d.h"
#include "aura/platform/system.h"


namespace draw2d_gdiplus
{


   void graphics::_gdiplus_draw_text(::draw2d::path * ppathParam, const ::scoped_string & scopedstr, double_rectangle & rectangleParam, const ::e_align & ealign, const ::e_draw_text & edrawtext, ::write_text::font * pfontParam, double dFontWidth, ::draw2d::brush * pbrushParam, bool bMeasure)
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

      auto pfont = __font(pfontParam)->get_os_data < Gdiplus::Font * >(this);

      if (::is_null(pfont))
      {

         //return ::error_failed;

         throw ::exception(error_failed);

      }

      Gdiplus::Graphics * pgraphics = m_pgraphics;

      _synchronous_lock synchronouslock(::write_text::font::s_pmutexFontTextMap);

      Gdiplus::GraphicsPath * ppath = nullptr;

      if (::is_set(ppathParam))
      {

         ppath = __graphics_path(ppathParam)->get_os_data < Gdiplus::GraphicsPath * >(this);

      }

      Gdiplus::Brush * pbrush = nullptr;

      if (::is_set(pbrushParam))
      {

         pbrush = __brush(pbrushParam)->get_os_data < Gdiplus::Brush * >(this);

         if (::is_null(pbrush))
         {

            //return ::error_failed;

            throw ::exception(error_failed);

         }

      }

      ASSERT(pgraphics != nullptr || ppath != nullptr);
      ASSERT(pfont != nullptr);
      ASSERT(ppath != nullptr || pbrush != nullptr);

      Gdiplus::Status status = Gdiplus::Status::GenericError;

      Gdiplus::StringFormat format(Gdiplus::StringFormat::GenericTypographic());

      format.SetFormatFlags((format.GetFormatFlags()
         //| Gdiplus::StringFormatFlagsNoClip | Gdiplus::StringFormatFlagsMeasureTrailingSpaces
         | Gdiplus::StringFormatFlagsMeasureTrailingSpaces
         | (edrawtext & DT_SINGLELINE ? Gdiplus::StringFormatFlagsNoWrap : 0))
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
      int nStyle;
      Gdiplus::REAL size;
      Gdiplus::Unit unit;

      if (ppath)
      {

         pfont->GetFamily(&f);
         nStyle = pfont->GetStyle();
         size = pfont->GetSize();
         unit = pfont->GetUnit();

         if (unit == Gdiplus::UnitPoint)
         {

            size = pgraphics->GetDpiY() * size / 73.0f;

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

         Gdiplus::RectF float_rectangle((Gdiplus::REAL)rectangleParam.left(), (Gdiplus::REAL)rectangleParam.top(), (Gdiplus::REAL)(width(rectangleParam) * dFontWidth), (Gdiplus::REAL)(height(rectangleParam)));

         character_count iSize = ptext->get_item(::write_text::font::text::e_size_backend_draw_text)->get_text().length();

         if (ppath)
         {

            status = ppath->AddString(ptext->get_item(::write_text::font::text::e_size_backend_draw_text)->get_text(), (INT)iSize, &f, nStyle, size, float_rectangle, &format);

            if (bMeasure)
            {

               Gdiplus::RectF box;

               status = pgraphics->MeasureString(ptext->get_item(::write_text::font::text::e_size_backend_draw_text)->get_text(), (INT)iSize, pfont, float_rectangle, &format, &box);

               copy(rectangleParam, box);

            }

         }
         else if (pgraphics)
         {

            auto eTextRenderingMode = pgraphics->GetTextRenderingHint();

            auto eCompositingMode = pgraphics->GetCompositingMode();

            if (eCompositingMode == ::Gdiplus::CompositingModeSourceCopy)
            {

               if (eTextRenderingMode != ::Gdiplus::TextRenderingHintAntiAlias)
               {

                  pgraphics->SetTextRenderingHint(::Gdiplus::TextRenderingHintAntiAlias);

               }

            }

            status = pgraphics->DrawString(ptext->get_item(::write_text::font::text::e_size_backend_draw_text)->get_text(), (INT)ptext->get_item(::write_text::font::text::e_size_backend_draw_text)->get_text().length(), pfont, float_rectangle, &format, pbrush);

            if (bMeasure)
            {

               Gdiplus::RectF box;

               status = pgraphics->MeasureString(ptext->get_item(::write_text::font::text::e_size_backend_draw_text)->get_text(), (INT)iSize, pfont, float_rectangle, &format, &box);

               copy(rectangleParam, box);

            }


            if (eCompositingMode == Gdiplus::CompositingModeSourceCopy)
            {

               if (eTextRenderingMode != ::Gdiplus::TextRenderingHintAntiAlias)
               {

                  pgraphics->SetTextRenderingHint(eTextRenderingMode);

               }

            }

         }

         //auto e = pgraphics->GetTextRenderingHint();

         //status = pgraphics->DrawString(ptext->m_wstr, (INT)iSize, pfont, float_rectangle, &format, pbrush);

      //}

      }
      else if (pgraphics)
      {

         g_keep k(pgraphics);

         Gdiplus::Matrix m;

         status = pgraphics->GetTransform(&m);

         auto pmNew = as_auto_pointer(m.Clone());

         status = pmNew->Translate((Gdiplus::REAL)rectangleParam.left(), (Gdiplus::REAL)rectangleParam.top());

         status = pmNew->Scale((Gdiplus::REAL)dFontWidth, (Gdiplus::REAL)1.0, Gdiplus::MatrixOrderAppend);

         Gdiplus::RectF float_rectangle(0, 0, (Gdiplus::REAL)(width(rectangleParam) * dFontWidth), (Gdiplus::REAL)(height(rectangleParam)));

         status = pgraphics->SetTransform(pmNew);

         character_count iSize = ptext->get_item(::write_text::font::text::e_size_backend_draw_text)->get_text().length();

         status = pgraphics->DrawString(ptext->get_item(::write_text::font::text::e_size_backend_draw_text)->get_text(), (INT)iSize, pfont, float_rectangle, &format, pbrush);

         if (bMeasure)
         {

            Gdiplus::RectF box;

            status = pgraphics->MeasureString(ptext->get_item(::write_text::font::text::e_size_backend_draw_text)->get_text(), (INT)iSize, pfont, float_rectangle, &format, &box);

            copy(rectangleParam, box);

         }

      }
      else if (ppath)
      {

         throw ::exception(error_not_supported);
         //Gdiplus::Matrix m;

         //status = ppath->GetTransform(&m);

         //ap(Gdiplus::Matrix) pmNew = m.Clone();

         //status = pmNew->Translate((Gdiplus::REAL) rectangleParam.left(), (Gdiplus::REAL) rectangleParam.top());

         //status = pmNew->Scale((Gdiplus::REAL) m_pfont->m_dFontWidth, (Gdiplus::REAL) 1.0, Gdiplus::MatrixOrderAppend);

         //Gdiplus::RectF float_rectangle(0, 0, (Gdiplus::REAL) (width(rectangleParam) * m_pfont->m_dFontWidth), (Gdiplus::REAL) (height(rectangleParam)));

         //status = ppath->SetTransform(pmNew);

         //wstring ptext->m_wstr = utf8_to_unicode(str);

         //Gdiplus::Font * pfont = gdiplus_font();

         //Gdiplus::Brush * pbrush = gdiplus_brush();

         //character_count iSize = ptext->m_wstr.get_length();

         //status = ppath->AddString(ptext->m_wstr, (INT)iSize, f, nStyle, emSize, float_rectangle, &format);

         //status = ppath->SetTransform(m);

      }


      //}
      //catch (...)
      //{

      //}

      //return Gdiplus::Status::Ok;

   }


} // namespace draw2d_gdiplus






