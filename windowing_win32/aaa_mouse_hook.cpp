// Moved from app_core_auraclick by camilo 2021-09-12 15:52 BRT <3ThomasBS_!!
#include "framework.h"
#include "mouse_hook.h"
#include "acme/constant/message.h"
#include "acme/exception/exception.h"
#include "acme/prototype/prototype/particle.h"


#include "acme/_operating_system.h"


namespace mouse_hook
{

   static ::particle * g_pparticle;

   static bool g_bRun = false;

   HHOOK g_hhook = nullptr;

   itask g_itask = 0;

   LRESULT CALLBACK LowLevelMouseProc(int nCode, WPARAM wParam, LPARAM lParam)
   {

      if (nCode == 0)
      {

         if (wParam == e_message_left_button_down
            || wParam == e_message_left_button_up
            || wParam == e_message_middle_button_down
            || wParam == e_message_middle_button_up
            || wParam == e_message_right_button_down
            || wParam == e_message_right_button_up
            )
         {

            enum_message emessage = (enum_message)wParam;

            g_pparticle->call(emessage);

         }

      }

      return ::CallNextHookEx(g_hhook, nCode, wParam, lParam);

   }


   void run()
   {

      auto ptask = get_task();

      //auto pthread = ptask->m_pthread;

      //pthread->m_bMessageThread = true;

  /*    if (!_install())
      {

         return error_failed;

      }*/

      // g_hhook = nullptr;

      g_itask = ::GetCurrentThreadId();

      MSG msg;

      ::PeekMessage(&msg, nullptr, 0, 0xffffffff, false);

      g_hhook = SetWindowsHookEx(WH_MOUSE_LL, LowLevelMouseProc, ::LoadLibraryW(L"app_core_auraclick.dll"), 0);

      while (task_get_run())
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


   void install(::particle * pparticle)
   {

      if (g_hhook != nullptr)
      {

         //return false;

         throw ::exception(error_null_pointer);

      }

      g_pparticle = pparticle;

      g_bRun = true;
      
      //return ::success;

   }


   void uninstall(::particle * pparticle)
   {

      if (g_hhook == nullptr)
      {

         //return false;

         throw ::exception(error_null_pointer);

      }

      g_pparticle = nullptr;

      PostThreadMessage((DWORD) g_itask, WM_QUIT, 0, 0);

      g_bRun = false;

      //return ::success;

   }


} // namespace mouse_hook



