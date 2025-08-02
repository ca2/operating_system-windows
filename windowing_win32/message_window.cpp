// From aura/user by camilo on 2023-04-06 19:53 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "message_window.h"
#include "apex/user/user/message.h"


namespace windowing_win32
{


   message_window::message_window()
   {

      // m_plistener = nullptr;

   }


   message_window::~message_window()
   {

   }


   void message_window::create_message_window(const ::scoped_string & scopedstrName,::user::interaction_listener * pinteractionlistener)
   {

      m_pinteractionlistener = pinteractionlistener;

      m_bMessageOnlyWindow = true;

      m_strWindowText2 = scopedstrName;

      //create_host(e_parallelization_synchronous);

      create_window();

      //if (!create_host())
      //{

      //   return false;

      //}

      if (m_pinteractionlistener)
      {

         m_pinteractionlistener->install_interaction_message_routing(this);

      }

      //return true;



   }


   void message_window::message_handler(::message::message * pmessage)
   {

      message_window_message_handler(pmessage);

      if (pmessage->m_bRet)
      {

         return;

      }

      ::user::interaction::message_handler(pmessage);

   }


   void message_window::message_window_message_handler(::message::message * pmessage)
   {

      if(m_pinteractionlistener != nullptr)
      {

         m_pinteractionlistener->interaction_message_handler(pmessage);

      }

   }


   bool message_window::message_window_is_initialized()
   {

      return is_window();

   }


   void message_window::message_window_set_timer(uptr uId, const class time & time)
   {

      set_timer(uId, time, nullptr);

   }


   void message_window::message_window_del_timer(uptr uId)
   {

      kill_timer(uId);

   }


   void message_window::message_window_post_message(::enum_message emessage, ::wparam wparam, ::lparam lparam)
   {

      post_message(emessage, wparam, lparam);

   }


   lresult message_window::message_window_send_message(::enum_message emessage, ::wparam wparam, ::lparam lparam)
   {

      return send_message(emessage, wparam, lparam);

   }


   void message_window::message_window_destroy()
   {

      destroy_window();

   }


   void * message_window::message_window_get_os_handle()
   {

      return get_os_data();

   }


} // namespace windowing_win32



