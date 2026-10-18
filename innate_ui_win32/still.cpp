// Created by camilo on 2024-09-13 01:00 <3ThomasBorregaardSorensen!!
#include "platform.h"
#include "dpi_compat.h"
#include "icon.h"
#include "still.h"
#include <memory>
#include "acme/operating_system/windows/windowing.h"


static ::Gdiplus::Image * LoadImageFromMemory(const void * imageData, memsize size, IStream **retainedStream)
{
   *retainedStream = nullptr;
   if (!imageData || size <= 0)
      return nullptr;
   HGLOBAL hGlobal = GlobalAlloc(GMEM_MOVEABLE, size);
   if (!hGlobal)
      return nullptr;
   void *pData = GlobalLock(hGlobal);
   if (!pData)
   {
      GlobalFree(hGlobal);
      return nullptr;
   }
   memcpy(pData, imageData, size);
   GlobalUnlock(hGlobal);

   struct stream_scope
   {
      IStream *stream = nullptr;
      ~stream_scope() { if (stream) stream->Release(); }
   } owner;
   if (FAILED(CreateStreamOnHGlobal(hGlobal, TRUE, &owner.stream)))
   {
      GlobalFree(hGlobal);
      return nullptr;
   }
   std::unique_ptr<Gdiplus::Image> image(new Gdiplus::Image(owner.stream));
   if (image->GetLastStatus() != Gdiplus::Ok)
      return nullptr;
   // Keep the stream alive through painting and image destruction.
   *retainedStream = owner.stream;
   owner.stream = nullptr;
   return image.release();
}

namespace innate_ui_win32
{

   //LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

   still::still()
   {
      m_pgdiplusimage = nullptr;
      m_pImageStream = nullptr;
      m_bIcon = false;
      m_iCreateStyle = WS_TABSTOP | WS_VISIBLE | WS_CHILD | SS_LEFT;
   }


   still::~still()
   {
      delete m_pgdiplusimage;
      m_pgdiplusimage = nullptr;
      if (m_pImageStream)
      {
         m_pImageStream->Release();
         m_pImageStream = nullptr;
      }
   }


   void still::_create_child(window * pwindowParent)
   {

      auto hwndParent = (HWND) pwindowParent->_HWND();

      if (::is_null(hwndParent) || hwndParent == INVALID_HANDLE_VALUE)
      {

         throw ::exception(error_bad_argument, "Parent window handle is null or INVALID_HANDLE_VALUE");
      }

      auto hinstanceParent = (HINSTANCE)GetWindowLongPtr(hwndParent, GWLP_HINSTANCE);

      if (::is_null(hinstanceParent))
      {

         throw ::exception(error_wrong_state, "Parent window hinstance is null");
      }

      auto hwndResult =
         _create_subclassed_window(
            0,
         L"STATIC",  // Predefined class; Unicode assumed 
         L"",      // Button text 
         m_iCreateStyle,  // Styles 
         10,         // x position 
         10,         // y position 
         100,        // Button width
         100,        // Button height
         hwndParent, // Parent window
         NULL,       // No menu.
         (HINSTANCE)hinstanceParent,
         NULL);

      if (!hwndResult || !_HWND())
      {

         throw ::exception(error_failed);

      }

      if (hwndResult != ::as_HWND(this->operating_system_window()))
      {

         m_windowswindow = hwndResult;

      }

      if (m_bIcon)
      {

         ::cast < ::windows::windowing > pwindowing = system()->acme_windowing();

         auto hwnd = ::as_HWND(this->operating_system_window());

         pwindowing->m_windowmap[hwnd] = this;

         SetWindowLongPtr(hwnd, GWLP_WNDPROC, (LPARAM) & ::windows::window::s_window_procedure);

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
      ::pointer<::innate_ui_win32::icon> picon = piconParam;
      // Image replacement must run on the same UI thread as WM_PAINT.
      main_send([this, picon]()
      {
#if defined(__REACTOS__)
         information() << "ABOUT_ICON replacing native image";
#endif
         delete m_pgdiplusimage;
         m_pgdiplusimage = nullptr;
         if (m_pImageStream)
         {
            m_pImageStream->Release();
            m_pImageStream = nullptr;
         }
         if (!picon)
            return;
         try
         {
            if (picon->m_memory.data() && picon->m_memory.size() > 0)
               m_pgdiplusimage = LoadImageFromMemory(picon->m_memory.data(),
                  picon->m_memory.size(), &m_pImageStream);
            else if (picon->m_hicon)
            {
               std::unique_ptr<Gdiplus::Bitmap> image(new Gdiplus::Bitmap(picon->m_hicon));
               if (image->GetLastStatus() == Gdiplus::Ok)
                  m_pgdiplusimage = image.release();
            }
         }
         catch (...)
         {
            // An unavailable icon must not prevent the dialog from opening.
         }
#if defined(__REACTOS__)
         informationf("ABOUT_ICON native image ready=%d", m_pgdiplusimage != nullptr);
#endif
      });
   }


   bool still::on_window_procedure(::lresult & lresult, ::u32 message, ::wparam wparam, ::lparam lparam)
   {

      if (message == WM_PAINT && m_bIcon)
      {
         
         PAINTSTRUCT ps;

         auto hwnd = ::as_HWND(this->operating_system_window());

         HDC hdc = ::BeginPaint(hwnd, &ps);

         RECT background;
         ::GetClientRect(hwnd, &background);
         ::FillRect(hdc, &background, m_bDarkMode
            ? m_hbrushDarkBackground : ::GetSysColorBrush(COLOR_3DFACE));

         ::Gdiplus::Graphics graphics(hdc);

         if (m_pgdiplusimage)
         {

            Gdiplus::Rect r;
            RECT rectClient;
            ::GetClientRect(hwnd, &rectClient);
            r.X = 0;
            r.Y = 0;
            r.Width = ::width(rectClient);
            r.Height = ::height(rectClient);

            graphics.DrawImage(m_pgdiplusimage, r, 0, 0, 
               m_pgdiplusimage->GetWidth(),
               m_pgdiplusimage->GetHeight(), Gdiplus::UnitPixel);

         }

         ::EndPaint(hwnd, &ps);

         lresult = 0;

         return true;

      }

      return ::innate_ui_win32::window::on_window_procedure(lresult, message, wparam, lparam);

   }

   
   void still::layout()
   {

      defer_set_scaled_font();

      auto hwnd = ::as_HWND(m_windowswindow.as_operating_system_window());

      // 1. Get the current DPI for the specific window (Windows 10 1607+)
      // For older versions, use GetDeviceCaps(hdc, LOGPIXELSX)
      UINT dpi = ca2_window_dpi(hwnd);
      if (dpi == 0)
         dpi = 96; // Fallback to default
      wstring wstr;

      // 2. Get the text from the control
      ::i32 len = GetWindowTextLength(hwnd);
      if (len > 0)
      {

         auto buffer = wstr.get_buffer(len);
         GetWindowText(hwnd, buffer, len + 1);
         wstr.release_buffer();
      }

            if (wstr.is_empty())
      {

         wstr = L"THOMÁSØ";
      }


      // 3. Prepare the Device Context
      HDC hdc = GetDC(hwnd);
      HFONT hFont = (HFONT)SendMessage(hwnd, WM_GETFONT, 0, 0);
      HFONT hOldFont = (HFONT)SelectObject(hdc, hFont);

      // 4. Calculate dimensions
      // We use a large initial width to simulate single-line or set a specific
      // max width if you want word-wrapping.
      RECT rect = {0, 0, 10000, 0};
      DrawText(hdc, wstr.c_str(), -1, &rect, DT_CALCRECT | DT_LEFT | DT_NOPREFIX);

      // 5. Account for Control Borders (DPI Scaled)
      // If the static has WS_BORDER or SS_SUNKEN, add scaled padding.
      ::i32 padding = MulDiv(2, dpi, 96); // Add 2 pixels of padding scaled to DPI
      ::i32 newWidth = (rect.right - rect.left) + padding;
      ::i32 newHeight = (rect.bottom - rect.top) + padding;

      // 6. Cleanup and Apply
      SelectObject(hdc, hOldFont);
      ReleaseDC(hwnd, hdc);
      //delete[] buffer;

      //SetWindowPos(hStatic, NULL, 0, 0, newWidth, newHeight, SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE);

      m_iLayoutWidth = newWidth;
      m_iLayoutHeight = newHeight;
   }

} // namespace innate_ui
