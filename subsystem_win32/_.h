//
// Created by camilo on 2026-04-06 06:16 <3ThomasBorregaardSørensen!!
//

#pragma once


#include "acme/_.h"
#include "acme_windows/_.h"


#ifndef ACME_OPERATING_SYSTEM
#undef USUAL_OPERATING_SYSTEM_SUPPRESSIONS
#include "acme/_operating_system.h"
#endif



#if defined(_subsystem_win32_project)
#define CLASS_DECL_SUBSYSTEM_WIN32  CLASS_DECL_EXPORT
#else
#define CLASS_DECL_SUBSYSTEM_WIN32  CLASS_DECL_IMPORT
#endif




namespace subsystem_win32
{

   class File;

   class DynamicLibrary;

   class WindowsCommandLineArguments;

   class WindowsHookEventListener;

   class WTS;

   class PipeServer;

} // namespace subsystem_win32



