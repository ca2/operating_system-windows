//
// Created by camilo on 2026-04-06 10:57 <3ThomasBorregaardSørensen!!
//
#include "framework.h"
#include "subsystem.h"
#include "SystemMetrics.h"
#include "Window.h"
#include "resource_loader.h"

CLASS_DECL_INNATE_SUBSYSTEM_WIN32 void innate_subsystem_win32_factory(::factory::factory * pfactory)
{

   //pfactory->add_factory_item<::windows::innate_subsystem_win32::subsystem, ::subsystem::subsystem>();

   pfactory->add_factory_item<::innate_subsystem_win32::SystemMetrics, ::subsystem_apex::SystemMetrics>();

   pfactory->add_factory_item<::innate_subsystem_win32::Window, ::subsystem_apex::Window>();

   pfactory->add_factory_item<::innate_subsystem_win32::resource_loader, ::subsystem::resource_loader>();

}
