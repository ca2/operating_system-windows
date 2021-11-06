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


extern "C"
void acme_windows_factory_exchange(::factory_map * pfactorymap);


extern "C"
void apex_windows_common_factory_exchange(::factory_map * pfactorymap);


extern "C"
void apex_windows_factory_exchange(::factory_map * pfactorymap)
{

   apex_windows_common_factory_exchange(pfactorymap);

   acme_windows_factory_exchange(pfactorymap);

   pfactorymap->create_factory < ::windows::dir_system, ::dir_system >();
   pfactorymap->create_factory < ::windows::file_system, ::file_system >();

   pfactorymap->create_factory < ::windows::dir_context, ::dir_context >();
   pfactorymap->create_factory < ::windows::file_context, ::file_context >();

   //create_factory < ::windows::stdio_file, ::file::text_file >();
   //create_factory < ::windows::file, ::file::file >();
   pfactorymap->create_factory < ::windows::os_context, ::os_context >();
   pfactorymap->create_factory < ::windows::pipe, ::operating_system::pipe >();
   pfactorymap->create_factory < ::windows::process, ::operating_system::process >();

   //create_factory < ::windows::console, ::console::console >();
   pfactorymap->create_factory < ::windows::crypto, ::crypto::crypto >();
   pfactorymap->create_factory < ::windows::ip_enum, ::net::ip_enum >();


   pfactorymap->create_factory < ::windows::interprocess_communication_base, ::interprocess_communication::base >();
   pfactorymap->create_factory < ::windows::interprocess_communication_rx, ::interprocess_communication::rx >();
   pfactorymap->create_factory < ::windows::interprocess_communication_tx, ::interprocess_communication::tx >();
   //create_factory < ::windows::interprocess_communication, ::interprocess_communication::interprocess_communication >();


   //create_factory < ::windows::buffer, ::graphics::graphics >();
   //create_factory < ::windows::interaction_impl, ::user::interaction_impl >();

   pfactorymap->create_factory < ::file::os_watcher, ::file::watcher >();
   pfactorymap->create_factory < ::file::os_watch, ::file::watch >();

   pfactorymap->create_factory < ::windows::file_context, ::file_context >();
   pfactorymap->create_factory < ::windows::service_handler, ::service_handler >();

   pfactorymap->create_factory < ::apex::windows::node, ::acme::node >();

   //create_factory < ::windows::copydesk, ::user::cop
   // 
   // 
   // ydesk >();
   ////create_factory < ::windows::shell, ::user::shell >();


}




