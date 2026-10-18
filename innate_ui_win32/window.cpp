// Created by camilo on 2024-09-12 22:45 <3ThomasBorregaardSorensen!!
#include "platform.h"
#include "dpi_compat.h"
#include "innate_ui.h"
#include "window.h"
#include "acme/nano/nano.h"
#include "acme/platform/application.h"
#include "acme/platform/platform_platform.h"
#include "acme/platform/system.h"
#include "acme/parallelization/manual_reset_happening.h"
#include "acme/prototype/geometry2d/size.h"
//#include "acme/operating_system/windows/nano/user/user.h"
#include "acme/user/user/mouse.h"
#include "acme/operating_system/windows/window.h"
#include "acme/operating_system/windows/dark_popup_menu.h"
#include "acme/operating_system/windows/windowing.h"
#include "acme_windowing_win32/activation_token.h"


#include <commctrl.h>
#pragma comment(lib, "Comctl32.lib")

namespace
{
   bool innate_dark_mode()
   {
#if defined(__REACTOS__)
      return false;
#else
      HIGHCONTRASTW contrast{sizeof(contrast)};
      if (!SystemParametersInfoW(SPI_GETHIGHCONTRAST, sizeof(contrast), &contrast, 0)
         || (contrast.dwFlags & HCF_HIGHCONTRASTON))
         return false;

      HKEY key = nullptr;
      if (RegOpenKeyExW(HKEY_CURRENT_USER,
         L"Software\\Microsoft\\Windows\\CurrentVersion\\Themes\\Personalize",
         0, KEY_QUERY_VALUE, &key) != ERROR_SUCCESS)
         return false;
      DWORD value = 1, type = 0, size = sizeof(value);
      const auto status = RegQueryValueExW(key, L"AppsUseLightTheme", nullptr,
         &type, reinterpret_cast<BYTE *>(&value), &size);
      RegCloseKey(key);
      return status == ERROR_SUCCESS && type == REG_DWORD
         && size == sizeof(value) && value == 0;
#endif
   }

   void innate_dark_title_bar(HWND hwnd, bool dark)
   {
#if !defined(__REACTOS__)
      using set_attribute = HRESULT (WINAPI *)(HWND, DWORD, LPCVOID, DWORD);
      // Retain the optional module for the lifetime of its cached function pointer.
      static const auto setAttribute = []() -> set_attribute
      {
         WCHAR path[MAX_PATH];
         const auto length = GetSystemDirectoryW(path, MAX_PATH);
         if (!length || length + 12 >= MAX_PATH)
            return nullptr;
         lstrcatW(path, L"\\dwmapi.dll");
         const auto module = LoadLibraryW(path);
         return module ? reinterpret_cast<set_attribute>(
            GetProcAddress(module, "DwmSetWindowAttribute")) : nullptr;
      }();
      if (setAttribute)
      {
         const BOOL enabled = dark;
         // Unsupported systems retain their native title bar.
         setAttribute(hwnd, 20, &enabled, sizeof(enabled));
      }
#endif
   }
}


HFONT CreateScaledFont(HWND hWnd, ::i32 pointSize, ::i32 weight, const wchar_t *fontFamily)
{
   // 1. Get the current DPI for the window
   UINT dpi = ca2_window_dpi(hWnd);
   if (dpi == 0)
      dpi = 96;

   // 2. Convert point size to logical height (scaled for DPI)
   // Formula: Height = -MulDiv(PointSize, DPI, 72)
   ::i32 height = -MulDiv(pointSize, dpi, 72);

   // 3. Create the font
   return CreateFont(height, // Height (DPI scaled)
                     0, 0, 0, // Width, Escapement, Orientation
                     weight, // Font Weight (e.g., FW_BOLD, FW_NORMAL)
                     FALSE, FALSE, FALSE, // Italic, Underline, Strikeout
                     DEFAULT_CHARSET, // Character Set
                     OUT_DEFAULT_PRECIS, // Output Precision
                     CLIP_DEFAULT_PRECIS, // Clipping Precision
                     DEFAULT_QUALITY, // Quality
                     DEFAULT_PITCH | FF_DONTCARE, // Pitch and Family
                     fontFamily // Typeface Name (e.g., L"Segoe UI", L"Arial")
   );
}


namespace innate_ui_win32
{

   

   //const WCHAR * g_pszWindowClass = L"innate_ui_win32_window";

   window::window()
   {
      m_hmenuSystem = nullptr;
      m_iChildIdSeed = 1000;
   }


   window::~window()
   {
      if (m_hbrushDarkBackground)
         ::DeleteObject(m_hbrushDarkBackground);
   }

   void window::refresh_theme()
   {
      apply_theme(innate_dark_mode());
   }

   void window::apply_theme(bool bDarkMode)
   {
      auto hwnd = ::as_HWND(this->operating_system_window());
      if (!::IsWindow(hwnd))
         return;
      if (bDarkMode && !m_hbrushDarkBackground)
         m_hbrushDarkBackground = ::CreateSolidBrush(RGB(32, 32, 32));
      m_bDarkMode = bDarkMode && m_hbrushDarkBackground;
      if (!(::GetWindowLongPtrW(hwnd, GWL_STYLE) & WS_CHILD))
         innate_dark_title_bar(hwnd, m_bDarkMode);
      for (auto & pchild : m_childa)
      {
         ::pointer<window> pwindow = pchild;
         if (pwindow)
            pwindow->apply_theme(m_bDarkMode);
      }
      ::RedrawWindow(hwnd, nullptr, nullptr, RDW_INVALIDATE | RDW_ERASE | RDW_FRAME | RDW_ALLCHILDREN);
   }



   void window::set_text(const ::scoped_string & scopedstr)
   {

      ::wstring wstr(scopedstr);

      main_send([this, wstr]
      ()
         {

            auto hwnd = ::as_HWND(this->operating_system_window());

            ::SetWindowTextW(hwnd, wstr);

});

   }
   //
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//

   LONG_PTR window::_get_style()
   {

      auto hwnd =(HWND)  _HWND();

      return ::GetWindowLongPtr(hwnd, GWL_STYLE);

   }

   const_char_pointer window::__get_class_name()
   {

      return typeid(*this).name();

   }


   wstring window::_get_class_name()
   {

      return __get_class_name();

   }


   ATOM window::_register_class()
   {

      auto pszClassName = __get_class_name();

      auto & atom = innate_ui()->m_classmap[pszClassName];

      if (atom)
      {

         return atom;

      }

      WNDCLASSEXW wcex;

      wcex.cbSize = sizeof(WNDCLASSEX);
      wstring wstrClassName(pszClassName);
      wcex.lpszClassName = wstrClassName;


      _get_class(wcex);

      atom = RegisterClassExW(&wcex);

      return atom;

   }


   void window::_get_class(WNDCLASSEXW & wndclassex)
   {

      auto hinstanceWndProc = ::windows::window::s_window_procedure_hinstance();

      wndclassex.hInstance = (HINSTANCE)hinstanceWndProc;
      wndclassex.lpfnWndProc = &::windows::window::s_window_procedure;
      wndclassex.style = CS_HREDRAW | CS_VREDRAW;
      //wndclassex.lpfnWndProc = WndProc;
      wndclassex.cbClsExtra = 0;
      wndclassex.cbWndExtra = 0;
      //wndclassex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINDOWSPROJECT1));
      wndclassex.hIcon = nullptr;
      wndclassex.hCursor = LoadCursor(nullptr, IDC_ARROW);
      wndclassex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
      //wndclassex.lpszMenuName = MAKEINTRESOURCEW(IDC_WINDOWSPROJECT1);
      wndclassex.lpszMenuName = nullptr;
      //wndclassex.hIconSm = LoadIcon(wndclassex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
      wndclassex.hIconSm = nullptr;

   }


   void window::_create()
   {

      HWND hwndResult =
         CreateWindowW(_get_class_name(), L"", WS_OVERLAPPEDWINDOW,
          CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, (HINSTANCE) ::platform::get()->m_hinstanceThis,
          nullptr);

      if (!hwndResult || !_HWND() || hwndResult != _HWND())
      {

         throw ::exception(error_failed);

      }

      system()->innate_ui()->add_top_level_window(this);

   }


   void window::_create_child(window * pwindow)
   {


   }


   void window::create()
   {

      main_send([this]()
      {

            _register_class();
            
            _create();

            //innate_ui()->m_windowmap[hwnd] = this;


      });

      if (!_HWND())
      {

         throw ::exception(error_failed);

      }

   }


   ::i32 window::_get_id()
   {

      auto hwnd = ::as_HWND(this->operating_system_window());

      return GetWindowLong(hwnd, GWL_ID);

   }


   ::pointer < window > window::_get_child_with_id(::i32 iId)
   {

      for (auto & pchild : m_childa)
      {

         ::pointer < window > pwindow = pchild;

         if (pwindow)
         {

            if (pwindow->_get_id() == iId)
            {

               return pwindow;
            }

         }

      }

      return {};

   }


   bool window::on_window_procedure(::lresult & lresult, unsigned message, ::wparam wparam, ::lparam lparam)
   {

      if (::windows::window::on_window_procedure(lresult, message, wparam, lparam))
      {

         return true;

      }

   //    lresult = _window_procedure(message, wparam, lparam);
   //
   //    return true;
   //
   // }
   //
   //
   // LRESULT window::_window_procedure(UINT message, WPARAM wparam, LPARAM lparam)
   // {
   //
   //    LRESULT lresult = 0;

      switch (message)

      {
      case WM_SHOWWINDOW:
      {
         if (wparam)
            refresh_theme();
      }
      break;
      case WM_SETTINGCHANGE:
      case WM_THEMECHANGED:
      case WM_SYSCOLORCHANGE:
         // Broadcasts reach each top-level dialog on its owning UI thread.
         refresh_theme();
         break;
      case WM_ERASEBKGND:
         if (m_bDarkMode)
         {
            RECT rectangle;
            ::GetClientRect((HWND)_HWND(), &rectangle);
            ::FillRect((HDC)(WPARAM)wparam, &rectangle, m_hbrushDarkBackground);
            lresult = 1;
            return true;
         }
         break;
      case WM_CTLCOLORSTATIC:
      case WM_CTLCOLORBTN:
         if (m_bDarkMode)
         {
            auto hdc = (HDC)(WPARAM)wparam;
            ::SetTextColor(hdc, RGB(240, 240, 240));
            ::SetBkColor(hdc, RGB(32, 32, 32));
            lresult = (LRESULT)m_hbrushDarkBackground;
            return true;
         }
         break;
      case WM_APP + 124:
      {
         PostQuitMessage(0);
         break;
      }
         case WM_SIZE:
      {

         on_size();

      }
            break;
      case WM_SYSCOMMAND:
      {
         ::i32 wmId = LOWORD(wparam);
         if ((wmId & 0xfff0) == SC_MOUSEMENU || (wmId & 0xfff0) == SC_KEYMENU)
         {
            auto hwnd = ::as_HWND(this->operating_system_window());
            ::windows::dark_popup_menu menuTheme(hwnd, ::GetSystemMenu(hwnd, FALSE));
            lresult = ::DefWindowProcW(hwnd, message, wparam, lparam);
            return true;
         }
         if (wmId == ID_SHOW_ABOUT_BOX)
         {
            application()->show_about_box(system()->acme_windowing()->get_user_activation_token());
            return 0;
         }
         
         auto hwnd = ::as_HWND(this->operating_system_window());

         lresult = DefWindowProc(hwnd, message, wparam, lparam);

         return true;
      }
         break;
      case WM_COMMAND:
      {
         ::i32 wmId = LOWORD(wparam);
         if (wmId == ID_SHOW_ABOUT_BOX)
         {
            application()->show_about_box(system()->acme_windowing()->get_user_activation_token());
            return 0;
         }
         auto pchild = _get_child_with_id(wmId);

         if (pchild)
         {

            if (pchild->_on_command())
            {

               return 0;

            }

         }
         //// Parse the menu selections:
         //switch (wmId)
         //{
         //   //case IDM_ABOUT:
         //     // DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
         //      //break;
         //case 123:
         //   DestroyWindow(hWnd);
         //   break;
         //default:

         auto hwnd = ::as_HWND(this->operating_system_window());

         lresult = DefWindowProc(hwnd, message, wparam, lparam);
         return true;
         //}
      }
      break;
      case WM_INITMENU:
      {

      }
         break;
      case WM_PAINT:
      {
         //PAINTSTRUCT ps;
         //HDC hdc = BeginPaint(hWnd, &ps);
         //// TODO: Add any drawing code that uses hdc here...
         //EndPaint(hWnd, &ps);

         auto hwnd = ::as_HWND(this->operating_system_window());
         lresult = DefWindowProc(hwnd, message, wparam, lparam);
         return true;
      }
      break;
      case WM_CLOSE:
         destroy_window();
         break;
      case WM_DESTROY:
         //PostQuitMessage(0);
      default:
      {
         //auto hwnd = ::as_HWND(this->operating_system_window());

         //return DefWindowProc(hwnd, message, wparam, lparam);
      }
      }
      //return lresult;
return false;

   }


   bool window::_on_command()
   {

      return false;

   }


   void window::create_child(::innate_ui::window * pwindow)
   {

      ::pointer< window > pwindowImpl = pwindow;

      main_send([this, pwindowImpl]()
         {

            _create_child(pwindowImpl);

            pwindowImpl->m_childa.add(this);
            apply_theme(pwindowImpl->m_bDarkMode);
            pwindowImpl->m_iChildIdSeed++;

            auto hwnd = ::as_HWND(this->operating_system_window());

            ::SetWindowLong(hwnd, GWL_ID, pwindowImpl->m_iChildIdSeed);


      });

      if (!_HWND())
      {

         throw ::exception(error_failed);

      }

   }


   void window::destroy_window()
   {

      auto hwnd =(HWND)  _HWND();

      if (::IsWindow(hwnd))
      {

         for (auto pchild : m_childa)
         {

            pchild->destroy_window();

         }

         m_childa.clear();

         if (!::GetParent(hwnd))
         {

            innate_ui()->m_windowa.erase(this);

         }

         ::DestroyWindow(hwnd);

         ::cast < ::windows::windowing > pwindowing = system()->acme_windowing();
         
         pwindowing->m_windowmap[hwnd].release();

         hwnd = nullptr;

      }

   }


   void window::show()
   {

      main_post([this]()
      {

         auto hwnd = ::as_HWND(this->operating_system_window());

         ShowWindow(hwnd, SW_SHOW);
      
         UpdateWindow(hwnd);

      });

   }


   void window::show_front(::user::activation_token * puseractivationtokenParameter)
   {

      auto puseractivationtoken = ::as_pointer(puseractivationtokenParameter);

      main_post(
         [this, puseractivationtoken]()
      {

         auto hwnd = ::as_HWND(this->operating_system_window());

#if defined(__REACTOS__)
         information() << "ABOUT_NATIVE ShowWindow begin";
#endif
         ShowWindow(hwnd, SW_SHOW);
#if defined(__REACTOS__)
         information() << "ABOUT_NATIVE ShowWindow returned; UpdateWindow begin";
#endif
         
         UpdateWindow(hwnd);
#if defined(__REACTOS__)
         information() << "ABOUT_NATIVE UpdateWindow returned";
#endif

#if defined(__REACTOS__)
         // A second modeless dialog can remain behind the About dialog on XP.
         // Raise and activate it here on its native UI thread; posting this to
         // another input thread can deadlock with layered presentation.
         const BOOL raised = ::SetWindowPos(hwnd, HWND_TOP, 0, 0, 0, 0,
            SWP_NOMOVE | SWP_NOSIZE);
         const BOOL activated = ::SetForegroundWindow(hwnd);
         RECT rectangle{};
         const BOOL hasRectangle = ::GetWindowRect(hwnd, &rectangle);
         informationf("ABOUT_NATIVE shown hwnd=%p visible=%d ownerThread=%lu currentThread=%lu foreground=%p rectangleValid=%d rectangle=(%ld,%ld)-(%ld,%ld) raised=%d activated=%d; native-thread foreground request",
            hwnd, (int)::IsWindowVisible(hwnd),
            (unsigned long)::GetWindowThreadProcessId(hwnd, nullptr),
            (unsigned long)::GetCurrentThreadId(), ::GetForegroundWindow(),
            (int)hasRectangle, rectangle.left, rectangle.top, rectangle.right, rectangle.bottom,
            (int)raised, (int)activated);
#else
          ::cast < ::win32::acme::windowing::activation_token> pwin32activationtoken = puseractivationtoken;

          if (pwin32activationtoken)
          {

             auto ptaskForeground = pwin32activationtoken->m_ptaskForeground;

             if (ptaskForeground)
             {

                ptaskForeground->post([this]()
                {
                      
                  auto hwnd = ::as_HWND(this->operating_system_window());

                  ::SetForegroundWindow(hwnd);

                });

             }


          }
#endif
     });


   }

   void window::hide()
   {

   }


   void window::set_position(const ::i32_point & pointParam)
   {

      auto point = pointParam;

      main_send([this, point]()
         {

            auto p = point;

            if (p.x < 0 || p.y < 0)
            {

               auto hwnd = ::as_HWND(this->operating_system_window());

               auto hwndParent  = GetParent(hwnd);
               RECT rParentClient;
               GetClientRect(hwndParent, &rParentClient);
               RECT rThis;
               GetClientRect(hwnd, &rParentClient);
               if (p.x < 0)
               {
                  p.x += ::width(rParentClient) - ::width(rThis);
               }

               if (p.y < 0)
               {
                  p.y += ::height(rParentClient) - ::height(rThis);
               }
            }

            auto hwnd = ::as_HWND(this->operating_system_window());

            ::SetWindowPos(hwnd, nullptr, p.x, p.y, 0, 0, SWP_NOSIZE);

         });

   }

   void window::set_size(const ::i32_size & sizeParam)
   {

      auto size = sizeParam;

      main_send([this, size]()
         {

            auto hwnd = ::as_HWND(this->operating_system_window());

            ::SetWindowPos(hwnd, nullptr, 0, 0, size.cx, size.cy, SWP_NOMOVE);

            RECT rThis2;
            ::GetWindowRect(hwnd, &rThis2);


         });

   }


   void window::adjust_for_client_size(const ::i32_size & sizeParam)
   {

      auto size = sizeParam;

      main_send([this, size]()
         {

            RECT r{};

            r.right = r.left + size.cx;
            r.bottom = r.top + size.cy;


            ::AdjustWindowRect(&r, (DWORD) _get_style(), FALSE);

            auto hwnd = ::as_HWND(this->operating_system_window());

            ::SetWindowPos(hwnd, nullptr, 0, 0, width(r), height(r), SWP_NOMOVE);

            RECT rThis2;
            ::GetWindowRect(hwnd, &rThis2);


         });

   }


   void window::center()
   {

      main_send([this]()
   {

            auto hwnd = ::as_HWND(this->operating_system_window());

      auto hwndParent = ::GetParent(hwnd);

      if (hwndParent == nullptr)
      {

         hwndParent = ::GetDesktopWindow();

      }

      RECT r;

      ::GetWindowRect(hwndParent, &r);
      RECT rThis;
      ::GetWindowRect(hwnd, &rThis);

      ::i32 wThis = rThis.right - rThis.left;
      ::i32 hThis = rThis.bottom - rThis.top;

      ::i32 x = ((r.right - r.left) - (wThis)) / 2;
      ::i32 y = ((r.bottom - r.top) - (hThis)) / 2;

      ::SetWindowPos(hwnd, nullptr, x, y, 0, 0, SWP_NOSIZE);

      RECT rThis2;
      ::GetWindowRect(hwnd, &rThis2);
         });


   }



   ::innate_ui_win32::innate_ui * window::innate_ui()
   {

      return dynamic_cast <::innate_ui_win32::innate_ui *> (::innate_ui::window::innate_ui());

   }


   ::operating_system::window window::operating_system_window() const
   {

      return m_windowswindow.as_operating_system_window();

   }

   
   void window::defer_show_system_menu(::user::mouse * pmouse)
   {

      //::pointer < ::windows::micro::user >pnanouserWindows = system()->acme_windowing();

      //pnanouserWindows->_defer_show_system_menu(hwnd, &m_hmenuSystem, pointAbsolute);

      _defer_show_system_menu(pmouse);

   }


   HWND window::_create_subclassed_window(DWORD dwExStyle, LPCWSTR lpClassName, LPCWSTR lpWindowName, DWORD dwStyle,
                                          ::i32 x, ::i32 y, ::i32 cx, ::i32 cy, HWND hwndParent, HMENU hmenu,
                                          HINSTANCE hinstance, LPVOID lpParam)
   {

      auto hwnd = CreateWindowExW(dwExStyle, lpClassName, lpWindowName, dwStyle, x, y, cx, cy, hwndParent, hmenu,
                                  (HINSTANCE)hinstance, lpParam);

      m_windowswindow = hwnd;

      SetWindowSubclass(hwnd, _static_subclass_procedure,
                        1, // Subclass ID
                        (DWORD_PTR) (void*)(innate_ui_win32::window * ) this); // Optional reference data

      return hwnd;

   }


   LRESULT CALLBACK window::_static_subclass_procedure(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam,
                                                       UINT_PTR uIdSubclass,
                                       DWORD_PTR dwRefData)
   {

      auto p = (innate_ui_win32::window *)dwRefData;

      ::lresult lresult;
      
      if (p->_subclass_procedure(lresult, msg, wParam, lParam))
      {

         return lresult;

      }

      switch (msg)
      {
         case WM_NCDESTROY:
            RemoveWindowSubclass(hwnd, _static_subclass_procedure, uIdSubclass);
            break;
         default:
            break;
      }

      return DefSubclassProc(hwnd, msg, wParam, lParam);

   }


   bool window::_subclass_procedure(::lresult & lresult, ::u32 message, ::wparam wparam, ::lparam lparam)
   {

      switch (message)
      {
         case WM_PAINT:
            // Do custom drawing here if desired
            break;
         default:
            break;

      }

      return false;

   }


   void window::defer_set_scaled_font()
   {


      auto hwnd = ::as_HWND(m_windowswindow.as_operating_system_window());

      // Create a bold, 12pt Segoe UI font scaled for the current monitor
      HFONT hNewFont = CreateScaledFont(hwnd, (::i32) ( 12 * m_dFontSizeEm), m_iFontWeight, L"Segoe UI");

      // Send the WM_SETFONT message to the control
      // wParam: Handle to the new font
      // lParam: TRUE to redraw the control immediately
      SendMessage(hwnd, WM_SETFONT, (WPARAM)hNewFont, TRUE);


   }



} // namespace innate_ui


// WindowsProject1.cpp : Defines the entry point for the application.
//

//#include "platform.h"
//#include "WindowsProject1.h"
//
//#define MAX_LOADSTRING 100
//
//// Global Variables:
//HINSTANCE hInst;                                // current instance
//WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
//WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name
//
//// Forward declarations of functions included in this code module:
//ATOM                MyRegisterClass(HINSTANCE hInstance);
//BOOL                InitInstance(HINSTANCE, ::i32);
//INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
//
//::i32 APIENTRY wWinMain(_In_ HINSTANCE hInstance,
//                     _In_opt_ HINSTANCE hPrevInstance,
//                     _In_ LPWSTR    lpCmdLine,
//                     _In_ ::i32       nCmdShow)
//{
//   UNREFERENCED_PARAMETER(hPrevInstance);
//   UNREFERENCED_PARAMETER(lpCmdLine);
//
//   //// TODO: Place code here.
//
//   //// Initialize global strings
//   //LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
//   //LoadStringW(hInstance, IDC_WINDOWSPROJECT1, szWindowClass, MAX_LOADSTRING);
//   //MyRegisterClass(hInstance);
//
//   // Perform application initialization:
//   if (!InitInstance(hInstance, nCmdShow))
//   {
//      return FALSE;
//   }
//
//   //HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINDOWSPROJECT1));
//
//   //MSG msg;
//
//
//   return (::i32)msg.wParam;
//}
//


//
//   FUNCTION: InitInstance(HINSTANCE, ::i32)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
//BOOL InitInstance(HINSTANCE hInstance, ::i32 nCmdShow)
//{
//
//   return TRUE;
//}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
//LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
//{
//   switch (message)
//   {
//   case WM_COMMAND:
//   {
//      ::i32 wmId = LOWORD(wParam);
//      // Parse the menu selections:
//      switch (wmId)
//      {
//      case IDM_ABOUT:
//         DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
//         break;
//      case IDM_EXIT:
//         DestroyWindow(hWnd);
//         break;
//      default:
//         return DefWindowProc(hWnd, message, wParam, lParam);
//      }
//   }
//   break;
//   case WM_PAINT:
//   {
//      PAINTSTRUCT ps;
//      HDC hdc = BeginPaint(hWnd, &ps);
//      // TODO: Add any drawing code that uses hdc here...
//      EndPaint(hWnd, &ps);
//   }
//   break;
//   case WM_DESTROY:
//      PostQuitMessage(0);
//      break;
//   default:
//      return DefWindowProc(hWnd, message, wParam, lParam);
//   }
//   return 0;
//}
//
//// Message handler for about box.
//INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
//{
//   UNREFERENCED_PARAMETER(lParam);
//   switch (message)
//   {
//   case WM_INITDIALOG:
//      return (INT_PTR)TRUE;
//
//   case WM_COMMAND:
//      if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
//      {
//         EndDialog(hDlg, LOWORD(wParam));
//         return (INT_PTR)TRUE;
//      }
//      break;
//   }
//   return (INT_PTR)FALSE;
//}
//
