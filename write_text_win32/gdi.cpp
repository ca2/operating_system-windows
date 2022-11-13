#include "framework.h"


namespace windowing_win32
{


   CLASS_DECL_WINDOWING_WIN32 HBITMAP create_alpha_bitmap_v5(const ::image * pimage)
   {

      if (!pimage->is_ok())
      {

         return nullptr;

      }

      //   HDC hMemDC;
      ::u32 dwWidth, dwHeight;
      BITMAPV5HEADER bi;
      // HBITMAP hOldBitmap;
      HBITMAP hBitmap;
      void * pBits;

      hcursor hAlphaCursor = nullptr;

      dwWidth = pimage->width();  // width of the Bitmap V5 Dib bitmap
      dwHeight = pimage->height();  // height of the Bitmap V5 Dib bitmap

      ZeroMemory(&bi, sizeof(BITMAPV5HEADER));
      bi.bV5Size = sizeof(BITMAPV5HEADER);
      bi.bV5Width = dwWidth;
      bi.bV5Height = -(::i32)dwHeight;
      bi.bV5Planes = 1;
      bi.bV5BitCount = 32;
      bi.bV5Compression = BI_BITFIELDS;
      // The following mask specification specifies a supported 32 BPP
      // alpha format for Windows XP.
      bi.bV5RedMask = 0x00FF0000;
      bi.bV5GreenMask = 0x0000FF00;
      bi.bV5BlueMask = 0x000000FF;
      bi.bV5AlphaMask = 0xFF000000;

      HDC hdc;
      hdc = GetDC(nullptr);

      // Create the DIB section with an alpha channel.
      hBitmap = CreateDIBSection(hdc, (BITMAPINFO *)&bi, DIB_RGB_COLORS, (void **)&pBits, nullptr, (::u32)0);


      //hMemDC = CreateCompatibleDC(hdc);
      ReleaseDC(nullptr, hdc);

      // Draw something on the DIB section.
      //hOldBitmap = (HBITMAP)set(hMemDC,hBitmap);
      //PatBlt(hMemDC,0,0,dwWidth,dwHeight,WHITENESS);
      //SetTextColor(hMemDC,rgb(0,0,0));
      //SetBkMode(hMemDC,TRANSPARENT);
      //text_out(hMemDC,0,9,"rgba",4);
      //set(hMemDC,hOldBitmap);
      //DeleteDC(hMemDC);

      // Set the alpha values for each pixel in the cursor so that
      // the complete cursor is semi-transparent.

      int iStrideDst = dwWidth * sizeof(color32_t);

      ::copy_colorref((color32_t *)pBits, pimage->width(), pimage->height(), iStrideDst, pimage->get_data(), pimage->scan_size());

      return hBitmap;

   }


   HCURSOR create_alpha_icon(const ::image * pimage, bool bIcon, int xHotSpot, int yHotSpot)
   {

      if (!pimage->is_ok())
      {

         return nullptr;

      }

      HBITMAP hBitmap = create_alpha_bitmap_v5(pimage);

      // Create an empty mask bitmap.
      HBITMAP hMonoBitmap = ::CreateBitmap(pimage->width(), pimage->height(), 1, 1, nullptr);

      if (bIcon)
      {
      
         xHotSpot = 0;
         yHotSpot = 0;

      }

      ICONINFO ii;
      ii.fIcon = bIcon ? true : false;  // Change fIcon to true to create an alpha icon
      ii.xHotspot = xHotSpot;
      ii.yHotspot = yHotSpot;
      ii.hbmMask = hMonoBitmap;
      ii.hbmColor = hBitmap;

      // Create the alpha cursor with the alpha DIB section.
      HICON hicon = CreateIconIndirect(&ii);

      DeleteObject(hBitmap);
      DeleteObject(hMonoBitmap);

      return hicon;

   }


   HCURSOR create_alpha_cursor(const ::image * pimage, int xHotSpot, int yHotSpot)
   {

      if (::not_ok(pimage))
      {

         return nullptr;

      }

      return (HCURSOR) create_alpha_icon(pimage, false, xHotSpot, yHotSpot);

   }


   CLASS_DECL_WINDOWING_WIN32 HBITMAP create_hbitmap(pixmap * ppixmap)
   {

      pixmap pixmap;

      pixmap.m_iScan = ppixmap->width() * sizeof(color32_t);

      pixmap.m_size = ppixmap->size();

      HBITMAP hbitmap = create_hbitmap_2(&pixmap);

      if (hbitmap == nullptr)
      {

         return nullptr;

      }

      ::copy_colorref(ppixmap, &pixmap);

      return hbitmap;

   }


   CLASS_DECL_WINDOWING_WIN32 HBITMAP create_hbitmap_2(pixmap * ppixmap)
   {

      HBITMAP hbmp = nullptr;

      BITMAPINFO bminfo;

      ZeroMemory(&bminfo, sizeof(bminfo));
      bminfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
      bminfo.bmiHeader.biWidth = ppixmap->width();
      bminfo.bmiHeader.biHeight = -((::i32)ppixmap->height());
      bminfo.bmiHeader.biPlanes = 1;
      bminfo.bmiHeader.biBitCount = 32;
      bminfo.bmiHeader.biCompression = BI_RGB;

      color32_t * pvImageBits = nullptr;

      HDC hdcScreen = GetDC(nullptr);

      hbmp = CreateDIBSection(hdcScreen, &bminfo, DIB_RGB_COLORS, (void **)&ppixmap->m_pcolorrefRaw, nullptr, 0);

      ReleaseDC(nullptr, hdcScreen);

      if (hbmp == nullptr)
      {

         return nullptr;

      }

      ppixmap->m_iScan = ppixmap->width() * sizeof(color32_t);

      return hbmp;

   }


   CLASS_DECL_WINDOWING_WIN32 float os_get_dpi()
   {

      return 96.0f;

   }


   HICON load_icon(::particle * pparticle, string_array & straMatter, string strIcon, int cx, int cy)
   {

      HICON hicon = nullptr;

      ::file::path path;

      for (auto & strMatter : straMatter)
      {

         path = strMatter;

         path = Ctx(pobject).dir().matter(path / strIcon);

         path = Ctx(pobject).get_matter_cache_path(path);

         hicon = (HICON) ::LoadImageW(nullptr, wstring(path), IMAGE_ICON, cx, cy, LR_LOADFROMFILE);

         if (hicon != nullptr)
         {

            break;

         }

      }

      return hicon;

   }




   CLASS_DECL_WINDOWING_WIN32 HBITMAP create_windows_dib(const ::size_i32 & size, i32 * piScan, color32_t ** ppdata)
   {

      BITMAPINFO bitmapinfo;

      zero(bitmapinfo);

      auto iScan = size.cx * 4;

      bitmapinfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
      bitmapinfo.bmiHeader.biWidth = (::i32)size.cx;
      bitmapinfo.bmiHeader.biHeight = (::i32)-size.cy;
      bitmapinfo.bmiHeader.biPlanes = 1;
      bitmapinfo.bmiHeader.biBitCount = 32;
      bitmapinfo.bmiHeader.biCompression = BI_RGB;
      bitmapinfo.bmiHeader.biSizeImage = (::i32)(size.cy * iScan);

      color32_t * pcolorref = nullptr;

      HBITMAP hbitmap = ::CreateDIBSection(nullptr, &bitmapinfo, DIB_RGB_COLORS, (void **)&pcolorref, nullptr, 0);

      if (hbitmap == nullptr)
      {

         return nullptr;

      }

      if (piScan)
      {

         *piScan = iScan;

      }

      if (ppdata)
      {

         *ppdata = pcolorref;

      }

      return hbitmap;

   }


} // namespace windowing_win32

