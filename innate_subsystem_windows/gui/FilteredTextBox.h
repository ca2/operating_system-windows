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
//#ifndef _FILTERED_TEXT_BOX_H_
//#define _FILTERED_TEXT_BOX_H_

#pragma once


#include "innate_subsystem/gui/FilteredTextBox.h"
#include "innate_subsystem_windows/_common_header.h"
#include "innate_subsystem_windows/gui/TextBox.h"
//#include "BalloonTip.h"
//#include "StringFilter.h"
//#include "util/StringStorage.h"

namespace innate_subsystem_windows
{

   class CLASS_DECL_INNATE_SUBSYSTEM_WINDOWS FilteredTextBox : 
   virtual public window_implementation<innate_subsystem::FilteredTextBoxInterface, TextBox>
   {
   public:
      FilteredTextBox();
      ~FilteredTextBox() override;

      // Override Control::setWindow method
      void setWindow(const ::operating_system::window & operatingsystemwindow) override;
      void setText(char *text) override;
      void setErrorBalloonTip(innate_subsystem::TooltipInterface *tip) override;
      void setStringFilter(::innate_subsystem::StringFilter *filter) override;
      LRESULT makeCheck() override;

   //protected:
      bool isStringValid(const char *string) override;
      ::lresult onKeyDown(::wparam code, ::lparam params) override;

      //static LRESULT CALLBACK windowProc(HWND hwnd, unsigned int uMsg, WPARAM wparam, LPARAM lparam);

      virtual bool window_procedure(::lresult & lresult, unsigned int message, ::wparam wparam, ::lparam lparam);

   //protected:
      WNDPROC  m_wndprocOld;
      ::string  m_strText;
      ::pointer < ::innate_subsystem::TooltipInterface > m_ptooltip;
      ::pointer < ::innate_subsystem::StringFilter >m_pstringfilter;
   };

   //#endif
} //   namespace innate_subsystem_windows
