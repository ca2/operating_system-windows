//
// Created by camilo on 2026-04-04.
//
#include "framework.h"
#include "platform/subsystem.h"
#include "thread/GlobalMutex.h"
#include "thread/Thread.h"
#include "node/NamedPipe.h"
#include "node/OperatingSystem.h"
#include "node/OperatingSystemApplication.h"
#include "node/OperatingSystemHook.h"
#include "node/Pipe.h"
#include "node/Shell.h"
#include "node/SystemInformation.h"
#include "node/Clipboard.h"
#include "node/PipeClient.h"
#include "node/PipeImpersonatedThread.h"
#include "node/security/SecurityAttributes.h"
#include "node/PipeServer.h"
#include "node/Process.h"
#include "thread/DesktopSelector.h"
#include "thread/ZombieKiller.h"
#include "thread/ThreadCollector.h"


DECLARE_FACTORY(subsystem_bsd_sockets);
   

IMPLEMENT_FACTORY(subsystem_windows)
{

   subsystem_bsd_sockets_factory(pfactory);

   pfactory->add_factory_item<::subsystem_windows::GlobalMutex, ::subsystem::GlobalMutexInterface>();
   pfactory->add_factory_item<::subsystem_windows::Thread, ::subsystem::ThreadInterface>();
   pfactory->add_factory_item<::subsystem_windows::Shell, ::subsystem::Shell>();
   pfactory->add_factory_item<::subsystem_windows::SecurityAttributes, ::subsystem::SecurityAttributesInterface>();
   pfactory->add_factory_item<::subsystem_windows::PipeServer, ::subsystem::PipeServer>();
   pfactory->add_factory_item<::subsystem_windows::Process, ::subsystem::ProcessInterface>();
   pfactory->add_factory_item<::subsystem_windows::ZombieKiller, ::subsystem::ZombieKiller>();
   pfactory->add_factory_item<::subsystem_windows::PipeClient, ::subsystem::PipeClientInterface>();
   pfactory->add_factory_item<::subsystem_windows::NamedPipe, ::subsystem::NamedPipeInterface>();
   pfactory->add_factory_item<::subsystem_windows::Pipe, ::subsystem::PipeInterface>();
   pfactory->add_factory_item<::subsystem_windows::ThreadCollector, ::subsystem::ThreadCollector>();
   pfactory->add_factory_item<::subsystem_windows::PipeImpersonatedThread, ::subsystem::PipeImpersonatedThreadInterface>();


   pfactory->add_factory_item<::subsystem_windows::subsystem, ::subsystem::subsystem>();
   pfactory->add_factory_item<::subsystem_windows::SystemInformation, ::subsystem::SystemInformationInterface>();
   pfactory->add_factory_item<::subsystem_windows::OperatingSystem,
                              ::subsystem::OperatingSystem>();
   pfactory->add_factory_item<::subsystem_windows::OperatingSystemApplication, ::subsystem::OperatingSystemApplicationInterface>();
   pfactory->add_factory_item<::subsystem_windows::OperatingSystemHook,
                              ::subsystem::OperatingSystemHookInterface>();

   pfactory->add_factory_item<::subsystem_windows::DesktopSelector, ::subsystem::DesktopSelector>();
   pfactory->add_factory_item<::subsystem_windows::Clipboard, ::subsystem::ClipboardInterface>();

}


