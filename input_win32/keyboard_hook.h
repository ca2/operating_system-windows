// Created from app_core_auratype by camilo 2021-09-12 16:31 BRT <3ThomasBS_!!
#pragma once


#include "acme/_operating_system.h"


namespace input_win32
{


   class keyboard_hook :
      virtual public ::particle
   {
   public:


      static bool                s_bKeyboardHook;
      static keyboard_hook *     s_pkeyboardhook;
      static ::task_pointer      s_ptaskKeyboard;
      static HHOOK               s_hhookKeyboard;

      keyboard_hook();
      ~keyboard_hook() override;


      virtual void install_keyboard_hook();

      virtual void uninstall_keyboard_hook();

      virtual bool is_keyboard_hook_installed();

      virtual void _keyboard_hook_task();


      static LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam);

      virtual void keyboard_proc(enum_message emessage, int iVirtualKeyCode, int iScanCode);


   };


} // namespace input_win32


