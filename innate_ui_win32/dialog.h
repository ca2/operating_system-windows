// Created by camilo on 2024-09-12 22:34 <3ThomasBorregaardSorensen!!
#pragma once


#include "apex/innate_ui/dialog.h"
#include "window.h"


namespace innate_ui_win32
{


   class CLASS_DECL_INNATE_UI_WIN32 dialog :
      virtual public ::innate_ui_win32::window,
      virtual public ::innate_ui::dialog
   {
   public:



      dialog();
      ~dialog() override;

      void create() override;
      void _create() override;
      void _get_class(WNDCLASSEXW & wcex);


      //void _show();

   };


} // namespace innate_ui_win32




