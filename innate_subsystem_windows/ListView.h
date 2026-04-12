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


#include "innate_subsystem/ListView.h"
#include "innate_subsystem_win32/_common_header.h"

//
// TODO: Maybe use class for this?
//

namespace innate_subsystem_win32
{
   // typedef struct
   // {
   //    int index;
   //    unsigned long long tag;
   // } ListViewItem;

   //
   // ListView class can be used only for listviews
   // that view data as report.
   //

   class CLASS_DECL_INNATE_SUBSYSTEM_WIN32 ListView :
   virtual public window_implementation<subsystem_apex::ListViewInterface>
   {
   public:

      // private:
      //    // Kind of sorting: ascending or descending
      bool m_sortAscending;
      //
      //    //
      //    // Is list view not sorted, then m_sortClumnIndex is negative,
      //    // else him contained index of column.
      //    //
      int m_sortColumnIndex;

      LPARAM m_lparamSort;
      //
      //    //
      //    // This pointer to compareFunction. By default is 0.
      //    //
      //PFNLVCOMPARE m_compareItem;

      ::function < int(::lparam, ::lparam) > m_compare;

      ListView();

      //
      // Adds new column to list view
      //

      virtual void addColumn(int index, const char *caption, int width, int fmt)override ;
      virtual void addColumn(int index, const char *caption, int width)override ;

      //
      // Returns list view item structure with specified index
      //

      virtual ::subsystem_apex::ListViewItem getItem(int index)override ;

      //
      // Returns list view items count
      //

      virtual int getCount()override ;

      //
      // Inserts new item to list view with specified index and caption
      //

      virtual void addItem(int index, const char *caption)override ;

      //
      // Inserts new item to list view with specified index, caption
      // and user data(tag)
      //

      virtual void addItem(int index, const char *caption, ::lparam tag)override ;

      //
      // Inserts new item to list view
      //

      virtual void addItem(int index, const char *caption, ::lparam tag, int imageIndex)override ;

      //
      // Removes item with specified index from list view
      //

      virtual void removeItem(int i)override ;

      //
      // Removes all list view items from list view
      //

      virtual void clear()override ;

      //
      // Changes text of list view item subitem
      //

      virtual void setSubItemText(int index, int subIndex, const char *caption)override ;

      //
      // Changes user data (tag) of list view item with specified index
      //

      virtual void setItemData(int index, ::lparam tag)override ;

      //
      // Returns user data of list view item with specified index
      //

      virtual ::lparam getItemData(int index)override ;

      //
      // Returns first selected list view item
      //

      virtual ::subsystem_apex::ListViewItem getSelectedItem()override ;

      //
      // Returns index of first selected list view item
      //

      virtual int getSelectedIndex()override ;

      //
      // Selectes list view item with specified index
      //

      virtual void selectItem(int index)override ;

      //
      // Changes full row select style of list view
      //

      virtual void setFullRowSelectStyle(bool fullRowSelect)override ;

      //
      // Enabled or disables multi selection on list view
      //

      virtual void allowMultiSelection(bool allow)override ;

      //
      // Returns count of selected items in list view
      //

      virtual unsigned int getSelectedItemsCount()override ;

      //
      // Sets selected list view index to output indexes array
      //

      virtual ::int_array getSelectedItemsIndexes()override ;

   //protected:

      virtual void setListViewExtendedStyle(unsigned int style)override ;
      virtual unsigned int getListViewExtendedStyle()override ;

      virtual void addListViewExtendedStyle(unsigned int style)override ;
      virtual void removeListViewExtendedStyle(unsigned int style)override ;

      //
      // This method sort list of item by column "columnIndex".
      // For comparing elements using function compareItem().
      //
      // Pointer to compareItem() must be not 0.
      // After add or changing elements, list may be not sorted.
      //
      // For example, you need to call this method, if user changed parameters of sorting.
      //
      void set_sort(int columnIndex,const ::function < int(::lparam, ::lparam) > & compare)override ;


      //typedef int (CALLBACK *PFNLVCOMPARE)(LPARAM, LPARAM, LPARAM);


      static int CALLBACK s_FNLVCOMPARE(LPARAM lparam1, LPARAM lparam2, LPARAM lparamSort);
      //
      // This method sort list of item by column m_sortColumIndex.
      // After add and removing elements, list may be not sorted.
      // For example, you need to call this method after add new element.
      //
      void sort()override ;

      void _000OnNotify(windows_reflect_notify_t & notify) override;

      void onAction() override;


   };

} // namespace innate_subsystem_win32



