#include "platform.h"
#include "image.h"
#include "graphics.h"
#include "bitmap.h"
#include "draw2d.h"
#include "acme/exception/exception.h"
#include "aura/graphics/image/icon.h"
#include "aura/graphics/image/drawing.h"
#include "aura/graphics/draw2d/graphics_lease.h"
#include "aura/windowing/window_buffer.h"
#include "aura/user/user/interaction.h"


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


   void image::update_bitmap_as_render_target(
      ::acme::user::interaction * pacmeuserinteractionAffinity, ::draw2d::graphics * pdraw2dgraphics)
   {

      return ::image::image::update_bitmap_as_render_target(
         pacmeuserinteractionAffinity,
         pdraw2dgraphics);

   }


   /*::draw2d::bitmap_pointer image::get_bitmap() const
   {

      return ::image::image::get_bitmap();

   }*/


   ::draw2d::bitmap_pointer image::detach_bitmap()
   {

      return m_pdraw2dbitmap.detach();

   }


   ::image_pixmap_lease image::_map(const ::i32_rectangle & rectangle)
   {

      auto ppixmap = ::transfer(::image::image::_map(rectangle));

      return ::transfer(ppixmap);

      // if (m_ppixmapOwned)
      // {
      //
      //    return {this, m_ppixmapOwned };
      //
      // }
      //
      // construct_newø(m_ppixmapOwned);
      //
      // m_ppixmapOwned->create_as_descriptor(this->raw_size());
      //
      // auto ppixmapOwned = ::transfer(m_ppixmapOwned->map(rectangle, bApplyAlphaTransform));
      //
      // return ::transfer(ppixmapOwned);

      //_on_map(bApplyTransform);

      //return true;

   }


   void image::_unmap(::image_pixmap_lease * pimagepixmaplease)
   {

      ::image::image::_unmap(pimagepixmaplease);
      
      //_on_unmap(bDoUnmap);
      
      //return true;

   }

   
   //bool image::on_host_read_pixels(::pixmap_t* ppixmapHost) const
   //{

   //   if (!ppixmapHost
   //      || !m_bHintCpuBackingEnabled
   //      || !m_ppixmapOwned
   //      || m_ppixmapOwned.m_p != ppixmapHost
   //      || !ppixmapHost->m_pimage32Raw
   //      || ppixmapHost->m_pimage32Raw != m_ppixmapOwned->m_pimage32Raw
   //      || ppixmapHost->m_iScan != m_ppixmapOwned->m_iScan
   //      || ppixmapHost->m_sizeRaw != m_ppixmapOwned->m_sizeRaw
   //      || ppixmapHost->m_point != m_point
   //      || ppixmapHost->m_size != m_size)
   //   {

   //      return false;

   //   }

   //   ::cast < ::draw2d_gdiplus::bitmap > pdraw2dbitmap = m_pdraw2dbitmap;

   //   return pdraw2dbitmap
   //      && pdraw2dbitmap->m_bHintCpuBackingEnabled
   //      && pdraw2dbitmap->m_pdraw2dbitmap
   //      && pdraw2dbitmap->m_pimage32Host == ppixmapHost->m_pimage32Raw
   //      && pdraw2dbitmap->m_iStride == ppixmapHost->m_iScan
   //      && pdraw2dbitmap->size() == m_sizeRaw;

   //}


   //void image::update_as_gpu_render_target(const ::i32_size & sizeRaw, ::user::interaction * puserinteraction, ::draw2d::graphics * pdraw2dgraphics, ::enum_flag eflagCreate, ::i32 iGoodStride, bool bPreserve, bool bTopDraw2d)
   //{

   //   update_as_render_target(sizeRaw, puserinteraction, pdraw2dgraphics, eflagCreate, iGoodStride, bPreserve, bTopDraw2d);

   //}


   void image::update_as_render_target(const ::i32_size & sizeRaw, ::user::interaction * puserinteraction, ::draw2d::graphics * pdraw2dgraphics, ::enum_flag eflagCreate, ::i32 iGoodStride, bool bPreserve, bool bTopDraw2d)
   {

      if (!puserinteraction)
      {

         throw ::exception(
            error_null_pointer,
            "GDI+ render target requires a user interaction");

      }

      m_pacmeuserinteractionAffinity = puserinteraction;

      ::cast < ::draw2d_gdiplus::bitmap > pbitmapCurrent = m_pdraw2dbitmap;

      auto ppixmapOwned = m_ppixmapOwned;

      auto bRebindBitmap = pbitmapCurrent
         && pbitmapCurrent->m_pgdiplusbitmap
         && pbitmapCurrent->size() != sizeRaw;

      ::cast < ::draw2d_gdiplus::graphics > pdraw2dgdiplusgraphics = pdraw2dgraphics;

      if (bRebindBitmap && pdraw2dgdiplusgraphics)
      {

         // A GDI+ Graphics keeps its target bitmap busy and retains its backing
         // address. Close it before preserving or replacing that bitmap.
         pdraw2dgdiplusgraphics->close_graphics();

      }

      //auto bRebindBitmap = pbitmapCurrent
      //   && (pbitmapCurrent->size() != sizeRaw
      //      || (m_bHintCpuBackingEnabled
      //         && ppixmapOwned
      //         && (pbitmapCurrent->m_pimage32Host != ppixmapOwned->m_pimage32Raw
      //            || pbitmapCurrent->m_iStride != ppixmapOwned->m_iScan
      //            || pbitmapCurrent->size() != ppixmapOwned->m_sizeRaw)));

      //::cast < ::draw2d_gdiplus::graphics > pdraw2dgraphics = pdraw2dgraphics;

      //if (bRebindBitmap)
      //{

      //   if (pdraw2dgraphics)
      //   {

      //      pdraw2dgraphics->close_graphics();

      //   }

      //   m_pdraw2dbitmap.release();

      //}

      try
      {

         create_from_data(
            sizeRaw,
            nullptr,
            iGoodStride,
            eflagCreate,
            bPreserve);

         update_bitmap_as_render_target(m_pacmeuserinteractionAffinity, pdraw2dgraphics);

      }
      catch (...)
      {

         if (bRebindBitmap && pdraw2dgraphics && m_pdraw2dbitmap)
         {

            pdraw2dgraphics->create_bitmap_graphics(m_pdraw2dbitmap);

         }

         throw;

      }

      if (bRebindBitmap && pdraw2dgraphics)
      {

         // Keep pbitmapCurrent and ppixmapOwned alive until create_bitmap_graphics
         // has destroyed the GDI+ Graphics that still references their storage.
         pdraw2dgraphics->create_bitmap_graphics(m_pdraw2dbitmap);

      }

      //if (bRebindBitmap && pdraw2dgraphics)
      //if (pdraw2dgraphics)
      //{

      //   pdraw2dgraphics->create_bitmap_graphics(m_pdraw2dbitmap);

      //}

      //constructø(m_pgraphicsOwned);

      //m_pgraphicsOwned->create_for_image(this);

   }


   //bool image::host(::windowing::window_buffer * pwindowbuffer, ::windowing::window * pwindow, const ::i32_size & sizeRaw)
   //{

   //   return ::image::image::host(pwindowbuffer, pwindow, sizeRaw);

   //   //if (!::is_ok(pwindowbuffer->m_ppixmapWindowBuffer))
   //   //{

   //   //   //return false;

   //   //   throw ::exception(error_failed);

   //   //}

   //   //if (m_pdraw2dbitmap.is_set()
   //   //      && m_pdraw2dbitmap->get_os_data() != nullptr
   //   //      && pwindowbuffer->m_pixmap.m_sizeRaw == this->m_sizeRaw
   //   //      && pwindowbuffer->m_pixmap.image32() == image32()
   //   //      && pwindowbuffer->m_pixmap.scan_size() == scan_size())
   //   //{

   //   //   if (pwindowbuffer->m_pixmap.size() != size())
   //   //   {

   //   //      m_size = pwindowbuffer->m_pixmap.size();

   //   //   }

   //   //   return true;

   //   //   //return;

   //   //}

   //   ////destroy();

   //   //defer_constructø(m_pdraw2dbitmap);

   //   ////defer_constructø(m_pgraphics);

   //   ////if (m_pdraw2dbitmap.is_null())
   //   ////{

   //   ////   m_sizeRaw.cx = 0;

   //   ////   m_sizeRaw.cy = 0;

   //   ////   m_sizeAlloc.cx = 0;

   //   ////   m_sizeAlloc.cy = 0;

   //   ////   m_iScan = 0;

   //   ////   return false;

   //   ////}

   //   //
   //   //if (m_pdraw2dbitmap->host_bitmap(nullptr, &pwindowbuffer->m_pixmap))
   //   //{
   //   //   //this->m_sizeRaw = pwindowbuffer->m_pixmap.m_sizeRaw;

   //   //}
   //   ////if (!)
   //   ////{

   //   ////   m_sizeRaw.cx = 0;

   //   ////   m_sizeRaw.cy = 0;

   //   ////   m_sizeAlloc.cx = 0;

   //   ////   m_sizeAlloc.cy = 0;

   //   ////   m_iScan = 0;

   //   ////   return false;

   //   ////}
   //   //   //throw ::exception(error_failed);
   //   ////if (m_pdraw2dbitmap->nok())
   //   ////{

   //   ////   destroy();

   //   ////   return false;

   //   ////}

   //   //initialize_pixmap(pwindowbuffer->m_pixmap.m_sizeRaw, pwindowbuffer->m_pixmap.image32(), pwindowbuffer->m_pixmap.m_iScan);

   //   //m_size = pwindowbuffer->m_pixmap.m_size;

   //   //m_sizeRaw = pwindowbuffer->m_pixmap.size();

   //   //set_ok_flag();

   //   //auto pdraw2dgraphics = acquire_graphics();

   //   //pdraw2dgraphics->m_pimage = this;

   //   //pdraw2dgraphics->reset_impact_area();

   //   //return true;

   //}


   void image::create_from_data(const ::i32_size& size, const ::image32_t * pimage32, ::i32 iScan, ::enum_flag eflagCreate, bool bPreserve)
   {

      if (m_pdraw2dbitmap.is_set()
            && size == m_sizeRaw)
      {

         //auto pdraw2dpen = createø < ::draw2d::pen > ();         return true;

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

        // pbitmapPrevious = m_pdraw2dbitmap;

//         pgraphicsPrevious = m_pgraphics;

//         m_pdraw2dbitmap.create();

//         m_pgraphics.create();

//      }
//      else
//      {

//         m_pdraw2dbitmap.defer_create();

//         m_pgraphics.defer_create();

//      }

      //destroy();

      //if (!i32_size)
      //{

      //   return true;

      //}

      
      auto pdraw2dbitmap = createø < ::draw2d::bitmap >();

      ::cast < ::draw2d_gdiplus::bitmap > pgdiplusbitmap = pdraw2dbitmap;

      //auto pdraw2dgraphics = draw2d()->acquire_memory_graphics(size);

      //if (pdraw2dbitmap.is_null() || pdraw2dgraphics.is_null())
      if (pdraw2dbitmap.is_null())
      {

         //destroy();

         //return false;

         throw ::exception(error_null_pointer);

      }

      //::i32 iScan = 0;

      ::image32_t * pimage32Bitmap = nullptr;

      auto str1 = _001_image32_diagnostics(size, pimage32, iScan);

      information("draw2d_gdiplus::image::create_from_data (1) {}", str1);

      if (size.cx > I32_MAXIMUM / (::i32) sizeof(::image32_t))
      {

         throw ::exception(error_bad_argument);

      }

      auto iMinimumScan = size.cx * (::i32) sizeof(::image32_t);

      if (iScan < iMinimumScan)
      {

         iScan = iMinimumScan;

      }

      auto uNewScanArea = (::u64) iScan * (::u64) size.cy;

      if (uNewScanArea > (::u64) ::numeric_info < memsize >::maximum())
      {

         throw ::exception(error_bad_argument);

      }

      auto iNewScanArea = (memsize) uNewScanArea;

      ::pixmap_pointer ppixmapOwnedNew;

      if (m_bHintCpuBackingEnabled)
      {

         construct_newø(ppixmapOwnedNew);

         ppixmapOwnedNew->create_as_descriptor(size, eflagCreate, iScan);

         if (::is_set(pimage32))
         {

            ppixmapOwnedNew->m_memoryPixmap.assign(pimage32, iNewScanArea);

         }
         else
         {

            ppixmapOwnedNew->m_memoryPixmap.set_size(iNewScanArea);

            if (!ppixmapOwnedNew->m_memoryPixmap.data()
               || ppixmapOwnedNew->m_memoryPixmap.size() < iNewScanArea)
            {

               throw ::exception(error_no_memory);

            }

            ppixmapOwnedNew->m_memoryPixmap.zero();

         }

         ppixmapOwnedNew->m_pimage32Raw =
            (::image32_t *)ppixmapOwnedNew->m_memoryPixmap.data();

         ppixmapOwnedNew->pixmap_map();

      }

      //pdraw2dbitmap->create_bitmap(nullptr, size, &pimage32Bitmap, pimage32, &iScan);

      pdraw2dbitmap->m_bHintCpuBackingEnabled = m_bHintCpuBackingEnabled;

      pdraw2dbitmap->create_bitmap(nullptr, size, ppixmapOwnedNew);

      auto str2 = _001_image32_diagnostics(size, pimage32Bitmap, iScan);

      information("draw2d_gdiplus::image::create_from_data (2) {}", str2);

      //if (!pdraw2dbitmap->create_bitmap(nullptr, size, (void**)&pimage32, &iScan))
      //{

      //   //destroy();

      //   return false;

      //}

      if (pgdiplusbitmap->m_pgdiplusbitmap == nullptr)
      {

         //destroy();

         //return false;

         throw ::exception(error_null_pointer);

      }

      //pdraw2dgraphics->set(pdraw2dbitmap);

      //if (!pdraw2dgraphics->set(pdraw2dbitmap))
      //{

      //   return false;

      //}

      //pdraw2dgraphics->place_impact_area(0., 0., m_sizeRaw.cx, m_sizeRaw.cy);
      //
      //if (!)
      //{

      //   //return false;

      //   throw ::exception(error_null_pointer);

      //}

      if (bPreserve
         && pdraw2dbitmap
         //&& pdraw2dgraphics
          && ::is_null(pimage32)
         && m_pdraw2dbitmap)
         //&& m_pgraphics)
      {

         auto w = minimum(m_pdraw2dbitmap->m_size.cx, pdraw2dbitmap->m_size.cx);

         auto h = minimum(m_pdraw2dbitmap->m_size.cy, pdraw2dbitmap->m_size.cy);

         Gdiplus::Rect rect(0, 0, w, h);

         auto pbitmapNew = pdraw2dbitmap.cast < ::draw2d_gdiplus::bitmap >();

         auto pbitmapPrevious = m_pdraw2dbitmap.cast < ::draw2d_gdiplus::bitmap >();

         Gdiplus::Graphics graphics(pbitmapNew->m_pgdiplusbitmap);

         auto status = graphics.Clear(Gdiplus::Color(0, 0, 0, 0));

         if (status == Gdiplus::Ok)
         {

            status = graphics.SetCompositingMode(Gdiplus::CompositingModeSourceCopy);

         }

         if (status == Gdiplus::Ok)
         {

            status = graphics.DrawImage(
               pbitmapPrevious->m_pgdiplusbitmap,
               rect, 0, 0, w, h, Gdiplus::UnitPixel);

         }

         if (status != Gdiplus::Ok)
         {

            throw ::exception(error_failed);

         }

      }

      m_ppixmapOwned = ppixmapOwnedNew;

      m_pdraw2dbitmap = pdraw2dbitmap;
//
  //    m_pgraphics = pdraw2dgraphics;

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
      
      //m_bMapped = false;

      set_flag(eflagCreate);

      //return true;

   }

   //void image::create(const ::i32_size & size, ::eobject eobjectCreate, ::i32 iGoodStride, bool bPreserve)
   //{

   //   //if (m_pdraw2dbitmap.is_set()
   //   //   && m_pdraw2dbitmap->get_os_data() != nullptr
   //   //   && size == m_sizeRaw)
   //   //{

   //   //   return true;

   //   //}

   //   //::draw2d::bitmap_pointer pbitmapPrevious;

   //   //::draw2d::graphics_pointer pgraphicsPrevious;

   //   //if (bPreserve)
   //   //{

   //   //   pbitmapPrevious = m_pdraw2dbitmap;

   //   //   pgraphicsPrevious = m_pgraphics;

   //   //   m_pdraw2dbitmap.create();

   //   //   m_pgraphics.create();

   //   //}
   //   //else
   //   //{

   //   //   m_pdraw2dbitmap.defer_create();

   //   //   m_pgraphics.defer_create();

   //   //}

   //   ////destroy();

   //   ////if (!i32_size)
   //   ////{

   //   ////   return true;

   //   ////}


   //   //if (m_pdraw2dbitmap.is_null() || m_pgraphics.is_null())
   //   //{

   //   //   destroy();

   //   //   return false;

   //   //}

   //   //::i32 iScan = 0;

   //   //::image32_t * pimage32 = nullptr;

   //   //if (!m_pdraw2dbitmap->create_bitmap(nullptr, size, (void **)&pimage32, &iScan))
   //   //{

   //   //   destroy();

   //   //   return false;

   //   //}

   //   //if (m_pdraw2dbitmap->nok())
   //   //{

   //   //   destroy();

   //   //   return false;

   //   //}

   //   //pixmap::init(size, pimage32, iScan);

   //   //m_pgraphics->set(m_pdraw2dbitmap);
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
   //   //      pbitmapPrevious.cast <::draw2d_gdiplus::bitmap>()->m_pdraw2dbitmap,
   //   //      r, r.X, r.Y, r.Width, r.Height, Gdiplus::UnitPixel);

   //   //}

   //   //m_bMapped = false;

   //   //m_eobject = eobjectCreate;

   //   //return true;

   //}


   // void image::dc_select(bool bSelect)
   // {
   //
   //    //return true;
   //
   // }


   void image::create_from_graphics(::draw2d::graphics * pdraw2dgraphics)
   {

      ::draw2d::bitmap * pdraw2dbitmap = (dynamic_cast<::draw2d_gdiplus::graphics *>(pdraw2dgraphics))->get_current_bitmap();

      if (pdraw2dbitmap == nullptr)
      {

         //return false;

         throw ::exception(error_null_pointer);

      }
      
      create_as_descriptor(pdraw2dbitmap->size());
      //if (!create(pdraw2dbitmap->get_size()))
      //{

      //   return false;

      //}

      auto ppixmapImageThis = this->map();

      auto ppixmapGraphicsImage = pdraw2dgraphics->m_pimage->map();

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


   void image::clear_node_data()
   {

      //::image::image::destroy();

      //return ::success;

   }


   //bool image::to(::draw2d::graphics * pdraw2dgraphics, const ::i32_point & point, const ::i32_size & size, const ::i32_point & pointSrc)
   //{

   //   return pdraw2dgraphics->draw(point, size, get_graphics(), pointSrc);

   //}


   //bool image::stretch(::image::image * pimage)
   //{

   ////   ::draw2d::bitmap_pointer bitmap(get_application());

   ////   bitmap->CreateCompatibleBitmap(pdraw2dgraphics, 1, 1);

   ////   const ::i32_size & size = bitmap->get_size();

   ////   if (!create(size))
   ////   {

   ////      return false;

   ////   }

   ////   HDC hdc = __graphics(pdraw2dgraphics)->get_hdc();

   ////   bool bOk = GetDIBits(hdc, (HBITMAP)bitmap->get_os_data(), 0, height(), m_pimage32Raw, nullptr, DIB_RGB_COLORS) != false;

   ////   g()->set(bitmap);

   ////   __graphics(pdraw2dgraphics)->release_hdc(hdc);

   ////   auto estatus = pdraw2dgraphics->set(bitmap);

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

      if (pimageDst->m_pimagepixmaplease || pimageSrc->m_pimagepixmaplease)
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


   void image::set_image_icon(::image::icon * picon, ::i32 cx, ::i32 cy)
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

      m_pdraw2dbitmap.release();
      //m_pgraphics.release();
      m_hbitmap               = nullptr;
      m_sizeWnd               = ::i64_size(0, 0);
      memset(&m_bitmapinfo, 0, sizeof(m_bitmapinfo));

   }


   bool image::_load_thumbnail(const ::scoped_string & scopedstr)
   {

      auto pgraphicsThis = acquire_graphics();

      ::cast < ::draw2d_gdiplus::graphics > pdraw2dgdiplusgraphics = pgraphicsThis;

      ::Gdiplus::Graphics *pdraw2dgraphics = pdraw2dgdiplusgraphics->m_pgdiplusgraphics;

      wstring wstr(scopedstr);

      // Create an image and a thumbnail of the pimage->
      ::Gdiplus::Image image(wstr);

      auto pthumbnail = as_auto_pointer(image.GetThumbnailImage(width(), height(), nullptr, nullptr));

      // Draw the original and the thumbnail images.
      pdraw2dgraphics->DrawImage(pthumbnail, 0, 0, pthumbnail->GetWidth(), pthumbnail->GetHeight());

      return true;

   }


   // void image::on_exif_orientation()
   // {
   //
   //    ::image::image::on_exif_orientation();
   //
   // }


} // namespace draw2d_gdiplus



