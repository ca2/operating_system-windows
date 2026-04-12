// Copyright (C) 2008,2009,2010,2011,2012 GlavSoft LLC.
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

#pragma once

#include "subsystem_apex/ListBox.h"
#include "innate_subsystem_win32/_common_header.h"

namespace innate_subsystem_win32
{


   class CLASS_DECL_INNATE_SUBSYSTEM_WIN32 ListBox : public window_implementation<subsystem_apex::ListBoxInterface>
   {
   public:
      ListBox();
      ~ListBox()override ;
      void addString(const char *str)override ;
      void addString(const char *str, void *tag)override ;
      ::string getItemText(int index)override ;
      void setItemText(int index, const char *str)override ;
      void insertString(int index, const char *str)override ;
      void insertString(int index, const char *str, ::lparam data)override ;
      void appendString(const char *str, ::lparam data)override ;
      void setItemData(int index, ::lparam data)override ;
      void removeString(int index)override ;
      int getSelectedIndex()override ;
      int getTopIndex()override ;
      void setTopIndex(int index)override ;
      void setSelectedIndex(int index)override ;
      ::lparam getItemData(int index)override ;
      int getCount()override ;
      void clear()override ;
   };
} // innate_subsystem_win32

   
   