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
#include "framework.h"
#include "Menu.h"

#include "innate_subsystem/gui/Window.h"


namespace innate_subsystem_windows
{
   Menu::Menu()
   : m_hmenu(0),
     m_bCreated(false)
   {
   }

   void * Menu::_HMENU()
    {
       return m_hmenu;
    }

   void Menu::_setHMENU(void * pHMENU)
   {
      _ASSERT(m_hmenu == 0);

      m_hmenu = (HMENU) pHMENU;
   }

   bool Menu::getWindowMenu(innate_subsystem::WindowInterface * pwindow)
   {
      _ASSERT(m_hmenu == 0);


      auto hwnd = ::as_HWND(pwindow->operating_system_window());

      m_hmenu = GetMenu(hwnd);
      return (m_hmenu == 0 ? false : true);
   }

   void Menu::getSystemMenu(innate_subsystem::WindowInterface * pwindow)
   {
      _ASSERT(m_hmenu == 0);

      auto hwnd = ::as_HWND(pwindow->operating_system_window());

      m_hmenu = GetSystemMenu(hwnd, FALSE);
   }

   void Menu::create()
   {
      _ASSERT(m_hmenu == 0);

      m_hmenu = CreateMenu();
      m_bCreated = true;
   }

   bool Menu::loadMenu(const ::i8 * lpMenuName)
   {
      _ASSERT(m_hmenu == 0);

      m_hmenu = LoadMenu(GetModuleHandle(0), wstring(lpMenuName));
      m_bCreated = true;
      return (!m_hmenu?false:true);
   }

   void Menu::createPopupMenu()
   {
      _ASSERT(m_hmenu == 0);

      m_hmenu = CreatePopupMenu();
      m_bCreated = true;
   }

   ::i32 Menu::getMenuItemCount()
   {
      _ASSERT(m_hmenu != 0);

      return GetMenuItemCount(m_hmenu);
   }

   bool Menu::_appendMenu(::u32 uFlags, ::uptr uIDNewItem, const ::i8 * lpNewItem)
   {
      _ASSERT(m_hmenu != 0);

      return !!AppendMenu(m_hmenu, uFlags, uIDNewItem,::wstring( lpNewItem));
   }

   bool Menu::_insertMenuItem(::u32 uItem, BOOL fByPosition, LPCMENUITEMINFO lpmii)
   {
      _ASSERT(m_hmenu != 0);

      return !!InsertMenuItem(m_hmenu, uItem, fByPosition, lpmii);
   }

   bool Menu::_modifyMenu(::u32 uPosition, ::u32 uFlags, LONG_PTR uIDNewItem, const ::i8 * lpNewItem)
   {
      _ASSERT(m_hmenu != 0);

      return !!ModifyMenu(m_hmenu, uPosition, uFlags, uIDNewItem, ::wstring(lpNewItem));
   }

   bool Menu::deleteMenu(::u32 uPosition)
   {
      _ASSERT(m_hmenu != 0);

      return !!DeleteMenu(m_hmenu, uPosition, MF_BYPOSITION);
   }

   bool Menu::getSubMenu(::i32 nPos, ::innate_subsystem::MenuInterface *pmenu)
   {
      HMENU tmenu;

      _ASSERT(m_hmenu != 0 && pmenu);
      tmenu = GetSubMenu(m_hmenu, nPos);
      if (tmenu) {
         pmenu->_setHMENU(tmenu);
      }
      return (!tmenu?false:true);
   }

   bool Menu::enableMenuItem(::u32 uID, ::u32 uEnable)
   {
      _ASSERT(m_hmenu != 0);

      return !!EnableMenuItem(m_hmenu, uID, uEnable);
   }

   bool Menu::_setMenuItem(::u32 uItem, BOOL fByPosition, LPMENUITEMINFO lpmii)
   {
      _ASSERT(m_hmenu != 0);

      return !!SetMenuItemInfo(m_hmenu, uItem, fByPosition, lpmii);
   }

   void Menu::termMenu()
   {
      if (m_hmenu && m_bCreated) {
         DestroyMenu(m_hmenu);
      }
      m_hmenu = 0;
      m_bCreated = false;
   }

   Menu::~Menu()
   {
      if (m_hmenu && m_bCreated) {
         DestroyMenu(m_hmenu);
      }
   }

   ::i32 Menu::findMenuItem(::u32 uID)
   {
      _ASSERT(m_hmenu != 0);

      for (::i32 i = 0; i < getMenuItemCount(); i++) {
         if (GetMenuItemID(m_hmenu, i) == uID) {
            return i;
         }
      }
      return -1;
   }

   bool Menu::appendMenu(const ::scoped_string & scopedstr, ::u32 uID)
   {
      return _appendMenu(MF_STRING, uID, ::string(scopedstr));
   }

   bool Menu::appendSeparator()
   {
      return _appendMenu(MF_MENUBREAK, 0, nullptr);
   }

   bool Menu::appendSubMenu(const ::scoped_string & scopedstr, ::innate_subsystem::MenuInterface *pMenu)
   {
      return _appendMenu(MF_POPUP, (::uptr)pMenu->_HMENU(),::string(scopedstr));
   }

   bool Menu::insertMenuItem(::u32 uItem, const ::scoped_string & scopedstr, ::u32 uID)
   {
      MENUITEMINFO mii;
      ::wstring wstr(scopedstr);
      ZeroMemory(&mii, sizeof(MENUITEMINFO));
      mii.cbSize = sizeof(MENUITEMINFO);
      mii.fMask = MIIM_STRING | MIIM_ID;
      mii.dwTypeData = (LPTSTR)wstr.c_str();
      mii.fState = MFS_DEFAULT;
      mii.wID = uID;
      return _insertMenuItem(uItem, TRUE, (LPMENUITEMINFO)&mii);
   }

   bool Menu::insertCheckMenuItem(::u32 uItem, const ::scoped_string & scopedstr, ::u32 uID)
   {
      MENUITEMINFO mii;
      ::wstring wstr(scopedstr);
      ZeroMemory(&mii, sizeof(MENUITEMINFO));
      mii.cbSize = sizeof(MENUITEMINFO);
      mii.fMask = MIIM_STRING | MIIM_ID | MIIM_STATE;
      mii.dwTypeData = (LPTSTR)wstr.c_str();
      mii.fState = MFS_UNCHECKED;
      mii.wID = uID;
      return _insertMenuItem(uItem, TRUE, (LPMENUITEMINFO)&mii);
   }

   bool Menu::checkedMenuItem(::u32 uID, bool bEnable)
   {
      _ASSERT(m_hmenu != 0);

      ::i32 pos = findMenuItem(uID);
      if (pos == -1) {
         return false;
      }
      ::u32 command = bEnable ? MF_CHECKED : MF_UNCHECKED;
      DWORD res = CheckMenuItem(m_hmenu, pos, MF_BYPOSITION | command);
      return (res == -1) ? false : true;
   }

   bool Menu::insertSeparator(::u32 uItem)
   {
      MENUITEMINFO mii;

      ZeroMemory(&mii, sizeof(MENUITEMINFO));
      mii.cbSize = sizeof(MENUITEMINFO);
      mii.fType = MFT_SEPARATOR;
      return _insertMenuItem(uItem, TRUE, (LPMENUITEMINFO)&mii);
   }

   bool Menu::insertSubMenu(::u32 uItem, const ::scoped_string & scopedstr, ::innate_subsystem::MenuInterface *pMenu)
   {
      MENUITEMINFO mii;

      ZeroMemory(&mii, sizeof(MENUITEMINFO));
      mii.cbSize = sizeof(MENUITEMINFO);
      mii.fMask = MIIM_SUBMENU;
      mii.hSubMenu = (HMENU) pMenu->_HMENU();
      return _insertMenuItem(uItem, TRUE, (LPMENUITEMINFO)&mii);
   }

   bool Menu::setDefaultItem(::u32 uID)
   {
      _ASSERT(m_hmenu != 0);

      return !!SetMenuDefaultItem(m_hmenu, uID, FALSE);
   }


   void Menu::trackPopupMenuOnCursorPosition(::innate_subsystem::WindowInterface * pwindowNotify, const function<void(::i32)> &onCommand)
   {

      m_papplication->fork([this, onCommand, pwindowNotify]()
         {

      POINT pos;

      if (!GetCursorPos(&pos)) {
         pos.x = pos.y = 0;
      }

      HWND notifyWnd = (HWND) ::as_HWND(pwindowNotify->operating_system_window());
      SetForegroundWindow(notifyWnd);

       ::i32 action = TrackPopupMenu(this->m_hmenu,
                                   TPM_NONOTIFY | TPM_RETURNCMD | TPM_RIGHTBUTTON,
                                   pos.x, pos.y, 0, notifyWnd, NULL);
         onCommand(action);
         });

      // switch (action) {
      //     case IDS_NEW_CONN:
      //         onNewConnection();
      //         break;
      //     case IDS_LISTENING_OPTIONS:
      //         onListeningOptions();
      //         break;
      //     case IDS_CONFIG:
      //         onConfiguration();
      //         break;
      //     case IDS_ABOUT_VIEWER:
      //         onAboutViewer();
      //         break;
      //     case IDS_CLOSE:
      //         onCloseListeningDaemon();
      //         break;
      //     default:
      //         _ASSERT(true);
      // }


   }

} // namespace innate_subsystem_windows



