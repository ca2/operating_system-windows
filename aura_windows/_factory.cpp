#include "framework.h"


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
   //add_factory_item < ::windows::interprocess_communication_base, ::interprocess_communication::base >();
   //add_factory_item < ::windows::interprocess_communication_tx, ::interprocess_communication::tx >();
   //add_factory_item < ::windows::interprocess_communication_rx, ::interprocess_communication::rx >();
   //add_factory_item < ::windows::interprocess_communication, ::interprocess_communication::interprocess_communication >();


   pfactory->add_factory_item < ::windows::interaction_impl, ::user::interaction_impl >();

   pfactory->add_factory_item < ::aura::windows::node, ::acme::node >();


}



