// Created by camilo on 2026-04-27 19:16 <3ThomasBorregaardSørensen!! Mummi!! bilbo!!
#include "platform.h"
#include "accessibility.h"
#include "main_window.h"
#include "acme/_operating_system.h"
#include "acme/operating_system/windows/windows.h"
#include "acme/operating_system/windows/window_util.h"


namespace accessibility_windows
{


   accessibility::accessibility()
   {

   }


   accessibility::~accessibility()
   {

   }


   ::pointer<::accessibility::application>
      accessibility::module_path_application(const ::scoped_string & scopedstr)
   {

      return ::accessibility::accessibility::module_path_application(scopedstr);

   }


   ::pointer_array < ::accessibility::main_window > accessibility::system_get_main_windows()
   {

      auto phwnda = ::transfer(::windows::get_top_level_windows(true, true));

      ::pointer_array < ::accessibility::main_window > mainwindowa;

      for (auto & hwnd : *phwnda)
      {

         auto pmainwindow = create_newø<::accessibility_windows::main_window>();

         pmainwindow->m_hwnd = hwnd;

         mainwindowa.add(pmainwindow);

      }

      return mainwindowa;

   }

} // namespace accessibility_windows




