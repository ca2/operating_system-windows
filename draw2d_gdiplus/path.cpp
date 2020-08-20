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


   bool path::internal_begin_figure()
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


   bool path::close_figure()
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

      m_bHasPointInternal = false;

      return true;

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


   //bool path::internal_add_line(double x, double y)
   //{

   //   bool bOk1 = true;

   //   if(m_bHasPointInternal)
   //   {

   //      if (almost_integer(m_pointInternal.X)
   //            && almost_integer(m_pointInternal.Y)
   //            && almost_integer(x)
   //            && almost_integer(y))
   //      {

   //         bOk1 = m_ppath->AddLine((INT) m_pointInternal.X, (INT)m_pointInternal.Y, (INT)x, (INT)y) == Gdiplus::Status::Ok;

   //      }
   //      else
   //      {

   //         bOk1 = m_ppath->AddLine((FLOAT)m_pointInternal.X, (FLOAT) m_pointInternal.Y, (FLOAT)x, (FLOAT)y) == Gdiplus::Status::Ok;

   //      }

   //   }

   //   m_bHasPointInternal = true;

   //   m_pointInternal.X = (Gdiplus::REAL) x;
   //   m_pointInternal.Y = (Gdiplus::REAL) y;

   //   return bOk1;

   //}

   pointd path::internal_current_point()
   {

      return get_current_point();

   }


   //bool path::internal_add_move(double x, double y)
   //{

   //   if(!m_bHasPointInternal)
   //   {
   //      //internal_begin_figure(m_bFill,m_efillmode);

   //      internal_begin_figure();

   //   }

   //   m_pointInternal.X   = (Gdiplus::REAL) x;
   //   m_pointInternal.Y   = (Gdiplus::REAL) y;
   //   m_bHasPointInternal     = true;
   //   m_bHasPath = false;


   //   return true;

   //}


   bool path::create(::draw2d::graphics * pgraphicsParam, ::i8 iCreate)
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

      //for(i32 i = 0; i < m_elementa.get_count(); i++)
      //{

        // set(pgraphicsParam, m_elementa(i));

      //}

      _set_create(pgraphicsParam);

      m_osdata[0] = m_ppath;

      return true;

   }


   void path::destroy()
   {

      ::aura::del(m_ppath);

   }



   bool path::internal_add_arc(const ::rectd & rect, const ::angle& angleBeg, const ::angle& angleEnd)
   {

      if (m_ppath == nullptr)
      {

         return false;

      }

      try
      {


         ::Gdiplus::RectF rectf((Gdiplus::REAL) rect.left, (Gdiplus::REAL) rect.top, (Gdiplus::REAL) width(rect), (Gdiplus::REAL) height(rect));


         m_ppath->AddArc(rectf, (Gdiplus::REAL) angleBeg.degree(), (Gdiplus::REAL) (angleEnd - angleBeg).degree());

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


   bool path::internal_add_text_out(::draw2d::graphics * pgraphics,i32 x,i32 y,const string & strText,::draw2d::font * pfont)
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

   
   bool path::_set(::draw2d::graphics* pgraphics, ::draw2d::path::begin* pbegin)
   {


      return true;

   }


   bool path::_set(::draw2d::graphics * pgraphics, ::draw2d::path::arc * parc)
   {

      ::rectd rect;

      rect.left      = parc->m_pointCenter.x - parc->m_sizeRadius.cx;
      rect.right     = parc->m_pointCenter.x + parc->m_sizeRadius.cx;
      rect.top       = parc->m_pointCenter.y - parc->m_sizeRadius.cy;
      rect.bottom    = parc->m_pointCenter.y + parc->m_sizeRadius.cy;

      //if (!m_bHasPath && m_bHasPointInternal)
      //{

      //   internal_add_line(parc->m_pointBeg.x, parc->m_pointBeg.y);

      //}

      bool bOk = internal_add_arc(rect,parc->m_angleBeg, parc->m_angleEnd);

      return bOk;

   }


   bool path::_set(::draw2d::graphics * pgraphics, ::draw2d::path::rect * prect)
   {

      return internal_add_rect(
         prect->m_rect.left, prect->m_rect.top, 
         prect->m_rect.width(), prect->m_rect.height());

   }


   bool path::_set(::draw2d::graphics * pgraphics, ::draw2d::path::line * pline)
   {

      return internal_add_line(
         pline->m_pointBeg.x, pline->m_pointBeg.y,
         pline->m_pointEnd.x, pline->m_pointEnd.y);

   }


   bool path::_set(::draw2d::graphics* pgraphics, ::draw2d::path::lines* plines)
   {

      ::array < Gdiplus::PointF > pointa;
      
      pointa.set_size(plines->m_pointa.get_count());

      for (::index i = 0; i < pointa.get_size(); i++)
      {

         __copy(pointa[i], plines->m_pointa[i]);

      }

      m_ppath->AddLines(pointa.get_data(), pointa.get_count());

      return true;

   }



   bool path::_set(::draw2d::graphics* pgraphics, ::draw2d::path::polygon * ppolygon)
   {

      ::array < Gdiplus::PointF > pointa;

      pointa.set_size(ppolygon->m_pointa.get_count());

      for (::index i = 0; i < pointa.get_size(); i++)
      {

         __copy(pointa[i], ppolygon->m_pointa[i]);

      }

      m_ppath->AddPolygon(pointa.get_data(), pointa.get_count());

      return true;


   }



   bool path::_set(::draw2d::graphics* pgraphics, ::draw2d::path::text_out* ptextout)
   {

      return internal_add_text_out(
         pgraphics,
         (i32)ptextout->m_point.x,
         (i32)ptextout->m_point.y,
         ptextout->m_strText,
         ptextout->m_pfont);

   }


   bool path::_set(::draw2d::graphics* pgraphics, ::draw2d::path::draw_text * pdrawtext)
   {

      return internal_add_draw_text(
         pgraphics,
         pdrawtext->m_rect, 
         pdrawtext->m_strText, 
         pdrawtext->m_pfont, 
         pdrawtext->m_iDrawTextFlags);

   }


   bool path::_set(::draw2d::graphics* pgraphics, ::draw2d::path::close * pclose)
   {


      return true;

   }



   bool path::contains(::draw2d::graphics_pointer& pgraphics, const pointd& point)
   {

      return ::draw2d::path::contains(pgraphics, point);

      auto pospath = get_os_data <GraphicsPath *>(pgraphics);

      if (is_null(pospath))
      {

         return false;

      }

      Gdiplus::PointF p((FLOAT) point.x, (FLOAT) point.y);

      return pospath->IsVisible(p);

   }

} // namespace draw2d_gdiplus


