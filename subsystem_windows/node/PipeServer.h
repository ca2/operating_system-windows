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


//#include "subsystem/node/PipeServer.h"

#include "subsystem/node/NamedPipe.h"
//#include "remoting/remoting/thread/LocalMutex.h"

//#include "DynamicLibrary.h"
//#include "subsystem_windows/_common_header.h"
//#include "subsystem_windows/node/::happening.h"
#include "acme/parallelization/happening.h"
//#include "subsystem/node/security/SecurityAttributes.h"
#include "subsystem_windows/node/security/SecurityAttributes.h"

typedef BOOL(WINAPI* pGetNamedPipeClientProcessId)(HANDLE Pipe, PULONG ClientProcessId);


namespace subsystem_windows
{
   /**
    * Server fabric of pipes.
    *
    * @author yuri, enikey.
    * @fixme not thread-safe, undone, strange code inside.
    */
   class CLASS_DECL_SUBSYSTEM_WINDOWS PipeServer :
   virtual public ::particle
   {
   public:



      //private:
      static ::pointer < ::subsystem_windows::DynamicLibrary >  s_pdynamiclibraryKernel32;
      static pGetNamedPipeClientProcessId s_GetNamedPipeClientProcessId;
      static bool s_bInitialized;


      //private:
      ::string m_pipeName;
      //::happening m_winEvent;
      ::happening m_happening;
      DWORD m_milliseconds;
      ::pointer < ::subsystem_windows::SecurityAttributes > m_psecurityattributes;
      ::pointer < ::subsystem_windows::File > m_pfileServerPipe;
      //HANDLE m_serverPipe;
      unsigned int m_bufferSize;

      /**
       * Creates new pipe server ready to accept connections.
       *
       * @param pipeName name of pipe to bind.
       * @throws PipeException on fail.
       *
       * @fixme stub.
       */
      // PipeServer(const ::scoped_string & scopedstrName, unsigned int bufferSize,
      //            ::subsystem::SecurityAttributesInterface *secAttr = 0,
      //            DWORD milliseconds = INFINITE);

      PipeServer();
      /**
       *
       *
       * Destroys pipe server.
       */
      virtual ~PipeServer();


      void initialize_pipe_server(const ::scoped_string & scopedstrName, unsigned int bufferSize,
           ::subsystem::SecurityAttributesInterface *secAttr = 0,
           DWORD milliseconds = INFINITE);

      /**
       * Waits until pipe client connects.
       * @return connected pipe.
       * @throws PipeException on fail.
       * @note accept() method can be breaked by call of close() method.
       *
       * @fixme stub.
       */
      ::pointer < ::subsystem::NamedPipeInterface > accept();

      /**
       * Closes pipe server.
       * @throws PipeException on fail.
       */
      void close();

      /**
       * @deprecated.
       */
      void waitForConnect(DWORD milliseconds = INFINITE);
      /**
       * @deprecated.
       */
      virtual void closeConnection();

   //private:
      void createServerPipe();

      // returns True on every error
      bool checkOtherSideBinaryName(::subsystem::FileInterface * pfilePipe);

      // loads GetNamedPipeClientProcessId (Vista or later) from kernel32
      //void initialize();

      static void s_initialize();

   };

   //// __PIPESERVER_H__
} // namespace subsystem_windows


