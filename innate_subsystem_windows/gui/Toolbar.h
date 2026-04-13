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

#include "innate_subsystem/gui/Toolbar.h"
#include "innate_subsystem_windows/_common_header.h"

#include <commctrl.h>

namespace innate_subsystem_windows
{
   class CLASS_DECL_INNATE_SUBSYSTEM_WINDOWS Toolbar :
virtual public window_implementation<innate_subsystem::ToolbarInterface>
   {
   public:
      Toolbar();
      virtual ~Toolbar();

      //static const int TB_Style_sep = 0;
      //static const int TB_Style_gap = 1;

      /////////////////////////////////////////////////////////
      // Auto mode procedures
      /////////////////////////////////////////////////////////

      // setViewAutoButtons()
      // It used only for auto buttons creation from
      // bitmap and making gaps or separators.
      void setViewAutoButtons(int iButton, int style) override;

      // loadToolbarfromRes()
      // This procedure will load a toolbar image from resource
      // id is a number of bitmap. It means that buttons are
      // square(for example 16x16).
      void loadToolbarfromRes(unsigned int id) override;

      // setButtonsRange()
      // If we want to catch the message from toolbar that some buttons
      // are pressed then we must set a range for message, we pass only
      // first item, and next is id+1 and so on.
      void setButtonsRange(unsigned int id) override;

      // attachToolbar()
      // This one will create and attach toolbar window to
      // which handle is passed in hwnd. Only for toolbar from bitmap.
      void attachToolbar(const ::operating_system::window & window) override;

      /////////////////////////////////////////////////////////
      // Manual mode procedures
      /////////////////////////////////////////////////////////

      // create() creates a windows toolbar. dwStyle is a combination of
      // the toolbar control and button styles. It returns true if successful,
      // or false otherwise.
      bool create(int tbID, const ::operating_system::window & windowParent,
           unsigned int dwStyle = WS_CHILD | WS_VISIBLE | TBSTYLE_FLAT) override;

      // addBitmap() adds one or more images from resources to
      // the list of button images available for a toolbar.
      // Returns the index of the first new image if successful,
      // or -1 otherwise.
      LRESULT addBitmap(int nButtons, unsigned int bitmapID) override;

      // addSystemBitmap() adds the system-defined button bitmaps to the list
      // of the toolbar button specifying by stdBitmapID. Returns the index of
      // the first new image if successful, or -1 otherwise.
      LRESULT addSystemBitmap(unsigned int stdBitmapID) override;

      // addNButton() adds nButtons buttons to a toolbar.
      bool addNButton(int nButtons, ::innate_subsystem::toolbar_button_t * ptoolbarbutton) override;

      // addButton() adds one button.
      bool addButton(int iBitmap, int idCommand, unsigned char state=TBSTATE_ENABLED,
                     unsigned char style=TBSTYLE_BUTTON,  unsigned int dwData=0, int iString=0) override;

      // checkButton() checks or unchecks a given button in a toolbar control.
      bool checkButton(int idButton, bool check) override;

      // enableButton() enables or disables the specified button
      // in the toolbar.
      bool enableButton(int idButton, bool enable) override;

      // pressButton() presses or releases the specified button in the toolbar.
      bool pressButton(int idButton, bool press) override;

      // getButtonRect() gets the bounding rectangle of a button in a toolbar.
      bool getButtonRect(int nIndex, ::int_rectangle & rectangle) override;

      // setButtonSize() sets the size of the buttons to be added to a toolbar.
      // Button size must be largen the button bitmap.
      bool setButtonsSize(const ::int_size & size) override;

      // autoSize() resizes the toolbar window.
      void autoSize() override;

      // getButtonsHeight() retrieves the height of the toolbar buttons.
      int getButtonsHeight() override;

      // getButtonsWidth() retrieves the width of the toolbar buttons.
      int getButtonsWidth() override;

      // isVisible() check the toolbar window on visible.
      bool isVisible() override;

      // hide() hides the toolbar window.
      void hide() override;

      // show() displays the toolbar window.
      void show() override;

      // getTotalWidth() returns the total size of all buttons and
      // separators in the toolbar.
      int getTotalWidth() override;

      // getHeight() returns the toolbar window height.
      int getHeight() override;

      // getState() gets button state
      LRESULT getState(int idButton) override;

      int m_initialStr;
      int m_numberTB;
      DWORD m_id;
      int m_width, m_height;
      HWND m_hWndToolbar;

      iptr_to_iptr m_autoButtons;
   };
} // namespace innate_subsystem_windows
