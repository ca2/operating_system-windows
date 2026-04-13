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



#include "innate_subsystem/Menu.h"
#include "innate_subsystem_windows/_common_header.h"


namespace innate_subsystem_windows
{
   
   class CLASS_DECL_INNATE_SUBSYSTEM_WINDOWS Menu :
      virtual public ::subsystem::implementation<innate_subsystem::MenuInterface>
   {
      public:
      Menu();
      ~Menu() override;

      void * _HMENU() override;
      void _setHMENU(void *pHMENU) override;
      bool getWindowMenu(innate_subsystem::WindowInterface * pwindow) override;
      void getSystemMenu(innate_subsystem::WindowInterface * pwindow) override;
      void create() override;
      bool loadMenu(const char * lpMenuName) override;
      void createPopupMenu() override;
      bool getSubMenu(int nPos, MenuInterface * pmenu) override;
      void termMenu() override;

      int getMenuItemCount() override;
      bool appendMenu(const ::scoped_string & scopedstr, unsigned int uID) override;
      bool appendSeparator() override;
      bool appendSubMenu(const ::scoped_string & scopedstr, MenuInterface *pMenu) override;

      bool insertMenuItem(unsigned int uItem, const ::scoped_string & scopedstr, unsigned int uID) override;
      bool insertCheckMenuItem(unsigned int uItem, const ::scoped_string & scopedstr, unsigned int uID) override;
      bool insertSeparator(unsigned int uItem) override;
      bool insertSubMenu(unsigned int uItem, const ::scoped_string & scopedstr, MenuInterface *pMenu) override;

      bool enableMenuItem(unsigned int uID, unsigned int uEnable) override;
      bool checkedMenuItem(unsigned int uID, bool bEnable) override;
      bool deleteMenu(unsigned int uPosition) override;

      int findMenuItem(unsigned int uID) override;

      bool setDefaultItem(unsigned int uID) override;

      // void operator= (HMENU hmenu)
      // {
      //    setMenu(hmenu) override;
      // }
      //
      // private:
      bool _appendMenu(unsigned int uFlags, ::uptr uptrNewItem, const char * lpNewItem);
      bool _insertMenuItem(unsigned int uItem, BOOL fByPosition, LPCMENUITEMINFO lpmii);
      bool _modifyMenu(unsigned int uPosition, unsigned int uFlags, LONG_PTR uIDNewItem, const char * lpNewItem);
      bool _setMenuItem(unsigned int uItem, BOOL fByPosition, LPMENUITEMINFO lpmii);

      //protected:
      HMENU m_hmenu;
      bool m_bCreated;

   };



} //  namespace innate_subsystem_windows




