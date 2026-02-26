// Created by camilo on 2024-09-13 01:00 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "button.h"
#include "icon.h"
#include "acme/_operating_system.h"


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

      auto hwndParent = pwindowParent->_HWND();

      if (::is_null(hwndParent) || hwndParent == INVALID_HANDLE_VALUE)
      {

         throw ::exception(error_bad_argument, "Parent window handle is null or INVALID_HANDLE_VALUE");
      }

      auto hinstanceParent = (HINSTANCE)GetWindowLongPtr(hwndParent, GWLP_HINSTANCE);

      if (::is_null(hinstanceParent))
      {

         throw ::exception(error_wrong_state, "Parent window hinstance is null");
      }

      auto hwndResult =
         ::CreateWindow(
         L"BUTTON",  // Predefined class; Unicode assumed 
         L"",      // Button text 
         WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
         10,         // x position 
         10,         // y position 
         100,        // Button width
         100,        // Button height
         hwndParent, // Parent window
         NULL,       // No menu.
         hinstanceParent,
         NULL);

      if (!hwndResult || !_HWND() || hwndResult != _HWND())
      {

         throw ::exception(error_failed);

      }

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
