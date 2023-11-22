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


   void message_window::create_message_window(const ::string & pszName,::user::interaction_listener * pinteractionlistener)
   {

      m_pinteractionlistener = pinteractionlistener;

      m_bMessageWindow = true;

      m_strWindowText2 = pszName;

      //create_host(e_parallelization_synchronous);

      create_host();

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


   void message_window::message_handler(::user::message * pusermessage)
   {

      message_window_message_handler(pusermessage);

      if (pusermessage->m_bRet)
      {

         return;

      }

      ::user::interaction::message_handler(pusermessage);

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

      SetTimer(uId, time, nullptr);

   }


   void message_window::message_window_del_timer(uptr uId)
   {

      KillTimer(uId);

   }


   void message_window::message_window_post_message(const ::atom & atom,wparam wparam,lparam lparam)
   {

      post_message(atom, wparam, lparam);

   }


   lresult message_window::message_window_send_message(const ::atom& atom,wparam wparam,lparam lparam)
   {

      return send_message(atom, wparam, lparam);

   }


   void message_window::message_window_destroy()
   {

      start_destroying_window();

   }


   void * message_window::message_window_get_os_handle()
   {

      return get_os_data();

   }


} // namespace windowing_win32



