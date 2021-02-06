#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "_windows.h"
#endif
#include "aura/message.h"
#include "aura/procedure.h"
#include "system_interaction.h"


namespace windowing_win32
{


   system_interaction::system_interaction()
   {

      m_ewindowflag -= e_window_flag_graphical;
      //m_bMessageWindow = true;

   }


   system_interaction::~system_interaction()
   {


   }


   void system_interaction::install_message_routing(::channel * pchannel)
   {

      ::user::interaction::install_message_routing(pchannel);

      MESSAGE_LINK(e_message_destroy, pchannel, this, &system_interaction::_001OnDestroy);
      MESSAGE_LINK(e_message_display_change, pchannel, this, &system_interaction::_001OnMessage);
      MESSAGE_LINK(WM_SETTINGCHANGE, pchannel, this, &system_interaction::_001OnMessage);
      MESSAGE_LINK(WM_FONTCHANGE, pchannel, this, &system_interaction::_001OnMessage);

   }


   bool system_interaction::is_system_message_window()
   {

      return true;

   }


   bool system_interaction::DestroyWindow()
   {

      return ::user::interaction::DestroyWindow();

   }


   void system_interaction::_001OnDestroy(::message::message * pmessage)
   {

      __pointer(::message::base) pbase(pmessage);

      ::output_debug_string("system_interaction::_001OnDestroy");

   }

   
   void system_interaction::_001OnMessage(::message::message * pmessage)
   {

      __pointer(::message::base) pbase(pmessage);

      if (pbase != nullptr)
      {

         wparam wparam = pbase->m_wparam;

         lparam lparam = pbase->m_lparam;

         string strLparamString;

         if (pbase->m_id == WM_SETTINGCHANGE && wparam == 0)
         {

            strLparamString = (const WCHAR *)(LPARAM(lparam));

         }

         if (pbase->m_id == WM_FONTCHANGE)
         {


            System.process_subject(id_os_font_change);

            //fork([this]()
              // {

                 // psession->call(e_routine_font_change);

               //});

         //}
         }
         else if (
            pbase->m_id == WM_SETTINGCHANGE &&
            strLparamString == "ImmersiveColorSet")
         {

            System.process_subject(id_os_dark_mode);

         }
         else if (pbase->m_id == e_message_display_change ||
            (pbase->m_id == WM_SETTINGCHANGE &&
               (pbase->m_wparam == SPI_SETWORKAREA)))
         {

            output_debug_string("test");

            //throw_todo();

            //System.enum_display_monitors();

            //__pointer(::user::interaction) puserinteraction;

            //while(System.get_frame(puserinteraction))
            //{

            //   try
            //   {

            //      puserinteraction->post_message(e_message_display_change);

            //   }
            //   catch(...)
            //   {
            //   }

            //}


         }

      }


   }


} // namespace windowing_win32



