// Created by camilo on 2021-01-30 <3ThomasBS_!!
#include "framework.h"


namespace windowing_win32
{


   windowing::windowing()
   {

   }

   windowing::~windowing()
   {

   }


   __pointer(::windowing::monitor) windowing::get_main_monitor()
   {

      const POINT_I32 pointZero = { 0,0 };

      return MonitorFromPoint(pointZero, MONITOR_DEFAULTTOPRIMARY);

   }


   virtual __pointer(::windowing::window) windowing::_wrap(HWND hwnd)
   {

      auto pwindow = __new(::windowing_win32::window(hwnd));

      return pwnd;

   }

   
   __pointer(::windowing::window) windowing::get_desktop_window()
   {

      HWND hwnd = ::GetDesktopWindow();

      return _wrap(hwnd);

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

      pbase->set(pmsg->hwnd, playeredUserPrimitive, (enum_message)pmsg->message, pmsg->wParam, pmsg->lParam);

      return pbase;

   }


} // namespace windowing_win32




