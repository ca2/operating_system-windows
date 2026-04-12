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

#include "subsystem_acme/node/Keyboard.h"
//#include "remoting/remoting_common/util/winhdr.h"
#include "subsystem_win32/_common_header.h"


namespace subsystem_win32
{
      /**
       * Wrapper on base WinAPI keyboard functions.
       */
      class CLASS_DECL_SUBSYSTEM_WIN32 Keyboard :
   virtual public ::subsystem::implementation<subsystem::KeyboardInterface>
      {
      public:
         /**
          * Copied current keyboard state (256 virtual keys state) to state array.
          * @param state [out] array of 256 virtual key states.
          * @throws SystemException on error.
          */
         void getState(BYTE state[256]) override;

         /**
          * Sets current keyboard state.
          * @param state array of 256 virtual key states.
          * @throws SystemException on error.
          */
         void setState(BYTE state[256]) override;

         /**
          * Check if specified key is in pressed state.
          * @param vkCode virtual code of key.
          * @return true if key is pressed, false if released.
          */
         bool isKeyPressed(BYTE vkCode) override;

      };
} // namespace subsystem_win32
