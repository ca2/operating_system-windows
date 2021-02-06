// Created by camilo on 2021-01-30 <3ThomasBS_!!
#include "framework.h"


wparam MapLeftRightKeys(wparam vk, lparam lParam);


namespace windowing_win32
{


   windowing::windowing()
   {

      set_layer(LAYERED_IMPL, this);

   }


   windowing::~windowing()
   {

   }


   ::e_status windowing::initialize_windowing(::user::user * puser)
   {

      auto estatus = ::windowing::windowing::initialize_windowing(puser);

      if (!estatus)
      {

         return estatus;

      }

      estatus = ::__construct(m_pdisplay);

      if (!estatus)
      {

         return estatus;

      }

      estatus = m_pdisplay->initialize_display(this);

      if (!estatus)
      {

         return estatus;

      }

      return estatus;

   }


   void windowing::defer_term_ui()
   {


   }


   void windowing::finalize_windowing()
   {

      ::windowing::windowing::finalize_windowing();

   }



   void windowing::finalize()
   {

      ::windowing::windowing::finalize();

   }


   ::windowing_win32::window * windowing::_window(HWND hwnd)
   {

      if (::is_null(hwnd))
      {

         return nullptr;

      }

      if (!::IsWindow(hwnd))
      {

         return nullptr;

      }

      critical_section_lock sl(&m_criticalsection);

      auto & pwindow = m_windowmap[hwnd];

      if (!pwindow)
      {

         pwindow = __new(::windowing_win32::window());

      }

      return pwindow;

   }

   
   ::windowing::display * windowing::display()
   {

      return m_pdisplay;

   }


   ::windowing::window * windowing::window(oswindow oswindow)
   {

      HWND hwnd = __hwnd(oswindow);

      auto pwindow = _window(hwnd);

      return pwindow;

   }


   HWND windowing::zorder_to_hwnd(const zorder & zorder)
   {

      if (zorder.m_ezorder == e_zorder_normal)
      {

         if (::IsWindow((HWND)zorder.m_iZOrder))
         {

            return (HWND)zorder.m_iZOrder;

         }
         else
         {

            return nullptr;

         }

      }
      else if (zorder.m_ezorder == e_zorder_top)
      {

         return (HWND)HWND_TOP;

      }
      else if (zorder.m_ezorder == e_zorder_top_most)
      {

         return (HWND)HWND_TOPMOST;

      }
      else if (zorder.m_ezorder == e_zorder_bottom)
      {

         return (HWND)HWND_BOTTOM;

      }
      else if (zorder.m_ezorder == e_zorder_hwnd)
      {

         return (HWND)zorder.m_iZOrder;

      }
      else
      {

         return nullptr;

      }

   }


   zorder windowing::zorder_from_hwnd(HWND hwnd)
   {

      zorder zorder;

      if (hwnd == HWND_BOTTOM)
      {

         zorder.m_ezorder = e_zorder_bottom;

         zorder.m_iZOrder = 0;

      }
      else if (hwnd == HWND_NOTOPMOST)
      {

         zorder.m_ezorder = e_zorder_no_top_most;

         zorder.m_iZOrder = 0;

      }
      else if (hwnd == HWND_TOP)
      {

         zorder.m_ezorder = e_zorder_top;

         zorder.m_iZOrder = 0;

      }
      else if (hwnd == HWND_TOPMOST)
      {

         zorder.m_ezorder = e_zorder_top_most;

         zorder.m_iZOrder = 0;

      }
      else if (::IsWindow(hwnd))
      {

         zorder.m_ezorder = e_zorder_hwnd;

         zorder.m_iZOrder = (iptr)hwnd;

      }
      else
      {

         zorder.m_ezorder = e_zorder_top;

         zorder.m_iZOrder = 0;

      }

      return zorder;

   }


   void windowing::__synthesizes_creates_styles(::user::interaction * pinteraction, ::u32 & nExStyle, ::u32 & nStyle)
   {

      if (pinteraction->m_bTransparent)
      {

         nExStyle |= WS_EX_LAYERED;

      }

      if (pinteraction->layout().sketch().is_visible())
      {

         nStyle |= WS_VISIBLE;

      }

   }

   
   ::windowing::window * windowing::get_desktop_window()
   {

      HWND hwnd = ::GetDesktopWindow();

      auto pwindow = _window(hwnd);

      return pwindow;

   }


   ::windowing::window * windowing::get_active_window()
   {

      HWND hwnd = ::GetActiveWindow();

      auto pwindow = _window(hwnd);

      return pwindow;

   }


   ::windowing::window * windowing::get_focus()
   {

      HWND hwnd = ::GetFocus();

      auto pwindow = _window(hwnd);

      return pwindow;

   }


   void windowing::get_app_wnda(hwnd_array & wnda)
   {

      EnumWindows(&windowing::GetAppsEnumWindowsProc, (lparam)&wnda);

   }

   

   __pointer(::message::base) windowing::get_message_base(MESSAGE * pmsg)
   {

      //__throw(todo("message"));
      //__throw(todo("interaction"));
      ::layered * playeredUserPrimitive = nullptr;

      //if (pinteraction == nullptr && pmsg->hwnd != nullptr)
      //{

      //   if (pmsg->message == 126)
      //   {

      //      TRACE("e_message_display_change");

      //   }

      //   ::user::interaction_impl * pimpl = System.impl_from_handle(pmsg->hwnd);

      //   if (pimpl != nullptr)
      //   {

      //      try
      //      {

      //         pinteraction = pimpl->m_puserinteraction;

      //      }
      //      catch (...)
      //      {

      //         pinteraction = nullptr;

      //      }

      //   }

      //   if (pinteraction == nullptr)
      //   {

      //      pinteraction = pimpl;

      //   }

      //}

      //if (pinteraction != nullptr)
      //{

      //   return pinteraction->get_message_base(pmsg->message, pmsg->wParam, pmsg->lParam);

      //}

      auto pbase = __new(::message::base);

      if (!pbase)
      {

         return nullptr;

      }

      pbase->set(pmsg->oswindow, playeredUserPrimitive, (enum_message)pmsg->message, pmsg->wParam, pmsg->lParam);

      return pbase;

   }



   void windowing::set(message::key * pkey, HWND hwnd, ::layered * playeredUserPrimitive, const ::id & id, wparam wparam, ::lparam lparam)
   {

      pkey->m_nChar = static_cast<::u32>(wparam);

      pkey->m_nRepCnt = LOWORD(lparam);

      pkey->m_nFlags = HIWORD(lparam);

      pkey->m_nScanCode = ((lparam >> 16) & 0xff);

      pkey->m_bExt = (lparam & (1 << 24)) != 0;

      pkey->m_iVirtualKey = (int)MapLeftRightKeys(wparam, lparam);

      auto psession = Session;

      psession->keyboard().translate_os_key_message(pkey);

   }


   void windowing::set(::message::mouse * pmouse, HWND hwnd, ::layered * playeredUserPrimitive, const ::id & id, wparam wparam, ::lparam lparam)
   {

      pmouse->m_nFlags = wparam;

      pmouse->m_point = __point(lparam);

      pmouse->m_bTranslated = true; // not in root coordinates

      ::ClientToScreen((HWND) pmouse->m_oswindow, (POINT *) &pmouse->m_point);

   }


   //void windowing::set_focus(::windowing::window * pwindow)
   //{

   //   auto pwindowFocus = __hwnd(pwindow);

   //   HWND hwnd  = pwindow->m_
   //   if (pinteraction == nullptr)
   //   {

   //      ::set_focus(nullptr);

   //      return;

   //   }


   //   ::set_focus(pinteraction->get_safe_handle());

   //   if (pinteraction->get_wnd() != nullptr)
   //   {

   //      pinteraction->SetFocus();

   //   }

   //   return;

   //}


   ::windowing::window * windowing::get_capture()
   {

      HWND hwnd = ::GetCapture();

      auto pwindow = _window(hwnd);

      return pwindow;

   }

   
   ::e_status windowing::release_capture()
   {

      if (!::ReleaseCapture())
      {

         return error_failed;

      }

      return success;

   }


   void windowing::get_cursor_pos(POINT_I32 * ppoint)
   {


      if (get_context_session()->m_bSystemSynchronizedCursor)
      {

         POINT point;

         ::GetCursorPos(&point);

         m_pointCursor.x = point.x;

         m_pointCursor.y = point.y;

      }

      if (ppoint != nullptr)
      {

         *ppoint = m_pointCursor;

      }

   }


   ::e_status windowing::remove_window(::windowing::window * pwindow)
   {

      if (!m_windowmap.remove_key(__hwnd(pwindow->get_oswindow())))
      {

         return ::error_failed;

      }

      return ::success;

   }



   ::windowing::cursor * windowing::get_cursor()
   {

      if (m_ecursor == e_cursor_none)
      {

         return nullptr;

      }
      else if (m_ecursor == e_cursor_default)
      {

         return get_cursor(m_ecursorDefault);

      }
      else
      {

         return get_cursor(m_ecursor);

      }

   }


   ::windowing::cursor * windowing::get_default_cursor()
   {

      return get_cursor(m_ecursorDefault);

   }

   
   int_bool windowing::point_is_window_origin(POINT_I32 ptHitTest, oswindow oswindowExclude, int iMargin)
   {

      HWND hwndExclude = __hwnd(oswindowExclude);

      auto phwnda = get_top_level_windows();

      if (phwnda->is_empty())
      {

         return false;

      }

      ::RECT rectWindow;

      for (auto & hwnd : *phwnda)
      {

         if (hwnd != hwndExclude)
         {

            if (!IsWindowVisible(hwnd))
            {

               continue;

            }

            if (::GetWindowRect(hwnd, &rectWindow))
            {

               ::rectangle_i32 rectHitTest;

               __copy(rectHitTest, rectWindow);

               rectHitTest.inflate(iMargin + 1);

               if (rectHitTest.contains(ptHitTest))
               {

                  return true;

               }

               //return true;

            }

         }

      }

      return false;

   }


   hwnd_array get_hwnda(const ::user::interaction_ptra & ptra)
   {

      hwnd_array hwnda;

      for (i32 i = 0; i < ptra.get_size(); i++)
      {

         hwnda.add(__hwnd(ptra.element_at(i)->get_oswindow()));

      }

      return hwnda;

   }


   hwnd_array get_hwnda(const ::user::primitive_ptra & ptra)
   {

      hwnd_array hwnda;

      for (i32 i = 0; i < ptra.get_size(); i++)
      {

         hwnda.add(__hwnd(ptra.element_at(i)->get_oswindow()));

      }

      return hwnda;

   }

   __pointer(::windowing::window) windowing::window_from_point(::aura::application * papp, const ::point_i32 & point)
   {

      auto uia = *papp->m_puiptraFrame;

      hwnd_array hwnda;

      hwnda = get_hwnda(uia);

      window_util::SortByZOrder(hwnda);

      for (i32 i = 0; i < hwnda.get_count(); i++)
      {

         auto puieWindow = uia.find_first(__oswindow(hwnda[i]));

         auto puie = puieWindow->_001FromPoint(point);

         if (puie != nullptr)
         {

            return puie;

         }

      }

      return nullptr;

   }


   bool windowing::_is_window(HWND hwnd)
   {

      if (!::IsWindow(hwnd))
      {

         return false;

      }

      return true;

   }


   __pointer(::user::interaction) windowing::create_system_window()
   {

      auto psysteminteraction = __create_new < system_interaction >();

      psysteminteraction->display(e_display_none);

      if (!psysteminteraction->create_host())
      {

         return nullptr;

      }

      return psysteminteraction;

   }


   BOOL CALLBACK windowing::GetAppsEnumWindowsProc(HWND hwnd, LPARAM lParam)
   {

      hwnd_array * phwnda = (hwnd_array *) lParam;

      phwnda->add(hwnd);

      return true;

   }


   void windowing::initialize_keyboard(::user::keyboard * pkeyboard)
   {

#ifdef WINDOWS

      for (char ch = 'A'; ch <= 'Z'; ch++)
      {

         m_mapKey[ch] = (::user::enum_key)(::user::e_key_a + (ch - 'A'));

      }

      for (char ch = '0'; ch <= '9'; ch++)
      {

         m_mapKey[ch] = (::user::enum_key)(::user::e_key_0 + (ch - '0'));

      }

      m_mapKey[VK_LEFT] = ::user::e_key_left;
      m_mapKey[VK_RIGHT] = ::user::e_key_right;
      m_mapKey[VK_UP] = ::user::e_key_up;
      m_mapKey[VK_DOWN] = ::user::e_key_down;
      m_mapKey[VK_DELETE] = ::user::e_key_delete;
      m_mapKey[VK_BACK] = ::user::e_key_back;
      m_mapKey[VK_RETURN] = ::user::e_key_return;
      m_mapKey[VK_SPACE] = ::user::e_key_space;
      m_mapKey[VK_HOME] = ::user::e_key_home;
      m_mapKey[VK_END] = ::user::e_key_end;
      m_mapKey[VK_PRIOR] = ::user::e_key_prior;
      m_mapKey[VK_NEXT] = ::user::e_key_next;
      m_mapKey[VK_TAB] = ::user::e_key_tab;
      m_mapKey[VK_ESCAPE] = ::user::e_key_escape;
      m_mapKey[VK_TAB] = ::user::e_key_tab;
      m_mapKey[VK_F1] = ::user::e_key_f1;
      m_mapKey[VK_F2] = ::user::e_key_f2;
      m_mapKey[VK_F3] = ::user::e_key_f3;
      m_mapKey[VK_F4] = ::user::e_key_f4;
      m_mapKey[VK_F5] = ::user::e_key_f5;
      m_mapKey[VK_F6] = ::user::e_key_f6;
      m_mapKey[VK_F7] = ::user::e_key_f7;
      m_mapKey[VK_F8] = ::user::e_key_f8;
      m_mapKey[VK_F9] = ::user::e_key_f9;
      m_mapKey[VK_F10] = ::user::e_key_f10;
      m_mapKey[VK_F11] = ::user::e_key_f11;
      m_mapKey[VK_F12] = ::user::e_key_f12;
      m_mapKey[VK_LSHIFT] = ::user::e_key_lshift;
      m_mapKey[VK_RSHIFT] = ::user::e_key_rshift;
      m_mapKey[VK_LCONTROL] = ::user::e_key_lcontrol;
      m_mapKey[VK_RCONTROL] = ::user::e_key_rcontrol;
      m_mapKey[VK_LMENU] = ::user::e_key_lalt;
      m_mapKey[VK_RMENU] = ::user::e_key_ralt;

#endif

   }


   bool windowing::is_window(oswindow oswindow)
   {

      HWND hwnd = (HWND)oswindow;

      if (::IsWindow(hwnd))
      {

         return false;

      }

      return true;

   }


} // namespace windowing_win32



