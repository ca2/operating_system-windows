#include "framework.h"
#include "acme/constant/user_message.h"
#include "window.h"
#include "windowing.h"


unsigned int g_puiaMessageTrace[] =
{
   ::user::e_message_reposition,
   ::user::e_message_size,
   ::user::e_message_activate,
   ::user::e_message_set_focus,
   ::user::e_message_kill_focus,
   (unsigned int)-1
};

//CLASS_DECL_APEX string get_message_text(unsigned int uMessage, bool bWithNumbers);


extern unsigned int g_puiaMessageMouseMove[];
extern unsigned int g_puiaMessageWindowDeactivating[];
extern unsigned int g_puiaMessageWindowActivating[];
extern unsigned int f[];
extern unsigned int g_puiaMessageWindowCreated[];
extern unsigned int g_puiaMessageInputLanguageChange[];
extern unsigned int g_puiaMessageTrace[];

#define STATE_WINDOW_CREATION 0
#define STATE_WINDOW_CREATED 1
#define STATE_INPUT_LANGUAGE_CHANGING 2
#define STATE_WINDOW_DEACTIVATING 3
#define STATE_WINDOW_ACTIVATING 4

bool __windows_message_bypass(HWND oswindow, unsigned int message, wparam wparam, lparam lparam, lresult & lresult, unsigned int * puia)
{

   for (int i = 0; puia[i] != -1; i++)
   {

      if (message == puia[i])
      {

         //string str;

         //str.formatf("\n%s", get_message_text(message, true).c_str());

         //output_debug_string(str);

         lresult = ::DefWindowProcW(oswindow, message, wparam, lparam);

         return true;

      }

   }

   return false;

}


namespace windowing_win32
{


   bool window::__windows_message_bypass(HWND oswindow, unsigned int message, wparam wparam, lparam lparam, lresult & lresult)
   {

      //if (message == ::user::e_message_mouse_move)
      //{

      //   //output_debug_string("mm.");

      //   lresult = ::DefWindowProcW(oswindow, message, wparam, lparam);

      //   return true;

      //}
      //else if (message == ::user::e_message_set_cursor)
      //{

      //   //output_debug_string("sc.");

      //   lresult = ::DefWindowProcW(oswindow, message, wparam, lparam);

      //   return true;

      //}
      //else if (message == ::user::e_message_non_client_hit_test)
      //{

      //   //output_debug_string("ht.");

      //   lresult = ::DefWindowProcW(oswindow, message, wparam, lparam);

      //   return true;

      //}

#if 0

      if (__windows_message_bypass(oswindow, message, wparam, lparam, lresult, g_puiaMessageMouseMove))
      {

         return true;

      }


      if (pimpl->m_iState1 == STATE_WINDOW_CREATION)
      {

         if (__windows_message_bypass(oswindow, message, wparam, lparam, lresult, g_puiaMessageTopLevelCreation))
         {

            if (message == ::user::e_message_paint)
            {

               pimpl->m_iState1 = STATE_WINDOW_CREATED;

            }

            return true;

         }


      }
      else if (pimpl->m_iState1 == STATE_WINDOW_CREATED)
      {

         if (message == WM_INPUTLANGCHANGE)
         {

            pimpl->m_iState1 = STATE_INPUT_LANGUAGE_CHANGING;

         }
         else if (message == WM_IME_NOTIFY)
         {

            pimpl->m_iState1 = STATE_INPUT_LANGUAGE_CHANGING;

         }
         else if (message == ::user::e_message_non_client_activate && wparam == 0)
         {

            pimpl->m_iState1 = STATE_WINDOW_DEACTIVATING;

         }
         else
         {

            if (__windows_message_bypass(oswindow, message, wparam, lparam, lresult, g_puiaMessageWindowCreated))
            {

               return true;

            }

         }


      }

      if (pimpl->m_iState1 == STATE_INPUT_LANGUAGE_CHANGING)
      {

         if (__windows_message_bypass(oswindow, message, wparam, lparam, lresult, g_puiaMessageInputLanguageChange))
         {

            return true;

         }
         else if (message == ::user::e_message_non_client_activate && wparam == 0)
         {

            pimpl->m_iState1 = STATE_WINDOW_DEACTIVATING;

         }

      }

      if (pimpl->m_iState1 == STATE_WINDOW_DEACTIVATING)
      {

         if (__windows_message_bypass(oswindow, message, wparam, lparam, lresult, g_puiaMessageWindowDeactivating))
         {

            return true;

         }

         if (message == ::user::e_message_window_position_changing)
         {

            pimpl->m_iState1 = STATE_WINDOW_ACTIVATING;

         }


      }

      if (pimpl->m_iState1 == STATE_WINDOW_ACTIVATING)
      {

         if (__windows_message_bypass(oswindow, message, wparam, lparam, lresult, g_puiaMessageWindowActivating))
         {

            if (message == ::user::e_message_set_focus)
            {

               pimpl->m_iState1 = STATE_WINDOW_CREATED;

            }

            return true;

         }


      }

#endif

      bool bTrace = false;

      for (int i = 0; g_puiaMessageTrace[i] != -1; i++)
      {

         if (message == g_puiaMessageTrace[i])
         {

            bTrace = true;

            break;

         }

      }

      string str;

      string strMessageText = ::operating_system::get_message_text((::user::enum_message)message);

      str.formatf("%s %d", strMessageText.c_str(), message, wparam, lparam);

      if (message == ::user::e_message_activate)
      {

         if (LOWORD(wparam) == WA_ACTIVE)
         {

            str += " WA_ACTIVE";

         }
         else if (LOWORD(wparam) == WA_CLICKACTIVE)
         {

            str += " WA_CLICKACTIVE";

         }
         else if (LOWORD(wparam) == WA_INACTIVE)
         {

            str += " WA_INACTIVE";

         }

         if (HIWORD(wparam))
         {

            str += " minimized_state_active";

         }

      }

      if (bTrace)
      {

         information() << "\n" + str;

      }

      return false;

   }


} // namespace windows



