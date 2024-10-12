//
// Created by camilo on 2024-09-27 02:45 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "icon.h"
#include "acme/_operating_system.h"
//#include <windows.h>
#include <wincodec.h> // Windows Imaging Component (WIC)

// Function to convert a PNG buffer in memory to an HBITMAP
HBITMAP LoadPNGFromMemoryIntoHBITMAP(const void * pngData, size_t dataSize, HDC hdc)
{
   // Initialize COM library
   CoInitialize(NULL);

   // Create the WIC factory
   IWICImagingFactory * pFactory = NULL;
   HRESULT hr = CoCreateInstance(
       CLSID_WICImagingFactory,
       NULL,
       CLSCTX_INPROC_SERVER,
       IID_IWICImagingFactory,
       (LPVOID *)&pFactory
   );

   if (FAILED(hr))
   {
      CoUninitialize();
      return NULL;
   }

   // Create a WIC stream to read from the memory buffer
   IWICStream * pStream = NULL;
   hr = pFactory->CreateStream(&pStream);

   if (FAILED(hr))
   {
      pFactory->Release();
      CoUninitialize();
      return NULL;
   }

   // Initialize the stream with the memory buffer
   hr = pStream->InitializeFromMemory((BYTE *)pngData, (DWORD) dataSize);

   if (FAILED(hr))
   {
      pStream->Release();
      pFactory->Release();
      CoUninitialize();
      return NULL;
   }

   // Create a decoder from the stream (PNG decoder in this case)
   IWICBitmapDecoder * pDecoder = NULL;
   hr = pFactory->CreateDecoderFromStream(
       pStream,                     // Stream with the PNG data
       NULL,                        // No preferred vendor
       WICDecodeMetadataCacheOnDemand, // Cache metadata on demand
       &pDecoder
   );

   if (FAILED(hr))
   {
      pStream->Release();
      pFactory->Release();
      CoUninitialize();
      return NULL;
   }

   // Get the first frame of the image
   IWICBitmapFrameDecode * pFrame = NULL;
   hr = pDecoder->GetFrame(0, &pFrame);

   if (FAILED(hr))
   {
      pDecoder->Release();
      pStream->Release();
      pFactory->Release();
      CoUninitialize();
      return NULL;
   }

   // Convert the frame to a format compatible with GDI (32bpp BGRA)
   IWICFormatConverter * pConverter = NULL;
   hr = pFactory->CreateFormatConverter(&pConverter);

   if (FAILED(hr))
   {
      pFrame->Release();
      pDecoder->Release();
      pStream->Release();
      pFactory->Release();
      CoUninitialize();
      return NULL;
   }

   hr = pConverter->Initialize(
       pFrame,                         // Input frame
       GUID_WICPixelFormat32bppBGRA,   // Output pixel format
       WICBitmapDitherTypeNone,        // No dithering
       NULL,                           // No palette needed
       0.0,                            // Alpha threshold
       WICBitmapPaletteTypeCustom      // No palette transformation
   );

   if (FAILED(hr))
   {
      pConverter->Release();
      pFrame->Release();
      pDecoder->Release();
      pStream->Release();
      pFactory->Release();
      CoUninitialize();
      return NULL;
   }

   // Create a DIB section that GDI can use
   UINT width = 0, height = 0;
   pConverter->GetSize(&width, &height);

   BITMAPINFO bminfo = { 0 };
   bminfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
   bminfo.bmiHeader.biWidth = width;
   bminfo.bmiHeader.biHeight = -(LONG)height; // Negative height for top-down DIB
   bminfo.bmiHeader.biPlanes = 1;
   bminfo.bmiHeader.biBitCount = 32; // 32 bits per pixel
   bminfo.bmiHeader.biCompression = BI_RGB;

   // Create the bitmap
   void * pvImageBits = NULL;
   HBITMAP hBitmap = CreateDIBSection(
       hdc, &bminfo, DIB_RGB_COLORS, &pvImageBits, NULL, 0
   );

   if (hBitmap == NULL)
   {
      pConverter->Release();
      pFrame->Release();
      pDecoder->Release();
      pStream->Release();
      pFactory->Release();
      CoUninitialize();
      return NULL;
   }

   // Copy the pixels from the WIC bitmap to the DIB section
   hr = pConverter->CopyPixels(
       NULL,                          // Copy the entire bitmap
       width * 4,                     // Bytes per scanline (4 bytes per pixel)
       width * height * 4,            // Total size of the image
       (BYTE *)pvImageBits             // Destination buffer
   );

   // Cleanup
   pConverter->Release();
   pFrame->Release();
   pDecoder->Release();
   pStream->Release();
   pFactory->Release();
   CoUninitialize();

   if (FAILED(hr))
   {
      DeleteObject(hBitmap);
      return NULL;
   }

   return hBitmap;
}

// Function to load image from memory buffer into a GDI+ Image object
Gdiplus::Image * LoadGdiplusImageFromMemory(BYTE * buffer, size_t bufferSize)
{
   // Create a stream from the memory buffer
   HGLOBAL hMemory = GlobalAlloc(GMEM_MOVEABLE, bufferSize);
   if (!hMemory)
      return nullptr;

   void * pMemory = GlobalLock(hMemory);
   memcpy(pMemory, buffer, bufferSize);
   GlobalUnlock(hMemory);

   IStream * pStream = NULL;
   if (CreateStreamOnHGlobal(hMemory, TRUE, &pStream) != S_OK)
   {
      GlobalFree(hMemory);
      return nullptr;
   }

   // Load the image from the stream
   Gdiplus::Image * pImage = __raw_new Gdiplus::Image(pStream, FALSE);

   // Clean up
   pStream->Release();

   return pImage;
}

namespace windows
{

   namespace nano
   {

      namespace graphics
      {

         icon::icon()
         {

            m_pimage = nullptr;

         }


         icon::~icon()
         {

            if (m_pimage)
            {

               delete m_pimage;

            }


         }


         void icon::load_image_file(const void * p, memsize size)
         {


            if (m_pimage)
            {

               delete m_pimage;

            }

            m_pimage = LoadGdiplusImageFromMemory((BYTE *) p, size);

            



         }


      } // namespace graphics


   } // namespace nano


} // namespace windows


