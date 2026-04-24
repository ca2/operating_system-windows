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
#include "SessionChangesWatcher.h"
#include "subsystem_windows/node/WTS.h"
#include "subsystem_windows/platform/subsystem.h"

namespace subsystem_windows
{

   // SessionChangesWatcher::SessionChangesWatcher(AnEventListener *extSessionChangesListener,
   //                                              ::subsystem::LogWriter *log)
   //: m_extSessionChangesListener(extSessionChangesListener),
   //  m_plogwriter(log)
   //{
   //  ProcessIdToSessionId(GetCurrentProcessId(), &m_baseSessionId);
   //  resume();
   //}

   SessionChangesWatcher::SessionChangesWatcher()
   {


   }

   SessionChangesWatcher::~SessionChangesWatcher()
   {
      terminate();
      wait();
   }


     void SessionChangesWatcher::start_SessionChangesWatcher(const ::procedure &procedureSessionChanged,
                                                ::subsystem::LogWriter *plogwriter) 
   {
        m_procedureSessionChanged = procedureSessionChanged;
      m_plogwriter = plogwriter;
      ProcessIdToSessionId(GetCurrentProcessId(), &m_baseSessionId);
      resume();
   }


   void SessionChangesWatcher::execute()
   {
      DWORD prevSession = m_baseSessionId;
      bool isRdp = WindowsSubsystem().WTS().SessionIsRdpSession(prevSession, m_plogwriter);
      ::string prevDeskName, currDeskName;
      prevDeskName = MainSubsystem().DesktopSelector().getThreadDesktopName();

      while (!isTerminating())
      {
         DWORD currSessionId = prevSession;
         if (!isRdp)
         {
            currSessionId = WindowsSubsystem().WTS().getActiveConsoleSessionId(m_plogwriter);
         }
         bool sessionChanged = prevSession != currSessionId;
         bool desktopInfoIsAvailable = MainSubsystem().DesktopSelector().getCurrentDesktopName(currDeskName);
         bool desktopChanged = currDeskName != prevDeskName;
         if (sessionChanged || desktopChanged || !desktopInfoIsAvailable)
         {
            m_plogwriter->debug("Session or desktop has been changed."
                                " The process session = %u, current session = %u"
                                " The process desktop = {}, current desktop = {}",
                                (unsigned int)prevSession, (unsigned int)currSessionId, prevDeskName, currDeskName);
            prevSession = currSessionId;
            prevDeskName = currDeskName;
            m_procedureSessionChanged();
            terminate();
         }
         else
         {
            // FIXME: Use ::happening instead of Sleep().
            preempt(100_ms);
         }
      }
   }


} // namespace subsystem_windows
 