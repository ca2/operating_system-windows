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
#include "ComboBox.h"

#include <Windowsx.h>


//namespace windows
//{
   namespace  innate_subsystem_win32
   {
      ComboBox::ComboBox()
      {
      }

      ComboBox::~ComboBox()
      {
      }

      int ComboBox::addItem(const char *text)
      {
         auto hwnd = ::as_HWND(operating_system_window());
         return ComboBox_AddString(hwnd, text);
      }

      int ComboBox::addItem(const char *text, void *tag)
      {
         int index = addItem(text);
         setItemData(index, tag);
         return index;
      }

      void ComboBox::insertItem(int index, const char *text)
      {
         auto hwnd = ::as_HWND(operating_system_window());
         ComboBox_InsertString(hwnd, index, text);
      }

      void ComboBox::insertItem(int index, const char *text, void *tag)
      {
         insertItem(index, text);
         setItemData(index, tag);
      }

      int ComboBox::getItemsCount()
      {
         auto hwnd = ::as_HWND(operating_system_window());
         return ComboBox_GetCount(hwnd);
      }

      void ComboBox::setItemData(int index, void *tag)
      {
         auto hwnd = ::as_HWND(operating_system_window());
         ComboBox_SetItemData(hwnd, index, (::lparam)tag);
      }

      void *ComboBox::getItemData(int index)
      {
         auto hwnd = ::as_HWND(operating_system_window());
         return (void *)ComboBox_GetItemData(hwnd, index);
      }

      ::string ComboBox::getItemText(int index)
      {

         ::wstring wstr;

         auto hwnd = ::as_HWND(operating_system_window());

         size_t length = ComboBox_GetLBTextLen(hwnd, index);

         ComboBox_GetLBText(hwnd, index, wstr.auto_release_buffer(length));

         return wstr;

      }


      int ComboBox::getSelectedItemIndex()
      {

         auto hwnd = ::as_HWND(operating_system_window());

         return ComboBox_GetCurSel(m_hwnd);
      }

      void ComboBox::setSelectedItem(int index)
      {
         ComboBox_SetCurSel(m_hwnd, index);
      }

      void ComboBox::deleteItem(int index)
      {
         ComboBox_DeleteString(m_hwnd, index);
      }

      void ComboBox::removeAllItems()
      {
         ComboBox_ResetContent(m_hwnd);
      }
   } // namespace subsystem
//
//} // namespace windows
