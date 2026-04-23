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
// with this program; if not, w_rite to the Free Software Foundation, Inc.,
// 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
//-------------------------------------------------------------------------
//

#pragma once


//#include "subsystem/winhdr.h"
#include "acme/prototype/collection/comparable_list.h"
#include "subsystem/node/OperatingSystemApplication.h"
#include "subsystem_windows/_common_header.h"

//#include "remoting/remoting/thread/LocalMutex.h"
//#include <list>

namespace subsystem_windows
{
      /**
       * Base Windows Application class.
       * Have hidden main window and main scopedstrMessage loop.
       */
      class CLASS_DECL_SUBSYSTEM_WINDOWS OperatingSystemApplication :
      virtual public Implementation< ::subsystem::OperatingSystemApplicationCallback >
      {
      public:

         int m_iExitCode = 0;
         /**
          * Creates WindowsApplication instance.
          * @param appInstance parameter that passed to WinMain.
          */

         OperatingSystemApplication();
         /**
          * Destroys WindowsApplication instance.
          * @remark it does not shutdown application if it's executing it
          * separate thread.
          */
         ~OperatingSystemApplication() override;


         void initialize_operating_system_application() override;


         void doDefaultMainLoop() override;
         //virtual void initialize_operating_system_application(const ::scoped_string & scopedstrwindowClassName);

         /**
          * Runs windows application.
          * @remark really it creates main window and starts windows scopedstrMessage loop.
          * @return application exit code.
          */
         void run() override;

         /**
          * Posts close and destroy scopedstrMessage to main window.
          */
         void shutdown() override;

         /**
          * Posts scopedstrMessage to main window.
          */
         void postMessage(unsigned int message, ::wparam wparam = 0, ::lparam lparam = 0) override;

         /**
          * Adds modeless dialog to application modeless dialog ::list_base to
          * enable switching between controls by pressing tab button.
          * @param dialogWindow HWND of modeless dialog.
          */
         void addModelessDialog(const ::operating_system::window &operatingsystemwindow) override;

         /**
          * Removes dialog from application modeless dialog ::list_base.
          * @param dialogWindow HWND of modeless dialog.
          */
         void removeModelessDialog(const ::operating_system::window &operatingsystemwindow) override;

         //protected:
         // Creates a window to receive messages.
         //virtual void createWindow(const ::scoped_string & scopedstrClassName);

         //protected:
         // Creates a window to receive messages.
         //virtual void createWindow(const ::scoped_string & scopedstrClassName) = 0;
         void createApplicationMainTask() override;


         //virtual void postMainThreadMessage(int iMainThreadMessage) override;


         int getExitCode() override;

         // Fills the wndClass argument and registers new class name in the Windows.
         //virtual void registerWindowClass(WNDCLASS *wndClass);

         // Runs main messages process cycle. The run() function returns
         // value returned by this function.
         //virtual int processMessages();

         /**
          * Windows prodecure for main application window.
          */
         //static LRESULT CALLBACK wndProc(HWND hWnd, UINT msg, WPARAM wparam, LPARAM lparam);

         HINSTANCE m_appInstance;
         HWND m_mainWindow;
         ::wstring m_wstrWindowClassName;
         //protected:
         /**
          * Helper method to process modeless dialog scopedstrMessage for modal dialog.
          * @param msg scopedstrMessage to process.
          * @return true if don't need to translate and dispatch scopedstrMessage in main scopedstrMessage loop.
          */
         bool processDialogMessage(MSG *msg);
         //private:
         critical_section m_MDLMutex; // Modeless dialog ::list_base mutex.
         ::comparable_list_base<HWND> m_modelessDialogList;

         void onMainThreadMessage(unsigned int message, ::wparam wparam, ::lparam lparam) override;

      };

      //// __WINDOWSAPPLICATION_H__
} // namespace subsystem_windows