// Copyright (C) 2011,2012 GlavSoft LLC.
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
#include "GuiThread.h"
#include "DesktopSelector.h"

namespace subsystem_windows
{
   GuiThread::GuiThread()
   : m_desk(0)
   {
      m_desk = MainSubsystem().desktop_selector()->getInputDesktop();
   }

   GuiThread::~GuiThread()
   {
      if (m_desk.m_u) {
          MainSubsystem().desktop_selector()->closeDesktop(m_desk);
      }
   }

   void GuiThread::initByDerived()
   {
       MainSubsystem().desktop_selector()->setDesktopToCurrentThread(m_desk);
      // If unsuccessful, desktop will be closed in destructor
      if ( MainSubsystem().desktop_selector()->closeDesktop(m_desk)) {
         m_desk = 0;
      }
   }
} // namespace subsystem_windows



