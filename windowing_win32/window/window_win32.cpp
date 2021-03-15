#include "framework.h"
#include "acme/const/timer.h"

CLASS_DECL_WINDOWING_WIN32 WNDPROC windows_user_interaction_impl_get_window_procedure();



// https://stackoverflow.com/questions/15966642/how-do-you-tell-lshift-apart-from-rshift-in-wm-keydown-events

wparam MapLeftRightKeys(wparam vk, lparam lParam)
{

   wparam new_vk = vk;

   ::u32 scancode = (lParam & 0x00ff0000) >> 16;

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



bool is_registered_windows_message(::u32 message)
{

   return message >= 0xc000 && message <= 0xffff;

}


lresult CALLBACK WndProc(HWND hwnd, ::u32 message, wparam wparam, lparam lparam);


int g_iCol = 0;


LRESULT CALLBACK __window_procedure(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
{

   ::windowing::window * pwindow = (::windowing::window *) ::GetWindowLongPtr(hwnd, 0);

   if (!pwindow)
   {

      if (message == WM_NCCREATE)
      {

         LPCREATESTRUCTW pcreatestructw = (LPCREATESTRUCTW)lparam;

         ::user::system * psystem = (::user::system *)pcreatestructw->lpCreateParams;

         pwindow = psystem->m_pwindow;

         if (!pwindow)
         {

            return ::DefWindowProcW(hwnd, message, wparam, lparam);

         }

         ::SetWindowLongPtr(hwnd, 0, (LONG_PTR)pwindow);

         pwindow->set_oswindow(__oswindow(hwnd));

         auto pwindowing = pwindow->windowing()->cast < ::windowing_win32::windowing >();

         pwindowing->m_windowmap[hwnd] = pwindow;

      }
      else
      {

         return ::DefWindowProcW(hwnd, message, wparam, lparam);

      }

   }

   lresult lresult = 0;

   if (message == WM_KEYDOWN)
   {

      output_debug_string("WM_IME_CHAR(2)");

   }

   if (is_registered_windows_message(message))
   {

      lresult = ::DefWindowProcW(hwnd, message, wparam, lparam);

      return lresult;

   }

   auto pimpl = pwindow->m_pimpl;

   if (pimpl)
   {

      if (pimpl->__windows_message_bypass(pwindow, message, wparam, lparam, lresult))
      {

         return lresult;

      }

   }

   //return ::DefWindowProcW(hwnd, message, wparam, lparam);

   auto psystem = pimpl->get_system();

   pimpl->m_uiMessage = message;

   pimpl->m_wparam = wparam;

   pimpl->m_lparam = lparam;

   auto puserinteraction = pimpl->m_puserinteraction;

   if (message == e_message_activate)
   {

      output_debug_string("test");

   }

   if (message == e_message_left_button_up)
   {

      ::output_debug_string("e_message_left_button_up");

   }
   else if (message == 33815)
   {

      string strType = puserinteraction->type_name();

      if (strType.contains("combo_list"))
      {

         ::output_debug_string("combo_list");

      }

   }

   if (message == e_message_mouse_move)
   {

      if (lparam == pimpl->m_lparamLastMouseMove)
      {

         return 0;

      }

      pimpl->m_lparamLastMouseMove = lparam;

      ::point_i32 pointCursor;

      ::GetCursorPos((POINT *)&pointCursor);

      if (pimpl->m_pointCursor == pointCursor)
      {

         return 0;

      }

      pimpl->m_pointCursor = pointCursor;

   }
   else if (message == e_message_timer)
   {

      if (wparam == e_timer_transparent_mouse_event)
      {

         ::point_i32 pointCursor;

         ::GetCursorPos((POINT *)&pointCursor);

         if (pimpl->m_pointCursor == pointCursor)
         {

            return 0;

         }

         pimpl->m_pointCursor = pointCursor;

         ::lparam lparam;

         ::ScreenToClient(hwnd, (POINT *)&pointCursor);

         lparam = MAKELPARAM(pointCursor.x, pointCursor.y);

         pimpl->call_message_handler(e_message_mouse_move, 0, lparam);

      }
      else
      {

         // ignoring Timer Event

         output_debug_string("iTE\n");

      }

      return 0;

   }

   if (pimpl->m_bDestroyImplOnly || ::is_null(puserinteraction))
   {

      auto pmessage = pimpl->get_message((enum_message)message, wparam, lparam);

      try
      {

         pimpl->message_handler(pmessage);

      }
      catch (...)
      {

      }

      if (!pmessage->m_bRet)
      {

         pimpl->default_message_handler(pmessage);

      }

      lresult = pmessage->m_lresult;

   }
   else if (::is_set(puserinteraction))
   {

      if (message == WM_GETTEXT)
      {

         return ::DefWindowProcW(hwnd, message, wparam, lparam);

      }
      else if (message == WM_GETTEXTLENGTH)
      {

         return ::DefWindowProcW(hwnd, message, wparam, lparam);

      }
      else if (message == WM_SETTEXT)
      {

         return ::DefWindowProcW(hwnd, message, wparam, lparam);

      }

      auto pmessage = puserinteraction->get_message((enum_message)message, wparam, lparam);

      try
      {

         //puserinteraction->message_handler(pmessage);
         pwindow->message_handler(pmessage);

      }
      catch (...)
      {

      }

      if (!pmessage->m_bRet)
      {

         puserinteraction->default_message_handler(pmessage);

      }

      lresult = pmessage->m_lresult;

   }
   else
   {

      lresult = ::DefWindowProcW(hwnd, message, wparam, lparam);

   }

   return lresult;

}






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
//      __pointer(::user::interaction) pTopLevel = pwindow->get_top_level();
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


wstring windowing::_windows_calc_icon_window_class(::user::interaction * puserinteraction, u32 dwDefaultStyle, const char * pszMatter)
{

   auto pcontext = puserinteraction->get_context();

   string strPath = pcontext->dir().matter(pszMatter, "icon.ico");

   hicon hIcon = (hicon) ::LoadImageW(nullptr, wstring(pcontext->get_matter_path(strPath)), IMAGE_ICON, 256, 256, LR_LOADFROMFILE);

   wstring strClass = _windows_get_user_interaction_window_class(puserinteraction);

   if (hIcon != nullptr)
   {

      auto psystem = get_system();
      // will fill pszClassName with default WNDCLASS name

      // ignore instance handle from pre_create_window.

      WNDCLASSEXW wndcls;

      if (strClass.get_length() > 0 && GetClassInfoExW((HINSTANCE)psystem->m_hinstance, strClass, &wndcls) && wndcls.hIcon != hIcon)
      {

         // register a very similar WNDCLASS

         return _windows_register_window_class(wndcls.style, wndcls.hCursor, wndcls.hbrBackground, hIcon);

      }

   }

   return strClass;

}




wstring windowing::_windows_get_user_interaction_window_class(::user::interaction * puserinteraction)
{

   ::user::interaction::enum_type etype = puserinteraction->get_window_type();

   WNDCLASSEXW wndcls;

   __memset(&wndcls, 0, sizeof(WNDCLASSEXW));   // start with nullptr defaults

   wndcls.lpfnWndProc = windows_user_interaction_impl_get_window_procedure();

   wndcls.hInstance = GetModuleHandleW(L"windowing_win32.dll");

   //INITCOMMONCONTROLSEX init;
   //init.dwSize = sizeof(init);

   if (etype == ::user::interaction::type_frame || etype == ::user::interaction::type_view)
   {

      // SDI Frame or MDI Child windows or views - normal colors

      wndcls.style = CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW | CS_OWNDC;

      //wndcls.style = CS_HREDRAW | CS_VREDRAW;

      wndcls.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);

      wndcls.cbWndExtra = wndcls.cbClsExtra = 40;

      if (_windows_register_with_icon(&wndcls, L"ca2_frame", 0))
      {

         return wndcls.lpszClassName;

      }

   }


   return _windows_register_window_class(0);

}

bool windowing::_windows_register_with_icon(WNDCLASSEXW * puserinteractionclass, const unichar * pszClassName, ::u32 nIDIcon)
{

   puserinteractionclass->lpszClassName = pszClassName;

   puserinteractionclass->hIcon = ::LoadIconW(nullptr, MAKEINTRESOURCEW(32512));

   return _windows_register_class(puserinteractionclass);

}


//CLASS_DECL_WINDOWING_WIN32 WNDPROC get_window_procedure();


wstring windowing::_windows_register_window_class(::u32 nClassStyle, hcursor hCursor, HBRUSH hbrBackground, hicon hIcon)
{

   //auto papp = pobject->get_application();

   const int iLen = 4096;

   wstring wstrClassName;

   HINSTANCE hinstance = ::GetModuleHandleW(L"windowing_win32.dll");



   {

      LPWSTR lpwsz = wstrClassName.get_string_buffer(iLen);

      if (hCursor == nullptr && hbrBackground == nullptr && hIcon == nullptr)
      {

         C_RUNTIME_ERRORCHECK_SPRINTF(_snwprintf_s(lpwsz, iLen, iLen - 1, L"windows_interaction_impl:%p,%x", hinstance, nClassStyle));

      }
      else
      {

         C_RUNTIME_ERRORCHECK_SPRINTF(_snwprintf_s(lpwsz, iLen, iLen - 1, L"windows_interaction_impl:%p,%x,%p,%p,%p", hinstance, nClassStyle, hCursor, hbrBackground, hIcon));

      }

      wstrClassName.release_string_buffer();

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
   // otherwise we need to register a new class
   wndcls.style = nClassStyle;
   wndcls.lpfnWndProc = windows_user_interaction_impl_get_window_procedure();

   wndcls.cbClsExtra = wndcls.cbWndExtra = 40;
   wndcls.hInstance = hinstance;
   //wndcls.hIcon = hIcon;
   //wndcls.hCursor = hCursor;
   wndcls.hCursor = nullptr;
   wndcls.hbrBackground = hbrBackground;
   wndcls.lpszMenuName = nullptr;

   wndcls.lpszClassName = wstrClassName;

   if (!_windows_register_class(&wndcls))
   {

      __throw(error_resource);

   }

   // return thread-local pointer
   return wstrClassName;

}



}//namespace windowing_win32


lresult CALLBACK WndProc(HWND hWnd, const ::id & id, wparam wParam, lparam lParam);

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


   bool windowing::_windows_register_class(WNDCLASSEXW* puserinteractionclass)
   {

      WNDCLASSEXW wndcls;

      if (GetClassInfoExW(puserinteractionclass->hInstance, puserinteractionclass->lpszClassName, &wndcls))

      {

         return true;

      }

      puserinteractionclass->cbSize = sizeof(WNDCLASSEXW);

      if (!::RegisterClassExW(puserinteractionclass))
      {

         ::u32 dw = GetLastError();

         return false;

      }

      bool bRet = true;

      return bRet;

   }


} // namespace windowing_win32



CLASS_DECL_WINDOWING_WIN32 WNDPROC windows_user_interaction_impl_get_window_procedure()
{

   return &__window_procedure;

}



