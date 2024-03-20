// Moved from app_core_auraclick by camilo 2021-09-12 15:52 BRT <3ThomasBS_!!
#include "framework.h"
#include "mouse_hook.h"
#include "acme/constant/message.h"
#include "acme/exception/exception.h"
#include "acme/parallelization/task.h"
#include "acme/platform/scoped_restore.h"
#include "acme/primitive/primitive/particle.h"
#include "aura/message/user.h"


namespace input_win32
{


   bool           mouse_hook::s_bMouseHook = false;
   mouse_hook *   mouse_hook::s_pmousehook = nullptr;
   ::task_pointer mouse_hook::s_ptaskMouse;
   HHOOK          mouse_hook::s_hhookMouse = nullptr;


   mouse_hook::mouse_hook()
   {


   }


   mouse_hook::~mouse_hook()
   {


   }


   void mouse_hook::install_mouse_hook()
   {

      if (is_mouse_hook_installed())
      {

         return;

      }

      s_bMouseHook = true;

      s_pmousehook = this;

      //if (g_hhook != nullptr)
      //{

      //   //return false;

      //   throw ::exception(error_null_pointer);

      //}

      s_ptaskMouse = app_fork([this]()
      {

         _mouse_hook_task();

      });

   }


   void mouse_hook::uninstall_mouse_hook()
   {

      if (s_ptaskMouse)
      {

         s_ptaskMouse->set_finish();

      }

   }


   bool mouse_hook::is_mouse_hook_installed()
   {

      return s_bMouseHook;

   }


   LRESULT CALLBACK mouse_hook::LowLevelMouseProc(int nCode, WPARAM wParam, LPARAM lParam)
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

            s_pmousehook->mouse_proc(emessage);

         }

      }

      return ::CallNextHookEx(s_hhookMouse, nCode, wParam, lParam);

   }


   void mouse_hook::_mouse_hook_task()
   {

      //auto ptask = get_task();

      //auto pthread = ptask->m_pthread;

      //pthread->m_bMessageThread = true;

  /*    if (!_install())
      {

         return error_failed;

      }*/

      // g_hhook = nullptr;

      //g_itask = ::GetCurrentThreadId();

      try
      {

         MSG msg;

         ::PeekMessage(&msg, nullptr, 0, 0xffffffff, false);

         s_hhookMouse = SetWindowsHookEx(WH_MOUSE_LL, LowLevelMouseProc, ::LoadLibraryW(L"app_core_auraclick.dll"), 0);

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

      }
      catch (...)
      {

      }

      try
      {

         UnhookWindowsHookEx(s_hhookMouse);

      }
      catch (...)
      {

      }

      s_hhookMouse = nullptr;

      s_bMouseHook = false;

      s_pmousehook = nullptr;

      s_ptaskMouse.release();

   }


   void mouse_hook::mouse_proc(enum_message emessage)
   {

      auto pmouse = __create_new < ::message::mouse >();

      pmouse->m_atom = emessage;

      handle_message(pmouse);

   }


} // namespace input_win32



