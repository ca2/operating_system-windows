#include "framework.h"
#include "font.h"
#include "graphics.h"
#include "path.h"
#include "brush.h"
#include "acme/exception/exception.h"


void gdiplus_draw_text(::draw2d::graphics* pgraphicsParam, ::draw2d::path* ppathParam, const string& str, rectangle_f64& rectangleParam, const ::e_align & ealign, const ::e_draw_text & edrawtext, ::write_text::font* pfontParam, double dFontWidth, ::draw2d::brush* pbrushParam, bool bMeasure)
{

   if (str.is_empty())
   {

      //return ::success;

      return;

   }

   if (::is_null(pfontParam))
   {

      throw ::exception(error_failed);

   }

   auto pfont = __font(pfontParam)->get_os_data < Gdiplus::Font * >(pgraphicsParam);

   if (::is_null(pfont))
   {

      //return ::error_failed;

      throw ::exception(error_failed);

   }

   Gdiplus::Graphics* pgraphics = nullptr;

   if (::is_set(pgraphicsParam))
   {

      pgraphics = __graphics(pgraphicsParam)->m_pgraphics;

   }

   Gdiplus::GraphicsPath* ppath = nullptr;

   if (::is_set(ppathParam))
   {

      ppath = __graphics_path(ppathParam)->get_os_data < Gdiplus::GraphicsPath * >(pgraphicsParam);

   }

   Gdiplus::Brush* pbrush = nullptr;

   if (::is_set(pbrushParam))
   {

      pbrush = __brush(pbrushParam)->get_os_data < Gdiplus::Brush * >(pgraphicsParam);

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

      auto& text = pfontParam->m_mapText[str];

      if (text.m_wstr.is_empty())
      {

         text.m_wstr = str;

      }

      if (dFontWidth == 1.0)
      {

         Gdiplus::RectF rectangle_f32((Gdiplus::REAL) rectangleParam.left, (Gdiplus::REAL) rectangleParam.top, (Gdiplus::REAL) (width(rectangleParam) * dFontWidth), (Gdiplus::REAL) (height(rectangleParam)));

         strsize iSize = text.m_wstr.get_length();

         if (ppath)
         {

            status = ppath->AddString(text.m_wstr, (INT)iSize, &f, nStyle, size, rectangle_f32, &format);

            if (bMeasure)
            {

               Gdiplus::RectF box;

               status = pgraphics->MeasureString(text.m_wstr, (INT)iSize, pfont, rectangle_f32, &format, &box);

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

            status = pgraphics->DrawString(text.m_wstr, (INT)text.m_wstr.get_length(), pfont, rectangle_f32, &format, pbrush);

            if (bMeasure)
            {

               Gdiplus::RectF box;

               status = pgraphics->MeasureString(text.m_wstr, (INT)iSize, pfont, rectangle_f32, &format, &box);

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

            //status = pgraphics->DrawString(text.m_wstr, (INT)iSize, pfont, rectangle_f32, &format, pbrush);

         //}

      }
      else if (pgraphics)
      {

         g_keep k(pgraphics);

         Gdiplus::Matrix m;

         status = pgraphics->GetTransform(&m);

         auto pmNew = __auto(m.Clone());

         status = pmNew->Translate((Gdiplus::REAL) rectangleParam.left, (Gdiplus::REAL) rectangleParam.top);

         status = pmNew->Scale((Gdiplus::REAL) dFontWidth, (Gdiplus::REAL) 1.0, Gdiplus::MatrixOrderAppend);

         Gdiplus::RectF rectangle_f32(0, 0, (Gdiplus::REAL) (width(rectangleParam) * dFontWidth), (Gdiplus::REAL) (height(rectangleParam)));

         status = pgraphics->SetTransform(pmNew);

         strsize iSize = text.m_wstr.get_length();

         status = pgraphics->DrawString(text.m_wstr, (INT)iSize, pfont, rectangle_f32, &format, pbrush);

         if (bMeasure)
         {

            Gdiplus::RectF box;

            status = pgraphics->MeasureString(text.m_wstr, (INT)iSize, pfont, rectangle_f32, &format, &box);

            copy(rectangleParam, box);

         }

      }
      else if (ppath)
      {

         throw ::exception(error_not_supported);
         //Gdiplus::Matrix m;

         //status = ppath->GetTransform(&m);

         //ap(Gdiplus::Matrix) pmNew = m.Clone();

         //status = pmNew->Translate((Gdiplus::REAL) rectangleParam.left, (Gdiplus::REAL) rectangleParam.top);

         //status = pmNew->Scale((Gdiplus::REAL) m_pfont->m_dFontWidth, (Gdiplus::REAL) 1.0, Gdiplus::MatrixOrderAppend);

         //Gdiplus::RectF rectangle_f32(0, 0, (Gdiplus::REAL) (width(rectangleParam) * m_pfont->m_dFontWidth), (Gdiplus::REAL) (height(rectangleParam)));

         //status = ppath->SetTransform(pmNew);

         //wstring text.m_wstr = utf8_to_unicode(str);

         //Gdiplus::Font * pfont = gdiplus_font();

         //Gdiplus::Brush * pbrush = gdiplus_brush();

         //strsize iSize = text.m_wstr.get_length();

         //status = ppath->AddString(text.m_wstr, (INT)iSize, f, nStyle, emSize, rectangle_f32, &format);

         //status = ppath->SetTransform(m);

      }


   //}
   //catch (...)
   //{

   //}

   //return Gdiplus::Status::Ok;

}


