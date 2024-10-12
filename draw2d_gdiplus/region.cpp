#include "framework.h"
#include "region.h"
#include "graphics.h"
#include "acme/exception/interface_only.h"
#include "acme/prototype/geometry2d/item.h"
#include "acme/prototype/geometry2d/_defer_item.h"


//#undef __new


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


   bool region::translate(const ::point_i32& point, ::draw2d::graphics * pgraphics)
   {

      return true;

   }


   bool region::get_bounding_box(::rectangle_i32 & rectangle, ::draw2d::graphics * pgraphics)
   {

      defer_update(pgraphics, 0);

      Gdiplus::Rect gdiplusrectangle;

      m_pregion->GetBounds(&gdiplusrectangle, __graphics(pgraphics)->m_pgraphics);

      copy(rectangle, gdiplusrectangle);

      return true;

   }


   void region::expand_bounding_box(::rectangle_f64 & rectangle, ::draw2d::graphics * pgraphics)
   {

      ::rectangle_i32 rectanglei32;

      ((region*)this)->get_bounding_box(rectanglei32, pgraphics);

      rectangle = rectanglei32;

   }


   bool region::contains(const ::point_i32 & point, ::draw2d::graphics * pgraphics)
   {

      defer_update(pgraphics, 0);

      if (!m_pregion)
      {

         return ::draw2d::region::contains(point, pgraphics);

      }

      Gdiplus::PointF pointf((Gdiplus::REAL) point.x(), (Gdiplus::REAL) point.y());

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

      auto eitem = this->m_pitem->type();

      switch(eitem)
      {
      case ::draw2d::e_item_none:
      {

         return __raw_new Gdiplus::Region();

      }
      case ::draw2d::e_item_rectangle:
         return get_rectangle(pgraphics);
      case ::draw2d::e_item_ellipse:
         return get_ellipse(pgraphics);
      case ::draw2d::e_item_polygon:
         return get_polygon(pgraphics);
      case ::draw2d::e_item_poly_polygon:
         return get_polygon(pgraphics);
      case ::draw2d::e_item_combine:
         return get_combine(pgraphics);
      default:
         throw ::interface_only();
      }

      return nullptr;

   }


   Gdiplus::Region * region::get_rectangle(::draw2d::graphics * pgraphics)
   {

      //Gdiplus::GraphicsPath path;

      Gdiplus::RectF rectangle;

      ::pointer<::geometry2d::rectangle_item>pitem = m_pitem;

      copy(rectangle, pitem->m_item);

      //path.AddRectangle(rectangle);

      return __raw_new Gdiplus::Region(rectangle);

   }


   Gdiplus::Region * region::get_ellipse(::draw2d::graphics * pgraphics)
   {

      Gdiplus::GraphicsPath path;

      ::pointer<::geometry2d::ellipse_item>pitem = m_pitem;

      path.AddEllipse((INT) pitem->m_item.left(),
         (INT) pitem->m_item.top(),
         (INT) pitem->m_item.width(),
         (INT) pitem->m_item.height());

      return __raw_new Gdiplus::Region(&path);

   }


   Gdiplus::Region * region::get_polygon(::draw2d::graphics * pgraphics)
   {

      Gdiplus::GraphicsPath path;

      array < Gdiplus::PointF > pa;

      ::pointer<::geometry2d::polygon_item>pitem = m_pitem;

      for(i32 i = 0; i < pitem->m_polygon.get_size(); i++)
      {
         pa.add(Gdiplus::PointF((Gdiplus::REAL) pitem->m_polygon[i].x(), (Gdiplus::REAL) pitem->m_polygon[i].y()));
      }

      if(pitem->m_efillmode == ::draw2d::e_fill_mode_alternate)
      {
         path.SetFillMode(Gdiplus::FillModeAlternate);
      }
      else
      {
         path.SetFillMode(Gdiplus::FillModeWinding);
      }

      path.AddPolygon(pa.data(), (i32) pa.get_count());

      return __raw_new Gdiplus::Region(&path);

   }


   Gdiplus::Region * region::get_poly_polygon(::draw2d::graphics * pgraphics)
   {

      Gdiplus::GraphicsPath path;

      array < Gdiplus::PointF > pa;

      ::pointer<::geometry2d::poly_polygon_item>pitem = m_pitem;

      if(pitem->m_efillmode == ::draw2d::e_fill_mode_alternate)
      {
         path.SetFillMode(Gdiplus::FillModeAlternate);
      }
      else
      {
         path.SetFillMode(Gdiplus::FillModeWinding);
      }

      i32 n = 0;

      for(i32 i = 0; i < pitem->m_polypolygon.get_size(); i++)
      {

         auto & ppolygon = pitem->m_polypolygon[i];
            
         auto jCount = ppolygon->get_size();

         pa.erase_all();

         for(i32 j = 0; j < jCount; j++)
         {

            auto & point = ppolygon->element_at(n);

            pa.add(Gdiplus::PointF((Gdiplus::REAL)point.x(), (Gdiplus::REAL) point.y()));

            n++;

         }

         path.AddPolygon(pa.data(), (i32) pa.get_count());

         path.CloseFigure();

      }

      return __raw_new Gdiplus::Region(&path);

   }


   Gdiplus::Region * region::get_combine(::draw2d::graphics * pgraphics)
   {

      ::pointer<::geometry2d::combine_item>pitem = m_pitem;

      if (!pitem->m_pregion1 || !pitem->m_pregion2)
      {

         return nullptr;

      }

      ::pointer < graphics > pgdiplusgraphics = pgraphics;

      Gdiplus::Region * pregion = pgdiplusgraphics->defer_update_os_data(pitem->m_pregion1)->Clone();

      Gdiplus::Region * pregionOp = pgdiplusgraphics->defer_update_os_data(pitem->m_pregion2);

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



