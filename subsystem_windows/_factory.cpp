//
// Created by camilo on 2026-04-04.
//
#include "framework.h"
#include "subsystem.h"
#include "thread/GlobalMutex.h"
#include "node/Shell.h"
#include "node/SystemInformation.h"
#include "thread/DesktopSelector.h"


CLASS_DECL_IMPORT void subsystem_bsd_sockets_factory(::factory::factory *pfactory);
   

CLASS_DECL_EXPORT void subsystem_win32_factory(::factory::factory * pfactory)
{

   subsystem_bsd_sockets_factory(pfactory);

   pfactory->add_factory_item<::subsystem_win32::GlobalMutex, ::subsystem::GlobalMutex>();
   pfactory->add_factory_item<::subsystem_win32::Shell, ::subsystem::Shell>();


   pfactory->add_factory_item<::subsystem_win32::subsystem, ::subsystem::subsystem>();
   pfactory->add_factory_item<::subsystem_win32::SystemInformation, ::subsystem::SystemInformationInterface>();

   pfactory->add_factory_item<::subsystem_win32::DesktopSelector, ::subsystem::DesktopSelector>();

}


