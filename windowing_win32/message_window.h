// From aura/user by camilo on 2023-04-06 19:53 <3ThomasBorregaardSorensen!!
#pragma once


#include "aura/user/user/interaction_listener.h"
#include "aura/user/user/interaction.h"


namespace windowing_win32
{


   class CLASS_DECL_WINDOWING_WIN32 message_window :
      virtual public ::user::interaction_listener,
      virtual public ::user::interaction
   {
   public:


      ::pointer<::user::interaction_listener>     m_pinteractionlistener;


      message_window();
      ~message_window() override;


      virtual void create_message_window(const ::string & pszName,::user::interaction_listener * plistener = nullptr);

      void message_handler(::message::message * pmessage) override;

      virtual void message_window_message_handler(::message::message * pmessage);

      virtual bool message_window_is_initialized();

      virtual void message_window_set_timer(uptr uId, const class time & time);

      virtual void message_window_post_message(::enum_message emessage, ::wparam wparam = {}, ::lparam lparam = {});

      virtual lresult message_window_send_message(::enum_message emessage, ::wparam wparam = {}, ::lparam lparam = {});

      virtual void message_window_del_timer(uptr uId);

      virtual void message_window_destroy();

      virtual void * message_window_get_os_handle();

   };


   typedef ::pointer<message_window>message_window_pointer;


} // namespace windowing_win32



