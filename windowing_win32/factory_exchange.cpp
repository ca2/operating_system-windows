#include "framework.h"


extern "C"
void windowing_win32_factory_exchange()
{

   create_factory < ::windowing_win32::windowing, ::windowing::windowing >();
   create_factory < ::windowing_win32::window, ::windowing::window >();
   create_factory < ::windowing_win32::display, ::windowing::display >();
   create_factory < ::windowing_win32::display >();
   create_factory < ::windowing_win32::buffer, ::graphics::graphics >();
   create_factory < ::windowing_win32::notify_icon, ::user::notify_icon >();
   create_factory < ::windowing_win32::cursor, ::windowing::cursor >();
   create_factory < ::windowing_win32::icon, ::windowing::icon >();
   create_factory < ::windowing_win32::shell, ::user::shell >();
   create_factory < ::windowing_win32::copydesk, ::user::copydesk >();
   create_factory < imm_client, ::user::text_composition_client >();

}