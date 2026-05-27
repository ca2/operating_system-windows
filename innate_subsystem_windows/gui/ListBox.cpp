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
#include "framework.h"
#include "ListBox.h"
namespace innate_subsystem_windows
   {
      ListBox::ListBox()
      {
      }

      ListBox::~ListBox()
      {
      }

      void ListBox::addString(const ::i8 *str)
      {
         addString(str, 0);
      }

      void ListBox::addString(const ::i8 *str, void *tag)
      {
         ::wstring wstr(str);
         LRESULT lresult = SendMessage(::as_HWND(this->operating_system_window()), LB_ADDSTRING, 0, (::lparam)(LPARAM) wstr.c_str());
         ::i32 i = (::i32)lresult;
         _ASSERT(i == lresult);
         setItemData(i, (::lparam)tag);
      }

      void ListBox::removeString(::i32 index)
      {
         ::i32 top = getTopIndex();
         SendMessage(::as_HWND(this->operating_system_window()), LB_DELETESTRING, index, NULL);
         setTopIndex(top);
      }

      ::i32 ListBox::getTopIndex()
      {
         return (::i32)SendMessage(::as_HWND(this->operating_system_window()), LB_GETTOPINDEX, NULL, NULL);
      }

      void ListBox::setTopIndex(::i32 index)
      {
         SendMessage(::as_HWND(this->operating_system_window()), LB_SETTOPINDEX, index, NULL);
      }

      ::string ListBox::getItemText(::i32 index)
      {
         size_t length = SendMessage(::as_HWND(this->operating_system_window()), LB_GETTEXTLEN, index, NULL);
         _ASSERT(length <= 65536);
         //std::vector<TCHAR> buffer(length + 1);
         ::wstring wstr;
         SendMessage(::as_HWND(this->operating_system_window()), LB_GETTEXT, index, (LPARAM) (const WCHAR *) wstr.auto_release_buffer(length));
         ////storage->setString(&buffer.front());
         return wstr;
      }

      void ListBox::setItemText(::i32 index, const ::i8 *str)
      {
         ::i32 si = getSelectedIndex();
         ::i32 top = getTopIndex();
         LRESULT lresult = SendMessage(::as_HWND(this->operating_system_window()), LB_GETTOPINDEX, NULL, NULL);
         ::u32 topIndex = (::u32)lresult;
         _ASSERT(topIndex == lresult);
         ::lparam data = getItemData(index);
         removeString(index);
         insertString(index, str, data);
         if (si == index) {
            setSelectedIndex(si);
         }
         setTopIndex(top);
      }

      void ListBox::appendString(const ::i8 *str, ::lparam data)
      {
         LRESULT lresult = SendMessage(::as_HWND(this->operating_system_window()), LB_ADDSTRING, 0, (LPARAM)::wstring(str).c_str());
         ::i32 index = (::i32)lresult;
         _ASSERT(index == lresult);
         setItemData(index, data);
      }

      void ListBox::insertString(::i32 index, const ::i8 *str)
      {
         SendMessage(::as_HWND(this->operating_system_window()), LB_INSERTSTRING, index, (LPARAM)wstring(str).c_str());
      }

      void ListBox::insertString(::i32 index, const ::i8 *str, ::lparam data)
      {
         LRESULT lresult = SendMessage(::as_HWND(this->operating_system_window()), LB_INSERTSTRING, index, (LPARAM)::wstring(str).c_str());
         ::i32 i = (::i32)lresult;
         _ASSERT(i == lresult);
         setItemData(i, data);
      }

      void ListBox::setItemData(::i32 index, ::lparam data)
      {
         SendMessage(::as_HWND(this->operating_system_window()), LB_SETITEMDATA, index, data);
      }

      ::lparam ListBox::getItemData(::i32 index)
      {
         return SendMessage(::as_HWND(this->operating_system_window()), LB_GETITEMDATA, index, NULL);
      }

      ::i32 ListBox::getCount()
      {
         LRESULT lresult = SendMessage(::as_HWND(this->operating_system_window()), LB_GETCOUNT, NULL, NULL);
         ::i32 result = (::i32)lresult;
         _ASSERT(result == lresult);
         return result;
      }

      void ListBox::clear()
      {
         SendMessage(::as_HWND(this->operating_system_window()), LB_RESETCONTENT, NULL, NULL);
      }

      ::i32 ListBox::getSelectedIndex()
      {
         LRESULT lresult = SendMessage(::as_HWND(this->operating_system_window()), LB_GETCURSEL, NULL, NULL);
         ::i32 index = (::i32)lresult;
         _ASSERT(index == lresult);
         return (index == LB_ERR) ? -1 : index;
      }

      void ListBox::setSelectedIndex(::i32 index)
      {
         SendMessage(::as_HWND(this->operating_system_window()), LB_SETCURSEL, index, NULL);
      }
   } // namespace innate_subsystem_windows
