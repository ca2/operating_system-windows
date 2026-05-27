// From apex/innate_ui/menu.cpp by camilo on 2026-05-19 16:52 <3ThomasBorregaardSørensen!!
#include "framework.h"
#include "menu.h"


namespace innate_ui_win32
{


   menu::menu() 
   {
   
      m_hmenuRoot = nullptr;

      m_hmenu = nullptr;
   
   }


   menu::~menu() {}


   void menu::load_menu_from_resource(::i32 iMenuResourceId)
   {

      
      m_hmenuRoot = LoadMenu(GetModuleHandle(0), MAKEINTRESOURCE(iMenuResourceId));

      if (!m_hmenuRoot)
      {

         throw ::exception(error_resource);
      }
      m_hmenu = GetSubMenu(m_hmenuRoot, 0);
      if (!m_hmenu)
      {

         throw ::exception(error_wrong_state);
      }


   }


   void menu::set_default_menu_item_command_id(::i32 iDefaultMenuItemCommandId)
   {

      SetMenuDefaultItem(m_hmenu, iDefaultMenuItemCommandId, false);

   }


   void menu::erase_menu_item_by_command_id(::i32 iDefaultMenuItemCommandId)
   {

      RemoveMenu(m_hmenu, iDefaultMenuItemCommandId, MF_BYCOMMAND);

   }
   
   void menu::track_popup_menu(
      const ::operating_system::window &operatingsystemwindow, const ::function<void(::i32)> &functionOnActionId)
   {
         POINT pos;

         if (!GetCursorPos(&pos))
         {
            pos.x = pos.y = 0;
         }


         HWND hwnd = ::as_HWND(operatingsystemwindow);

         /// SetForegroundWindow(operating_system_window());
         ///
         /// 
         
         ::SetForegroundWindow(hwnd);

         ::i32 action = TrackPopupMenu(m_hmenu, TPM_NONOTIFY | TPM_RETURNCMD | TPM_RIGHTBUTTON, pos.x, pos.y, 0,
                                     hwnd, NULL);

         functionOnActionId(action);
    
   }


} // namespace innate_ui
