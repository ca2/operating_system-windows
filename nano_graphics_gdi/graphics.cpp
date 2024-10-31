//
// Created by camilo on 2024-09-13 14:01 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "graphics.h"
#include "acme/platform/application.h"
#include <objidl.h>  // For IStream
#include <gdiplus.h> // For GDI+
#pragma comment (lib, "gdiplus.lib")
#pragma comment (lib, "ole32.lib") // For CreateStreamOnHGlobal

using namespace Gdiplus;

// Function to initialize GDI+
void InitGDIPlus(ULONG_PTR * gdiplusToken)
{

   GdiplusStartupInput gdiplusStartupInput;

   GdiplusStartup(gdiplusToken, &gdiplusStartupInput, NULL);

}


// Function to shutdown GDI+
void ShutdownGDIPlus(ULONG_PTR gdiplusToken)
{

   GdiplusShutdown(gdiplusToken);

}


namespace windows
{


   namespace nano
   {


      namespace graphics
      {



         graphics::graphics()
         {

            gdiplusToken = 0;

            InitGDIPlus(&gdiplusToken);

         }


         graphics::~graphics()
         {
            
            ShutdownGDIPlus(gdiplusToken);

         }






         
         //void user::_erase_minimize_box_style(HWND hwnd)
         //{
         // 
         //   LONG style = GetWindowLong(hwnd, GWL_STYLE);

         //   style = style & ~(WS_MINIMIZEBOX);

         //   SetWindowLong(hwnd, GWL_STYLE, style);

         //}


      } // namespace graphics


   } // namespace nano


} // namespace windows



