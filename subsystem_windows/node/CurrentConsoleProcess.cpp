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
#include "CurrentConsoleProcess.h"

#include "subsystem_windows/node/WinStaLibrary.h"
//#include "remoting/remoting/win_system/Environment.h"
#include "subsystem/node/SystemException.h"
#include "subsystem_windows/node/Process.h"
#include "subsystem_windows/node/Workstation.h"
#include "subsystem_windows/node/WTS.h"
#include "subsystem_windows/subsystem.h"



namespace subsystem_windows
{

   CurrentConsoleProcess::CurrentConsoleProcess(::subsystem::LogWriter *log, bool connectRdpSession,
                                                const ::scoped_string &scopedstrPath,
                                                const ::scoped_string &scopedstrArgs) :
       m_log(log), m_connectRdpSession(connectRdpSession)
   {
      initialize_process(scopedstrPath, scopedstrArgs);
   }

   CurrentConsoleProcess::~CurrentConsoleProcess() {}

   void CurrentConsoleProcess::start()
   {
      cleanup();

      auto pprocessWindows = impl<::subsystem_windows::Process>();

      m_log->information("Try to start \"{} {}\" process", pprocessWindows->m_path, pprocessWindows->m_args);

      DWORD uiAccess = 1; // Nonzero enables UI control
      PROCESS_INFORMATION pi;
      STARTUPINFO sti;
      pprocessWindows->_getStartupInfo(&sti);

      m_log->debug("sti: cb = {}, hStdError = %p, hStdInput = %p,"
                   " hStdOutput = %p, dwFlags = %u",
                   (unsigned int)sti.cb, (void *)sti.hStdError, (void *)sti.hStdInput, (void *)sti.hStdOutput,
                   (unsigned int)sti.dwFlags);

      try
      {
         HANDLE userToken = WindowsSubsystem().WTS().duplicateCurrentProcessUserToken(m_connectRdpSession, m_log);

         ::string commandLine = getCommandLineString();

         m_log->debug("Try CreateProcessAsUser({} 0, {}, 0, 0, {}, NORMAL_PRIORITY_CLASS, 0, 0,"
                      " sti, pi)",
                      (void *)userToken, commandLine, (int)pprocessWindows->m_handlesIsInherited);
         if (CreateProcessAsUser(userToken, 0, (LPTSTR)::wstring(commandLine).c_str(), 0, 0,
                                 pprocessWindows->m_handlesIsInherited,
                                 NORMAL_PRIORITY_CLASS, 0, 0, &sti, &pi) == 0)
         {
            throw ::subsystem::SystemException();
         }
         m_log->information("Created \"{}\" process", commandLine);
         //
         // FIXME: Leak.
         //
         CloseHandle(userToken);
      }
      catch (::subsystem::SystemException &sysEx)
      {
         m_log->error("Failed to start process with {} error", sysEx.getErrorCode());
         throw;
      }

      pprocessWindows->m_hThread = pi.hThread;
      pprocessWindows->m_pprocesshandle->m_hProcess      = pi.hProcess;
   }


} // namespace subsystem_windows
