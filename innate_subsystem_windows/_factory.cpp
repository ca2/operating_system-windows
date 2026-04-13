//
// Created by camilo on 2026-04-06 10:57 <3ThomasBorregaardSørensen!!
//
#include "framework.h"
#include "subsystem.h"
#include "gui/SystemMetrics.h"
#include "gui/Window.h"
#include "resource_loader.h"

CLASS_DECL_INNATE_SUBSYSTEM_WINDOWS void innate_subsystem_win32_factory(::factory::factory * pfactory)
{

   //pfactory->add_factory_item<::windows::innate_subsystem_windows::subsystem, ::subsystem::subsystem>();

   pfactory->add_factory_item<::innate_subsystem_windows::SystemMetrics, ::innate_subsystem::SystemMetrics>();

   pfactory->add_factory_item<::innate_subsystem_windows::Window, ::innate_subsystem::Window>();

   pfactory->add_factory_item<::innate_subsystem_windows::resource_loader, ::subsystem::resource_loader>();

}
