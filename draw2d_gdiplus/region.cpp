#include "framework.h"


#undef new


namespace draw2d_gdiplus
{


   region::region()
   {

      m_pthis = this;
      m_pregion = nullptr;

   }


   region::~region()
   {

      destroy();

   }


   bool region::translate(const POINT& point, ::draw2d::graphics * pgraphics)
   {

      return true;

   }


   bool region::get_bounding_box(RECT * prect, ::draw2d::graphics * pgraphics)
   {

      defer_update(pgraphics);

      Gdiplus::Rect rect;

      m_pregion->GetBounds(&rect, __graphics(pgraphics)->m_pgraphics);

      prect->left = rect.X;

      prect->top = rect.Y;

      prect->right = rect.X + rect.Width;

      prect->bottom = rect.Y + rect.Height;


      return true;

   }



   void region::max_bounding_box(RECTD * prect, ::draw2d::graphics * pgraphics)
   {

      ::rect rect;
      ((region*)this)->get_bounding_box(rect);
      __copy(prect, rect);

   }


   bool region::contains(const POINT & point, ::draw2d::graphics * pgraphics)
   {

      defer_update(pgraphics);

      if (!m_pregion)
      {

         return ::draw2d::region::contains(point, pgraphics);

      }

      Gdiplus::PointF pointf((Gdiplus::REAL) point.x, (Gdiplus::REAL) point.y);

      return m_pregion->IsVisible(pointf)  != FALSE;

   }


   bool region::create(::draw2d::graphics * pgraphics)
   {

      m_pregion = get(pgraphics);

      m_osdata[0] = m_pregion;

      return m_pregion != nullptr;

   }


   void region::destroy()
   {

      ::aura::del(m_pregion);

      ::draw2d::region::destroy();

   }


   Gdiplus::Region * region::get(::draw2d::graphics * pgraphics)
   {

      switch(m_etype)
      {
      case type_none:
         return new Gdiplus::Region();
      case type_rect:
         return get_rect(pgraphics);
      case type_oval:
         return get_oval(pgraphics);
      case type_polygon:
         return get_polygon(pgraphics);
      case type_poly_polygon:
         return get_polygon(pgraphics);
      case type_combine:
         return get_combine(pgraphics);
      default:
         ::exception::throw_not_implemented();
      }

      return nullptr;

   }

   Gdiplus::Region * region::get_rect(::draw2d::graphics * pgraphics)
   {

      Gdiplus::GraphicsPath path;

      Gdiplus::RectF rect;

      rect.X      = (Gdiplus::REAL) m_x1;
      rect.Y      = (Gdiplus::REAL) m_y1;
      rect.Width  = (Gdiplus::REAL) (m_x2 - m_x1);
      rect.Height = (Gdiplus::REAL) (m_y2 - m_y1);

      path.AddRectangle(rect);

      return new Gdiplus::Region(&path);

   }


   Gdiplus::Region * region::get_oval(::draw2d::graphics * pgraphics)
   {

      Gdiplus::GraphicsPath path;

      path.AddEllipse((INT) m_x1, (INT) m_y1, (INT) (m_x2 - m_x1), (INT) (m_y2 - m_y1));

      return new Gdiplus::Region(&path);

   }


   Gdiplus::Region * region::get_polygon(::draw2d::graphics * pgraphics)
   {

      Gdiplus::GraphicsPath path;

      array < Gdiplus::PointF > pa;

      for(i32 i = 0; i < m_nCount; i++)
      {
         pa.add(Gdiplus::PointF((Gdiplus::REAL) m_lppoints[i].x, (Gdiplus::REAL) m_lppoints[i].y));
      }

      if(m_efillmode == ::draw2d::fill_mode_alternate)
      {
         path.SetFillMode(Gdiplus::FillModeAlternate);
      }
      else
      {
         path.SetFillMode(Gdiplus::FillModeWinding);
      }

      path.AddPolygon(pa.get_data(), (i32) pa.get_count());

      return new Gdiplus::Region(&path);

   }


   Gdiplus::Region * region::get_poly_polygon(::draw2d::graphics * pgraphics)
   {

      Gdiplus::GraphicsPath path;

      array < Gdiplus::PointF > pa;

      if(m_efillmode == ::draw2d::fill_mode_alternate)
      {
         path.SetFillMode(Gdiplus::FillModeAlternate);
      }
      else
      {
         path.SetFillMode(Gdiplus::FillModeWinding);
      }

      i32 n = 0;

      for(i32 i = 0; i < m_nCount; i++)
      {
         i32 jCount = m_lppolycounts[i];
         pa.remove_all();
         for(i32 j = 0; j < jCount; j++)
         {
            pa.add(Gdiplus::PointF((Gdiplus::REAL) m_lppoints[n].x, (Gdiplus::REAL) m_lppoints[n].y));
            n++;
         }
         path.AddPolygon(pa.get_data(), (i32) pa.get_count());
         path.CloseFigure();
      }

      return new Gdiplus::Region(&path);

   }


   Gdiplus::Region * region::get_combine(::draw2d::graphics * pgraphics)
   {

      if (!m_pregion1 || !m_pregion2)
      {

         return nullptr;

      }

      Gdiplus::Region * pregion = m_pregion1->get_os_data <Region *>(pgraphics)->Clone();

      Gdiplus::Region * pregionOp = m_pregion2->get_os_data<Region *>(pgraphics);

      if(m_ecombine == combine_add)
      {
         pregion->Union(pregionOp);
      }
      else if(m_ecombine == combine_exclude)
      {
         pregion->Exclude(pregionOp);
      }
      else if(m_ecombine == combine_intersect)
      {
         pregion->Intersect(pregionOp);
      }
      else
      {
         pregion->Union(pregionOp);
      }

      return pregion;

   }


} // namespace draw2d_gdiplus



