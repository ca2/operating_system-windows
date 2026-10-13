// From apex/operating_system/windows/gdi.cpp by camilo on 2022-11-07 04:22 <3ThomasBorregaardSorensen!!
#include "platform.h"


#include "acme/_operating_system.h"


// http://stackoverflow.com/questions/7375003/how-to-convert-hicon-to-hbitmap-in-vc

// answered Aug 12 at 15:34
// befzz
// 10714


CLASS_DECL_APEX_WINDOWS HBITMAP get_icon_hbitmap(HICON hICON)
{

   //HICON hICON = /*your code here*/
   HBITMAP hBITMAPcopy;
#ifdef __REACTOS__
   ICONINFO IconInfo{};
#else
   ICONINFOEX IconInfo{};
#endif
   //BITMAP BM_32_bit_color;
   //BITMAP BM_1_bit_mask;

   // 1. From HICON to HBITMAP for color and mask separately
   //.cbSize required
   //memory_set((void*)&IconInfo, 0, sizeof(ICONINFOEX));
#ifdef __REACTOS__
   if (!GetIconInfo(hICON, &IconInfo))
      return nullptr;
#else
   IconInfo.cbSize = sizeof(ICONINFOEX);
   if (!GetIconInfoEx(hICON, &IconInfo))
      return nullptr;
#endif


   //HBITMAP IconInfo.hbmColor is 32bit per pxl, however alpha bytes can be zeroed or can be not.
   //HBITMAP IconInfo.hbmMask is 1bit per pxl

   // 2. From HBITMAP to BITMAP for color
   //    (HBITMAP without raw data -> HBITMAP with raw data)
   //         LR_CREATEDIBSECTION - DIB section will be created,
   //         so .bmBits pointer will not be null
   hBITMAPcopy = (HBITMAP)CopyImage(IconInfo.hbmColor, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
   if (IconInfo.hbmColor)
      DeleteObject(IconInfo.hbmColor);
   if (IconInfo.hbmMask)
      DeleteObject(IconInfo.hbmMask);
   //    (HBITMAP to BITMAP)
   //GetObject(hBITMAPcopy,sizeof(BITMAP),&BM_32_bit_color);
   //Now: BM_32_bit_color.bmBits pointing to BGRA data.(.bmWidth * .bmHeight * (.bmBitsPixel/8))

   // 3. From HBITMAP to BITMAP for mask
   //hBITMAPcopy = (HBITMAP)CopyImage(IconInfo.hbmMask,IMAGE_BITMAP,0,0,LR_CREATEDIBSECTION);
   //GetObject(hBITMAPcopy,sizeof(BITMAP),&BM_1_bit_mask);
   //Now: BM_1_bit_mask.bmBits pointing to mask data (.bmWidth * .bmHeight Bits!)

   return hBITMAPcopy;
}



