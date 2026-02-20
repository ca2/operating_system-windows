// Created by camilo on 2024-09-13 01:00 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "icon.h"
#include "still.h"
#include "acme/operating_system/windows/windowing.h"



::Gdiplus::Image * LoadImageFromMemory(const void * imageData, memsize size)
{
   // Create an IStream object from the memory buffer
   HGLOBAL hGlobal = GlobalAlloc(GMEM_MOVEABLE, size);
   if (!hGlobal)
      return nullptr;

   void * pData = GlobalLock(hGlobal);
   memcpy(pData, imageData, size);
   GlobalUnlock(hGlobal);

   IStream * pStream = nullptr;
   HRESULT hr = CreateStreamOnHGlobal(hGlobal, TRUE, &pStream); // TRUE so the stream releases the memory
   if (FAILED(hr))
   {
      GlobalFree(hGlobal);
      return nullptr;
   }

   // Load the image from the stream using GDI+
   ::Gdiplus::Image * image = new ::Gdiplus::Image(pStream);
   pStream->Release();

   return image;
}

namespace innate_ui_win32
{

   //LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

   still::still()
   {
      m_bIcon = false;
      m_iCreateStyle = WS_TABSTOP | WS_VISIBLE | WS_CHILD | SS_LEFT;
   }


   still::~still()
   {

      if (m_pgdiplusimage)
      {

         delete m_pgdiplusimage;

         m_pgdiplusimage = nullptr;

      }

   }




   void still::_create_child(window * pwindowParent)
   {

      HINSTANCE hinstanceParent = (HINSTANCE)GetWindowLongPtr(pwindowParent->m_hwnd, GWLP_HINSTANCE);

      m_hwnd = CreateWindow(
         L"STATIC",  // Predefined class; Unicode assumed 
         L"",      // Button text 
         m_iCreateStyle,  // Styles 
         10,         // x position 
         10,         // y position 
         100,        // Button width
         100,        // Button height
         pwindowParent->m_hwnd,     // Parent window
         NULL,       // No menu.
         (HINSTANCE)hinstanceParent,
         NULL);

      if (m_bIcon)
      {

         ::cast < ::windows::windowing > pwindowing = system()->acme_windowing();

         pwindowing->m_windowmap[m_hwnd] = this;

         SetWindowLongPtr(m_hwnd, GWLP_WNDPROC, (LPARAM)&::windows::window_procedure);

      }

   }

   void still::create_icon_still(::innate_ui::window * pwindowParent)
   {

      m_bIcon = true;

      m_iDebugAtom = 123;

      m_iCreateStyle = WS_TABSTOP | WS_VISIBLE | WS_CHILD | SS_OWNERDRAW;

      create_child(pwindowParent);


   }


   void still::set_icon(::innate_ui::icon * piconParam)
   {

      ::pointer <::innate_ui_win32::icon > picon = piconParam;

      main_send([this, picon]()
      {

         
         //::SendMessage(m_hwnd, STM_SETICON, (WPARAM) picon->m_hicon, 0);

         m_pgdiplusimage = LoadImageFromMemory(picon->m_memory.data(), picon->m_memory.size());
         
      });

   }

   
   LRESULT still::_window_procedure(UINT message, WPARAM wparam, LPARAM lparam)
   {

      if (message == WM_PAINT && m_bIcon)
      {
         
         PAINTSTRUCT ps;

         HDC hdc = ::BeginPaint(m_hwnd, &ps);

         ::Gdiplus::Graphics graphics(hdc);

         if (m_pgdiplusimage)
         {

            Gdiplus::Rect r;
            RECT rectClient;
            ::GetClientRect(m_hwnd, &rectClient);
            r.X = 0;
            r.Y = 0;
            r.Width = ::width(rectClient);
            r.Height = ::height(rectClient);

            graphics.DrawImage(m_pgdiplusimage, r, 0, 0, 
               m_pgdiplusimage->GetWidth(),
               m_pgdiplusimage->GetHeight(), Gdiplus::UnitPixel);

         }

         ::EndPaint(m_hwnd, &ps);

      }

      return ::innate_ui_win32::window::_window_procedure(message, wparam, lparam);

   }


} // namespace innate_ui
