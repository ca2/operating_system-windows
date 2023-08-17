#include "framework.h"
#include "acme/platform/node.h"
#include "acme/filesystem/filesystem/acme_directory.h"
#include "node.h"
#include "dir_context.h"
#include "dir_system.h"
#include "file_context.h"
#include "file_system.h"
#include "file_watcher.h"
#include "application.h"
#include "main_window.h"
#include "acme_directory.h"
#include "acme_path.h"
#include "acme_file.h"
#include "acme/platform/acme.h"
#include "acme/filesystem/filesystem/acme_path.h"
#include "acme/platform/serial.h"
#include "serial.h"
#include "file_memory_map.h"
#include "pipe.h"
#include "console.h"
//#include "file.h"
//#include "acme/operating_system.h"


//BEGIN_FACTORY(acme_windows)
//FACTORY_DEPENDENCY(acme_windows_common)
//FACTORY_ITEM(::windows::acme_directory)
//FACTORY_ITEM(::windows::acme_file)
//FACTORY_ITEM(::windows::acme_path)
//FACTORY_ITEM(::acme::windows::node)
//FACTORY_ITEM(::windows::file)
//END_FACTORY()


////void CLASS_DECL_ACME_WINDOWS __cdecl _ca2_purecall();
//
//
__FACTORY_IMPORT void acme_windows_common_factory(::factory::factory* pfactory);




IMPLEMENT_FACTORY(acme_windows)
{

   acme_windows_common_factory(pfactory);

   //_set_purecall_handler(_ca2_purecall);

   //pfactory->add_factory_item < ::windows::dir_system, ::dir_system >();
   //pfactory->add_factory_item < ::windows::file_system, ::file_system >();

   //pfactory->add_factory_item < ::windows::dir_context, ::dir_context >();
   //pfactory->add_factory_item < ::windows::file_context, ::file_context >();

   //add_factory_item < ::windows::stdio_file, ::file::text_file >();
   //pfactory->add_factory_item < ::windows::file, ::file::file >();
   //pfactory->add_factory_item < ::windows::os_context, ::os_context >();
   //pfactory->add_factory_item < ::windows::pipe, ::operating_system::pipe >();
   //pfactory->add_factory_item < ::windows::process, ::operating_system::process >();

   ////add_factory_item < ::windows::console, ::console::console >();
   //pfactory->add_factory_item < ::windows::crypto, ::crypto::crypto >();
   //pfactory->add_factory_item < ::windows::ip_enum, ::net::ip_enum >();

   pfactory->add_factory_item < ::acme_windows::node, ::acme::node >();
   pfactory->add_factory_item < ::acme_windows::acme_directory, ::acme_directory >();
   pfactory->add_factory_item < ::acme_windows::acme_file, ::acme_file >();
   pfactory->add_factory_item < ::acme_windows::acme_path, ::acme_path >();



   pfactory->add_factory_item < ::acme_windows::dir_system, ::dir_system >();
   pfactory->add_factory_item < ::acme_windows::file_system, ::file_system >();

   pfactory->add_factory_item < ::acme_windows::dir_context, ::dir_context >();
   pfactory->add_factory_item < ::acme_windows::file_context, ::file_context >();

   pfactory->add_factory_item < ::acme_windows::file_watcher, ::file::watcher >();
   pfactory->add_factory_item < ::acme_windows::file_watch, ::file::watch >();

   //pfactory->add_factory_item < ::windows::interprocess_communication_base, ::inteprocess_channel::base >();
   //pfactory->add_factory_item < ::windows::interprocess_handler, ::inteprocess::handler >();
   //pfactory->add_factory_item < ::windows::interprocess_caller, ::inteprocess::caller >();
   //add_factory_item < ::windows::inteprocess_channel, ::inteprocess_channel::inteprocess_channel >();


   //add_factory_item < ::windows::buffer, ::graphics::graphics >();
   //add_factory_item < ::windows::interaction_impl, ::user::interaction_impl >();

   //pfactory->add_factory_item < ::file::os_watcher, ::file::watcher >();
   //pfactory->add_factory_item < ::file::os_watch, ::file::watch >();

   //pfactory->add_factory_item < ::windows::file_context, ::file_context >();
   //add_factory_item < ::windows::copydesk, ::user::cop
   // 
   // 
   // ydesk >();
   ////add_factory_item < ::windows::shell, ::user::shell >();

   pfactory->add_factory_item < ::acme_windows::serial, ::serial::serial >();
   pfactory->add_factory_item < ::acme_windows::file_memory_map, ::file::memory_map >();

   pfactory->add_factory_item < ::acme_windows::pipe, ::operating_system::pipe >();
   //pfactory->add_factory_item < ::windows::file, ::file::file >();
   pfactory->add_factory_item < ::acme_windows::console, ::console::console >();

   pfactory->add_factory_item < ::acme_windows::application, ::operating_system::application >();
   pfactory->add_factory_item < ::acme_windows::main_window, ::operating_system::main_window >();

   //pfactory->add_factory_item < ::windows::dir_system, ::dir_system >();
   //pfactory->add_factory_item < ::windows::file_system, ::file_system >();

   //pfactory->add_factory_item < ::windows::dir_context, ::dir_context >();
   //pfactory->add_factory_item < ::windows::file_context, ::file_context >();

   //pfactory->add_factory_item < ::windows::stdio_file, ::file::text_file >();
   //pfactory->add_factory_item < ::windows::os_context, ::os_context >();
   //pfactory->add_factory_item < ::windows::future, ::operating_system::process >();

   //pfactory->add_factory_item < ::windows::crypto, ::crypto::crypto >();
   //pfactory->add_factory_item < ::windows::ip_enum, ::net::ip_enum >();

   //pfactory->add_factory_item < ::windows::file_memory_map, ::file::memory_map >();
   //pfactory->add_factory_item < ::windows::buffer, ::graphics::graphics >();
   //pfactory->add_factory_item < ::windows::interaction_impl, ::user::interaction_impl >();

   //pfactory->add_factory_item < ::file::os_watcher, ::file::watcher >();
   //pfactory->add_factory_item < ::file::os_watch, ::file::watch >();

   //pfactory->add_factory_item < ::windows::copydesk, ::user::copydesk >();
   //pfactory->add_factory_item < ::windows::shell, ::user::shell >();

}



