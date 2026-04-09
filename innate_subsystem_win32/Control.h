// Copyright (C) 2008,2009,2010,2011,2012 GlavSoft LLC.
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

#pragma once

#include "apex/innate_subsystem/Control.h"
#include "innate_subsystem_win32/_common_header.h"


namespace innate_subsystem_win32
{


   //
   // Base class to control windows control
   //

   class Control :
      virtual public window_implementation<::innate_subsystem::ControlInterface>
   {
   public:


      //::pointer < Control > m_psubsystemcontrolThis;


      Control();
      //Control(HWND hwnd);
      ~Control()override;

      //
      // Sets HWND associated with this control
      //





      void initialize_control(const ::operating_system::window & window) override;

      //void setWindow(const ::operating_system::window & window) override;

      //
      // Changes enable state of this control
      //

      //void setEnabled(bool enabled) override;

      //
      // Sets text associated with window
      //

      void setText(const char *text) override;
      void setSignedInt(int value) override;
      void setUnsignedInt(unsigned int value) override;

      //
      // Sets text vertical alignment
      //

      void setTextVerticalAlignment(::innate_subsystem::VerticalAlignment align) override;


      //
      // Returns text vertical alignment
      //

      ::innate_subsystem::VerticalAlignment getTextVerticalAlignment() override;

      //
      // Gets HWND associated with this control
      //

      //::operating_system::window operating_system_window() override;

      //void operator= (const ::operating_system::window& window)
      //{
        // setWindow(window);
      //};

      //protected:

      //
      // Sets windows style for this control
      //

      //void setStyle(unsigned int styleFlags) override;

      //
      // Gets windows style for this control
      //

      //long long getStyle() override;

      //
      // Adds style to this control
      //

      //void addStyle(unsigned int styleFlag) override;

      //
      // Removes style from this control
      //

      //void removeStyle(unsigned int styleFlag) override;

      //
      // Returns true if styleFlags parameter is in
      // this control's style
      //

      //bool isStyleEnabled(unsigned int styleFlags) override;

      //
      // Private methods for manipulation window extended styles
      //

      //void setExStyle(unsigned int style) override;
      //void addExStyle(unsigned int styleFlag) override;
      //void removeExStyle(unsigned int styleFlag) override;

      //unsigned int getExStyle() override;
      //bool isExStyleEnabled(unsigned int styleFlag) override;

      //
      // Replaces default window proc with wndProc.
      //
      // This method must be called by child classes if needs to
      // override default window behavour.
      //

      //void replaceWindowProc(WNDPROC wndProc);

      // protected:
      //
      //    //
      //    // Handle of window
      //    //
      //
      //    HWND m_hwnd;
      //
      //    //
      //    // Pointer to default window procedure
      //    //
      //
      //    WNDPROC m_defWindowProc;
      void postUserMessage(unsigned int uMessage, ::wparam wparam, ::lparam lparam) override;


   };


} // namespace innate_subsystem_win32



