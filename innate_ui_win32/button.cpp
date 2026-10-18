// Created by camilo on 2024-09-13 01:00 <3ThomasBorregaardSorensen!!
#include "platform.h"
#include "button.h"
#include "icon.h"
#include "acme/_operating_system.h"
#include "dpi_compat.h"
#include <string>


namespace innate_ui_win32
{


   button::button()
   {
   }


   button::~button()
   {

   }

   void button::paint_dark_button(HDC hdc)
   {
      const auto hwnd = (HWND)_HWND();
      const auto saved = ::SaveDC(hdc);
      RECT rectangle;
      ::GetClientRect(hwnd, &rectangle);
      const auto state = ::SendMessageW(hwnd, BM_GETSTATE, 0, 0);
      const bool enabled = ::IsWindowEnabled(hwnd) != FALSE;
      const bool pressed = (state & BST_PUSHED) != 0;
      const bool focused = (state & BST_FOCUS) != 0;
      const int inset = maximum(1, ::MulDiv(2, ca2_window_dpi(hwnd), 96));
      const auto brush = (HBRUSH)::GetStockObject(DC_BRUSH);
      ::SetDCBrushColor(hdc, pressed ? RGB(48, 48, 48) : RGB(64, 64, 64));
      ::FillRect(hdc, &rectangle, brush);
      ::SetDCBrushColor(hdc, focused ? RGB(160, 190, 230) : RGB(120, 120, 120));
      ::FrameRect(hdc, &rectangle, brush);
      if ((::GetWindowLongPtrW(hwnd, GWL_STYLE) & BS_TYPEMASK) == BS_DEFPUSHBUTTON)
      {
         ::InflateRect(&rectangle, -1, -1);
         ::FrameRect(hdc, &rectangle, brush);
      }
      ::SetBkMode(hdc, TRANSPARENT);
      ::SetTextColor(hdc, enabled ? RGB(240, 240, 240) : RGB(150, 150, 150));
      auto font = (HFONT)::SendMessageW(hwnd, WM_GETFONT, 0, 0);
      if (font)
         ::SelectObject(hdc, font);
      const auto length = ::GetWindowTextLengthW(hwnd);
      std::wstring text(length + 1, L'\0');
      ::GetWindowTextW(hwnd, &text[0], length + 1);
      ::InflateRect(&rectangle, -inset, -inset);
      if (pressed)
         ::OffsetRect(&rectangle, 1, 1);
      const auto uiState = ::SendMessageW(hwnd, WM_QUERYUISTATE, 0, 0);
      const UINT flags = DT_CENTER | DT_VCENTER | DT_SINGLELINE
         | ((uiState & UISF_HIDEACCEL) ? DT_HIDEPREFIX : 0);
      ::DrawTextW(hdc, text.c_str(), length, &rectangle, flags);
      if (focused && !(uiState & UISF_HIDEFOCUS))
         ::DrawFocusRect(hdc, &rectangle);
      if (saved)
         ::RestoreDC(hdc, saved);
   }

   bool button::_subclass_procedure(::lresult & lresult, ::u32 message, ::wparam wparam, ::lparam lparam)
   {
      if (m_bDarkMode && (message == WM_PAINT || message == WM_PRINTCLIENT))
      {
         PAINTSTRUCT paint{};
         const auto hwnd = (HWND)_HWND();
         const auto hdc = message == WM_PAINT ? ::BeginPaint(hwnd, &paint) : (HDC)(WPARAM)wparam;
         if (hdc)
            paint_dark_button(hdc);
         if (message == WM_PAINT)
            ::EndPaint(hwnd, &paint);
         lresult = 0;
         return true;
      }
      return window::_subclass_procedure(lresult, message, wparam, lparam);
   }


   bool button::_on_command()
   {
      if (!m_callbackOnClick)
      {
         return false;

      }

         m_callbackOnClick();

         return true;
   }


   void button::_create_child(window * pwindowParent)
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
         L"BUTTON",  // Predefined class; Unicode assumed 
         L"",      // Button text 
         WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
         10,         // x position 
         10,         // y position 
         100,        // Button width
         100,        // Button height
         hwndParent, // Parent window
         NULL,       // No menu.
         hinstanceParent,
         NULL);

      if (!hwndResult || !_HWND() || hwndResult != _HWND())
      {

         throw ::exception(error_failed);

      }

      defer_set_scaled_font();

   }


   void button::set_icon(::innate_ui::icon * piconParam)
   {

      ::pointer <icon > picon = piconParam;

      main_send([this, picon]()
      {

         //::SendMessage(m_hwnd, BM_SETICON, (WPARAM) picon->m_hicon, 0);

         });

   }


} // namespace innate_ui
