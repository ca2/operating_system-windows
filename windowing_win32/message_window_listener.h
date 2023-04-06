// From aura/user by camilo on 2023-04-06 19:53 <3ThomasBorregaardSorensen!!
#pragma once


#include "acme/primitive/primitive/particle.h"


namespace windowing_win32
{


   class CLASS_DECL_WINDOWING_WIN32 message_window_listener:
      virtual public ::particle
   {
   public:

      virtual void message_window_message_handler(::message::message * pmessage) { __UNREFERENCED_PARAMETER(pmessage); }

      virtual void install_message_window_routing(::channel* pchannel) {}

   };


} // namespace windowing_win32



