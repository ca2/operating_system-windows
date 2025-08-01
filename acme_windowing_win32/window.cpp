// Created by camilo on 2022-01-21 05:05 PM <3ThomasBorregaardSorensen
#include "framework.h"
#include "acme/nano/graphics/device.h"
#include "window.h"
//#include "user.h"
#include "acme/parallelization/task.h"
#include "acme/parallelization/task.h"
//#include "acme/nano/nano.h"
//#include "acme/nano/user/button.h"
//#include "acme/nano/user/message_box.h"
#include "acme/platform/system.h"
#include "acme/user/micro/elemental.h"
#include "acme/user/user/frame_interaction.h"
#include "acme/user/user/interaction.h"
#include "acme/user/user/mouse.h"
#include "acme/windowing/windowing.h"
#include "acme/operating_system/windows/windows.h"


void win32_post(HWND hwnd, const ::procedure& procedure)
{

   auto p = procedure.m_pbase.m_p;

   p->increment_reference_count();

   PostMessage(hwnd, WM_APP+ 876, 0, (LPARAM) p);

}


void win32_send(HWND hwnd, const ::procedure& procedure)
{

   auto p = procedure.m_pbase.m_p;

   p->increment_reference_count();

   SendMessage(hwnd, WM_APP + 876, 0, (LPARAM)p);

}

CLASS_DECL_ACME bool _c_simple_message_loop_step();

CLASS_DECL_ACME string task_get_name();
CLASS_DECL_ACME void task_set_name(const ::scoped_string & scopedstrName);


class CLASS_DECL_ACME scoped_task_name
{
public:

   ::string       m_strTask;

   scoped_task_name(const ::scoped_string & scopedstrTask)
   {

      m_strTask = ::task_get_name();

      ::task_set_name(scopedstrTask);

   }


   ~scoped_task_name()
   {

      ::task_set_name(m_strTask);

   }


};


namespace win32
{


   namespace acme
   {


      namespace windowing
      {


         window::window()
         {

            
            m_bSizeMoveMode = false;
            //      m_bDestroy = false;
            m_hwnd = nullptr;
            m_hmenuSystem = nullptr;
            m_bNcActive = false;
         }


         window::~window()
         {

            //delete_drawing_objects();

         }


         bool g_bNanoWindowClassRegistered = false;



         //CLASS_DECL_ACME_WINDOWING_WIN32 LRESULT CALLBACK acme_window_procedure(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);


#define ACME_WINDOW_CLASS "acme_window_class"





         void register_nano_window_class()
         {

            if (g_bNanoWindowClassRegistered)
            {

               return;

            }

            auto hinstanceWndProc = ::windows::get_window_procedure_hinstance();

            WNDCLASSEX wndclassex{};

            //Step 1: Registering the Window Class
            wndclassex.cbSize = sizeof(WNDCLASSEX);
            wndclassex.style = CS_DBLCLKS;
            wndclassex.lpfnWndProc = &windows::window_procedure;
            wndclassex.cbClsExtra = 0;
            wndclassex.cbWndExtra = 0;
            wndclassex.hInstance = hinstanceWndProc;
            wndclassex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
            wndclassex.hCursor = LoadCursor(NULL, IDC_ARROW);
            wndclassex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
            wndclassex.lpszMenuName = NULL;
            wndclassex.lpszClassName = _T(ACME_WINDOW_CLASS);
            wndclassex.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

            if (!RegisterClassEx(&wndclassex))
            {

               throw ::exception(error_failed, "Failed to register nano message box window class.");

            }

            g_bNanoWindowClassRegistered = true;

         }




         void window::create_window()
         {

            _create_window();

         }


         void window::_create_window()
         {


            if (!g_bNanoWindowClassRegistered)
            {

               register_nano_window_class();

            }

            wstring wstrTitle(m_pacmeuserinteraction->get_title());

            auto hinstanceWndProc = ::windows::get_window_procedure_hinstance();

            m_ptask = ::get_task();

            auto r = m_pacmeuserinteraction->get_rectangle();

            ::cast < ::acme::user::frame_interaction > pframeinteraction = m_pacmeuserinteraction;

            DWORD dwExStyle = 0;

            if (pframeinteraction && pframeinteraction->m_bTopMost)
            {

               dwExStyle |= WS_EX_TOPMOST;

            }

            HWND hwnd = CreateWindowEx(
               dwExStyle,
               _T(ACME_WINDOW_CLASS),
               wstrTitle,
               WS_POPUP | WS_SYSMENU,
               r.left(),
               r.top(),
               r.width(),
               r.height(),
               NULL, NULL, hinstanceWndProc,
               (::windows::window *)this);

            if (hwnd == NULL)
            {
               throw ::exception(error_failed, "Failed to create nano message box window.");
               return;
            }

            //nanowindowimplementationa().add(this);

            //system()->window_

         }


         void window::destroy_window()
         {

            main_send()
               << [this]()
               {

                  if (!::DestroyWindow(m_hwnd))
                  {

                     informationf("window::destroy_window Failed to destroy window");

                  }
                  else
                  {

                     informationf("window::destroy_window Window destroyed!!");

                  }

               };

            destroy();

         }


         //void window::on_char(int iChar)
         //{

         //   m_pacmeuserinteraction->on_char(iChar);

         //}


         void window::_draw(HDC hdc)
         {

            ::int_rectangle r;

            GetWindowRect(m_hwnd, (LPRECT)&r);

            HGDIOBJ hbrushOld = ::GetCurrentObject(hdc, OBJ_BRUSH);
            HGDIOBJ hfontOld = ::GetCurrentObject(hdc, OBJ_FONT);
            HGDIOBJ hpenOld = ::GetCurrentObject(hdc, OBJ_PEN);

            {

               //nano()->graphics();

               __øconstruct(m_pnanodevice);

               m_pnanodevice->attach(hdc, { ::width(r), ::height(r) });

               ::pointer < ::micro::elemental > pelemental;

               pelemental = m_pacmeuserinteraction;

               if (pelemental)
               {

                  pelemental->draw_background(m_pnanodevice);

                  pelemental->draw_foreground(m_pnanodevice);

               }

            }

            ::SelectObject(hdc, hpenOld);
            ::SelectObject(hdc, hfontOld);
            ::SelectObject(hdc, hbrushOld);

         }


         //bool window::is_active()
         //{

         //   return m_pm_bNcActive;

         //}


         //void window::draw_children(HDC hdc)
         //{

         //   for (auto & pchild: m_childa)
         //   {

         //      pchild->on_draw(hdc);

         //   }

         //}

         //void window::delete_drawing_objects()
         //{

         //   //if (m_hbrushWindow)
         //   //{

         //   //   ::DeleteObject(m_hbrushWindow);

         //   //   m_hbrushWindow = nullptr;

         //   //}

         //   //if (m_hpenBorder)
         //   //{

         //   //   ::DeleteObject(m_hpenBorder);

         //   //   m_hpenBorder = nullptr;

         //   //}


         //   //if (m_hpenBorderFocus)
         //   //{

         //   //   ::DeleteObject(m_hpenBorderFocus);

         //   //   m_hpenBorderFocus = nullptr;

         //   //}

         //   m_pacmeuserinteraction->delete_drawing_objects();

         //}


         //bool window::get_dark_mode()
         //{

         //   return !_is_light_theme();

         //}


         //void window::create_drawing_objects()
         //{

         //   //if (m_hfont == nullptr)
         //   //{

         //   //   HDC hdc = ::GetDC(m_hwnd);
         //   //   int nHeight = -MulDiv(14, GetDeviceCaps(hdc, LOGPIXELSY), 72);
         //   //   m_hfont = ::CreateFontW(nHeight, 0, 0, 0, FW_NORMAL, 0, 0, 0, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
         //   //                           CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, FF_SWISS, L"Segoe UI");
         //   //   ::ReleaseDC(m_hwnd, hdc);

         //   //}

         //   //bool bDarkMode = get_dark_mode();

         //   //if (bDarkMode)
         //   //{

         //   //   m_crWindow = RGB(0, 0, 0);
         //   //   m_crText = RGB(255, 255, 255);
         //   //   m_crFocus = RGB(2, 128, 255);

         //   //} else
         //   //{

         //   //   m_crWindow = RGB(255, 255, 255);
         //   //   m_crText = RGB(0, 0, 0);
         //   //   m_crFocus = RGB(1, 64, 128);

         //   //}

         //   //m_hbrushWindow = CreateSolidBrush(m_crWindow);
         //   //m_hpenBorder = CreatePen(PS_SOLID, 1, m_crText);
         //   //m_hpenBorderFocus = CreatePen(PS_SOLID, 1, m_crFocus);

         //   m_pacmeuserinteraction->create_drawing_objects();

         //}

         //void window::update_drawing_objects()
         //{

         //   delete_drawing_objects();
         //   create_drawing_objects();


         //}


         //::atom window::hit_test(int x, int y)
         //{
         //
         //   for (int i = 0; i < m_iButtonCount; i++)
         //   {
         //      if (m_buttona[i].m_rectangle.contains(int_point(x, y)))
         //      {
         //
         //         return m_buttona[i].m_edialogresult;
         //
         //      }
         //
         //   }
         //
         //   return e_dialog_result_none;
         //
         //}
         //

         //void window::on_left_button_down(::user::mouse* pmouse)
         //{

         //   //SetCapture(m_hwnd);

         //   //m_atomLeftButtonDown = hit_test(x, y);

         //   //if (m_pdragmove && m_atomLeftButtonDown == e_dialog_result_none)
         //   //{

         //   //   m_pdragmove->m_bLButtonDown = true;

         //   //   m_pdragmove->m_bDrag = false;

         //   //   int_point pointCursor(x, y);

         //   //   pointCursor += m_rectangle.origin();

         //   //   m_pdragmove->m_pointLButtonDown = pointCursor;

         //   //   m_pdragmove->m_sizeLButtonDownOffset = m_pdragmove->m_pointLButtonDown - m_rectangle.origin();

         //   //   return;

         //   //}

         //   m_pacmeuserinteraction->on_left_button_down(pmouse);

         //}


         //void window::on_left_button_up(::user::mouse* pmouse)
         //{

         //   //ReleaseCapture();

         //   //if (m_pdragmove && (m_pdragmove->m_bLButtonDown || m_pdragmove->m_bDrag))
         //   //{

         //   //   m_pdragmove->m_bLButtonDown = false;

         //   //   m_pdragmove->m_bDrag = false;

         //   //   return;

         //   //}

         //   //m_atomLeftButtonUp = hit_test(x, y);

         //   //if (m_atomLeftButtonUp == m_atomLeftButtonDown && m_atomLeftButtonUp != e_dialog_result_none)
         //   //{

         //   //   m_atomResult = m_atomLeftButtonUp;

         //   //   on_click(m_atomResult);

         //   //}

         //   m_pacmeuserinteraction->on_left_button_up(pmouse);

         //}

         //void window::on_mouse_move(::user::mouse* pmouse)
         //{

         //   //if (m_pdragmove && m_pdragmove->m_bLButtonDown)
         //   //{

         //   //   ::SetCursor(::LoadCursor(NULL, IDC_SIZEALL));

         //   //   if (!m_pdragmove->m_bDrag)
         //   //   {

         //   //      m_pdragmove->m_bDrag = true;

         //   //      int_point pointCursor(x, y);

         //   //      pointCursor += m_rectangle.origin();

         //   //      auto point = pointCursor - m_pdragmove->m_sizeLButtonDownOffset;

         //   //      move_to(pmouse);

         //   //      m_pdragmove->m_bDrag = false;

         //   //   }

         //   //   return;

         //   //}

         //   m_pacmeuserinteraction->on_mouse_move(pmouse);

         //}


         //void window::on_right_button_down(::user::mouse* pmouse)
         //{

         //   //SetCapture(m_hwnd);

         //   //m_atomLeftButtonDown = hit_test(x, y);

         //   //if (m_pdragmove && m_atomLeftButtonDown == e_dialog_result_none)
         //   //{

         //   //   m_pdragmove->m_bLButtonDown = true;

         //   //   m_pdragmove->m_bDrag = false;

         //   //   int_point pointCursor(x, y);

         //   //   pointCursor += m_rectangle.origin();

         //   //   m_pdragmove->m_pointLButtonDown = pointCursor;

         //   //   m_pdragmove->m_sizeLButtonDownOffset = m_pdragmove->m_pointLButtonDown - m_rectangle.origin();

         //   //   return;

         //   //}

         //   m_pacmeuserinteraction->on_right_button_down(pmouse);

         //}


         //void window::on_right_button_up(::user::mouse* pmouse)
         //{

         //   //ReleaseCapture();

         //   //if (m_pdragmove && (m_pdragmove->m_bLButtonDown || m_pdragmove->m_bDrag))
         //   //{

         //   //   m_pdragmove->m_bLButtonDown = false;

         //   //   m_pdragmove->m_bDrag = false;

         //   //   return;

         //   //}

         //   //m_atomLeftButtonUp = hit_test(x, y);

         //   //if (m_atomLeftButtonUp == m_atomLeftButtonDown && m_atomLeftButtonUp != e_dialog_result_none)
         //   //{

         //   //   m_atomResult = m_atomLeftButtonUp;

         //   //   on_click(m_atomResult);

         //   //}

         //   m_pacmeuserinteraction->on_right_button_up(pmouse);

         //}



         //::payload window::get_result()
         //{

         //   return m_pacmeuserinteraction->get_result();

         //}




         //::micro::child * window::hit_test(const ::int_point & point, ::user::e_zorder ezorder)
         //{

         //   return m_pacmeuserinteraction->hit_test(point);

         //}


      //LRESULT CALLBACK ::micro::message_box::s_window_procedure(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
      //{
      //if (msg == WM_NCCREATE)
      //{
      //
      //   CREATESTRUCT * pcreatestruct = (CREATESTRUCT *)lParam;
      //   SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)pcreatestruct->lpCreateParams);
      //
      //}
      //::micro::message_box * pwindow = (::micro::message_box *)GetWindowLongPtr(hwnd, GWLP_USERDATA);
      //
      //if (!pwindow)
      //{
      //   return DefWindowProc(hwnd, msg, wParam, lParam);
      //}
      //return pwindow->window_procedure(msg, wParam, lParam);
      //
      //}


         ::oswindow window::oswindow()
         {

            return as_oswindow(m_hwnd);

         }

         bool window::_is_light_theme()
         {

            DWORD dwBuffer;

            DWORD dwSize = sizeof(dwBuffer);

            auto res = RegGetValueW(
               HKEY_CURRENT_USER,
               L"Software\\Microsoft\\Windows\\CurrentVersion\\Themes\\Personalize",
               L"AppsUseLightTheme",
               RRF_RT_REG_DWORD, // expected value type
               nullptr,
               &dwBuffer,
               &dwSize);

            if (res != ERROR_SUCCESS)
            {

               throw ::exception(error_failed);

            }

            return dwBuffer != FALSE;

         }


         bool window::on_window_procedure(LRESULT & lresult, UINT message, WPARAM wparam, LPARAM lparam)
         {

            if (::windows::window::on_window_procedure(lresult, message, wparam, lparam))
            {

               return true;

            }

            lresult = window_procedure(message, wparam, lparam);

            return true;

         }



         LRESULT window::window_procedure(unsigned int message, wparam wparam, lparam lparam)
         {

            //{

            //   LRESULT lresult = 0;

            //   if (on_window_procedure(lresult, message, wparam, lparam))
            //   {

            //      return lresult;

            //   }

            //}

            switch (message)
            {
            case WM_COMMAND:
            {
               /* ::pointer < ::windows::micro::user > pnanouser = system()->acme_windowing();

                LRESULT lresult = 0;

                if (pnanouser->_on_command(lresult, m_hwnd, wparam, lparam))
                {

                   return lresult;

                }*/

               return DefWindowProc(m_hwnd, message, wparam, lparam);

            }

            break;
            case WM_SYSCOMMAND:
            {

               return DefWindowProc(m_hwnd, message, wparam, lparam);

            }

            break;
            case WM_CLOSE:
            {
               //DestroyWindow(m_hwnd);

               ::cast < ::micro::elemental > pelemental = m_pacmeuserinteraction;

               if (pelemental)
               {

                  pelemental->on_click(e_dialog_result_cancel, nullptr);

               }

            }
            return 0;
            break;
            case WM_NCDESTROY:
               break;
               //case WM_INITMENU:
               //   {
               //   ::pointer < ::windows::micro::user > pnanouser = system()->acme_windowing();

               //   LRESULT lresult = 0;

               //   if (pnanouser->_on_default_system_menu_init_menu(lresult, m_hwnd, m_hmenuSystem, wparam))
               //   {

               //      return lresult;

               //   }

               //   }
               //   break;
            case WM_DESTROY:
               //PostQuitMessage(0);
               system()->acme_windowing()->m_windowa.erase(this);
               break;
            case WM_CREATE:
            {
               //update_drawing_objects();

               on_create_window();

            }
            break;
            case WM_CHAR:
            {

               ::cast < ::micro::elemental > pelemental = m_pacmeuserinteraction;

               if (pelemental)
               {

                  pelemental->on_char((int)wparam);

               }
               return 0;
            }
            break;
            case WM_LBUTTONDOWN:
            {

               auto pmouse = __create_new < ::user::mouse >();

               pmouse->m_pointHost = lparam;

               pmouse->m_pointAbsolute = client_to_screen(lparam);

               ::cast < ::micro::elemental > pelemental = m_pacmeuserinteraction;

               if (pelemental)
               {

                  pelemental->fore_on_left_button_down(pmouse);

               }

               if (!pmouse->m_bRet)
               {


                  if (pelemental)
                  {

                     pelemental->back_on_left_button_down(pmouse);

                  }

               }

            }
            break;
            case WM_MOUSELEAVE:
            {

               //::cast < ::micro::elemental > pelemental = m_pacmeuserinteraction;

               //if (pelemental)
               {

                 // pelemental->on_mouse_leave();

                  on_mouse_leave();

                  m_bMouseOn = false;

               }


            }
            break;
            case WM_NCMOUSEMOVE:
            {

               debug() << "WM_NCMOUSEMOVE";

            }
               break;
            case WM_MOUSEMOVE:
            {

               if (!m_bMouseOn)
               {

                  m_bMouseOn = true;

                  TRACKMOUSEEVENT trackmouseevent = { sizeof(TRACKMOUSEEVENT) };
                  trackmouseevent.dwFlags = TME_LEAVE;
                  trackmouseevent.hwndTrack = m_hwnd;
                  ::TrackMouseEvent(&trackmouseevent);

                  on_mouse_enter();

               }

               auto pmouse = __create_new < ::user::mouse >();

               pmouse->m_pointHost = lparam;

               pmouse->m_pointAbsolute = client_to_screen(lparam);

               fore_on_mouse_move(pmouse);

               //::cast < ::micro::elemental > pelemental = m_pacmeuserinteraction;

               //if (pelemental)
               //{

               //   pelemental->fore_on_mouse_move(pmouse);

               //}

               if (!pmouse->m_bRet)
               {


                  //if (pelemental)
                  //{

                     back_on_mouse_move(pmouse);

                  //}

               }


            }
            break;
            case WM_LBUTTONUP:
            {

               auto pmouse = __create_new < ::user::mouse >();

               pmouse->m_pointHost = lparam;

               pmouse->m_pointAbsolute = client_to_screen(lparam);

               ::cast < ::micro::elemental > pelemental = m_pacmeuserinteraction;

               if (pelemental)
               {

                  pelemental->fore_on_left_button_up(pmouse);

               }

               if (!pmouse->m_bRet)
               {


                  if (pelemental)
                  {

                     pelemental->back_on_left_button_up(pmouse);

                  }

               }


            }
            break;
            case WM_RBUTTONDOWN:
            {

               auto pmouse = __create_new < ::user::mouse >();

               pmouse->m_pointHost = lparam;

               pmouse->m_pointAbsolute = client_to_screen(lparam);

               ::cast < ::micro::elemental > pelemental = m_pacmeuserinteraction;

               if (pelemental)
               {

                  pelemental->fore_on_right_button_down(pmouse);

               }

               if (!pmouse->m_bRet)
               {


                  if (pelemental)
                  {

                     pelemental->back_on_right_button_down(pmouse);

                  }

               }


            }
            break;
            case WM_RBUTTONUP:
            {

               auto pmouse = __create_new < ::user::mouse >();

               pmouse->m_pointHost = lparam;

               pmouse->m_pointAbsolute = client_to_screen(lparam);

               ::cast < ::micro::elemental > pelemental = m_pacmeuserinteraction;

               if (pelemental)
               {

                  pelemental->fore_on_right_button_up(pmouse);

               }

               if (!pmouse->m_bRet)
               {


                  if (pelemental)
                  {

                     pelemental->back_on_right_button_up(pmouse);

                  }

               }


            }
            break;
            case WM_ERASEBKGND:
               return 1;
            case WM_MOUSEACTIVATE:
               return MA_ACTIVATE;
            case WM_PAINT:
            {

               PAINTSTRUCT paintstruct{};

               HDC hdcWindow = BeginPaint(m_hwnd, &paintstruct);

               HDC hdc = ::CreateCompatibleDC(hdcWindow);

               ::int_rectangle rectangleX;

               ::GetClientRect(m_hwnd, (LPRECT)&rectangleX);

               HBITMAP hbitmap = ::CreateCompatibleBitmap(hdcWindow, rectangleX.width(), rectangleX.height());

               HGDIOBJ hbitmapOld = ::SelectObject(hdc, hbitmap);

               _draw(hdc);


               ::BitBlt(hdcWindow, 0, 0, rectangleX.width(), rectangleX.height(),
                  hdc, 0, 0, SRCCOPY);

               hbitmapOld = ::SelectObject(hdc, hbitmapOld);

               ::DeleteDC(hdc);
               EndPaint(m_hwnd, &paintstruct);
            }
            break;
            case WM_NCACTIVATE:
            {
               LRESULT lresult = DefWindowProc(m_hwnd, message, wparam, lparam);
               m_bNcActive = wparam != 0;
               redraw();

               return lresult;

            }
            case WM_ACTIVATE:
            {

               if (wparam > 0)
               {

                  ::SetFocus(m_hwnd);

               }

               return 0;

            }
            case WM_FONTCHANGE:
            {

               redraw();

            }
            break;
            case WM_SETTINGCHANGE:
            {

               string strLparamString;

               if (wparam == 0)
               {

                  strLparamString = (const WCHAR *)(LPARAM(lparam));

               }

               if (strLparamString == "ImmersiveColorSet")
               {

                  //system()->acme_windowing()->fetch_dark_mode();

                  //update_drawing_objects();

                  //redraw();

               }
               else if (wparam == SPI_SETWORKAREA)
               {

                  redraw();

               }

            }
            break;

            default:
            {

               return DefWindowProc(m_hwnd, message, wparam, lparam);

            }

            }

            return 0;

         }

         //
         //
         //HINSTANCE nano_message_box_hinstance()
         //{
         //
         //   HINSTANCE hinstanceWndProc = (HINSTANCE) ::GetModuleHandleA("acme.dll");
         //
         //   if (hinstanceWndProc == nullptr)
         //   {
         //
         //      hinstanceWndProc = (HINSTANCE)::GetModuleHandleA(NULL);
         //
         //   }
         //
         //   return hinstanceWndProc;
         //
         //}

         //
         //void register_nano_window_class()
         //{
         //
         //   if (g_bNanoWindowClassRegistered)
         //   {
         //
         //      return;
         //
         //   }
         //
         //   auto hinstanceWndProc = nano_message_box_hinstance();
         //
         //   WNDCLASSEX wndclassex;
         //
         //   //Step 1: Registering the Window Class
         //   wndclassex.cbSize = sizeof(WNDCLASSEX);
         //   wndclassex.style = 0;
         //   wndclassex.lpfnWndProc = &message_box_window_procedure;
         //   wndclassex.cbClsExtra = 0;
         //   wndclassex.cbWndExtra = 0;
         //   wndclassex.hInstance = hinstanceWndProc;
         //   wndclassex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
         //   wndclassex.hCursor = LoadCursor(NULL, IDC_ARROW);
         //   wndclassex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
         //   wndclassex.lpszMenuName = NULL;
         //   wndclassex.lpszClassName = _T(NANO_MESSAGE_BOX_WINDOW_CLASS);
         //   wndclassex.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
         //
         //   if (!RegisterClassEx(&wndclassex))
         //   {
         //
         //      throw ::exception(error_failed, "Failed to register nano message box window class.");
         //
         //   }
         //
         //   g_bNanoWindowClassRegistered = true;
         //
         //}
         //

         void window::show_window()
         {

            main_send([this]()
               {

                  if (!::IsWindow(m_hwnd))
                  {

                     create_window();

                  }

                  DWORD dwPid;
                  HWND hwndForeground = ::GetForegroundWindow();
                  DWORD dwThread = GetWindowThreadProcessId(
                     hwndForeground,
                     &dwPid
                  );
                  auto dwCurrentPid = GetCurrentProcessId();
                  warning() << "dwThread = " << dwThread;
                  warning() << "hwndForeground = " << (iptr) hwndForeground;
                  warning() << "m_hwnd         = " << (iptr) m_hwnd;
                  warning() << "dwPid          = " << dwPid;
                  warning() << "dwCurrentPid   = " << dwCurrentPid;


                  if(dwThread && hwndForeground != m_hwnd && dwPid == dwCurrentPid)
                  { 

                     ::ShowWindow(m_hwnd, SW_SHOWNOACTIVATE);

                     warning() << "ShowWindow  SW_SHOWNOACTIVATE at thread " << ::GetCurrentThreadId();

                     win32_post(hwndForeground, [this]()
                        {

                           warning() << "Before SetForegroundWindow  At thread " << ::GetCurrentThreadId();

                           ::SetForegroundWindow(m_hwnd);

                           warning() << "SetForegroundWindow  At thread " << ::GetCurrentThreadId();

                           win32_post(m_hwnd, [this]()
                              {

                                 warning() << "SetActiveWindow  At thread " << ::GetCurrentThreadId();

                                 ::SetActiveWindow(m_hwnd);

                                 ::SetFocus(m_hwnd);

                                 ::UpdateWindow(m_hwnd);

                                 ::BringWindowToTop(m_hwnd);

                                 debug() << "Show window";

                              });

                        });


                  }
                  else
                  {
                     ::SetForegroundWindow(m_hwnd);

                     ::ShowWindow(m_hwnd, SW_SHOW);

                     ::UpdateWindow(m_hwnd);

                     ::BringWindowToTop(m_hwnd);
                  }


            });

         }


         void window::hide_window()
         {

            main_send([this]()
               {

                  if (::IsWindow(m_hwnd))
                  {

                     ::ShowWindow(m_hwnd, SW_HIDE);

                  }

            });

         }

         //void window::add_child(::micro::child* pchild)
         //{

         //   m_pacmeuserinteraction->add_child(pchild);

         //}


         void window::redraw()
         {

            ::RedrawWindow(m_hwnd, nullptr, nullptr, RDW_UPDATENOW | RDW_INVALIDATE);

         }


         bool window::_is_window()
         {

            return ::IsWindow(m_hwnd);

         }


         ::int_point window::client_to_screen(const ::int_point & point)
         {

            POINT p{ point.x(), point.y() };

            ::ClientToScreen(m_hwnd, &p);

            return { p.x, p.y };

         }


         //void window::_destroy_window()
         //{
         //
         //}


         void window::destroy()
         {

            ::acme::windowing::window::destroy();
            ::windows::window::destroy();
            //user_post([this]()
            //   {

            //      //::ShowWindow(m_hwnd, SW_HIDE);

            //      ::DestroyWindow(m_hwnd);

            //      system()->acme_windowing()->process_messages();

            //   });

         }


         //
         //LRESULT window::window_procedure(UINT message, WPARAM wparam, LPARAM lparam)
         //{
         //   switch (message)
         //   {
         //   case WM_CLOSE:
         //      DestroyWindow(m_hwnd);
         //      break;
         //   case WM_DESTROY:
         //      PostQuitMessage(0);
         //      break;
         //   case WM_CREATE:
         //   {
         //      update_drawing_objects();
         //   }
         //   break;
         //   case WM_LBUTTONDOWN:
         //      on_left_button_down(lparam_int_x(lparam), lparam_int_y(lparam));
         //      break;
         //   case WM_LBUTTONUP:
         //   {
         //      on_left_button_up(lparam_int_x(lparam), lparam_int_y(lparam));
         //   }
         //
         //   break;
         //   case WM_PAINT:
         //   {
         //      PAINTSTRUCT paintstruct{};
         //      HDC hdc = BeginPaint(m_hwnd, &paintstruct);
         //      draw(hdc);
         //      EndPaint(m_hwnd, &paintstruct);
         //   }
         //   break;
         //   default:
         //      return DefWindowProc(m_hwnd, message, wparam, lparam);
         //   }
         //   return 0;
         //}


         //void window::on_click(const ::payload& payloadParam, ::user::mouse* pmouse)
         //{

         //   auto payload = payloadParam;

         //   //fork([this, atom, pmouse]()
         //      //{

         //   m_pacmeuserinteraction->on_click(payload, pmouse);

         //   //}, { pmouse });

         //}


         //void window::on_right_click(const ::payload& payloadParam, ::user::mouse* pmouse)
         //{

         //   auto payload = payloadParam;

         //   //fork([this, atom, pmouse]()
         //     // {

         //   m_pacmeuserinteraction->on_right_click(payload, pmouse);

         //   //}, {pmouse});


         //}


         void window::set_position(const ::int_point & point)
         {

            auto pacmeuserinteractionOwner = owner_interaction();

            HWND hwndParent = nullptr;

            if (pacmeuserinteractionOwner)
            {

               ::cast < ::win32::acme::windowing::window > pwindowOwner = pacmeuserinteractionOwner->m_pacmewindowingwindow;

               hwndParent = pwindowOwner->m_hwnd;

            }

            ::cast < ::acme::user::frame_interaction > pframeinteraction = m_pacmeuserinteraction;

            DWORD dwFlags = SWP_NOSIZE;

            if (pframeinteraction && pframeinteraction->m_bTopMost)
            {

               hwndParent = HWND_TOPMOST;

            }
            else if (!hwndParent)
            {

               dwFlags |= SWP_NOZORDER;

            }

            ::SetWindowPos(m_hwnd, hwndParent, point.x(), point.y(), 0, 0, dwFlags);

         }


         //::int_point window::try_absolute_mouse_position(const ::int_point& point)
         //{

         //   return point;

         //}


         //::int_rectangle window::get_client_rectangle()
         //{

         //   ::int_rectangle rectangle;

         //   ::GetClientRect(m_hwnd, (LPRECT)&rectangle);

         //   return rectangle;

         //}


         int_rectangle window::get_window_rectangle()
         {

            ::int_rectangle rectangle;

            ::GetWindowRect(m_hwnd, (LPRECT)&rectangle);

            return rectangle;

         }


         //void window::set_mouse_capture()
         //{

         //   SetCapture(m_hwnd);

         //}


         //bool window::has_mouse_capture()
         //{

         //   return ::GetCapture() == m_hwnd;

         //}


         void window::release_mouse_capture()
         {

            ReleaseCapture();

         }


         void window::set_cursor(enum_cursor ecursor)
         {

            if (ecursor == e_cursor_move)
            {

               ::SetCursor(::LoadCursor(NULL, IDC_SIZEALL));

            }

         }






         void window::_user_post(const ::procedure & procedure)
         {

            if (m_ptask)
            {

               m_ptask->post(procedure);

            }
            else
            {

               ::acme::windowing::window::_user_post(procedure);

            }


         }


         void window::implementation_message_loop_step()
         {

            _c_simple_message_loop_step();

         }


         void window::defer_show_system_menu(::user::mouse * pmouse)
         {

            //::pointer < ::windows::micro::user > pnanouser = system()->acme_windowing();

            //pnanouser->_defer_show_system_menu(m_hwnd, &m_hmenuSystem, pointAbsolute);

            _defer_show_system_menu(pmouse);


         }


         void process_messages(bool bWait)
         {

            auto strThreadName = ::task_get_name();

            //auto pmessagebox = m_pacmeuserinteraction.cast < ::micro::message_box >();

            //::string strAbbreviation("window");

            //if (strType.contains("message_box"))
            //if (pmessagebox)
            //{
               //auto pmessagebox = m_pacmeuserinteraction.cast<nano::me
               /// @brief ////////123456789012345
               //strAbbreviation = "msgbx:" + pmessagebox->m_strMessage.left(20);

              // strAbbreviation = "msgbx:" + pmessagebox->m_strMessage;

            //}

            //scoped_task_name scopedtaskname(strAbbreviation);

            //::task_set_name("nanownd");

            MSG msg;

            while (bWait ? (::GetMessage(&msg, NULL, 0, 0) > 0) :
               (::PeekMessage(&msg, NULL, 0, 0, TRUE)))
            {

               TranslateMessage(&msg);

               DispatchMessage(&msg);

            }

         }


         void window::set_mouse_capture()
         {

            HWND hwnd = m_hwnd;

            HWND hwndPreviouslyCapturedIfAny = ::SetCapture(hwnd);

            HWND hwndGet = ::GetCapture();

            if (hwndGet != hwnd && hwndGet != nullptr)
            {

               //return ::error_failed;

               throw ::exception(error_failed);

            }

         }


         bool window::has_mouse_capture()
         {

            itask itask = get_itask();

            HWND hwndCapture = ::windows::get_mouse_capture(itask);

            HWND hwnd = m_hwnd;

            if (hwndCapture == hwnd)
            {

               return true;

            }

            return false;

         }


      } // namespace windowing


   } // namespace acme


} // namespace win32



