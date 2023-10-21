// Created by camilo on 2021-01-30 <3ThomasBS_!!
#include "framework.h"
#undef USUAL_OPERATING_SYSTEM_SUPPRESSIONS
#include "input.h"
#include "mouse_hook.h"
#include "keyboard_hook.h"
#include "acme/constant/message.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/platform/scoped_restore.h"
#include "aura/message/user.h"
//#include "windowing.h"
//#include "window.h"
//#include "keyboard.h"
//#include "display.h"
//#include "message_window.h"
//#include "monitor.h"
//#include "system_interaction.h"
//#include "top_level_enum.h"
//#include "win32.h"
//#include "window_util.h"
//#include "acme/constant/message.h"
//#include "acme/exception/exception.h"
//#include "apex/platform/system.h"
//#include "aura/message/user.h"
//#include "aura/platform/session.h"
//#include "aura/platform/application.h"
//#include "aura/user/user/interaction_array.h"
//#include "aura/windowing/cursor.h"


//wparam MapLeftRightKeys(wparam vk, lparam lParam);


namespace input_win32
{


   input::input()
   {

      //m_pWindowing4 = this;

      //      set_layer(LAYERED_IMPL, this);
      //m_emessageWindowsTaskbarCreatedMessage = e_message_undefined;

   }


   input::~input()
   {

   }


   //   void windowing::initialize_windowing(::user::user* puser)
   //   {
   //
   //      //auto estatus = 
   //
   //      ::windowing::windowing::initialize_windowing(puser);
   //
   //      //if (!estatus)
   //      //{
   //
   //      //   return estatus;
   //
   //      //}
   //
   //      //estatus = 
   //
   //      __construct(m_pdisplay);
   //
   //      //if (!estatus)
   //      //{
   //
   //      //   return estatus;
   //
   //      //}
   //
   //      //estatus =
   //
   //      m_pdisplay->initialize_display(this);
   //
   //      //if (!estatus)
   //      //{
   //
   //      //   return estatus;
   //
   //      //}
   //
   //      bool bCreateSessionWindow = defer_create_system_window();
   //
   //      if (!bCreateSessionWindow)
   //      {
   //
   //         warning() << "Could not create session window";
   //
   //      }
   //
   //      auto pdisplay = dynamic_cast <class display*>(display());
   //
   //      pdisplay->register_device_listener(::hardware::e_device_monitor);
   //
   //
   //
   //      //return estatus;
   //
   //   }
   //
   //
   //   bool windowing::defer_create_system_window()
   //   {
   //
   //      if (m_psysteminteraction)
   //      {
   //
   //         return true;
   //
   //      }
   //
   //      m_psysteminteraction = create_system_window();
   //
   //      if (!m_psysteminteraction)
   //      {
   //
   //         return false;
   //
   //      }
   //
   //      return true;
   //
   //   }
   //
   //
   //   ::pointer<system_interaction>windowing::create_system_window()
   //   {
   //
   //      auto psysteminteraction = __create_new < ::windowing_win32::system_interaction >();
   //
   //      psysteminteraction->display(e_display_none);
   //
   //      //auto estatus = 
   //
   //      psysteminteraction->create_host();
   //
   //      //if(!estatus)
   //      //{
   //
   //      //   return estatus;
   //
   //      //}
   //
   //      //add_object(psysteminteraction);
   //
   //      return psysteminteraction;
   //
   //   }
   //
   //
   //
   //
   //   void windowing::defer_term_ui()
   //   {
   //
   //      if (m_psysteminteraction)
   //      {
   //
   //         m_psysteminteraction->start_destroying_window();
   //
   //      }
   //
   //   }
   //
   //
   //   void windowing::finalize_windowing()
   //   {
   //
   //      ::windowing::windowing::finalize_windowing();
   //
   //      m_psysteminteraction.release();
   //
   //   }
   //
   //
   //   void windowing::destroy()
   //   {
   //
   //      if (m_psysteminteraction)
   //      {
   //
   //         m_psysteminteraction->start_destroying_window();
   //
   //      }
   //
   //      //auto estatus = 
   //
   //      ::windowing::windowing::destroy();
   //
   //      //if (!estatus)
   //      //{
   //
   //      //   return estatus;
   //
   //      //}
   //
   //      //return estatus;
   //
   //   }
   //
   //
   //   //void windowing::destroy()
   //   //{
   //
   //   //   auto estatus = ::windowing::windowing::destroy();
   //
   //   //   return estatus;
   //
   //   //}
   //
   //
   //   ::windowing_win32::window* windowing::_window(HWND hwnd)
   //   {
   //
   //      if (::is_null(hwnd))
   //      {
   //
   //         return nullptr;
   //
   //      }
   //
   //      if (!::IsWindow(hwnd))
   //      {
   //
   //         return nullptr;
   //
   //      }
   //
   //      critical_section_lock synchronouslock(&m_criticalsection);
   //
   //      auto& pwindow = m_windowmap[hwnd];
   //
   //      if (!pwindow)
   //      {
   //
   //         pwindow = __new(::windowing_win32::window());
   //
   //      }
   //
   //      return pwindow;
   //
   //   }
   //
   //
   //   ::windowing::display* windowing::display()
   //   {
   //
   //      return m_pdisplay;
   //
   //   }
   //
   //
   //
   //
   //   ::windowing::window* windowing::window(oswindow oswindow)
   //   {
   //
   //      HWND hwnd = __hwnd(oswindow);
   //
   //      auto pwindow = _window(hwnd);
   //
   //      return pwindow;
   //
   //   }
   //
   //
   //   HWND windowing::zorder_to_hwnd(const zorder& zorder)
   //   {
   //
   //      if (zorder.m_ezorder == e_zorder_normal)
   //      {
   //
   //         if (::IsWindow((HWND)zorder.m_iZOrder))
   //         {
   //
   //            return (HWND)zorder.m_iZOrder;
   //
   //         }
   //         else
   //         {
   //
   //            return nullptr;
   //
   //         }
   //
   //      }
   //      else if (zorder.m_ezorder == e_zorder_top)
   //      {
   //
   //         return (HWND)HWND_TOP;
   //
   //      }
   //      else if (zorder.m_ezorder == e_zorder_top_most)
   //      {
   //
   //         return (HWND)HWND_TOPMOST;
   //
   //      }
   //      else if (zorder.m_ezorder == e_zorder_bottom)
   //      {
   //
   //         return (HWND)HWND_BOTTOM;
   //
   //      }
   //      else if (zorder.m_ezorder == e_zorder_hwnd)
   //      {
   //
   //         return (HWND)zorder.m_iZOrder;
   //
   //      }
   //      else
   //      {
   //
   //         return nullptr;
   //
   //      }
   //
   //   }
   //
   //
   //   zorder windowing::zorder_from_hwnd(HWND hwnd)
   //   {
   //
   //      zorder zorder;
   //
   //      if (hwnd == HWND_BOTTOM)
   //      {
   //
   //         zorder.m_ezorder = e_zorder_bottom;
   //
   //         zorder.m_iZOrder = 0;
   //
   //      }
   //      else if (hwnd == HWND_NOTOPMOST)
   //      {
   //
   //         zorder.m_ezorder = e_zorder_no_top_most;
   //
   //         zorder.m_iZOrder = 0;
   //
   //      }
   //      else if (hwnd == HWND_TOP)
   //      {
   //
   //         zorder.m_ezorder = e_zorder_top;
   //
   //         zorder.m_iZOrder = 0;
   //
   //      }
   //      else if (hwnd == HWND_TOPMOST)
   //      {
   //
   //         zorder.m_ezorder = e_zorder_top_most;
   //
   //         zorder.m_iZOrder = 0;
   //
   //      }
   //      else if (::IsWindow(hwnd))
   //      {
   //
   //         zorder.m_ezorder = e_zorder_hwnd;
   //
   //         zorder.m_iZOrder = (iptr)hwnd;
   //
   //      }
   //      else
   //      {
   //
   //         zorder.m_ezorder = e_zorder_top;
   //
   //         zorder.m_iZOrder = 0;
   //
   //      }
   //
   //      return zorder;
   //
   //   }
   //
   //
   //   void windowing::__synthesizes_creates_styles(::user::interaction* pinteraction, ::u32& nExStyle, ::u32& nStyle)
   //   {
   //
   //      if (pinteraction->m_bCompositedFrameWindow)
   //      {
   //
   //         nExStyle |= WS_EX_LAYERED;
   //
   //         nStyle |= WS_POPUP;
   //
   //         nStyle |= WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX;
   //
   //      }
   //
   //      if (pinteraction->const_layout().sketch().is_visible())
   //      {
   //
   //         nStyle |= WS_VISIBLE;
   //
   //      }
   //
   //      if (pinteraction->m_bToolWindow)
   //      {
   //
   //         nExStyle |= WS_EX_TOOLWINDOW;
   //
   //      }
   //
   //   }
   //
   //
   //   ::windowing::window* windowing::get_desktop_window()
   //   {
   //
   //      HWND hwnd = ::GetDesktopWindow();
   //
   //      auto pwindow = _window(hwnd);
   //
   //      return pwindow;
   //
   //   }
   //
   //
   //   ::windowing::window* windowing::get_active_window(::thread* pthread)
   //   {
   //
   //      itask_t itask = 0;
   //
   //      if (pthread)
   //      {
   //
   //         itask = pthread->get_itask();
   //
   //      }
   //
   //      GUITHREADINFO info = {};
   //
   //      info.cbSize = sizeof(GUITHREADINFO);
   //
   //      HWND hwndActive;
   //
   //      if (GetGUIThreadInfo((DWORD)itask, &info))
   //      {
   //
   //         hwndActive = info.hwndActive;
   //
   //      }
   //      else
   //      {
   //
   //         hwndActive = ::GetActiveWindow();
   //
   //      }
   //
   //      if (::is_null(hwndActive))
   //      {
   //
   //         return nullptr;
   //
   //      }
   //
   //      auto pwindow = _window(hwndActive);
   //
   //      return pwindow;
   //
   //   }
   //
   //
   //   void windowing::clear_keyboard_focus(::user::element* pelementGainingFocusIfAny)
   //   {
   //
   //
   //
   //   }
   //
   //
   //   ::windowing::window* windowing::get_keyboard_focus(::thread* pthread)
   //   {
   //
   //      itask_t itask = 0;
   //
   //      if (pthread)
   //      {
   //
   //         itask = pthread->get_itask();
   //
   //      }
   //
   //      GUITHREADINFO info = {};
   //
   //      info.cbSize = sizeof(GUITHREADINFO);
   //
   //      HWND hwndFocus;
   //
   //      if (GetGUIThreadInfo((DWORD)itask, &info))
   //      {
   //
   //         hwndFocus = info.hwndFocus;
   //
   //      }
   //      else
   //      {
   //
   //         hwndFocus = ::GetFocus();
   //
   //      }
   //
   //      if (::is_null(hwndFocus))
   //      {
   //
   //         return nullptr;
   //
   //      }
   //
   //      auto pwindow = _window(hwndFocus);
   //
   //      return pwindow;
   //
   //   }
   //
   //
   //   void windowing::get_app_wnda(::windows::hwnd_array& wnda)
   //   {
   //
   //      EnumWindows(&windowing::GetAppsEnumWindowsProc, (lparam)&wnda);
   //
   //   }
   //
   //
   //   //::pointer<::user::message>windowing::get_user_message(MESSAGE * pmsg)
   //   //{
   //
   //   //   //throw ::exception(todo("message"));
   //   //   //throw ::exception(todo("interaction"));
   //   //   ::windowing::window * pwindow = nullptr;
   //
   //   //   //if (pinteraction == nullptr && pmsg->hwnd != nullptr)
   //   //   //{
   //
   //   //   //   if (pmsg->message == 126)
   //   //   //   {
   //
   //   //   //      informationf("e_message_display_change");
   //
   //   //   //   }
   //
   //   //   //   ::user::interaction_impl * pimpl = psystem->impl_from_handle(pmsg->hwnd);
   //
   //   //   //   if (pimpl != nullptr)
   //   //   //   {
   //
   //   //   //      try
   //   //   //      {
   //
   //   //   //         pinteraction = pimpl->acmesystem()interaction;
   //
   //   //   //      }
   //   //   //      catch (...)
   //   //   //      {
   //
   //   //   //         pinteraction = nullptr;
   //
   //   //   //      }
   //
   //   //   //   }
   //
   //   //   //   if (pinteraction == nullptr)
   //   //   //   {
   //
   //   //   //      pinteraction = pimpl;
   //
   //   //   //   }
   //
   //   //   //}
   //
   //   //   //if (pinteraction != nullptr)
   //   //   //{
   //
   //   //   //   return pinteraction->get_message_base(pmsg->message, pmsg->wParam, pmsg->lParam);
   //
   //   //   //}
   //
   //   //   auto pusermessage = __new(::user::message);
   //
   //   //   if (!pusermessage)
   //   //   {
   //
   //   //      return nullptr;
   //
   //   //   }
   //
   //   //   pusermessage->set(pmsg->oswindow, pwindow, pmsg->m_atom, pmsg->wParam, pmsg->lParam);
   //
   //   //   return pusermessage;
   //
   //   //}
   //
   //
   //   void windowing::set(message::key* pkey, oswindow oswindow, ::windowing::window* pwindow, const ::atom& atom, wparam wparam, ::lparam lparam)
   //   {
   //
   //      pkey->m_nChar = static_cast<::u32>(wparam);
   //
   //      pkey->m_nRepCnt = LOWORD(lparam);
   //
   //      pkey->m_nFlags = HIWORD(lparam);
   //
   //      pkey->m_nScanCode = ((lparam >> 16) & 0xff);
   //
   //      pkey->m_bExt = (lparam & (1 << 24)) != 0;
   //
   //      pkey->m_iVirtualKey = (int)MapLeftRightKeys(wparam, lparam);
   //
   //      ::windowing::windowing::set(pkey, oswindow, pwindow, atom, wparam, lparam);
   //
   //   }
   //
   //
   //   void windowing::set(::message::mouse* pmouse, oswindow oswindow, ::windowing::window* pwindow, const ::atom& atom, wparam wparam, ::lparam lparam)
   //   {
   //
   //      //pmouse->m_nFlags = wparam;
   //
   //      //pmouse->m_point = ::point_i32(lparam);
   //
   //      //pmouse->m_bTranslated = true; // not in root coordinates
   //
   //      //::ClientToScreen((HWND) pmouse->m_oswindow, (POINT *) &pmouse->m_point);
   //
   //   }
   //
   //
   //   //void windowing::set_focus(::windowing::window * pwindow)
   //   //{
   //
   //   //   auto pwindowFocus = __hwnd(pwindow);
   //
   //   //   HWND hwnd  = pwindow->m_
   //   //   if (pinteraction == nullptr)
   //   //   {
   //
   //   //      ::set_focus(nullptr);
   //
   //   //      return;
   //
   //   //   }
   //
   //
   //   //   ::set_focus(pinteraction->get_safe_handle());
   //
   //   //   if (pinteraction->get_wnd() != nullptr)
   //   //   {
   //
   //   //      pinteraction->XXXSetFocus();
   //
   //   //   }
   //
   //   //   return;
   //
   //   //}
   //
   //
   //   ::windowing::window* windowing::get_mouse_capture(::thread* pthread)
   //   {
   //
   //      itask_t itask;
   //
   //      if (pthread)
   //      {
   //
   //         itask = pthread->get_itask();
   //
   //      }
   //      else
   //      {
   //
   //         itask = ::current_itask();
   //
   //      }
   //
   //      auto hwndCapture = ::windows::get_mouse_capture(itask);
   //
   //      if (::is_null(hwndCapture))
   //      {
   //
   //         return nullptr;
   //
   //      }
   //
   //      auto pwindow = _window(hwndCapture);
   //
   //      return pwindow;
   //
   //   }
   //
   //
   //   bool windowing::defer_release_mouse_capture(::thread* pthread, ::windowing::window* pwindowDeferRelease)
   //   {
   //
   //      itask_t itask;
   //
   //      if (pthread)
   //      {
   //
   //         itask = pthread->get_itask();
   //
   //      }
   //      else
   //      {
   //
   //         itask = ::current_itask();
   //
   //      }
   //
   //      auto hwndCapture = ::windows::get_mouse_capture(itask);
   //
   //      if (::is_null(hwndCapture))
   //      {
   //
   //         return false;
   //
   //      }
   //
   //      auto pwindow = _window(hwndCapture);
   //
   //      if (pwindow != pwindowDeferRelease)
   //      {
   //
   //         return false;
   //
   //      }
   //
   //      bool bOk = ::windows::defer_release_mouse_capture(itask, hwndCapture);
   //
   //      if (!bOk)
   //      {
   //
   //         return false;
   //
   //      }
   //
   //      return true;
   //
   //   }
   //
   //
   //   //HWND windowing::_get_mouse_capture(itask_t itask)
   //   //{
   //
   //   //   GUITHREADINFO info = {};
   //
   //   //   info.cbSize = sizeof(GUITHREADINFO);
   //
   //   //   HWND hwndCapture = nullptr;
   //
   //   //   if (GetGUIThreadInfo((DWORD)itask, &info))
   //   //   {
   //
   //   //      hwndCapture = info.hwndCapture;
   //
   //   //   }
   //
   //   //   return hwndCapture;
   //
   //   //}
   //
   //
   //   //void windowing::release_mouse_capture()
   //   //{
   //
   //   //   if (!::ReleaseCapture())
   //   //   {
   //
   //   //      //return error_failed;
   //
   //   //      throw ::exception(error_null_pointer);
   //
   //   //   }
   //
   //   //   //return success;
   //
   //   //}
   //
   //
   //   void windowing::get_cursor_pos(::point_i32* ppoint)
   //   {
   //
   //
   //      if (get_session()->m_bSystemSynchronizedCursor)
   //      {
   //
   //         POINT point;
   //
   //         ::GetCursorPos(&point);
   //
   //         m_pointCursor.x() = point.x;
   //
   //         m_pointCursor.y() = point.y;
   //
   //      }
   //
   //      if (ppoint != nullptr)
   //      {
   //
   //         *ppoint = m_pointCursor;
   //
   //      }
   //
   //   }
   //
   //
   //   void windowing::set_cursor_position(const ::point_i32& point)
   //   {
   //
   //      if (!::SetCursorPos(point.x(), point.y()))
   //      {
   //
   //         //return false;
   //
   //      }
   //
   //      //return tru;
   //
   //   }
   //
   //
   //   void windowing::erase_window(::windowing::window* pwindow)
   //   {
   //
   //      if (!m_windowmap.erase_item(__hwnd(pwindow->oswindow())))
   //      {
   //
   //         //return ::error_failed;
   //
   //      }
   //
   //      //return ::success;
   //
   //   }
   //
   //
   //
   //   ::windowing::cursor* windowing::get_cursor()
   //   {
   //
   //      if (m_ecursor == e_cursor_none)
   //      {
   //
   //         return nullptr;
   //
   //      }
   //      else if (m_ecursor == e_cursor_default)
   //      {
   //
   //         return get_cursor(m_ecursorDefault);
   //
   //      }
   //      else
   //      {
   //
   //         return get_cursor(m_ecursor);
   //
   //      }
   //
   //   }
   //
   //
   //   ::windowing::cursor* windowing::get_default_cursor()
   //   {
   //
   //      return get_cursor(m_ecursorDefault);
   //
   //   }
   //
   //
   //   //   enum_dialog_result windowing::message_box(const ::string & pszMessage, const ::string & pszTitle, const ::e_message_box & emessagebox)
   //   //   {
   //   //
   //   //      wstring wstrMessage(pszMessage);
   //   //
   //   //      wstring wstrTitle(pszTitle);
   //   //
   //   //      auto iResult = ::MessageBoxW(nullptr, wstrMessage, wstrTitle, emessagebox);
   //   //
   //   ////      auto strResult = message_box_result_to_string(iResult);
   //   //
   //   ////      return setrResult;
   //   //
   //   //      return (enum_dialog_result) iResult;
   //   //
   //   //   }
   //
   //
   //   int_bool windowing::point_is_window_origin(::point_i32 ptHitTest, oswindow oswindowExclude, int iMargin)
   //   {
   //
   //      HWND hwndExclude = __hwnd(oswindowExclude);
   //
   //      auto phwnda = ::windows::get_top_level_windows();
   //
   //      if (phwnda->is_empty())
   //      {
   //
   //         return false;
   //
   //      }
   //
   //      ::RECT rectWindow;
   //
   //      for (auto& hwnd : *phwnda)
   //      {
   //
   //         if (hwnd != hwndExclude)
   //         {
   //
   //            if (!IsWindowVisible(hwnd))
   //            {
   //
   //               continue;
   //
   //            }
   //
   //            if (::GetWindowRect(hwnd, &rectWindow))
   //            {
   //
   //               ::rectangle_i32 rectangleHitTest;
   //
   //               rectangleHitTest = rectWindow;
   //
   //               rectangleHitTest.inflate(iMargin + 1);
   //
   //               if (rectangleHitTest.contains(ptHitTest))
   //               {
   //
   //                  return true;
   //
   //               }
   //
   //               //return true;
   //
   //            }
   //
   //         }
   //
   //      }
   //
   //      return false;
   //
   //   }
   //
   //
   //   ::windows::hwnd_array windowing::_get_hwnda(const ::user::primitive_pointer_array& primitivepointera)
   //   {
   //
   //      ::windows::hwnd_array hwnda;
   //
   //      for (i32 i = 0; i < primitivepointera.primitive_count(); i++)
   //      {
   //
   //         ::pointer<::user::interaction>puserinteraction = primitivepointera.primitive_at(i);
   //
   //         hwnda.add((HWND)puserinteraction->oswindow());
   //
   //      }
   //
   //      return hwnda;
   //
   //   }
   //
   //
   //   ::pointer<::windowing::window>windowing::window_from_point(::aura::application* papp, const ::point_i32& point)
   //   {
   //
   //      auto uia = *papp->m_puserinteractiona;
   //
   //      ::windows::hwnd_array hwnda;
   //
   //      hwnda = ::windows::get_hwnda(uia);
   //
   //      ::windows::window_util::SortByZOrder(hwnda);
   //
   //      for (i32 i = 0; i < hwnda.get_count(); i++)
   //      {
   //
   //         auto puieWindow = uia.find_first(__oswindow(hwnda[i]));
   //
   //         auto puie = puieWindow->_001FromPoint(point);
   //
   //         if (puie != nullptr)
   //         {
   //
   //            return puie;
   //
   //         }
   //
   //      }
   //
   //      return nullptr;
   //
   //   }
   //
   //
   //   void windowing::windowing_post(const ::procedure& procedure)
   //   {
   //
   //      acmesystem()->m_papexsystem->post_procedure(procedure);
   //
   //   }
   //
   //
   //   bool windowing::_is_window(HWND hwnd)
   //   {
   //
   //      if (!::IsWindow(hwnd))
   //      {
   //
   //         return false;
   //
   //      }
   //
   //      return true;
   //
   //   }
   //
   //
   //   //::pointer<::user::interaction>windowing::create_system_window()
   //   //{
   //
   //   //   auto psysteminteraction = __create_new < system_interaction >();
   //
   //   //   psysteminteraction->display(e_display_none);
   //
   //   //   if (!psysteminteraction->create_host())
   //   //   {
   //
   //   //      return nullptr;
   //
   //   //   }
   //
   //   //   return psysteminteraction;
   //
   //   //}
   //
   //
   //   BOOL CALLBACK windowing::GetAppsEnumWindowsProc(HWND hwnd, LPARAM lParam)
   //   {
   //
   //      ::windows::hwnd_array* phwnda = (::windows::hwnd_array*)lParam;
   //
   //      phwnda->add(hwnd);
   //
   //      return true;
   //
   //   }
   //
   //
   //   //void windowing::set(::message::key * pkey, oswindow oswindow, ::windowing::window * pwindow, const ::atom & atom, wparam wparam, ::lparam lparam)
   //   //{
   //
   //
   //   //}
   //
   //
   //   //void windowing::set(::message::mouse * pmouse, oswindow oswindow, ::windowing::window * pwindow, const ::atom & atom, wparam wparam, ::lparam lparam)
   //   //{
   //
   //
   //   //}
   //
   //
   //   void windowing::initialize_keyboard(::windowing::keyboard* pkeyboard)
   //   {
   //
   //
   //      for (char ch = 'A'; ch <= 'Z'; ch++)
   //      {
   //
   //         pkeyboard->m_mapKey[ch] = (::user::enum_key)(::user::e_key_a + (ch - 'A'));
   //
   //      }
   //
   //      for (char ch = '0'; ch <= '9'; ch++)
   //      {
   //
   //         pkeyboard->m_mapKey[ch] = (::user::enum_key)(::user::e_key_0 + (ch - '0'));
   //
   //      }
   //
   //      pkeyboard->m_mapKey[VK_LEFT] = ::user::e_key_left;
   //      pkeyboard->m_mapKey[VK_RIGHT] = ::user::e_key_right;
   //      pkeyboard->m_mapKey[VK_UP] = ::user::e_key_up;
   //      pkeyboard->m_mapKey[VK_DOWN] = ::user::e_key_down;
   //      pkeyboard->m_mapKey[VK_DELETE] = ::user::e_key_delete;
   //      pkeyboard->m_mapKey[VK_BACK] = ::user::e_key_back;
   //      pkeyboard->m_mapKey[VK_RETURN] = ::user::e_key_return;
   //      pkeyboard->m_mapKey[VK_SPACE] = ::user::e_key_space;
   //      pkeyboard->m_mapKey[VK_HOME] = ::user::e_key_home;
   //      pkeyboard->m_mapKey[VK_END] = ::user::e_key_end;
   //      pkeyboard->m_mapKey[VK_PRIOR] = ::user::e_key_prior;
   //      pkeyboard->m_mapKey[VK_NEXT] = ::user::e_key_next;
   //      pkeyboard->m_mapKey[VK_TAB] = ::user::e_key_tab;
   //      pkeyboard->m_mapKey[VK_ESCAPE] = ::user::e_key_escape;
   //      pkeyboard->m_mapKey[VK_TAB] = ::user::e_key_tab;
   //      pkeyboard->m_mapKey[VK_F1] = ::user::e_key_f1;
   //      pkeyboard->m_mapKey[VK_F2] = ::user::e_key_f2;
   //      pkeyboard->m_mapKey[VK_F3] = ::user::e_key_f3;
   //      pkeyboard->m_mapKey[VK_F4] = ::user::e_key_f4;
   //      pkeyboard->m_mapKey[VK_F5] = ::user::e_key_f5;
   //      pkeyboard->m_mapKey[VK_F6] = ::user::e_key_f6;
   //      pkeyboard->m_mapKey[VK_F7] = ::user::e_key_f7;
   //      pkeyboard->m_mapKey[VK_F8] = ::user::e_key_f8;
   //      pkeyboard->m_mapKey[VK_F9] = ::user::e_key_f9;
   //      pkeyboard->m_mapKey[VK_F10] = ::user::e_key_f10;
   //      pkeyboard->m_mapKey[VK_F11] = ::user::e_key_f11;
   //      pkeyboard->m_mapKey[VK_F12] = ::user::e_key_f12;
   //      pkeyboard->m_mapKey[VK_LSHIFT] = ::user::e_key_left_shift;
   //      pkeyboard->m_mapKey[VK_RSHIFT] = ::user::e_key_right_shift;
   //      pkeyboard->m_mapKey[VK_LCONTROL] = ::user::e_key_left_control;
   //      pkeyboard->m_mapKey[VK_RCONTROL] = ::user::e_key_right_control;
   //      pkeyboard->m_mapKey[VK_LMENU] = ::user::e_key_left_alt;
   //      pkeyboard->m_mapKey[VK_RMENU] = ::user::e_key_right_alt;
   //
   //   }
   //
   //
   //   bool windowing::is_window(oswindow oswindow)
   //   {
   //
   //      HWND hwnd = (HWND)oswindow;
   //
   //      if (::IsWindow(hwnd))
   //      {
   //
   //         return false;
   //
   //      }
   //
   //      return true;
   //
   //   }
   //
   //
   //   void windowing::lock_set_foreground_window(bool bLock)
   //   {
   //
   //      if (bLock)
   //      {
   //
   //         if (!LockSetForegroundWindow(LSFW_LOCK))
   //         {
   //
   //            //return error_last_error;
   //            throw ::exception(error_null_pointer);
   //
   //         }
   //
   //      }
   //      else
   //      {
   //
   //         if (!LockSetForegroundWindow(LSFW_UNLOCK))
   //         {
   //
   //            //return error_last_error;
   //            throw ::exception(error_null_pointer);
   //
   //         }
   //
   //      }
   //
   //      //return ::success;
   //
   //   }
   //
   //
   //   //void windowing::get_cursor_position(::point_i32* ppoint)
   //   //{
   //
   //   //   ::GetCursorPos((POINT *) ppoint);
   //
   //   //}
   //
   //
   //   //#ifdef WINDOWS_DESKTOP
   ////
   ////                  CHOOSECOLOR cc;
   ////
   ////                  ::color::color crCustColors[16];
   ////
   ////                  // init-int this array did not affect the mouse problem
   ////                  // ::u32 idx ;
   ////                  // for (idx=0; idx<16; idx++) {
   ////                  // crCustColors[idx] = rgb(idx, idx, idx) ;
   ////                  // }
   ////
   ////                  ZeroMemory(&cc, sizeof(cc));
   ////                  cc.lStructSize = sizeof(CHOOSECOLOR);
   ////                  cc.rgbResult = rgb(0, 0, 0);
   ////                  cc.lpCustColors = (::color::color *) crCustColors;
   ////
   ////                  cc.Flags = CC_RGBINIT | CC_FULLOPEN;
   ////                  cc.hwndOwner = get_safe_handle() ; // this hangs parent, as well as me
   ////
   ////                  if (::ChooseColor(&cc))
   ////                  {
   ////
   ////                     m_eattribute |= ::user::rich_text::attribute_foreground;
   ////
   ////                     m_formata[0]->m_colorForeground = cc.rgbResult | (255 << 24);
   ////
   ////                     update_data(true);
   ////
   ////                  }
   ////#endif
   //
   //
   ////   bool user::modal_get_color(::user::interaction * puiOwner, ::color::hls & hls)
   ////   {
   ////
   ////#ifdef WINDOWS_DESKTOP
   ////
   ////      CHOOSECOLOR cc;
   ////      ::color::color crCustColors[16];
   ////
   ////      // init-int this array did not affect the mouse problem
   ////      // ::u32 idx ;
   ////      // for (idx=0; idx<16; idx++) {
   ////      // crCustColors[idx] = rgb(idx, idx, idx) ;
   ////      // }
   ////
   ////      ::color::color color(hls);
   ////
   ////      ZeroMemory(&cc, sizeof(cc));
   ////      cc.lStructSize = sizeof(CHOOSECOLOR);
   ////      cc.rgbResult = c.get_rgb();
   ////      cc.lpCustColors = (::color::color *)crCustColors;
   ////
   ////      cc.Flags = CC_RGBINIT | CC_FULLOPEN;
   ////      cc.hwndOwner = puiOwner->get_safe_handle(); // this hangs parent, as well as me
   ////
   ////      if (::ChooseColor(&cc))
   ////      {
   ////
   ////         c.set_COLORREF(cc.rgbResult | (255 << 24));
   ////
   ////         c.get_hls(hls);
   ////
   ////         return true;
   ////
   ////      }
   ////
   ////      return false;
   ////
   ////#else
   ////
   ////      auto puser = user();
   ////
   ////      puser->will_use_impact_hint(COLORSEL_IMPACT);
   ////
   ////      auto pdocument = m_mapimpactsystem[COLORSEL_IMPACT]->open_document_file(puiOwner->get_application(), ::e_type_null, __visible(true));
   ////
   ////      ::pointer<::userex::color_impact>pimpact = pdocument->get_typed_impact < ::userex::color_impact >();
   ////
   ////      ::pointer<::user::frame_window>pframe = pimpact->top_level_frame();
   ////
   ////      pframe->set_owner(puiOwner);
   ////
   ////      pframe->_001RunModalLoop();
   ////
   ////      hls = pimpact->m_hls;
   ////
   ////      return true;
   ////
   ////#endif
   ////
   ////
   ////   }
   //
   //
   //   string windowing::_get_window_text_timeout(oswindow oswindow, const class time& timeSendMessageMax)
   //   {
   //
   //      return windows::get_window_text_timeout((HWND)oswindow, timeSendMessageMax);
   //
   //   }
   //
   //
   //   bool windowing::_top_level_contains_name(string str)
   //   {
   //
   //      return _top_level_contains_predicate([this, str](oswindow oswindow)
   //         {
   //
   //            //PSEUDO-Code char sz[1024]; GetWindowTextA(sz,1024, oswindow); return !strcmp(sz, str.c_str());
   //
   //            string strWindowText = _get_window_text_timeout(oswindow, 200_ms);
   //
   //            return strWindowText.case_insensitive_contains(str);
   //
   //         });
   //
   //   }
   //
   //
   //   bool windowing::_visible_top_level_contains_name(string str)
   //   {
   //
   //      return _top_level_contains_predicate([this, str](oswindow oswindow)
   //         {
   //
   //            //PSEUDO-Code char sz[1024]; GetWindowTextA(sz,1024, oswindow); return !strcmp(sz, str.c_str());
   //
   //            if (!::IsWindowVisible((HWND)oswindow))
   //            {
   //
   //               return false;
   //
   //            }
   //
   //            string strWindowText = _get_window_text_timeout(oswindow, 50_ms);
   //
   //            return strWindowText.case_insensitive_contains(str);
   //
   //         });
   //
   //   }
   //
   //
   //   bool windowing::_visible_top_level_contains_all_names(const string_array& stra)
   //   {
   //
   //      return _top_level_contains_predicate([this, &stra](oswindow oswindow)
   //         {
   //
   //            //PSEUDO-Code char sz[1024]; GetWindowTextA(sz,1024, oswindow); return !strcmp(sz, str.c_str());
   //
   //            if (!::IsWindowVisible((HWND)oswindow))
   //            {
   //
   //               return false;
   //
   //            }
   //
   //            string strWindowText = _get_window_text_timeout(oswindow, 50_ms);
   //
   //            for (auto& str : stra)
   //            {
   //
   //               if (!strWindowText.case_insensitive_contains(str))
   //               {
   //
   //                  return false;
   //
   //               }
   //
   //            }
   //
   //            return true;
   //
   //         });
   //
   //   }
   //
   //
   //   void windowing::install_keyboard_hook(::matter* pmatterListener)
   //   {
   //
   //      //auto estatus = 
   //
   //      ::keyboard_hook::install(pmatterListener);
   //
   //      fork([]()
   //         {
   //
   //            ::keyboard_hook::run();
   //
   //         });
   //
   //   }
   //
   //
   //   void windowing::uninstall_keyboard_hook(::matter* pmatterListener)
   //   {
   //
   //      ::keyboard_hook::uninstall(pmatterListener);
   //
   //   }
   //
   //
   //   void windowing::install_mouse_hook(::matter* pmatterListener)
   //   {
   //
   //      ::mouse_hook::install(pmatterListener);
   //
   //      fork([]()
   //         {
   //
   //            ::mouse_hook::run();
   //
   //         });
   //
   //   }
   //
   //
   //   void windowing::uninstall_mouse_hook(::matter* pmatterListener)
   //   {
   //
   //      ::mouse_hook::uninstall(pmatterListener);
   //
   //   }
   //
   //
   //   void windowing::register_windows_message()
   //   {
   //
   //      if (m_emessageWindowsTaskbarCreatedMessage == e_message_undefined)
   //      {
   //
   //         m_emessageWindowsTaskbarCreatedMessage = (enum_message)RegisterWindowMessageW(L"TaskbarCreated");
   //
   //      }
   //
   //   }
   //
   //
   //   ::pointer < ::user::interaction > windowing::create_message_window(const ::string& pszName, ::user::interaction_listener* pinteractionlistener)
   //   {
   //
   //      auto pmessagewindow = __create_new < message_window >();
   //
   //      pmessagewindow->create_message_window(pszName, pinteractionlistener);
   //
   //      return pmessagewindow;
   //
   //   }
   //
   //
   //   void windowing::set_mouse_cursor(::windowing::cursor* pcursor)
   //   {
   //
   //      HCURSOR hcursor = nullptr;
   //
   //      if (::is_set(pcursor))
   //      {
   //
   //         hcursor = (HCURSOR)pcursor->get_os_data();
   //
   //         if (hcursor == nullptr)
   //         {
   //
   //            //auto estatus =
   //
   //            pcursor->_create_os_cursor();
   //
   //            //if (!estatus)
   //            //{
   //
   //            //   return estatus;
   //
   //            //};
   //
   //            hcursor = (HCURSOR)pcursor->get_os_data();
   //
   //            //if (!hcursor)
   //            //{
   //
   //            //   return error_resource;
   //
   //            //}
   //
   //         }
   //
   //      }
   //
   //      // At windows SetMouseCursor(nullptr) removes the cursor from screen
   //      // similar apis in other platforms behave the same?
   //
   //      if (!::SetCursor(hcursor))
   //      {
   //
   //         throw ::exception(error_failed);
   //
   //      }
   //
   //      //return ::success;
   //
   //   }

   void input::defer_input()
   {

      synchronous_lock  synchronouslock(this->synchronization());

      if (m_particleaMouseHandler.has_element())
      {

         mouse_hook::install_mouse_hook();

      }
      else
      {

         mouse_hook::uninstall_mouse_hook();

      }


      if (m_particleaKeyboardHandler.has_element())
      {
         
         keyboard_hook::install_keyboard_hook();

      }
      else
      {

         keyboard_hook::uninstall_keyboard_hook();

      }


   }


   void input::handle(::message::message * pmessage)
   {

      if (pmessage->m_atom.m_etype == atom::e_type_message)
      {

         if (pmessage->m_atom.m_emessage >= e_message_mouse_first
            && pmessage->m_atom.m_emessage <= e_message_mouse_last)
         {

            for (auto & pparticle : m_particleaMouseHandler)
            {

               pparticle->handle(pmessage);

            }

         }
         else if (pmessage->m_atom.m_emessage >= e_message_key_first
            && pmessage->m_atom.m_emessage <= e_message_key_last)
         {

            for (auto & pparticle : m_particleaKeyboardHandler)
            {

               pparticle->handle(pmessage);

            }

         }

      }

   }


} // namespace input_win32



