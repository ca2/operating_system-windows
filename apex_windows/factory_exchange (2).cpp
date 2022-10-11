#include "framework.h"
#include "apex/operating_system.h"
#include "apex/node/windows/_windows.h"
#include "file_os_watcher.h"
//#include "apex/node/windows/buffer.h"
//#include "apex/os/console.h"
//#include "console.h"



//namespace apex
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
//} // namespace apex


void ([a-z0-9_]+)_factory(::factory::factory * pfactory)
{

   add_factory_item < ::windows::dir_system, ::dir_system >();
   add_factory_item < ::windows::file_system, ::file_system >();

   add_factory_item < ::windows::dir_context, ::dir_context >();
   add_factory_item < ::windows::file_context, ::file_context >();

   //add_factory_item < ::windows::stdio_file, ::file::text_file >();
   //add_factory_item < ::windows::file, ::file::file >();
   add_factory_item < ::windows::os_context, ::os_context >();
   add_factory_item < ::windows::pipe, ::operating_system::pipe >();
   add_factory_item < ::windows::process, ::operating_system::process >();

   //add_factory_item < ::windows::console, ::console::console >();
   add_factory_item < ::windows::crypto, ::crypto::crypto >();
   add_factory_item < ::windows::ip_enum, ::net::ip_enum >();


   add_factory_item < ::windows::interprocess_communication_base, ::inteprocess_channel::base >();
   add_factory_item < ::windows::interprocess_handler, ::inteprocess::handler >();
   add_factory_item < ::windows::interprocess_caller, ::inteprocess::caller >();
   //add_factory_item < ::windows::inteprocess_channel, ::inteprocess_channel::inteprocess_channel >();


   //add_factory_item < ::windows::buffer, ::graphics::graphics >();
   //add_factory_item < ::windows::interaction_impl, ::user::interaction_impl >();

   add_factory_item < ::file::os_watcher, ::file::watcher >();
   add_factory_item < ::file::os_watch, ::file::watch >();

   //add_factory_item < ::windows::copydesk, ::user::copydesk >();
   ////add_factory_item < ::windows::shell, ::user::shell >();


}




