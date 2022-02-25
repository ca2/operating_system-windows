#include "framework.h"
#include "apex/operating_system.h"
#include "file_os_watcher.h"
#include "apex/platform/launcher.h"
#include "launcher.h"
#include "dir_system.h"
#include "dir_context.h"
#include "file_system.h"
#include "file_context.h"
#include "process.h"
#include "os_context.h"
#include "apex/parallelization/service.h"
#include "apex/parallelization/service_handler.h"
#include "service_handler.h"
#include "acme_windows/pipe.h"
#include "crypto.h"
#include "ip_enum.h"
#include "interprocess_communication.h"
#include "apex/platform/node.h"
#include "acme_windows/node.h"
#include "node.h"


//BEGIN_FACTORY(apex_windows)
//FACTORY_DEPENDENCY(apex_windows_common)
//FACTORY_DEPENDENCY(acme_windows)
//FACTORY_ITEM(::windows::dir_context)
//FACTORY_ITEM(::windows::dir_system)
//FACTORY_ITEM(::windows::file_context)
//FACTORY_ITEM(::windows::file_system)
//FACTORY_ITEM(::windows::os_context)
//FACTORY_ITEM(::windows::process)
//FACTORY_ITEM(::file::os_watch)
//FACTORY_ITEM(::file::os_watcher)
//END_FACTORY()


__FACTORY_EXPORT void acme_windows_factory(::factory::factory * pfactory);


__FACTORY_EXPORT void apex_windows_common_factory(::factory::factory * pfactory);


__FACTORY_EXPORT void apex_windows_factory(::factory::factory * pfactory)
{

   apex_windows_common_factory(pfactory);

   acme_windows_factory(pfactory);

   pfactory->add_factory_item < ::windows::dir_system, ::dir_system >();
   pfactory->add_factory_item < ::windows::file_system, ::file_system >();

   pfactory->add_factory_item < ::windows::dir_context, ::dir_context >();
   pfactory->add_factory_item < ::windows::file_context, ::file_context >();

   //add_factory_item < ::windows::stdio_file, ::file::text_file >();
   //add_factory_item < ::windows::file, ::file::file >();
   pfactory->add_factory_item < ::windows::os_context, ::os_context >();
   //pfactory->add_factory_item < ::windows::pipe, ::operating_system::pipe >();
   pfactory->add_factory_item < ::windows::process, ::operating_system::process >();

   //add_factory_item < ::windows::console, ::console::console >();
   //pfactory->add_factory_item < ::windows::crypto, ::crypto::crypto >();
   //pfactory->add_factory_item < ::windows::ip_enum, ::net::ip_enum >();


   pfactory->add_factory_item < ::windows::interprocess_communication_base, ::interprocess_communication::base >();
   pfactory->add_factory_item < ::windows::interprocess_communication_rx, ::interprocess_communication::rx >();
   pfactory->add_factory_item < ::windows::interprocess_communication_tx, ::interprocess_communication::tx >();
   //add_factory_item < ::windows::interprocess_communication, ::interprocess_communication::interprocess_communication >();


   //add_factory_item < ::windows::buffer, ::graphics::graphics >();
   //add_factory_item < ::windows::interaction_impl, ::user::interaction_impl >();

   pfactory->add_factory_item < ::file::os_watcher, ::file::watcher >();
   pfactory->add_factory_item < ::file::os_watch, ::file::watch >();

   //pfactory->add_factory_item < ::windows::file_context, ::file_context >();
   pfactory->add_factory_item < ::windows::service_handler, ::service_handler >();

   //pfactory->add_factory_item < ::apex::windows::node, ::acme::node >();

   //add_factory_item < ::windows::copydesk, ::user::cop
   // 
   // 
   // ydesk >();
   ////add_factory_item < ::windows::shell, ::user::shell >();


}




