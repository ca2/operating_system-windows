//
// Created by camilo on 2026-04-06 06:16 <3ThomasBorregaardSørensen!!
//

#pragma once


#include "acme_windows/_.h"
#include "subsystem_bsd_sockets/_.h"



#ifndef ACME_OPERATING_SYSTEM
#undef USUAL_OPERATING_SYSTEM_SUPPRESSIONS
#include "acme/_operating_system.h"
#endif



#if defined(_subsystem_windows_project)
#define CLASS_DECL_SUBSYSTEM_WINDOWS  CLASS_DECL_EXPORT
#else
#define CLASS_DECL_SUBSYSTEM_WINDOWS  CLASS_DECL_IMPORT
#endif




namespace subsystem_windows
{


   class File;

   class DynamicLibrary;

   //class CommandLineArguments;

   class WindowsHookEventListener;

   class WTS;

   class PipeServer;

   //class WindowMessageHandler;


} // namespace subsystem_windows



