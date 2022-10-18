#include "framework.h"
#include "region.h"
#include "graphics.h"


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


   bool region::translate(const POINT_I32& point, ::draw2d::graphics * pgraphics)
   {

      return true;

   }


   bool region::get_bounding_box(RECTANGLE_I32 * prectangle, ::draw2d::graphics * pgraphics)
   {

      defer_update(pgraphics, 0);

      Gdiplus::Rect rectangle;

      m_pregion->GetBounds(&rectangle, __graphics(pgraphics)->m_pgraphics);

      prectangle->left = rectangle.X;

      prectangle->top = rectangle.Y;

      prectangle->right = rectangle.X + rectangle.Width;

      prectangle->bottom = rectangle.Y + rectangle.Height;


      return true;

   }



   void region::max_bounding_box(RECTANGLE_F64 * prectangle, ::draw2d::graphics * pgraphics)
   {

      ::rectangle_i32 rectangle;
      ((region*)this)->get_bounding_box(rectangle);
      copy(prectangle, &rectangle);

   }


   bool region::contains(const POINT_I32 & point, ::draw2d::graphics * pgraphics)
   {

      defer_update(pgraphics, 0);

      if (!m_pregion)
      {

         return ::draw2d::region::contains(point, pgraphics);

      }

      Gdiplus::PointF pointf((Gdiplus::REAL) point.x, (Gdiplus::REAL) point.y);

      return m_pregion->IsVisible(pointf)  != false;

   }


   void region::create(::draw2d::graphics * pgraphics, ::i8 iCreate)
   {

      m_pregion = get(pgraphics);

      m_osdata[0] = m_pregion;

      //return m_pregion != nullptr;

   }


   void region::destroy()
   {

      ::acme::del(m_pregion);

      ::draw2d::region::destroy();

      //return ::success;
   
   }


   Gdiplus::Region * region::get(::draw2d::graphics * pgraphics)
   {

      switch(m_eregion)
      {
      case ::draw2d::e_region_none:
      {

         return new Gdiplus::Region();

      }
      case ::draw2d::e_region_rect:
         return get_rectangle(pgraphics);
      case ::draw2d::e_region_ellipse:
         return get_ellipse(pgraphics);
      case ::draw2d::e_region_polygon:
         return get_polygon(pgraphics);
      case ::draw2d::e_region_poly_polygon:
         return get_polygon(pgraphics);
      case ::draw2d::e_region_combine:
         return get_combine(pgraphics);
      default:
         throw ::interface_only();
      }

      return nullptr;

   }


   Gdiplus::Region * region::get_rectangle(::draw2d::graphics * pgraphics)
   {

      Gdiplus::GraphicsPath path;

      Gdiplus::RectF rectangle;

      ::pointer<rectangle_item>pitem = m_pitem;

      copy(&rectangle, &pitem->m_rectangle);

      path.AddRectangle(rectangle);

      return new Gdiplus::Region(&path);

   }


   Gdiplus::Region * region::get_ellipse(::draw2d::graphics * pgraphics)
   {

      Gdiplus::GraphicsPath path;


      ::pointer<ellipse_item>pitem = m_pitem;

      path.AddEllipse((INT) pitem->m_rectangle.left,
         (INT) pitem->m_rectangle.top,
         (INT) pitem->m_rectangle.width(),
         (INT) pitem->m_rectangle.height());

      return new Gdiplus::Region(&path);

   }


   Gdiplus::Region * region::get_polygon(::draw2d::graphics * pgraphics)
   {

      Gdiplus::GraphicsPath path;

      array < Gdiplus::PointF > pa;

      ::pointer<polygon_item>pitem = m_pitem;

      for(i32 i = 0; i < pitem->m_polygon.get_size(); i++)
      {
         pa.add(Gdiplus::PointF((Gdiplus::REAL) pitem->m_polygon[i].x, (Gdiplus::REAL) pitem->m_polygon[i].y));
      }

      if(pitem->m_efillmode == ::draw2d::e_fill_mode_alternate)
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

      ::pointer<poly_polygon_item>pitem = m_pitem;

      if(pitem->m_efillmode == ::draw2d::e_fill_mode_alternate)
      {
         path.SetFillMode(Gdiplus::FillModeAlternate);
      }
      else
      {
         path.SetFillMode(Gdiplus::FillModeWinding);
      }

      i32 n = 0;

      for(i32 i = 0; i < pitem->m_polygona.get_size(); i++)
      {

         auto & polygon = *pitem->m_polygona[i];
            
         auto jCount = polygon.get_size();

         pa.erase_all();

         for(i32 j = 0; j < jCount; j++)
         {

            pa.add(Gdiplus::PointF((Gdiplus::REAL) polygon[n].x, (Gdiplus::REAL) polygon[n].y));

            n++;

         }

         path.AddPolygon(pa.get_data(), (i32) pa.get_count());

         path.CloseFigure();

      }

      return new Gdiplus::Region(&path);

   }


   Gdiplus::Region * region::get_combine(::draw2d::graphics * pgraphics)
   {

      ::pointer<combine_item>pitem = m_pitem;

      if (!pitem->m_pregion1 || !pitem->m_pregion2)
      {

         return nullptr;

      }

      Gdiplus::Region * pregion = pitem->m_pregion1->get_os_data < Gdiplus::Region *>(pgraphics)->Clone();

      Gdiplus::Region * pregionOp = pitem->m_pregion2->get_os_data < Gdiplus::Region *>(pgraphics);

      if(pitem->m_ecombine == ::draw2d::e_combine_add)
      {
         pregion->Union(pregionOp);
      }
      else if(pitem->m_ecombine == ::draw2d::e_combine_exclude)
      {
         pregion->Exclude(pregionOp);
      }
      else if(pitem->m_ecombine == ::draw2d::e_combine_intersect)
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



