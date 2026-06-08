//
// Created by camilo on 2026-06-08.
//
#include "framework.h"
#include "image.h"
#include "acme/prototype/geometry2d/size.h"
#include <objidl.h>


namespace nano_graphics_gdiplus
{


   image::image()
   {

      m_iStride = 0;

   }


   image::~image()
   {


   }


   ::i32_size image::size() const
   {

      return m_size;

   }


   void image::create_image(const ::i32_size & size)
   {

      m_pbitmap.release();
      m_memory.set_size(0);
      m_size = {};
      m_iStride = 0;

      if (size.cx <= 0 || size.cy <= 0)
      {

         return;

      }

      if (size.cx > I32_MAXIMUM / 4)
      {

         throw ::exception(error_bad_argument);

      }

      m_iStride = size.cx * 4;

      auto sizeMemory = (memsize) m_iStride * size.cy;

      if (sizeMemory / m_iStride != size.cy)
      {

         throw ::exception(error_bad_argument);

      }

      m_memory.set_size(sizeMemory);
      m_memory.zero();

      m_pbitmap = new ::Gdiplus::Bitmap(
         size.cx,
         size.cy,
         m_iStride,
         PixelFormat32bppARGB,
         (::BYTE *) m_memory.data());

      if (!m_pbitmap || m_pbitmap->GetLastStatus() != ::Gdiplus::Ok)
      {

         m_pbitmap.release();
         m_memory.set_size(0);
         m_iStride = 0;

         throw ::exception(error_failed);

      }

      m_size = size;

   }


   void * image::get_buffer()
   {

      return m_memory.data();

   }


   void image::load_image_file(const void * p, memsize size)
   {

      if (!p || size <= 0 || size > U32_MAXIMUM)
      {

         throw ::exception(error_bad_argument);

      }

      auto hglobal = ::GlobalAlloc(GMEM_MOVEABLE, (SIZE_T) size);

      if (!hglobal)
      {

         throw ::exception(error_no_memory);

      }

      auto pglobal = ::GlobalLock(hglobal);

      if (!pglobal)
      {

         ::GlobalFree(hglobal);

         throw ::exception(error_failed);

      }

      ::memory_copy(pglobal, p, size);
      ::GlobalUnlock(hglobal);

      IStream * pstream = nullptr;

      if (FAILED(::CreateStreamOnHGlobal(hglobal, TRUE, &pstream)))
      {

         ::GlobalFree(hglobal);

         throw ::exception(error_failed);

      }

      auto pimageSource = øraw_new ::Gdiplus::Image(pstream, FALSE);

      if (pimageSource->GetLastStatus() != ::Gdiplus::Ok)
      {

         delete pimageSource;
         pstream->Release();

         throw ::exception(error_failed);

      }

      auto width = pimageSource->GetWidth();
      auto height = pimageSource->GetHeight();

      if (width > I32_MAXIMUM || height > I32_MAXIMUM)
      {

         delete pimageSource;
         pstream->Release();

         throw ::exception(error_bad_argument);

      }

      try
      {

         create_image({ (::i32) width, (::i32) height });

      }
      catch (...)
      {

         delete pimageSource;
         pstream->Release();

         throw;

      }

      ::Gdiplus::Graphics graphics(m_pbitmap);
      graphics.SetCompositingMode(::Gdiplus::CompositingModeSourceCopy);

      auto status = graphics.DrawImage(pimageSource, 0, 0, width, height);

      delete pimageSource;
      pstream->Release();

      if (status != ::Gdiplus::Ok)
      {

         throw ::exception(error_failed);

      }

   }


} // namespace nano_graphics_gdiplus
