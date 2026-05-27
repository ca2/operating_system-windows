// Copyright (C) 2008,2009,2010,2011,2012 GlavSoft LLC.
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
#pragma once


#include "innate_subsystem/gui/ListBox.h"
#include "innate_subsystem_windows/_common_header.h"
#include "innate_subsystem_windows/gui/Control.h"


namespace innate_subsystem_windows
{


   class CLASS_DECL_INNATE_SUBSYSTEM_WINDOWS ListBox : public window_implementation<innate_subsystem::ListBoxInterface, Control>
   {
   public:
      ListBox();
      ~ListBox()override ;
      void addString(const ::i8 *str)override ;
      void addString(const ::i8 *str, void *tag)override ;
      ::string getItemText(::i32 index)override ;
      void setItemText(::i32 index, const ::i8 *str)override ;
      void insertString(::i32 index, const ::i8 *str)override ;
      void insertString(::i32 index, const ::i8 *str, ::lparam data)override ;
      void appendString(const ::i8 *str, ::lparam data)override ;
      void setItemData(::i32 index, ::lparam data)override ;
      void removeString(::i32 index)override ;
      ::i32 getSelectedIndex()override ;
      ::i32 getTopIndex()override ;
      void setTopIndex(::i32 index)override ;
      void setSelectedIndex(::i32 index)override ;
      ::lparam getItemData(::i32 index)override ;
      ::i32 getCount()override ;
      void clear()override ;
   };
} // innate_subsystem_windows

   
   