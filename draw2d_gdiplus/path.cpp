#include "framework.h"


#undef new


bool almost_integer(double d)
{

   if (fmod(fabs(d), 1.0) < 0.01)
   {

      return true;

   }

   return false;
}

namespace draw2d_gdiplus
{



   path::path()
   {

      m_pthis = this;
      m_ppath = nullptr;
      m_bHasPath = false;

   }


   path::~path()
   {

      destroy();

   }



   pointd path::internal_last_point()
   {

      if(m_bHasPointInternal)
      {

         return pointd((LONG) m_pointInternal.X, (LONG) m_pointInternal.Y);

      }
      else
      {

         throw ::exception::exception("path does not have last point");

      }

   }


   bool path::internal_begin_figure(bool bFill, ::draw2d::e_fill_mode efillmode)
   {

      if (m_ppath == nullptr)
      {

         return false;

      }

      try
      {

         return m_ppath->StartFigure() == Gdiplus::Status::Ok;

      }
      catch (...)
      {


      }


      return false;

   }

   bool path::internal_end_figure(bool bClose)
   {



      if(bClose)
      {

         if (m_ppath == nullptr)
         {

            return false;

         }

         try
         {

            m_bHasPointInternal = false;

            return m_ppath->CloseFigure() == Gdiplus::Status::Ok;

         }
         catch (...)
         {


         }

         return false;


      }
      else
      {
         m_bHasPointInternal = false;
         return true;

      }

   }

   bool path::internal_add_line(double x1, double y1, double x2, double y2)
   {


      if (m_ppath == nullptr)
      {

         return false;

      }

      bool bOk1 = false;

      bool bOk2 = false;

      try
      {

         bOk1 = true;

         if (m_bHasPointInternal)
         {
            if (almost_integer(m_pointInternal.X)
                  && almost_integer(m_pointInternal.Y)
                  && almost_integer(x1)
                  && almost_integer(x2))
            {

               bOk1 = m_ppath->AddLine((INT) m_pointInternal.X, (INT)m_pointInternal.Y, (INT)x1, (INT)y1) == Gdiplus::Status::Ok;

            }
            else
            {

               bOk1 = m_ppath->AddLine(m_pointInternal.X, m_pointInternal.Y, (FLOAT)x1, (FLOAT)y1) == Gdiplus::Status::Ok;

            }

         }

         if (bOk1)
         {

            if (almost_integer(m_pointInternal.X)
                  && almost_integer(m_pointInternal.Y)
                  && almost_integer(x1)
                  && almost_integer(x2))
            {

               bOk2 = m_ppath->AddLine((INT) x1, (INT) y1, (INT) x2, (INT) y2) == Gdiplus::Status::Ok;

            }
            else
            {

               bOk2 = m_ppath->AddLine((FLOAT)x1, (FLOAT)y1, (FLOAT)x2, (FLOAT)y2) == Gdiplus::Status::Ok;

            }

         }

         m_pointInternal.X = (Gdiplus::REAL) x2;
         m_pointInternal.Y = (Gdiplus::REAL) y2;

         m_bHasPointInternal = true;

      }
      catch (...)
      {

      }

      return bOk1 && bOk2;

   }


   bool path::internal_add_rect(double x,double y, double cx, double cy)
   {

      if (m_ppath == nullptr)
      {

         return false;

      }

      bool bOk2 = false;

      if (almost_integer(x) && almost_integer(cx) && almost_integer(y) && almost_integer(cy))
      {

         Gdiplus::Rect rect(
         (INT) (x),
         (INT)(y),
         (INT)(cx),
         (INT)(cy)
         );

         try
         {

            bOk2 = m_ppath->AddRectangle(rect) == Gdiplus::Status::Ok;

         }
         catch (...)
         {


         }

      }
      else
      {

         Gdiplus::RectF rect(
         (float)(x),
         (float)(y),
         (float)(cx),
         (float)(cy)
         );

         try
         {

            bOk2 = m_ppath->AddRectangle(rect) == Gdiplus::Status::Ok;

         }
         catch (...)
         {


         }
      }

      return bOk2;

   }

   bool path::internal_add_line(double x, double y)
   {

      bool bOk1 = true;

      if(m_bHasPointInternal)
      {

         if (almost_integer(m_pointInternal.X)
               && almost_integer(m_pointInternal.Y)
               && almost_integer(x)
               && almost_integer(y))
         {

            bOk1 = m_ppath->AddLine((INT) m_pointInternal.X, (INT)m_pointInternal.Y, (INT)x, (INT)y) == Gdiplus::Status::Ok;

         }
         else
         {

            bOk1 = m_ppath->AddLine((FLOAT)m_pointInternal.X, (FLOAT) m_pointInternal.Y, (FLOAT)x, (FLOAT)y) == Gdiplus::Status::Ok;

         }

      }

      m_bHasPointInternal = true;

      m_pointInternal.X = (Gdiplus::REAL) x;
      m_pointInternal.Y = (Gdiplus::REAL) y;

      return bOk1;

   }

   pointd path::internal_current_point()
   {

      return last_point();

   }


   bool path::internal_add_move(double x, double y)
   {

      if(!m_bHasPointInternal)
      {
         internal_begin_figure(m_bFill,m_efillmode);
      }

      m_pointInternal.X   = (Gdiplus::REAL) x;
      m_pointInternal.Y   = (Gdiplus::REAL) y;
      m_bHasPointInternal     = true;
      m_bHasPath = false;


      return true;

   }


   bool path::create(::draw2d::graphics * pgraphicsParam)
   {

      auto pgdiplusgraphics = __graphics(pgraphicsParam);

      if (::is_null(pgdiplusgraphics))
      {

         return false;

      }

      auto pgraphics = pgdiplusgraphics->m_pgraphics;

      if (::is_null(pgraphics))
      {

         return false;

      }

      if(m_efillmode == ::draw2d::fill_mode_winding)
      {

         m_ppath = new Gdiplus::GraphicsPath(Gdiplus::FillModeWinding);

      }
      else
      {

         m_ppath = new Gdiplus::GraphicsPath(Gdiplus::FillModeAlternate);

      }

      m_bHasPoint = false;

      m_pointInternal.X = 69;

      m_pointInternal.Y = 69;

      m_bHasPointInternal = false;

      //if(m_elementa.get_count() != 1 && m_elementa[0].m_etype != element::type_string)
      {
         //internal_begin_figure(m_bFill,m_efillmode);
      }

      for(i32 i = 0; i < m_elementa.get_count(); i++)
      {

         set(pgraphicsParam, m_elementa(i));

      }

      m_osdata[0] = m_ppath;

      return true;

   }


   void path::destroy()
   {

      ::aura::del(m_ppath);

   }


   bool path::set(::draw2d::graphics * pgraphics, const ::draw2d::path::element & e)
   {

      switch(e.m_etype)
      {
      case ::draw2d::path::element::type_arc:
         set(pgraphics, e.u.m_arc);
         break;
      case ::draw2d::path::element::type_move:
         set(pgraphics, e.u.m_move);
         break;
      case ::draw2d::path::element::type_line:
         set(pgraphics, e.u.m_line);
         break;
      case ::draw2d::path::element::type_rect:
         set(pgraphics, e.u.m_rect);
         break;
      case ::draw2d::path::element::type_string:
      case ::draw2d::path::element::type_draw_text:
         set(pgraphics,e.m_etype, e.m_stringpath);
         break;
      case ::draw2d::path::element::type_end:
         internal_end_figure(e.u.m_end.m_bClose);
         break;
      default:
         throw "unexpected simple os graphics element type";
      }

      return false;

   }

   bool path::internal_add_arc(const ::rect & rect, double iStart, double iAngle)
   {

      if (m_ppath == nullptr)
      {

         return false;

      }

      try
      {


         ::Gdiplus::RectF rectf((Gdiplus::REAL) rect.left, (Gdiplus::REAL) rect.top, (Gdiplus::REAL) width(rect), (Gdiplus::REAL) height(rect));


         m_ppath->AddArc(rectf, (Gdiplus::REAL) iStart, (Gdiplus::REAL) iAngle);

         ::Gdiplus::PointF point;

         m_ppath->GetLastPoint(&point);

         m_pointInternal.X = point.X;
         m_pointInternal.Y = point.Y;

      }
      catch (...)
      {

      }

      return true;

   }


   bool path::internal_add_string(::draw2d::graphics * pgraphics,i32 x,i32 y,const string & strText,::draw2d::font * pfont)
   {

      if (m_ppath == nullptr)
      {

         return false;

      }

      try
      {

         Gdiplus::FontFamily fontFamily;

         Gdiplus::StringFormat format(Gdiplus::StringFormat::GenericTypographic());

         wstring wstr(strText);

         Gdiplus::REAL dSize = (Gdiplus::REAL) pfont->m_dFontSize;

         Gdiplus::Unit unit = __graphics(pgraphics)->m_pgraphics->GetPageUnit();

         switch (unit)
         {

         case Gdiplus::UnitMillimeter:
            dSize = dSize * 25.4f / __graphics(pgraphics)->m_pgraphics->GetDpiY();
            break;

         case Gdiplus::UnitInch:

            dSize = dSize / __graphics(pgraphics)->m_pgraphics->GetDpiY();
            break;
         case Gdiplus::UnitPoint:

            dSize = dSize * 72.0f / __graphics(pgraphics)->m_pgraphics->GetDpiY();
            break;

         }

         auto pdrawdgdiplusfont = __font(pfont);

         auto pfont = pdrawdgdiplusfont->get_os_data < Font * > (pgraphics);

         INT iStyle = pfont->GetStyle();

         pfont->GetFamily(&fontFamily);
         //      Gdiplus::Status status;

         //Gdiplus::StringFormat format();

         format.SetFormatFlags(format.GetFormatFlags()
                               | Gdiplus::StringFormatFlagsNoClip | Gdiplus::StringFormatFlagsMeasureTrailingSpaces
                               | Gdiplus::StringFormatFlagsLineLimit | Gdiplus::StringFormatFlagsNoWrap
                               | Gdiplus::StringFormatFlagsNoFitBlackBox);


         format.SetLineAlignment(Gdiplus::StringAlignmentNear);


         m_ppath->AddString(wstr, (INT)wstr.get_length(), &fontFamily, iStyle, dSize, Gdiplus::Point(x, y), &format);

      }
      catch (...)
      {

      }

      return true;

   }


   bool path::internal_add_draw_text(::draw2d::graphics * pgraphics, const ::rect & rectParam, const string & strText, ::draw2d::font * pfont, int nFormat)
   {

      ::rectd rect(rectParam);

      auto estatus = gdiplus_draw_text(pgraphics, this, strText, rect, nFormat, pfont, 1.0);

      return !estatus;

   }


   bool path::set(::draw2d::graphics * pgraphics, const ::draw2d::path::arc & arc)
   {

      ::rect rect;

      rect.left = (LONG)(arc.m_pointCenter.x - arc.m_sizeRadius.cx);
      rect.right = (LONG)(arc.m_pointCenter.x + arc.m_sizeRadius.cx);
      rect.top = (LONG)(arc.m_pointCenter.y - arc.m_sizeRadius.cy);
      rect.bottom = (LONG)(arc.m_pointCenter.y + arc.m_sizeRadius.cy);
      //if(!m_bHasPointInternal)
      //{

      //   internal_add_move(arc.m_pointEnd.x,arc.m_pointEnd.y);

      //}
      if (!m_bHasPath && m_bHasPointInternal)
      {

         internal_add_line(arc.m_pointStart.x, arc.m_pointStart.y);

      }


      bool bOk = internal_add_arc(rect,(int)(arc.m_dAngle1 * 180.0 / 3.1415),(int)(arc.m_dAngle* 180.0 / 3.1415));


      return bOk;

   }


   bool path::set(::draw2d::graphics * pgraphics, const ::draw2d::path::rect & rect)
   {

      return internal_add_rect(rect.m_x, rect.m_y, rect.m_cx, rect.m_cy);

   }


   bool path::set(::draw2d::graphics * pgraphics, const ::draw2d::path::line & l)
   {

      internal_add_line(l.m_x, l.m_y);

      return true;

   }


   bool path::set(::draw2d::graphics * pgraphics, const ::draw2d::path::move & point)
   {

      internal_add_move((i32) point.m_x, (i32) point.m_y);


      return true;

   }

   bool path::set(::draw2d::graphics * pgraphics, ::draw2d::path::element::e_type etype, const ::draw2d::path::string_path & s)
   {

      switch (etype)
      {
      case ::draw2d::path::element::type_string:
         internal_add_string(pgraphics, (i32)s.m_x, (i32)s.m_y, s.m_strText, s.m_pfont);
         break;
      case ::draw2d::path::element::type_draw_text:
         internal_add_draw_text(pgraphics, s.m_rect, s.m_strText, s.m_pfont, s.m_iDrawTextFlags);
         break;
      default:
         __throw(not_supported_exception());
         break;
      }



      return true;

   }


   bool path::contains(::draw2d::graphics_pointer& pgraphics, const pointd& point)
   {

      auto pospath = get_os_data <GraphicsPath *>(pgraphics);

      if (is_null(pospath))
      {

         return false;

      }

      Gdiplus::PointF p(point.x, point.y);

      return pospath->IsVisible(p);

   }

} // namespace draw2d_gdiplus


