#include "framework.h"
#include "apex/operating_system.h"
#include "aura/node/windows/buffer.h"
#include "shell_open.h"
//#include "copydesk.h"
#include "interaction_impl.h"


//namespace aura
//{
//
//
//   namespace windows
//   {
//
//
//      factory_exchange::factory_exchange()
//      {
//
//
//
//         //::windows::shell::theWindowsShell.Initialize();
//
//      }
//
//
//      factory_exchange::~factory_exchange()
//      {
//
//      }
//
//
//   } // namespace windows
//
//
//} // namespace aura


void ([a-z0-9_]+)_factory(::factory::factory * pfactory)
{


   //add_factory_item < ::windows::console, ::console::console >();
   //add_factory_item < ::windows::crypto, ::crypto::crypto >();
   //add_factory_item < ::windows::ip_enum, ::net::ip_enum >();


   //add_factory_item < ::windows::buffer, ::graphics::graphics >();
   add_factory_item < ::windows::interaction_impl, ::windowing::window >();

   //add_factory_item < ::file::os_watcher, ::file::watcher >();
   //add_factory_item < ::file::os_watch, ::file::watch >();

   //add_factory_item < ::windows::copydesk, ::user::copydesk >();
   add_factory_item < ::windows::shell_open, ::shell_open >();
   //add_factory_item < ::windows::interprocess_communication_base, ::inteprocess_channel::base >();
   //add_factory_item < ::windows::interprocess_caller, ::inteprocess::caller >();
   //add_factory_item < ::windows::interprocess_handler, ::inteprocess::handler >();
   //add_factory_item < ::windows::inteprocess_channel, ::inteprocess_channel::inteprocess_channel >();

}




