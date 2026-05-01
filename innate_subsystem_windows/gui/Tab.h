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

#include "innate_subsystem/gui/Tab.h"
//#include "Control.h"
//#include "util/StringStorage.h"

namespace innate_subsystem_windows
{
   class CLASS_DECL_INNATE_SUBSYSTEM_WINDOWS Tab :
   virtual public ::Implementation<::innate_subsystem::TabInterface>
   {
   public:
      Tab();
      void initialize_tab(::innate_subsystem::WindowInterface *dialog, const char *caption) override;

      //
      // Access methods to protected members
      //

      void setCaption(const char *caption) override { m_caption = caption; }

      const char *getCaption() override;

      void setWindow(::innate_subsystem::WindowInterface  *pdialog) override;
      ::innate_subsystem::WindowInterface *getWindow() override;

      //
      // Method return true if tab has dialog
      //

      bool isOk();

      //
      // Changes visible state of dialog donates by this tab
      //

      void setVisible(bool visible);

   //protected:

      ::pointer < ::innate_subsystem::WindowInterface > m_pwindow;
      ::string m_caption;
   };


} // namespace innate_subsystem_windows