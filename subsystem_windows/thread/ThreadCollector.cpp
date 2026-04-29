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
#include "ThreadCollector.h"

//#include "critical_section_lock.h"

namespace subsystem_windows
{
   ThreadCollector::ThreadCollector()
   {
      resume();
   }

   ThreadCollector::~ThreadCollector()
   {
      if (isActive()) {
         terminate();
         m_timer.set_happening() ;
         wait();
      }
      destroyAllThreads();
   }

   void ThreadCollector::execute()
   {
      while (!isTerminating()) {
         deleteDeadThreads();
         m_timer.wait(50_ms);
      }
   }

   void ThreadCollector::addThread(::subsystem::ThreadInterface *pthread)
   {
      critical_section_lock l(&m_lockObj);
      m_threada.add(pthread);
   }

   void ThreadCollector::deleteDeadThreads()
   {
      critical_section_lock l(&m_lockObj);

      auto iter = m_threada.begin();
      while ( iter != m_threada.end()) {
         auto it= iter;
         iter++;
         auto pthread = *it;
         if (!pthread->isActive()) {
            //delete thread;
            m_threada.erase_at(it - m_threada.data());
         }
      }
   }

   void ThreadCollector::destroyAllThreads()
   {
      critical_section_lock l(&m_lockObj);

      auto iter = m_threada.begin();
      for (; iter != m_threada.end(); iter++) {
         (*iter)->terminate();
      }
      for (iter = m_threada.begin(); iter != m_threada.end(); iter++) {
         (*iter)->wait();
      }

      deleteDeadThreads();
   }

   const memsize ThreadCollector::Size()
   {
      return m_threada.size();
   }
} // namespace subsystem_windows


