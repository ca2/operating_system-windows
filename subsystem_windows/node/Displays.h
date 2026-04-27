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
// with this program; if not, w_rite to the Free Software Foundation, Inc.,
// 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
//-------------------------------------------------------------------------
//

#pragma once



#include "subsystem/node/Displays.h"
#include "subsystem_windows/_common_header.h"


namespace subsystem_windows
{


   class CLASS_DECL_SUBSYSTEM_WINDOWS Displays :
      virtual public Implementation<::subsystem::DisplaysInterface >
   {
   public:


      int m_xVirtualScreen;
      int m_yVirtualScreen;

      ::int_rectangle_array_base m_displayRects;
      critical_section m_displayRectsMutex;

      static const unsigned int UPDATE_INTERVAL = 3000;
      class ::time m_latestUpdateTime;

      Displays();
      ~Displays() override;

      // If a display does not exist now the function return an empty rectangle.
      virtual void getDisplayCoordinates(unsigned char displayNumber, ::int_rectangle & rectangle)override;

      virtual ::int_rectangle_array_base getDisplaysCoords() override;

      // Returns a ::array_base that contain dispalys coordinates at the current time.
      virtual ::int_rectangle_array_base getDisplays() override;

      //private:
      // Updates internal information to a current state.
      virtual void update() override;

      static BOOL CALLBACK monitorEnumProc(HMONITOR hMonitor,
                                           HDC hdcMonitor,
                                           LPRECT lprcMonitor,
                                           LPARAM dwData);

      // Returns true if the update() function has been called lately.
      virtual bool isAlreadyUpdated() override;


   };


   // class CLASS_DECL_SUBSYSTEM_WINDOWS Displays :
   //    virtual public composite<DisplaysInterface>
   // {
   // public:
   //
   //
   //    Displays();
   //    ~Displays() override;
   //
   //    // If a display does not exist now the function return an empty rectangle.
   //    void getDisplayCoordinates(unsigned char displayNumber, ::int_rectangle *rect) override;
   //
   //    ::int_rectangle_array_base getDisplaysCoords() override;
   //
   //    // Returns a ::array_base that contain dispalys coordinates at the current time.
   //    ::int_rectangle_array_base getDisplays() override;
   //
   //    //private:
   //    // Updates internal information to a current state.
   //    void update() override;
   //
   //    // static BOOL CALLBACK monitorEnumProc(HMONITOR hMonitor,
   //    //                                      HDC hdcMonitor,
   //    //                                      LPRECT lprcMonitor,
   //    //                                      LPARAM dwData);
   //
   //    // Returns true if the update() function has been called lately.
   //    bool isAlreadyUpdated() override;
   //
   //    // int m_xVirtualScreen;
   //    // int m_yVirtualScreen;
   //    //
   //    // ::int_rectangle_array_base m_displayRects;
   //    // LocalMutex m_displayRectsMutex;
   //    //
   //    // static const unsigned int UPDATE_INTERVAL = 3000;
   //    // class ::time m_latestUpdateTime;
   // };

   //// __WINDOWSDISPLAYS_H__
   ///
}// namespace subsystem_windows
