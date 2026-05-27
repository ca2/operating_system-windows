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
//
#pragma once



#include "innate_subsystem/gui/Menu.h"
#include "innate_subsystem_windows/_common_header.h"


namespace innate_subsystem_windows
{
   
   class CLASS_DECL_INNATE_SUBSYSTEM_WINDOWS Menu :
      virtual public Implementation<innate_subsystem::MenuInterface>
   {
      public:
      Menu();
      ~Menu() override;

      void * _HMENU() override;
      void _setHMENU(void *pHMENU) override;
      bool getWindowMenu(innate_subsystem::WindowInterface * pwindow) override;
      void getSystemMenu(innate_subsystem::WindowInterface * pwindow) override;
      void create() override;
      bool loadMenu(const ::i8 * lpMenuName) override;
      void createPopupMenu() override;
      bool getSubMenu(::i32 nPos, MenuInterface * pmenu) override;
      void termMenu() override;

      ::i32 getMenuItemCount() override;
      bool appendMenu(const ::scoped_string & scopedstr, ::u32 uID) override;
      bool appendSeparator() override;
      bool appendSubMenu(const ::scoped_string & scopedstr, MenuInterface *pMenu) override;

      bool insertMenuItem(::u32 uItem, const ::scoped_string & scopedstr, ::u32 uID) override;
      bool insertCheckMenuItem(::u32 uItem, const ::scoped_string & scopedstr, ::u32 uID) override;
      bool insertSeparator(::u32 uItem) override;
      bool insertSubMenu(::u32 uItem, const ::scoped_string & scopedstr, MenuInterface *pMenu) override;

      bool enableMenuItem(::u32 uID, ::u32 uEnable) override;
      bool checkedMenuItem(::u32 uID, bool bEnable) override;
      bool deleteMenu(::u32 uPosition) override;

      ::i32 findMenuItem(::u32 uID) override;

      bool setDefaultItem(::u32 uID) override;

      void trackPopupMenuOnCursorPosition(::innate_subsystem::WindowInterface * pwindowNotify, const function<void(::i32)> &onCommand) override;

      // void operator= (HMENU hmenu)
      // {
      //    setMenu(hmenu) override;
      // }
      //
      // private:
      bool _appendMenu(::u32 uFlags, ::uptr uptrNewItem, const ::i8 * lpNewItem);
      bool _insertMenuItem(::u32 uItem, BOOL fByPosition, LPCMENUITEMINFO lpmii);
      bool _modifyMenu(::u32 uPosition, ::u32 uFlags, LONG_PTR uIDNewItem, const ::i8 * lpNewItem);
      bool _setMenuItem(::u32 uItem, BOOL fByPosition, LPMENUITEMINFO lpmii);

      //protected:
      HMENU m_hmenu;
      bool m_bCreated;

   };



} //  namespace innate_subsystem_windows




