#include "framework.h"


extern "C"
void windowing_win32_factory_exchange(::factory_map * pfactorymap)
{

   pfactorymap->create_factory < ::windowing_win32::windowing, ::windowing::windowing >();
   pfactorymap->create_factory < ::windowing_win32::window, ::windowing::window >();
   pfactorymap->create_factory < ::windowing_win32::display, ::windowing::display >();
   pfactorymap->create_factory < ::windowing_win32::display >();
   pfactorymap->create_factory < ::windowing_win32::buffer, ::graphics::graphics >();
   pfactorymap->create_factory < ::windowing_win32::notify_icon, ::user::notify_icon >();
   pfactorymap->create_factory < ::windowing_win32::cursor, ::windowing::cursor >();
   pfactorymap->create_factory < ::windowing_win32::icon, ::windowing::icon >();
   pfactorymap->create_factory < ::windowing_win32::shell, ::user::shell >();
   pfactorymap->create_factory < ::windowing_win32::copydesk, ::user::copydesk >();
   pfactorymap->create_factory < imm_client, ::user::text_composition_client >();

}