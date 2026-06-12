//
// Created by camilo on 2024-09-13 14:01 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "graphics.h"
#include "acme/platform/application.h"
#include "operating_system-windows/gdiplus_library/_.h"
#include <objidl.h>  // For IStream
#include <gdiplus.h> // For GDI+
#pragma comment (lib, "gdiplus.lib")
#pragma comment (lib, "ole32.lib") // For CreateStreamOnHGlobal

using namespace Gdiplus;

      namespace nano_graphics_gdiplus
      {



         graphics::graphics()
         {

            initialize_gdiplus();

         }


         graphics::~graphics()
         {
            
            terminate_gdiplus();

         }






         
         //void user::_erase_minimize_box_style(HWND hwnd)
         //{
         // 
         //   LONG style = GetWindowLong(hwnd, GWL_STYLE);

         //   style = style & ~(WS_MINIMIZEBOX);

         //   SetWindowLong(hwnd, GWL_STYLE, style);

         //}


      } // namespace nano_graphics_gdiplus

