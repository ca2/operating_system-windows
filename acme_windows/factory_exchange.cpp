#include "framework.h"
#include "acme/operating_system.h"
#include "acme/platform/node.h"
#include "acme/filesystem/filesystem/acme_dir.h"
#include "acme.h"
#include "acme_dir.h"
#include "acme/filesystem/filesystem/acme_path.h"
#include "acme_path.h"

void CLASS_DECL_ACME_WINDOWS __cdecl _ca2_purecall();


void acme_windows_factory_exchange(::factory_map * pfactorymap)
{

   _set_purecall_handler(_ca2_purecall);

   //pfactorymap->create_factory < ::windows::dir_system, ::dir_system >();
   //pfactorymap->create_factory < ::windows::file_system, ::file_system >();

   //pfactorymap->create_factory < ::windows::dir_context, ::dir_context >();
   //pfactorymap->create_factory < ::windows::file_context, ::file_context >();

   //create_factory < ::windows::stdio_file, ::file::text_file >();
   //create_factory < ::windows::file, ::file::file >();
   //pfactorymap->create_factory < ::windows::os_context, ::os_context >();
   //pfactorymap->create_factory < ::windows::pipe, ::process::pipe >();
   //pfactorymap->create_factory < ::windows::process, ::process::process >();

   ////create_factory < ::windows::console, ::console::console >();
   //pfactorymap->create_factory < ::windows::crypto, ::crypto::crypto >();
   //pfactorymap->create_factory < ::windows::ip_enum, ::net::ip_enum >();

   pfactorymap->create_factory < ::windows::acme, ::acme::node >();
   pfactorymap->create_factory < ::windows::acme_dir, ::acme_dir >();
   pfactorymap->create_factory < ::windows::acme_path, ::acme_path >();

   //pfactorymap->create_factory < ::windows::interprocess_communication_base, ::interprocess_communication::base >();
   //pfactorymap->create_factory < ::windows::interprocess_communication_rx, ::interprocess_communication::rx >();
   //pfactorymap->create_factory < ::windows::interprocess_communication_tx, ::interprocess_communication::tx >();
   //create_factory < ::windows::interprocess_communication, ::interprocess_communication::interprocess_communication >();


   //create_factory < ::windows::buffer, ::graphics::graphics >();
   //create_factory < ::windows::interaction_impl, ::user::interaction_impl >();

   //pfactorymap->create_factory < ::file::os_watcher, ::file::watcher >();
   //pfactorymap->create_factory < ::file::os_watch, ::file::watch >();

   //pfactorymap->create_factory < ::windows::file_context, ::file_context >();
   //create_factory < ::windows::copydesk, ::user::cop
   // 
   // 
   // ydesk >();
   ////create_factory < ::windows::shell, ::user::shell >();


}




