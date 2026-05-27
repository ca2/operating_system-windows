// From apex/innate_ui/menu.h by camilo on 2026-05-19 16:52 <3ThomasBorregaardSørensen!!
#pragma once


#include "apex/innate_ui/menu.h"


namespace innate_ui_win32
{


   class CLASS_DECL_INNATE_UI_WIN32 menu : virtual public ::innate_ui::menu
   {
   public:


      HMENU m_hmenuRoot;
      HMENU m_hmenu;


      menu();
      ~menu() override;


      void load_menu_from_resource(::i32 iMenuResourceId) override; 
      void set_default_menu_item_command_id(::i32 iDefaultMenuItemCommandId) override; 

      void erase_menu_item_by_command_id(::i32 iDefaultMenuItemCommandId) override; 

      void track_popup_menu(const ::operating_system::window &operatingsystemwindow,
                            const ::function<void(::i32)> &functionOnActionId) override;




   };


} // namespace innate_ui
