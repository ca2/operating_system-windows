#include "platform.h"
#include "image.h"
#include "graphics.h"
#include "bitmap.h"
#include "draw2d.h"
#include "acme/exception/exception.h"
#include "acme/platform/auto_pointer.h"
#include "aura/graphics/image/icon.h"
#include "aura/graphics/image/drawing.h"
#include "aura/graphics/draw2d/graphics_lease.h"
#include "aura/windowing/window_buffer.h"


CLASS_DECL_ACME ::string _001_image32_diagnostics(const ::i32_size &size, const image32_t *pimage32, int iScan);


namespace draw2d_gdiplus
{


   image::image()
   {

      m_sizeWnd.cx = 0;
      m_sizeWnd.cy = 0;
      m_hbitmap = nullptr;
      

      memset(&m_bitmapinfo, 0, sizeof(m_bitmapinfo));

   }


   image::image(image&& image) :
      IMAGE_IMAGE_TRANSFER(image)
   {


   }


   image::~image()
   {

      destroy();

   }


   void image::create_bitmap(
      ::acme::user::interaction * pacmeuserinteractionAffinity, ::draw2d::graphics * pgraphics)
   {

      return ::image::image::create_bitmap(
         pacmeuserinteractionAffinity,
         pgraphics);

   }


   ::draw2d::bitmap_pointer image::get_bitmap() const
   {

      return ::image::image::get_bitmap();

   }


   ::draw2d::bitmap_pointer image::detach_bitmap()
   {

      return m_pbitmap.detach();

   }


   ::pixmap_lease image::_map(const ::i32_rectangle & rectangle, bool bApplyAlphaTransform)
   {

      if (m_ppixmapOwned)
      {

         auto ppixmapOwned = ::transfer(m_ppixmapOwned->map(rectangle, bApplyAlphaTransform));

         return ::transfer(ppixmapOwned);

      }

      construct_newø(m_ppixmapOwned);

      m_ppixmapOwned->create_as_descriptor(this->raw_size());

      auto ppixmapOwned = ::transfer(m_ppixmapOwned->map(rectangle, bApplyAlphaTransform));

      return ::transfer(ppixmapOwned);

      //_on_map(bApplyTransform);

      //return true;

   }


   void image::_unmap(bool bDoUnmap)
   {

      image::image::_unmap(false);
      
      //_on_unmap(bDoUnmap);
      
      //return true;

   }

   
   bool image::on_host_read_pixels(::pixmap_t* ppixmapHost) const
   {

      return ::image::image::on_host_read_pixels(ppixmapHost);

   }


   void image::create_as_render_target(const ::i32_size & sizeRaw, ::user::interaction * puserinteraction, ::draw2d::graphics * pdraw2dgraphics, ::enum_flag eflagCreate, ::i32 iGoodStride, bool bPreserve, bool bTopDraw2d)
   {

      create_from_data(sizeRaw, nullptr, 0);

      //constructø(m_pgraphicsOwned);

      //m_pgraphicsOwned->create_for_image(this);

   }


   bool image::host(::windowing::window_buffer * pwindowbuffer, ::windowing::window * pwindow, const ::i32_size & sizeRaw)
   {

      return ::image::image::host(pwindowbuffer, pwindow, sizeRaw);

      //if (!::is_ok(pwindowbuffer->m_ppixmapWindowBuffer))
      //{

      //   //return false;

      //   throw ::exception(error_failed);

      //}

      //if (m_pbitmap.is_set()
      //      && m_pbitmap->get_os_data() != nullptr
      //      && pwindowbuffer->m_pixmap.m_sizeRaw == this->m_sizeRaw
      //      && pwindowbuffer->m_pixmap.image32() == image32()
      //      && pwindowbuffer->m_pixmap.scan_size() == scan_size())
      //{

      //   if (pwindowbuffer->m_pixmap.size() != size())
      //   {

      //      m_size = pwindowbuffer->m_pixmap.size();

      //   }

      //   return true;

      //   //return;

      //}

      ////destroy();

      //defer_constructø(m_pbitmap);

      ////defer_constructø(m_pgraphics);

      ////if (m_pbitmap.is_null())
      ////{

      ////   m_sizeRaw.cx = 0;

      ////   m_sizeRaw.cy = 0;

      ////   m_sizeAlloc.cx = 0;

      ////   m_sizeAlloc.cy = 0;

      ////   m_iScan = 0;

      ////   return false;

      ////}

      //
      //if (m_pbitmap->host_bitmap(nullptr, &pwindowbuffer->m_pixmap))
      //{
      //   //this->m_sizeRaw = pwindowbuffer->m_pixmap.m_sizeRaw;

      //}
      ////if (!)
      ////{

      ////   m_sizeRaw.cx = 0;

      ////   m_sizeRaw.cy = 0;

      ////   m_sizeAlloc.cx = 0;

      ////   m_sizeAlloc.cy = 0;

      ////   m_iScan = 0;

      ////   return false;

      ////}
      //   //throw ::exception(error_failed);
      ////if (m_pbitmap->get_os_data() == nullptr)
      ////{

      ////   destroy();

      ////   return false;

      ////}

      //initialize_pixmap(pwindowbuffer->m_pixmap.m_sizeRaw, pwindowbuffer->m_pixmap.image32(), pwindowbuffer->m_pixmap.m_iScan);

      //m_size = pwindowbuffer->m_pixmap.m_size;

      //m_sizeRaw = pwindowbuffer->m_pixmap.size();

      //set_ok_flag();

      //auto pgraphics = acquire_graphics();

      //pgraphics->m_pimage = this;

      //pgraphics->reset_impact_area();

      //return true;

   }


   void image::create_from_data(const ::i32_size& size, const ::image32_t * pimage32, ::i32 iScan, ::enum_flag eflagCreate, bool bPreserve)
   {

      if (m_pbitmap.is_set()
            && m_pbitmap->get_os_data() != nullptr
            && size == m_sizeRaw)
      {

         //auto ppen = createø < ::draw2d::pen > ();         return true;

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

      //if (!i32_size)
      //{

      //   return true;

      //}

      
      auto pbitmap = createø < ::draw2d::bitmap >();

      //auto pgraphics = draw2d()->acquire_memory_graphics(size);

      //if (pbitmap.is_null() || pgraphics.is_null())
      if (pbitmap.is_null())
      {

         //destroy();

         //return false;

         throw ::exception(error_null_pointer);

      }

      //::i32 iScan = 0;

      ::image32_t * pimage32Bitmap = nullptr;

      auto str1 = _001_image32_diagnostics(size, pimage32, iScan);

      information("draw2d_gdiplus::image::create_from_data (1) {}", str1);

      if (iScan < size.cx * 4)
      {

         iScan = size.cx * 4;

      }

      defer_constructø(m_ppixmapOwned);

      if (::is_set(pimage32))
      {

         m_ppixmapOwned->m_memoryPixmap.assign(pimage32, iScan * size.cy);

      }
      else
      {

         m_ppixmapOwned->m_memoryPixmap.set_size(iScan * size.cy);

         m_ppixmapOwned->m_memoryPixmap.zero();

      }


      //pbitmap->create_bitmap(nullptr, size, &pimage32Bitmap, pimage32, &iScan);

      pbitmap->create_bitmap(nullptr, size, m_ppixmapOwned);

      auto str2 = _001_image32_diagnostics(size, pimage32Bitmap, iScan);

      information("draw2d_gdiplus::image::create_from_data (2) {}", str2);

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

      //pgraphics->set(pbitmap);

      //if (!pgraphics->set(pbitmap))
      //{

      //   return false;

      //}

      //pgraphics->place_impact_area(0., 0., m_sizeRaw.cx, m_sizeRaw.cy);
      //
      //if (!)
      //{

      //   //return false;

      //   throw ::exception(error_null_pointer);

      //}

      if (bPreserve
         && pbitmap
         //&& pgraphics
          && ::is_null(pimage32)
         && m_pbitmap)
         //&& m_pgraphics)
      {

         auto w = minimum(m_pbitmap->m_size.cx, pbitmap->m_size.cx);

         auto h = minimum(m_pbitmap->m_size.cy, pbitmap->m_size.cy);

         auto pgraphics = draw2d()->acquire_memory_graphics({w, h});

         Gdiplus::Rect rect(0, 0, w, h);
         
         __graphics(pgraphics)->m_pgraphics->DrawImage(
            m_pbitmap.cast <::draw2d_gdiplus::bitmap>()->m_pbitmap,
            rect, 0, 0, w, h, Gdiplus::UnitPixel);

      }

      m_pbitmap = pbitmap;
//
  //    m_pgraphics = pgraphics;

      //initialize_pixmap(size, pimage32Bitmap, iScan);

      create_as_descriptor(size);

      //m_pgraphics->m_pimage = this;
      //m_sizeRaw.cx = width;
      //m_sizeRaw.cy = height;
      //m_sizeRaw = size;
      //m_sizeAlloc.cy = height;

      //if (pbitmapPrevious && pgraphicsPrevious)
      //{


      //}
      
      m_bMapped = false;

      set_flag(eflagCreate);

      //return true;

   }

   //void image::create(const ::i32_size & size, ::eobject eobjectCreate, ::i32 iGoodStride, bool bPreserve)
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

   //   ////if (!i32_size)
   //   ////{

   //   ////   return true;

   //   ////}


   //   //if (m_pbitmap.is_null() || m_pgraphics.is_null())
   //   //{

   //   //   destroy();

   //   //   return false;

   //   //}

   //   //::i32 iScan = 0;

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
   //   ////m_sizeRaw.cx = width;
   //   ////m_sizeRaw.cy = height;
   //   //m_sizeAlloc = size;
   //   ////m_sizeAlloc.cy = height;

   //   //if (pbitmapPrevious && pgraphicsPrevious)
   //   //{

   //   //   Gdiplus::Rect r(0, 0, pbitmapPrevious->m_size.cx, pbitmapPrevious->m_size.cy);
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


   void image::create_from_graphics(::draw2d::graphics * pgraphics)
   {

      ::draw2d::bitmap * pbitmap = (dynamic_cast<::draw2d_gdiplus::graphics *>(pgraphics))->get_current_bitmap();

      if (pbitmap == nullptr)
      {

         //return false;

         throw ::exception(error_null_pointer);

      }
      
      create_as_descriptor(pbitmap->get_size());
      //if (!create(pbitmap->get_size()))
      //{

      //   return false;

      //}

      auto ppixmapImageThis = this->map();

      auto ppixmapGraphicsImage = pgraphics->m_pimage->map();

      ppixmapImageThis->copy_from(ppixmapGraphicsImage);

      //return true;

   }


   void image::preserve(const ::i32_size& size, ::enum_flag eflagCreate)
   {

      auto imageBefore = ::transfer(*this);

      create_as_descriptor(size, eflagCreate);

      auto ppixmapImageThis = this->map();

      auto ppixmapImageBefore = imageBefore.map();

      ppixmapImageThis->copy(ppixmapImageBefore);
      //copy(size.minimum(ppixmapImageBefore->size()), ppixmapImageBefore->data(), ppixmapImageBefore->m_iScan);

   }


   void image::destroy()
   {

      ::image::image::destroy();

      //return ::success;

   }


   //bool image::to(::draw2d::graphics * pgraphics, const ::i32_point & point, const ::i32_size & size, const ::i32_point & pointSrc)
   //{

   //   return pgraphics->draw(point, size, get_graphics(), pointSrc);

   //}


   //bool image::stretch(::image::image * pimage)
   //{

   ////   ::draw2d::bitmap_pointer bitmap(get_application());

   ////   bitmap->CreateCompatibleBitmap(pgraphics, 1, 1);

   ////   const ::i32_size & size = bitmap->get_size();

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


   //bool image::draw(const ::i32_point & pointDest, ::image::image * pimage, const ::i32_rectangle & rectangleSource)
   //{

   //   return m_pgraphics->draw(pointDest, pimage, rectangleSource) != false;

   //}


   void image::_draw_raw(const ::i32_rectangle & rectangleDstParam, ::image::image * pimageSrc, const ::i32_point & pointSrcParam)
   {

      ::i32_rectangle rectangleTarget(rectangleDstParam);

      ::i32_point pointSrc(pointSrcParam);

      ::i32_size size(rectangleTarget.size());

      ::image::image * pimageDst = this;

      if (pimageDst->m_bMapped || pimageSrc->m_bMapped)
      {

         throw ::exception(error_wrong_state);

      }

      // if (pimageDst->m_bMapped && pimageSrc->m_bMapped)
      // {
      //
      //    //rectangleTarget += m_point;
      //
      //    if (pointSrc.x < 0)
      //    {
      //
      //       rectangleTarget.left -= pointSrc.x;
      //
      //       pointSrc.x = 0;
      //
      //    }
      //
      //    if (pointSrc.y < 0)
      //    {
      //
      //       rectangleTarget.top -= pointSrc.y;
      //
      //       pointSrc.y = 0;
      //
      //    }
      //
      //    if (rectangleTarget.left < 0)
      //    {
      //
      //       size.cx += rectangleTarget.left;
      //
      //       pointSrc.x -= rectangleTarget.left;
      //
      //       rectangleTarget.left = 0;
      //
      //    }
      //
      //    if (size.cx < 0)
      //    {
      //
      //       return;
      //
      //    }
      //
      //    if (rectangleTarget.top < 0)
      //    {
      //
      //       size.cy += rectangleTarget.top;
      //
      //       pointSrc.y -= rectangleTarget.top;
      //
      //       rectangleTarget.top = 0;
      //
      //    }
      //
      //    if (size.cy < 0)
      //    {
      //
      //       return;
      //
      //    }
      //
      //    ::i32 xEnd = minimum(size.cx, minimum(pimageSrc->width() - pointSrc.x, pimageDst->width() - rectangleTarget.left));
      //
      //    ::i32 yEnd = minimum(size.cy, minimum(pimageSrc->height() - pointSrc.y, pimageDst->height() - rectangleTarget.top));
      //
      //    if (xEnd < 0)
      //    {
      //
      //       return;
      //
      //    }
      //
      //    if (yEnd < 0)
      //    {
      //
      //       return;
      //
      //    }
      //
      //    ::i32 scanDst = pimageDst->scan_size();
      //
      //    ::i32 scanSrc = pimageSrc->scan_size();
      //
      //    ::u8 * pdst = &((::u8 *)pimageDst->image32())[scanDst * rectangleTarget.top + rectangleTarget.left * sizeof(::color::color)];
      //
      //    ::u8 * psrc = &((::u8 *)pimageSrc->image32())[scanSrc * pointSrc.y + pointSrc.x * sizeof(::color::color)];
      //
      //    ::color::color * pdst2;
      //
      //    ::color::color * psrc2;
      //
      //    for (::i32 y = 0; y < yEnd; y++)
      //    {
      //
      //       pdst2 = (::color::color *)&pdst[scanDst * y];
      //
      //       psrc2 = (::color::color *)&psrc[scanSrc * y];
      //
      //       memory_copy(pdst2, psrc2, xEnd * 4);
      //
      //    }
      //
      // }
      // else
      {

         ::image::image_source imagesource(pimageSrc, ::f64_rectangle(pointSrc, size));

         ::image::image_drawing_options imagedrawingoptions(::f64_rectangle(rectangleTarget.top_left(), size));

         ::image::image_drawing imagedrawing(imagedrawingoptions, imagesource);

         auto pgraphicsImageDst = pimageDst->acquire_graphics();

         pgraphicsImageDst->draw(imagedrawing);

      }

      //return true;

   }


 /*  bool image::draw(const ::i32_rectangle & rectangleTarget, ::image::image * pimage, const ::i32_point & pointSrc)
   {

      return ::image::draw(rectangleTarget, pimage, pointSrc);

   }*/


   void image::SetIconMask(::image::icon * picon, ::i32 cx, ::i32 cy)
   {

      if (cx <= 0 || cy <= 0)
      {

         //return error_invalid_parameter;

         throw ::exception(error_null_pointer);

      }

      //auto estatus = 
      
      create_as_descriptor({cx, cy});

      //if (!estatus)
      //{

      //   return estatus;

      //}

      // White blend image
      ::image::image_pointer pimage1;

      //estatus = 
      
      constructø(pimage1);

      //if (!estatus)
      //{

      //   return estatus;

      //}
      
      //estatus = 
      
      pimage1->create_as_descriptor({cx, cy});

      //if (!estatus)
      //{

      //   return estatus;

      //}

      {
      
         auto pgraphicsImage1 = pimage1->acquire_graphics();


         pgraphicsImage1->clear(color::white);

         ::image::image_source imagesource(picon);

         ::image::image_drawing_options imagedrawingoptions(::i32_rectangle_dimension(0, 0, cx, cy));

         ::image::image_drawing imagedrawing(imagedrawingoptions, imagesource);

         //auto pgraphicsImage1 = pimage1->acquire_graphics();

         pgraphicsImage1->draw(imagedrawing);

      }

      // Black blend image
      ::image::image_pointer pimage2;

      //estatus = 
      
      constructø(pimage2);
      
      //if (!estatus)
      //{

      //   return estatus;

      //}

      //estatus=
      
      pimage2->create_as_descriptor( 
      { cx, cy } );

 /*     if (!estatus)
      {

         return estatus;

      }*/

      {

         auto pgraphicsImage2 = pimage2->acquire_graphics();

         //pimage2->fill_byte(0);

         pgraphicsImage2->clear(::color::transparent);

         ::image::image_source imagesource(picon);

         ::image::image_drawing_options imagedrawingoptions(::i32_rectangle_dimension(0, 0, cx, cy));

         ::image::image_drawing imagedrawing(imagedrawingoptions, imagesource);

         //auto pgraphicsImage2 = pimage1->acquire_graphics();

         pgraphicsImage2->draw(imagedrawing);

      }

      //nullptr,
      //DI_IMAGE | DI_MASK);

      // Mask image
      ::image::image_pointer pimageM;

      //estatus = 
      
      constructø(pimageM);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      // estatus = 
      
      pimageM->create_as_descriptor(
         { cx, cy });

      //if (!estatus)
      //{

      //   return estatus;

      //}

      {

         auto pgraphicsImageM = pimageM->acquire_graphics();

         ::image::image_source imagesource(picon);

         ::image::image_drawing_options imagedrawingoptions(::i32_rectangle_dimension(0, 0, cx, cy));

         ::image::image_drawing imagedrawing(imagedrawingoptions, imagesource);

         //auto pgraphicsImageM = pimageM->acquire_graphics();

         pgraphicsImageM->draw(imagedrawing);

      }

      auto ppixmapImage1 = pimage1->map();

      auto ppixmapImage2 = pimage2->map();

      auto ppixmapImageM = pimageM->map();

      auto ppixmapImageThis = this->map();

      ::u8 * r1 = (::u8 *)ppixmapImage1->image32();
      ::u8 * r2 = (::u8 *)ppixmapImage2->image32();
      ::u8 * srcM = (::u8 *)ppixmapImageM->image32();
      ::u8 * dest = (::u8 *)ppixmapImageThis->image32();
      ::i32 iSize = cx*cy;

      ::u8 b;
      ::u8 bMax;
      while (iSize-- > 0)
      {
         if (srcM[0] == 255)
         {
            bMax = 0;
         }
         else
         {
            bMax = 0;
            b = (::u8)(r1[0] - r2[0]);
            bMax = maximum(b, bMax);
            b = (::u8)(r1[1] - r2[1]);
            bMax = maximum(b, bMax);
            b = (::u8)(r1[2] - r2[2]);
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


   //::draw2d::graphics * image::_get_graphics() const
   //{

   //   return m_pgraphics;

   //}


   void image::draw2d_gdiplus_image_common_construct()
   {

      m_pbitmap.release();
      //m_pgraphics.release();
      m_hbitmap               = nullptr;
      m_sizeWnd               = ::i64_size(0, 0);
      memset(&m_bitmapinfo, 0, sizeof(m_bitmapinfo));

   }


   bool image::_load_thumbnail(const ::scoped_string & scopedstr)
   {

      auto pgraphicsThis = acquire_graphics();

      ::Gdiplus::Graphics *pgraphics = (::Gdiplus::Graphics *)pgraphicsThis->get_os_data();

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



