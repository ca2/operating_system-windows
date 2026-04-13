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
#include "framework.h"
#include "DeviceContext.h"

#include "Bitmap.h"
#include "../gui/PaintWindow.h"
#include "innate_subsystem/drawing/GraphicsObject.h"


namespace innate_subsystem_windows
{

   // class CarrierGraphicsObject :
   //    virtual public ::innate_subsystem::GraphicsObject
   // {
   // public:
   //
   //    HGDIOBJ m_hgdiobj = nullptr;
   //
   //
   //    bool is_temporary_graphics_object() const override
   //    {
   //
   //       return true;
   //
   //    }
   //
   //    void * _HGDIOBJ() override
   // {
   //
   //    return m_hgdiobj;
   //
   // }
   //
   // };

   // DeviceContext::DeviceContext(HWND window)
   // : m_hasOwnDC(false), m_wnd(window)
   // {
   //    m_dc = GetDC(window);
   // }
   //
   // DeviceContext::DeviceContext(DeviceContext* compatibleDevice)
   // : m_hasOwnDC(true)
   // {
   //    m_wnd = compatibleDevice->m_wnd;
   //    m_dc = CreateCompatibleDC(compatibleDevice->m_dc);
   // }
   //
   // DeviceContext::DeviceContext(PaintWindow* pntWnd)
   // : m_wnd(0), m_hasOwnDC(false)
   // {
   //    m_dc = pntWnd->getHDCPaint();
   // }

   DeviceContext::DeviceContext() :
   m_bHasOwnDC(false),
   m_hwnd(nullptr),
   m_hdc2(nullptr),
   m_pgraphics(nullptr)
   {


   }

   DeviceContext::~DeviceContext()
   {

      destroyDeviceContext();
   }


   void DeviceContext::destroyDeviceContext()
   {

      if (m_pgraphics)
      {

         delete m_pgraphics;

         m_pgraphics = nullptr;

      }

      if (m_hwnd && m_hdc2) {
         ReleaseDC(m_hwnd, m_hdc2);
      }
      if (m_bHasOwnDC) {
         DeleteDC(m_hdc2);
      }
      m_hwnd = nullptr;
      m_bHasOwnDC = false;
      m_hdc2 = nullptr;

   }


   void DeviceContext::initialize_device_context(const ::operating_system::window & operatingsystemwindow)
   {

      destroyDeviceContext();
      m_hwnd = ::as_HWND(operatingsystemwindow);
      m_hdc2 = ::GetDC(m_hwnd);
      m_pgraphics = new ::Gdiplus::Graphics(m_hdc2);

   }


   void DeviceContext::initialize_device_context(::innate_subsystem::DeviceContextInterface* pdevicecontext)
   {
      destroyDeviceContext();
      m_bHasOwnDC = true;
      ::cast < ::innate_subsystem_windows::DeviceContext > pdevicecontextWin32 = pdevicecontext;
      m_hwnd = nullptr;
      m_hdc2 = ::CreateCompatibleDC(pdevicecontextWin32->m_hdc2);
      m_pgraphics = new ::Gdiplus::Graphics(m_hdc2);
   }


   void DeviceContext::initialize_device_context(::innate_subsystem::BitmapInterface * pbitmap)
   {
      destroyDeviceContext();
      m_bHasOwnDC = false;
      ::cast < ::innate_subsystem_windows::Bitmap > pbitmapWin32 = pbitmap;
      m_hwnd = nullptr;
      m_hdc2 = nullptr;
      m_pgraphics = new ::Gdiplus::Graphics(pbitmapWin32->m_pbitmap);
   }


   void DeviceContext::_initialize_device_context(HDC hdc)
   {
      destroyDeviceContext();
      m_bHasOwnDC = true;
      m_hwnd = nullptr;
      m_hdc2 = ::CreateCompatibleDC(hdc);
      m_pgraphics = new ::Gdiplus::Graphics(m_hdc2);
   }

   void DeviceContext::_attach_HDC(HDC hdc)
   {
      destroyDeviceContext();
      m_bHasOwnDC = false;
      m_hwnd = nullptr;
      m_hdc2 = hdc;
      m_pgraphics = new ::Gdiplus::Graphics(m_hdc2);
   }

   void DeviceContext::initialize_device_context(innate_subsystem::PaintWindowInterface* ppaintwindow)
   {
      destroyDeviceContext();
      m_bHasOwnDC = true;
      auto pdevicecontextPaint = ppaintwindow->getPaintDeviceContext();
      auto pdevicecontextWin32 = pdevicecontextPaint-> impl<::innate_subsystem_windows::DeviceContext >() ;
      m_hdc2 = ::CreateCompatibleDC(pdevicecontextWin32->m_hdc2);
      m_pgraphics = new ::Gdiplus::Graphics(m_hdc2);
   }

   // HGDIOBJ DeviceContext::_selectObject2(HGDIOBJ object)
   // {
   //    return SelectObject(m_hdc, object);
   // }
   //
   // ::pointer < ::innate_subsystem::GraphicsObject>DeviceContext::selectObject(::innate_subsystem::GraphicsObject * pgraphicsobjectNew)
   // {
   //
   //    auto pgraphicsobjectOld = create_newø < ::innate_subsystem_windows::CarrierGraphicsObject >();
   //
   //    pgraphicsobjectOld->m_hgdiobj = _selectObject2((HGDIOBJ) pgraphicsobjectNew->_HGDIOBJ());
   //
   //    return pgraphicsobjectOld;
   //
   // }

} // namespace innate_subsystem_windows



