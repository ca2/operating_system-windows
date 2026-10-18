// Created by camilo on 2024-09-13 00:36 <3ThomasBorregaardSorensen!!
#pragma once


#include "apex/innate_ui/button.h"
#include "window.h"


namespace innate_ui_win32
{


   class CLASS_DECL_INNATE_UI_WIN32 button :
      virtual public ::innate_ui_win32::window,
      virtual public ::innate_ui::button
   {
   public:



      button();
      ~button() override;


      void _create_child(window * pwindowParent) override;

      bool _on_command() override;

      bool _subclass_procedure(::lresult & lresult, ::u32 message, ::wparam wparam, ::lparam lparam) override;
      void paint_dark_button(HDC hdc);

      void set_icon(::innate_ui::icon * picon) override;

   };


} // namespace innate_ui_win32




