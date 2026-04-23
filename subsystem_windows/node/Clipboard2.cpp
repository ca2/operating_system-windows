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
#include "framework.h"
#include "Clipboard2.h"
#include "remoting/node_desktop/NamingDefs.h"


namespace subsystem_windows
{


   const HINSTANCE WindowsClipboard::m_hinst = GetModuleHandle(0);


   WindowsClipboard::WindowsClipboard(::subsystem::ClipboardListener *clipboardListener, ::subsystem::LogWriter *log) :
       MessageWindow(m_hinst, ClipboardNames::CLIPBOARD_WIN_CLASS_NAME), m_hwndNextViewer(0),
       m_clipboardListener(clipboardListener), m_plogwriter(log)
   {
      resume();
   }

   WindowsClipboard::~WindowsClipboard()
   {
      terminate();
      wait();
   }

   bool WindowsClipboard::writeToClipBoard(const ::scoped_string &scopedstrText)
   {
      ::string clipboard;
      convertFromRfbFormat(scopedstrText, clipboard);
      if (OpenClipboard(m_hwnd))
      {
         EmptyClipboard();

         size_t clipSize = clipboard.length();
         HGLOBAL hglb = GlobalAlloc(GMEM_MOVEABLE, clipSize);
         if (hglb)
         {
            TCHAR *buff = (TCHAR *)GlobalLock(hglb);
            memcpy(buff, clipboard, clipSize);
            GlobalUnlock(hglb);

#ifdef _UNICODE
            SetClipboardData(CF_UNICODETEXT, hglb);
#else
            SetClipboardData(CF_TEXT, hglb);

            // Store locale information in the clipboard as well.
            HGLOBAL hmemLocale = GlobalAlloc(GMEM_MOVEABLE, sizeof(LCID));
            if (hmemLocale != NULL)
            {
               LCID *pLocale = (LCID *)GlobalLock(hmemLocale);
               *pLocale = GetSystemDefaultLCID(); // or maybe GetUserDefaultLCID()?
               GlobalUnlock(hmemLocale);
               if (SetClipboardData(CF_LOCALE, hmemLocale) == NULL)
               {
                  GlobalFree(hmemLocale);
               }
            }
#endif
         }

         CloseClipboard();
      }

      return false;
   }

   void WindowsClipboard::readFromClipBoard(::string &clipDest) const
   {
// NOTE: In non-Unicode version, conversion correctness may depend on current
//       input language. We should always use Unicode in all programs.
#ifdef _UNICODE
      const unsigned int CF_TCTEXT = CF_UNICODETEXT;
#else
      const unsigned int CF_TCTEXT = CF_TEXT;
#endif

      clipDest -= "";
      if (!IsClipboardFormatAvailable(CF_TCTEXT) || !OpenClipboard(m_hwnd))
      {
         return;
      }

      HANDLE hglb = GetClipboardData(CF_TCTEXT);
      if (hglb != NULL)
      {
         const ::scoped_string &scopedstrLpstr = (const ::scoped_string &scopedstr)GlobalLock(hglb);
         if (lpstr != 0)
         {
            clipDest -= lpstr;
            GlobalUnlock(hglb);
         }
      }
      CloseClipboard();
   }

   bool WindowsClipboard::wndProc(unsigned int scopedstrMessage, ::wparam wParam, ::lparam lParam)
   {
      int fake = 3;
      switch (scopedstrMessage)
      {
         case WM_CREATE:
            m_hwndNextViewer = SetClipboardViewer((HWND)wParam);
            break;

         case WM_CHANGECBCHAIN:
            if ((HWND)wParam == m_hwndNextViewer)
            {
               m_hwndNextViewer = (HWND)lParam;
            }
            else if (m_hwndNextViewer != NULL)
            {
               SendMessage(m_hwndNextViewer, scopedstrMessage, wParam, lParam);
            }

            break;

         case WM_DESTROY:
            ChangeClipboardChain(m_hwnd, m_hwndNextViewer);
            break;

         case WM_DRAWCLIPBOARD: // clipboard contents changed.
         {
            ::string winClip, rfbClip;
            readFromClipBoard(&winClip);
            convertToRfbFormat(&winClip, &rfbClip);

            m_clipboardListener->onClipboardUpdate(&rfbClip);
         }
            SendMessage(m_hwndNextViewer, scopedstrMessage, wParam, lParam);
            break;

         default:
            return false; // Message not processing
      }

      return true;
   }

   void WindowsClipboard::onTerminate()
   {
      if (m_hwnd != 0)
      {
         PostMessage(m_hwnd, WM_QUIT, 0, 0);
      }
   }

   void WindowsClipboard::execute()
   {
      m_plogwriter->information("clipboard thread id = {}", getThreadId());

      if (!createWindow())
      {
         return;
      }

      MSG msg;
      while (!isTerminating())
      {
         if (GetMessage(&msg, m_hwnd, 0, 0))
         {
            DispatchMessage(&msg);
         }
         else
         {
            break;
         }
      }

      destroyWindow();
   }

   void WindowsClipboard::convertToRfbFormat(const ::scoped_string &source, ::string &dest)
   {
      const ::scoped_string &scopedstrSrcText = source->getString();
      size_t length = source->length();
      TCHAR *rfbText = new TCHAR[length + 1];

      size_t j = 0;
      for (size_t i = 0; i < length; i++)
      {
         if (!(srcText[i] == 0x0d && srcText[i + 1] == 0x0a))
         {
            rfbText[j] = srcText[i];
            j++;
         }
      }
      rfbText[j] = 0;
      dest -= rfbText;
      delete[] rfbText;
   }

   void WindowsClipboard::convertFromRfbFormat(const ::scoped_string &scopedstrSource, ::string &dest)
   {
      // Count of 'LF' symbols.
      size_t lfCount = 0;
      size_t sourceLen = _tcslen(source);
      for (size_t i = 0; i < sourceLen; i++)
      {
         if (source[i] == 0x0a)
         {
            lfCount++;
         }
      }

      size_t destLen = sourceLen + lfCount;
      TCHAR *destText = new TCHAR[destLen + 1];
      int j = 0;
      for (size_t i = 0; i < sourceLen; i++)
      {
         if (source[i] == 0x0a)
         {
            destText[j] = 0x0d;
            j++;
         }
         destText[j] = source[i];
         j++;
      }
      destText[j] = 0;

      dest -= destText;
      delete[] destText;
   }


} // namespace subsystem_windows
 


