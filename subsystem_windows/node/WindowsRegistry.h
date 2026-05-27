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

#pragma once


#include "subsystem_windows/node/WindowsRegistryKey.h"

namespace subsystem_windows
{
   class CLASS_DECL_SUBSYSTEM_WINDOWS WindowsRegistry
   {
   public:
      const static ::i32 STRING_TYPE = REG_SZ;
      const static ::i32 EXPAND_STRING_TYPE = REG_EXPAND_SZ;
      const static ::i32 BINARY_TYPE = REG_BINARY;
      const static ::i32 DWORD_TYPE = REG_DWORD;
      const static ::i32 QWORD_TYPE = REG_QWORD;

   //public:
      static HKEY getCurrentUserKey();
      static HKEY getCurrentLocalMachineKey();

   //private:
      WindowsRegistry();
      ~WindowsRegistry();
   };
} // namespace subsystem_windows