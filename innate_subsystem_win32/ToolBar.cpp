// Copyright (C) 2011,2012 GlavSoft LLC.
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
#include "framework.h"
#include "Toolbar.h"
#include <CommCtrl.h>

TBBUTTON * copy(TBBUTTON * ptbb, ::innate_subsystem::toolbar_button_t * ptoolbarbutton)
{

   ptbb->dwData = ptoolbarbutton->dwData;
   ptbb->iString = ptoolbarbutton->iString;
   ptbb->iBitmap = ptoolbarbutton->iBitmap;
   ptbb->idCommand = ptoolbarbutton->idCommand;
   ptbb->fsState = ptoolbarbutton->fsState;
   ptbb->fsStyle = ptoolbarbutton->fsState;

   return ptbb;

}


namespace innate_subsystem_win32
{
   
   Toolbar::Toolbar()
   {
      INITCOMMONCONTROLSEX initCtrlEx;

      initCtrlEx.dwSize = sizeof(INITCOMMONCONTROLSEX);
      initCtrlEx.dwICC  = ICC_BAR_CLASSES;
      InitCommonControlsEx(&initCtrlEx);

      m_hWndToolbar = 0;
      m_initialStr = -1;
   }

   Toolbar::~Toolbar()
   {
      if (m_hWndToolbar) {
         DestroyWindow(m_hWndToolbar);
      }
   }

   bool Toolbar::create(int _tbID, const ::operating_system::window & windowParent, unsigned int dwStyle)
   {
      dwStyle |= WS_CHILD;

      _ASSERT(m_hWndToolbar == 0);
      // Create the Toolbar window
      m_hWndToolbar = CreateWindowEx(0, TOOLBARCLASSNAME, 0, dwStyle,
                                     0, 0, 0, 0,
                                     ::as_HWND(windowParent),
                                     (HMENU)(::iptr)_tbID,
                                     GetModuleHandle(0),
                                     0);
      if (m_hWndToolbar) {
         // It's required for backward compatibility
         SendMessage(m_hWndToolbar,
                     TB_BUTTONSTRUCTSIZE,
                     static_cast<::wparam>(sizeof(TBBUTTON)),
                     0);
      }
      return !!m_hWndToolbar;
   };

   void Toolbar::setViewAutoButtons(int iButton, int style)
   {
      m_autoButtons[iButton] = style;
   }

   void Toolbar::loadToolbarfromRes(unsigned int id)
   {
      BITMAP bmp;

      HBITMAP hbmp = LoadBitmap(GetModuleHandle(NULL),
                                MAKEINTRESOURCE(id));
      GetObject(hbmp, sizeof(BITMAP), &bmp);
      m_width = bmp.bmWidth;
      m_height = bmp.bmHeight;
      m_numberTB = m_width / m_height;
      m_id = id;
      DeleteObject(hbmp);
   }

   void Toolbar::setButtonsRange(unsigned int id)
   {
      m_initialStr = id;
   }

   void Toolbar::attachToolbar(const ::operating_system::window & window)
   {
      ::raw_array_base<TBBUTTON> tbuttons;

      for (int i=0; i < m_numberTB; i++) {
         TBBUTTON tbutton;

         ZeroMemory(&tbutton, sizeof(tbutton));
         if (m_autoButtons.find(i) != m_autoButtons.end()) {
            // TODO: paste here all your variants of possible
            // toolbar buttons
            switch(m_autoButtons[i]) {
               case ::innate_subsystem::TB_Style_sep:
                  tbutton.fsStyle = TBSTYLE_SEP;
                  tbuttons.add(tbutton);
                  break;
               case ::innate_subsystem::TB_Style_gap:
                  tbutton.iBitmap = I_IMAGENONE;
                  tbuttons.add(tbutton);
                  break;
            }
         }
         tbutton.iBitmap = i;
         tbutton.idCommand = m_initialStr == 0 ? 0 : m_initialStr + i;
         tbutton.fsState   = TBSTATE_ENABLED;
         tbutton.fsStyle   = TBSTYLE_BUTTON;
         tbuttons.add(tbutton);
      }
      m_autoButtons.clear();

      m_hWndToolbar = CreateToolbarEx(::as_HWND(window),
         WS_VISIBLE | WS_CHILD | TBSTYLE_TOOLTIPS | WS_CLIPSIBLINGS | TBSTYLE_FLAT | WS_BORDER,
         m_id,
         static_cast<int>(tbuttons.size()),
         GetModuleHandle(NULL),
         m_id,
         tbuttons.data(),
         static_cast<int>(tbuttons.size()),
         0, 0, 0, 0,
         sizeof(TBBUTTON));
      SendMessage(m_hWndToolbar, TB_SETINDENT, 4, 0);
   }

   bool Toolbar::enableButton(int idButton, bool enable)
   {
      LRESULT result = SendMessage(m_hWndToolbar, TB_ENABLEBUTTON,
                                   idButton, MAKELONG(enable, 0));
      return !!result;
   }

   bool Toolbar::pressButton(int idButton, bool press)
   {
      LRESULT result = SendMessage(m_hWndToolbar, TB_PRESSBUTTON,
                                   idButton, MAKELONG(press, 0));
      return !!result;
   }

   bool Toolbar::getButtonRect(int nIndex, ::int_rectangle & buttonRect)
   {
      RECT rc;
      LRESULT result = SendMessage(m_hWndToolbar, TB_GETITEMRECT,
                                   nIndex, (LPARAM)&rc);
      ::copy(buttonRect, rc);
      return !!result;
   }

   bool Toolbar::setButtonsSize(const ::int_size & size)
   {
      LRESULT result = SendMessage(m_hWndToolbar, TB_SETBUTTONSIZE,
                                   0, MAKELONG(size.cx, size.cy));
      if (result) {
         SendMessage(m_hWndToolbar, TB_AUTOSIZE, 0, 0);
         return true;
      }
      return false;
   }

   void Toolbar::autoSize()
   {
      LRESULT style = SendMessage(m_hWndToolbar, TB_GETSTYLE,  0, 0);
      if (style & CCS_NORESIZE) {
         RECT r;
         ::int_rectangle btnRect;
         GetClientRect(GetParent(m_hWndToolbar), &r);
         getButtonRect(0, btnRect);
         int height = getButtonsHeight() + btnRect.top * 2 + 2;
         SetWindowPos(m_hWndToolbar, HWND_TOP, 0, 0, r.right - r.left, height,
                      SWP_NOMOVE);
      } else {
         SendMessage(m_hWndToolbar, TB_AUTOSIZE, 0, 0);
      }
   }

   int Toolbar::getButtonsHeight()
   {
      return HIWORD(SendMessage(m_hWndToolbar, TB_GETBUTTONSIZE, 0, 0));
   }

   int Toolbar::getButtonsWidth()
   {
      return LOWORD(SendMessage(m_hWndToolbar, TB_GETBUTTONSIZE, 0, 0));
   }

   int Toolbar::getHeight()
   {
      RECT r;
      GetWindowRect(m_hWndToolbar, &r);
      return r.bottom - r.top;
   }

   int Toolbar::getTotalWidth()
   {
      SIZE size;
      SendMessage(m_hWndToolbar, TB_GETMAXSIZE, 0, reinterpret_cast<LPARAM>(&size));
      return size.cx;
   }

   void Toolbar::show()
   {
      ShowWindow(m_hWndToolbar, SW_SHOW);
   }

   void Toolbar::hide()
   {
      ShowWindow(m_hWndToolbar, SW_HIDE);
   }

   bool Toolbar::isVisible()
   {
      LRESULT style = GetWindowLong(m_hWndToolbar, GWL_STYLE);
      return !!(style & WS_VISIBLE);
   }

   bool Toolbar::checkButton(int idButton, bool check)
   {
      LRESULT result = SendMessage(m_hWndToolbar, TB_CHECKBUTTON,
              idButton, MAKELONG(check, 0));
      return !!result;
   }

   LRESULT Toolbar::getState(int idButton)
   {
      LRESULT result = SendMessage(m_hWndToolbar, TB_GETSTATE,
                       idButton, 0);
      return result;
   }

   LRESULT Toolbar::addBitmap(int nButtons, unsigned int bitmapID)
   {
      TBADDBITMAP resBitmap;

      resBitmap.hInst = GetModuleHandle(0);
      resBitmap.nID = bitmapID;
      return SendMessage(m_hWndToolbar, TB_ADDBITMAP, nButtons, (LPARAM)&resBitmap);
   }

   LRESULT Toolbar::addSystemBitmap(unsigned int stdBitmapID)
   {
      TBADDBITMAP resBitmap;

      resBitmap.hInst = HINST_COMMCTRL;
      resBitmap.nID = stdBitmapID;
      return SendMessage(m_hWndToolbar, TB_ADDBITMAP, 0, (::lparam)&resBitmap);
   }

   bool Toolbar::addButton(int iBitmap, int idCommand, BYTE state, BYTE style, unsigned int dwData, int iString)
   {
      TBBUTTON tbb;

      tbb.iBitmap = iBitmap;
      tbb.idCommand = idCommand;
      tbb.fsState = state;
      tbb.fsStyle = style;
      tbb.dwData = dwData;
      tbb.iString = iString;

      LRESULT result = SendMessage(m_hWndToolbar, TB_ADDBUTTONS, 1, (LPARAM)(&tbb));
      if (result) {
         SendMessage(m_hWndToolbar, TB_AUTOSIZE, 0, 0);
      }
      return !!result;
   }

   bool Toolbar::addNButton(int nButtons, ::innate_subsystem::toolbar_button_t * ptoolbarbutton)
   {
      TBBUTTON tbb{};
      copy(&tbb, ptoolbarbutton);
      LRESULT result = SendMessage(m_hWndToolbar, TB_ADDBUTTONS, nButtons, (LPARAM)&tbb);
      if (result) {
         SendMessage(m_hWndToolbar, TB_AUTOSIZE, 0, 0);
      }
      return !!result;
   }
} // namespace innate_subsystem_win32
