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


#include "innate_subsystem/drawing/DeviceContext.h"
#include "subsystem_win32/_common_header.h"
//#include "util/CommonHeader.h"
//#include "gui/PaintWindow.h"
#include <Gdiplus.h>

namespace innate_subsystem_win32
{


   class CLASS_DECL_INNATE_SUBSYSTEM_WIN32 DeviceContext :
      virtual public ::subsystem::implementation<::subsystem_apex::DeviceContextInterface>
   {
   public:
      // // Create device context linked to window DC.
      // DeviceContext(const ::operating_system::window & window);
      // // Create device context complatible with other DC.
      // DeviceContext(DeviceContext* compatibleDevice);
      // //private:
      // // Initialize class from PaintWindow
      // DeviceContext(class PaintWindow * pntWnd);
      DeviceContext();
      // Destroys device context.
       ~DeviceContext() override;


      //friend class PaintWindow;


      // Create device context linked to window DC.
      void initialize_device_context(const operating_system::window& window) override;
      // Create device context complatible with other DC.
      void initialize_device_context(DeviceContextInterface* compatibleDevice) override;
      virtual void initialize_device_context(::subsystem_apex::BitmapInterface * pbitmap);
      virtual void _initialize_device_context(HDC hdc);
      virtual void _attach_HDC(HDC hdc);
      //private:
      // Initialize class from PaintWindow
      void initialize_device_context(subsystem_apex::PaintWindowInterface* pntWnd) override;
      //protected:
      // Selects an object into this device context.
      //virtual HGDIOBJ _selectObject2(HGDIOBJ object);
//::pointer < ::subsystem_apex::GraphicsObject>selectObject(::subsystem_apex::GraphicsObject * pgraphicsobjectNew);

      void destroyDeviceContext() override;

      // protected:
      HDC m_hdc2;
      ::Gdiplus::Graphics * m_pgraphics;
      HWND m_hwnd;
      bool m_bHasOwnDC;

      // friend class Graphics;
      // friend class BitmapGraphics;
   };

} // namespace innate_subsystem_win32
