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


//#include "util/CommonHeader.h"

#include "apex/innate_subsystem/drawing/Icon.h"
#include "subsystem_win32/_common_header.h"


namespace innate_subsystem_win32
{


   class CLASS_DECL_INNATE_SUBSYSTEM_WIN32 Icon :
      virtual public ::subsystem::implementation<::innate_subsystem::IconInterface>
   {
   public:

      Icon();
      // Icon(HICON icon);
      // Icon(Bitmap *bitmap);
      // Icon(Bitmap *bitmap, Bitmap *mask);
      // Icon(DWORD icon);
      ~Icon() override;

      void * _HICON() override;

      virtual void initialize_icon(::innate_subsystem::IconInterface * picon) override;
      virtual void initialize_icon(::innate_subsystem::BitmapInterface *bitmap) override;
      virtual void initialize_icon(::innate_subsystem::BitmapInterface *bitmap, ::innate_subsystem::BitmapInterface *mask) override;
      virtual void initialize_icon(unsigned int icon) override;

      //void initi(HICON icon);
      //Icon(Bitmap *bitmap);
      //Icon(Bitmap *bitmap, Bitmap *mask);
      //Icon(DWORD icon);

   //protected:
      void fromBitmap(::innate_subsystem::BitmapInterface *bitmap, ::innate_subsystem::BitmapInterface *mask) override;

   // protected:
      HICON m_hicon;
      bool m_bHasOwnIcon;
   };


} // namespace innate_subsystem_win32


