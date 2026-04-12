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
#include "Impersonator.h"
#include "WTS.h"
#include "../subsystem.h"
#include "subsystem/node/SystemException.h"
#include "subsystem/node/SystemInformation.h"

//#include <crtdbg.h>

//#include "remoting/remoting_common/win_system/WTS.h"

namespace subsystem_windows
{

   // Impersonator::Impersonator(LogWriter *log)
   // : m_token(INVALID_HANDLE_VALUE),
   //   m_dupToken(INVALID_HANDLE_VALUE),
   //   m_log(log)
   // {
   // }
   //
   Impersonator::Impersonator()
   : m_token(INVALID_HANDLE_VALUE),
     m_dupToken(INVALID_HANDLE_VALUE)
   {
   }


   Impersonator::~Impersonator()
   {
   }

   void Impersonator::initialize_impersonator(::subsystem::LogWriter *plogwriter)
   {
     m_plogwriter = plogwriter;
   }


   void Impersonator::impersonateAsLoggedUser()
   {
      HANDLE token = windows_subsystem()->wts()->queryConsoleUserToken(m_plogwriter);
      impersonateAsUser(token);
   }


   void Impersonator::impersonateAsUser(HANDLE token)
   {
      if (m_token != INVALID_HANDLE_VALUE) {
         CloseHandle(m_token);
      }
      m_token = token;

      ::string name = windows_subsystem()->wts()->getTokenUserName(m_token);
      m_plogwriter->debug("impersonate as user: {}", name);

      if ((!DuplicateToken(m_token, SecurityImpersonation, &m_dupToken))) {
         throw ::subsystem::SystemException("could not DuplicateToken");
      }
      if (!ImpersonateLoggedOnUser(m_dupToken)) {
         throw ::subsystem::SystemException("could not ImpersonateLoggedOnUser");
      }

   }


   void Impersonator::impersonateAsCurrentProcessUser(bool rdpEnabled)
   {
      HANDLE token = windows_subsystem()->wts()->duplicateCurrentProcessUserToken(rdpEnabled, m_plogwriter);
      impersonateAsUser(token);
   }


   void Impersonator::revertToSelf()
   {
      if (m_dupToken != INVALID_HANDLE_VALUE) {
         CloseHandle(m_dupToken);
      }

      if (m_token != INVALID_HANDLE_VALUE) {
         CloseHandle(m_token);
      }

      m_dupToken = INVALID_HANDLE_VALUE;
      m_token = INVALID_HANDLE_VALUE;

      if (!RevertToSelf()) {
         throw ::subsystem::SystemException("could not RevertToSelf");
      }
   }


   bool Impersonator::sessionIsLocked(bool rdpEnabled)
   {
      DWORD id = 0;
      if (rdpEnabled) {
         id = windows_subsystem()->wts()->getRdpSessionId(m_plogwriter);
      }
      if (id == 0) {
         id = windows_subsystem()->wts()->getActiveConsoleSessionId(m_plogwriter);
      }
      return windows_subsystem()->wts()->sessionIsLocked(id, m_plogwriter);
   }


} // namespace subsystem_windows