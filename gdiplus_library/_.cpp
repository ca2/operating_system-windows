#include "framework.h"
#include "acme/exception/error_number.h"
#include "acme/_library.h"
#include <mutex>



#pragma comment (lib, "gdiplus.lib")

Gdiplus::GdiplusStartupInput *   g_pgdiplusStartupInput = nullptr;
Gdiplus::GdiplusStartupOutput *  g_pgdiplusStartupOutput = nullptr;
DWORD_PTR                        g_gdiplusToken = NULL;
DWORD_PTR                        g_gdiplusHookToken = NULL;
::i32                            g_iGdiplusReferenceCount = 0;
std::mutex                       g_mutexGdiplus;


CLASS_DECL_GDIPLUS_LIBRARY void initialize_gdiplus()
{

   std::scoped_lock lock(g_mutexGdiplus);

   if (g_iGdiplusReferenceCount > 0)
   {

      g_iGdiplusReferenceCount++;

      return;

   }

   g_pgdiplusStartupInput = øraw_new Gdiplus::GdiplusStartupInput ();

   g_pgdiplusStartupOutput = øraw_new Gdiplus::GdiplusStartupOutput ();

   g_gdiplusToken = NULL;

   g_gdiplusHookToken = NULL;

   g_pgdiplusStartupInput->SuppressBackgroundThread = true;

   Gdiplus::Status statusStartup = GdiplusStartup(&g_gdiplusToken, g_pgdiplusStartupInput, g_pgdiplusStartupOutput);

   if (statusStartup != Gdiplus::Ok)
   {

      output_debug_string("Gdiplus Failed to Startup. ca cannot continue.");

      ::acme::del(g_pgdiplusStartupInput);
      ::acme::del(g_pgdiplusStartupOutput);

      throw ::exception(error_failed, "GdiplusStartup failed");

   }

   statusStartup = g_pgdiplusStartupOutput->NotificationHook(&g_gdiplusHookToken);

   if (statusStartup != Gdiplus::Ok)
   {

      output_debug_string("Gdiplus Failed to Hook. ca cannot continue.");

      ::Gdiplus::GdiplusShutdown(g_gdiplusToken);

      ::acme::del(g_pgdiplusStartupInput);
      ::acme::del(g_pgdiplusStartupOutput);

      throw ::exception(error_failed, "GDI+ notification hook failed");

   }

   g_iGdiplusReferenceCount = 1;

}


CLASS_DECL_GDIPLUS_LIBRARY void terminate_gdiplus()
{

   std::scoped_lock lock(g_mutexGdiplus);

   if (g_iGdiplusReferenceCount <= 0)
   {

      return;

   }

   g_iGdiplusReferenceCount--;

   if (g_iGdiplusReferenceCount == 0 && g_pgdiplusStartupOutput != nullptr)
   {

      g_pgdiplusStartupOutput->NotificationUnhook(g_gdiplusHookToken);

      ::Gdiplus::GdiplusShutdown(g_gdiplusToken);

      ::acme::del(g_pgdiplusStartupInput);
      ::acme::del(g_pgdiplusStartupOutput);

      g_gdiplusToken = NULL;
      g_gdiplusHookToken = NULL;

   }

}


CLASS_DECL_GDIPLUS_LIBRARY ::string _001_gdiplus_bitmap_diagnostics(Gdiplus::Bitmap *bitmap)
{
  
   if (!bitmap)
   {

      return "bitmap is null";

   }

   ::string str;

   // 1. Width, Height
   UINT width = bitmap->GetWidth();
   UINT height = bitmap->GetHeight();

   Gdiplus::Rect rect(0, 0, width, height);
   Gdiplus::BitmapData bitmapData;

   // Lock bits in 32-bit ARGB format to guarantee an alpha channel is present
   if (bitmap->LockBits(&rect, Gdiplus::ImageLockModeRead, PixelFormat32bppARGB, &bitmapData) == Gdiplus::Ok)
   {

      // 2. Scan size (Stride) and Pointer Address
      INT stride = bitmapData.Stride; // Scan size in bytes
      BYTE *pixelPtr = (BYTE *)bitmapData.Scan0; // Pointer address


      str.formatf("\n\n   gdiplus::bitmap=%p (%d,%d) scan=%d,", pixelPtr, width, height, stride);


      int totalPixels = width * height;
      int transparentCount = 0;
      int translucentCount = 0;
      int opaqueCount = 0;

      // Iterate through pixel data
      UINT *pixels = (UINT *)pixelPtr;
      for (UINT y = 0; y < height; ++y)
      {
         for (UINT x = 0; x < width; ++x)
         {
            // Get the ARGB color of the pixel
            UINT color = pixels[y * (stride / 4) + x];
            BYTE alpha = (color >> 24) & 0xFF; // Shift and mask for Alpha

            if (alpha == 0)
            {
               transparentCount++;
            }
            else if (alpha > 0 && alpha < 255)
            {
               translucentCount++;
            }
            else
            {
               opaqueCount++;
            }
         }
      }

      // Always unlock the bits when finished
      bitmap->UnlockBits(&bitmapData);

      str.append_formatf("\n   pixel=%d opaque=%d transp=%d transl=%d\n", totalPixels, opaqueCount,
                                transparentCount, translucentCount);

      // Output or store the statistics as needed
      // totalPixels, width, height, stride, pixelPtr, transparentCount, translucentCount, opaqueCount
   }
   else
   {

      str.formatf("\n\n   gdiplus::bitmap (%d,%d) couldn't lock bits!!");

   }

   return str;
}
