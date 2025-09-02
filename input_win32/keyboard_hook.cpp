// Moved from app_core_auratype by camilo 2021-09-12 16:31 BRT <3ThomasBS_!!
#include "framework.h"
#include "keyboard_hook.h"
#include "acme/constant/user_message.h"
#include "acme/constant/user_key.h"
#include "acme/exception/exception.h"
#include "acme/parallelization/task.h"
#include "acme/platform/scoped_restore.h"
#include "acme/prototype/prototype/particle.h"
#include "acme/_operating_system.h"
#include "aura/message/user.h"


namespace input_win32
{


   bool              keyboard_hook::s_bKeyboardHook = false;
   keyboard_hook *   keyboard_hook::s_pkeyboardhook = nullptr;
   ::task_pointer    keyboard_hook::s_ptaskKeyboard;
   HHOOK             keyboard_hook::s_hhookKeyboard = nullptr;


   keyboard_hook::keyboard_hook()
   {


   }


   keyboard_hook::~keyboard_hook()
   {


   }


   void keyboard_hook::install_keyboard_hook()
   {

      if (is_keyboard_hook_installed())
      {

         return;

      }

      s_bKeyboardHook = true;

      s_pkeyboardhook = this;

      s_ptaskKeyboard = app_fork([this]()
      {

         _keyboard_hook_task();

      });

   }

   
   bool keyboard_hook::is_keyboard_hook_installed()
   {

      return s_bKeyboardHook;

   }

   
   LRESULT CALLBACK keyboard_hook::LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
   {

      if (nCode == 0)
      {

         LPKBDLLHOOKSTRUCT pk = (LPKBDLLHOOKSTRUCT)lParam;

         if (wParam == ::user::e_message_key_down || wParam == ::user::e_message_sys_key_down)
         {

            auto eusermessage = (::user::enum_message)wParam;

            s_pkeyboardhook->keyboard_proc(eusermessage, pk->vkCode, pk->scanCode);

            //output_debug_string("X");

            //if (pk->vkCode == VK_MENU)
            //{

            //   alt = 1;

            //}
            //else if (pk->vkCode == '0')
            //{

            //   if (GetAsyncKeyState(VK_CONTROL) & 0x8000)
            //   {

            //      INPUT inputa[2];

            //      zero(inputa);

            //      inputa[0].type = INPUT_KEYBOARD;
            //      inputa[0].ki.dwFlags = KEYEVENTF_UNICODE;
            //      inputa[0].ki.wScan = 0xb7;

            //      inputa[1].type = INPUT_KEYBOARD;
            //      inputa[1].ki.dwFlags = KEYEVENTF_UNICODE | KEYEVENTF_KEYUP;
            //      inputa[1].ki.wScan = 0xb7;

            //      ::SendInput(2, inputa, sizeof(INPUT));

            //   }

            //}

         }
         else if (wParam == ::user::e_message_key_up || wParam == ::user::e_message_sys_key_up)
         {

            auto eusermessage = (::user::enum_message)wParam;

            s_pkeyboardhook->keyboard_proc(eusermessage, pk->vkCode, pk->scanCode);

            //output_debug_string("Y");

            //if (pk->vkCode == VK_MENU)
            //{

            //   alt = 0;

            //}

         }

      }

      return ::CallNextHookEx(s_hhookKeyboard, nCode, wParam, lParam);

   }


   void keyboard_hook::_keyboard_hook_task()
   {

      ::parallelization::set_priority(::e_priority_time_critical);

      MSG msg;

      ::PeekMessage(&msg, nullptr, 0, 0xffffffff, false);

      s_hhookKeyboard = SetWindowsHookEx(WH_KEYBOARD_LL, LowLevelKeyboardProc, ::LoadLibraryW(L"app_core_auratype.dll"), 0);

      ::SetTimer(NULL, NULL, 250, NULL);

      while (::task_get_run())
      {

         int iRet = ::GetMessage(&msg, 0, 0, 0xffffffff);

         if (iRet == 0)
         {

            break;

         }

         ::TranslateMessage(&msg);

         ::DispatchMessage(&msg);

      }

      try
      {

         UnhookWindowsHookEx(s_hhookKeyboard);

      }
      catch (...)
      {


      }

      s_hhookKeyboard = nullptr;

      s_bKeyboardHook = false;

      s_ptaskKeyboard = nullptr;

      s_ptaskKeyboard.release();

   }


   void install(::particle * pparticle)
   {


   }


   void keyboard_hook::uninstall_keyboard_hook()
   {

      if (s_ptaskKeyboard)
      {

         s_ptaskKeyboard->set_finish();

      }

   }


   void keyboard_hook::keyboard_proc(::user::enum_message eusermessage, int iVirtualKeyCode, int iScanCode)
   {

      auto pkey = øcreate_new < ::message::key >();

      pkey->m_eusermessage = eusermessage;

      if (iVirtualKeyCode == VK_RETURN)
      {

         pkey->m_ekey = ::user::e_key_return;

      }
      else if (iVirtualKeyCode == VK_SPACE)
      {

         pkey->m_ekey = ::user::e_key_space;

      }
      else
      {

         pkey->m_ekey = ::user::e_key_a;

      }

      handle_message(pkey);

   }


} // namespace keyboard_hook



