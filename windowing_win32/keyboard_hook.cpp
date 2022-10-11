// Moved from app_core_auratype by camilo 2021-09-12 16:31 BRT <3ThomasBS_!!
#include "framework.h"
#include "acme/operating_system.h"
#include "keyboard_hook.h"


namespace keyboard_hook
{

   
   ::matter * g_pmatter = nullptr;

   HHOOK g_hhook = nullptr;

   int alt = 0;

   int g_bRun = false;

   LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
   {

      if (nCode == 0)
      {

         LPKBDLLHOOKSTRUCT pk = (LPKBDLLHOOKSTRUCT)lParam;

         if (wParam == e_message_key_down || wParam == e_message_sys_key_down)
         {

            auto emessage = (enum_message)wParam;

            g_pmatter->call(emessage, pk->vkCode, pk->scanCode, g_pmatter);

            output_debug_string("X");

            if (pk->vkCode == VK_MENU)
            {

               alt = 1;

            }
            else if (pk->vkCode == '0')
            {

               if (GetAsyncKeyState(VK_CONTROL) & 0x8000)
               {

                  INPUT inputa[2];

                  xxf_zeroa(inputa);

                  inputa[0].type = INPUT_KEYBOARD;
                  inputa[0].ki.dwFlags = KEYEVENTF_UNICODE;
                  inputa[0].ki.wScan = 0xb7;

                  inputa[1].type = INPUT_KEYBOARD;
                  inputa[1].ki.dwFlags = KEYEVENTF_UNICODE | KEYEVENTF_KEYUP;
                  inputa[1].ki.wScan = 0xb7;

                  ::SendInput(2, inputa, sizeof(INPUT));

               }

            }

         }
         else if (wParam == e_message_key_up || wParam == e_message_sys_key_up)
         {

            auto emessage = (enum_message)wParam;

            g_pmatter->call(emessage, pk->vkCode, pk->scanCode, g_pmatter);

            output_debug_string("Y");

            if (pk->vkCode == VK_MENU)
            {

               alt = 0;

            }

         }

      }

      return ::CallNextHookEx(g_hhook, nCode, wParam, lParam);

   }


   void run()
   {

      ::parallelization::set_priority(::e_priority_time_critical);

      MSG msg;

      ::PeekMessage(&msg, nullptr, 0, 0xffffffff, false);

      g_hhook = SetWindowsHookEx(WH_KEYBOARD_LL, LowLevelKeyboardProc, ::LoadLibraryW(L"app_core_auratype.dll"), 0);

      SetTimer(NULL, NULL, 250, NULL);

      while (::task_get_run() && g_bRun)
      {

         int iRet = ::GetMessage(&msg, 0, 0, 0xffffffff);

         if (iRet == 0)
         {

            break;

         }

         ::TranslateMessage(&msg);

         ::DispatchMessage(&msg);

      }

      UnhookWindowsHookEx(g_hhook);

      g_hhook = nullptr;

      //return ::success;

   }


   void install(::matter * pmatter)
   {

      if (g_hhook != nullptr)
      {

         //return true;

         return;

      }

      g_pmatter = pmatter;

      g_bRun = true;

      //return true;

   }


   void uninstall(::matter * pmatter)
   {

      if (g_hhook == nullptr)
      {

         //return false;

         throw ::exception(error_null_pointer);

      }

      g_bRun = false;

      //return true;

   }


} // namespace keyboard_hook



