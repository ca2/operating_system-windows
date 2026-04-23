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
// with this program; if not, w_rite to the Free Software Foundation, Inc.,
// 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
//-------------------------------------------------------------------------
//

#pragma once


#include "subsystem/_common_header.h"
//#include "innate_subsystem/gui/MessageWindow.h"
#include "subsystem/node/ClipboardListener.h"
//#include "log_writer/LogWriter.h"
#include "subsystem/thread/GuiThread.h"
#include "subsystem_windows/node/MessageWindow.h"
//#include "subsystem/node/MessageWindow.h"


namespace subsystem_windows
{


   class WindowsClipboard : protected MessageWindow, subsystem::GuiThread
   {
   public:


      WindowsClipboard(::subsystem::ClipboardListener *clipboardListener, ::subsystem::LogWriter *log);
      ~WindowsClipboard(void);

      // This function replaces clipboard content by the text
      virtual bool writeToClipBoard(const ::scoped_string &scopedstrText);

      virtual void readFromClipBoard(::string &clipDest) const;

   protected:
      virtual bool wndProc(unsigned int scopedstrMessage, ::wparam wParam, ::lparam lParam);

      virtual void execute();
      virtual void onTerminate();

      void convertToRfbFormat(const ::scoped_string &source, ::string &dest);
      void convertFromRfbFormat(const ::scoped_string &scopedstrSource, ::string &dest);

      HWND m_hwndNextViewer;

      ::subsystem::ClipboardListener *m_clipboardListener;

      ::subsystem::LogWriter *m_plogwriter;

      static const HINSTANCE m_hinst;
   };


} // namespace subsystem_windows 



