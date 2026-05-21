// Copyright (C) 2009,2010,2011,2012 GlavSoft LLC.
// All rights reserved.
//
//-------------------------------------------------------------------------
// This file is part of the T i g h t V N C software.  Please visit our Web site:
//
//                       http://www.t i g h t v n c.com/
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
#include "ThreadCollector.h"

//#include "critical_section_lock.h"

namespace subsystem_windows
{
   ThreadCollector::ThreadCollector()
   {
      resumeThread();
   }

   ThreadCollector::~ThreadCollector()
   {
      if (isThreadActive()) {
         setThreadToFinish();
         m_timer.set_happening() ;
         wait();
      }
      destroyAllThreads();
   }

   void ThreadCollector::onThreadMain()
   {
      while (!isThreadTerminating()) {
         deleteDeadThreads();
         m_timer.wait(50_ms);
      }
   }

   void ThreadCollector::addThread(::subsystem::Thread *pthread)
   {
      critical_section_lock l(&m_lockObj);
      m_threada.add(pthread);
   }

   void ThreadCollector::deleteDeadThreads()
   {
      critical_section_lock l(&m_lockObj);

      for(auto & pthread : m_threada)
      {
         if (!pthread->isThreadActive())
         {
            m_threada.erase(pthread);
            break;
         }
      }
   }

   void ThreadCollector::destroyAllThreads()
   {
      critical_section_lock l(&m_lockObj);

      auto iter = m_threada.begin();
      for (; iter != m_threada.end(); iter++) {
         (*iter)->setThreadToFinish();
      }
      for (iter = m_threada.begin(); iter != m_threada.end(); iter++) {
         (*iter)->waitThreadToFinish();
      }

      deleteDeadThreads();
   }

   const memsize ThreadCollector::Size()
   {
      return m_threada.size();
   }
} // namespace subsystem_windows


