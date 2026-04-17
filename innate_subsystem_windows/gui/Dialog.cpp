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
#include "framework.h"
#include "Dialog.h"

//#include "util/CommonHeader.h"

#include <commctrl.h>
#include <crtdbg.h>

#include "Window.h"


namespace innate_subsystem_windows
{

   Dialog::Dialog()
//   : m_ctrlParent(NULL), m_resourceName(0), m_resourceId(0), m_hicon(0)
   : m_resourceName(0), m_resourceId(0), m_hicon(0)
   {
   }

   // Dialog::Dialog(DWORD resourceId)
   // : m_ctrlParent(NULL), m_resourceName(0), m_resourceId(resourceId), m_hicon(0)
   // {
   // }
   //
   // Dialog::Dialog(const TCHAR *resourceName)
   // : m_ctrlParent(NULL), m_resourceName(0), m_resourceId(0), m_hicon(0)
   // {
   //    setResourceName(resourceName);
   // }

   Dialog::~Dialog()
   {
      if (m_hicon) {
         DeleteObject(m_hicon);
      }
      if (m_resourceName != 0) {
         free(m_resourceName);
      }
   }

   void Dialog::initialize_dialog(unsigned int resourceId)
   //: m_ctrlParent(NULL), m_resourceName(0), m_resourceId(resourceId), m_hicon(0)
   {

      m_resourceId = resourceId;
   }
void
   Dialog::initialize_dialog(const char *resourceName)
   //: m_ctrlParent(NULL), m_resourceName(0), m_resourceId(0), m_hicon(0)
   {
      setResourceName(resourceName);
   }


   void Dialog::setResourceName(const char * resourceName)
   {
      if (m_resourceName != 0) {
         free(m_resourceName);
      }

      m_resourceName = _strdup(resourceName);
   }

   void Dialog::setResourceId(unsigned int id)
   {
      m_resourceId = id;
   }

   void Dialog::setDefaultPushButton(unsigned int buttonId)
   {
      SendMessage(m_hwnd, DM_SETDEFID, buttonId, 0);
   }

   // void Dialog::setParent(Control *ctrlParent)
   // {
   //    m_ctrlParent = ctrlParent;
   // }

   void Dialog::show()
   {
      if (m_hwnd == NULL) {
         create();
      } else {
         setForeground();
      }
      //return 0;
   }

   void Dialog::hide()
   {
      Window::hide();
   }

   void Dialog::closeDialog(int code)
   {
      // Destroy dialog
      if (!m_isModal) {
         DestroyWindow(m_hwnd);
      } else {
         EndDialog(m_hwnd, code);
      }
      // We have no valid hwnd, so forse set hwnd to NULL
      _setHWND(NULL);
   }

   void Dialog::create()
   {
      HWND window, parentWindow = NULL;

      if (m_pcontrolParent != NULL) {
         parentWindow = ::as_HWND(m_pcontrolParent->operating_system_window());
      }

      //window = CreateDialogParam(GetModuleHandle(NULL), (LPCWSTR) getResouceName(),
      window = CreateDialogParam((HINSTANCE)::system()->m_hinstanceMain, (LPCWSTR)getResouceName(), parentWindow,
                                 dialogProc, (::lparam)(::uptr)(::innate_subsystem_windows::Dialog *)this);

      m_isModal = false;

      _ASSERT(window != NULL);
   }

   int Dialog::showModal()
   {
      int result = 0;
      if (m_hwnd == NULL) {
         m_isModal = true;
         HWND parentWindow = (m_pcontrolParent != NULL) ?(HWND)m_pcontrolParent->_HWND() : (HWND) nullptr;
         //result = (int)DialogBoxParam(GetModuleHandle(NULL),
         result = (int)DialogBoxParam((HINSTANCE) system()->m_hinstanceMain,
                                      ::wstring(getResouceName()), parentWindow,
                                      dialogProc,(::lparam) (::uptr)(::innate_subsystem_windows::Dialog * )this);
      } else {
         setVisible(true);
         setForeground();
      }

      //
      // TODO: Place error notification here
      //

      if (result == -1) {
      }

      return result;
   }

   bool Dialog::isCreated()
   {
      bool isInit = m_hwnd != 0;

      if (!isInit) {
         return false;
      }

      return !!IsWindow(m_hwnd);
   }

   bool Dialog::onDrawItem(::wparam controlID, innate_subsystem::draw_item_t * pdrawitem)
   {
      return TRUE;
   }


   bool Dialog::_onDrawItem(::wparam controlID, LPDRAWITEMSTRUCT pdrawitem)
   {

      return true;

   }

   void Dialog::onMessageReceived(unsigned int uMsg, ::wparam wparam, ::lparam lparam)
   {
   }

   INT_PTR CALLBACK Dialog::dialogProc(HWND hwnd, unsigned int uMsg, WPARAM wparam, LPARAM lparam)
   {
      ::innate_subsystem_windows::Dialog * _this = nullptr;
      BOOL bResult;

      bResult = FALSE;
      if (uMsg == WM_INITDIALOG) {
         _this = (::innate_subsystem_windows::Dialog *)lparam;
         SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)_this);
         _this->_setHWND(hwnd);
         _this->updateIcon();
      } else {
         _this = (::innate_subsystem_windows::Dialog *)GetWindowLongPtr(hwnd, GWLP_USERDATA);
         if (_this == 0) {
            return FALSE;
         }
      }

      _this->onMessageReceived(uMsg, wparam, lparam);

      switch (uMsg) {
         case WM_INITDIALOG:
            bResult = _this->onInitDialog();
            break;
         case WM_NOTIFY:
         {
            LRESULT lresult = 0;
            if (_this->_000OnNotify(lresult, wparam, lparam))
            {

               return lresult;

            }
         }
            break;
         case WM_COMMAND:
            bResult =_this->onCommand(LOWORD(wparam), HIWORD(wparam));
            break;
         case WM_CLOSE:
            bResult = _this->onClose();
            break;
         case WM_DESTROY:
            bResult = _this->onDestroy();
            break;
         case WM_DRAWITEM:
            bResult = _this->_onDrawItem(wparam, (LPDRAWITEMSTRUCT)lparam);
            break;
      }

      return bResult;
   }

   char *Dialog::getResouceName()
   {
      if (m_resourceId != 0) {
         return (char *)MAKEINTRESOURCE(m_resourceId);
      }
      return m_resourceName;
   }

   // void Dialog::subControlById(ControlInterface *control, unsigned int id)
   // {
   //    control = GetDlgItem(m_hwnd, id);
   // }

   void Dialog::updateIcon()
   {
      if (m_hicon) {
         SetClassLongPtr(m_hwnd, GCLP_HICON, (LONG_PTR)m_hicon);
      }
   }

   void Dialog::loadIcon(unsigned int id)
   {
      if (m_hicon) {
         DeleteObject(m_hicon);
      }
      m_hicon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(id));
   }

   bool Dialog::setForeground()
   {
      //return m_ctrlThis.setForeground();
      return Control::setForeground();
   }

   bool Dialog::onInitDialog()
   {

      auto pcomposite = m_pdialogCallback.m_p;

      return pcomposite->onInitDialog();
   }

   // bool Dialog::_onNotify(int iControl, LPNMHDR lpnmhdr)
   // {
   //    return FALSE;
   // }

   bool Dialog::onCommand(unsigned int controlID, unsigned int notificationID)
   {
      return m_pwindowCallback->onCommand(controlID, notificationID);
      //return FALSE;
   }

   bool Dialog::onDestroy()
   {
      return FALSE;
   }

   bool Dialog::onClose()
   {
      return FALSE;
   }


   bool Dialog::dialog_procedure(iptr & iptrResult, unsigned int message, ::wparam wparam, ::lparam lparam)
   {

      return false;

   }

} // namespace innate_subsystem_windows
