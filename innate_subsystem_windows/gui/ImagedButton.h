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


#include "innate_subsystem/gui/ImagedButton.h"
#include "innate_subsystem_windows/_common_header.h"
#include "innate_subsystem_windows/gui/Control.h"
#include <uxtheme.h>


namespace innate_subsystem_windows
{
    //
    // Owner draw button, that displays button with image and text.
    //

    class ImagedButton : //public Control
   virtual public Implementation<::innate_subsystem::ImagedButtonInterface>,
    virtual public Control
    {
    public:
        ImagedButton();
        ~ImagedButton();

        //
        // Draws this ownder-draw button.
        // This method must be called in WM_DRAWITEM message handler of parent control
        //

        virtual void drawItem(LPDRAWITEMSTRUCT dis);

        virtual void subclassWindow(const ::operating_system::window & window) override;

        virtual void _setHICON(HICON hicon, const ::int_size & size);
        //virtual void setIcon(::innate_subsystem::IconInterface * picon, const ::int_size & size, int flags, int iInitialSize = 1, int iGrow = 1) override;
       virtual void setIcon(::innate_subsystem::IconInterface * picon, const ::int_size & size) override;

    //private:

        //
        // Parameters:
        //
        // IN buttonRect - button area rectangle
        // IN isButtonPressed - flag that true if button pressed
        // IN textWidth - width of button text that will be drawn in pixels
        // IN textHeight - height of button text that will be drawn in pixels
        // IN imageWidth - width of image in pixels
        // IN imageHeight - height of image in pixels
        // OUT textRect - output text rectangle
        // OUT imageRect - output image rectangle
        //

        virtual void calcRect(RECT* buttonRect, bool isButtonPressed,
                      DWORD textWidth, DWORD textHeight,
                      DWORD imageWidth, DWORD imageHeight,
                      RECT * textRect, RECT* imageRect);

        virtual void drawIcon(HDC* dc, RECT* imageRect, bool isPressed, bool isDisabled);
    //protected:
      bool m_isUsingTheme;
      bool m_mouseOver;
      HTHEME m_theme;


         //Icon to display


      ::pointer < ::innate_subsystem_windows::Icon > m_picon;

       ::int_size m_size;
      //int m_iconWidth;
      //int m_iconHeight;
  //  private:
      virtual bool window_procedure(::lresult & lresult, unsigned int message, ::wparam wparam, ::lparam lparam);

   };

//#endif
} // namespace innate_subsystem_windows


