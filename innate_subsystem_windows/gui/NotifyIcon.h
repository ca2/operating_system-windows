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


#include "subsystem/_common_header.h"

#include "innate_subsystem/gui/NotifyIcon.h"

#include "innate_subsystem/drawing/Icon.h"

#include <shellapi.h>

namespace innate_subsystem_windows
{

   // FIXME: Add documentation to class.
   class CLASS_DECL_INNATE_SUBSYSTEM_WINDOWS NotifyIcon :
      virtual public ::subsystem::implementation< innate_subsystem::NotifyIconInterface>
   {
   public:
      NotifyIcon();
      virtual ~NotifyIcon();

      void initialize_notify_icon(bool showAfterCreation = true) override;

      ::innate_subsystem::IconInterface *getIcon()override;
      bool isVisible() const override;

      void setIcon(::innate_subsystem::IconInterface *icon) override;
      void setText(const char *text) override;

      void showBalloon(const char *message, const char *caption, unsigned int timeoutMillis) override;

      void show() override;
      void hide() override;

//   protected:
      NOTIFYICONDATA m_nid;
      ::pointer < ::innate_subsystem_windows::Icon > m_picon;
      bool m_visible;



   };

}// namespace innate_subsystem_windows




