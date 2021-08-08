#include "framework.h"
#include "aura/operating_system.h"
#include "aura/user/_user.h"
#undef User
#undef Usr
#include "shell.h"
#include "apex/compress/zip/context.h"
#include "acme/filesystem/filesystem/acme_dir.h"
#include "acme_windows/known_folder_struct.h"

bool IsDibSection(HBITMAP bmp)
{
   bool Result = true; //assume that it is a DIBSECTION.

   DIBSECTION ds; //initialize everything to zeros
   //int res ;

   //Try to decode hbitmap as a DIBSECTION
   int res = GetObject(bmp, sizeof(ds), &ds);
   if (res == 0)
      return false;

   //If the bitmap actually was a BITMAP (and not a DIBSECTION), 
   //then BitmapInfoHeader values will remain zeros
   if ((ds.dsBmih.biSize == 0)
      && (ds.dsBmih.biWidth == 0)
      && (ds.dsBmih.biHeight == 0)
      && (ds.dsBmih.biPlanes == 0)
      && (ds.dsBmih.biBitCount == 0)
      && (ds.dsBmih.biCompression == 0)
      && (ds.dsBmih.biSizeImage == 0)
      && (ds.dsBmih.biXPelsPerMeter == 0)
      && (ds.dsBmih.biYPelsPerMeter == 0)
      && (ds.dsBmih.biClrUsed == 0)
      && (ds.dsBmih.biClrImportant == 0))
   {
      Result = false; //it's not a dibsection

   }
   return Result;
}
//__pointer(::image) create_image_from_hbitmap1(HBITMAP hbitmap)
//{
//   //comptr < IKnownFolder > get_known_folder(const ::string & strPath);
//
//
//   
//
//   BITMAP bitmap = {};
//
//   ::GetObject(hbitmap, sizeof(bitmap), &bitmap);
//
//   int w = bitmap.bmWidth;
//   int h = bitmap.bmHeight;
//
//   //   HDC hMemDC;
//   ::u32 dwWidth, dwHeight;
//   BITMAPV5HEADER bi;
//   // HBITMAP hOldBitmap;
//   HBITMAP hBitmap;
//   void * pBits;
//
//   hcursor hAlphaCursor = nullptr;
//
//   dwWidth = pimage->width();  // width of the Bitmap V5 Dib bitmap
//   dwHeight = pimage->height();  // height of the Bitmap V5 Dib bitmap
//
//   ZeroMemory(&bi, sizeof(BITMAPV5HEADER));
//   bi.bV5Size = sizeof(BITMAPV5HEADER);
//   bi.bV5Width = dwWidth;
//   bi.bV5Height = -(::i32)dwHeight;
//   bi.bV5Planes = 1;
//   bi.bV5BitCount = 32;
//   bi.bV5Compression = BI_BITFIELDS;
//   // The following mask specification specifies a supported 32 BPP
//   // alpha format for Windows XP.
//   bi.bV5RedMask = 0x00FF0000;
//   bi.bV5GreenMask = 0x0000FF00;
//   bi.bV5BlueMask = 0x000000FF;
//   bi.bV5AlphaMask = 0xFF000000;
//
//   int iStride = w * 4;
//
//   HDC hdc;
//   hdc = GetDC(nullptr);
//
//   // Create the DIB section with an alpha channel.
//   hBitmap = CreateDIBSection(hdc, (BITMAPINFO *)&bi, DIB_RGB_COLORS, (void **)&pBits, nullptr, (::u32)0);
//
//
//   HDC sourceHdc = ::CreateCompatibleDC(hdc);
//   auto hOld  =::SelectObject(sourceHdc, hbitmap);
//
//   // This pixel has partial transparency, but ::GetPixel returns just RGB.
//   COLORREF c = ::GetPixel(sourceHdc, 20, 20);
//
//   // Draw the bitmap to hdcDraw
//   BLENDFUNCTION bf1;
//   bf1.BlendOp = AC_SRC_OVER;
//   bf1.BlendFlags = 0;
//   bf1.SourceConstantAlpha = 0xff;
//   bf1.AlphaFormat = AC_SRC_ALPHA;
//   ::AlphaBlend(hdc, 0, 0, w, h, sourceHdc, 0, 0, w, h, bf1);
//
//   ::SelectObject(sourceHdc, hOld);
//   ::DeleteDC(sourceHdc);
//
//   //hMemDC = CreateCompatibleDC(hdc);
//   ReleaseDC(nullptr, hdc);
//
//   // Draw something on the DIB section.
//   //hOldBitmap = (HBITMAP)set(hMemDC,hBitmap);
//   //PatBlt(hMemDC,0,0,dwWidth,dwHeight,WHITENESS);
//   //SetTextColor(hMemDC,rgb(0,0,0));
//   //SetBkMode(hMemDC,TRANSPARENT);
//   //text_out(hMemDC,0,9,"rgba",4);
//   //set(hMemDC,hOldBitmap);
//   //DeleteDC(hMemDC);
//
//   // Set the alpha values for each pixel in the cursor so that
//   // the complete cursor is semi-transparent.
//
//   int iStrideDst = dwWidth * sizeof(::color32_t);
//
//   ::copy_colorref(pimage->get_data(), pimage->width(), pimage->height(), pimage->scan_size(), (const color32_t *) pBits, iStride);
//
//   return pimage;
//
//}

__pointer(::image) create_image_from_hbitmap(HBITMAP hbitmap)
{


   bool bDibSection = IsDibSection(hbitmap);

   if (bDibSection)
   {
      DIBSECTION ds; //initialize everything to zeros
      ::GetObject(hbitmap, sizeof(ds), &ds);

      if (ds.dsBmih.biBitCount == 32
         && ds.dsBmih.biPlanes == 1
         && ds.dsBmih.biCompression == 0)
      {

         int w = ds.dsBmih.biWidth;
         int h = ds.dsBmih.biHeight;

         auto pBits = ds.dsBm.bmBits;
         auto pimage = create_image({ w, h });
         int iStride = ds.dsBmih.biSizeImage / abs(h );

         ::vertical_swap_copy_colorref(pimage->get_data(), pimage->width(), pimage->height(), pimage->scan_size(), (const color32_t *)pBits, iStride);

         return pimage;

      }

   }

   BITMAP bitmap = {};

   ::GetObject(hbitmap, sizeof(bitmap), &bitmap);

   auto pimage = create_image({ bitmap.bmWidth, bitmap.bmHeight });

   BITMAPINFO bitmapinfo = {};

   bitmapinfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
   bitmapinfo.bmiHeader.biWidth = pimage->width();
   bitmapinfo.bmiHeader.biHeight = -pimage->height();
   bitmapinfo.bmiHeader.biPlanes = 1;
   bitmapinfo.bmiHeader.biBitCount = 32;
   bitmapinfo.bmiHeader.biCompression = BI_RGB;
   bitmapinfo.bmiHeader.biSizeImage = pimage->area() * sizeof(COLORREF);
   //bitmapinfo.bmiHeader.biXPelsPerMeter;
   //bitmapinfo.bmiHeader.biYPelsPerMeter;
   //bitmapinfo.bmiHeader.biClrUsed;
   //bitmapinfo.bmiHeader.biClrImportant;
   
   HDC hdc = ::CreateCompatibleDC(NULL);


   if (!::GetDIBits(hdc, hbitmap, 0, bitmap.bmHeight, pimage->m_pcolorrefRaw, &bitmapinfo, DIB_RGB_COLORS))
   {

      ::DeleteDC(hdc);

      return nullptr;

   }
   
   ::DeleteDC(hdc);

   ::DeleteDC(hdc);



   return pimage;

}

//CLASS_DECL_AURA HICON ExtractResourceIcon(const ::string & strPath, int & cx, int & cy, int iIcon);


namespace windowing_win32
{


   shell::shell()
   {

      //m_iMaxThreadCount = maximum(4, ::get_processor_count());

      m_iMaxThreadCount = 1;

      defer_create_mutex();

      m_iThread = 0;

      defer_co_initialize_ex(false);

      SHGetDesktopFolder(&m_pfolderDesktop);

      SHGetMalloc(&m_pmalloc);

      SHGetImageList(SHIL_SMALL, IID_IImageList, (void **)&m_pilSmall);

      SHGetImageList(SHIL_LARGE, IID_IImageList, (void **)&m_pilLarge);

      SHGetImageList(SHIL_EXTRALARGE, IID_IImageList, (void **)&m_pilExtraLarge);

      SHGetImageList(SHIL_JUMBO, IID_IImageList, (void **)&m_pilJumbo);



   }


   shell::~shell()
   {

   }




   //      i32 shell::thread::get_image_by_file_extension(oswindow image_key & imagekey, ::color::color colorBackground)
   //      {
   //
   //#ifdef WINDOWS_DESKTOP
   //
   //         return get_foo_image(imagekey, colorBackground);
   //
   //#else
   //
   //         return 0x80000000;
   //
   //#endif // WINDOWS_DESKTOP
   //
   //      }


      // returned image should be "Definitive" icon/pimage->
      // maybe fallback but not temporary
   i32 shell::get_file_image(image_key & imagekey, const itemidlist & itemidlistParam, const unichar * pcszExtra, const ::color::color & colorBackground)
   {

      comptr < IShellFolder> pshellfolder;

      ::itemidlist itemidlist(itemidlistParam);

      ::itemidlist itemidlistChild;

      ::itemidlist itemidlistFolder;

      ::string strChild;

      if (itemidlist.has_child())
      {

         itemidlistFolder = itemidlist.last_item_id_removed();

         itemidlistChild = itemidlist.last();

         m_pfolderDesktop->BindToObject(
            itemidlistFolder,
            nullptr,
            IID_IShellFolder, 
            (void **) &pshellfolder);

         if (pshellfolder && itemidlistChild.m_pidl)
         {

            STRRET strretChild;

            HRESULT hr = pshellfolder->GetDisplayNameOf(itemidlistChild, 0, &strretChild);

            if (SUCCEEDED(hr))
            {

               strChild = ::itemidlist::_display_name(strretChild, itemidlistChild);

               output_debug_string(strChild);

            }

         }

      }
      else
      {

         itemidlistChild = itemidlist;

      }

      int iImage = 0x80000000;

      i32 iType;

      switch (imagekey.m_eicon)
      {
      case icon_normal:
         iType = 0;
         break;
      case icon_open:
         iType = GIL_OPENICON;
         break;
      default:
         // unexpected icon type
         ASSERT(false);
         return 0x80000000;
      }

      string strFileParam(imagekey.m_strPath);

      string strResource;

      WCHAR wszPath[_MAX_PATH * 6];

      WCHAR szPath[_MAX_PATH * 6];

      HICON hicon16 = nullptr;

      HICON hicon48 = nullptr;

      HRESULT hrIconLocation = E_FAIL;

      HRESULT hrExtract = E_FAIL;

      HRESULT hrExtractIconUI = E_FAIL;

      HRESULT hrGetOverlayInfo = E_FAIL;

      HRESULT hrGetLocation = E_FAIL;

      string strExtra;

      string strPathEx;

      strPathEx = strFileParam;

      ::str::international::unicode_to_utf8(strExtra, pcszExtra);

      if (strExtra.get_length() > 0)
      {

         strPathEx += ":" + strExtra;

      }

      auto psession = get_session();

      auto puser = psession->user();

      auto psystem = m_psystem;

      auto pnode = psystem->node();

      auto pwindowing = puser->windowing()->cast < windowing >();

      HWND hwnd = __hwnd(pwindowing->system_window()->get_oswindow());

      comptr < IExtractIconW > piextracticon;

      comptr< IShellItemImageFactory> pfactory;

      string strPath(imagekey.m_strPath);

      wstring wstrPath(strPath);

      if (imagekey.m_strPath.ends_ci(".sln"))
      {

         output_debug_string(".sln");

      }

     
      comptr < IShellIcon > pshellicon;

      HRESULT hrShellIcon=pshellfolder.As(pshellicon);

      if (SUCCEEDED(hrShellIcon) && pshellicon)
      {

         int iIconIndex = -1;

         HRESULT hrGetIconOf = pshellicon->GetIconOf(itemidlistChild, 0, &iIconIndex);

         if (SUCCEEDED(hrGetIconOf))
         {

            imagekey.m_strPath = "::system";

            imagekey.m_iIcon = iIconIndex;

            if (contains_image(imagekey, iImage))
            {

               return iImage;

            }

            iImage = _reserve_image(imagekey);

            if(iImage >= 0)
            {

               add_system_icon(iIconIndex, imagekey.m_cr, iImage);

               return iImage;

            }

         }

      }



      //HRESULT hr = SHCreateItemFromIDList(itemidlist, IID_IShellItemImageFactory, (void **) &pfactory);

      //if(SUCCEEDED(hr))
      //{

      //   iImage = _reserve_image(imagekey);

      //   int iSuccessCount = 0;

      //   for (auto & iSize : m_iaSize)
      //   {

      //      HBITMAP hbitmap = nullptr;

      //      SIZE size = { iSize, iSize };

      //      if (SUCCEEDED(pfactory->GetImage(size, 0, &hbitmap)))
      //      {

      //         auto pimage = create_image_from_hbitmap(hbitmap);

      //         set_image(iImage, pimage, imagekey.m_cr);

      //         DeleteObject(hbitmap);

      //         iSuccessCount++;

      //      }

      //   }
      //      
      //   return iImage;

      //}

      comptr < IShellIconOverlayIdentifier > pioverlay;

      comptr < IExtractImage > piextractimage;

      HRESULT hrIconOverlay = E_FAIL;

      HRESULT hrExtractImage = E_FAIL;

      if (pshellfolder)
      {

         //hrIconOverlay = pshellfolder->GetUIObjectOf(
         //   hwnd,
         //   1,
         //   itemidlistChild,
         //   IID_IShellIconOverlayIdentifier,
         //   nullptr,
         //   (void **)&pioverlay);


         //if (pioverlay)
         //{

         //   int iIndex = 0;

         //   DWORD dwFlags = 0;

         //   if (SUCCEEDED(hrGetOverlayInfo = pioverlay->GetOverlayInfo(
         //      wszPath,
         //      sizeof(wszPath),
         //      &iIndex,
         //      &dwFlags)))
         //   {

         //      if (wcscmp(wszPath, L"*") == 0)
         //      {

         //         imagekey.m_iIcon = 0x80000000;

         //         imagekey.set_extension(strFileParam);

         //         imagekey.m_strPath = "";

         //      }
         //      else
         //      {

         //         auto psystem = m_psystem;

         //         auto pnode = psystem->node();

         //         imagekey.set_path(pnode->expand_env(szPath));

         //         imagekey.m_iIcon = iIndex;

         //         imagekey.m_strExtension = "";

         //      }

         //   }

         //}
         //else
         //{

          hrExtractImage = pshellfolder->GetUIObjectOf(
               hwnd,
               1,
               itemidlistChild,
               IID_IExtractImage,
               nullptr,
               (void **)&piextractimage);


            if (piextractimage)
            {

               SIZE s;

               s.cx = 48;

               s.cy = 48;

               DWORD dwDepth = 32;

               DWORD dwFlags = 0;

               if (SUCCEEDED(hrGetLocation = piextractimage->GetLocation(

                  wszPath,
                  sizeof(wszPath),
                  nullptr,
                  &s,
                  dwDepth,
                  &dwFlags)))
               {


                  if (wcscmp(wszPath, L"*") == 0)
                  {

                     imagekey.m_iIcon = 0x80000000;

                     imagekey.set_path(strFileParam);

                     imagekey.m_strPath = "";

                  }
                  else
                  {

                     auto psystem = m_psystem;

                     auto pnode = psystem->node();

                     imagekey.set_path(pnode->expand_env(wszPath));

                     imagekey.m_iIcon = 0;

                     imagekey.m_strExtension = "";

                  }

               }

            }
            else
            {

               imagekey.set_path(strFileParam);

               imagekey.m_iIcon = 0;

            }

         //}

      }



      if (FAILED(hrExtractImage) && pshellfolder)
      {

         hrExtractIconUI = pshellfolder->GetUIObjectOf(
            hwnd,
            1,
            itemidlistChild,
            IID_IExtractIconW,
            nullptr,
            (void **)&piextracticon);

      }

      ::u32 uExtractIconLocationFlags = 0;

      string strIconLocation;

      if(piextracticon)
      {

         int iIcon = 0;

         if (SUCCEEDED(hrIconLocation = piextracticon->GetIconLocation(
            iType,
            wszPath,
            sizeof(wszPath) / sizeof(wszPath[0]),
            &iIcon,
            &uExtractIconLocationFlags)))
         {

            if (wcscmp(wszPath, L"*") == 0)
            {

               imagekey.m_iIcon = 0x80000000;

               imagekey.set_extension(strFileParam);

               imagekey.m_strPath = "";

            }
            else
            {

               strIconLocation = pnode->expand_env(wszPath);

               imagekey.set_path(strIconLocation);

               imagekey.m_iIcon = iIcon;

               imagekey.m_strExtension = "";

            }

         }

      }

      ::file::path pathTarget;

      if (((FAILED(hrIconLocation) && FAILED(hrGetLocation))
         || imagekey.m_iIcon == 0x80000000
         || !m_pcontext->m_papexcontext->file().exists(strIconLocation))
         && ::str::ends_ci(strFileParam, ".lnk"))
      {

         m_pcontext->m_papexcontext->file().resolve_link(pathTarget, strFileParam);

         if (!m_pcontext->m_papexcontext->file().exists(pathTarget) && !m_pcontext->m_papexcontext->dir().is(pathTarget))
         {

            if (pathTarget.ends_ci(".exe"))
            {

               imagekey.set_path(pathTarget);

            }
            else
            {

               imagekey.set_path("");

            }

            iImage = get_image_by_file_extension(imagekey);

            return iImage;

         }

         if (FAILED(hrIconLocation) && FAILED(hrGetLocation))
         {

            imagekey.set_path(pathTarget);

            iImage = get_file_image(imagekey, pcszExtra, colorBackground);

            return iImage;

         }

      }
      else
      {

         pathTarget = strFileParam;

      }

      if (imagekey.m_iIcon == 0x80000000)
      {

         if (imagekey.m_strShellThemePrefix.has_char())
         {

            string strExtension = file_extension_dup(pathTarget);

            image_key imagekeyTheme;

            string strFooPath = imagekey.m_strShellThemePrefix + "foo." + strExtension;

            imagekeyTheme.set_path(strFooPath);

            imagekeyTheme.m_iIcon = 0;

            if (contains_image(imagekeyTheme, iImage))
            {

               return iImage;

            }

            string strIcon;

            strIcon = m_psystem->m_pacmedir->config() / "shell/app_theme" / imagekey.m_strShellThemePrefix + strExtension + ".ico";

            if (m_pcontext->m_papexcontext->file().exists(strIcon))
            {

               if (reserve_image(imagekeyTheme, iImage))
               {

                  set_icon(iImage,  strIcon, colorBackground);

               }

               return iImage;

            }

         }

         if (wcscmp(wszPath, L"*") == 0)
         {

            return get_image_by_file_extension(imagekey);

         }

      }

      if (uExtractIconLocationFlags & GIL_NOTFILENAME)
      {

         if (reserve_image(imagekey, iImage))
         {

            HICON hicon = nullptr;

            HRESULT hrExtract = E_FAIL;

            synchronous_lock synchronouslock(mutex());

            auto iaSize = m_iaSize;

            synchronouslock.unlock();

            for (auto iSize : iaSize)
            {

               if (iSize <= 16)
               {

                  if (SUCCEEDED(hrExtract = piextracticon->Extract(

                     wszPath,
                     imagekey.m_iIcon,
                     nullptr,
                     &hicon,
                     iSize << 16)))
                  {

                     add_icon(iSize, hicon, colorBackground, iImage);

                     ::DestroyIcon(hicon);

                  }

               }
               else
               {

                  if (SUCCEEDED(hrExtract = piextracticon->Extract(

                     wszPath,
                     imagekey.m_iIcon,
                     &hicon,
                     nullptr,
                     iSize)))
                  {

                     add_icon(iSize, hicon, colorBackground, iImage);

                     ::DestroyIcon(hicon);

                  }

               }

            }

         }

         return iImage;

      }
      else if (strIconLocation.has_char())
      {

         if (strIconLocation.ends_ci(".ico"))
         {

            set_image_ico(strIconLocation, iImage, colorBackground);

         }
         else
         {

            set_image_resource(strIconLocation, iImage, imagekey, colorBackground);


         }

         return iImage;

      }


      //if (imagekey.m_iIcon >= 0 && strFileParam.get_length() > 0)
      //{

      //   SHFILEINFOW shfi16;

      //   SHFILEINFOW shfi48;

      //   wstring wstrPath(strFileParam);

      //   SHGetFileInfoW(
      //   wstrPath,
      //   FILE_ATTRIBUTE_NORMAL,
      //   &shfi16,
      //   sizeof(shfi16),
      //   SHGFI_ICON
      //   | SHGFI_SMALLICON);

      //   SHGetFileInfoW(
      //   wstrPath,
      //   FILE_ATTRIBUTE_NORMAL,
      //   &shfi48,
      //   sizeof(shfi48),
      //   SHGFI_ICON
      //   | SHGFI_LARGEICON);

      //   bool b16 = false;

      //   bool b48 = false;

      //   if (shfi16.hIcon != nullptr || shfi48.hIcon != nullptr)
      //   {

      //      if (reserve_image(imagekey, iImage))
      //      {

      //         add_icon_set(&shfi16, &shfi48, colorBackground, b16, b48, iImage);

      //         if (!b16 && shfi16.hIcon != nullptr)
      //         {

      //            ::DestroyIcon(shfi16.hIcon);

      //         }

      //         if (!b48 && shfi48.hIcon != nullptr)
      //         {

      //            ::DestroyIcon(shfi48.hIcon);

      //         }


      //      }

      //   }

      //}

      imagekey.set_extension(pathTarget);

      imagekey.m_strPath.Empty();

      imagekey.m_iIcon = 0;

      return get_image_by_file_extension(imagekey);

   }


   i32 shell::get_image_by_file_extension(image_key & imagekey)
   {

      i32 iImage;

      if (reserve_image(imagekey, iImage))
      {

         SHFILEINFOW shfi = {};

         wstring wstrFilePath;

         if (imagekey.m_eattribute.has(file_attribute_directory))
         {

            SHGetFileInfoW(
               L"foo",
               FILE_ATTRIBUTE_DIRECTORY,
               &shfi,
               sizeof(shfi),
               SHGFI_USEFILEATTRIBUTES
               | SHGFI_SYSICONINDEX);


         }
         else
         {

            wstrFilePath = wstring(L"foo.") + wstring(imagekey.m_strExtension);

            SHGetFileInfoW(
               wstrFilePath,
               FILE_ATTRIBUTE_NORMAL,
               &shfi,
               sizeof(shfi),
               SHGFI_USEFILEATTRIBUTES |
               SHGFI_SYSICONINDEX);

         }

         add_system_icon(shfi.iIcon, imagekey.m_cr, iImage);

      }

      return iImage;

   }


   //index shell::GetCSIDL(LPITEMIDLIST piidl)

   //{
   //   LPITEMIDLIST ppidl;

   //   i32 csidla[] =
   //   {
   //      CSIDL_DESKTOP,
   //      CSIDL_DRIVES,
   //      CSIDL_PERSONAL,
   //      CSIDL_NETHOOD,
   //      CSIDL_NETWORK,
   //      CSIDL_BITBUCKET,
   //      -1,
   //   };

   //   i32 * pcsidl = csidla;

   //   while (*pcsidl != -1)
   //   {
   //      if (SUCCEEDED(SHGetSpecialFolderLocation(
   //                    nullptr,
   //                    *pcsidl,
   //                    &ppidl)))
   //      {
   //         if (_017ItemIDListIsEqual(ppidl, piidl))

   //         {
   //            m_pmalloc->Free(ppidl);
   //            break;
   //         }
   //         m_pmalloc->Free(ppidl);
   //      }
   //      pcsidl++;
   //   }

   //   return *pcsidl;


   //}


   //index shell::GetCSIDLSort(index iCsidl)
   //{
   //   switch (iCsidl)
   //   {
   //   case CSIDL_DESKTOP:
   //      return 100;
   //   case CSIDL_PERSONAL:
   //      return 200;
   //   case CSIDL_DRIVES:
   //      return 300;
   //   case CSIDL_NETHOOD:
   //      return 1000;
   //   default:
   //      return 2000 + iCsidl;
   //   }

   //}



   shell::e_folder shell::get_folder_type(::object * pobject, const ::string & pcsz)
   {

      return get_folder_type(pobject, ::str::international::utf8_to_unicode(pcsz));

   }


   shell::e_folder shell::get_folder_type(::object * pobject, const ::wstring & wstrPath)
   {

      string strPath;

      ::str::international::unicode_to_utf8(strPath, wstrPath);

      if (dir::is(strPath))
      {

         return folder_file_system;

      }
      else
      {

         zip_context zipcontext(this);

         if (zipcontext.is_unzippable(strPath))
         {

            return folder_zip;

         }
         else
         {

            return folder_none;

         }

      }

   }


   i32 shell::_get_file_image(const image_key & key)
   {

      return get_file_image(key, nullptr, key.m_cr);

   }


   i32 shell::get_file_image(image_key imagekey, const unichar * pcszExtra, ::color::color colorBackground)
   {

      i32 iImage = 0x80000000;

      if (::str::begins_ci(imagekey.m_strPath, "uifs:"))
      {

         if (reserve_image(imagekey, iImage))
         {

            ::file::path path = m_pcontext->m_papexcontext->dir().matter("cloud.ico");

            set_icon(iImage, path, colorBackground);

         }

         return iImage;

      }
      else if (::str::begins_ci(imagekey.m_strPath, "fs:"))
      {

         if (reserve_image(imagekey, iImage))
         {

            ::file::path path = m_pcontext->m_papexcontext->dir().matter("remote.ico");

            set_icon(iImage, path, colorBackground);

         }

         return iImage;

      }
      else if (::str::begins_ci(imagekey.m_strPath, "ftp:"))
      {

         if (reserve_image(imagekey, iImage))
         {

            ::file::path path = m_pcontext->m_papexcontext->dir().matter("ftp.ico");

            set_icon(iImage, path, colorBackground);

         }

         return iImage;

      }

      if (::str::ends_ci(imagekey.m_strPath, ".aura"))
      {

         string str = m_pcontext->m_papexcontext->file().as_string(imagekey.m_strPath);

         if (::str::begins_eat_ci(str, "ca2prompt\r\n"))
         {

            str.trim();


         }

         return iImage;

      }

      if (m_knownfoldermanager)
      {

         auto pknownfolderstruct = get_known_folder_struct(imagekey.m_strPath);

         if (pknownfolderstruct)
         {

            comptr < IKnownFolder > pknownfolder;

            HRESULT hrGetFolder = m_knownfoldermanager->GetFolder(pknownfolderstruct->m_idKnownFolder, &pknownfolder);

            if (SUCCEEDED(hrGetFolder) && pknownfolder)
            {

               KNOWNFOLDER_DEFINITION definition = {};

               HRESULT hrFolderDefinition = pknownfolder->GetFolderDefinition(&definition);

               if (SUCCEEDED(hrFolderDefinition))
               {

                  iImage = _reserve_image(imagekey);

                  if(iImage >= 0)
                  {

                     string strResource = definition.pszIcon;

                     string_array stra;

                     stra.explode(",", strResource);

                     if (stra.get_size() == 2)
                     {

                        imagekey.m_strPath = stra[0];

                        imagekey.m_iIcon = atoi(stra[1]);

                        set_image_resource(stra[0], iImage, imagekey, colorBackground);

                        return iImage;

                     }

                  }

               }

            }

         }

      }

      SHFILEINFOW shfi = {};

      if (imagekey.m_strPath.get_length() == 2
         && ansi_char_is_alphabetic(imagekey.m_strPath[0])
         && imagekey.m_strPath[1] == ':')
      {

         ::wstring wstrPath(imagekey.m_strPath);

         if (SHGetFileInfoW(wstrPath, 0, &shfi, sizeof(shfi), SHGFI_ICONLOCATION))
         {

            string strPath = shfi.szDisplayName;

            if (strPath.has_char())
            {

               imagekey.m_iIcon = shfi.iIcon;

               set_image_resource(strPath, iImage, imagekey, colorBackground);

               return iImage;

            }

         }

      }



      //// Check for URL addresses like uifs://, http://, or ftp://
      //// Except A: B: C: (Windows drive letters)
      //// And then should find icon by extension if
      //// it is a file or as folder otherwise.

      //strsize iFind = imagekey.m_strPath.find_ci("://");

      //strsize iFind2 = imagekey.m_strPath.find_ci(":");

      //if (iFind >= 0 || iFind2 >= 2)
      //{

      //   string strProtocol = imagekey.m_strPath.Left(maximum(iFind, iFind2));

      //   i32 i = 0;

      //   while (i < strProtocol.get_length() && ansi_char_is_alphanumeric(strProtocol[i]))
      //   {

      //      i++;

      //   }

      //   if (i > 0 && i == strProtocol.get_length())
      //   {

      //      // heuristically valid protocol
      //      return get_image_by_file_extension(imagekey);

      //   }

      //   if (imagekey.m_eattribute.has(file_attribute_directory))
      //   {

      //      return get_image_by_file_extension(imagekey);

      //   }

      //}

      string strExtension;

      if (::str::ends_ci(imagekey.m_strPath, ".sln"))
      {

         //output_debug_string("test .sln");

      }

      string str(imagekey.m_strPath);

      if (str == "foo")
      {

         return get_image_by_file_extension(imagekey);

      }

      if (::str::begins_eat(str, "foo."))
      {

         return get_image_by_file_extension(imagekey);

      }

      ::file::path path = imagekey.m_strPath;

      ::file::path pathFolder = path.folder();

      itemidlist idlist;

      bool bParseError = false;

      try
      {

         idlist.parse(imagekey.m_strPath);

      }
      catch (...)
      {

         bParseError = true;

      }

      if (bParseError)
      {

         return get_image_by_file_extension(imagekey);

      }

    /*  itemidlist idlistAbsolute = idlist;

      itemidlist idlistChild;

      idlistChild = idlistAbsolute.last();

      if (idlistChild.m_pidl)
      {

         idlistAbsolute = idlist - 1;

      }
      else
      {

         idlistAbsolute = nullptr;

         idlistChild = idlist;

      }*/



      iImage = get_file_image(imagekey, idlist, pcszExtra, colorBackground);

      return iImage;

   }


   //i32 _017ItemIDListGetLen(LPITEMIDLIST piidl)

   //{
   //   if (piidl == nullptr)

   //      return 0;
   //   LPSHITEMID  pshiid = (LPSHITEMID)lpiidl;

   //   LPSHITEMID  pshiidLast = nullptr;

   //   USHORT cb;
   //   i32 iLen = 0;
   //   while (true)
   //   {
   //      cb = pshiid->cb;

   //      iLen += cb;
   //      if (cb == 0)
   //         break;
   //      pshiidLast = lpshiid;

   //      pshiid = (LPSHITEMID)(((byte *)lpshiid) + cb);


   //   }

   //   return iLen;

   //}


   ::e_status shell::initialize(::object * pobject)
   {

      if (m_bInitialized)
      {

         return ::success;

      }

      auto estatus = ::user::shell::initialize(pobject);

      if (!estatus)
      {

         return estatus;

      }

      //estatus = __compose_new(m_pmessagequeue);


      //if (!estatus)
      //{

      //   return estatus;

      //}

      //m_pmessagequeue->create_message_queue("user::shell", this);

      return estatus;

   }


   ::e_status shell::run()
   {

      m_knownfoldermanager.CoCreateInstance(CLSID_KnownFolderManager);

      auto estatus = ::user::shell::run();

      if (!estatus)
      {

         return estatus;

      }

      return estatus;

   }


   int shell::add_system_icon(int iIcon, const ::color::color & colorBackground, int iImage)
   {

      synchronous_lock synchronouslock(mutex());

      auto iaSize = m_iaSize;

      synchronouslock.unlock();

      for (auto iSize : iaSize)
      {

         iImage = add_system_icon(iSize, iIcon, colorBackground, iImage);

      }

      return iImage;

   }


   int shell::set_icon(int iImage, const ::file::path & pathIconParam, const ::color::color & colorBackground)
   {

      if (pathIconParam.ends_ci(".ico"))
      {

         synchronous_lock synchronouslock(mutex());

         auto iaSize = m_iaSize;

         synchronouslock.unlock();

         ::file::path path = m_pcontext->m_papexcontext->defer_process_path(pathIconParam);

         for (auto iSize : m_iaSize)
         {

            HICON hicon = (HICON)LoadImageW(nullptr, wstring(path), IMAGE_ICON, iSize, iSize, LR_LOADFROMFILE);

            if (hicon == nullptr)
            {

               ::u32 dwLastError = ::GetLastError();

               output_debug_string("LastError = " + __str(dwLastError));

            }

            iImage = add_icon(iSize, hicon, colorBackground, iImage);

            ::DestroyIcon(hicon);

         }

      }
      else
      {

         ::user::shell::set_icon(iImage, pathIconParam, colorBackground);

      }

      return iImage;

   }


   int shell::add_icon(int iSize, HICON hicon, const ::color::color & colorBackground, int iImage)
   {

      synchronous_lock synchronouslock(m_pil[iSize]->mutex());

      synchronous_lock slHover(m_pilHover[iSize]->mutex());

      auto picon = __create_new < ::windowing_win32::icon >();

      picon->add_icon(hicon);

      iImage = m_pil[iSize]->add(picon, iImage);

      if (iImage == 14)
      {

         //iImage = m_pil[iSize]->add(picon);

      }

      iImage = add_hover_image(iSize, iImage, colorBackground);

      return iImage;

   }


   int shell::add_system_icon(int iSize, int iIcon, const ::color::color & colorBackground, int iImage)
   {

      bool bUsed = false;

      if (iSize <= 16)
      {

         iImage = add_system_icon(iSize, m_pilSmall, iIcon, colorBackground, iImage);

      }
      else if (iSize <= 32)
      {

         iImage = add_system_icon(iSize, m_pilLarge, iIcon, colorBackground, iImage);

      }
      else if (iSize <= 48)
      {

         iImage = add_system_icon(iSize, m_pilExtraLarge, iIcon, colorBackground, iImage);

      }
      else
      {

         iImage = add_system_icon(iSize, m_pilJumbo, iIcon, colorBackground, iImage);

      }

      return iImage;

   }


   int shell::add_system_icon(int iSize, IImageList * pil, int iIcon, const ::color::color & colorBackground, int iImage)
   {

      if (pil != nullptr)
      {

         HICON hicon = nullptr;

         HRESULT hr = pil->GetIcon(iIcon, ILD_TRANSPARENT, &hicon);

         if (hicon != nullptr)
         {

            iImage = add_icon(iSize, hicon, colorBackground, iImage);

            ::DestroyIcon(hicon);

         }

      }

      return iImage;

   }






   void shell::set_image_ico(string strIconLocation, i32 & iImage, ::color::color colorBackground)
   {

      ASSERT(strIconLocation.ends_ci(".ico"));

      image_key imagekeyIco;

      imagekeyIco.set_path(strIconLocation, false);

      imagekeyIco.m_iIcon = 0;

      if (reserve_image(imagekeyIco, iImage))
      {

         set_icon(iImage, strIconLocation, colorBackground);

      }

   }


   void shell::set_image_resource(string strIconLocation, i32 & iImage, const image_key & imagekey, ::color::color colorBackground)
   {

      ASSERT(!strIconLocation.ends_ci(".ico"));

      image_key imagekeyIco;

      imagekeyIco.set_path(strIconLocation, false);

      imagekeyIco.m_iIcon = imagekey.m_iIcon;

      if (reserve_image(imagekeyIco, iImage))
      {

         auto psystem = m_psystem->m_paurasystem;

         auto pnode = psystem->node()->m_pAuraPlatform;

         synchronous_lock synchronouslock(mutex());

         auto iaSize = m_iaSize;

         synchronouslock.unlock();

         for (auto iSize : iaSize)
         {

            int iSizeOut = iSize;

            HICON hicon = pnode->extract_resource_icon(strIconLocation, iSizeOut, iSizeOut, imagekey.m_iIcon);

            if (hicon == nullptr && imagekey.m_iIcon == 0)
            {

               hicon = pnode->extract_resource_icon(strIconLocation, iSizeOut, iSizeOut, 0x80000000);

            }

            add_icon(iSize, hicon, colorBackground, iImage);

            ::DestroyIcon(hicon);

         }

      }

   }


   ::e_status shell::destroy()
   {

      return ::user::shell::destroy();

   }


} // namespace windows


namespace core
{


   


} // namespace core



