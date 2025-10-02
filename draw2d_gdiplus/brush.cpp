#include "framework.h"
#include "brush.h"
#include "image.h"
#include "path.h"


//#undef ___new


namespace draw2d_gdiplus
{


   brush::brush()
   {

      m_pthis = this;
      m_pbrush = nullptr;

   }

   brush::~brush()
   {

      destroy();

   }


//#ifdef DEBUG
//
//   void brush::dump(dump_context & dumpcontext) const
//   {
//
//      ::draw2d::object::dump(dumpcontext);
//
//   }
//
//#endif

   void brush::create(::draw2d::graphics * pgraphics, char iCreate)
   {

      if(m_ebrush == ::draw2d::e_brush_solid)
      {

         try
         {

            m_pbrush = øraw_new Gdiplus::SolidBrush(gdiplus_color(m_color));

         }
         catch(...)
         {

         }

      }
      else if(m_ebrush == ::draw2d::e_brush_linear_gradient_point_color)
      {

         try
         {

            m_pbrush = øraw_new Gdiplus::LinearGradientBrush(
            Gdiplus::PointF((Gdiplus::REAL) m_point1.x(),(Gdiplus::REAL) m_point1.y()),
            Gdiplus::PointF((Gdiplus::REAL) m_point2.x(),(Gdiplus::REAL) m_point2.y()),
            gdiplus_color(m_color1),
               gdiplus_color(m_color2));

         }
         catch(...)
         {
         }
      }
      else if(m_ebrush == ::draw2d::e_brush_radial_gradient_color)
      {

         try
         {

            Gdiplus::GraphicsPath * ppath = øraw_new Gdiplus::GraphicsPath();

            ppath->AddEllipse((Gdiplus::REAL) (m_point.x() - m_size.cx() / 2),(Gdiplus::REAL)(m_point.y() - m_size.cy() / 2),(Gdiplus::REAL) (m_size.cx()),(Gdiplus::REAL) (m_size.cy()));

            Gdiplus::PathGradientBrush * pgradientbrush = øraw_new Gdiplus::PathGradientBrush(ppath);

            auto c1 = gdiplus_color(m_color1);
            auto c2 = gdiplus_color(m_color2);

            INT c = 1;

            pgradientbrush->SetCenterPoint(Gdiplus::PointF((Gdiplus::REAL) m_point.x(),(Gdiplus::REAL) m_point.y()));
            pgradientbrush->SetCenterColor(c1);
            pgradientbrush->SetSurroundColors(&c2,&c);

            m_pbrush = pgradientbrush;

         }
         catch(...)
         {
         }
      }
      else if (m_ebrush == ::draw2d::e_brush_pattern)
      {

         try
         {

            if (m_pimage.ok())
            {

               auto pimage = m_pimage;

               if (m_size.area() > 0)
               {

                  pimage = pimage->get_resized_image(m_size);

               }

               Gdiplus::Image * pgdiplusimage = pimage->get_bitmap()->get_os_data < Gdiplus::Bitmap * >();

               if (::is_set(pgdiplusimage))
               {

                  Gdiplus::TextureBrush* ptexturebrush = øraw_new Gdiplus::TextureBrush(pgdiplusimage);

                  m_pbrush = ptexturebrush;

               }

            }

         }
         catch (...)
         {

         }

      }
      else if (m_ebrush == ::draw2d::e_brush_box_gradient)
      {

         try
         {

            ::pointer<::draw2d::path>ppath;

            pgraphics->øconstruct(ppath);

            ::double_rectangle rectangleRoundRect(m_point, m_size);

            double dDiameter = m_dRadius * 2.0;

            if (dDiameter <= rectangleRoundRect.minimum_dimension())
            {


               ppath->add_round_rectangle(rectangleRoundRect, m_dRadius);

               auto pgdipath = (Gdiplus::GraphicsPath *)ppath->get_os_data(0);

               Gdiplus::PathGradientBrush * pgradientbrush = øraw_new Gdiplus::PathGradientBrush(pgdipath);

               auto c1 = gdiplus_color(m_color1);

               Gdiplus::Color colora[4];
               colora[0] = gdiplus_color(m_color2);
               colora[1] = gdiplus_color(m_color2);
               colora[2] = gdiplus_color(m_color2);
               colora[3] = gdiplus_color(m_color2);

               INT c = 4;

               Gdiplus::PointF pointCenter((Gdiplus::REAL)rectangleRoundRect.center_x(), (Gdiplus::REAL)rectangleRoundRect.center_y());

               auto innerRectangle = rectangleRoundRect;

               innerRectangle.deflate(m_dRadius, m_dRadius);

               double dCenterToOuterVertice = rectangleRoundRect.top_left().distance(rectangleRoundRect.center());
               double dCenterToInnerVertice = innerRectangle.top_left().distance(innerRectangle.center());

               //auto d = (Gdiplus::REAL)(dCenterToInnerVertice / dCenterToOuterVertice);

               auto d = (Gdiplus::REAL)(rectangleRoundRect.height() - m_dRadius * 2.0) / (Gdiplus::REAL)rectangleRoundRect.height();

               pgradientbrush->SetCenterPoint(pointCenter);
               pgradientbrush->SetCenterColor(c1);
               pgradientbrush->SetSurroundColors(colora, &c);
               pgradientbrush->SetInterpolationColors(&c1, &d, 1);
               //pgradientbrush->SetInterpolationColors(&c1, &d, 1);


               m_pbrush = pgradientbrush;

            }

         }
         catch (...)
         {
         }
      }
      else
      {

         try
         {

            m_pbrush = øraw_new Gdiplus::SolidBrush(gdiplus_color(m_color));

         }
         catch(...)
         {

         }

      }

      m_osdata[0] = m_pbrush;

      //return m_pbrush != nullptr;

   }


   void brush::destroy_os_data()
   {

      ::acme::del(m_pbrush);

      //return ::success;

   }


   void brush::destroy()
   {

      destroy_os_data();

      ::draw2d::brush::destroy();

      //return ::success;

   }




} // namespace draw2d_gdiplus



