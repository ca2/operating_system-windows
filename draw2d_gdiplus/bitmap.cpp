#include "platform.h"
#include "bitmap.h"
#include "image.h"
#include "acme/exception/exception.h"
#include "acme/exception/interface_only.h"
#include "acme/graphics/image/pixmap.h"

//#undef ___new


CLASS_DECL_IMPORT ::string _001_gdiplus_bitmap_diagnostics(Gdiplus::Bitmap *bitmap);


namespace draw2d_gdiplus
{


   bitmap::bitmap()
   {

      m_mem.m_bAligned = true;

      //m_pgdiplusbitmap   = nullptr;

      //m_pimage32Host = nullptr;

      m_iStride   = 0;

   }


   bitmap::bitmap(bitmap&& bitmap) :
      DRAW2D_BITMAP_TRANSFER(bitmap),
      m_pgdiplusbitmap(::transfer(bitmap.m_pgdiplusbitmap)),
      m_mem(::transfer(bitmap.m_mem))//,
      //m_pimage32Host(bitmap.m_pimage32Host)
   {

      //bitmap.m_pimage32Host = nullptr;
      bitmap.m_size.set_null();

   }


   bitmap::~bitmap()
   {

      destroy();

   }


   void bitmap::clear_node_data()
   {

      m_pgdiplusbitmap.destroy();

      //m_pimage32Host = nullptr;

      //::draw2d::bitmap::destroy();

      //return ::success;

   }


   void bitmap::update_bitmap_as_image_render_target(
      ::image::image * pimage,
      ::acme::user::interaction * pacmeuserinteractionAffinity,
      ::draw2d::graphics * pdraw2dgraphics)
   {

      __UNREFERENCED_PARAMETER(pacmeuserinteractionAffinity);

      auto ppixmapOwned = pimage->m_ppixmapOwned;

      //if (m_bHintCpuBackingEnabled
      //   && ppixmapOwned
      //   && ppixmapOwned->m_pimage32Raw
      //   && ppixmapOwned->m_iScan
      //      >= ppixmapOwned->m_sizeRaw.cx * (::i32) sizeof(::image32_t))
      //{

      //   host_bitmap(pdraw2dgraphics, ppixmapOwned);

      //}
      //else
      {

         create_bitmap(pdraw2dgraphics, pimage->raw_size(), ppixmapOwned);

      }

      pimage->m_pdraw2dbitmap = this;

      //pimage->m_pimage32Raw = (::image32_t *) pimage->m_memoryPixmap.data();

      //pimage->m_pimage32 = (::image32_t*)pimage->m_memoryPixmap.data();

      //pimage->m_bMapped = true;

      //pimage->m_interlockedcountMap = 1;

   }


   void bitmap::preserve_image(const ::i32_size& size, ::image::image* pimage)
   {

      auto bitmap = ::transfer(*this);

      update_bitmap_as_image_render_target(pimage);

      pimage->m_pdraw2dbitmap = this;

   }


   bool bitmap::CreateBitmap(::draw2d::graphics * pdraw2dgraphics, ::i32 nWidth, ::i32 nHeight, UINT nPlanes, UINT nBitcount, const void * pBits, ::i32 stride)

   {

      __UNREFERENCED_PARAMETER(pdraw2dgraphics);

      //m_pgdiplusbitmap.destroy();

      //m_pimage32Host = nullptr;

      m_pgdiplusbitmap = ::as_pointer(new ::Gdiplus::Bitmap(nWidth, nHeight, Gdiplus::PixelOffsetModeHighQuality));

      //m_osdata[0] = m_pgdiplusbitmap;

      return true;

   }


   bool bitmap::CreateBitmapIndirect(::draw2d::graphics * pdraw2dgraphics, LPBITMAP pBitmap)
   {

      __UNREFERENCED_PARAMETER(pdraw2dgraphics);

      return false;
   }


   //bool bitmap::host_bitmap(::draw2d::graphics * pdraw2dgraphics, pixmap_t * ppixmap)
   //{

   //   __UNREFERENCED_PARAMETER(pdraw2dgraphics);

   //   ::acme::del(m_pgdiplusbitmap);

   //   m_pimage32Host = nullptr;

   //   m_iStride = ppixmap->m_iScan;

   //   if (!ppixmap->m_pimage32Raw
   //      || ppixmap->m_sizeRaw.is_empty()
   //      || m_iStride
   //         < ppixmap->m_sizeRaw.cx * (::i32) sizeof(::image32_t))
   //   {

   //      //return false;

   //      throw ::exception(error_failed);

   //   }

   //   m_pgdiplusbitmap = øraw_new Gdiplus::Bitmap(
   //      ppixmap->m_sizeRaw.cx,
   //      ppixmap->m_sizeRaw.cy,
   //      m_iStride,
   //      PixelFormat32bppPARGB,
   //      (BYTE *) ppixmap->m_pimage32Raw);

   //   if (m_pgdiplusbitmap == nullptr)
   //   {

   //      //return false;

   //      throw ::exception(error_failed);

   //   }

   //   m_pimage32Host = ppixmap->m_pimage32Raw;

   //   m_osdata[0] = m_pgdiplusbitmap;

   //   m_size = ppixmap->m_sizeRaw;

   //   set_ok_flag();

   //   m_estatus = ::success;

   //   return true;

   //}


   void bitmap::create_bitmap(::draw2d::graphics* pdraw2dgraphics, const ::i32_size& size, ::pixmap * ppixmapOwned)
   {

      if (size == m_size)
      {

         //return true;

         return;

      }

      if (size.is_empty()
         || size.cx > I32_MAXIMUM / (::i32) sizeof(::image32_t))
      {

         throw ::exception(error_bad_argument);

      }

      __UNREFERENCED_PARAMETER(pdraw2dgraphics);

      //BITMAPINFO info = {};

      //info.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
      //info.bmiHeader.biWidth = size.cx;
      //info.bmiHeader.biHeight = -size.cy;
      //info.bmiHeader.biPlanes = 1;
      //info.bmiHeader.biBitCount = 32;
      //info.bmiHeader.biCompression = BI_RGB;
      //info.bmiHeader.biSizeImage = size.area() * sizeof(::color::color);

      //const BITMAPINFO* pbmi = &info;

      //m_pgdiplusbitmap.destroy();

      //m_pimage32Host = nullptr;

      m_iStride = (::i32) sizeof(::image32_t) * size.cx;
         
      ::i32 iScan = m_iStride;

      if (ppixmapOwned && ppixmapOwned->m_iScan > iScan)
      {

         iScan = ppixmapOwned->m_iScan;

      }

      auto uBitmapSize = (::u64) iScan * (::u64) size.cy;

      if (uBitmapSize > (::u64) ::numeric_info < memsize >::maximum())
      {

         throw ::exception(error_bad_argument);

      }

      auto iBitmapSize = (memsize) uBitmapSize;

      if (m_bHintCpuBackingEnabled)
      {

         if (ppixmapOwned && ppixmapOwned->m_memoryPixmap.size() >= iBitmapSize)
         {

            m_mem.reference_data(ppixmapOwned->m_memoryPixmap);

            m_iStride = iScan;

         }
         else
         {

            m_mem.set_size(iBitmapSize);

            if (ppixmapOwned)
            {

               ppixmapOwned->m_memoryPixmap.reference_data(m_mem);

            }

         }

         if (m_mem.data() == nullptr)
         {

            //return false;

            return;

         }

      }

      //auto pimage32Map = (::image32_t *)m_mem.data();

      //::i32 iStrideSrc = size.cx * 4;

      //if (stride && *stride > iStrideSrc)
      //{

      //   iStrideSrc = *stride;

      //}

      //if (pimage32)
      //{

      //   pimage32Map->copy(size, m_iStride, pimage32, iStrideSrc);

      //}

      if (m_bHintCpuBackingEnabled)
      {

         m_pgdiplusbitmap = ::as_pointer(new Gdiplus::Bitmap(size.cx, size.cy, m_iStride, PixelFormat32bppPARGB, (BYTE *)m_mem.data()));

      }
      else
      {

         m_pgdiplusbitmap = ::as_pointer(new Gdiplus::Bitmap(size.cx, size.cy, PixelFormat32bppPARGB));

         if (::is_set(ppixmapOwned))
         {

            write_pixels(ppixmapOwned->size(), {}, ppixmapOwned->data(), ppixmapOwned->m_iScan);

         }

      }

      if(m_pgdiplusbitmap == nullptr)
      {

         throw ::exception(error_failed);

      }

      //if(ppimage32 != nullptr)
      //{

      //   *ppimage32 = (::image32_t *) m_mem.data();

      //}

      if(ppixmapOwned)
      {

         ppixmapOwned->m_iScan = m_iStride;

      }

      //m_osdata[0] = m_pgdiplusbitmap;

      m_size = size;

      set_ok_flag();

      m_estatus = ::success;

      //return true;

   }


   void bitmap::CreateDIBitmap(::draw2d::graphics * pdraw2dgraphics, ::i32 cx, ::i32 cy, ::u32 flInit, const void *pjBits, UINT iUsage)
   {
      //return false;
   }


   ::u32 bitmap::SetBitmapBits(::u32 dwCount, const void * pBits)

   {

      //return ::SetBitmapBits((HBITMAP)get_handle(), dwCount, pBits);

      return 0;

   }
   ::u32 bitmap::GetBitmapBits(::u32 dwCount, LPVOID pBits) const

   {
      //return ::GetBitmapBits((HBITMAP)get_handle(), dwCount, pBits);

      return 0;
   }
   bool bitmap::LoadBitmap(const ::scoped_string & scopedstrResourceName)

   {
      //   return attach(::LoadBitmap(::aura::FindResourceHandle(
      //pszResourceName, RT_BITMAP), pszResourceName));

      return false;

   }

   i32_size bitmap::SetBitmapDimension(::i32 nWidth, ::i32 nHeight)
   {


      throw ::interface_only();

      //::i32_size size;
      //VERIFY(::SetBitmapDimensionEx((HBITMAP)get_handle(), nWidth, nHeight, &size));
      //return size;
      return ::i32_size(0, 0);

   }

   
   i32_size bitmap::size() const
   {

      if (m_pgdiplusbitmap == nullptr)
      {

         return ::i32_size(0, 0);

      }

      return ::i32_size(m_pgdiplusbitmap->GetWidth(), m_pgdiplusbitmap->GetHeight());

   }


   //i32_size bitmap::size() const
   //{

   //   return GetBitmapDimension();

   //}


   void bitmap::set_size(const ::i32_size & size, bool bPreserve)
   {

      if (size.cx <= 0 || size.cy <= 0)
      {

         throw ::exception(error_bad_argument);

      }

      auto sizeOld = this->size();

      if (size == sizeOld)
      {

         return;

      }

      auto pbitmapNew = øraw_new ::Gdiplus::Bitmap(
         size.cx,
         size.cy,
         PixelFormat32bppPARGB);

      if (!pbitmapNew || pbitmapNew->GetLastStatus() != Gdiplus::Ok)
      {

         ::acme::del(pbitmapNew);

         throw ::exception(error_failed);

      }

      if (bPreserve)
      {

         Gdiplus::Status status;

         {

            Gdiplus::Graphics graphics(pbitmapNew);

            status = graphics.Clear(Gdiplus::Color(0, 0, 0, 0));

            if (status == Gdiplus::Ok)
            {

               status = graphics.SetCompositingMode(Gdiplus::CompositingModeSourceCopy);

            }

            if (status == Gdiplus::Ok && m_pgdiplusbitmap)
            {

               status = graphics.DrawImage(
                  m_pgdiplusbitmap,
                  0,
                  0,
                  (INT)m_pgdiplusbitmap->GetWidth(),
                  (INT)m_pgdiplusbitmap->GetHeight());

            }

         }

         if (status != Gdiplus::Ok)
         {

            ::acme::del(pbitmapNew);

            throw ::exception(error_failed);

         }

      }

      m_pgdiplusbitmap = ::as_pointer(pbitmapNew);
      //m_pimage32Host = nullptr;
      //m_osdata[0] = m_pgdiplusbitmap;
      m_size = size;
      m_iStride = size.cx * (::i32) sizeof(::image32_t);

   }


   bool bitmap::LoadBitmap(UINT nIDResource)
   {
      //return attach(::LoadBitmap(::aura::FindResourceHandle(MAKEINTRESOURCE(nIDResource), RT_BITMAP), MAKEINTRESOURCE(nIDResource)));
      return false;
   }
   bool bitmap::LoadOEMBitmap(UINT nIDBitmap)
   {
      //return attach(::LoadBitmap(nullptr, MAKEINTRESOURCE(nIDBitmap)));
      return false;

   }


   void bitmap::CreateCompatibleBitmap(::draw2d::graphics * pdraw2dgraphics, ::i32 nWidth, ::i32 nHeight)
   {

      {

         //::acme::del(m_pgdiplusbitmap);

         //m_pimage32Host = nullptr;

         m_pgdiplusbitmap = ::as_pointer(new ::Gdiplus::Bitmap(nWidth, nHeight, Gdiplus::PixelOffsetModeHighQuality));

      }

      //m_osdata[0] = m_pgdiplusbitmap;

      //return true;

   }


   void bitmap::CreateDiscardableBitmap(::draw2d::graphics * pdraw2dgraphics, ::i32 nWidth, ::i32 nHeight)
   {

      // ::acme::del(m_pgdiplusbitmap);

      //m_pimage32Host = nullptr;

      m_pgdiplusbitmap = ::as_pointer(new ::Gdiplus::Bitmap(nWidth, nHeight, Gdiplus::PixelOffsetModeHighQuality));

      //m_osdata[0] = m_pgdiplusbitmap;

      //return true;

   }


   ::i32 bitmap::GetBitmap(BITMAP* pBitMap)
   {
      //   ASSERT(get_handle() != nullptr);
      // return ::GetObject(get_handle(), sizeof(BITMAP), pBitMap);
      return 0;
   }


//#ifdef DEBUG
//   /////////////////////////////////////////////////////////////////////////////
//
//
//   void bitmap::dump(dump_context & dumpcontext) const
//   {
//      ::draw2d::object::dump(dumpcontext);
//
//      /*         if (get_handle() == nullptr)
//                  return;
//
//               if (!::windows_definition::Data.bWin95 && ::GetObjectType(get_handle()) != OBJ_BITMAP)
//               {
//                  // not a valid object
//                  dumpcontext << "has ILLEGAL HBITMAP!";
//                  return;
//               }*/
//
//      /*BITMAP bm;
//      VERIFY(GetObject(sizeof(bm), &bm));
//      dumpcontext << "bm.bmType = " << bm.bmType;
//      dumpcontext << "\nbm.bmHeight = " << bm.bmHeight;
//      dumpcontext << "\nbm.bmWidth = " << bm.bmWidth;
//      dumpcontext << "\nbm.bmWidthBytes = " << bm.bmWidthBytes;
//      dumpcontext << "\nbm.bmPlanes = " << bm.bmPlanes;
//      dumpcontext << "\nbm.bmBitsPixel = " << bm.bmBitsPixel;
//      */
//      dumpcontext << "\n";
//   }
//
//
//#endif


   //void bitmap::attach(void * posdata)
   //{

   //   ::acme::del(m_pgdiplusbitmap);

   //   //m_pimage32Host = nullptr;

   //   m_pgdiplusbitmap = (Gdiplus::Bitmap *) posdata;

   //   //m_osdata[0] = m_pgdiplusbitmap;

   //   //return true;

   //}


   //void * bitmap::detach()
   //{

   //   Gdiplus::Bitmap * pdraw2dbitmap = m_pgdiplusbitmap;

   //   m_pgdiplusbitmap = nullptr;

   //   //m_pimage32Host = nullptr;

   //   //clear_os_data();

   //   return m_pgdiplusbitmap;

   //}


   HBITMAP bitmap::_GetHBITMAP()
   {

      if(m_pgdiplusbitmap == nullptr)
         return nullptr;

      HBITMAP hbitmap = nullptr;

      Gdiplus::Color colorBk(0,0,0,0);

      m_pgdiplusbitmap->GetHBITMAP(colorBk,&hbitmap);

      return hbitmap;

   }


   void bitmap::_ReleaseHBITMAP(HBITMAP hbitmap)
   {

      ::DeleteObject(hbitmap);

   }


   ::string bitmap::_001_os_bitmap_diagnostics()
   {


      return _001_gdiplus_bitmap_diagnostics(m_pgdiplusbitmap);

   }


   void bitmap::read_pixels(
      const ::i32_size & size,
      const ::i32_point & point,
      ::image32_t * pimage32,
      ::i32 iScan)
   {

      if (size.cx <= 0 || size.cy <= 0)
      {

         return;

      }

      if (!m_pgdiplusbitmap || !pimage32)
      {

         throw ::exception(error_null_pointer);

      }

      if (iScan < size.cx * (::i32) sizeof(::image32_t))
      {

         throw ::exception(error_bad_argument);

      }

      auto sizeBitmap = this->size();

      if (point.x < 0 || point.y < 0
         || point.x > sizeBitmap.cx - size.cx
         || point.y > sizeBitmap.cy - size.cy)
      {

         throw ::exception(error_bad_argument);

      }

      Gdiplus::Rect rect(point.x, point.y, size.cx, size.cy);

      Gdiplus::BitmapData bitmapdata{};

      auto status = m_pgdiplusbitmap->LockBits(&rect, Gdiplus::ImageLockModeRead, PixelFormat32bppPARGB, &bitmapdata);

      if (status != Gdiplus::Ok)
      {

         throw ::exception(error_failed);

      }

      auto pimage32Source = (image32_t *) bitmapdata.Scan0;

      auto iScanSource = bitmapdata.Stride;

      auto pimage32Target = pimage32;

      auto iScanTarget = iScan;

      try
      {

         pimage32Target->copy(size, iScanTarget, pimage32Source, iScanSource);

      }
      catch (...)
      {

         m_pgdiplusbitmap->UnlockBits(&bitmapdata);

         throw;

      }

      status = m_pgdiplusbitmap->UnlockBits(&bitmapdata);

      if (status != Gdiplus::Ok)
      {

         throw ::exception(error_failed);

      }

   }


   bool bitmap::is_cpu_backed_by(const ::pixmap_t * ppixmap) const
   {

      return m_bHintCpuBackingEnabled
         && m_pgdiplusbitmap
         && ppixmap
         && ppixmap->m_pimage32Raw
         && m_mem.data() == (::u8 *) ppixmap->m_pimage32Raw
         && m_iStride == ppixmap->m_iScan
         && size() == ppixmap->m_sizeRaw;

   }


   void bitmap::write_pixels(
      const ::i32_size & size,
      const ::i32_point & point,
      const ::image32_t * pimage32,
      ::i32 iScan)
   {

      if (size.cx <= 0 || size.cy <= 0)
      {

         return;

      }

      if (!m_pgdiplusbitmap || !pimage32)
      {

         throw ::exception(error_null_pointer);

      }

      if (iScan < size.cx * (::i32) sizeof(::image32_t))
      {

         throw ::exception(error_bad_argument);

      }

      auto sizeBitmap = this->size();

      if (point.x < 0 || point.y < 0
         || point.x > sizeBitmap.cx - size.cx
         || point.y > sizeBitmap.cy - size.cy)
      {

         throw ::exception(error_bad_argument);

      }

      Gdiplus::Rect rect(point.x, point.y, size.cx, size.cy);

      Gdiplus::BitmapData bitmapdata{};

      auto status = m_pgdiplusbitmap->LockBits(&rect, Gdiplus::ImageLockModeWrite, PixelFormat32bppPARGB, &bitmapdata);

      if (status != Gdiplus::Ok)
      {

         throw ::exception(error_failed);

      }

      auto pimage32Target = (image32_t *) bitmapdata.Scan0;

      auto iScanTarget = bitmapdata.Stride;

      auto pimage32Source = pimage32;

      auto iScanSource = iScan;

      try
      {

         pimage32Target->copy(size, iScanTarget, pimage32Source, iScanSource);

      }
      catch (...)
      {

         m_pgdiplusbitmap->UnlockBits(&bitmapdata);

         throw;

      }

      status = m_pgdiplusbitmap->UnlockBits(&bitmapdata);

      if (status != Gdiplus::Ok)
      {

         throw ::exception(error_failed);

      }

   }


} // namespace draw2d_gdiplus



