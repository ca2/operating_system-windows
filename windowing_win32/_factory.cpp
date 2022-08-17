#include "framework.h"
#include "_windows.h"


//BEGIN_FACTORY(windowing_win32)
//FACTORY_DEPENDENCY(aura_windows)
//FACTORY_ITEM(::windowing_win32::windowing)
//FACTORY_ITEM(::windowing_win32::window)
//FACTORY_ITEM(::windowing_win32::display)
//FACTORY_ITEM(::windowing_win32::buffer)
//FACTORY_ITEM(::windowing_win32::notify_icon)
//FACTORY_ITEM(::windowing_win32::cursor)
//FACTORY_ITEM(::windowing_win32::icon)
//FACTORY_ITEM(::windowing_win32::shell)
//FACTORY_ITEM(::windowing_win32::copydesk)
//FACTORY_ITEM(imm_client)
//FACTORY_ITEM(::windowing_win32::keyboard)
//FACTORY_ITEM(::windowing_win32::node)
//END_FACTORY()



__FACTORY_EXPORT void aura_windows_factory(::factory::factory * pfactory);


__FACTORY_EXPORT void windowing_win32_factory(::factory::factory * pfactory)
{

   aura_windows_factory(pfactory);

   pfactory->add_factory_item < ::windowing_win32::windowing, ::windowing::windowing >();
   pfactory->add_factory_item < ::windowing_win32::window, ::windowing::window >();
   pfactory->add_factory_item < ::windowing_win32::display, ::windowing::display >();
   pfactory->add_factory_item < ::windowing_win32::display >();
   pfactory->add_factory_item < ::windowing_win32::buffer, ::graphics::graphics >();
   pfactory->add_factory_item < ::windowing_win32::notify_icon, ::user::notify_icon >();
   pfactory->add_factory_item < ::windowing_win32::cursor, ::windowing::cursor >();
   pfactory->add_factory_item < ::windowing_win32::icon, ::windowing::icon >();
   pfactory->add_factory_item < ::windowing_win32::shell, ::user::shell >();
   pfactory->add_factory_item < ::windowing_win32::copydesk, ::user::copydesk >();
   pfactory->add_factory_item < imm_client, ::user::text_composition_client >();

   pfactory->add_factory_item < ::windowing_win32::keyboard, ::windowing::keyboard >();

   pfactory->add_factory_item < ::windowing_win32::monitor, ::windowing::monitor >();

   //pfactory->add_factory_item < ::windowing_win32::node, ::acme::node >();

   pfactory->add_factory_item < ::windowing_win32::devices, ::hardware::devices >();

   pfactory->add_factory_item < ::windowing_win32::desktop_environment, ::windowing::desktop_environment >();

}
