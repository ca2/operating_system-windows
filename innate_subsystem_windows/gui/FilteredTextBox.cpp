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
#include "FilteredTextBox.h"
#include "innate_subsystem/gui/StringFilter.h"


namespace innate_subsystem_windows
{


   FilteredTextBox::FilteredTextBox()
   : m_wndprocOld(NULL)
   {
      //m_strText.setString(_T(""));
   }

   FilteredTextBox::~FilteredTextBox()
   {
   }

   void FilteredTextBox::setWindow(const ::operating_system::window & operatingsystemwindow)
   {

      auto hwnd = ::as_HWND(operatingsystemwindow);
      // if (hwnd != NULL) {
      //    m_wndprocOld = (WNDPROC) SetWindowLongPtr(hwnd, GWLP_WNDPROC, (LONG_PTR)&windowProc);
      //    SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)this);
      // } else {
      //    m_wndprocOld = NULL;
      // }
      _setHWND(hwnd);
   }

   void FilteredTextBox::setText(char *text)
   {
      m_strText = text;
      TextBox::setText(text);
   }

   void FilteredTextBox::setErrorBalloonTip(innate_subsystem::TooltipInterface *tip)
   {
      m_ptooltip = tip;
   }

   void FilteredTextBox::setStringFilter(::innate_subsystem::StringFilter *filter)
   {
      m_pstringfilter = filter;
   }

   LRESULT FilteredTextBox::makeCheck()
   {
      ::string updatedText;
      updatedText = TextBox::getText();
      if (isStringValid(updatedText)) {
         m_strText = updatedText;
      } else {
         if (m_ptooltip) {
            showBalloonTip(m_ptooltip);
            TextBox::setText(m_strText);
            TextBox::selectText(m_strText.length(), m_strText.length());
         } else {
            //
            // TODO: Play annoying sound this
            //
         }
         return -1;
      }
      return 0;
   }

   bool FilteredTextBox::isStringValid(const char *string)
   {
      if (m_pstringfilter != NULL) {
         return m_pstringfilter->isStringCorrect(string);
      }
      return true;
   }

   //
   // Return values: 0 - if window process this message
   //      other value - otherwise
   //

   LRESULT  FilteredTextBox::onKeyDown(::wparam code, ::lparam params)
   {
      return makeCheck();
   }


   bool FilteredTextBox::window_procedure(::lresult & lresult, unsigned int message, ::wparam wparam, ::lparam lparam)
   {

      if (message == WM_CHAR)
      {


         lresult = onKeyDown(wparam, lparam);

         return true;

      }


      return false;

   }
   // LRESULT FilteredTextBox::windowProc(HWND hwnd, unsigned int uMsg, WPARAM wparam, LPARAM lparam)
   // {
   //    FilteredTextBox *_this = (FilteredTextBox *)GetWindowLongPtr(hwnd, GWLP_USERDATA);
   //    if (_this == NULL) {
   //       return FALSE;
   //    }
   //    switch (uMsg) {
   //       case WM_CHAR:
   //          LRESULT result = CallWindowProc((WNDPROC)_this->m_wndprocOld, hwnd, uMsg, wparam, lparam);
   //          return _this->onKeyDown(wparam, lparam);
   //    }
   //    return CallWindowProc((WNDPROC)_this->m_wndprocOld, hwnd, uMsg,wparam, lparam);
   // }
} // namespace innate_subsystem_windows
