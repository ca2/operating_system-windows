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
// with this program; if not, write to the Free Software Foundation, Inc.,
// 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
//-------------------------------------------------------------------------
//
// Adapted by camilo on beginning of 2026-April <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "SpinControl.h"
#include <CommCtrl.h>
//#include "util/StringParser.h"

// namespace windows
// {
namespace innate_subsystem_windows
{
   SpinControl::SpinControl()
 //  : m_buddy(NULL),
   :  m_isAutoAccelerationEnabled(false), m_maxDelta(0)
   {
   }

   SpinControl::~SpinControl()
   {
   }

   void SpinControl::setBuddy(ControlInterface *buddyControl)
   {
       ::cast < WindowInterface > pwindow = buddyControl;
      SendMessage((HWND) ::as_HWND(this->operating_system_window()), UDM_SETBUDDY, (::wparam) ::as_HWND(pwindow->operating_system_window()), NULL);
      m_pcontrolBuddy = buddyControl;
   }

   void SpinControl::setRange(::i16 lower, ::i16 upper)
   {
      SendMessage((HWND) ::as_HWND(this->operating_system_window()), UDM_SETRANGE, NULL, (::lparam)MAKELONG(upper, lower));
   }

   void SpinControl::setRange32(::i32 lower, ::i32 upper)
   {
      SendMessage((HWND) ::as_HWND(this->operating_system_window()), UDM_SETRANGE32, lower, upper);
   }

   void SpinControl::setAccel(::u32 nSec, ::u32 nInc)
   {
      UDACCEL accel = {0};
      accel.nSec = nSec;
      accel.nInc = nInc;

      SendMessage((HWND) ::as_HWND(this->operating_system_window()), UDM_SETACCEL, 1, (::lparam)&accel);
   }

   void SpinControl::autoAccelerationHandler(::i32 & iPos, ::i32 & iDelta)
   {
      if (m_limitters.size() == 0 ||
          m_pcontrolBuddy == NULL || !m_isAutoAccelerationEnabled) {
         return;
          }

      ::i32 currentValue = 0;
      ::i32 delta = m_maxDelta;

      // Get buddy textbox value
      ::string  storage;
      ::cast < ::innate_subsystem::Window > pwindowBuddy = m_pcontrolBuddy;
      storage = pwindowBuddy->getText();
      if (!MainSubsystem().StringParser().parseInt(storage, &currentValue)) {
         return;
      }

      size_t size = minimum(m_limitters.size(), m_deltas.size());

      if (iDelta < 0) {
         for (size_t i = 0; i < size; i++) {
            if (currentValue <= m_limitters[i]) {
               delta = m_deltas[i];
               break;
            } // if
         } // for
         delta = -delta;
      } // if

      if (iDelta > 0) {
         for (size_t i = 0; i < size; i++) {
            if (currentValue < m_limitters[i]) {
               delta = m_deltas[i];
               break;
            } // if
         } // for
      } // if

      ::i32 mod = (currentValue + delta) % delta;
      if (mod != 0) {
         delta -= mod;
      }

      iDelta = delta;
   }

   void SpinControl::enableAutoAcceleration(bool enabled)
   {
      m_isAutoAccelerationEnabled = enabled;
   }

   void SpinControl::setAutoAccelerationParams(const i32_array & limitters,
                                               const i32_array & deltas,
                                               ::i32 maxDelta)
   {
      m_limitters = limitters;
      m_deltas = deltas;
      m_maxDelta = maxDelta;
   }



   void SpinControl::_000OnNotify(windows_reflect_notify_t & notify)
   {

      switch (notify.m_lpnmhdr->code)
      {
         case NM_DBLCLK:
         {
            //onAction();
            notify.m_bHandled= _001OnAction();
            //onRemoteListViewDoubleClick();
            break;
         }
         case UDN_DELTAPOS:
         {
            LPNMUPDOWN lpnmupdown = (LPNMUPDOWN)notify.m_lpnmhdr;
            notify.m_bHandled = _001OnUpDown(lpnmupdown->iPos, lpnmupdown->iDelta);

         }
            break;
      }


   }

} // namespace innate_subsystem_windows
