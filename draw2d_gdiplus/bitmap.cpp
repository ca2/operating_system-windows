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


   bool bitmap::CreateBitmap(::draw2d::graphics * pgraphics, int nWidth, int nHeight, UINT nPlanes, UINT nBitcount, const void * pBits, int stride)

   {

      __UNREFERENCED_PARAMETER(pgraphics);

      ::acme::del(m_pbitmap);

      m_pbitmap = __raw_new ::Gdiplus::Bitmap(nWidth, nHeight, Gdiplus::PixelOffsetModeHighQuality);

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

      m_pbitmap = __raw_new Gdiplus::Bitmap(ppixmap->m_sizeRaw.cx(), ppixmap->m_sizeRaw.cy(), m_iStride, PixelFormat32bppPARGB, (BYTE *) ppixmap->image32());

      if (m_pbitmap == nullptr)
      {

         //return false;

         throw ::exception(error_failed);

      }

      m_osdata[0] = m_pbitmap;

      m_size = ppixmap->m_size;

      return true;

   }


   void bitmap::create_bitmap(::draw2d::graphics* pgraphics, const ::int_size& size, void** ppvBits, int* stride)
   {

      if (size == m_size)
      {

         //return true;

         return;

      }

      BITMAPINFO info = {};

      info.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
      info.bmiHeader.biWidth = size.cx();
      info.bmiHeader.biHeight = -size.cy();
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

      m_pbitmap = __raw_new Gdiplus::Bitmap(abs(pbmi->bmiHeader.biWidth), abs(pbmi->bmiHeader.biHeight),m_iStride, PixelFormat32bppPARGB, (BYTE *)m_mem.data());

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


   void bitmap::CreateDIBitmap(::draw2d::graphics * pgraphics, int cx, int cy, unsigned int flInit, const void *pjBits, UINT iUsage)
   {
      //return false;
   }


   unsigned int bitmap::SetBitmapBits(unsigned int dwCount, const void * pBits)

   {

      //return ::SetBitmapBits((HBITMAP)get_handle(), dwCount, pBits);

      return 0;

   }
   unsigned int bitmap::GetBitmapBits(unsigned int dwCount, LPVOID pBits) const

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

   int_size bitmap::SetBitmapDimension(int nWidth, int nHeight)
   {


      throw ::interface_only();

      //::int_size size;
      //VERIFY(::SetBitmapDimensionEx((HBITMAP)get_handle(), nWidth, nHeight, &size));
      //return size;
      return ::int_size(0, 0);

   }

   
   int_size bitmap::GetBitmapDimension() const
   {

      if (m_pbitmap == nullptr)
      {

         return ::int_size(0, 0);

      }

      return ::int_size(m_pbitmap->GetWidth(), m_pbitmap->GetHeight());

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


   void bitmap::CreateCompatibleBitmap(::draw2d::graphics * pgraphics, int nWidth, int nHeight)
   {

      {

         ::acme::del(m_pbitmap);

         m_pbitmap = __raw_new ::Gdiplus::Bitmap(nWidth, nHeight, Gdiplus::PixelOffsetModeHighQuality);

      }

      m_osdata[0] = m_pbitmap;

      //return true;

   }


   void bitmap::CreateDiscardableBitmap(::draw2d::graphics * pgraphics, int nWidth, int nHeight)
   {

      ::acme::del(m_pbitmap);

      m_pbitmap = __raw_new ::Gdiplus::Bitmap(nWidth, nHeight, Gdiplus::PixelOffsetModeHighQuality);

      m_osdata[0] = m_pbitmap;

      //return true;

   }


   int bitmap::GetBitmap(BITMAP* pBitMap)
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



