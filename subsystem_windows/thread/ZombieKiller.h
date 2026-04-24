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

#pragma once


//#include "Thread.h"
//#include "critical_section.h"

//#include "subsystem/platform/Singleton.h"

//#include <list>

//#include "acme/prototype/collection/list.h"
#include "subsystem/thread/ZombieKiller.h"

//typedef ::list_base<Thread *> ThreadList;

namespace  subsystem_windows
{
   /**
    * Collector of "zombie" threads.
    * Zombie killer has it's own thread which deletes in infinity loop not
    * active zombie threads.
    * @remark ZombieKiller is singleton without "lazy" initialization.
    */
   class ZombieKiller : virtual public subsystem::ZombieKiller
   {
   public:
      /**
       * Creates zombie killed instance.
       */
      ZombieKiller();
      /**
       * Deletes zombie killer.
       */
      ~ZombieKiller() override;



      /**
       * Adds thread to zombie list.
       */
      //void addZombie(::subsystem::Thread *zombie);

      /**
       * Forces terminates all threads, waits until they dies and than
       * delete them from memory and thread ::list_base.
       */
      //  void killAllZombies() override;

      //protected:
      /**
       * Inherited from Thread class.
       */
      //virtual void run() override;

      /**
       * Deletes all dead zombie threads from memory and removes them from zombies ::list_base.
       */
      //virtual void deleteDeadZombies();

      // protected:
      //   /**
      //    * Thread ::array_base.
      //    */
      //   ThreadList m_zombies;
      //
      //   /**
      //    * Thread-safety.
      //    */
      //   critical_section m_lockObj;
   };
} // namespace subsystem_windows

