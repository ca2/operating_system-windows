// Copyright (C) 2008,2009,2010,2011,2012 GlavSoft LLC.
// All rights reserved.
//
//-------------------------------------------------------------------------
// This file is part of the T i g h t V N C software.  Please visit our Web site:
//
//                       http://www.t i g h t v n c.com/
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
#pragma once

#include "innate_subsystem/gui/Dialog.h"
#include "Control.h"


namespace innate_subsystem_windows
{


   class Dialog :
      virtual public window_implementation<::innate_subsystem::DialogCallback, Control>
      //, public Control
   {
   public:


      Dialog();


      // BaseDialog(::u32 resourceId);
      // BaseDialog(const ::i8 *resourceName);
      ~Dialog() override;


      //   public:

      void initialize_dialog(::u32 resourceId) override;


      void initialize_dialog(const ::i8 *resourceName) override;


      // Method creates non modal window but not shows it
      void create() override;


      //
      // Methods creates windows and show it in nonmodal/modal mode
      //

      void show() override;


      void doAttachedModal(const ::function < void(::i32) > & callback) override;


      ::i32 showModal() override;


      // Returns true if dialog is already created.
      bool isCreated() override;


      // Method hides window
      void hide() override;


      // Method closes dialog
      void closeDialog(::i32 code) override;


      // Method sets parent window
      //void setParent(::innate_subsystem::ControlInterface *ctrlParent) override;

      //
      // // Set resource name for dialog
      // void initialize_dialog(const ::i8 *resourceName) override;
      //
      //
      // // Set resource id for dialog.
      // void initialize_dialog(::u32 id) override;
      //

      // Return
      //::innate_subsystem::ControlInterface *getControl() override; // { return this; }
      // Setup control by ID
      //void subclassControlById(::innate_subsystem::ControlInterface *pcontrol, ::u32 id) override;


      // Icon manipulation
      void loadIcon(::u32 id) override;


      void updateIcon() override;


      // Puts this control foreground and activates it
      bool setForeground() override;


      //protected:
      /**
       * Sets default push button for dialog.
       * @pararm buttonId new default push button id.
       */
      void setDefaultPushButton(::u32 buttonId) override;


      //protected:

      //
      // This methods must be overrided by child classes.
      //

      bool onInitDialog() override;


      //bool onNotify(::u32 controlID, ::lparam data) override;


      bool onCommand(::u32 controlID, ::u32 notificationID) override;


      bool onClose() override;


      bool onDestroy() override;


      //
      // This methods can be overrided by child classes.
      //
      //#ifdef WINDOWS


      bool onDrawItem(::wparam controlID, ::innate_subsystem::draw_item_t * pdrawitem) override;


      virtual bool _onDrawItem(::wparam controlID, LPDRAWITEMSTRUCT pdrawitem);


      //#endif
      void onMessageReceived(::u32 uMsg, ::wparam wparam, ::lparam lparam) override;


      //
      // Window message proccessing method
      //

      static INT_PTR CALLBACK dialogProc(HWND hwnd, ::u32 uMsg, WPARAM wparam, LPARAM lparam);

      bool dialog_procedure(iptr &iptrResult, ::u32 message, ::wparam wparam, ::lparam lparam) override;


      //private:
      //::i8 *getResouceName() override;


      //protected:

      ::i8 *m_resourceName; // Name of dialog resource
      DWORD m_resourceId; // Id of dialog resouce
      //Control m_ctrlThis;           // This dialog control
      //::pointer<::innate_subsystem_windows::Control> m_pcontrolParent; // Parent dialog or NULL if no parent

      bool m_isModal;
      bool m_isCreated;

      HICON m_hicon;

   };



} // namespace innate_subsystem_windows



