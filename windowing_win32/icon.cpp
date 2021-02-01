// created by Camilo <3CamiloSasukeThomasBorregaardSoerensen  - Honoring Thomas Borregaard Sørensen MY ONLY LORD
// recreated by Camilo 2021-01-28 16:44
#include "framework.h"
#include "_windowing.h"


namespace windowing_win32
{


   icon::icon()
   {

      m_hicon = nullptr;

   }


   icon::~icon()
   {

      ::DestroyIcon(m_hicon);

   }


   iptr icon::get_os_data() const
   {

      return (iptr) m_hicon;

   }


   bool icon::load_file(string strPath)
   {

#ifdef WINDOWS_DESKTOP

      strPath = Context.defer_process_matter_path(strPath);

      int_array ia;

      ia.add(16);
      ia.add(24);
      ia.add(32);
      ia.add(48);
      ia.add(256);

      hicon hIcon = nullptr;

      for (auto i : ia)
      {

         hIcon = (hicon) ::LoadImageW(nullptr, wstring(strPath), IMAGE_ICON, i, i, LR_LOADFROMFILE);

         if (hIcon != nullptr)
         {

            m_iconmap[::size_i32(i, i)] = hIcon;

            m_picon = hIcon;

            on_update_icon();

         }

      }

      return m_picon != nullptr;

#else

      m_strAppTrayIcon = strPath;

      return true;

#endif

   }

   //::e_status     icon::attach_os_data(void * picon, bool bTakeOwnership)
   //{

   //   m_picon = picon;

   //   m_bAutoDelete = bTakeOwnership;

   //   on_update_icon();

   //   return ::success;

   //}


   image * icon::get_image(const concrete < ::size_i32 > & size)
   {

      bool bExists;

      __defer_construct_new(m_pimagemap);

      auto pimage = m_pimagemap->get(size, bExists);

      if (bExists)
      {

         return pimage;

      }

#ifdef WINDOWS_DESKTOP

      bool bOk = false;

      HBITMAP hbitmap = nullptr;

      HDC hdc = nullptr;

      HBITMAP hbitmapOld = nullptr;

      try
      {

         BITMAPINFO info;

         ZeroMemory(&info, sizeof(BITMAPINFO));

         auto iScan = size.cx * 4;

         info.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
         info.bmiHeader.biWidth = size.cx;
         info.bmiHeader.biHeight = -size.cy;
         info.bmiHeader.biPlanes = 1;
         info.bmiHeader.biBitCount = 32;
         info.bmiHeader.biCompression = BI_RGB;
         info.bmiHeader.biSizeImage = size.cy * iScan;

         color32_t * pcolorref = nullptr;

         hbitmap = ::CreateDIBSection(nullptr, &info, DIB_RGB_COLORS, (void **)&pcolorref, nullptr, 0);

         ::pixmap pixmap;

         pixmap.init(size, pcolorref, iScan);

         hdc = ::CreateCompatibleDC(nullptr);

         hbitmapOld = (HBITMAP) ::SelectObject(hdc, hbitmap);

         if (!::DrawIconEx(hdc, 0, 0, (hicon)m_picon, size.cx, size.cy, 0, nullptr, DI_IMAGE | DI_MASK))
         {

            output_debug_string("nok");

         }
         else
         {

            bool bAllZeroAlpha = true;
            bool bTheresUint32 = false;

            pixmap.map();

            int area = size.area();

            auto pc = pixmap.colorref();
            byte * pA = &((byte *)pc)[3];

            for (int i = 0; i < area; i++)
            {
               if (*pc != 0)
               {
                  bTheresUint32 = true;
               }
               if (*pA != 0)
               {
                  bAllZeroAlpha = false;
                  break;
               }
               pc++;
               pA += 4;
            }

            if (bAllZeroAlpha && bTheresUint32)
            {

               pc = pixmap.colorref();
               pA = &((byte *)pc)[3];

               for (int i = 0; i < area; i++)
               {
                  if (*pc != 0)
                  {
                     *pA = 255;
                  }
                  pc++;
                  pA += 4;
               }
            }

            ::SelectObject(hdc, hbitmapOld);

            pimage->map();

            ::copy_colorref(pimage, pixmap);

         }

      }
      catch (...)
      {

         output_debug_string("!");

      }

      if (hdc != nullptr)
      {

         if (hbitmapOld != nullptr)
         {

            ::SelectObject(hdc, hbitmapOld);

         }

         ::DeleteDC(hdc);

      }

      if (hbitmap != nullptr)
      {

         ::DeleteObject(hbitmap);

      }

#endif

      return pimage;


   }




} // namespace windowing_win32






#ifdef WINDOWS_DESKTOP

// http ://stackoverflow.com/questions/1913468/how-to-determine-the-size_i32-of-an-icon-from-a-hicon
// http://stackoverflow.com/users/739731/sergey

MYICON_INFO MyGetIconInfo(hicon hIcon)
{
   MYICON_INFO myinfo;
   __zero(myinfo);

   ICONINFO info;
   __zero(info);

   BOOL bRes = FALSE;

   bRes = GetIconInfo(hIcon, &info);
   if (!bRes)
      return myinfo;

   BITMAP bmp;
   ZeroMemory(&bmp, sizeof(bmp));

   if (info.hbmColor)
   {
      const int nWrittenBytes = GetObject(info.hbmColor, sizeof(bmp), &bmp);
      if (nWrittenBytes > 0)
      {
         myinfo.nWidth = bmp.bmWidth;
         myinfo.nHeight = bmp.bmHeight;
         myinfo.nBitsPerPixel = bmp.bmBitsPixel;
      }
   }
   else if (info.hbmMask)
   {
      // Icon has no color plane, image data stored in mask
      const int nWrittenBytes = GetObject(info.hbmMask, sizeof(bmp), &bmp);
      if (nWrittenBytes > 0)
      {
         myinfo.nWidth = bmp.bmWidth;
         myinfo.nHeight = bmp.bmHeight / 2;
         myinfo.nBitsPerPixel = 1;
      }
   }

   if (info.hbmColor)
      DeleteObject(info.hbmColor);
   if (info.hbmMask)
      DeleteObject(info.hbmMask);

   return myinfo;
}



#endif


