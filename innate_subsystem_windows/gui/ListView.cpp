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
#include "framework.h"
#include "ListView.h"

#include "innate_subsystem/subsystem.h"
#include <commctrl.h>

namespace innate_subsystem_windows
{

   ListView::ListView() :
     m_sortAscending(false)
   {
      m_sortColumnIndex = -1;
      //m_compareItem = 0;
   }

   void ListView::addColumn(int index, const char *caption, int width, int fmt)
   {
      //
      // Create LV_COLUMN struct
      //
      ::wstring wstr(caption);
      LV_COLUMN lvColumn = {0};
      lvColumn.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT;
      lvColumn.fmt = fmt;
      lvColumn.cx = width;
      lvColumn.pszText = (WCHAR *)wstr.c_str();

      //
      // Add column to list view
      //

      ListView_InsertColumn((HWND) _HWND(), index, &lvColumn);
   }

   void ListView::addColumn(int index, const char *caption, int width)
   {
      addColumn(index, caption, width, LVCFMT_LEFT);
   }

   innate_subsystem::ListViewItem ListView::getItem(int index)
   {
      // Output structure
      innate_subsystem::ListViewItem item;
      // Windows list view item concept
      LVITEM lvI;
      // Buffer for text data
      WCHAR textBuffer[256];

      //
      // Retrieve text and tag from list view item (zero subitem)
      //

      lvI.mask = LVIF_TEXT | LVIF_PARAM;
      lvI.pszText = (WCHAR *)&textBuffer[0];
      lvI.iItem = index;
      lvI.iSubItem = 0;

      //
      // FIXME: Forced set text limit. 256 chars max
      //

      lvI.cchTextMax = 256 * sizeof(WCHAR);

      // Trying to get data from window
      ListView_GetItem((HWND) _HWND(), &lvI);

      //
      // Copying data to our list view item structure
      //

      item.index = lvI.iItem;
      item.tag = lvI.lParam;

      return item;
   }

   void ListView::addItem(int index, const char *caption)
   {
      addItem(index, caption, NULL);
   }

   void ListView::addItem(int index, const char *caption, ::lparam tag)
   {
      //
      // Prepare LVITEM structure
      //
::wstring wstr(caption);
      LVITEM lvI;
      lvI.mask = LVIF_TEXT | LVIF_PARAM;
      lvI.lParam = tag;
      lvI.iItem = index;
      lvI.iSubItem = 0;
      lvI.pszText = (WCHAR*)wstr.c_str();

      //
      // Send message to window
      //

      ListView_InsertItem((HWND) _HWND(), &lvI);
   }

   void ListView::addItem(int index, const char *caption, ::lparam tag, int imageIndex)
   {
      //
      // Prepare LVITEM structure
      //
::wstring wstr(caption);
      LVITEM lvI;
      lvI.mask = LVIF_TEXT | LVIF_PARAM | LVIF_IMAGE;
      lvI.lParam = tag;
      lvI.iItem = index;
      lvI.iSubItem = 0;
      lvI.iImage = imageIndex;
      lvI.pszText = (WCHAR*)wstr.c_str();

      //
      // Send message to window
      //

      ListView_InsertItem((HWND) _HWND(), &lvI);
   }

   void ListView::removeItem(int i)
   {
      ListView_DeleteItem((HWND) _HWND(), i);
   }

   void ListView::clear()
   {
      ListView_DeleteAllItems((HWND) _HWND());
   }

   void ListView::setSubItemText(int index, int subIndex, const char  *caption)
   {
      //
      // Prepare LVITEM structure
      //
      ::wstring wstr(caption);
      LVITEM lvI;
      lvI.mask = LVIF_TEXT;
      lvI.iItem = index;
      lvI.iSubItem = subIndex;
      lvI.pszText = (TCHAR*)caption;

      //
      // Send message to window
      //

      SendMessage((HWND) _HWND(), LVM_SETITEM, 0, (LPARAM)&lvI);
   }

   void ListView::setItemData(int index, ::lparam tag)
   {
      //
      // Prepare LVITEM structure
      //

      LVITEM lvI;
      lvI.mask = LVIF_PARAM;
      lvI.lParam = tag;
      lvI.iItem = index;
      lvI.iSubItem = 0;
      lvI.lParam = tag;

      //
      // Send message to window
      //

      SendMessage((HWND) _HWND(), LVM_SETITEM, 0, (LPARAM)&lvI);
   }

   ::lparam ListView::getItemData(int index)
   {
      return getItem(index).tag;
   }

   ::innate_subsystem::ListViewItem ListView::getSelectedItem()
   {
      ::innate_subsystem::ListViewItem item;
      int index = getSelectedIndex();
      if (index == -1) {
         item.index = -1;
         item.tag = NULL;
      } else {
         item = getItem(index);
      }
      return item;
   }

   int ListView::getSelectedIndex()
   {
      int iSelect = ListView_GetNextItem((HWND) _HWND(), -1, LVNI_SELECTED);
      return iSelect;
   }

   void ListView::selectItem(int index)
   {
      ::wparam itemIndex = (::wparam)index;
      ListView_SetItemState((HWND) _HWND(), -1, 0, LVIS_SELECTED);
      SendMessage((HWND) _HWND(), LVM_ENSUREVISIBLE , itemIndex, FALSE);
      ListView_SetItemState((HWND) _HWND(), itemIndex, LVIS_SELECTED, LVIS_SELECTED);
      ListView_SetItemState((HWND) _HWND(), itemIndex, LVIS_FOCUSED, LVIS_FOCUSED);
      setFocus();
   }

   void ListView::setFullRowSelectStyle(bool fullRowSelect)
   {
      if (fullRowSelect) {
         addExStyle(LVS_EX_FULLROWSELECT);
      } else {
         removeExStyle(LVS_EX_FULLROWSELECT);
      }
   }

   void ListView::allowMultiSelection(bool allow)
   {
      if (allow) {
         removeStyle(LVS_SINGLESEL);
      } else {
         addStyle(LVS_SINGLESEL);
      }
   }

   unsigned int ListView::getSelectedItemsCount()
   {
      return ListView_GetSelectedCount((HWND) _HWND());
   }


   int ListView::getCount()
   {
      return (int) ListView_GetItemCount((HWND) _HWND());
   }

   ::int_array ListView::getSelectedItemsIndexes()
   {
      int i = -1;
      ::int_array ia;
      ia.set_size(getSelectedItemsCount());
      for (auto & iItem : ia)
      {
         i = ListView_GetNextItem((HWND) _HWND(), i, LVNI_SELECTED);
         iItem = i;
      }
      return ia;
   }

   int CALLBACK ListView::s_FNLVCOMPARE(LPARAM lparam1, LPARAM lparam2, LPARAM lparamSort)
   {

      auto pbase = (::function < int(::lparam, ::lparam) >::base *)lparamSort;

      return pbase->operator()(lparam1, lparam2);

   }

   void ListView::set_sort(int columnIndex, const ::function < int(::lparam, ::lparam) > & compare)
   {
      // Update parameters of sorting.
      int oldSortColumnIndex = m_sortColumnIndex;
      m_sortColumnIndex = columnIndex;

      // make decision about order
      // positive value of m_sortAscending for ascending order
      // negative value of m_sortAscending for descending order
      if (oldSortColumnIndex == m_sortColumnIndex) {
         m_sortAscending = !m_sortAscending;
      } else {
         m_sortAscending = true;
      }
      m_compare = compare;

      // Update arrow in header.
      HWND hHeader = ListView_GetHeader((HWND) _HWND());
      if (hHeader != 0) {
         HDITEM hdrItem = { 0 };
         hdrItem.mask = HDI_FORMAT;

         // delete all header icons
         if (Header_GetItem(hHeader, oldSortColumnIndex, &hdrItem)) {
            hdrItem.fmt = hdrItem.fmt & ~HDF_SORTUP & ~HDF_SORTDOWN;
            Header_SetItem(hHeader, oldSortColumnIndex, &hdrItem);
         }

         // add necessary header icon
         if (Header_GetItem(hHeader, m_sortColumnIndex, &hdrItem)) {
            hdrItem.fmt = hdrItem.fmt | (m_sortAscending ? HDF_SORTUP : HDF_SORTDOWN);
            Header_SetItem(hHeader, m_sortColumnIndex, &hdrItem);
         }
      }
      // Sort list of item.
      sort();
   }

   void ListView::sort()
   {
      if (m_sortColumnIndex >= 0 && m_compare != 0) {
         // use sortColumnIndex (::lparamSort) as an index of column and
         // as a flag: positive for ascending order,
         // negative for descending order
         int sortColumnIndex = m_sortColumnIndex + 1;
         if (!m_sortAscending) {
            sortColumnIndex = -sortColumnIndex;
         }
         m_lparamSort = sortColumnIndex;
         //ListView_SortItems((HWND) _HWND(), s_LVNCOMPARE, sortColumnIndex);
         ListView_SortItems((HWND) _HWND(), s_FNLVCOMPARE, m_compare.m_p);
      }
   }

   void ListView::setListViewExtendedStyle(unsigned int style)
   {
      ::SendMessage((HWND) _HWND(), LVM_SETEXTENDEDLISTVIEWSTYLE, 0, (::lparam)style);
   }

   unsigned int ListView::getListViewExtendedStyle()
   {
      return ListView_GetExtendedListViewStyle((HWND) _HWND());
   }

   void ListView::addListViewExtendedStyle(unsigned int styleFlag)
   {
      DWORD flags = getExStyle();
      flags |= styleFlag;
      setExStyle(flags);
   }

   void ListView::removeListViewExtendedStyle(unsigned int styleFlag)
   {
      DWORD flags = getExStyle();
      flags &= ~styleFlag;
      setExStyle(flags);
   }


   void ListView::onAction()
   {

      m_plistviewCallback->onAction();

   }


   void ListView::_000OnNotify(windows_reflect_notify_t & notify)
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
         case LVN_KEYDOWN:
         {
            auto lpnmlvkeydown = (LPNMLVKEYDOWN)notify.m_lpnmhdr;
            auto euserkey = MainInnateSubsystem().virtual_key_code_to_user_key(lpnmlvkeydown->wVKey);
            notify.m_bHandled = _001OnKeyDownNotification(euserkey);
            //onKeyDownNotification(euserkey);
            //onRemoteListViewKeyDown(nmlvkd->wVKey);
            break;
         }
         break;
         case LVN_COLUMNCLICK:
         {
            auto lpdi = (LPNMLISTVIEW)notify.m_lpnmhdr;
            notify.m_bHandled = _001OnColumnClick(lpdi->iSubItem);
         } // switch notification code
break;
         //
         // FIXME: Not better way to call this method at every notification
         // for ::list_base view control, but windows have no notification for ::list_base view
         // selection changed event. So for now, i didn't found better solution.
         //
        //
        //         checkRemoteListViewSelection();
        //         break;
        //     case IDC_LOCAL_FILE_LIST:
        //         switch (nmhdr->code) {
        //         case NM_DBLCLK:
        //                 onLocalListViewDoubleClick();
        //                 break;
        //         case LVN_KEYDOWN:
        //         {
        //             LPNMLVKEYDOWN nmlvkd = (LPNMLVKEYDOWN)data;
        //             onLocalListViewKeyDown(nmlvkd->wVKey);
        //         }
        //                 break;
        //         case LVN_COLUMNCLICK:
        //         {
        //             NMLISTVIEW *lpdi = reinterpret_cast<NMLISTVIEW *>(data);
        //             m_localFileListView.sort(lpdi->iSubItem);
        //         }
        //                 break;
        //         } // switch notification code
        //
        //         //
        //         // FIXME: Not better way to call this method at every notification
        //         // for ::list_base view control, but windows have no notification for ::list_base view
        //         // selection changed event. So for now, i didn't found better solution.
        //         //
        //
        //         checkLocalListViewSelection();
        //         break;
        }
        //return false;

   }

} // namespace innate_subsystem_windows
