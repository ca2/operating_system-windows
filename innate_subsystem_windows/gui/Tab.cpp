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
#include "Tab.h"
namespace innate_subsystem_windows
{
      Tab::Tab()
      //: m_dialog(NULL)
      {
//         m_caption.setString(_T(""));
      }

      void Tab::initialize_tab(::innate_subsystem::WindowInterface *pwindow, const char *caption)

      {
         m_pwindow = pwindow;
         m_caption = caption;
      }
   const char *Tab::getCaption()
   {
         return m_caption;
      }

   void Tab::setWindow(::innate_subsystem::WindowInterface  *pwindow) { m_pwindow = pwindow; }
   ::innate_subsystem::WindowInterface *Tab::getWindow() { return m_pwindow; }

   //
   // Method return true if tab has dialog
   //

   bool Tab:: isOk() { return m_pwindow != NULL; }

      void Tab::setVisible(bool visible)
      {
         if (m_pwindow != NULL) {
            if (visible)
            {
               m_pwindow->show();

            }
            else
            {
               m_pwindow->hide();

            }
         }
      }

} // namespace innate_subsystem_windows