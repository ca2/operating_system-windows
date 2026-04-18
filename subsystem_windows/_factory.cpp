//
// Created by camilo on 2026-04-04.
//
#include "framework.h"
#include "subsystem.h"
#include "thread/GlobalMutex.h"
#include "thread/Thread.h"
#include "node/OperatingSystemApplication.h"
#include "node/OperatingSystemHook.h"
#include "node/Shell.h"
#include "node/SystemInformation.h"
#include "node/Clipboard.h"
#include "thread/DesktopSelector.h"


DECLARE_FACTORY(subsystem_bsd_sockets);
   

IMPLEMENT_FACTORY(subsystem_windows)
{

   subsystem_bsd_sockets_factory(pfactory);

   pfactory->add_factory_item<::subsystem_windows::GlobalMutex, ::subsystem::GlobalMutex>();
   pfactory->add_factory_item<::subsystem_windows::Thread, ::subsystem::ThreadInterface>();
   pfactory->add_factory_item<::subsystem_windows::Shell, ::subsystem::Shell>();



   pfactory->add_factory_item<::subsystem_windows::subsystem, ::subsystem::subsystem>();
   pfactory->add_factory_item<::subsystem_windows::SystemInformation, ::subsystem::SystemInformationInterface>();
   pfactory->add_factory_item<::subsystem_windows::OperatingSystemApplication, ::subsystem::OperatingSystemApplicationInterface>();
   pfactory->add_factory_item<::subsystem_windows::OperatingSystemHook,
                              ::subsystem::OperatingSystemHookInterface>();

   pfactory->add_factory_item<::subsystem_windows::DesktopSelector, ::subsystem::DesktopSelector>();
   pfactory->add_factory_item<::subsystem_windows::Clipboard, ::subsystem::ClipboardInterface>();

}


