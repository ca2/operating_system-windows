#include "framework.h"
#include "service_handler.h"
#include "ip_enum.h"
#include "node.h"
#include "interprocess_caller.h"
#include "interprocess_target.h"
#include "launcher.h"
#include "dir_system.h"
#include "dir_context.h"
#include "file_system.h"
#include "file_context.h"
#include "process.h"
#include "app_launcher.h"
#include "os_context.h"
#include "file_os_watcher.h"
#include "acme/parallelization/event.h"
#include "apex/filesystem/file/listener.h"
#include "apex/platform/launcher.h"
#include "apex/parallelization/service.h"
#include "apex/parallelization/service_handler.h"
#include "acme_windows/pipe.h"
#include "apex/platform/node.h"
#include "acme_windows/node.h"


__FACTORY_EXPORT void acme_windows_factory(::factory::factory * pfactory);


__FACTORY_EXPORT void apex_windows_common_factory(::factory::factory * pfactory);


IMPLEMENT_FACTORY(apex_windows)
{

   apex_windows_common_factory(pfactory);

   acme_windows_factory(pfactory);

   //add_factory_item < ::windows::stdio_file, ::file::text_file >();
   //add_factory_item < ::windows::file, ::file::file >();
   pfactory->add_factory_item < ::apex_windows::os_context, ::os_context >();
   //pfactory->add_factory_item < ::windows::pipe, ::operating_system::pipe >();
   pfactory->add_factory_item < ::apex_windows::process, ::operating_system::process >();

   //add_factory_item < ::windows::console, ::console::console >();
   //pfactory->add_factory_item < ::windows::crypto, ::crypto::crypto >();
   //pfactory->add_factory_item < ::windows::ip_enum, ::net::ip_enum >();


   //pfactory->add_factory_item < ::apex_windows::interprocess_communication_base, ::inteprocess_channel::base >();
   pfactory->add_factory_item < ::apex_windows::interprocess_caller, ::interprocess::caller >();
   pfactory->add_factory_item < ::apex_windows::interprocess_target, ::interprocess::target >();
   //add_factory_item < ::windows::inteprocess_channel, ::inteprocess_channel::inteprocess_channel >();


   //add_factory_item < ::windows::buffer, ::graphics::graphics >();
   //add_factory_item < ::windows::interaction_impl, ::user::interaction_impl >();

   pfactory->add_factory_item < ::apex_windows::os_watcher, ::file::watcher >();
   pfactory->add_factory_item < ::apex_windows::os_watch, ::file::watch >();


   pfactory->add_factory_item < ::apex_windows::app_launcher, ::apex::app_launcher >();

   //pfactory->add_factory_item < ::windows::file_context, ::file_context >();
   pfactory->add_factory_item < ::apex_windows::service_handler, ::service_handler >();

   pfactory->add_factory_item < ::apex_windows::node, ::acme::node >();

   //add_factory_item < ::windows::copydesk, ::user::cop
   // 
   // 
   // ydesk >();
   ////add_factory_item < ::windows::shell, ::user::shell >();


}




