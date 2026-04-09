//
// Created by camilo on 2026-04-04.
//
#include "framework.h"
#include "subsystem.h"
#include "thread/GlobalMutex.h"
#include "node/Shell.h"

//namespace subsystem_win32
//{

CLASS_DECL_EXPORT void subsystem_win32_factory(::factory::factory * pfactory)
{

   pfactory->add_factory_item<::subsystem_win32::GlobalMutex, ::subsystem::GlobalMutex>();
   pfactory->add_factory_item<::subsystem_win32::Shell, ::subsystem::Shell>();


   pfactory->add_factory_item<::subsystem_win32::subsystem, ::subsystem::subsystem>();

}


//} // namespace subsystem_win32

