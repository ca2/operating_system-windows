// Created from app_core_auraclick by camilo 2021-09-12 16:34 BRT <3ThomasBS_!!
#pragma once


#include "acme/_operating_system.h"


namespace input_win32
{


   class mouse_hook :
      virtual public ::particle
   {
   public:


      static bool                s_bMouseHook;
      static mouse_hook *        s_pmousehook;
      static ::task_pointer      s_ptaskMouse;
      static HHOOK               s_hhookMouse;

      
      mouse_hook();
      ~mouse_hook() override;


      virtual void install_mouse_hook();

      virtual void uninstall_mouse_hook();

      virtual bool is_mouse_hook_installed();

      virtual void _mouse_hook_task();

      static LRESULT CALLBACK LowLevelMouseProc(int nCode, WPARAM wParam, LPARAM lParam);

      virtual void mouse_proc(enum_message emessage);

   };


} // namespace input_win32



