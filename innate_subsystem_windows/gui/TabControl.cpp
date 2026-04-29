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
#include "TabControl.h"
#include "innate_subsystem/gui/Tab.h"
#include <commctrl.h>

namespace innate_subsystem_windows
{
   TabControl::TabControl()
   {
   }

   TabControl::~TabControl()
   {
      deleteAllTabs();
   }

   innate_subsystem::TabContainer &TabControl::getTabs()
   {

      return m_tabContainer;

   }

   innate_subsystem::TabInterface *TabControl::getTab(int index)
   {
      if ((index < 0) || ((size_t)index > m_tabContainer.size() - 1)) {
         return NULL;
      }
      return m_tabContainer[index];
   }

   void TabControl::addTab(innate_subsystem::DialogInterface *dialog, const char *caption)
   {
      auto ptab = create_newø<::innate_subsystem::Tab>();
      ptab->initialize_tab(dialog, caption);
      m_tabContainer.add(ptab);
      TCITEM tcitem = {0};
      tcitem.mask = TCIF_TEXT;
      TCHAR fixedCaption[255];
      ::wstring wstr(ptab->getCaption());
      _tcscpy(&fixedCaption[0], wstr.c_str());
      tcitem.pszText = fixedCaption;
      if (TabCtrl_InsertItem((HWND) _HWND(), m_tabContainer.size() - 1, &tcitem) == FALSE) {
         //
         // Handle error
         // ...
         //
      }
   }

   void TabControl::showTab(int index)
   {
      int selectedIndex = getSelectedTabIndex();
      if (selectedIndex >= 0) {
         getTab(selectedIndex)->setVisible(false);
      }
      TabCtrl_SetCurSel((HWND) _HWND(), index);
      getTab(index)->setVisible(true);
   }

   void TabControl::showTab(innate_subsystem::DialogInterface *dialog)
   {
      for (size_t i = 0; i < m_tabContainer.size(); i++) {
         if (m_tabContainer[i]->getDialog() == dialog) {
            showTab((int)i);
            return;
         }
      }
      _ASSERT(FALSE);
   }

   void TabControl::deleteAllTabs()
   {
      // for (size_t i = 0; i < m_tabContainer.size(); i++) {
      //    Tab *tab = m_tabContainer.at(i);
      //    delete tab;
      // }
      m_tabContainer.clear();
      TabCtrl_DeleteAllItems((HWND) _HWND());
   }

   void TabControl::removeTab(int index)
   {
      //int i = 0;
      //for (TabContainer::iterator it = m_tabContainer.begin(); it != m_tabContainer.end(); it++) {
        // if (i == index) {
            //delete *it;
            m_tabContainer.erase_at(index);
            TabCtrl_DeleteItem((HWND) _HWND(), index);
        //    break;
         //}
         //i++;
      //}
   }

   int TabControl::getSelectedTabIndex()
   {
      int page = TabCtrl_GetCurSel((HWND) _HWND());
      return page;
   }

   void TabControl::adjustRect(::int_rectangle &rect)
   {
      RECT rc;
      GetClientRect((HWND) _HWND(), &rc);
      TabCtrl_AdjustRect((HWND) _HWND(), FALSE, &rc);
      ::copy(&rect, &rc);

   }


   void TabControl::_000OnNotify(windows_reflect_notify_t & notify)
   {

      switch (notify.m_lpnmhdr->code)
      {
         case TCN_SELCHANGE:
         {
            _001OnTabChanged();
            break;
         }
         case TCN_SELCHANGING:
         {

            bool bOk = true;

            bool bHandled = _001OnTabChanging(bOk);

            if (bHandled)
            {

               notify.m_lresult = bOk ? TRUE : FALSE;

               notify.m_bHandled = true;

            }

            break;
         }
         break;
        }

   }

} // namespace innate_subsystem_windows
