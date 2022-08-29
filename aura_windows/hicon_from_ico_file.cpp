// Created by camilo on 2021-11-16 12:53 BRT <3ThomasBorregaardSørensen!!
#include "framework.h"
#include "acme/operating_system.h"
#include "aura/graphics/image/image.h"
#include "node.h"
#include <gdiplus.h>


namespace aura_windows
{


   // If you can use GDI + , you can wrap the raw ICO data
   // in an IStream using CreateStreamOnHGlobal() or SHCreateMemStream(),
   // and then pass that stream to the Bitmap class constructor 
   // or Bitmap::FromStream() method, and then finally call the 
   // Bitmap::ToHICON() method.
   // – Remy Lebeau,  Feb 11 '17 at 3:34
   void* node::HICON_from_image(::image *pimage)
   {

      //comptr < IStream > pistream = SHCreateMemStream((const BYTE*)block.get_data(), (UINT)block.get_size());

      //if (!pistream)
      //{

      //   return nullptr;

      //}

      Gdiplus::Bitmap bitmap(pimage->width(),
         pimage->height(),
         pimage->m_iScan,
         PixelFormat32bppARGB,
         (BYTE *) pimage->get_data()
         );

      HICON hicon = nullptr;

      auto status = bitmap.GetHICON(&hicon);

      if (status != Gdiplus::Ok)
      {

         return nullptr;

      }

      return hicon;

   }


} // namespace aura_windows



