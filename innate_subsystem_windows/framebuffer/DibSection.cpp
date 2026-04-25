// Copyright (C) 2012 GlavSoft LLC.
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
#include "framework.h"
#include "subsystem_windows/_common_header.h"
#include "DibSection.h"
#include "innate_subsystem_windows/drawing/DeviceContext.h"
#include "subsystem_windows/node/Screen.h"
#include "subsystem/node/SystemException.h"
#include "subsystem/node/Screen.h"
#include "drawing/Bitmap.h"


namespace innate_subsystem_windows
{


   DibSection::DibSection() : m_memDC(nullptr), m_hbmOld(nullptr), m_targetDC(nullptr), m_hbmDIB(nullptr)
   {


   }


   // DibSection::DibSection(const ::innate_subsystem::PixelFormat & pf, const ::int_size & dim, const ::operating_system::window & operatingsystemwindowCompatible)
   // // : m_isOwnTargetDC(false),
   // //   m_targetDC(0),
   // //   m_memDC(0),
   // //   m_hbmOld(0),
   // //   m_hbmDIB(0),
   // //   m_srcOffsetX(0),
   // //   m_srcOffsetY(0),
   // //   m_buffer(0)
   // {
   //    initialize_dib_section(pf, dim, operatingsystemwindowCompatible);
   //    // try {
   //    //    openDIBSection(pf, dim, compatibleWin);
   //    // } catch (...) {
   //    //    closeDIBSection();
   //    //    throw;
   //    // }
   // }

   DibSection::~DibSection()
   {
      // try {
      //    closeDIBSection();
      // } catch (...) {
      // }
   }


   void DibSection::initialize_dib_section(const ::innate_subsystem::PixelFormat& pf, const int_size& dim, const operating_system::window& operatingsystemwindowCompatible)
   {

      //m_pparticleThis->initialize_dib_section(pf, dim, operatingsystemwindowCompatible);
      //construct_newø(m_pbitmapDib);
      //m_pbitmapDib->initialize_bitmap(dim);

               try {
                  _openDIBSection(pf, dim, ::as_HWND(operatingsystemwindowCompatible));
           } catch (...) {
              closeDIBSection();
              throw;
           }


   }


    void DibSection::setTargetDeviceContext(::innate_subsystem::DeviceContextInterface * pdevicecontextTarget)
    {
       releaseTargetDC();
       m_isOwnTargetDC = false;
       m_pdevicecontextTarget = pdevicecontextTarget;
       m_targetDC = m_pdevicecontextTarget->m_hdc2;
       ASSERT(m_targetDC != nullptr);
    }

   void *DibSection::getBuffer()
   {
      return m_buffer;
      //return m_pparticleThis->getBuffer();
   }

   void DibSection::blitToDibSection(const ::int_rectangle &  rect)
   {
      blitToDibSection(rect, SRCCOPY);
      //m_pparticleThis->blitToDibSection(rect);
   }

   void DibSection::blitTransparentToDibSection(const ::int_rectangle &  rect)
   {
      blitToDibSection(rect, SRCCOPY | CAPTUREBLT);
      //m_pparticleThis->blitTransparentToDibSection(rect);
   }

   void DibSection::blitFromDibSection(const ::int_rectangle &  rect)
   {
      blitFromDibSection(rect, SRCCOPY);
      //m_pparticleThis->blitFromDibSection(rect);
   }

   void DibSection::stretchFromDibSection(const ::int_rectangle &  srcRect,const ::int_rectangle & rectangleTarget)
   {
      stretchFromDibSection(srcRect, rectangleTarget, SRCCOPY);

      //m_pparticleThis->stretchFromDibSection(srcRect, rectangleTarget);
   }

   void DibSection::blitToDibSection(const ::int_rectangle &  rect, unsigned int flags)
   {
      // m_pparticleThis->blitToDibSection(rect, flags);
        if (BitBlt(m_memDC, rect.left, rect.top, rect.width(), rect.height(),
                   m_targetDC, rect.left + m_srcOffsetX,
                   rect.top + m_srcOffsetY, flags) == 0) {
          throw ::subsystem::Exception("Can't blit to DIB section.");
                  }
   }

   void DibSection::blitFromDibSection(const ::int_rectangle &  rect, unsigned int flags)
   {
      // m_pparticleThis->blitFromDibSection(rect, flags);
       if (BitBlt(m_targetDC, rect.left + m_srcOffsetX, rect.top + m_srcOffsetY,
                  rect.width(), rect.height(),
                 m_memDC, rect.left, rect.top, flags) == 0) {
          throw ::subsystem::Exception("Can't blit from DIB section.");
                 }
   }

   void DibSection::stretchFromDibSection(const ::int_rectangle &  srcRect,const ::int_rectangle & rectangleTarget, unsigned int flags)
   {
      // m_pparticleThis->stretchFromDibSection(srcRect, rectangleTarget, flags);
           SetStretchBltMode(m_targetDC, HALFTONE);
           if (StretchBlt(m_targetDC, srcRect.left + m_srcOffsetX, srcRect.top + m_srcOffsetY,
                          srcRect.width(), srcRect.height(),
                          m_memDC, rectangleTarget.left, rectangleTarget.top, rectangleTarget.width(), rectangleTarget.height(),
                          flags) == 0) 
           {
              throw ::subsystem::Exception("Can't strech blit from DIB section.");
                          }
        //}
   }
   
    void DibSection::_setupBMIStruct(BITMAPINFO *pBmi, const ::innate_subsystem::PixelFormat & pf, const ::int_size & dim)
    {
       if (pf.bitsPerPixel == 8) {
          subsystem_windows::Screen::Palette8bitBMI *paletteBMI =
             reinterpret_cast<subsystem_windows::Screen::Palette8bitBMI *>(pBmi);
          memset(paletteBMI, 0, sizeof(subsystem_windows::Screen::Palette8bitBMI));
          pBmi->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
          unsigned char index = 0;
          for (int i = 0; i < 256; i++, index++) {
             unsigned int red = (index >> pf.redShift) & pf.redMax;
             red = red * 0xFF / pf.redMax;
             paletteBMI->rgbQuad[index].rgbRed = (BYTE)red;
             unsigned int green = (index >> pf.greenShift) & pf.greenMax;
             green = green * 0xFF / pf.greenMax;
             paletteBMI->rgbQuad[index].rgbGreen = (BYTE)(green);
             unsigned int blue = (index >> pf.blueShift) & pf.blueMax;
             blue = blue * 0xFF / pf.blueMax;
             paletteBMI->rgbQuad[index].rgbBlue  = (BYTE)blue;
          }
       } else {
          ::subsystem_windows::Screen::BMI *bitFieldBmi = reinterpret_cast<::subsystem_windows::Screen::BMI *>(pBmi);
          memset(bitFieldBmi, 0, sizeof(::subsystem_windows::Screen::BMI));
          bitFieldBmi->bmiHeader.biCompression = BI_BITFIELDS;
          bitFieldBmi->red   = pf.redMax   << pf.redShift;
          bitFieldBmi->green = pf.greenMax << pf.greenShift;
          bitFieldBmi->blue  = pf.blueMax  << pf.blueShift;
       }
       pBmi->bmiHeader.biPlanes = 1;
       pBmi->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
       pBmi->bmiHeader.biBitCount = pf.bitsPerPixel;
       pBmi->bmiHeader.biWidth = dim.cx;
       pBmi->bmiHeader.biHeight = -dim.cy;
    }

    void DibSection::_openDIBSection(const ::innate_subsystem::PixelFormat & pf, const ::int_size & dim, HWND compatibleWin)
    {
       m_targetDC = GetDC(compatibleWin);
       m_isOwnTargetDC = true;
       if (m_targetDC == 0) {
          throw ::subsystem::SystemException("Can't get DC to create a DIB section");
       }
       if (compatibleWin == 0) {
          // In this special case is needed to store offset of the desktop, because coordinates
          // of the top level corner may be non zero.
          defer_constructø(m_pscreen);
          m_pscreen->update();
          ::int_rectangle deskRect = m_pscreen->getDesktopRect();
          m_srcOffsetX = deskRect.left;
          m_srcOffsetY = deskRect.top;
       }
   
       ::subsystem_windows::Screen::BMI bitFieldBmi;
       ::subsystem_windows::Screen::Palette8bitBMI paletteBMI;
       BITMAPINFO *pBmi = 0;
   
       if (pf.bitsPerPixel == 8) {
          pBmi = reinterpret_cast<BITMAPINFO *>(&paletteBMI);
       } else {
          pBmi = reinterpret_cast<BITMAPINFO *>(&bitFieldBmi);
       }
       _setupBMIStruct(pBmi, pf, dim);
   
       m_memDC = CreateCompatibleDC(m_targetDC);
       if (m_memDC == NULL) {
          throw ::subsystem::SystemException("Can't create a compatible DC to open a dib section");
       }
   
       m_hbmDIB = CreateDIBSection(m_memDC, (BITMAPINFO *)pBmi, DIB_RGB_COLORS, &m_buffer, NULL, NULL);
       if (m_hbmDIB == 0) {
          throw ::subsystem::SystemException("Can't create a dib section");
       }
   
       m_hbmOld = (HBITMAP)SelectObject(m_memDC, m_hbmDIB);
    }

   void DibSection::closeDIBSection()
   {
      //m_pparticleThis->closeDIBSection();
       if (m_hbmOld != 0) {
          SelectObject(m_memDC, m_hbmOld);
          m_hbmOld = 0;
       }
      
       if (m_hbmDIB != 0) {
          DeleteObject(m_hbmDIB);
          m_hbmDIB = 0;
       }
      
       if (m_memDC != 0) {
          DeleteDC(m_memDC);
          m_memDC = 0;
       }
      
       releaseTargetDC();
   }

   void DibSection::releaseTargetDC()
   {
      //m_pparticleThis->releaseTargetDC();
       if (m_targetDC != 0 && m_isOwnTargetDC) {
          ReleaseDC(0, m_targetDC);
          m_targetDC = 0;
       }
   }
} // namespace innate_subsystem_windows

