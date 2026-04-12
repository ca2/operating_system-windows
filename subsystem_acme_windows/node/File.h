// Copyright (C) 2012 GlavSoft LLC.
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


#include "subsystem_acme/node/File.h"
#include "subsystem_win32/_common_header.h"

namespace subsystem_win32
{

   class CLASS_DECL_SUBSYSTEM_WIN32 File :
      virtual public ::subsystem::implementation<::subsystem::FileInterface>
   {
   public:



      HANDLE m_handle;

      bool m_bOwned;


      File();
      ~File() override;


      void * _HANDLE() override;


   };

} // namespace subsystem_win32


CLASS_DECL_SUBSYSTEM_WIN32 HANDLE as_HANDLE(::subsystem::FileInterface * pfile);
CLASS_DECL_SUBSYSTEM_WIN32 bool is_ok(const ::subsystem_win32::File * pfile);
CLASS_DECL_SUBSYSTEM_WIN32 bool is_ok(const ::pointer < ::subsystem_win32::File > & pfile);