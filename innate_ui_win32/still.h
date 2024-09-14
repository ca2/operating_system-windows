// Created by camilo on 2024-09-13 00:36 <3ThomasBorregaardSorensen!!
#pragma once


#include "apex/innate_ui/still.h"
#include "window.h"


namespace innate_ui_win32
{


   class CLASS_DECL_INNATE_UI_WIN32 still :
      virtual public ::innate_ui_win32::window,
      virtual public ::innate_ui::still
   {
   public:

      

      still();
      ~still() override;


      void _create_child(window * pwindowParent) override;
      void create_icon_still(::innate_ui::window * pwindowParent) override;

      void set_icon(::innate_ui::icon * picon) override;

   };


} // namespace innate_ui_win32




