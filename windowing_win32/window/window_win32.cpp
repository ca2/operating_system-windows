#include "framework.h"
#include "acme/constant/message.h"
#include "acme/constant/message_prototype.h"
#include "acme/constant/timer.h"
#include "acme/exception/exception.h"
#include "acme/filesystem/filesystem/directory_context.h"
#include "aura/message/timer.h"
#include "aura/message/user.h"
#include "aura/user/user/system.h"
#include "aura/user/user/user.h"
#include "aura/platform/session.h"
#include "aura/platform/system.h"
//#include "aura_windows/interaction_impl.h"
#include "windowing_win32/window.h"
#include "windowing_win32/windowing.h"


CLASS_DECL_ACME void acme_set_main_hwnd(HWND hwnd);
CLASS_DECL_ACME HWND acme_get_main_hwnd();


//CLASS_DECL_WINDOWING_WIN32 WNDPROC windows_user_interaction_impl_get_window_procedure();





// https://stackoverflow.com/questions/15966642/how-do-you-tell-lshift-apart-from-rshift-in-wm-keydown-happenings

wparam MapLeftRightKeys(wparam vk, lparam lParam)
{

   wparam new_vk = vk;

   unsigned int scancode = (lParam & 0x00ff0000) >> 16;

   int extended = (lParam & 0x01000000) != 0;

   switch (vk)
   {
   case VK_SHIFT:
      new_vk = MapVirtualKey(scancode, MAPVK_VSC_TO_VK_EX);
      break;
   case VK_CONTROL:
      new_vk = extended ? VK_RCONTROL : VK_LCONTROL;
      break;
   case VK_MENU:
      new_vk = extended ? VK_RMENU : VK_LMENU;
      break;
   default:
      // not a key we map from matter to left/right specialized
      //  just return it.
      new_vk = vk;
      break;
   }
   return new_vk;
}



bool is_registered_windows_message(unsigned int message)
{

   return message >= 0xc000 && message <= 0xffff;

}


//lresult CALLBACK WndProc(HWND hwnd, unsigned int message, wparam wparam, lparam lparam);
//
//
//int g_iCol = 0;
//
//
//LRESULT CALLBACK __window_procedure(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
//{
//
//   if (message == WM_SYSCOMMAND)
//   {
//
//      informationf("WM_SYSCOMMAND");
//
//   }
//   else if (message == WM_LBUTTONUP)
//   {
//
//      informationf("WM_LBUTTONUP");
//
//   }
//   else if (message == WM_NCDESTROY)
//   {
//
//      informationf("WM_NCDESTROY");
//
//   }
//   else if (message == WM_COMMAND)
//   {
//
//      informationf("WM_COMMAND");
//
//   }
//   else if (message == WM_MOUSEMOVE)
//   {
//
//      //informationf("WM_MOUSEMOVE");
//
//   }
//   else if (message == WM_NCMOUSEMOVE)
//   {
//
//      informationf("WM_NCMOUSEMOVE");
//
//   }
//   else if (message == WM_KILLFOCUS)
//   {
//
//      informationf("WM_KILLFOCUS");
//
//   }
//   else if (message == WM_MOUSEWHEEL)
//   {
//
//      informationf("WM_MOUSEWHEEL");
//
//   }
//   else if (message == WM_SHOWWINDOW)
//   {
//
//      if (wparam)
//      {
//
//         if(!acme_get_main_hwnd() || !::IsWindow(acme_get_main_hwnd()))
//         {
//
//            acme_set_main_hwnd(hwnd);
//
//         }
//
//      }
//
//   }
//
//   if (message == WM_APP + 12345)
//   {
//
//      ::procedure p;
//
//      p.m_pbase.m_p = (decltype(p.m_pbase.m_p)) lparam;
//
//      p();
//
//      return 0;
//
//   }
//
//   ::windowing_win32::window * pwindow = (::windowing_win32::window *) ::GetWindowLongPtr(hwnd, 0);
//
//   if (!pwindow)
//   {
//
//      if (message == WM_NCCREATE)
//      {
//
//         LPCREATESTRUCTW pcreatestructw = (LPCREATESTRUCTW)lparam;
//
//         ::user::system * psystem = (::user::system *)pcreatestructw->lpCreateParams;
//
//         pwindow = psystem->m_pwindow.cast < ::windowing_win32::window >();
//
//         if (!pwindow)
//         {
//
//            return ::DefWindowProcW(hwnd, message, wparam, lparam);
//
//         }
//
//         ::SetLastError(0);
//
//         auto lResult = ::SetWindowLongPtr(hwnd, 0, (LONG_PTR)pwindow);
//
//         if (lResult == 0)
//         {
//
//            auto dwResult = ::GetLastError();
//
//            if (dwResult)
//            {
//
//               pwindow->informationf("__window_procedure SetWindowLongPtr Failed");
//
//            }
//
//         }
//
//         pwindow->set_oswindow(as_oswindow(hwnd));
//
//         pwindow->set_os_data(hwnd);
//
//         auto pwin32windowing = pwindow->win32_windowing();
//
//         critical_section_lock synchronouslock(&pwin32windowing->m_criticalsection);
//
//         pwin32windowing->m_windowmap[hwnd] = pwindow;
//
//         //pwindow->m_pimpl2->m_hwnd = hwnd;
//
//      }
//      else
//      {
//
//         return ::DefWindowProcW(hwnd, message, wparam, lparam);
//
//      }
//
//   }
//
//   auto lresult = pwindow->__window_procedure(hwnd, message, wparam, lparam);
//
//   return lresult;
//
//}


namespace windowing_win32
{


   //void window::default_set(::message::message * pmessage, ::enum_message emessage, ::wparam wparam, ::lparam lparam)
   //{
   //
   //
   //
   //}


} // namespace windowing_win32




//CLASS_DECL_WINDOWING_WIN32 bool hook_window_create(::windowing_win32::window * pwindow)
//{
//
//   if (pwindow == nullptr)
//   {
//
//      return false;
//
//   }
//
//   if (pwindow->get_hwnd() != nullptr)
//   {
//
//      return false;
//
//   }
//
//   if (t_hHookOldCbtFilter == nullptr)
//   {
//
//      t_hHookOldCbtFilter = ::SetWindowsHookExW(WH_CBT, windows::__cbt_filter_hook, nullptr, ::GetCurrentThreadId());
//
//      if (t_hHookOldCbtFilter == nullptr)
//      {
//
//         return false;
//
//      }
//
//   }
//
//   if (t_hHookOldCbtFilter == nullptr)
//   {
//
//      return false;
//
//   }
//
//   thread_set("wnd_init") = pwindow;
//
//   if (thread_set("wnd_init") == nullptr)   // hook not already in progress
//   {
//
//      return false;
//
//   }
//
//   if (thread_set("wnd_init") != pwindow)
//   {
//
//      return false;
//
//   }
//
//   return true;
//
//}
//
//
//CLASS_DECL_WINDOWING_WIN32 bool unhook_window_create()
//{
//
//   if (thread_set("wnd_init") != nullptr)
//   {
//
//      thread_set("wnd_init") = nullptr;
//
//      return false;   // was not successfully hooked
//
//   }
//
//   return true;
//
//}
//

//void CLASS_DECL_WINDOWING_WIN32 _handle_activate(::windowing::window * pwindow, wparam nState, ::windowing::window * pWndOther)
//{
//
//   ASSERT(pwindow);
//
//   // send WM_ACTIVATETOPLEVEL when top-level parents change
//   if (!(pwindow->get_style() & WS_CHILD))
//   {
//
//      ::pointer<::user::interaction>pTopLevel = pwindow->get_top_level();
//
//      if (pTopLevel && (!pWndOther || !::IsWindow((pWndOther)->get_hwnd()) || pTopLevel != (pWndOther)->get_top_level()))
//      {
//         // lParam points to window getting the e_message_activate message and
//         //  oswindow_Other from the e_message_activate.
//         hwnd oswindow_2[2];
//         oswindow_2[0] = (pwindow)->get_hwnd();
//         if (!pWndOther)
//         {
//            oswindow_2[1] = nullptr;
//         }
//         else
//         {
//
//            oswindow_2[1] = (pWndOther)->get_hwnd();
//
//         }
//
//         // send it...
//         pTopLevel->send_message(WM_ACTIVATETOPLEVEL, nState, (lparam)&oswindow_2[0]);
//
//      }
//
//   }
//
//}


void __term_windowing()
{

   //if (t_hHookOldCbtFilter != nullptr)
   //{

   //   ::UnhookWindowsHookEx(t_hHookOldCbtFilter);

   //   t_hHookOldCbtFilter = nullptr;

   //}

}


//bool windowing::_windows_register_class(WNDCLASSEXW * puserinteractionclass);


namespace windowing_win32
{


   wstring windowing::_windows_calc_icon_window_class(::user::interaction * puserinteraction, unsigned int dwDefaultStyle, const ::string & pszMatter)
   {

      auto papplication = application();

      ::file::path pathFolder(pszMatter);

      ::file::path pathIcon;

      pathIcon = pathFolder / "icon.ico";

      string strPath = directory()->matter(pathIcon);

      HICON hIcon = (HICON) ::LoadImageW(nullptr, wstring(papplication->get_matter_path(strPath)), IMAGE_ICON, 256, 256, LR_LOADFROMFILE);

      wstring strClass = _windows_get_user_interaction_window_class(puserinteraction);

      if (hIcon != nullptr)
      {

         auto psystem = system();

         // will fill pszClassName with default WNDCLASS name

         // ignore instance handle from pre_create_window.

         WNDCLASSEXW wndcls;

         if (strClass.length() > 0 && GetClassInfoExW((HINSTANCE)psystem->m_hinstanceThis, strClass, &wndcls) && wndcls.hIcon != hIcon)
         {

            // register a very similar WNDCLASS

            return _windows_register_window_class(wndcls.style, strClass, wndcls.hCursor, wndcls.hbrBackground, hIcon);

         }

      }

      return strClass;

   }




   wstring windowing::_windows_get_user_interaction_window_class(::user::interaction * puserinteraction)
   {

      ::user::enum_window_type ewindowtype = puserinteraction->get_window_type();

      ::wstring wstrClassName = puserinteraction->payload("class_name").as_string();

      WNDCLASSEXW wndcls;

      memory_set(&wndcls, 0, sizeof(WNDCLASSEXW));   // start with nullptr defaults

      wndcls.lpfnWndProc = &windows::window_procedure;

      wndcls.hInstance = ::windows::get_window_procedure_hinstance();

      wndcls.cbWndExtra = wndcls.cbClsExtra = 40;

      if (ewindowtype == ::user::e_window_type_frame
         || ewindowtype == ::user::e_window_type_impact)
      {

         wndcls.style = CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW | CS_OWNDC;

         wndcls.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);

         if (wstrClassName.is_empty())
         {

            wstrClassName = "ca2_frame";

         }

         if (_windows_register_with_icon(&wndcls, wstrClassName, 0))
         {

            return wndcls.lpszClassName;

         }

      }

      HBRUSH hbrushBackground = nullptr;

      if (m_papplication->m_gpu.m_bUseSwapChainWindow)
      {

         hbrushBackground = (HBRUSH)CreateSolidBrush(0x00000000);

      }

      return _windows_register_window_class(0, wstrClassName, nullptr, hbrushBackground);

   }

   bool windowing::_windows_register_with_icon(WNDCLASSEXW * puserinteractionclass, const unichar * pszClassName, unsigned int nIDIcon)
   {

      puserinteractionclass->lpszClassName = pszClassName;

      puserinteractionclass->hIcon = ::LoadIconW(nullptr, MAKEINTRESOURCEW(32512));

      return _windows_register_class(puserinteractionclass);

   }


   //CLASS_DECL_WINDOWING_WIN32 WNDPROC get_window_procedure();


   wstring windowing::_windows_register_window_class(unsigned int nClassStyle, const WCHAR * pwszClassName, HCURSOR hCursor, HBRUSH hbrBackground, HICON hIcon)
   {

      //auto papp = pobject->get_application();

      const int iLen = 4096;

      wstring wstrClassName;

#ifdef CUBE

      HINSTANCE hinstance = ::GetModuleHandleW(nullptr);

#else 

      HINSTANCE hinstance = ::GetModuleHandleW(L"windowing_win32.dll");

#endif

      if (pwszClassName && *pwszClassName)
      {

         wstrClassName = pwszClassName;

      }
      else
      {

         LPWSTR lpwsz = wstrClassName.get_buffer(iLen);

         if (hCursor == nullptr && hbrBackground == nullptr && hIcon == nullptr)
         {

            _snwprintf_s(lpwsz, iLen, iLen - 1, L"windows_interaction_impl:%p,%x", hinstance, nClassStyle);

         }
         else
         {

            _snwprintf_s(lpwsz, iLen, iLen - 1, L"windows_interaction_impl:%p,%x,%p,%p,%p", hinstance, nClassStyle, hCursor, hbrBackground, hIcon);

         }

         wstrClassName.release_buffer();

      }

      // see if the class already exists
      WNDCLASSEXW wndcls = {};

      if (::GetClassInfoExW((HINSTANCE)hinstance, wstrClassName, &wndcls))
      {
         // already registered, assert everything is good
         ASSERT(wndcls.style == nClassStyle);

         // NOTE: We have to trust that the hIcon, hbrBackground, and the
         //  hCursor are semantically the same, because sometimes Windows does
         //  some internal translation or copying of those handles before
         //  storing them in the internal WNDCLASS retrieved by GetClassInfo.
         return wstrClassName;

      }
      wndcls.cbSize = sizeof(wndcls);
      // otherwise we need to register a ___new class
      wndcls.style = nClassStyle;
      wndcls.lpfnWndProc = &::windows::window_procedure;
      auto hinstanceWindowProcedure = ::windows::get_window_procedure_hinstance();
      wndcls.cbClsExtra = wndcls.cbWndExtra = 40;
      wndcls.hInstance = hinstanceWindowProcedure;
      //wndcls.hIcon = hIcon;
      //wndcls.hCursor = hCursor;
      wndcls.hCursor = nullptr;
      wndcls.hbrBackground = hbrBackground;
      wndcls.lpszMenuName = nullptr;

      wndcls.lpszClassName = wstrClassName;

      if (!_windows_register_class(&wndcls))
      {

         throw ::exception(error_resource);

      }

      // return thread-local pointer
      return wstrClassName;

   }



}//namespace windowing_win32


lresult CALLBACK WndProc(HWND hWnd, ::enum_message emessage, ::wparam wparam, ::lparam lparam);

//bool windows_register_class(HINSTANCE hinstance)
//{
//   
//   WNDCLASSEXW wcex = {};
//
//   wcex.cbSize = sizeof(WNDCLASSEXW);
//   wcex.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
//   wcex.lpfnWndProc = windows_user_interaction_impl_get_window_procedure();
//   wcex.cbClsExtra = 0;
//   wcex.cbWndExtra = 0;
//   wcex.hInstance = hinstance;
//   wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW);
//   wcex.lpszClassName = L"windows_interaction_impl";
//
//   if (!RegisterClassExW(&wcex))
//   {
//
//      return false;
//
//   }
//
//   return true;
//
//}
//


namespace windowing_win32
{


   bool windowing::_windows_register_class(WNDCLASSEXW * puserinteractionclass)
   {

      WNDCLASSEXW wndcls{};

      ::SetLastError(0);

      if (GetClassInfoExW(puserinteractionclass->hInstance, puserinteractionclass->lpszClassName, &wndcls))
      {

         return true;

      }

      auto dwLastError = ::GetLastError();

      if (dwLastError == ERROR_CLASS_DOES_NOT_EXIST)
      {

         ::SetLastError(0);

      }
      else
      {

         output_debug_string("GetClassInfoExW failed with error number '" + ::as_string(dwLastError) + "'");

      }

      puserinteractionclass->cbSize = sizeof(WNDCLASSEXW);

      if (!::RegisterClassExW(puserinteractionclass))
      {

         unsigned int dw = GetLastError();

         return false;

      }

      unsigned int dw = GetLastError();

      bool bRet = true;

      return bRet;

   }


} // namespace windowing_win32



//CLASS_DECL_WINDOWING_WIN32 WNDPROC windows_user_interaction_impl_get_window_procedure()
//{
//
//   return &__window_procedure;
//
//}



