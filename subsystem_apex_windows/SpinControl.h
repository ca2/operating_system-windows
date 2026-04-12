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
// with this program; if not, write to the Free Software Foundation, Inc.,
// 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
//-------------------------------------------------------------------------
//
// Adapted by camilo on beginning of 2026-April <3ThomasBorregaardSorensen!!
//
#pragma once
//#define _SPIN_CONTROL_H_

#include "subsystem_apex/SpinControl.h"
#include "innate_subsystem_win32/_common_header.h"

namespace innate_subsystem_win32
{

class CLASS_DECL_INNATE_SUBSYSTEM_WIN32 SpinControl : public window_implementation<subsystem_apex::SpinControlInterface>
{
public:
  SpinControl();
  ~SpinControl() override;

  void setBuddy(ControlInterface *buddyControl) override;
  void setRange(short lower, short upper) override;
  void setRange32(int lower, int upper) override;
  void setAccel(unsigned int nSec, unsigned int nInc) override;

  //
  // Auto acceleration methods
  //

  //
  // Handler, call it on UDN_DELTAPOS notification
  //

  virtual void autoAccelerationHandler(LPNMUPDOWN message);
  void enableAutoAcceleration(bool enabled) override;
  void setAutoAccelerationParams(const int_array & limitters,
                                 const int_array & deltas,
                                 int maxDelta) override;
// protected:
   ::pointer < ::subsystem_apex::ControlInterface> m_pcontrolBuddy;
//
//   //
//   // Members needed for auto acceleration
//   //
//
   bool m_isAutoAccelerationEnabled;
   int_array m_limitters;
   int_array m_deltas;
   int m_maxDelta;
};

} // namespace innate_subsystem_win32

//#endif


