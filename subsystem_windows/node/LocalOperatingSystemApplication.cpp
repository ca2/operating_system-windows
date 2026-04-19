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
// with this program; if not, w_rite to the Free Software Foundation, Inc.,
// 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
//-------------------------------------------------------------------------
//
#include "framework.h"
#include "subsystem_windows/_common_header.h"
#include "LocalOperatingSystemApplication.h"

//#include "remoting/remoting_common/util/winhdr.h"
#include "subsystem_windows/_common_header.h"

#include "subsystem/thread/DesktopSelector.h"

namespace subsystem_windows
{

   //LocalOperatingSystemApplication::LocalOperatingSystemApplication(HINSTANCE hInstance,
     //                                               const ::scoped_string &scopedstrwindowClassName)
   LocalOperatingSystemApplication::LocalOperatingSystemApplication()
   {

      initialize_operating_system_application();
      //initialize_operating_system_application(hInstance, scopedstrwindowClassName);
      HWINSTA winSta = 0;

      winSta = OpenWindowStation(L"WinSta0", TRUE, GENERIC_ALL);

      if (winSta == 0)
      {
         throw ::subsystem::SystemException();
      }

      if (SetProcessWindowStation(winSta) == 0)
      {
         CloseWindowStation(winSta);
         throw ::subsystem::SystemException();
      }

      CloseWindowStation(winSta);

      // FIXME: why we don't check returning values?
      //DesktopSelector::selectDesktop();
      MainSubsystem()->desktop_selector()->selectDesktop();
   }

   LocalOperatingSystemApplication::~LocalOperatingSystemApplication() {}


} // namespace subsystem_windows




