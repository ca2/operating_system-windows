// Created by camilo on 2024-09-12 22:45 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "innate_ui.h"
#include "window.h"
#include "acme/nano/nano.h"
#include "acme/platform/platform.h"
#include "acme/platform/application.h"
#include "acme/platform/system.h"
#include "acme/parallelization/manual_reset_happening.h"
#include "acme/prototype/geometry2d/size.h"
//#include "acme/operating_system/windows/nano/user/user.h"
#include "acme/user/user/mouse.h"
#include "acme/operating_system/windows/window.h"
#include "acme/operating_system/windows/windowing.h"
#include "acme_windowing_win32/activation_token.h"


namespace innate_ui_win32
{

   

   //const WCHAR * g_pszWindowClass = L"innate_ui_win32_window";

   window::window()
   {
      m_hwnd = nullptr;
      m_hmenuSystem = nullptr;
      m_iChildIdSeed = 1000;
   }


   window::~window()
   {

   }



   void window::set_text(const ::scoped_string & scopedstr)
   {

      ::wstring wstr(scopedstr);

      main_post([this, wstr]
      ()
         {

            ::SetWindowTextW(m_hwnd, wstr);

});

   }
   //
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//

   LONG_PTR window::_get_style()
   {

      return ::GetWindowLongPtr(m_hwnd, GWL_STYLE);

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

      auto hinstanceWndProc = ::windows::get_window_procedure_hinstance();

      wndclassex.hInstance = (HINSTANCE)hinstanceWndProc;
      wndclassex.lpfnWndProc = &::windows::window_procedure;
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

      m_hwnd = CreateWindowW(_get_class_name(), L"", WS_OVERLAPPEDWINDOW,
          CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, (HINSTANCE) ::platform::get()->m_hinstanceThis,
          nullptr);

      if (m_hwnd)
      {

         system()->innate_ui()->add_top_level_window(this);

      }

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

            //innate_ui()->m_windowmap[m_hwnd] = this;


      });

      if (!m_hwnd)
      {
         
         throw ::exception(error_failed);

      }



   }
   int window::_get_id()
   {

      return GetWindowLong(m_hwnd, GWL_ID);

   }

   ::pointer < window > window::_get_child_with_id(int iId)
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


   bool window::on_window_procedure(LRESULT & lresult, UINT message, WPARAM wparam, LPARAM lparam)
   {

      if (::windows::window::on_window_procedure(lresult, message, wparam, lparam))
      {

         return true;

      }

      lresult = _window_procedure(message, wparam, lparam);

      return true;

   }


   LRESULT window::_window_procedure(UINT message, WPARAM wparam, LPARAM lparam)
   {

      LRESULT lresult = 0;

      switch (message)

      {
      case WM_SHOWWINDOW:
      {
         if (wparam)
         {
            if (!m_hmenuSystem)
            {
               //auto hmenu = GetSystemMenu(m_hwnd, true);
               m_hmenuSystem = GetSystemMenu(m_hwnd, false);
               WPARAM wparamHere = (WPARAM) m_hmenuSystem;
               LRESULT lresultHere = 1;
               if (_on_default_system_menu_init_menu(lresultHere, wparamHere))
               {

                  return lresult;

               }

            }
         }

      }
      break;
      case WM_APP + 124:
         PostQuitMessage(0);
         break;
      case WM_SYSCOMMAND:
      {
         int wmId = LOWORD(wparam);
         if (wmId == 123)
         {
            application()->show_about_box(system()->acme_windowing()->get_user_activation_token());
            return 0;
         }
         return DefWindowProc(m_hwnd, message, wparam, lparam);
      }
         break;
      case WM_COMMAND:
      {
         int wmId = LOWORD(wparam);
         if (wmId == 123)
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
         return DefWindowProc(m_hwnd, message, wparam, lparam);
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
         return DefWindowProc(m_hwnd, message, wparam, lparam);
      }
      break;
      case WM_CLOSE:
         destroy_window();
         break;
      case WM_DESTROY:
         //PostQuitMessage(0);
      default:
         return DefWindowProc(m_hwnd, message, wparam, lparam);
      }
      return lresult;


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
            pwindowImpl->m_iChildIdSeed++;
            ::SetWindowLong(m_hwnd, GWL_ID, pwindowImpl->m_iChildIdSeed);


      });

      if (!m_hwnd)
      {
         throw ::exception(error_failed);
      }



   }


   void window::destroy_window()
   {

      if (::IsWindow(m_hwnd))
      {

         for (auto pchild : m_childa)
         {

            pchild->destroy_window();

         }

         m_childa.clear();

         if (!::GetParent(m_hwnd))
         {

            innate_ui()->m_windowa.erase(this);

         }

         ::DestroyWindow(m_hwnd);

         ::cast < ::windows::windowing > pwindowing = system()->acme_windowing();
         
         pwindowing->m_windowmap[(::oswindow) m_hwnd].release();

         m_hwnd = nullptr;

      }

   }


   void window::show()
   {

      main_post([this]()
         {

            ShowWindow(m_hwnd, SW_SHOW);
            UpdateWindow(m_hwnd);


      });



   }


   void window::show_front(::user::activation_token * puseractivationtokenParameter)
   {

      auto puseractivationtoken = ::as_pointer(puseractivationtokenParameter);

      
      main_post([this, puseractivationtoken]()
        {

          ShowWindow(m_hwnd, SW_SHOW);
          UpdateWindow(m_hwnd);

          ::cast < ::win32::acme::windowing::activation_token> pwin32activationtoken = puseractivationtoken;

          if (pwin32activationtoken)
          {

             if (pwin32activationtoken->m_ptaskForeground)
             {

                pwin32activationtoken->m_ptaskForeground->_post([this]()
                   {

                         ::SetForegroundWindow(m_hwnd);

                      });


             }


          }
     });


   }

   void window::hide()
   {

   }


   void window::set_position(const ::int_point & pointParam)
   {

      auto point = pointParam;

      main_send([this, point]()
         {

            auto p = point;

            if (p.x < 0 || p.y < 0)
            {
               auto hwndParent  = GetParent(m_hwnd);
               RECT rParentClient;
               GetClientRect(hwndParent, &rParentClient);
               RECT rThis;
               GetClientRect(m_hwnd, &rParentClient);
               if (p.x < 0)
               {
                  p.x += ::width(rParentClient) - ::width(rThis);
               }

               if (p.y < 0)
               {
                  p.y += ::height(rParentClient) - ::height(rThis);
               }
            }

            ::SetWindowPos(m_hwnd, nullptr, p.x, p.y, 0, 0, SWP_NOSIZE);

         });

   }

   void window::set_size(const ::int_size & sizeParam)
   {

      auto size = sizeParam;

      main_send([this, size]()
         {

            ::SetWindowPos(m_hwnd, nullptr, 0, 0, size.cx, size.cy, SWP_NOMOVE);

            RECT rThis2;
            ::GetWindowRect(m_hwnd, &rThis2);


         });

   }


   void window::adjust_for_client_size(const ::int_size & sizeParam)
   {

      auto size = sizeParam;

      main_send([this, size]()
         {

            RECT r{};

            r.right = r.left + size.cx;
            r.bottom = r.top + size.cy;


            ::AdjustWindowRect(&r, (DWORD) _get_style(), FALSE);

            ::SetWindowPos(m_hwnd, nullptr, 0, 0, width(r), height(r), SWP_NOMOVE);

            RECT rThis2;
            ::GetWindowRect(m_hwnd, &rThis2);


         });

   }


   void window::center()
   {

      main_send([this]()
   {


      auto hwnd = ::GetParent(m_hwnd);

      if (hwnd == nullptr)
      {

         hwnd = ::GetDesktopWindow();

      }

      RECT r;

      ::GetWindowRect(hwnd, &r);
      RECT rThis;
      ::GetWindowRect(m_hwnd, &rThis);

      int wThis = rThis.right - rThis.left;
      int hThis = rThis.bottom - rThis.top;

      int x = ((r.right - r.left) - (wThis)) / 2;
      int y = ((r.bottom - r.top) - (hThis)) / 2;

      ::SetWindowPos(m_hwnd, nullptr, x, y, 0, 0, SWP_NOSIZE);

      RECT rThis2;
      ::GetWindowRect(m_hwnd, &rThis2);
         });


   }



   ::innate_ui_win32::innate_ui * window::innate_ui()
   {

      return dynamic_cast <::innate_ui_win32::innate_ui *> (::innate_ui::window::innate_ui());

   }

   
   void window::defer_show_system_menu(::user::mouse * pmouse)
   {

      //::pointer < ::windows::micro::user >pnanouserWindows = system()->acme_windowing();

      //pnanouserWindows->_defer_show_system_menu(m_hwnd, &m_hmenuSystem, pointAbsolute);

      _defer_show_system_menu(pmouse);

   }

} // namespace innate_ui


// WindowsProject1.cpp : Defines the entry point for the application.
//

//#include "framework.h"
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
//BOOL                InitInstance(HINSTANCE, int);
//INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
//
//int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
//                     _In_opt_ HINSTANCE hPrevInstance,
//                     _In_ LPWSTR    lpCmdLine,
//                     _In_ int       nCmdShow)
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
//   return (int)msg.wParam;
//}
//


//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
//BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
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
//      int wmId = LOWORD(wParam);
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
