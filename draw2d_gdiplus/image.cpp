#include "framework.h"
#include "image.h"
#include "graphics.h"
#include "bitmap.h"
#include "acme/exception/exception.h"
#include "acme/platform/auto_pointer.h"
#include "aura/graphics/image/icon.h"
#include "aura/graphics/image/drawing.h"


namespace draw2d_gdiplus
{


   image::image()
   {

      m_sizeWnd.cx() = 0;
      m_sizeWnd.cy() = 0;
      m_hbitmap = nullptr;

      memset(&m_bitmapinfo, 0, sizeof(m_bitmapinfo));

   }


   image::~image()
   {

      destroy();

   }


   ::draw2d::bitmap_pointer image::get_bitmap() const
   {

      return m_pbitmap;

   }


   ::draw2d::bitmap_pointer image::detach_bitmap()
   {

      return m_pbitmap.detach();

   }


   void image::_map(bool)
   {

      //return true;

   }


   void image::_unmap()
   {

      //return true;

   }

   
   bool image::on_host_read_pixels(::pixmap* ppixmapHost) const
   {

      return ::image::image::on_host_read_pixels(ppixmapHost);

   }


   bool image::host(::pixmap * ppixmap, ::windowing::window * pwindow)
   {

      if (!ppixmap->is_ok())
      {

         //return false;

         throw ::exception(error_failed);

      }

      if (m_pbitmap.is_set()
            && m_pbitmap->get_os_data() != nullptr
            && ppixmap->m_sizeRaw == this->m_sizeRaw
            && ppixmap->image32() == image32()
            && ppixmap->scan_size() == scan_size())
      {

         if (ppixmap->size() != size())
         {

            m_size = ppixmap->size();

         }

         return true;

         //return;

      }

      //destroy();

      ødefer_construct(m_pbitmap);

      ødefer_construct(m_pgraphics);

      //if (m_pbitmap.is_null())
      //{

      //   m_sizeRaw.cx() = 0;

      //   m_sizeRaw.cy() = 0;

      //   m_sizeAlloc.cx() = 0;

      //   m_sizeAlloc.cy() = 0;

      //   m_iScan = 0;

      //   return false;

      //}

      
      if (m_pbitmap->host_bitmap(nullptr, ppixmap))
      {
         //this->m_sizeRaw = ppixmap->m_sizeRaw;

      }
      //if (!)
      //{

      //   m_sizeRaw.cx() = 0;

      //   m_sizeRaw.cy() = 0;

      //   m_sizeAlloc.cx() = 0;

      //   m_sizeAlloc.cy() = 0;

      //   m_iScan = 0;

      //   return false;

      //}
         //throw ::exception(error_failed);
      //if (m_pbitmap->get_os_data() == nullptr)
      //{

      //   destroy();

      //   return false;

      //}

      pixmap::initialize(ppixmap->m_sizeRaw, ppixmap->image32(), ppixmap->m_iScan);

      m_size = ppixmap->m_size;

      m_pgraphics->set(m_pbitmap);

      m_pgraphics->m_pimage = this;

      m_pgraphics->reset_impact_area();

      m_sizeRaw = ppixmap->size();

      set_ok_flag();

      return true;

   }


   void image::create_ex(const ::int_size& size, ::image32_t * pimage32, int iScan, ::enum_flag eflagCreate, int iGoodStride, bool bPreserve)
   {

      if (m_pbitmap.is_set()
            && m_pbitmap->get_os_data() != nullptr
            && size == m_sizeRaw)
      {

         //auto ppen = øcreate < ::draw2d::pen > ();         return true;

         return;

      }

      if (size.is_empty())
      {

         destroy();

         return;

      }

      //::draw2d::bitmap_pointer pbitmapPrevious;

      //::draw2d::graphics_pointer pgraphicsPrevious;

      //if (bPreserve)
      //{

        // pbitmapPrevious = m_pbitmap;

//         pgraphicsPrevious = m_pgraphics;

//         m_pbitmap.create();

//         m_pgraphics.create();

//      }
//      else
//      {

//         m_pbitmap.defer_create();

//         m_pgraphics.defer_create();

//      }

      //destroy();

      //if (!int_size)
      //{

      //   return true;

      //}

      
      auto pbitmap = øcreate < ::draw2d::bitmap >();

      auto pgraphics = øcreate < ::draw2d::graphics >();

      if (pbitmap.is_null() || pgraphics.is_null())
      {

         //destroy();

         //return false;

         throw ::exception(error_null_pointer);

      }

      //int iScan = 0;

      //::image32_t * pimage32 = nullptr;

      pbitmap->create_bitmap(nullptr, size, (void**)&pimage32, &iScan);

      //if (!pbitmap->create_bitmap(nullptr, size, (void**)&pimage32, &iScan))
      //{

      //   //destroy();

      //   return false;

      //}

      if (pbitmap->get_os_data() == nullptr)
      {

         //destroy();

         //return false;

         throw ::exception(error_null_pointer);

      }

      pgraphics->set(pbitmap);

      //if (!pgraphics->set(pbitmap))
      //{

      //   return false;

      //}

      pgraphics->place_impact_area(0., 0., m_sizeRaw.cx(), m_sizeRaw.cy());
      //
      //if (!)
      //{

      //   //return false;

      //   throw ::exception(error_null_pointer);

      //}

      if (bPreserve
         && pbitmap
         && pgraphics
         && m_pbitmap
         && m_pgraphics)
      {

         auto w = minimum(m_pbitmap->m_size.cx(), pbitmap->m_size.cx());

         auto h = minimum(m_pbitmap->m_size.cy(), pbitmap->m_size.cy());

         Gdiplus::Rect rect(0, 0, w, h);
         
         __graphics(pgraphics)->m_pgraphics->DrawImage(
            m_pbitmap.cast <::draw2d_gdiplus::bitmap>()->m_pbitmap,
            rect, 0, 0, w, h, Gdiplus::UnitPixel);

      }

      m_pbitmap = pbitmap;

      m_pgraphics = pgraphics;

      pixmap::initialize(size, pimage32, iScan);

      m_pgraphics->m_pimage = this;
      //m_sizeRaw.cx() = width;
      //m_sizeRaw.cy() = height;
      m_sizeRaw = size;
      //m_sizeAlloc.cy() = height;

      //if (pbitmapPrevious && pgraphicsPrevious)
      //{


      //}
      
      m_bMapped = false;

      set_flag(eflagCreate);

      //return true;

   }

   //void image::create(const ::int_size & size, ::eobject eobjectCreate, int iGoodStride, bool bPreserve)
   //{

   //   //if (m_pbitmap.is_set()
   //   //   && m_pbitmap->get_os_data() != nullptr
   //   //   && size == m_sizeRaw)
   //   //{

   //   //   return true;

   //   //}

   //   //::draw2d::bitmap_pointer pbitmapPrevious;

   //   //::draw2d::graphics_pointer pgraphicsPrevious;

   //   //if (bPreserve)
   //   //{

   //   //   pbitmapPrevious = m_pbitmap;

   //   //   pgraphicsPrevious = m_pgraphics;

   //   //   m_pbitmap.create();

   //   //   m_pgraphics.create();

   //   //}
   //   //else
   //   //{

   //   //   m_pbitmap.defer_create();

   //   //   m_pgraphics.defer_create();

   //   //}

   //   ////destroy();

   //   ////if (!int_size)
   //   ////{

   //   ////   return true;

   //   ////}


   //   //if (m_pbitmap.is_null() || m_pgraphics.is_null())
   //   //{

   //   //   destroy();

   //   //   return false;

   //   //}

   //   //int iScan = 0;

   //   //::image32_t * pimage32 = nullptr;

   //   //if (!m_pbitmap->create_bitmap(nullptr, size, (void **)&pimage32, &iScan))
   //   //{

   //   //   destroy();

   //   //   return false;

   //   //}

   //   //if (m_pbitmap->get_os_data() == nullptr)
   //   //{

   //   //   destroy();

   //   //   return false;

   //   //}

   //   //pixmap::init(size, pimage32, iScan);

   //   //m_pgraphics->set(m_pbitmap);
   //   //m_pgraphics->set_origin(origin());

   //   //m_pgraphics->m_pimage = this;
   //   ////m_sizeRaw.cx() = width;
   //   ////m_sizeRaw.cy() = height;
   //   //m_sizeAlloc = size;
   //   ////m_sizeAlloc.cy() = height;

   //   //if (pbitmapPrevious && pgraphicsPrevious)
   //   //{

   //   //   Gdiplus::Rect r(0, 0, pbitmapPrevious->m_size.cx(), pbitmapPrevious->m_size.cy());
   //   //   __graphics(m_pgraphics)->m_pgraphics->DrawImage(
   //   //      pbitmapPrevious.cast <::draw2d_gdiplus::bitmap>()->m_pbitmap,
   //   //      r, r.X, r.Y, r.Width, r.Height, Gdiplus::UnitPixel);

   //   //}

   //   //m_bMapped = false;

   //   //m_eobject = eobjectCreate;

   //   //return true;

   //}


   void image::dc_select(bool bSelect)
   {

      //return true;

   }


   void image::create(::draw2d::graphics * pgraphics)
   {

      ::draw2d::bitmap * pbitmap = (dynamic_cast<::draw2d_gdiplus::graphics *>(pgraphics))->get_current_bitmap();

      if (pbitmap == nullptr)
      {

         //return false;

         throw ::exception(error_null_pointer);

      }
      
      create(pbitmap->get_size());
      //if (!create(pbitmap->get_size()))
      //{

      //   return false;

      //}

      copy_from(pgraphics->m_pimage);

      //return true;

   }


   void image::destroy()
   {

      ::image::image::destroy();

      //return ::success;

   }


   //bool image::to(::draw2d::graphics * pgraphics, const ::int_point & point, const ::int_size & size, const ::int_point & pointSrc)
   //{

   //   return pgraphics->draw(point, size, get_graphics(), pointSrc);

   //}


   //bool image::stretch(::image::image * pimage)
   //{

   ////   ::draw2d::bitmap_pointer bitmap(get_application());

   ////   bitmap->CreateCompatibleBitmap(pgraphics, 1, 1);

   ////   const ::int_size & size = bitmap->get_size();

   ////   if (!create(size))
   ////   {

   ////      return false;

   ////   }

   ////   HDC hdc = __graphics(pgraphics)->get_hdc();

   ////   bool bOk = GetDIBits(hdc, (HBITMAP)bitmap->get_os_data(), 0, height(), m_pimage32Raw, nullptr, DIB_RGB_COLORS) != false;

   ////   g()->set(bitmap);

   ////   __graphics(pgraphics)->release_hdc(hdc);

   ////   auto estatus = pgraphics->set(bitmap);

   ////   if (!estatus)
   ////   {

   ////      return false;

   ////   }

   ////   return bOk;

   //   return true;

   //}


   //bool image::draw(const ::int_point & pointDest, ::image::image * pimage, const ::int_rectangle & rectangleSource)
   //{

   //   return m_pgraphics->draw(pointDest, pimage, rectangleSource) != false;

   //}


   void image::_draw_raw(const ::int_rectangle & rectangleDstParam, ::image::image * pimageSrc, const ::int_point & pointSrcParam)
   {

      ::int_rectangle rectangleTarget(rectangleDstParam);

      ::int_point pointSrc(pointSrcParam);

      ::int_size size(rectangleTarget.size());

      ::image::image * pimageDst = this;

      if (pimageDst->m_bMapped && pimageSrc->m_bMapped)
      {

         rectangleTarget += m_point;

         if (pointSrc.x < 0)
         {

            rectangleTarget.left() -= pointSrc.x;

            pointSrc.x = 0;

         }

         if (pointSrc.y < 0)
         {

            rectangleTarget.top() -= pointSrc.y;

            pointSrc.y = 0;

         }

         if (rectangleTarget.left() < 0)
         {

            size.cx() += rectangleTarget.left();

            pointSrc.x -= rectangleTarget.left();

            rectangleTarget.left() = 0;

         }

         if (size.cx() < 0)
         {

            return;

         }

         if (rectangleTarget.top() < 0)
         {

            size.cy() += rectangleTarget.top();

            pointSrc.y -= rectangleTarget.top();

            rectangleTarget.top() = 0;

         }

         if (size.cy() < 0)
         {

            return;

         }

         int xEnd = minimum(size.cx(), minimum(pimageSrc->width() - pointSrc.x, pimageDst->width() - rectangleTarget.left()));

         int yEnd = minimum(size.cy(), minimum(pimageSrc->height() - pointSrc.y, pimageDst->height() - rectangleTarget.top()));

         if (xEnd < 0)
         {

            return;

         }

         if (yEnd < 0)
         {

            return;

         }

         int scanDst = pimageDst->scan_size();

         int scanSrc = pimageSrc->scan_size();

         unsigned char * pdst = &((unsigned char *)pimageDst->image32())[scanDst * rectangleTarget.top() + rectangleTarget.left() * sizeof(::color::color)];

         unsigned char * psrc = &((unsigned char *)pimageSrc->image32())[scanSrc * pointSrc.y + pointSrc.x * sizeof(::color::color)];

         ::color::color * pdst2;

         ::color::color * psrc2;

         for (int y = 0; y < yEnd; y++)
         {

            pdst2 = (::color::color *)&pdst[scanDst * y];

            psrc2 = (::color::color *)&psrc[scanSrc * y];

            memory_copy(pdst2, psrc2, xEnd * 4);

         }

      }
      else
      {

         ::image::image_source imagesource(pimageSrc, ::double_rectangle(pointSrc, size));

         ::image::image_drawing_options imagedrawingoptions(::double_rectangle(rectangleTarget.top_left(), size));

         ::image::image_drawing imagedrawing(imagedrawingoptions, imagesource);

         pimageDst->g()->draw(imagedrawing);

      }

      //return true;

   }


 /*  bool image::draw(const ::int_rectangle & rectangleTarget, ::image::image * pimage, const ::int_point & pointSrc)
   {

      return ::image::draw(rectangleTarget, pimage, pointSrc);

   }*/


   void image::SetIconMask(::image::icon * picon, int cx, int cy)
   {

      if (cx <= 0 || cy <= 0)
      {

         //return error_invalid_parameter;

         throw ::exception(error_null_pointer);

      }

      //auto estatus = 
      
      create({ cx, cy });

      //if (!estatus)
      //{

      //   return estatus;

      //}

      // White blend image
      ::image::image_pointer pimage1;

      //estatus = 
      
      øconstruct(pimage1);

      //if (!estatus)
      //{

      //   return estatus;

      //}
      
      //estatus = 
      
      pimage1->create({ cx, cy });

      //if (!estatus)
      //{

      //   return estatus;

      //}



      pimage1->clear(color::white);

      {
      
         ::image::image_source imagesource(picon);

         ::image::image_drawing_options imagedrawingoptions(::int_rectangle_dimension(0, 0, cx, cy));

         ::image::image_drawing imagedrawing(imagedrawingoptions, imagesource);

         pimage1->g()->draw(imagedrawing);

      }

      // Black blend image
      ::image::image_pointer pimage2;

      //estatus = 
      
      øconstruct(pimage2);
      
      //if (!estatus)
      //{

      //   return estatus;

      //}

      //estatus=
      
      pimage2->create( 
      { cx, cy } );

 /*     if (!estatus)
      {

         return estatus;

      }*/

      pimage2->fill_byte(0);

      {

         ::image::image_source imagesource(picon);

         ::image::image_drawing_options imagedrawingoptions(::int_rectangle_dimension(0, 0, cx, cy));

         ::image::image_drawing imagedrawing(imagedrawingoptions, imagesource);

         pimage2->g()->draw(imagedrawing);

      }

      //nullptr,
      //DI_IMAGE | DI_MASK);

      // Mask image
      ::image::image_pointer pimageM;

      //estatus = 
      
      øconstruct(pimageM);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      // estatus = 
      
      pimageM->create(
         { cx, cy });

      //if (!estatus)
      //{

      //   return estatus;

      //}

      {

         ::image::image_source imagesource(picon);

         ::image::image_drawing_options imagedrawingoptions(::int_rectangle_dimension(0, 0, cx, cy));

         ::image::image_drawing imagedrawing(imagedrawingoptions, imagesource);

         pimageM->g()->draw(imagedrawing);

      }

      unsigned char * r1 = (unsigned char *)pimage1->image32();
      unsigned char * r2 = (unsigned char *)pimage2->image32();
      unsigned char * srcM = (unsigned char *)pimageM->image32();
      unsigned char * dest = (unsigned char *)image32();
      int iSize = cx*cy;

      unsigned char b;
      unsigned char bMax;
      while (iSize-- > 0)
      {
         if (srcM[0] == 255)
         {
            bMax = 0;
         }
         else
         {
            bMax = 0;
            b = (unsigned char)(r1[0] - r2[0]);
            bMax = maximum(b, bMax);
            b = (unsigned char)(r1[1] - r2[1]);
            bMax = maximum(b, bMax);
            b = (unsigned char)(r1[2] - r2[2]);
            bMax = maximum(b, bMax);
            bMax = 255 - bMax;
         }
         dest[0] = bMax;
         dest[1] = bMax;
         dest[2] = bMax;
         dest += 4;
         srcM += 4;
         r1 += 4;
         r2 += 4;
      }

      //return ::success;

   }


   ::draw2d::graphics * image::_get_graphics() const
   {

      return m_pgraphics;

   }


   void image::draw2d_gdiplus_image_common_construct()
   {

      m_pbitmap.release();
      m_pgraphics.release();
      m_hbitmap               = nullptr;
      m_sizeWnd               = ::long_long_size(0, 0);
      memset(&m_bitmapinfo, 0, sizeof(m_bitmapinfo));

   }


   bool image::_load_thumbnail(const ::scoped_string & scopedstr)
   {

      ::Gdiplus::Graphics * pgraphics = (::Gdiplus::Graphics *)get_graphics()->get_os_data();

      wstring wstr(scopedstr);

      // Create an image and a thumbnail of the pimage->
      ::Gdiplus::Image image(wstr);

      auto pthumbnail = as_auto_pointer(image.GetThumbnailImage(width(), height(), nullptr, nullptr));

      // Draw the original and the thumbnail images.
      pgraphics->DrawImage(pthumbnail, 0, 0, pthumbnail->GetWidth(), pthumbnail->GetHeight());

      return true;

   }


   void image::on_exif_orientation()
   {

      ::image::image::on_exif_orientation();

   }


} // namespace draw2d_gdiplus



