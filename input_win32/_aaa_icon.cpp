// created by Camilo <3CamiloSasukeThomasBorregaardSoerensen  - Honoring Thomas Borregaard Soerensen MY ONLY LORD
// recreated by Camilo 2021-01-28 16:44
#include "framework.h"
#undef USUAL_OPERATING_SYSTEM_SUPPRESSIONS
#include "icon.h"
#include "acme/exception/exception.h"
#include "acme/filesystem/file/memory_file.h"
#include "acme/platform/system.h"
#include "acme/filesystem/filesystem/file_context.h"
#include "aura/graphics/image/context.h"
#include "aura/graphics/image/drawing.h"
#include "aura/platform/context.h"
#include "aura/platform/node.h"


// http ://stackoverflow.com/questions/1913468/how-to-determine-the-int_size-of-an-icon-from-a-hicon
// http://stackoverflow.com/users/739731/sergey


struct MYICON_INFO
{

   int     nWidth;
   int     nHeight;
   int     nBitsPerPixel;

};


MYICON_INFO MyGetIconInfo(HICON hIcon);

// https://stackoverflow.com/questions/16330403/get-hbitmaps-for-all-sizes-and-depths-of-a-file-type-icon-c
// https://stackoverflow.com/users/1136711/simion32
// Code written by Simion32.
// Please feel free to use it anywhere. 
// Credit would be nice but isn't required.

//#include "include.h" //std::vectors and whatever else you need
//#include <allegro.h>
//#include <winalleg.h> //Allegro and Win32
//#include "Shellapi.h"

// In the following block, the (required!!) pragmas
// force correct data alignment. Needed in at least GCC.
#pragma pack( push, 1 ) 
typedef struct
{
   BYTE                bWidth;         // Width, in pixels, of the image
   BYTE                bHeight;        // Height, in pixels, of the image
   BYTE                bColorCount;    // Number of colors in image (0 if >=8bpp)
   BYTE                bReserved;      // Reserved ( must be 0)
   WORD                wPlanes;        // Color Planes
   WORD                wBitCount;      // Bits per pixel
   DWORD               dwBytesInRes;   // How many bytes in this resource?
   DWORD               dwImageOffset;  // Where in the file is this image?
} ICONDIRENTRY, * LPICONDIRENTRY;
typedef struct
{
   WORD                idReserved;     // Reserved (must be 0)
   WORD                idType;         // Resource Type (1 for icons)
   WORD                idCount;        // How many images?
   ICONDIRENTRY        idEntries[1];   // An entry for each image (idCount of 'em)
} ICONDIR, * LPICONDIR;
typedef struct
{
   BITMAPINFOHEADER     icHeader;       // DIB header
   RGBQUAD              icColors[1];    // Color table
   BYTE                 icXOR[1];       // DIB bits for XOR mask
   BYTE                 icAND[1];       // DIB bits for AND mask
} ICONIMAGE, * LPICONIMAGE;
#pragma pack( pop)
#pragma pack( push, 2 )
typedef struct
{
   BYTE                 bWidth;         // Width, in pixels, of the image
   BYTE                 bHeight;        // Height, in pixels, of the image
   BYTE                 bColorCount;    // Number of colors in image (0 if >=8bpp)
   BYTE                 bReserved;      // Reserved
   WORD                 wPlanes;        // Color Planes
   WORD                 wBitCount;      // Bits per pixel
   DWORD                dwBytesInRes;   // total size of the RT_ICON resource referenced by the nID member.
   WORD                 nID;            // resourceID of RT_ICON (LockResource to obtain a pointer to its ICONIMAGE)
} GRPICONDIRENTRY, * LPGRPICONDIRENTRY;
typedef struct
{
   WORD                 idReserved;     // Reserved (must be 0)
   WORD                 idType;         // Resource type (1 for icons)
   WORD                 idCount;        // How many images?
   GRPICONDIRENTRY      idEntries[1];   // The entries for each image
} GRPICONDIR, * LPGRPICONDIR;
#pragma pack( pop )




uint32_t Convert16BitToARGB(uint16_t value)
{
   return (0xFF000000 | ((value >> 7) & 0x0000F8) | ((value << 6) & 0x00F800) | ((value << 19) & 0xF80000));
}
uint32_t GetMaskBit(uint8_t * data, int x, int y, int w, int h)
{
   uint32_t mask_data_rowsize = (((w + 31) >> 5) * 4);
   return ((~(data[(mask_data_rowsize * ((h - 1) - y)) + (x >> 3)] >> (0x07 - (x & 0x07))) & 1) * 0xFFFFFFFF);
}
uint32_t GetColorMonochrome(uint8_t * xordata, uint8_t * anddata, int x, int y, int w, int h, uint32_t * pal)
{
   uint32_t mask_data_rowsize = (((w + 31) >> 5) * 4);
   uint32_t xor_bit = (((xordata[(mask_data_rowsize * ((h - 1) - y)) + (x >> 3)] >> (0x07 - (x & 0x07))) << 1) & 2);
   uint32_t and_bit = (((anddata[(mask_data_rowsize * ((h - 1) - y)) + (x >> 3)] >> (0x07 - (x & 0x07)))) & 1);
   uint32_t value = (xor_bit | and_bit);
   return pal[value];
}



//BITMAP * CreateBmp32bppFromIconResData(void * data, int size, int depth, int w, int h, int colors)
//{
//   char * pngheader = "\211PNG\r\n\032\n";
//   char * cpd = (char *)data;
//   bool is_png = ((cpd[0] == pngheader[0])
//      && (cpd[1] == pngheader[1])
//      && (cpd[2] == pngheader[2])
//      && (cpd[3] == pngheader[3])
//      && (cpd[4] == pngheader[4])
//      && (cpd[5] == pngheader[5])
//      && (cpd[6] == pngheader[6])
//      && (cpd[7] == pngheader[7]));
//   if (is_png)
//   {
//      //###########################################################
//      //#  PSEUDO-CODE: Somehow convert the PNG file into a bitmap.
//      BITMAP * result = ConvertPngFileToBmp32bpp(data, size);
//      return result;
//   }
//   else
//   {
//      uint32_t ignore_size = ((BITMAPINFOHEADER *)(data))->biSize;
//      BITMAP * bmp = create_bitmap_ex(32, w, h);
//      uint32_t pixel_count = (w * h);
//      uint32_t color_data_size = ((((((w * depth) + 7) >> 3) + 3) & ~3) * h);
//      switch (depth)
//      {
//      default: return bmp; break;
//      case 32:
//      {
//         uint32_t * src = (uint32_t *)(((uint8_t *)data) + ignore_size);
//         for (int yy = h - 1; yy >= 0; --yy) {
//            for (int xx = 0; xx < w; ++xx) {
//               _putpixel32(bmp, xx, yy, src[0]);
//               src++;
//            }
//            //There should never be any padding to jump over here.
//         }
//         return bmp;
//      }
//      break;
//      case 24:
//      {
//         uint32_t * src = (uint32_t *)(((uint8_t *)data) + ignore_size);
//         uint8_t * bitmask = (uint8_t *)(((uint8_t *)data) + ignore_size + color_data_size);
//         int padding_checker = 0;
//         for (int yy = h - 1; yy >= 0; --yy) {
//            for (int xx = 0; xx < w; ++xx) {
//               _putpixel32(bmp, xx, yy, ((src[0] & 0x00FFFFFF) | 0xFF000000) & GetMaskBit(bitmask, xx, yy, w, h));
//               src++;
//               src = (uint32_t *)(((uint8_t *)src) - 1); //go back a unsigned char due to packing
//               padding_checker += 3;
//               padding_checker &= 3;
//            }
//            //This loop jumps over any padding bytes.
//            while (padding_checker)
//            {
//               src = (uint32_t *)(((uint8_t *)src) + 1);
//               padding_checker++;
//               padding_checker &= 3;
//            }
//         }
//         return bmp;
//      }
//      break;
//      case 16:
//      {
//         //Note: there might be a color table present! ignore it.
//         uint16_t * src = (uint16_t *)(((uint8_t *)data) + ignore_size + (colors << 2));
//         uint8_t * bitmask = (uint8_t *)(((uint8_t *)data) + ignore_size + (colors << 2) + color_data_size);
//         int padding_checker = 0;
//         for (int yy = h - 1; yy >= 0; --yy) {
//            for (int xx = 0; xx < w; ++xx) {
//               _putpixel32(bmp, xx, yy, Convert16BitToARGB(src[0]) & GetMaskBit(bitmask, xx, yy, w, h));
//               src++;
//               padding_checker += 2;
//               padding_checker &= 3;
//            }
//            //This loop jumps over any padding bytes.
//            while (padding_checker)
//            {
//               src = (uint16_t *)(((uint8_t *)src) + 1);
//               padding_checker++;
//               padding_checker &= 3;
//            }
//         }
//         return bmp;
//      }
//      break;
//      case 8:
//      {
//         if (colors > 256) colors = 256; //Color Count must be restricted to 256 entries at the most.
//         if (colors <= 0) colors = 256; //Color Count might be reported as zero. This means 256.
//         uint8_t * src = (((uint8_t *)data) + ignore_size + (colors << 2));
//         uint32_t * pal = ((uint32_t *)(((uint8_t *)data) + ignore_size));
//         uint8_t * bitmask = (uint8_t *)(((uint8_t *)data) + ignore_size + (colors << 2) + color_data_size);
//         int padding_checker = 0;
//         for (int yy = h - 1; yy >= 0; --yy) {
//            for (int xx = 0; xx < w; ++xx) {
//               uint8_t color = src[0];
//               if (color < colors) {
//                  _putpixel32(bmp, xx, yy, (pal[color] | 0xFF000000) & GetMaskBit(bitmask, xx, yy, w, h));
//               }
//               else {
//                  _putpixel32(bmp, xx, yy, 0x00FF00FF);
//               }
//               src++;
//               padding_checker++;
//               padding_checker &= 3;
//            }
//            //This loop jumps over any padding bytes.
//            while (padding_checker)
//            {
//               src++;
//               padding_checker++;
//               padding_checker &= 3;
//            }
//         }
//         return bmp;
//      }
//      break;
//      case 4:
//      {
//         if (colors > 16) colors = 16; //Color Count must be restricted to 16 entries at the most.
//         if (colors <= 0) colors = 16; //Color Count might be reported as zero. This means 16.
//         uint8_t * src = (((uint8_t *)data) + ignore_size + (colors << 2));
//         uint32_t * pal = ((uint32_t *)(((uint8_t *)data) + ignore_size));
//         uint8_t * bitmask = (uint8_t *)(((uint8_t *)data) + ignore_size + (colors << 2) + color_data_size);
//         int padding_checker = 0;
//         for (int yy = h - 1; yy >= 0; --yy) {
//            for (int xx = 0; xx < w; ++xx) {
//               uint8_t color = src[0];
//               if (xx & 1) color = (color & 0x0F);
//               else       color = ((color >> 4) & 0x0F);
//               if (color < colors) {
//                  _putpixel32(bmp, xx, yy, (pal[color] | 0xFF000000) & GetMaskBit(bitmask, xx, yy, w, h));
//               }
//               else {
//                  _putpixel32(bmp, xx, yy, 0x00FF00FF);
//               }
//               if (xx & 1)
//               {
//                  src++;
//                  padding_checker++;
//                  padding_checker &= 3;
//               }
//            }
//            //if the pointer hasn't incremented to the next unsigned char yet, do so.
//            if (w & 1) //odd width
//            {
//               src++;
//               padding_checker++;
//               padding_checker &= 3;
//            }
//            //This loop jumps over any padding bytes.
//            while (padding_checker)
//            {
//               src++;
//               padding_checker++;
//               padding_checker &= 3;
//            }
//         }
//         return bmp;
//      }
//      break;
//      case 1:
//      {
//         if (colors > 2) colors = 2; //Color Count must be restricted to 2 entries at the most.
//         if (colors <= 0) colors = 2; //Color Count might be reported as zero. This means 2.
//         uint32_t * pal = (uint32_t *)(((uint8_t *)data) + ignore_size);
//         uint8_t * bitmaskXOR = (uint8_t *)(((uint8_t *)data) + ignore_size + (colors << 2));
//         uint8_t * bitmaskAND = (uint8_t *)(((uint8_t *)data) + ignore_size + (colors << 2) + color_data_size);
//         uint32_t  ret_colors[4] = { pal[0] | 0xFF000000, 0x00FF00FF, pal[1] | 0xFF000000, 0x0000FF00 };
//         for (int yy = h - 1; yy >= 0; --yy) {
//            for (int xx = 0; xx < w; ++xx) {
//               _putpixel32(bmp, xx, yy, GetColorMonochrome(bitmaskXOR, bitmaskAND, xx, yy, w, h, ret_colors));
//            }
//         }
//         return bmp;
//      }
//      break;
//      }
//      return bmp;
//   }
//}



//vector< BITMAP * > ResourceToBitmapVector(HMODULE hm, HRSRC hr, bool is_group_icon)
//{
//   vector< BITMAP * > results;
//   if (is_group_icon)
//   {
//      HGLOBAL hg = LoadResource(hm, hr);
//      GRPICONDIR * gd = (GRPICONDIR *)LockResource(hg);
//      if (gd->idType == 1)
//      {
//         for (int i = 0; i < gd->idCount; ++i)
//         {
//            //WARNING: The GRPICONDIRENTRY's data might be wrong!
//            GRPICONDIRENTRY * ie = (GRPICONDIRENTRY *)&(gd->idEntries[i]);
//            HRSRC ihr = FindResource(hm, MAKEINTRESOURCE(ie->nID), RT_ICON);
//            if (ihr != NULL)
//            {
//               HGLOBAL ihg = LoadResource(hm, ihr);
//               void * data = (void *)LockResource(ihg);
//               DWORD size = SizeofResource(hm, ihr);
//               uint32_t b = ((BITMAPINFOHEADER *)(data))->biBitCount;
//               uint32_t w = ((BITMAPINFOHEADER *)(data))->biWidth;
//               uint32_t h = (((BITMAPINFOHEADER *)(data))->biHeight >> 1); //icons have doubled height value.
//               uint32_t c = ((BITMAPINFOHEADER *)(data))->biClrUsed;
//               results.add(CreateBmp32bppFromIconResData(data, size, b, w, h, c));
//            }
//         }
//      }
//   }
//   else
//   {
//      HGLOBAL ihg = LoadResource(hm, hr);
//      void * data = (void *)LockResource(ihg);
//      DWORD size = SizeofResource(hm, hr);
//      uint32_t b = ((BITMAPINFOHEADER *)(data))->biBitCount;
//      uint32_t w = ((BITMAPINFOHEADER *)(data))->biWidth;
//      uint32_t h = (((BITMAPINFOHEADER *)(data))->biHeight >> 1); //icons have doubled height value.
//      uint32_t c = ((BITMAPINFOHEADER *)(data))->biClrUsed;
//      results.add(CreateBmp32bppFromIconResData(data, size, b, w, h, c));
//   }
//   return results;
//}
//
//
//
//vector< BITMAP * > IconFileToBitmapVector(void * icon_data, uint32_t icon_size)
//{
//   vector< BITMAP * > results;
//   ICONDIR * gd = (ICONDIR *)icon_data;
//   if (gd->idType == 1)
//   {
//      for (int i = 0; i < gd->idCount; ++i)
//      {
//         //WARNING: The ICONDIRENTRY's data might be wrong!
//         DWORD offset = gd->idEntries[i].dwImageOffset;
//         DWORD size = gd->idEntries[i].dwBytesInRes;
//         void * data = (void *)(((uint8_t *)icon_data) + ((uint32_t)offset));
//         uint32_t b = ((BITMAPINFOHEADER *)(data))->biBitCount;
//         uint32_t w = ((BITMAPINFOHEADER *)(data))->biWidth;
//         uint32_t h = (((BITMAPINFOHEADER *)(data))->biHeight >> 1); //icons have doubled height value.
//         uint32_t c = ((BITMAPINFOHEADER *)(data))->biClrUsed;
//         results.add(CreateBmp32bppFromIconResData(data, size, b, w, h, c));
//      }
//   }
//   return results;
//}

array< ::int_size > ico_file_sizes(const ::block & block)
{
   array< ::int_size > sizea;
   ICONDIR * gd = (ICONDIR *)block.data();
   if (gd->idType == 1)
   {
      for (int i = 0; i < gd->idCount; ++i)
      {
         //WARNING: The ICONDIRENTRY's data might be wrong!
         DWORD offset = gd->idEntries[i].dwImageOffset;
         DWORD size = gd->idEntries[i].dwBytesInRes;
         if (offset > block.size())
         {

            throw exception(::error_bad_data_format, "Could not get ico_file_sizes");

         }


         auto buf = (unsigned char *)(((uint8_t *)block.data()) + ((uint32_t)offset));

         int w;
         int h;

         if (buf[0] == 0x89 && buf[1] == 'P' && buf[2] == 'N' && buf[3] == 'G' && buf[4] == 0x0D && buf[5] == 0x0A 
            && buf[6] == 0x1A && buf[7] == 0x0A
            && buf[12] == 'I' && buf[13] == 'H' && buf[14] == 'D' && buf[15] == 'R')
         {

            w = (buf[16] << 24) + (buf[17] << 16) + (buf[18] << 8) + (buf[19] << 0);

            h = (buf[20] << 24) + (buf[21] << 16) + (buf[22] << 8) + (buf[23] << 0);

         }
         else
         {

            auto pheader = ((BITMAPINFOHEADER *)(buf));

            w = pheader->biWidth;

            h = pheader->biHeight >> 1; //icons have doubled height value.

         }

         sizea.add({w, h });

      }

   }
   
   return ::transfer(sizea);

}


//vector< BITMAP * > UnearthIconResource(string & file, bool self_refrence, bool res_index, int index)
//{
//#define LOAD_IGNORE_CODE_AUTHZ_LEVEL 0x00000010
//
//   //prevents a negative indexing error 
//   // (the boolean res_index handles whether it's icon index VS resource ID)
//   index = abs(index);
//
//   vector< BITMAP * > results; //array of results to return (pointers to 32bpp images)
//
//   //extract and 'demangle' the file extension by convertng to lowercase.
//   string ext = get_file_extension(file.c_str());
//   for (int i = 0; i < ext.size(); ++i) ext[i] = tolower(ext[i]);
//
//   bool is_icl = false;
//   if ((ext == "exe") || (ext == "dll") || (ext == "scr") || (is_icl = (ext == "icl")))
//   {
//      // Portable Executable Resource (works for both DLL and EXE)
//      // Also works for any 32bit Icon Library (Microangelo Studio?)
//      HMODULE hm = LoadLibraryEx(file.c_str(), NULL,
//         (DONT_RESOLVE_DLL_REFERENCES | LOAD_IGNORE_CODE_AUTHZ_LEVEL | LOAD_LIBRARY_AS_DATAFILE));
//      if (hm != NULL)
//      {
//         HRSRC hr;
//         if (!self_refrence)
//         {
//            if (res_index)
//            {
//               //The icon we want is at the resource ID (==index)
//               bool is_single_icon = false;
//               hr = FindResource(hm, MAKEINTRESOURCE(index), RT_GROUP_ICON);
//               if (hr == NULL)
//               {
//                  hr = FindResource(hm, MAKEINTRESOURCE(index), RT_ICON);
//                  is_single_icon = (hr != NULL);
//               }
//               if (hr != NULL)
//               {
//                  results = ResourceToBitmapVector(hm, hr, !is_single_icon);
//               }
//            }
//            else
//            {
//               //The icon we want is the (index)'th icon in the file
//               //We must preform a manual search for the resource ID!
//               //WARNING: Using EnumResourceNames() *DOES NOT WORK PROPERLY* for this.
//               for (int nicon = 0, i = 0; i < 0x8000; ++i)
//               {
//                  bool is_single_icon = false;
//                  hr = FindResource(hm, MAKEINTRESOURCE(i), RT_GROUP_ICON);
//                  if (hr != NULL)
//                  {
//                     if (nicon == index)
//                     {
//                        results = ResourceToBitmapVector(hm, hr, true);
//                        break;
//                     }
//                     nicon++;
//                  }
//               }
//            }
//         }
//         else
//         {
//            //The icon we want is the "first" icon in the file. 
//            //Happens when location is a %1.
//            //We must preform a manual search for the resource ID!
//            //WARNING: Using EnumResourceNames() *DOES NOT WORK PROPERLY* for this.
//            for (int i = 0; i < 0x8000; ++i)
//            {
//               bool is_single_icon = false;
//               hr = FindResource(hm, MAKEINTRESOURCE(i), RT_GROUP_ICON);
//               if (hr != NULL)
//               {
//                  results = ResourceToBitmapVector(hm, hr, true);
//                  break;
//               }
//            }
//         }
//         FreeLibrary(hm);
//      }
//      else /*if(is_icl)
//      {//OH NOES. We have to load a *16bit* .icl file!
//          //not supported yet. sorry. left as another excecise to the programmer.
//      }*/
//   }
//   else if (ext == "ico")
//   {
//      //Single Icon File
//
//      //###################################################
//      //#  PSEUDO-CODE: Do the file loading yourself ;)
//      //void * data_pointer = NULL;
//      //uint32_t data_size = 0;
//      //if (data_pointer = MyLoadFile(file.c_str(), &data_size))
//      //{
//      //   if (data_size)
//      //   {
//            //results = IconFileToBitmapVector((void *)data_pointer, data_size);
//      //   }
//      //}
//      //MyCloseFile(data_pointer);
//   }
//   return results;
//}


namespace windowing_win32
{


   icon::icon()
   {

      
   }


   icon::~icon()
   {

      _erase_all();

   }


   void * icon::get_os_data(const ::int_size & size) const
   {

      auto & iconitem = ((icon *)this)->m_iconmap[size];

      if (!iconitem.m_bCalculated)
      {

         iconitem.m_bCalculated = true;

         if (m_pathProcessed.has_character())
         {

            string strPath = m_pathProcessed;

            if (strPath.case_insensitive_begins_eat("zipresource://"))
            {

               auto pfile = m_papplication->file()->create_resource_file(strPath);

               if (!image())
               {

                  return nullptr;

               }

               auto pimage = image()->get_image(pfile);

               auto pimageResized = image()->create_image(size);

               bool bOk = false;

               try
               {

                  ::image::image_source imagesource(pimage);

                  ::image::image_drawing_options imagedrawingoptions(size);

                  ::image::image_drawing imagedrawing(imagedrawingoptions, imagesource);

                  pimageResized->g()->set_compositing_quality(::draw2d::e_compositing_quality_high_quality);

                  pimageResized->draw(imagedrawing);

                  bOk = true;

               }
               catch (...)
               {


               }

               if (bOk)
               {

                  iconitem.m_hicon = (HICON)((icon *)this)->system()->node()->m_pauranode->HICON_from_image(pimageResized);

               }

            }
            else 
            {

               iconitem.m_hicon = (HICON) ::LoadImageW(nullptr, wstring(m_pathProcessed), IMAGE_ICON, size.cx(), size.cy(), LR_LOADFROMFILE);

            }

         }

      }

      if (!iconitem.m_hicon)
      {

         if (!m_iconmap.is_empty())
         {

            ::int_size size1 = size;

            for (auto& pair : m_iconmap)
            {

               auto iconitem1 = pair.element2();

               if (iconitem1.m_hicon)
               {

                  auto info = MyGetIconInfo((HICON)iconitem1.m_hicon);

                  if (info.nWidth > size1.cx() && info.nHeight > size1.cy())
                  {

                     size1.cx() = info.nWidth;
                     size1.cy() = info.nHeight;
                     iconitem.m_hicon = (HICON)iconitem1.m_hicon;

                  }

               }

            }

            if (!iconitem.m_hicon)
            {

               size1.cx() = 0;
               size1.cy() = 0;

               for (auto& pair : m_iconmap)
               {

                  auto & iconitem1 = pair.m_element2;

                  if (iconitem1.m_hicon)
                  {

                     auto info = MyGetIconInfo(iconitem1.m_hicon);

                     if (info.nWidth > size1.cx()
                        && info.nHeight > size1.cy())
                     {

                        size1.cx() = info.nWidth;
                        size1.cy() = info.nHeight;
                        iconitem.m_hicon = iconitem1.m_hicon;

                     }

                  }

               }

            }

         }

      }

      return iconitem.m_hicon;

   }


   bool icon::add_icon(HICON hicon)
   {

      if (::is_null(hicon))
      {

         return false;

      }

      auto info = MyGetIconInfo(hicon);

      m_iconmap[{info.nWidth, info.nHeight}].m_hicon = hicon;

      m_iconmap[{info.nWidth, info.nHeight}].m_bCalculated = true;
      
      return true;

   }


   void icon::load_file(const ::string & strPath)
   {

      m_pathProcessed = m_papplication->defer_process_matter_path(strPath);

      auto memory = m_papplication->file()->as_memory(m_pathProcessed);

      if (memory.is_empty())
      {

         throw exception(error_failed);

      }

      auto pmemoryfile = create_memory_file(memory);

      auto pimage = image()->load_image(pmemoryfile);

      if (pimage.ok())
      {

         m_imagemap[pimage->size()] = pimage;

         return;

      }

      auto sizes = ico_file_sizes(memory);

      for (auto & size : sizes)
      {
         // just to enumerate the sizes
         m_iconmap.set_at(size, { });

      }

      //::i32_array ia;

      //ia.add(16);
      //ia.add(24);
      //ia.add(32);
      //ia.add(48);
      //ia.add(256);

      //for (auto i : ia)
      //{

      //   HICON hicon = (HICON) ::LoadImageW(nullptr, wstring(strProcessedPath), IMAGE_ICON, i, i, LR_LOADFROMFILE);

      //   if (hicon != nullptr)
      //   {

      //      m_iconmap[::int_size(i, i)] = hicon;

      //   }

      //}

      //return m_pathProcessed.has_character();

//      return !m_iconmap.is_empty();

//#else
//
//      m_strAppTrayIcon = strPath;
//
//      return true;
//
//#endif

   }


   void icon::load_app_tray_icon(const ::string & strApp)
   {

      string strMatter = "main/icon.png";

      load_matter(strMatter);

      //if (!load_matter(strMatter))
      //{

      //   return false;

      //}

      //return true;

   }


   void icon::get_sizes(::size_i32_array & a)
   {

      a.erase_all();

      for (auto & size : m_iconmap.items())
      {

         a.add(size);

      }

   }

   ::image::image_pointer icon::get_image(const ::int_size & size)
   {

      auto& pimage  = m_imagemap[size];

      if (pimage)
      {

         return pimage;

      }

      pimage = _create_image(size);

      return pimage;

   }


   ::image::image_pointer icon::_create_image(const ::int_size & size)
   {

      HICON hicon = (HICON) get_os_data(size);

      if (::is_null(hicon))
      {

         return nullptr;

      }

      ::pointer<::image>pimage;

      ::__construct(this, pimage);

      bool bOk = false;

      HBITMAP hbitmap = nullptr;

      HDC hdc = nullptr;

      HBITMAP hbitmapOld = nullptr;

      try
      {

         BITMAPINFO info;

         ZeroMemory(&info, sizeof(BITMAPINFO));

         auto iScan = size.cx() * 4;

         info.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
         info.bmiHeader.biWidth = size.cx();
         info.bmiHeader.biHeight = -size.cy();
         info.bmiHeader.biPlanes = 1;
         info.bmiHeader.biBitCount = 32;
         info.bmiHeader.biCompression = BI_RGB;
         info.bmiHeader.biSizeImage = size.cy() * iScan;

         ::image32_t * pimage32 = nullptr;

         hbitmap = ::CreateDIBSection(nullptr, &info, DIB_RGB_COLORS, (void **)&pimage32, nullptr, 0);

         ::pixmap pixmap;

         pixmap.init(size, pimage32, iScan);

         hdc = ::CreateCompatibleDC(nullptr);

         hbitmapOld = (HBITMAP) ::SelectObject(hdc, hbitmap);

         if (!::DrawIconEx(hdc, 0, 0, hicon, size.cx(), size.cy(), 0, nullptr, DI_IMAGE | DI_MASK))
         {

            return nullptr;

         }

         ::GdiFlush();

         //bool bAllZeroAlpha = true;
         //bool bTheresUint32 = false;

         //pixmap.map();

         //int area = size.area();

         //auto pc = pixmap.colorref();
         //unsigned char * pA = &((unsigned char *)pc)[3];

         //for (int i = 0; i < area; i++)
         //{
         //   if (*pc != 0)
         //   {
         //      bTheresUint32 = true;
         //   }
         //   if (*pA != 0)
         //   {
         //      bAllZeroAlpha = false;
         //      break;
         //   }
         //   pc++;
         //   pA += 4;
         //}

         //if (bAllZeroAlpha && bTheresUint32)
         //{

         //   pc = pixmap.colorref();
         //   pA = &((unsigned char *)pc)[3];

         //   for (int i = 0; i < area; i++)
         //   {
         //      if (*pc != 0)
         //      {
         //         *pA = 255;
         //      }
         //      pc++;
         //      pA += 4;
         //   }

         //   ::SelectObject(hdc, hbitmapOld);

            pimage->create(size);

            pimage->map();

            ::copy_image32(pimage, pixmap);

         //}

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

      return pimage;


   }


   void icon::_erase_all()
   {

      for (auto iconitem : m_iconmap.payloads())
      {

         if (iconitem.m_hicon)
         {

            ::DestroyIcon(iconitem.m_hicon);

         }

      }

      m_iconmap.erase_all();

   }


} // namespace windowing_win32





#ifdef WINDOWS_DESKTOP

// http ://stackoverflow.com/questions/1913468/how-to-determine-the-int_size-of-an-icon-from-a-hicon
// http://stackoverflow.com/users/739731/sergey

MYICON_INFO MyGetIconInfo(HICON hIcon)
{
   MYICON_INFO myinfo{};

   ICONINFO info{};

   BOOL bRes = false;

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


