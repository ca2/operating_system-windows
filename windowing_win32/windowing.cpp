// Created by camilo on 2021-01-30 <3ThomasBS_!!
#include "framework.h"


wparam MapLeftRightKeys(wparam vk, lparam lParam);


namespace windowing_win32
{


   windowing::windowing()
   {

      m_pWindowing = this;

//      set_layer(LAYERED_IMPL, this);

   }


   windowing::~windowing()
   {

   }


   void windowing::initialize_windowing(::user::user * puser)
   {

      //auto estatus = 
      
      ::windowing::windowing::initialize_windowing(puser);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //estatus = 
      
      __construct(m_pdisplay);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //estatus =
      
      m_pdisplay->initialize_display(this);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      bool bCreateSessionWindow = defer_create_system_window();

      if (!bCreateSessionWindow)
      {

         WARNING("Could not create session window");

      }

      //return estatus;

   }


   bool windowing::defer_create_system_window()
   {

      if (m_psysteminteraction)
      {

         return true;

      }

      m_psysteminteraction = create_system_window();

      if (!m_psysteminteraction)
      {

         return false;

      }

      return true;

   }


   __pointer(system_interaction) windowing::create_system_window()
   {

      auto psysteminteraction = __create_new < system_interaction >();

      psysteminteraction->display(e_display_none);

      //auto estatus = 
      
      psysteminteraction->create_host();

      //if(!estatus)
      //{

      //   return estatus;

      //}

      //add_object(psysteminteraction);

      return psysteminteraction;

   }




   void windowing::defer_term_ui()
   {

      if (m_psysteminteraction)
      {

         m_psysteminteraction->start_destroying_window();

      }


   }


   void windowing::finalize_windowing()
   {

      ::windowing::windowing::finalize_windowing();

      m_psysteminteraction.release();

   }

   
   void windowing::destroy()
   {

      if (m_psysteminteraction)
      {

         m_psysteminteraction->start_destroying_window();

      }

      //auto estatus = 
      
      ::windowing::windowing::destroy();

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //return estatus;

   }


   //void windowing::destroy()
   //{

   //   auto estatus = ::windowing::windowing::destroy();

   //   return estatus;

   //}


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

      critical_section_lock synchronouslock(&m_criticalsection);

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

      if (pinteraction->m_bCompositedFrameWindow)
      {

         nExStyle |= WS_EX_LAYERED;

         nStyle |= WS_POPUP;
         
         nStyle |= WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX;

      }

      if (pinteraction->layout().sketch().is_visible())
      {

         nStyle |= WS_VISIBLE;

      }

      if (pinteraction->m_bToolWindow)
      {

         nExStyle |= WS_EX_TOOLWINDOW;

      }

   }

   
   ::windowing::window * windowing::get_desktop_window()
   {

      HWND hwnd = ::GetDesktopWindow();

      auto pwindow = _window(hwnd);

      return pwindow;

   }


   ::windowing::window * windowing::get_active_window(::thread * pthread)
   {

      itask_t itask = 0;

      if (pthread)
      {

         itask = pthread->get_itask();

      }

      GUITHREADINFO info = {};

      info.cbSize = sizeof(GUITHREADINFO);

      HWND hwndActive;

      if (GetGUIThreadInfo((DWORD) itask, &info))
      {

         hwndActive = info.hwndActive;

      }
      else
      {

         hwndActive = ::GetActiveWindow();

      }

      if (::is_null(hwndActive))
      {

         return nullptr;

      }

      auto pwindow = _window(hwndActive);

      return pwindow;

   }


   ::windowing::window * windowing::get_keyboard_focus(::thread * pthread)
   {

      itask_t itask = 0;

      if (pthread)
      {

         itask = pthread->get_itask();

      }

      GUITHREADINFO info = {};

      info.cbSize = sizeof(GUITHREADINFO);

      HWND hwndFocus;

      if (GetGUIThreadInfo((DWORD)itask, &info))
      {

         hwndFocus = info.hwndFocus;

      }
      else
      {

         hwndFocus = ::GetFocus();

      }

      if (::is_null(hwndFocus))
      {

         return nullptr;

      }

      auto pwindow = _window(hwndFocus);

      return pwindow;

   }


   void windowing::get_app_wnda(hwnd_array & wnda)
   {

      EnumWindows(&windowing::GetAppsEnumWindowsProc, (lparam)&wnda);

   }


   __pointer(::user::message) windowing::get_user_message(MESSAGE * pmsg)
   {

      //throw ::exception(todo("message"));
      //throw ::exception(todo("interaction"));
      ::windowing::window * pwindow = nullptr;

      //if (pinteraction == nullptr && pmsg->hwnd != nullptr)
      //{

      //   if (pmsg->message == 126)
      //   {

      //      TRACE("e_message_display_change");

      //   }

      //   ::user::interaction_impl * pimpl = psystem->impl_from_handle(pmsg->hwnd);

      //   if (pimpl != nullptr)
      //   {

      //      try
      //      {

      //         pinteraction = pimpl->m_psysteminteraction;

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

      auto pusermessage = __new(::user::message);

      if (!pusermessage)
      {

         return nullptr;

      }

      pusermessage->set(pmsg->oswindow, pwindow, pmsg->m_atom, pmsg->wParam, pmsg->lParam);

      return pusermessage;

   }


   void windowing::set(message::key * pkey, oswindow oswindow, ::windowing::window * pwindow, const ::atom & atom, wparam wparam, ::lparam lparam)
   {

      pkey->m_nChar = static_cast<::u32>(wparam);

      pkey->m_nRepCnt = LOWORD(lparam);

      pkey->m_nFlags = HIWORD(lparam);

      pkey->m_nScanCode = ((lparam >> 16) & 0xff);

      pkey->m_bExt = (lparam & (1 << 24)) != 0;

      pkey->m_iVirtualKey = (int)MapLeftRightKeys(wparam, lparam);

      ::windowing::windowing::set(pkey, oswindow, pwindow, atom, wparam, lparam);

   }


   void windowing::set(::message::mouse * pmouse, oswindow oswindow, ::windowing::window * pwindow, const ::atom & atom, wparam wparam, ::lparam lparam)
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


   ::windowing::window * windowing::get_mouse_capture(::thread * pthread)
   {

      itask_t itask = 0;

      if (pthread)
      {

         itask = pthread->get_itask();

      }

      auto hwndCapture = ::windows_get_mouse_capture(itask);

      if (::is_null(hwndCapture))
      {

         return nullptr;

      }

      auto pwindow = _window(hwndCapture);

      return pwindow;

   }


   //HWND windowing::_get_mouse_capture(itask_t itask)
   //{

   //   GUITHREADINFO info = {};

   //   info.cbSize = sizeof(GUITHREADINFO);

   //   HWND hwndCapture = nullptr;

   //   if (GetGUIThreadInfo((DWORD)itask, &info))
   //   {

   //      hwndCapture = info.hwndCapture;

   //   }

   //   return hwndCapture;

   //}

   
   void windowing::release_mouse_capture()
   {

      if (!::ReleaseCapture())
      {

         //return error_failed;

         throw ::exception(error_null_pointer);

      }

      //return success;

   }


   void windowing::get_cursor_pos(POINT_I32 * ppoint)
   {


      if (get_session()->m_bSystemSynchronizedCursor)
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


   void windowing::set_cursor_position(const ::point_i32 & point)
   {

      if (!::SetCursorPos(point.x, point.y))
      {

         //return false;

      }

      //return tru;

   }


   void windowing::erase_window(::windowing::window * pwindow)
   {

      if (!m_windowmap.erase_key(__hwnd(pwindow->get_oswindow())))
      {

         //return ::error_failed;

      }

      //return ::success;

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


//   enum_dialog_result windowing::message_box(const ::string & pszMessage, const ::string & pszTitle, const ::e_message_box & emessagebox)
//   {
//
//      wstring wstrMessage(pszMessage);
//
//      wstring wstrTitle(pszTitle);
//
//      auto iResult = ::MessageBoxW(nullptr, wstrMessage, wstrTitle, emessagebox);
//
////      auto strResult = message_box_result_to_string(iResult);
//
////      return setrResult;
//
//      return (enum_dialog_result) iResult;
//
//   }

   
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

               ::rectangle_i32 rectangleHitTest;

               __copy(rectangleHitTest, rectWindow);

               rectangleHitTest.inflate(iMargin + 1);

               if (rectangleHitTest.contains(ptHitTest))
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


   hwnd_array windowing::_get_hwnda(const ::user::primitive_pointer_array & primitivepointera)
   {

      hwnd_array hwnda;

      for (i32 i = 0; i < primitivepointera.primitive_count(); i++)
      {

         __pointer(::user::interaction) puserinteraction = primitivepointera.primitive_at(i);

         hwnda.add((HWND) puserinteraction->get_oswindow());

      }

      return hwnda;

   }

   __pointer(::windowing::window) windowing::window_from_point(::aura::application * papp, const ::point_i32 & point)
   {

      auto uia = *papp->m_puserinteractiona;

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


   void windowing::windowing_post(const ::routine& routine)
   {

      //auto estatus = 
      
      m_psystem->m_papexsystem->post_routine(routine);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //return estatus;

   }


   bool windowing::_is_window(HWND hwnd)
   {

      if (!::IsWindow(hwnd))
      {

         return false;

      }

      return true;

   }


   //__pointer(::user::interaction) windowing::create_system_window()
   //{

   //   auto psysteminteraction = __create_new < system_interaction >();

   //   psysteminteraction->display(e_display_none);

   //   if (!psysteminteraction->create_host())
   //   {

   //      return nullptr;

   //   }

   //   return psysteminteraction;

   //}


   BOOL CALLBACK windowing::GetAppsEnumWindowsProc(HWND hwnd, LPARAM lParam)
   {

      hwnd_array * phwnda = (hwnd_array *) lParam;

      phwnda->add(hwnd);

      return true;

   }


   //void windowing::set(::message::key * pkey, oswindow oswindow, ::windowing::window * pwindow, const ::atom & atom, wparam wparam, ::lparam lparam)
   //{


   //}


   //void windowing::set(::message::mouse * pmouse, oswindow oswindow, ::windowing::window * pwindow, const ::atom & atom, wparam wparam, ::lparam lparam)
   //{


   //}


   void windowing::initialize_keyboard(::windowing::keyboard * pkeyboard)
   {


      for (char ch = 'A'; ch <= 'Z'; ch++)
      {

         pkeyboard->m_mapKey[ch] = (::user::enum_key)(::user::e_key_a + (ch - 'A'));

      }

      for (char ch = '0'; ch <= '9'; ch++)
      {

          pkeyboard->m_mapKey[ch] = (::user::enum_key)(::user::e_key_0 + (ch - '0'));

      }

       pkeyboard->m_mapKey[VK_LEFT] = ::user::e_key_left;
       pkeyboard->m_mapKey[VK_RIGHT] = ::user::e_key_right;
       pkeyboard->m_mapKey[VK_UP] = ::user::e_key_up;
       pkeyboard->m_mapKey[VK_DOWN] = ::user::e_key_down;
       pkeyboard->m_mapKey[VK_DELETE] = ::user::e_key_delete;
       pkeyboard->m_mapKey[VK_BACK] = ::user::e_key_back;
       pkeyboard->m_mapKey[VK_RETURN] = ::user::e_key_return;
       pkeyboard->m_mapKey[VK_SPACE] = ::user::e_key_space;
       pkeyboard->m_mapKey[VK_HOME] = ::user::e_key_home;
       pkeyboard->m_mapKey[VK_END] = ::user::e_key_end;
       pkeyboard->m_mapKey[VK_PRIOR] = ::user::e_key_prior;
       pkeyboard->m_mapKey[VK_NEXT] = ::user::e_key_next;
       pkeyboard->m_mapKey[VK_TAB] = ::user::e_key_tab;
       pkeyboard->m_mapKey[VK_ESCAPE] = ::user::e_key_escape;
       pkeyboard->m_mapKey[VK_TAB] = ::user::e_key_tab;
       pkeyboard->m_mapKey[VK_F1] = ::user::e_key_f1;
       pkeyboard->m_mapKey[VK_F2] = ::user::e_key_f2;
       pkeyboard->m_mapKey[VK_F3] = ::user::e_key_f3;
       pkeyboard->m_mapKey[VK_F4] = ::user::e_key_f4;
       pkeyboard->m_mapKey[VK_F5] = ::user::e_key_f5;
       pkeyboard->m_mapKey[VK_F6] = ::user::e_key_f6;
       pkeyboard->m_mapKey[VK_F7] = ::user::e_key_f7;
       pkeyboard->m_mapKey[VK_F8] = ::user::e_key_f8;
       pkeyboard->m_mapKey[VK_F9] = ::user::e_key_f9;
       pkeyboard->m_mapKey[VK_F10] = ::user::e_key_f10;
       pkeyboard->m_mapKey[VK_F11] = ::user::e_key_f11;
       pkeyboard->m_mapKey[VK_F12] = ::user::e_key_f12;
       pkeyboard->m_mapKey[VK_LSHIFT] = ::user::e_key_left_shift;
       pkeyboard->m_mapKey[VK_RSHIFT] = ::user::e_key_right_shift;
       pkeyboard->m_mapKey[VK_LCONTROL] = ::user::e_key_left_control;
       pkeyboard->m_mapKey[VK_RCONTROL] = ::user::e_key_right_control;
       pkeyboard->m_mapKey[VK_LMENU] = ::user::e_key_left_alt;
       pkeyboard->m_mapKey[VK_RMENU] = ::user::e_key_right_alt;

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


   void windowing::lock_set_foreground_window(bool bLock)
   {

      if (bLock)
      {

         if (!LockSetForegroundWindow(LSFW_LOCK))
         {

            //return error_last_error;
            throw ::exception(error_null_pointer);

         }

      }
      else
      {

         if (!LockSetForegroundWindow(LSFW_UNLOCK))
         {

            //return error_last_error;
            throw ::exception(error_null_pointer);

         }

      }

      //return ::success;

   }


   void windowing::get_cursor_position(POINT_I32* ppoint)
   {

      ::GetCursorPos((POINT *) ppoint);

   }


   //#ifdef WINDOWS_DESKTOP
//
//                  CHOOSECOLOR cc;
//
//                  ::color::color crCustColors[16];
//
//                  // init-int this array did not affect the mouse problem
//                  // ::u32 idx ;
//                  // for (idx=0; idx<16; idx++) {
//                  // crCustColors[idx] = rgb(idx, idx, idx) ;
//                  // }
//
//                  ZeroMemory(&cc, sizeof(cc));
//                  cc.lStructSize = sizeof(CHOOSECOLOR);
//                  cc.rgbResult = rgb(0, 0, 0);
//                  cc.lpCustColors = (::color::color *) crCustColors;
//
//                  cc.Flags = CC_RGBINIT | CC_FULLOPEN;
//                  cc.hwndOwner = get_safe_handle() ; // this hangs parent, as well as me
//
//                  if (::ChooseColor(&cc))
//                  {
//
//                     m_eattribute |= ::user::rich_text::attribute_foreground;
//
//                     m_formata[0]->m_colorForeground = cc.rgbResult | (255 << 24);
//
//                     update_data(true);
//
//                  }
//#endif


//   bool user::modal_get_color(::user::interaction * puiOwner, ::color::hls & hls)
//   {
//
//#ifdef WINDOWS_DESKTOP
//
//      CHOOSECOLOR cc;
//      ::color::color crCustColors[16];
//
//      // init-int this array did not affect the mouse problem
//      // ::u32 idx ;
//      // for (idx=0; idx<16; idx++) {
//      // crCustColors[idx] = rgb(idx, idx, idx) ;
//      // }
//
//      ::color::color color(hls);
//
//      ZeroMemory(&cc, sizeof(cc));
//      cc.lStructSize = sizeof(CHOOSECOLOR);
//      cc.rgbResult = c.get_rgb();
//      cc.lpCustColors = (::color::color *)crCustColors;
//
//      cc.Flags = CC_RGBINIT | CC_FULLOPEN;
//      cc.hwndOwner = puiOwner->get_safe_handle(); // this hangs parent, as well as me
//
//      if (::ChooseColor(&cc))
//      {
//
//         c.set_COLORREF(cc.rgbResult | (255 << 24));
//
//         c.get_hls(hls);
//
//         return true;
//
//      }
//
//      return false;
//
//#else
//
//      auto puser = user();
//
//      puser->will_use_view_hint(COLORSEL_IMPACT);
//
//      auto pdocument = m_mapimpactsystem[COLORSEL_IMPACT]->open_document_file(puiOwner->get_application(), ::e_type_null, __visible(true));
//
//      __pointer(::userex::color_view) pimpact = pdocument->get_type_impact < ::userex::color_view >();
//
//      __pointer(::user::frame_window) pframe = pimpact->top_level_frame();
//
//      pframe->set_owner(puiOwner);
//
//      pframe->_001RunModalLoop();
//
//      hls = pimpact->m_hls;
//
//      return true;
//
//#endif
//
//
//   }

   
   string windowing::_get_window_text_timeout(oswindow oswindow, const ::duration& durationSendMessageMax)
   {

      DWORD_PTR dw = 0;

      //if (!SendMessageTimeoutW(hwnd, WM_GETTEXTLENGTH, 0, 0, SMTO_ABORTIFHUNG | SMTO_NOTIMEOUTIFNOTHUNG, 100, &dw))
      if (!SendMessageTimeoutW((HWND)oswindow, WM_GETTEXTLENGTH, 0, 0, SMTO_ABORTIFHUNG, (class ::wait) durationSendMessageMax, &dw))
      {

         return "";

      }

      if (!dw)
      {

         return "";

      }

      wstring wstr;

      auto pwsz = wstr.get_string_buffer(dw);

      if (!SendMessageTimeoutW((HWND)oswindow, WM_GETTEXT, dw + 1, (LPARAM)pwsz, SMTO_ABORTIFHUNG, (class ::wait) durationSendMessageMax, &dw))
      {

         return "";

      }

      wstr.release_string_buffer();

      return wstr;

   }


   bool windowing::_top_level_contains_name(string str)
   {

      return _top_level_contains_predicate([this, str](oswindow oswindow)
         {

            //PSEUDO-Code char sz[1024]; GetWindowTextA(sz,1024, oswindow); return !strcmp(sz, str.c_str());

            string strWindowText = _get_window_text_timeout(oswindow, 50_ms);

            return strWindowText.contains_ci(str);

         });

   }


   bool windowing::_visible_top_level_contains_name(string str)
   {

      return _top_level_contains_predicate([this, str](oswindow oswindow)
         {

            //PSEUDO-Code char sz[1024]; GetWindowTextA(sz,1024, oswindow); return !strcmp(sz, str.c_str());

            if (!::IsWindowVisible((HWND)oswindow))
            {

               return false;

            }

            string strWindowText = _get_window_text_timeout(oswindow, 50_ms);

            return strWindowText.contains_ci(str);

         });

   }


   bool windowing::_visible_top_level_contains_all_names(const string_array& stra)
   {

      return _top_level_contains_predicate([this, &stra](oswindow oswindow)
         {

            //PSEUDO-Code char sz[1024]; GetWindowTextA(sz,1024, oswindow); return !strcmp(sz, str.c_str());

            if (!::IsWindowVisible((HWND)oswindow))
            {

               return false;

            }

            string strWindowText = _get_window_text_timeout(oswindow, 50_ms);

            for (auto& str : stra)
            {

               if (!strWindowText.contains_ci(str))
               {

                  return false;

               }

            }

            return true;

         });

   }



} // namespace windowing_win32



