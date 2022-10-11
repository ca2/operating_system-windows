#include "framework.h"
#include "shell_open.h"
#include "node.h"
#include "interaction_impl.h"



//BEGIN_FACTORY(aura_windows)
//FACTORY_DEPENDENCY(apex_windows)
//FACTORY_DEPENDENCY(aura_windows_common)
//FACTORY_ITEM(::aura::windows_common::node)
//FACTORY_ITEM(::windows::interaction_impl)
//END_FACTORY()

__FACTORY_EXPORT void apex_windows_factory(::factory::factory * pfactory);


__FACTORY_EXPORT void aura_windows_common_factory(::factory::factory * pfactory);


__FACTORY_EXPORT void aura_windows_factory(::factory::factory * pfactory)
{

   aura_windows_common_factory(pfactory);

   apex_windows_factory(pfactory);

   //add_factory_item < ::windows::console, ::console::console >();
   //add_factory_item < ::windows::crypto, ::crypto::crypto >();
   //add_factory_item < ::windows::ip_enum, ::net::ip_enum >();


   //add_factory_item < ::windows::buffer, ::graphics::graphics >();
   //pfactory->add_factory_item < ::windows::interaction_impl, ::user::interaction_impl >();

   //add_factory_item < ::file::os_watcher, ::file::watcher >();
   //add_factory_item < ::file::os_watch, ::file::watch >();

   //add_factory_item < ::windows::copydesk, ::user::copydesk >();
   //add_factory_item < ::windows::shell_open, ::shell_open >();
   //add_factory_item < ::windows::interprocess_communication_base, ::inteprocess_channel::base >();
   //add_factory_item < ::windows::interprocess_caller, ::inteprocess::caller >();
   //add_factory_item < ::windows::interprocess_handler, ::inteprocess::handler >();
   //add_factory_item < ::windows::inteprocess_channel, ::inteprocess_channel::inteprocess_channel >();


   pfactory->add_factory_item < ::aura_windows::interaction_impl, ::user::interaction_impl >();

   pfactory->add_factory_item < ::aura_windows::node, ::acme::node >();

   //add_factory_item < ::windows::console, ::console::console >();
//add_factory_item < ::windows::crypto, ::crypto::crypto >();
//add_factory_item < ::windows::ip_enum, ::net::ip_enum >();


//add_factory_item < ::windows::buffer, ::graphics::graphics >();
   //add_factory_item < ::windows::interaction_impl, ::user::interaction_impl >();

   //add_factory_item < ::file::os_watcher, ::file::watcher >();
   //add_factory_item < ::file::os_watch, ::file::watch >();

   //add_factory_item < ::windows::copydesk, ::user::copydesk >();
   pfactory->add_factory_item < ::aura_windows::shell_open, ::shell_open >();
   //add_factory_item < ::windows::interprocess_communication_base, ::inteprocess_channel::base >();
   //add_factory_item < ::windows::interprocess_caller, ::inteprocess::caller >();
   //add_factory_item < ::windows::interprocess_handler, ::inteprocess::handler >();
   //add_factory_item < ::windows::inteprocess_channel, ::inteprocess_channel::inteprocess_channel >();



}




