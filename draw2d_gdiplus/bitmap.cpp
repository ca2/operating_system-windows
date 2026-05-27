#include "framework.h"
#include "bitmap.h"
#include "acme/exception/exception.h"
#include "acme/exception/interface_only.h"
#include "acme/graphics/image/pixmap.h"

//#undef ___new


namespace draw2d_gdiplus
{


   bitmap::bitmap()
   {

      m_mem.m_bAligned = true;

      m_pbitmap   = nullptr;
      m_iStride   = 0;

   }

   bitmap::~bitmap()
   {

      destroy();

   }

   
   void bitmap::destroy()
   {

      ::acme::del(m_pbitmap);

      ::draw2d::bitmap::destroy();

      //return ::success;

   }


   bool bitmap::CreateBitmap(::draw2d::graphics * pgraphics, ::i32 nWidth, ::i32 nHeight, UINT nPlanes, UINT nBitcount, const void * pBits, ::i32 stride)

   {

      __UNREFERENCED_PARAMETER(pgraphics);

      ::acme::del(m_pbitmap);

      m_pbitmap = øraw_new ::Gdiplus::Bitmap(nWidth, nHeight, Gdiplus::PixelOffsetModeHighQuality);

      m_osdata[0] = m_pbitmap;

      return true;

   }

   bool bitmap::CreateBitmapIndirect(::draw2d::graphics * pgraphics, LPBITMAP pBitmap)

   {

      __UNREFERENCED_PARAMETER(pgraphics);

      return false;
   }


   bool bitmap::host_bitmap(::draw2d::graphics * pgraphics, pixmap * ppixmap)
   {

      if (ppixmap->m_sizeRaw == m_size)
      {

         return true;

      }

      __UNREFERENCED_PARAMETER(pgraphics);

      ::acme::del(m_pbitmap);

      m_iStride = ppixmap->m_iScan;

      if (ppixmap->image32() == nullptr)
      {

         //return false;

         throw ::exception(error_failed);

      }

      m_pbitmap = øraw_new Gdiplus::Bitmap(ppixmap->m_sizeRaw.cx, ppixmap->m_sizeRaw.cy, m_iStride, PixelFormat32bppPARGB, (BYTE *) ppixmap->image32());

      if (m_pbitmap == nullptr)
      {

         //return false;

         throw ::exception(error_failed);

      }

      m_osdata[0] = m_pbitmap;

      m_size = ppixmap->m_size;

      return true;

   }


   void bitmap::create_bitmap(::draw2d::graphics* pgraphics, const ::i32_size& size, void** ppvBits, ::i32* stride)
   {

      if (size == m_size)
      {

         //return true;

         return;

      }

      BITMAPINFO info = {};

      info.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
      info.bmiHeader.biWidth = size.cx;
      info.bmiHeader.biHeight = -size.cy;
      info.bmiHeader.biPlanes = 1;
      info.bmiHeader.biBitCount = 32;
      info.bmiHeader.biCompression = BI_RGB;
      info.bmiHeader.biSizeImage = size.area() * sizeof(::color::color);

      const BITMAPINFO* pbmi = &info;

      __UNREFERENCED_PARAMETER(pgraphics);

      ::acme::del(m_pbitmap);

      m_iStride = 4 * pbmi->bmiHeader.biWidth;

      m_mem.set_size(abs(m_iStride * pbmi->bmiHeader.biHeight));

      if (m_mem.data() == nullptr)
      {

         //return false;

         return;

      }

      m_pbitmap = øraw_new Gdiplus::Bitmap(abs(pbmi->bmiHeader.biWidth), abs(pbmi->bmiHeader.biHeight),m_iStride, PixelFormat32bppPARGB, (BYTE *)m_mem.data());

      if(m_pbitmap == nullptr)
      {

         throw ::exception(error_failed);

      }

      if(ppvBits != nullptr)
      {

         *ppvBits = m_mem.data();

      }

      if(stride != nullptr)
      {

         *stride = m_iStride;

      }

      m_osdata[0] = m_pbitmap;

      m_size = size;

      //return true;

   }


   void bitmap::CreateDIBitmap(::draw2d::graphics * pgraphics, ::i32 cx, ::i32 cy, ::u32 flInit, const void *pjBits, UINT iUsage)
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

   
   i32_size bitmap::GetBitmapDimension() const
   {

      if (m_pbitmap == nullptr)
      {

         return ::i32_size(0, 0);

      }

      return ::i32_size(m_pbitmap->GetWidth(), m_pbitmap->GetHeight());

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


   void bitmap::CreateCompatibleBitmap(::draw2d::graphics * pgraphics, ::i32 nWidth, ::i32 nHeight)
   {

      {

         ::acme::del(m_pbitmap);

         m_pbitmap = øraw_new ::Gdiplus::Bitmap(nWidth, nHeight, Gdiplus::PixelOffsetModeHighQuality);

      }

      m_osdata[0] = m_pbitmap;

      //return true;

   }


   void bitmap::CreateDiscardableBitmap(::draw2d::graphics * pgraphics, ::i32 nWidth, ::i32 nHeight)
   {

      ::acme::del(m_pbitmap);

      m_pbitmap = øraw_new ::Gdiplus::Bitmap(nWidth, nHeight, Gdiplus::PixelOffsetModeHighQuality);

      m_osdata[0] = m_pbitmap;

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


   void bitmap::attach(void * posdata)
   {

      ::acme::del(m_pbitmap);

      m_pbitmap = (Gdiplus::Bitmap *) posdata;

      m_osdata[0] = m_pbitmap;

      //return true;

   }


   void * bitmap::detach()
   {

      Gdiplus::Bitmap * pbitmap = m_pbitmap;

      m_pbitmap = nullptr;

      clear_os_data();

      return m_pbitmap;

   }


   HBITMAP bitmap::_GetHBITMAP()
   {

      if(m_pbitmap == nullptr)
         return nullptr;

      HBITMAP hbitmap = nullptr;

      Gdiplus::Color colorBk(0,0,0,0);

      m_pbitmap->GetHBITMAP(colorBk,&hbitmap);

      return hbitmap;

   }


   void bitmap::_ReleaseHBITMAP(HBITMAP hbitmap)
   {

      ::DeleteObject(hbitmap);

   }


} // namespace draw2d_gdiplus



