// Created by camilo on 2024-09-13 01:00 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "button.h"
#include "icon.h"


namespace innate_ui_win32
{


   button::button()
   {
   }


   button::~button()
   {

   }


   bool button::_on_command()
   {
      if (!m_callbackOnClick)
      {
         return false;

      }

         m_callbackOnClick();

         return true;
   }


   void button::_create_child(window * pwindowParent)
   {

      m_hwnd = CreateWindow(
         L"BUTTON",  // Predefined class; Unicode assumed 
         L"",      // Button text 
         WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
         10,         // x position 
         10,         // y position 
         100,        // Button width
         100,        // Button height
         pwindowParent->m_hwnd,     // Parent window
         NULL,       // No menu.
         (HINSTANCE)GetWindowLongPtr(pwindowParent->m_hwnd, GWLP_HINSTANCE),
         NULL);

   }


   void button::set_icon(::innate_ui::icon * piconParam)
   {

      ::pointer <icon > picon = piconParam;

      main_send([this, picon]()
      {

         //::SendMessage(m_hwnd, BM_SETICON, (WPARAM) picon->m_hicon, 0);

         });

   }


} // namespace innate_ui
