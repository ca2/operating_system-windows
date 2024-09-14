// Created by camilo on 2024-09-13 01:00 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "icon.h"
#include "still.h"


namespace innate_ui_win32
{


   still::still()
   {
      m_iCreateStyle = WS_TABSTOP | WS_VISIBLE | WS_CHILD | SS_LEFT;
   }


   still::~still()
   {

   }




   void still::_create_child(window * pwindowParent)
   {

      m_hwnd = CreateWindow(
         L"STATIC",  // Predefined class; Unicode assumed 
         L"",      // Button text 
         m_iCreateStyle,  // Styles 
         10,         // x position 
         10,         // y position 
         100,        // Button width
         100,        // Button height
         pwindowParent->m_hwnd,     // Parent window
         NULL,       // No menu.
         (HINSTANCE)GetWindowLongPtr(pwindowParent->m_hwnd, GWLP_HINSTANCE),
         NULL);

   }

   void still::create_icon_still(::innate_ui::window * pwindowParent)
   {

      m_iCreateStyle = WS_TABSTOP | WS_VISIBLE | WS_CHILD | SS_ICON | SS_REALSIZEIMAGE;

      create_child(pwindowParent);


   }


   void still::set_icon(::innate_ui::icon * piconParam)
   {

      ::pointer <::innate_ui_win32::icon > picon = piconParam;

      sync([this, picon]()
      {
         
         ::SendMessage(m_hwnd, STM_SETICON, (WPARAM) picon->m_hicon, 0);
         
         });

   }


} // namespace innate_ui
