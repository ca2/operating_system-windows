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
#pragma once
//#ifndef _COMBOBOX_H_
//#define _COMBOBOX_H_

//#include "acCommonHeader.h"
#include "innate_subsystem/gui/ComboBox.h"
#include "innate_subsystem_windows/_common_header.h"
#include "innate_subsystem_windows/gui/Control.h"


namespace innate_subsystem_windows
{


    class ComboBox :// public Control
   virtual public window_implementation<::innate_subsystem::ComboBoxInterface, Control>
       //, virtual public Control
    {
    public:


        ComboBox();
        ~ComboBox();

        // Adds new item to the end of combo box items list.
        virtual ::i32 addItem(const ::i8 *text);

        // Adds new item to the end of combo box items list.
        virtual ::i32 addItem(const ::i8 *text, void *tag);

        // Inserts new item to the specified position
        virtual void insertItem(::i32 index, const ::i8 *text);

        // Inserts new item to the specified position
        virtual void insertItem(::i32 index, const ::i8 *text, void *tag);

        // Returns count of combo box items
        virtual ::i32 getItemsCount();

        // Sets user data (tag) associated with combo box item with specified index
        virtual void setItemData(::i32 index, void *tag);

        // Returns user data associated with combo box item with specified index
        virtual void *getItemData(::i32 index);

        // Sets text associated with combo box item with specified index
        virtual ::string getItemText(::i32 index);

        // Returns current selected item index
        virtual ::i32 getSelectedItemIndex();

        // Selects item with specified index
        virtual void setSelectedItem(::i32 index);

        // Deletes item from specified location
        virtual void deleteItem(::i32 index);

        // Removes all combo box items
        virtual void removeAllItems();


    };

    //#endif
} // namespace innate_subsystem_windows




