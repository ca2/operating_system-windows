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
// with this program; if not, write to the Free Software Foundation, Inc.,
// 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
//-------------------------------------------------------------------------
//
#include "framework.h"
// #include "DibFramebuffer.h"
// #include "util/Exception.h"
//
//
// namespace windows
// {
//    namespace subsystem
//    {
//       DibFramebuffer::DibFramebuffer()
//       : m_dibSection(0)
//       {
//       }
//
//       DibFramebuffer::~DibFramebuffer()
//       {
//          releaseDibSection();
//       }
//
//       void DibFramebuffer::setTargetDC(HDC targetDC)
//       {
//          checkDibValid();
//          m_dibSection->setTargetDC(targetDC);
//       }
//
//       bool DibFramebuffer::assignProperties(const Framebuffer * pframebufferSource)
//       {
//          throw Exception(_T("Wrong: You shouln't use the DibFramebuffer::assignProperties() function."));
//       }
//
//       bool DibFramebuffer::clone(const Framebuffer * pframebufferSource)
//       {
//          throw Exception(_T("Wrong: You shouln't use the DibFramebuffer::clone() function."));
//       }
//
//       void DibFramebuffer::setColor(unsigned int8 reg, unsigned int8 green, unsigned int8 blue)
//       {
//          m_fb.setColor(reg, green, blue);
//       }
//
//       void DibFramebuffer::fillRect(const ::int_rectangle &rectangleTarget, unsigned int32 color)
//       {
//          m_fb.fillRect(rectangleTarget, color);
//       }
//
//       bool DibFramebuffer::isEqualTo(const Framebuffer * pframebuffer)
//       {
//          return m_fb.isEqualTo(pframebuffer);
//       }
//
//       bool DibFramebuffer::copyFrom(const ::int_rectangle &rectangleTarget, const Framebuffer * pframebufferSource,
//                                     int srcX, int srcY)
//       {
//          return m_fb.copyFrom(rectangleTarget, pframebufferSource, srcX, srcY);
//       }
//
//       bool DibFramebuffer::copyFrom(const Framebuffer * pframebufferSource, int srcX, int srcY)
//       {
//          return m_fb.copyFrom(pframebufferSource, srcX, srcY);
//       }
//
//       bool DibFramebuffer::overlay(const ::int_rectangle &rectangleTarget, const Framebuffer * pframebufferSource,
//                                    int srcX, int srcY, const char *andMask)
//       {
//          return m_fb.overlay(rectangleTarget, pframebufferSource, srcX, srcY, andMask);
//       }
//
//       void DibFramebuffer::move(const ::int_rectangle &rectangleTarget, const int srcX, const int srcY)
//       {
//          m_fb.move(rectangleTarget, srcX, srcY);
//       }
//
//       bool DibFramebuffer::cmpFrom(const ::int_rectangle &rectangleTarget, const Framebuffer * pframebufferSource,
//                                    const int srcX, const int srcY)
//       {
//          return m_fb.cmpFrom(rectangleTarget, pframebufferSource, srcX, srcY);
//       }
//
//       bool DibFramebuffer::setDimension(const Dimension *newDim)
//       {
//          throw Exception(_T("Wrong: You shouln't use the DibFramebuffer::clone() function."));
//       }
//
//       bool DibFramebuffer::setDimension(const ::int_rectangle &rect)
//       {
//          throw Exception(_T("Wrong: You shouln't use the DibFramebuffer::clone() function."));
//       }
//
//       void DibFramebuffer::setEmptyDimension(const ::int_rectangle &dimByRect)
//       {
//          throw Exception(_T("This function is deprecated"));
//       }
//
//       void DibFramebuffer::setEmptyPixelFmt(const PixelFormat *pf)
//       {
//          throw Exception(_T("This function is deprecated"));
//       }
//
//       void DibFramebuffer::setPropertiesWithoutResize(const Dimension *newDim, const PixelFormat *pf)
//       {
//          throw Exception(_T("Wrong: You shouln't use the DibFramebuffer::setPropertiesWithoutResize() function."));
//       }
//
//       inline Dimension DibFramebuffer::getDimension() const
//       {
//          return m_fb.getDimension();
//       }
//
//       bool DibFramebuffer::setPixelFormat(const PixelFormat *pixelFormat)
//       {
//          throw Exception(_T("Wrong: You shouln't use the DibFramebuffer::setPixelFormat() function."));
//       }
//
//       inline PixelFormat DibFramebuffer::getPixelFormat() const
//       {
//          return m_fb.getPixelFormat();
//       }
//
//       bool DibFramebuffer::setProperties(const Dimension *newDim, const PixelFormat *pixelFormat)
//       {
//          throw Exception(_T("Wrong: You shouln't use this variant of the DibFramebuffer::setProperties() function."));
//       }
//
//       bool DibFramebuffer::setProperties(const ::int_rectangle &dimByRect, const PixelFormat *pixelFormat)
//       {
//          throw Exception(_T("Wrong: You shouln't use this variant of the DibFramebuffer::setProperties() function."));
//       }
//
//       unsigned int8 DibFramebuffer::getBitsPerPixel() const
//       {
//          return m_fb.getBitsPerPixel();
//       }
//
//       unsigned int8 DibFramebuffer::getBytesPerPixel() const
//       {
//          return m_fb.getBytesPerPixel();
//       }
//
//       void DibFramebuffer::setBuffer(void *newBuffer)
//       {
//          throw Exception(_T("Wrong: You shouln't use the DibFramebuffer::setBuffer() function."));
//       }
//
//       inline void *DibFramebuffer::getBuffer() const
//       {
//          return m_fb.getBuffer();
//       }
//
//       void *DibFramebuffer::getBufferPtr(int x, int y) const
//       {
//          return m_fb.getBufferPtr(x, y);
//       }
//
//       inline int DibFramebuffer::getBufferSize() const
//       {
//          return m_fb.getBufferSize();
//       }
//
//       inline int DibFramebuffer::getBytesPerRow() const
//       {
//          return m_fb.getBytesPerRow();
//       }
//
//       void DibFramebuffer::blitToDibSection(const ::int_rectangle &rect)
//       {
//          checkDibValid();
//          m_dibSection->blitToDibSection(rect);
//       }
//
//       void DibFramebuffer::blitTransparentToDibSection(const ::int_rectangle &rect)
//       {
//          checkDibValid();
//          m_dibSection->blitTransparentToDibSection(rect);
//       }
//
//       void DibFramebuffer::blitFromDibSection(const ::int_rectangle &rect)
//       {
//          checkDibValid();
//          m_dibSection->blitFromDibSection(rect);
//       }
//
//       void DibFramebuffer::stretchFromDibSection(const ::int_rectangle &srcRect, const ::int_rectangle &rectangleTarget)
//       {
//          checkDibValid();
//          m_dibSection->stretchFromDibSection(srcRect, rectangleTarget);
//       }
//
//       void DibFramebuffer::setProperties(const Dimension *newDim,
//                                          const PixelFormat *pixelFormat,
//                                          HWND compatibleWindow)
//       {
//          m_fb.setPropertiesWithoutResize(newDim, pixelFormat);
//          void *buffer = updateDibSection(newDim, pixelFormat, compatibleWindow);
//          m_fb.setBuffer(buffer);
//       }
//
//       void *DibFramebuffer::updateDibSection(const Dimension *newDim,
//                                             const PixelFormat *pixelFormat,
//                                             HWND compatibleWindow)
//       {
//          releaseDibSection();
//          m_dibSection = new DibSection(pixelFormat, newDim, compatibleWindow);
//          return m_dibSection->getBuffer();
//       }
//
//       void DibFramebuffer::releaseDibSection()
//       {
//          if (m_dibSection) {
//             delete m_dibSection;
//             m_dibSection = 0;
//             m_fb.setBuffer(0);
//          }
//       }
//
//       void DibFramebuffer::checkDibValid()
//       {
//          if (m_dibSection == 0) {
//             throw Exception(_T("Can't set target DC because it is not initialized a DIB section yet"));
//          }
//       }
//    } // namespace subsystem
// } // namespace windows