// Copyright (C) 2009,2010,2011,2012 GlavSoft LLC.
// All rights reserved.
//
//-------------------------------------------------------------------------
// This file is part of the TightVNC software.  Please visit our Web site:
//
//                       http://www.tightvnc.com/
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License along
// with this program; if not, write to the Free Software Foundation, Inc.,
// 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
//-------------------------------------------------------------------------
//
// Adapted by camilo on beginning of 2026-April <3ThomasBorregaardSorensen!!
//
#pragma once
//#define _TAB_CONTROL_H_

//#include "Control.h"
//#include "Tab.h"
//#include "TabContainer.h"

#include "innate_subsystem/TabControl.h"
#include "innate_subsystem_win32/_common_header.h"


namespace innate_subsystem_win32
{
   class CLASS_DECL_INNATE_SUBSYSTEM_WIN32 TabControl : public window_implementation<subsystem_apex::TabControlInterface>
   {
   public:
      TabControl();
      ~TabControl() override;

      //
      // Tab access members
      //

      subsystem_apex::TabContainer &getTabs() override;
      ::subsystem_apex::TabInterface *getTab(int index) override;
      void addTab(subsystem_apex::DialogInterface *dialog, const char *caption) override;
      void showTab(int index) override;
      void showTab(subsystem_apex::DialogInterface *dialog) override;
      void deleteAllTabs() override;
      void removeTab(int index) override;

      //
      // Return selected tab number
      //

      int getSelectedTabIndex() override;

      //
      // Tab work rect methods
      //

      void adjustRect(::int_rectangle &rect) override;

   //protected:
      ::subsystem_apex::TabContainer m_tabContainer;
   };
} // namespace innate_subsystem_win32
