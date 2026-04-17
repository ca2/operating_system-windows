//
// Created by camilo on 2026-04-06 10:57 <3ThomasBorregaardSørensen!!
//
#include "framework.h"
#include "subsystem.h"
#include "drawing/Icon.h"
#include "drawing/SolidBrush.h"
#include "gui/SystemMetrics.h"
#include "gui/Window.h"
#include "gui/Control.h"
#include "gui/Dialog.h"
#include "gui/CheckBox.h"
#include "gui/TextBox.h"
#include "gui/SpinControl.h"
#include "gui/Trackbar.h"
#include "gui/ComboBox.h"
#include "gui/NotifyIconWindow.h"
#include "gui/NotifyIcon.h"
#include "gui/Menu.h"
#include "gui/PaintWindow.h"
//#include "gui/OperatingSystemApplication.h"
#include "resource_loader.h"
#include "subsystem.h"


DECLARE_FACTORY(subsystem_windows);


IMPLEMENT_FACTORY(innate_subsystem_windows)
{

   subsystem_windows_factory(pfactory);

   pfactory->add_factory_item<::innate_subsystem_windows::subsystem, ::platform::subsystem>();

   pfactory->add_factory_item<::innate_subsystem_windows::SystemMetrics, ::innate_subsystem::SystemMetrics>();

   pfactory->add_factory_item<::innate_subsystem_windows::Window, ::innate_subsystem::WindowInterface>();

   pfactory->add_factory_item<::innate_subsystem_windows::Control, ::innate_subsystem::ControlInterface>();

   pfactory->add_factory_item<::innate_subsystem_windows::Dialog, ::innate_subsystem::DialogInterface>();

   pfactory->add_factory_item<::innate_subsystem_windows::CheckBox, ::innate_subsystem::CheckBoxInterface>();

   pfactory->add_factory_item<::innate_subsystem_windows::TextBox, ::innate_subsystem::TextBoxInterface>();

   pfactory->add_factory_item<::innate_subsystem_windows::SpinControl, ::innate_subsystem::SpinControlInterface>();

   pfactory->add_factory_item<::innate_subsystem_windows::Trackbar, ::innate_subsystem::TrackbarInterface>();

   pfactory->add_factory_item<::innate_subsystem_windows::ComboBox, ::innate_subsystem::ComboBoxInterface>();

   pfactory->add_factory_item<::innate_subsystem_windows::NotifyIconWindow, ::innate_subsystem::NotifyIconWindowInterface>();

   pfactory->add_factory_item<::innate_subsystem_windows::NotifyIcon, ::innate_subsystem::NotifyIconInterface>();

   pfactory->add_factory_item<::innate_subsystem_windows::Menu, ::innate_subsystem::MenuInterface>();

   pfactory->add_factory_item<::innate_subsystem_windows::Icon, ::innate_subsystem::IconInterface>();

   pfactory->add_factory_item<::innate_subsystem_windows::SolidBrush, ::innate_subsystem::SolidBrushInterface>();

   pfactory->add_factory_item<::innate_subsystem_windows::PaintWindow, ::innate_subsystem::PaintWindowInterface>();

   pfactory->add_factory_item<::innate_subsystem_windows::resource_loader, ::subsystem::resource_loader>();

   //pfactory->add_factory_item<::innate_subsystem_windows::OperatingSystemApplication,
     //                         ::subsystem::OperatingSystemApplicationInterface>();

}
